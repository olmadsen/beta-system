/*
 * BETA RUNTIME SYSTEM, Copyright (C) 1990-1991 Mjolner Informatics Aps.
 * Mod: $RCSfile: scavenging.c,v $, rel: %R%, date: $Date: 1992-08-19 11:56:02 $, SID: $Revision: 1.27 $
 * by Lars Bak.
 */
#include "beta.h"
#include "scavenging.h"

extern ref(Object) NewCopyObject();

#ifdef sparc
/* Traverse an activation record (AR) [ar, end[
   Notice end is *not* included
*/

void ProcessAR(struct RegWin *ar, struct RegWin *end)
{
  struct Object **theCell = (struct Object **) &ar[1];

  Claim(((long)  ar) % 4 == 0, "ProcessAR: ar is 4 byte aligned");
  Claim(((long) end) % 4 == 0, "ProcessAR: end is 4 byte aligned");

  if (inBetaHeap(ar->i0) && isObject(ar->i0)) ProcessReference(&ar->i0);
  if (inBetaHeap(ar->i1) && isObject(ar->i1)) ProcessReference(&ar->i1);
  if (inBetaHeap(ar->i2) && isObject(ar->i2)) ProcessReference(&ar->i2);
  if (inBetaHeap(ar->i3) && isObject(ar->i3)) ProcessReference(&ar->i3);

  for (; theCell != (struct Object **) end; theCell += 2)
    if (inBetaHeap(*theCell) && isObject(*theCell))
      ProcessReference(theCell);
  CompleteScavenging();
}

/* Doesn't yet handle Callback */
void ProcessStack()
{
  struct RegWin *theAR;

  /* Flush register windows to stack */
  asm("ta 3");
  for (theAR =  (struct RegWin *) StackEnd;
       theAR != (struct RegWin *) lastCompBlock;
       theAR =  (struct RegWin *) theAR->fp)
    ProcessAR(theAR, (struct RegWin *) theAR->fp);
}

void ProcessStackObj(struct StackObject *theStack)
{
    struct RegWin *theAR;
    int delta = (char *) &theStack->Body[1] - (char *) theStack->Body[0];

    for (theAR =  (struct RegWin *) &theStack->Body[1];
	 theAR != (struct RegWin *) &theStack->Body[theStack->StackSize];
	 theAR =  (struct RegWin *) (theAR->fp + delta)) {
	Claim(&theStack->Body[1] <= (long *) theAR
	      && (long *) theAR <= &theStack->Body[theStack->StackSize],
	      "ProcessStackObj: theAR in StackObject");
	ProcessAR(theAR, (struct RegWin *) (theAR->fp + delta));
    }
}
#else
/* Traverse the StackArea [low..high] and Process all references within it. */
void ProcessStackPart( low, high)
     ptr(long) low;
     ptr(long) high;
{
  ptr(long) current = low;
  ref(Object) theObj;
  handle(Object) theCell;
  
  DEBUG_IOA( fprintf( output, "[%x..%x]", low, high));
  
  while( current <= high ){
    if( inBetaHeap( *current)){
      theCell = (handle(Object)) current;
      theObj  = *theCell;
      if( isObject( theObj) ){
	if( inLVRA( theObj) || isValRep(theObj) ){
	  DEBUG_IOA( fprintf( output, "(STACK(%d) is *ValRep)", current-low));
	}else{
	  ProcessReference( current);
	  CompleteScavenging();
	}
      }
    }else{
      /* handle value register objects on the stack ref. ../Asm/DataRegs.s */
      switch( *current){
      case -8: current++;
      case -7: current++;
      case -6: current++;
      case -5: current++;
	break;
      }
    }
    current++;
  }
}

void ProcessStack()
{
  ptr(long)          theTop;
  ptr(long)          theBottom;
  
  ref(CallBackFrame)  theFrame;
  ref(ComponentBlock) currentBlock;
  
  /*
   * First handle the topmost component block
   */
  theTop    = StackEnd;
  theBottom = (ptr(long)) lastCompBlock;
  theFrame  = ActiveCallBackFrame;
  /* Follow the stack */
  while( theFrame){
    ProcessStackPart( theTop, (long) theFrame - 4);
    theTop   = theFrame->betaTop;
    theFrame = theFrame->next;
  }
  ProcessStackPart( theTop, theBottom+4);  
  
  /*
   * Then handle the remaining component blocks.
   */
  currentBlock = lastCompBlock;
  while( currentBlock->next ){
    theTop    = (ptr(long)) ((long) currentBlock + 12);
    theBottom = (ptr(long)) currentBlock->next;
    theFrame  = currentBlock->callBackFrame;
    while( theFrame){
      ProcessStackPart( theTop, (long) theFrame - 4);
      theTop   = theFrame->betaTop;
      theFrame = theFrame->next;
    }
    ProcessStackPart( theTop, theBottom+4);  
    currentBlock = currentBlock->next;
  }
}
#endif

static int FreePercentage( bottom, top, limit)
     int bottom, top, limit;
{
  return (100 * areaSize(top, limit))/areaSize(bottom, limit); 
}

/*
 * IOAGc:
 *  Called from DoGC in the assembly part of the runtime system.
 *  Make a scavenging garbage collection on IOA.
 */
void IOAGc()
{
#ifdef macintosh
  RotateTheCursor();
#endif
  
  NumIOAGc++;
  IOAActive = TRUE;
  
  INFO_IOA( fprintf( output, "#(IOA-%d %d? ", NumIOAGc, ReqObjectSize));
  InfoS_LabA();
  
  /* Initialize the ToSpace */
  ToSpaceTop       = ToSpace;
  HandledInToSpace = ToSpace;

  DEBUG_IOA( IOACheck() );
  DEBUG_LVRA( LVRACheck() );
  
#ifdef AO_Area
  DEBUG_AOA( AOAtoIOACheck() );
  DEBUG_AOA( AOACheck() );
  ToSpacePtr = ToSpaceLimit;
  ToSpaceToAOAtable = ToSpaceLimit;
  { int i; for(i=0; i < IOAMaxAge;i++) IOAAgeTable[i] = 0; }
  /* Save the state of AOA, this state is used at end of IOAGc, to proceed 
   * not handled objects.
   */
  HandledAOABlock = AOATopBlock;
  if( AOATopBlock ) HandledInAOA = AOATopBlock->top;
  
  AOAtoIOACount = 0;
  if( AOAtoIOAtable ){ 
    int i; ptr(long) pointer = BlockStart( AOAtoIOAtable);
    INFO_IOA( fprintf(output, "# AOAtoIOAtable\n"));
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
  
  /* Follow ActiveComponent */ 
  ActiveComponent->StackObj = 0;  /* the stack is not valid anymore. */
  ProcessReference( &ActiveComponent);
#ifdef sparc
  ProcessReference( BasicItemHandle );
#endif
  CompleteScavenging();

  ProcessStack();
  
  /* Follow all struct pointers in the Call Back Functions area. */
  if( CBFATop != CBFA->entries ){
    ref(CallBackArea) cbfa = CBFA;
    ref(CallBackEntry) current = cbfa->entries;
    long limit = (long) cbfa->entries + CBFABlockSize + sizeof(struct CallBackEntry);
    
    for (; current != CBFATop; current++){
      if ( (long) current > limit){
	/* Go to next block */
	cbfa = cbfa->next;        /* guarentied to be non-nil since current != CBFATop */
	current = cbfa->entries;  /* guarentied to be different from CBFATop. If not the block
				     would not have been allocated */
	limit = (long) cbfa->entries + CBFABlockSize + sizeof(struct CallBackEntry);
      }
      if (current->theStruct)
	ProcessReference(&current->theStruct);
    }
    CompleteScavenging();
  }
  
#ifdef DOT
  if( DOTSize > 0 ){
    /* The Debugger Object Table is in use, so traverse this table. */
    ptr(long) current = DOT;
    while( current < DOTTop){
      if( *current != 0 ) UpdateReference( current);
      current++;
    }
    CompleteScavenging(); /* CHECK */
  }
#endif
  
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
				    + 4*ObjectSize( (ref(Object)) HandledInAOA ));
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
    
    IOA     = ToSpace;                          
#ifndef sparc
    IOATop    = ToSpaceTop; 
#else
    IOATopoff = (char *) ToSpaceTop - (char *) IOA;
#endif
    IOALimit     = ToSpaceLimit;
    
    ToSpace = Tmp;     ToSpaceTop = TmpTop;     ToSpaceLimit = TmpLimit;
  }
  
  IOAActive = FALSE;
  
#ifdef AO_Area
  { int limit = areaSize(IOA,IOALimit) / 10;int sum = 0;
    
    IOAtoAOAtreshold = 0;
    do{ sum += IOAAgeTable[IOAtoAOAtreshold++];
      }while( ( sum < limit ) && (IOAtoAOAtreshold < IOAMaxAge));
    IOAtoAOAtreshold +=1;
  }
  DEBUG_IOA( fprintf( output, " treshold=%d", IOAtoAOAtreshold));
  DEBUG_IOA( fprintf( output, " IOAtoAOA=%d", areaSize(ToSpacePtr,IOALimit)));
#endif
  
  INFO_IOA( fprintf( output," %d%%)\n",
		    (100 * areaSize(IOA,IOATop))/areaSize(IOA,IOALimit)));
  
  DEBUG_IOA( IOACheck() );
  DEBUG_AOA( AOACheck() );
  DEBUG_LVRA( LVRACheck() );
  InfoS_LabB();
  
  /* Based on IOAPercentage, determine if IOA space is exhausted. */
  
  if( FreePercentage( IOA, (long) IOATop + ReqObjectSize*4, IOALimit) < IOAPercentage ){
    fprintf( output,"#IOA Heap space full, request: %d.\n", ReqObjectSize);
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
 *  TIPS: USE theObj instead of newObj and inline GetDistanceToEnc....
 */

void ProcessReference( theCell)
     handle(Object) theCell;
{
  ref(Object) theObj;
  long GCAttribute;
  
  theObj = *theCell;
  
  if( inIOA(theObj)){
    /* 'theObj' is inside IOA */
    DEBUG_IOA( Claim(isObject(theObj),"ProcessReference: theObj is consistent."));
    GCAttribute = theObj->GCAttr;
    if( isForward(GCAttribute) ){ 
      /* theObj has a forward pointer. */
      *theCell = (ref(Object)) GCAttribute;
      DEBUG_LVRA( Claim( !inLVRA(GCAttribute), "ProcessAOAReference: Forward ValRep"));
#ifdef AO_Area
      /* If the forward pointer refers an AOA object, insert
       * theCell in ToSpaceToAOAtable.
       */
      if( !inToSpace( GCAttribute))
	if( inAOA( GCAttribute)){
	  if (ToSpacePtr) *--ToSpacePtr = (long) theCell;
	}
#endif
    }else{
      if( GCAttribute >= 0 ){ 
	/* '*theCell' is an autonomous object. */
	*theCell = NewCopyObject( *theCell, theCell);
      }else{
	/* theObj is a part object. */
	int Distance;
	ref(Object) newObj;
	ref(Object) AutObj;
	
	Distance = GetDistanceToEnclosingObject( theObj);
	AutObj = (ref(Object)) Offset( theObj, Distance);
	if( isForward(AutObj->GCAttr) ){
	  newObj = (ref(Object)) AutObj->GCAttr;
#ifdef AO_Area
	  /* If the forward pointer refers an AOA object, insert
	   * theCell in ToSpaceToAOAtable.
	   */
	  if( !inToSpace( AutObj->GCAttr))
	    if( inAOA( AutObj->GCAttr)){
	      if (ToSpacePtr) *--ToSpacePtr = (long) theCell;
	    }
#endif
	}else
	  newObj = NewCopyObject( AutObj, theCell);
	*theCell = (ref(Object)) Offset( newObj, -Distance);
      }
    }
    DEBUG_IOA( Claim( !inIOA(*theCell),"ProcessAOAReference: !inIOA(*theCell)"));
  }else{
    /* '*theCell' is pointing outside IOA */
#ifdef AO_Area
    /* If the forward pointer refers an AOA object, insert
     * theCell in ToSpaceToAOAtable.
     */
    if( inAOA( *theCell)){
      *--ToSpacePtr = (long) theCell;
      return;
    }
#endif
#ifdef LVR_Area
    if( inLVRA( *theCell)){
      /* Preserve the LVRA-cycle. */
      ((ref(ValRep)) *theCell)->GCAttr = (long) theCell;
      DEBUG_LVRA( Claim( isValRep(*theCell),
			"ProcessObject: isValRep(*theCell)"));
      return;
    }
#endif
  }
}

/*
 * ProcessObject:
 *  Takes as input a reference to an object residing in the ToSpace.
 *  It traverse the object and process all the references in it.    
 */

void ProcessObject(theObj)
     ref(Object) theObj;
{ ref(ProtoType) theProto;
  
  theProto = theObj->Proto;
  
  if( (long) theProto < 0 ){  
    switch( (int) theProto ){
    case (int) ByteRepPTValue:
    case (int) WordRepPTValue:
    case (int) DoubleRepPTValue:
    case (int) ValRepPTValue: return; /* No references in the type of object, so do nothing*/
      
    case (int) RefRepPTValue:
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
      
    case (int) ComponentPTValue:
      { ref(Component) theComponent;
	
        theComponent = Coerce( theObj, Component);
        ProcessReference( &theComponent->StackObj);
        ProcessReference( &theComponent->CallerComp);
        ProcessReference( &theComponent->CallerObj);
        ProcessObject( ComponentItem( theComponent));
      }
      return;
      
    case (int) StackObjectPTValue:
#ifndef sparc
      { ref(StackObject) theStackObject;
        ptr(long)        stackptr; 
        handle(Object)   theCell; 
        ptr(long)        theEnd;
	
        theStackObject = Coerce(theObj, StackObject);
	
	DEBUG_IOA( Claim(theStackObject->StackSize <= theStackObject->ObjectSize,
			 "ProcessReference: StackObjectType: Stack > Object") );
	
        theEnd = &theStackObject->Body[0] + theStackObject->StackSize;
	
        for( stackptr = &theStackObject->Body[0]; stackptr < theEnd; stackptr++){
          if( inBetaHeap( *stackptr)){
            theCell = (handle(Object)) stackptr;
            if( isObject( *theCell ) )
	      ProcessReference( stackptr);
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
#else
      ProcessStackObj((struct StackObject *)theObj);
#endif
      return;
      
    case (int) StructurePTValue:
      ProcessReference( &(toStructure(theObj))->iOrigin );
      return;
    }
  }else{
#ifdef UGLY_CODE
    ptr(short)  Tab;
    ptr(long)   theCell;
    
    /* Calculate a pointer to the GCTabel inside the ProtoType. */
    Tab = (ptr(short)) ((long) ((long) theProto) + ((long) theProto->GCTabOff));
    
    /* Handle all the static objects. 
     * The static table have the following structure:
     * { .word Offset
     *   .word Distance_To_Inclosing_Object
     *   .long T_entry_point
     * }*
     * This table contains all static objects on all levels.
     * Here vi only need to perform ProcessObject on static objects
     * on 1 level. The recursion in ProcessObject handle other
     * levels. 
     * The way to determine the level of an static object is to 
     * compare the Offset and the Distance_To_Inclosing_Object.
     */
    
    while( *Tab != 0 ){
      if( *Tab == -Tab[1] ) 
	ProcessObject( Offset( theObj, *Tab * 4));
      Tab += 4;
    }
    Tab++;
    
    /* Handle all the references in the Object. */
    while( *Tab != 0 ){
      theCell = (ptr(long)) Offset( theObj, *Tab++ );
      if( *theCell != 0 ) ProcessReference( theCell );
    }
#else
    struct GCEntry *tab =
      (struct GCEntry *) ((char *) theProto + theProto->GCTabOff);
    short *refs_ofs;
    struct Object **theCell;

    /* Handle all the static objects. 
     *
     * The static table, tab[0], tab[1], 0,
     * contains all static objects on all levels.
     * Here we only need to perform ProcessObject on static objects
     * on 1 level. The recursion in ProcessObject handle other
     * levels. 
     * The way to determine the level of an static object is to 
     * compare the Offset (StaticOff) and the
     * Distance_To_Inclosing_Object (OrigOff).
     */
    for (;tab->StaticOff; ++tab)
      if (tab->StaticOff == -tab->OrigOff)
	ProcessObject((long *)theObj + tab->StaticOff);
    
    /* Handle all the references in the Object. */
    for (refs_ofs = &tab->StaticOff + 1; *refs_ofs; ++refs_ofs) {
	theCell = (struct Object **) ((char *) theObj + *refs_ofs);
	if (*theCell) ProcessReference(theCell);
    }
#endif
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
void ProcessAOAReference( theCell)
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
      DEBUG_LVRA( Claim( !inLVRA(GCAttribute),
			"ProcessAOAReference: Forward ValRep"));
    }else{
      if( GCAttribute >= 0 ){ /* theObj is an autonomous object. */
	*theCell = NewCopyObject( theObj, 0);
#ifdef LVR_Area
	if( !inToSpace( *theCell)){
	  if( inLVRA( *theCell)){
	    /* Preserve the LVRA-cycle. */
	    ((ref(ValRep)) *theCell)->GCAttr = (long) theCell;
	    DEBUG_LVRA( Claim( isvalRep(*theCell),
			      "ProcessAOAReference: isValRep(*theCell)"));
	  }
	}
#endif
      }else{ /* theObj is a part object. */
	int Distance;
	ref(Object) newObj;
	ref(Object) AutObj;
	
	Distance = GetDistanceToEnclosingObject( theObj);
	AutObj = (ref(Object)) Offset( theObj, Distance);
	if( !isAutonomous(AutObj->GCAttr)) 
	  newObj = (ref(Object)) AutObj->GCAttr;
	else
	  newObj = NewCopyObject( AutObj, 0);
	*theCell = (ref(Object)) Offset( newObj, -Distance);
      }
    }
  }else{
#ifdef LVR_Area
    if( inLVRA( *theCell)){
      /* Preserve the LVRA-cycle. */
      ((ref(ValRep)) *theCell)->GCAttr = (long) theCell;
      DEBUG_LVRA( Claim( isValRep(*theCell), 
			"ProcessAOAReference: isValRep(*theCell)"));
    }
#endif
  }
  DEBUG_AOA( Claim( !inIOA(*theCell),"ProcessAOAReference: !inIOA(*theCell)"));
  DEBUG_AOA( if( inAOA( *theCell)){ AOACheckObjectSpecial( *theCell); } );
  
  /* Insert 'theCell' in the AOAtoIOAtable iff *theCell is inToSpace. */
  if( inToSpace( *theCell ) ) AOAtoIOAInsert( theCell);
}

/*
 * ProcessAOAObject:
 *  Takes as input a reference to an object residing in the AOA.
 *  It traverse the object and process all the references in it.    
 */

void ProcessAOAObject(theObj)
     ref(Object) theObj;
{ ref(ProtoType) theProto;
  
  theProto = theObj->Proto;
  
  if( (long) theProto < 0 ){  
    switch( (int) theProto ){
    case (int) ByteRepPTValue: 
    case (int) WordRepPTValue: 
    case (int) DoubleRepPTValue: 
    case (int) ValRepPTValue: 
      return; /* No references in the type of object, so do nothing*/
    case (int) RefRepPTValue:
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
    case (int) ComponentPTValue:
      { ref(Component) theComponent;
        theComponent = Coerce( theObj, Component);
        ProcessAOAReference( &theComponent->StackObj);
        ProcessAOAReference( &theComponent->CallerComp);
        ProcessAOAReference( &theComponent->CallerObj);
        ProcessAOAObject( ComponentItem( theComponent));
      }
      return;
    case (int) StackObjectPTValue:
      Claim( FALSE, "ProcessAOAObject: No StackObject in AOA");
      return;
    case (int) StructurePTValue:
      ProcessAOAReference( &(toStructure(theObj))->iOrigin );
      return;
    }
  }else{
    ptr(short)  Tab;
    ptr(long)   theCell;
    
    /* Calculate a pointer to the GCTabel inside the ProtoType. */
    Tab = (ptr(short)) ((long) ((long) theProto) + ((long) theProto->GCTabOff));
    
    /* Handle all the static objects. 
     * The static table have the following structure:
     * { .word Offset
     *   .word Distance_To_Inclosing_Object
     *   .long T_entry_point
     * }*
     * This table contains all static objects on all levels.
     * Here vi only need to perform ProcessAOAObject on static objects
     * on 1 level. The recursion in ProcessAOAObject handle other
     * levels. 
     * The way to determine the level of an static object is to 
     * compare the Offset and the Distance_To_Inclosing_Object.
     */
    
    while( *Tab != 0 ){
      if( *Tab == -Tab[1] ) 
	ProcessAOAObject( Offset( theObj, *Tab * 4));
      Tab += 4;
    }
    Tab++;
    
    /* Handle all the references in the Object. */
    while( *Tab != 0 ){
      theCell = (ptr(long)) Offset( theObj, *Tab++ );
      if( *theCell != 0 ) ProcessAOAReference( theCell );
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

void CompleteScavenging()
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
void IOACheck()
{
    ref(Object) theObj;
    long        theObjectSize;
    
    theObj = (ref(Object)) IOA;
    while ((long *) theObj < IOATop) {
	theObjectSize = 4*ObjectSize(theObj);
	IOACheckObject (theObj);
	theObj = (ref(Object)) Offset(theObj, theObjectSize);
    }
}

void IOACheckObject (theObj)
     ref(Object) theObj;
{
    ref(ProtoType) theProto;
  
    theProto = theObj->Proto;
  
    Claim( !inBetaHeap(theProto),"#IOACheckObject: !inBetaHeap(theProto)");
  
    if( (long) theProto < 0 ){  
	switch( (int) theProto ){
	  case (int) ByteRepPTValue:
	  case (int) WordRepPTValue:
	  case (int) DoubleRepPTValue:
	  case (int) ValRepPTValue:
	    /* No references in the type of object, so do nothing*/
	    return;
      
	  case (int) RefRepPTValue:
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
      
	  case (int) ComponentPTValue:
	    { ref(Component) theComponent;
	
	      theComponent = Coerce( theObj, Component);
	      if (theComponent->StackObj == (ref(StackObject))-1) {
		  printf("\nIOACheckObject: theComponent->StackObj=-1, skipped!\n");
	      } else {
		  IOACheckReference( &theComponent->StackObj);
	      }
	      IOACheckReference( &theComponent->CallerComp);
	      IOACheckReference( &theComponent->CallerObj);
	      IOACheckObject( ComponentItem( theComponent));
	  }
	    return;
      
	  case (int) StackObjectPTValue:
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
      
	  case (int) StructurePTValue:
	    IOACheckReference( &(toStructure(theObj))->iOrigin );
	    return;
	}
    } else {
	short *Tab;
	long *theCell;
    
	/* Calculate a pointer to the GCTabel inside the ProtoType. */
	Tab = (short *) ((long) theProto + (long) theProto->GCTabOff);
    
	/* Handle all the static objects. 
	 * The static table have the following structure:
	 * { .word Offset
	 *   .word Distance_To_Inclosing_Object
	 *   .long T_entry_point
	 * }*
	 * This table contains all static objects on all levels.
	 * Here vi only need to perform ProcessObject on static objects
	 * on 1 level. The recursion in ProcessObject handle other
	 * levels. 
	 * The way to determine the level of an static object is to 
	 * compare the Offset and the Distance_To_Inclosing_Object.
	 */
	
	while( *Tab != 0 ){
	    if( *Tab == -Tab[1] ) 
	      IOACheckObject( Offset( theObj, *Tab * 4));
	    Tab += 4;
	}
	Tab++;
    
	/* Handle all the references in the Object. */
	while (*Tab != 0) {
	    theCell = (long *) Offset(theObj, *Tab++);
	    if (*theCell != 0) IOACheckReference(theCell);
	}
    }
}

void IOACheckReference(theCell)
     handle(Object) theCell;
{
  if( *theCell ){
      if (!(inIOA(*theCell) || inAOA(*theCell) || inLVRA(*theCell)))
	Claim( inIOA(*theCell) || inAOA(*theCell) || inLVRA(*theCell),
	      "IOACheckReference: *theCell inside IOA, AOA or LVRA");
    if( inLVRA(*theCell) ){
      Claim( ((ref(ValRep)) *theCell)->GCAttr == (long) theCell,
	    "IOACheckReference:  ((ref(ValRep)) *theCell)->GCAttr == theCell");
      DEBUG_LVRA( Claim( isValRep(*theCell),
			"IOACheckReference: isValRep(*theCell)"));
    }
  }
}
#endif
