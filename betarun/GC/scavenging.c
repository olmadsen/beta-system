/*
 * BETA RUNTIME SYSTEM, Copyright (C) 1990-1991 Mjolner Informatics Aps.
 * Mod: $RCSfile: scavenging.c,v $, rel: %R%, date: $Date: 1991-01-30 10:51:33 $, SID: $Revision: 1.1 $
 * by Lars Bak.
 */
#include "beta.h"

extern ref(Object) NewCopyObject();

/*
 * IOAGc:
 *  Called from PerformGC in the assembly part of the runtime system.
 *  Make a scavenging garbage collection on IOA.
 */
IOAGc()
{
  ptr(long)      stackptr;
  handle(Object) theCell;
  ref(Object)    theObj;

  NumIOAGc++;
  IOAActive = TRUE;

  INFO_IOA( fprintf( output, "#(IOA-%d ?%d ", NumIOAGc, ReqObjectSize));
  InfoS_LabA();

  /* Initialize the ToSpace */
  ToSpaceTop       = ToSpace;
  HandledInToSpace = ToSpace;

  DEBUG_IOA( IOACheck() );

#ifdef AO_Area
  DEBUG_AOA( AOAtoIOACheck() );
  DEBUG_AOA( AOACheck() );
  ToSpacePtr = ToSpaceLimit;
  { int i; for(i=0; i < IOAMaxAge;i++) IOAAgeTable[i] = 0; }
  /* Save the state of AOA, this state is used at end of IOAGc, to proceed 
   * not handled objects.
   */
  HandledAOABlock = AOATopBlock;
  if( AOATopBlock ) HandledInAOA = AOATopBlock->top;

  AOAtoIOACount = 0;
  if( AOAtoIOAtable ){ 
    int i; ptr(long) pointer = BlockStart( AOAtoIOAtable);
    for(i=0; i<AOAtoIOAtableSize; i++){ 
      if( *pointer ){
	AOAtoIOACount++;
	ProcessAOAReference( *pointer);
      }
      pointer++;
    }
  }
  DEBUG_AOA( AOAtoIOAReport() );
  DEBUG_AOA( AOAcopied = 0; IOAcopied = 0; );
#endif


#ifdef LVR_Area
  if(LVRAIOAAge++ == -1){
    fprintf(stderr,"#Beta error: LVRAIOAAge has reached its limit!\n");
    exit(1);
  }
#endif

  /* Follow ActiveComponent */ 
  ActiveComponent->StackObj = 0;  /* the stack is not valid anymore. */
  ProcessReference( &ActiveComponent);
  CompleteScavenging();

  /* Follow the stack */
  for( stackptr = StackEnd; stackptr <= StackStart ; stackptr++){
    if( inBetaHeap(*stackptr)){
      theCell = (handle(Object)) stackptr;
      theObj  = *theCell;
      if( isObject( theObj) ){
	ProcessReference( stackptr);
	CompleteScavenging();
      }
    }else{
      /* handle value register objects on the stack ref. ../Asm/DataRegs.s */
      switch( *stackptr){
      case -8: stackptr++;
      case -7: stackptr++;
      case -6: stackptr++;
      case -5: stackptr++;
               break;
      }
    }
  }

  /* Follow all struct pointers in the Call Back Functions area. */
  if( CBFATop > CBFA ){ 
     /* The CBFArea constintsa of an array where each element has 
      * the following structure:
      *   .long (ref(Structure)) Pointer
      *   .word jsr instruction prefix
      *   .long jsr destination == HandleCallBack
      *   .word rts instruction code.
      */
     ptr(long) current;

     current = CBFA;
     while( current < CBFATop){
       if( *current != 0 ) ProcessReference( current);
       current += 3;
     }
     CompleteScavenging();
  }

#ifdef AO_Area  
  /* Objects copied til AOA until now has not been proceesed. 
   * During proceesing these objects, new objects may be copied to
   * ToSpace and AOA, therefore we must alternate between handeling
   * objects in ToSpace and AOA until no more objects is to procees.
   */
  if( AOABaseBlock ){
    if( !HandledAOABlock ){
      HandledAOABlock = AOABaseBlock; HandledInAOA = BlockStart( AOABaseBlock);
    }
    while( HandledAOABlock ){
      /* Process objects from AOAoldTop to blockPtr->top. */
      while( HandledInAOA < HandledAOABlock->top ){
	ProcessAOAObject( (ref(Object))  HandledInAOA );
	HandledInAOA = (ptr(long)) (((long) HandledInAOA)
				  + 4 * ObjectSize( (ref(Object)) HandledInAOA ));
	CompleteScavenging();
      }
      HandledAOABlock = HandledAOABlock->next;
      if( HandledAOABlock ) HandledInAOA = BlockStart( HandledAOABlock);
    }
    DEBUG_AOA( AOAtoIOACheck());
  }
  if( AOANeedCompaction)  AOAGc();
#endif

  /* Swap IOA and ToSpace */
  { ptr(long) Tmp; ptr(long) TmpTop; ptr(long) TmpLimit;

    Tmp     = IOA;     TmpTop     = IOATop;     TmpLimit     = IOALimit; 
    IOA     = ToSpace; IOATop     = ToSpaceTop; IOALimit     = ToSpaceLimit;
    ToSpace = Tmp;     ToSpaceTop = TmpTop;     ToSpaceLimit = TmpLimit;
  }

  IOAActive = FALSE;

  INFO_IOA( fprintf( output,", %d%%)\n",
		    (100 * areaSize(IOA,IOATop))/areaSize(IOA,IOALimit)));

#ifdef AO_Area
  { int limit = areaSize(IOA,IOALimit) / 10;int sum = 0;

    IOAtoAOAtreshold = 0;
    do{ sum += IOAAgeTable[IOAtoAOAtreshold++];
    }while( ( sum < limit ) && (IOAtoAOAtreshold < IOAMaxAge));
    IOAtoAOAtreshold +=1;

    INFO_IOA( fprintf( output, "#AOATreshold %d\n", IOAtoAOAtreshold));
  }
#endif

#ifdef LVR_Area
  if( LVRANeedCompaction) LVRACompaction();
#endif

  DEBUG_IOA( IOACheck() );
  DEBUG_AOA( AOACheck() );

  InfoS_LabB();

  if( ReqObjectSize *4 >= ( (long) IOALimit - (long) IOATop ) ){
    fprintf( stderr,"#IOA Heap space full, req.: %d.\n", ReqObjectSize);
    BetaExit(1);
  }
} 

/*
 * ProcessReference:
 *  Takes as input a reference to a cell residing outside IOA.
 *  If the cell refers an object residing in IOA, the 
 *  object is copied to ToSpace/AOA and the cell is updated.
 *  Furthermore one forward reference in the most enclosing
 *  object is inserted in the GC-attribute.
 */

ProcessReference( theCell)
  handle(Object) theCell;
{
  ref(Object) theObj;
  long GCAttribute;

  theObj = *theCell;

  if( inIOA(theObj)){ /* theObj is inside IOA */
    DEBUG_IOA( Claim( isObject(theObj), "ProcessReference: theObj is consistent."));
    GCAttribute = theObj->GCAttr;
    if( GCAttribute > 2048 ){ /* theObj has a forward pointer. */
      *theCell = (ref(Object)) GCAttribute;
    }else{
      if( GCAttribute >= 0 ){ /* theObj is an autonomous object. */
	*theCell = NewCopyObject( theObj);
      }else{ /* theObj is a part object. */
         int Distance;
         ref(Object) newObj;
         ref(Object) AutObj;

	 Distance = GetDistanceToEnclosingObject( theObj);
	 AutObj = (ref(Object)) Offset( theObj, Distance);
	 if( !isAutonomous(AutObj->GCAttr)) 
	   newObj = (ref(Object)) AutObj->GCAttr;
	 else
	   newObj = NewCopyObject( AutObj);
	 *theCell = (ref(Object)) Offset( newObj, -Distance);
      }
    }
    DEBUG_IOA( Claim( !inIOA(*theCell),"ProcessAOAReference: !inIOA(*theCell)"));
  }
/* PLEASE OPTIMIZE THIS. */
#ifdef AO_Area
  if( inAOA( *theCell)){ /* theCell belongs to IOA and theObj belongs to AOA. */
    *--ToSpacePtr = (long) theCell;
  }
#endif

#ifdef LVR_Area
    if( inLVRA( *theCell) ){
      theObj = *theCell;
      ((ref(ValRep)) theObj)->Proto  = (ref(ProtoType)) theCell;
      ((ref(ValRep)) theObj)->GCAttr = LVRAIOAAge;
    }
#endif
}

/*
 * ProcessObject:
 *  Takes as input a reference to an object residing in the ToSpace.
 *  It traverse the object and process all the references in it.    
 */

ProcessObject(theObj)
  ref(Object) theObj;
{ ref(ProtoType) theProto;

  theProto = theObj->Proto;

  if( (long) theProto < 0 ){  
    switch( (long) theProto ){
    case ValRepPTValue: return; /* No references in the type of object, so do nothing*/

    case RefRepPTValue:
      /* Scan the repetition and follow all entries */
      { ptr(long) pointer;
        register long size, index;

        size = toRefRep(theObj)->HighBorder;
        pointer =  (ptr(long)) &toRefRep(theObj)->Body[0];

        for(index=0; index<size; index++) 
          if( *pointer != 0) ProcessReference( pointer++ );
          else pointer++;
      }
      
      return;

    case ComponentPTValue:
      { ref(Component) theComponent;

        theComponent = Coerce( theObj, Component);
        ProcessReference( &theComponent->StackObj);
        ProcessReference( &theComponent->CallerComp);
        ProcessReference( &theComponent->CallerObj);
        ProcessObject( ComponentItem( theComponent));
      }
      return;

    case StackObjectPTValue:
      { ref(StackObject) theStackObject;
        ptr(long)        stackptr; 
        handle(Object)   theCell; 
        ptr(long)        theEnd;

        DEBUG_IOA( fprintf( output, "+"));

        theStackObject = Coerce(theObj, StackObject);

	DEBUG_IOA( Claim(theStackObject->StackSize <= theStackObject->ObjectSize,
			 "ProcessReference: StackObjectType: Stack > Object") );

        theEnd = &theStackObject->Body[0] + theStackObject->StackSize;

        for( stackptr = &theStackObject->Body[0]; stackptr < theEnd; stackptr++){
          if( inIOA( *stackptr)){
            theCell = (handle(Object)) stackptr;
            if( isObject( *theCell ) ) ProcessReference( stackptr);
          }else{
             switch( *stackptr ){
	     case -8: stackptr++;
	     case -7: stackptr++;
	     case -6: stackptr++;
             case -5: stackptr++;
	       break;
	     }
          }
	}
      }
      return;

    case StructurePTValue:
      ProcessReference( &(toStructure(theObj))->iOrigin );
      return;
    }
  }else{
    ptr(short)  Tab;
    ptr(long)   theCell;

    /* Calculate a pointer to the GCTabel inside the ProtoType. */
    Tab = (ptr(short)) ((long) ((long) theProto) + ((long) theProto->GCTabOff));

    /* Handle all the references in the Object. */
    while( *Tab != 0 ){
      theCell = (ptr(long)) Offset( theObj, *Tab++ );
      if( *theCell != 0 ) ProcessReference( theCell );
    }
    Tab++;

    /* Handle all the static objects. 
     * The static table have the following structure:
     * { .word Offset
     *   .long T_entry_point
     *   .word Distance_To_Inclosing_Object
     * }*
     * This table contains all static objects on all levels.
     * Here vi only need to perform ProcessObject on static objects
     * on 1 level. The recursion in ProcessObject handle other
     * levels. 
     * The way to determine the level of an static object is to 
     * compare the Offset and the Distance_To_Inclosing_Object.
     */

    while( *Tab != 0 ){
      if( *Tab == -Tab[3] ) 
	ProcessObject( Offset( theObj, *Tab * 4));
      Tab += 4;
    }
  }
}


#ifdef AO_Area
/*
 * ProcessAOAReference:
 *  Takes as input a reference to a cell residing outside IOA.
 *  If the cell refers an object residing in IOA, the 
 *  object is copied to ToSpace/AOA and the cell is updated.
 *  Furthermore one forward reference in the most enclosing
 *  object is inserted in the GC-attribute.
 */
ProcessAOAReference( theCell)
  handle(Object) theCell;
{
  ref(Object) theObj;
  long GCAttribute;

  DEBUG_AOA( Claim( inAOA( theCell),"#ProcessAOAReference: theCell inside AOA\n"));
  theObj = *theCell;

  if( inIOA(theObj)){ /* theObj is inside IOA */
    GCAttribute = theObj->GCAttr;
    if( GCAttribute > 2048 ){ /* theObj has a forward pointer. */
      *theCell = (ref(Object)) GCAttribute;
    }else{
      if( GCAttribute >= 0 ){ /* theObj is an autonomous object. */
	*theCell = NewCopyObject( theObj);
      }else{ /* theObj is a part object. */
         int Distance;
         ref(Object) newObj;
         ref(Object) AutObj;

	 Distance = GetDistanceToEnclosingObject( theObj);
	 AutObj = (ref(Object)) Offset( theObj, Distance);
	 if( !isAutonomous(AutObj->GCAttr)) 
	   newObj = (ref(Object)) AutObj->GCAttr;
	 else
	   newObj = NewCopyObject( AutObj);
	 *theCell = (ref(Object)) Offset( newObj, -Distance);
      }
    }
  }
#ifdef LVR_Area
  if( inLVRA(theObj) )
    ((ref(ValRep)) theObj)->Proto  = (ref(ProtoType)) theCell;
#endif
  DEBUG_AOA( Claim( !inIOA(*theCell),"ProcessAOAReference: !inIOA(*theCell)"));
  /* Insert 'theCell' in the AOAtoIOAtable iff *theCell is inToSpace. */
  if( inToSpace( *theCell ) ) AOAtoIOAInsert( theCell);
}

/*
 * ProcessAOAObject:
 *  Takes as input a reference to an object residing in the AOA.
 *  It traverse the object and process all the references in it.    
 */

ProcessAOAObject(theObj)
  ref(Object) theObj;
{ ref(ProtoType) theProto;

  theProto = theObj->Proto;

  if( (long) theProto < 0 ){  
    switch( (long) theProto ){
    case ValRepPTValue: 
      return; /* No references in the type of object, so do nothing*/
    case RefRepPTValue:
      /* Scan the repetition and follow all entries */
      { ptr(long) pointer;
        register long size, index;

        size = toRefRep(theObj)->HighBorder;
        pointer =  (ptr(long)) &toRefRep(theObj)->Body[0];
        for(index=0; index<size; index++) 
          if( *pointer != 0) ProcessAOAReference( pointer++ );
          else pointer++;
      }
      return;
    case ComponentPTValue:
      { ref(Component) theComponent;
        theComponent = Coerce( theObj, Component);
        ProcessAOAReference( &theComponent->StackObj);
        ProcessAOAReference( &theComponent->CallerComp);
        ProcessAOAReference( &theComponent->CallerObj);
        ProcessAOAObject( ComponentItem( theComponent));
      }
      return;
    case StackObjectPTValue:
       Claim( FALSE, "ProcessAOAObject: StackObject in AOA");
       return;
    case StructurePTValue:
      ProcessAOAReference( &(toStructure(theObj))->iOrigin );
      return;
    }
  }else{
    ptr(short)  Tab;
    ptr(long)   theCell;

    /* Calculate a pointer to the GCTabel inside the ProtoType. */
    Tab = (ptr(short)) ((long) ((long) theProto) + ((long) theProto->GCTabOff));

    /* Handle all the references in the Object. */
    while( *Tab != 0 ){
      theCell = (ptr(long)) Offset( theObj, *Tab++ );
      if( *theCell != 0 ) ProcessAOAReference( theCell );
    }
    Tab++;


    /* Handle all the static objects. 
     * The static table have the following structure:
     * { .word Offset
     *   .long T_entry_point
     *   .word Distance_To_Inclosing_Object
     * }*
     * This table contains all static objects on all levels.
     * Here vi only need to perform ProcessAOAObject on static objects
     * on 1 level. The recursion in ProcessAOAObject handle other
     * levels. 
     * The way to determine the level of an static object is to 
     * compare the Offset and the Distance_To_Inclosing_Object.
     */

    while( *Tab != 0 ){
      if( *Tab == -Tab[3] ) 
	ProcessAOAObject( Offset( theObj, *Tab * 4));
      Tab += 4;
    }


  }
}
#endif

/*
 * CompleteScavenging:
 *  Process all the objects in the ToSpace, which has not been handled yet.
 *  The reason is to ensure the locallity of related objects, to avoid
 *  unneseccary swapping. 
 */

CompleteScavenging()
{
  ref(Object) theObj;

  while( HandledInToSpace < ToSpaceTop){
    theObj = (ref(Object)) HandledInToSpace;
    HandledInToSpace = (ptr(long)) (((long) HandledInToSpace)
                                + 4*ObjectSize(theObj));
    ProcessObject( theObj);
  }
  DEBUG_IOA( Claim( HandledInToSpace == ToSpaceTop,
		   "CompleteScavenging: HandledInToSpace == ToSpaceTop"));
}

/*
 * GetDistanceToEnclosingObject:
 *  Find the offset (negative) to the most inclosing object e.g.
 *  the offset to the autonomous object in which theObj reside.  
 */
   
int GetDistanceToEnclosingObject( theObj)
  ref(Object)theObj;
{
  int Distance, GCAttribute;

  Distance = 0;
  GCAttribute = theObj->GCAttr*4;
  while( GCAttribute < 0 ){
     Distance += GCAttribute; 
     theObj = (struct Object *) Offset( theObj, GCAttribute);
     GCAttribute = theObj->GCAttr*4;
  }
  return Distance;
}

#ifdef RTDEBUG
IOACheck()
{ ref(Object) theObj;
  long        theObjectSize;

  theObj = (ref(Object)) IOA;
  while( (ptr(long)) theObj < IOATop ){
    theObjectSize = 4*ObjectSize( theObj);
    IOACheckObject( theObj);
    theObj = (ref(Object)) Offset( theObj, theObjectSize);
  }
} 

IOACheckObject( theObj)
  ref(Object) theObj;
{ ref(ProtoType) theProto;

  theProto = theObj->Proto;

  if( (long) theProto < 0 ){  
    switch( (long) theProto ){
    case ValRepPTValue: return; /* No references in the type of object, so do nothing*/

    case RefRepPTValue:
      /* Scan the repetition and follow all entries */
      { ptr(long) pointer;
        register long size, index;

        size = toRefRep(theObj)->HighBorder;
        pointer =  (ptr(long)) &toRefRep(theObj)->Body[0];

        for(index=0; index<size; index++) 
          if( *pointer != 0) IOACheckReference( pointer++ );
          else pointer++;
      }
      
      return;

    case ComponentPTValue:
      { ref(Component) theComponent;

        theComponent = Coerce( theObj, Component);
        IOACheckReference( &theComponent->StackObj);
        IOACheckReference( &theComponent->CallerComp);
        IOACheckReference( &theComponent->CallerObj);
        IOACheckObject( ComponentItem( theComponent));
      }
      return;

    case StackObjectPTValue:
      { ref(StackObject) theStackObject;
        ptr(long)        stackptr; 
        handle(Object)   theCell; 
        ptr(long)        theEnd;

        theStackObject = Coerce(theObj, StackObject);

        theEnd = &theStackObject->Body[0] + theStackObject->StackSize;

        for( stackptr = &theStackObject->Body[0]; stackptr < theEnd; stackptr++){
          if( inIOA( *stackptr)){
            theCell = (handle(Object)) stackptr;
            if( isObject( *theCell ) ) IOACheckReference( stackptr);
          }else{
             switch( *stackptr ){
	     case -8: stackptr++;
	     case -7: stackptr++;
	     case -6: stackptr++;
             case -5: stackptr++;
	       break;
	     }
          }
	}
      }
      return;

    case StructurePTValue:
      IOACheckReference( &(toStructure(theObj))->iOrigin );
      return;
    }
  }else{
    ptr(short)  Tab;
    ptr(long)   theCell;

    /* Calculate a pointer to the GCTabel inside the ProtoType. */
    Tab = (ptr(short)) ((long) ((long) theProto) + ((long) theProto->GCTabOff));

    /* Handle all the references in the Object. */
    while( *Tab != 0 ){
      theCell = (ptr(long)) Offset( theObj, *Tab++ );
      if( *theCell != 0 ) IOACheckReference( theCell );
    }
    Tab++;


    /* Handle all the static objects. 
     * The static table have the following structure:
     * { .word Offset
     *   .long T_entry_point
     *   .word Distance_To_Inclosing_Object
     * }*
     * This table contains all static objects on all levels.
     * Here vi only need to perform ProcessObject on static objects
     * on 1 level. The recursion in ProcessObject handle other
     * levels. 
     * The way to determine the level of an static object is to 
     * compare the Offset and the Distance_To_Inclosing_Object.
     */

    while( *Tab != 0 ){
      if( *Tab == -Tab[3] ) 
	IOACheckObject( Offset( theObj, *Tab * 4));
      Tab += 4;
    }
  }
}

IOACheckReference( theCell)
  handle(Object) theCell;
{
  int i; ptr(long) pointer = BlockStart( AOAtoIOAtable);
  int found = FALSE;

  if( *theCell ){
    Claim( inAOA(*theCell) || inIOA(*theCell) || inLVRA(*theCell),
	  "IOACheckReference: *theCell outside IOA, AOA and LVRA");
  }
}
#endif
