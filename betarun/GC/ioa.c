/*
 * BETA RUNTIME SYSTEM, Copyright (C) 1990-93 Mjolner Informatics Aps.
 * ioa.c (was: scavenging.c)
 * by Lars Bak, Peter Andersen, Peter Orbaek and Tommy Thorn.
 */

#include "beta.h"
#ifdef sparc
#include "../CRUN/crun.h"
#endif

#ifdef hpux
/* #include <sys/cache.h> */
#endif


static long FreePercentage( bottom, top, limit)
     long bottom, top, limit;
{
    return (100 * areaSize(top, limit))/areaSize(bottom, limit); 
}

/*
 * IOAGc:
 *  Called from doGC in Misc.c / PerformGC.run.
 *  Make a scavenging garbage collection on IOA.
 */
void IOAGc()
{
#ifdef macintosh
    RotateTheCursor();
#endif

#ifdef RTDEBUG
    memset(ToSpace, 0, IOASize);
#endif
    
    NumIOAGc++;

/******************** DEMO Limitation in IOAGc ****************************/
#ifdef DEMO
    if (NumIOAGc==20) {

#ifdef macintosh
      Prompt(
"\p\
This program was compiled using the demo version of \
the Mj\277lner BETA System. The demo version is limited \
in the number of garbage collections allowed. This ",
"\p\
limit will soon be reached; if you want to save your \
work, please do it now, and quit your program.",
"", "");

#else macintosh
      fprintf(output, "\
  ********************************************************\n\
  * This program was compiled using the demo version of  *\n\
  * the Mjolner BETA System. The demo version is limited *\n\
  * in the number of garbage collections allowed. This   *\n\
  * limit will soon be reached; if you want to save your *\n\
  * work, please do it now, and quit your program.       *\n\
  ********************************************************\n\
");
#endif macintosh

    } else
    if (NumIOAGc==30) {

#ifdef macintosh
      Prompt(
"\p\
This program was compiled using the demo version of \
the Mj\277lner BETA System. The demo version is limited \
in the number of garbage collections allowed. This ",
"\p\
limit has now been reached and your program will be \
terminated - sorry!\n\
You may order an unconstrained version from\n",
"\p\n\
    Mj\277lner Informatics, Gustav Wiedsvej 10,\n\
    Science Park Aarhus, DK-8000 Aarhus C, Denmark,\n",
"\p\
    Phone: +45 86 20 20 00,  Fax: +45 86 20 12 22\n\
    e-mail: support@mjolner.dk"
);

#else macintosh
      fprintf(output, "\
  ********************************************************\n\
  * This program was compiled using the demo version of  *\n\
  * the Mjolner BETA System. The demo version is limited *\n\
  * in the number of garbage collections allowed. This   *\n\
  * limit has now been reached and your program will be  *\n\
  * terminated - sorry!                                  *\n\
  * You may order an unconstrained version from          *\n\
  *                                                      *\n\
  *     Mjolner Informatics, Gustav Wiedsvej 10,         *\n\
  *     Science Park Aarhus, DK-8000 Aarhus C, Denmark,  *\n\
  *     Phone: +45 86 20 20 00,  Fax: +45 86 20 12 22    *\n\
  *     e-mail: support@mjolner.dk                       *\n\
  ********************************************************\n\
");
#endif macintosh

      exit(0);
    }
#endif DEMO
/***************** End of DEMO Limitation in IOAGc ****************************/

    IOAActive = TRUE;
    
    INFO_IOA( fprintf( output, "#(IOA-%d %d? ", NumIOAGc, ReqObjectSize));
    InfoS_LabA();
    
    /* Initialize the ToSpace */
    ToSpaceTop       = ToSpace;
    HandledInToSpace = ToSpace;
    
    DEBUG_IOA( IOACheck() );
    DEBUG_LVRA( LVRACheck() );
    
    DEBUG_AOA( AOAtoIOACheck() );
    DEBUG_AOA( AOACheck() );
    IOAStackObjectSum = IOAStackObjectNum = 0;
    AOArootsLimit = AOArootsPtr = ToSpaceLimit;
    { long i; for(i=0; i < IOAMaxAge;i++) IOAAgeTable[i] = 0; }
    /* Save the state of AOA, this state is used at end of IOAGc, to proceed 
     * not handled objects.
     */
    HandledAOABlock = AOATopBlock;
    if( AOATopBlock ) HandledInAOA = AOATopBlock->top;
    
    AOAtoIOACount = 0;
    if( AOAtoIOAtable ){ 
	long i; ptr(long) pointer = BlockStart( AOAtoIOAtable);
	for(i=0; i<AOAtoIOAtableSize; i++){ 
#ifdef RTLAZY
	    if( *pointer > 0){
#else
	    if ( *pointer ){
#endif
	      AOAtoIOACount++;
	      ProcessAOAReference( *pointer);
	    }
	    pointer++;
	}
    }
    DEBUG_AOA( AOAtoIOAReport() );
    DEBUG_AOA( AOAcopied = 0; IOAcopied = 0; );
    
    /* Follow ActiveComponent */ 
    if (!ActiveComponent && NumIOAGc == 1) {
      fprintf(output, "#BETA: Could not allocate basic component\n");
      exit(1);
    }
    ActiveComponent->StackObj = 0;  /* the stack is not valid anymore. */
    ProcessReference( &ActiveComponent);
    ProcessReference( &BasicItem );
    if (InterpretItem) {
      INFO_IOA(fprintf(output, " (InterpretItem"); fflush(output));
      ProcessReference( &InterpretItem );
      INFO_IOA(fprintf(output, ")"); fflush(output));
    }
    if (LazyItem) {
      INFO_IOA(fprintf(output, " (LazyItem"); fflush(output));
      ProcessReference( &LazyItem );
      INFO_IOA(fprintf(output, ")"); fflush(output));
    }
    CompleteScavenging();
    
    ProcessStack();
    
    /* Follow all struct pointers in the Call Back Functions area. */
    if (CBFABlockSize){
	if( CBFATop != CBFA->entries ){
	    ref(CallBackArea) cbfa = CBFA;
	    ref(CallBackEntry) current = cbfa->entries;
	    long limit = (long) cbfa->entries + CBFABlockSize;
	    
	    for (; current != CBFATop; current++){
		if ( (long) current >= limit){
		    /* Go to next block */
		    cbfa = cbfa->next;        
		    /* guarentied to be non-nil since current != CBFATop */
		    
		    current = cbfa->entries; 
		    /* guarentied to be different from CBFATop. 
		     * If not the block would not have been allocated 
		     */
		    limit = (long)cbfa->entries + CBFABlockSize;
		}
		if (current->theStruct){
		  ProcessReference(&current->theStruct);
		}
	    }
	    CompleteScavenging();
	}
    }
    
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

    if( DOT ){
	/* The Debugger Object Table is in use, so traverse this table. */
	ptr(long) current = DOT;
	while( current < DOTTop){
	    if( *current ) {
	      if (inIOA(*current)){
		INFO_DOT(fprintf(output, "#DOT: updating IOA reference 0x%x\n", *current));
		if( isForward( (cast(Object)(*current))->GCAttr ) ){ 
		  /* *current has a forward pointer. */
		  *current = (long) (ref(Object)) (cast(Object)(*current))->GCAttr;
		} else {
		  *current = 0;
                  DOTSize--;
		}
	      }
	    }
	    current++;
	}
    }
    
    if( AOANeedCompaction)  AOAGc();
    
    if (tempAOAroots) {
	/* ToSpace was not big enough to hold both objects and table.
	 * Free the table that was allocated in CopyObject().
	 */
	tempAOArootsFree();
    }
#ifdef RTDEBUG
    else {
      /* Clear the part of ToSpace used for AOArootstable */
      memset(AOArootsPtr, 0, AOArootsLimit-AOArootsPtr);
    }
#endif
    
    /* Swap IOA and ToSpace */
    {
	ptr(long) Tmp; ptr(long) TmpTop; ptr(long) TmpLimit;
      
	Tmp     = IOA;     TmpTop     = IOATop;     TmpLimit     = IOALimit; 
      
#ifdef sparc
	IOA       = ToSpace;                          
	IOATopoff = (char *) ToSpaceTop - (char *) IOA;
#endif
#ifdef hppa
	setIOAReg(ToSpace);
	setIOATopoffReg((char *) ToSpaceTop - (char *) IOA);
#endif
#ifdef mc68020
	IOA       = ToSpace;                          
	IOATop    = ToSpaceTop; 
#endif
#ifdef linux
	IOA       = ToSpace;                          
	IOATop    = ToSpaceTop; 
#endif
	IOALimit     = ToSpaceLimit;
      
	ToSpace = Tmp;     ToSpaceTop = TmpTop;     ToSpaceLimit = TmpLimit;
    }
    
    IOAActive = FALSE;
    
    {
	long limit = areaSize(IOA,IOALimit) / 10;long sum = 0;
      
	limit -= IOAStackObjectSum;
	if (limit < 0) {
	    DEBUG_IOA( fprintf(output, 
			       "#IOA: %d StackObjects fill up more than 10%% of IOA (%d)\n", 
			       IOAStackObjectNum, 
			       IOAStackObjectSum));
	    limit = 0;
	}
	IOAtoAOAtreshold = 0;
	do
	  {
	      sum += IOAAgeTable[IOAtoAOAtreshold++];
	  } while ((sum < limit) && (IOAtoAOAtreshold < IOAMaxAge));
	
	if (limit)
	  IOAtoAOAtreshold +=1; 
    }
    DEBUG_IOA( fprintf( output, " treshold=%d", IOAtoAOAtreshold));
    DEBUG_IOA( fprintf( output, " AOAroots=%d", 
		       areaSize(AOArootsPtr,AOArootsLimit)));
    
    INFO_IOA( fprintf( output," %d%%)\n",
		      (100 * areaSize(IOA,IOATop))/areaSize(IOA,IOALimit)));
    
    DEBUG_IOA( IOACheck() );
    DEBUG_AOA( AOACheck() );
    DEBUG_LVRA( LVRACheck() );
    InfoS_LabB();
    
    /* Based on IOAPercentage, determine if IOA space is exhausted. */
    
    if( FreePercentage( IOA, (long) IOATop + ReqObjectSize*4, IOALimit) 
       < IOAPercentage ){
	fprintf( output,"#IOA Heap space full, request: %d.\n", ReqObjectSize);
	BetaExit(1);
    }

#ifdef hpux
/*    cachectl(CC_FLUSH, 0, 0); */
#endif
}

/*
 * ProcessReference:
 *  Takes as input a reference to a cell containing a root for IOA.
 *  If the cell refers an object residing in IOA, the 
 *  object is copied to ToSpace/AOA and the cell is updated.
 *  Furthermore one forward reference in the most enclosing
 *  object is inserted in the GC-attribute.
 *  Copies at most one object to ToSpace/AOA. You must call 
 *  CompleteScavenging sometimes later to process references from the 
 *  copied object.
 *  Optimization: USE theObj instead of newObj and inline GetDistanceToEnc....
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
	    DEBUG_LVRA( Claim( !inLVRA(GCAttribute), "ProcessReference: Forward ValRep"));
	    /* If the forward pointer refers an AOA object, insert
	     * theCell in AOAroots table.
	     */
	    if( !inToSpace( GCAttribute))
	      if (inAOA( GCAttribute)) {
		  saveAOAroot(theCell);
	      }
	}else{
	    if( GCAttribute >= 0 ){ 
		/* '*theCell' is an autonomous object. */
		*theCell = NewCopyObject( *theCell, theCell);
	    }else{
		/* theObj is a part object. */
		long Distance;
		ref(Object) newObj;
		ref(Object) AutObj;
		
		Distance = GetDistanceToEnclosingObject( theObj);
		AutObj = (ref(Object)) Offset( theObj, Distance);
		if( isForward(AutObj->GCAttr) ){
		    newObj = (ref(Object)) AutObj->GCAttr;
		    /* If the forward pointer refers an AOA object, insert
		     * theCell in AOAroots table.
		     */
		    if( !inToSpace( AutObj->GCAttr))
		      if( inAOA( AutObj->GCAttr)){
			  saveAOAroot(theCell);
		      }
		}else
		  newObj = NewCopyObject( AutObj, theCell);
		*theCell = (ref(Object)) Offset( newObj, -Distance);
	    }
	}
	DEBUG_IOA( Claim( !inIOA(*theCell),"ProcessReference: !inIOA(*theCell)"));
    }else{
      /* '*theCell' is pointing outside IOA */
      /* If the forward pointer refers an AOA object, insert
       * theCell in AOAroots table.
       */
#ifdef RTLAZY
      if (isLazyRef( *theCell)) {
	if (negIOArefs)
	  /* This is a dangling reference, and we are currently 
	   * collecting as part of the trap handling */
	  negIOArefsINSERT((long) theCell);
	return;
      }
#endif
      if (inAOA( *theCell)) {
	saveAOAroot(theCell);
	return;
      }
      if( inLVRA( *theCell)){
	/* Preserve the LVRA-cycle. */
	((ref(ValRep)) *theCell)->GCAttr = (long) theCell;
	DEBUG_LVRA( Claim( isValRep(*theCell),
			  "ProcessObject: isValRep(*theCell)"));
	return;
      }
    }
}

/*
 * ProcessObject:
 *  Takes as input a reference to an object residing in the ToSpace.
 *  It traverses the object and processes all the references in it.    
 */

void ProcessObject(theObj)
     ref(Object) theObj;
{ ref(ProtoType) theProto;
  
  theProto = theObj->Proto;
  
  if( (long) theProto < 0 ){  
      switch( (long) theProto ){
	case (long) ByteRepPTValue:
	case (long) WordRepPTValue:
	case (long) DoubleRepPTValue:
	case (long) ValRepPTValue: return; /* No references in the type of object, so do nothing*/
	  
	case (long) RefRepPTValue:
	  /* Scan the repetition and follow all entries */
	  { ptr(long) pointer;
	    register long size, index;

	    size = toRefRep(theObj)->HighBorder;
	    pointer =  (ptr(long)) &toRefRep(theObj)->Body[0];
	    
	    for(index=0; index<size; index++) 
	      if( *pointer != 0 ) ProcessReference( pointer++ );
	      else pointer++;
	}
	  
	  return;
	  
	case (long) ComponentPTValue:
	  { ref(Component) theComponent;
	    
	    theComponent = Coerce( theObj, Component);
	    ProcessReference( &theComponent->StackObj);
	    ProcessReference( &theComponent->CallerComp);
	    ProcessReference( &theComponent->CallerObj);
	    ProcessObject( ComponentItem( theComponent));
	  }
	  return;
	  
	case (long) StackObjectPTValue:
	  ProcessStackObj((struct StackObject *)theObj);
	  return;
	  
	case (long) StructurePTValue:
	  ProcessReference( &(toStructure(theObj))->iOrigin );
	  return;

	case (long) DopartObjectPTValue:
	  ProcessReference( &(cast(DopartObject)(theObj))->Origin );
	  return;
      }
  }else{
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
      for (refs_ofs = (short *)&tab->StaticOff + 1; *refs_ofs; ++refs_ofs) {
	  theCell = (struct Object **) ((char *) theObj + *refs_ofs);
	  if (*theCell ) ProcessReference(theCell);
      }
  }
}


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
		if( !inToSpace( *theCell)){
		    if( inLVRA( *theCell)){
			/* Preserve the LVRA-cycle. */
			((ref(ValRep)) *theCell)->GCAttr = (long) theCell;
			DEBUG_LVRA( Claim( isValRep(*theCell),
					  "ProcessAOAReference: isValRep(*theCell)"));
		    }
		}
	    }else{ /* theObj is a part object. */
		long Distance;
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
	if( inLVRA( *theCell)){
	    /* Preserve the LVRA-cycle. */
	    ((ref(ValRep)) *theCell)->GCAttr = (long) theCell;
	    DEBUG_LVRA( Claim( isValRep(*theCell), 
			      "ProcessAOAReference: isValRep(*theCell)"));
	}
    }
    DEBUG_AOA( Claim( !inIOA(*theCell),"ProcessAOAReference: !inIOA(*theCell)"));
    DEBUG_AOA( if( inAOA( *theCell)){ AOACheckObjectSpecial( *theCell); } );
    
    /* Insert 'theCell' in the AOAtoIOAtable iff *theCell is inToSpace. */
    /* Otherwise, if *theCell is a dangling (negative) reference, insert it in
     * negAOArefs */
    if( inToSpace( *theCell ) ) 
      AOAtoIOAInsert( theCell);
#ifdef RTLAZY
    else if ( isLazyRef (*theCell ) )
      negAOArefsINSERT((long) theCell);
#endif
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
      switch( (long) theProto ){
	case (long) ByteRepPTValue: 
	case (long) WordRepPTValue: 
	case (long) DoubleRepPTValue: 
	case (long) ValRepPTValue: 
	  return; /* No references in the type of object, so do nothing*/
	case (long) RefRepPTValue:
	  /* Scan the repetition and follow all entries */
	  { ptr(long) pointer;
	    register long size, index;
	    
	    size = toRefRep(theObj)->HighBorder;
	    pointer =  (ptr(long)) &toRefRep(theObj)->Body[0];
	    for(index=0; index<size; index++) 
	      if( *pointer != 0 ) ProcessAOAReference( pointer++ );
	      else pointer++;
	}
	  return;
	case (long) ComponentPTValue:
	  { ref(Component) theComponent;
	    theComponent = Coerce( theObj, Component);
	    ProcessAOAReference( &theComponent->StackObj);
	    ProcessAOAReference( &theComponent->CallerComp);
	    ProcessAOAReference( &theComponent->CallerObj);
	    ProcessAOAObject( ComponentItem( theComponent));
	}
	  return;
	case (long) StackObjectPTValue:
	  Claim( FALSE, "ProcessAOAObject: No StackObject in AOA");
	  return;
	case (long) StructurePTValue:
	  ProcessAOAReference( &(toStructure(theObj))->iOrigin );
	  return;
	case (long) DopartObjectPTValue:
	  ProcessAOAReference( &(cast(DopartObject)(theObj))->Origin );
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

/*
 * CompleteScavenging:
 *  Process all the objects in the ToSpace, which has not been handled yet.
 *  i.e. objects coiped to ToSpace since last call of CompleteScavenging.
 *  The reason that this is done "stepwise" is to ensure the locallity of 
 *  related objects, to avoid unnecessary swapping. 
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

long GetDistanceToEnclosingObject( theObj)
     ref(Object)theObj;
{
    long Distance, GCAttribute;
    
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
    /*fprintf(output, "\n");*/
    while ((long *) theObj < IOATop) {
      Claim(theObj->Proto, "IOACheck: theObj->Proto");
      theObjectSize = 4*ObjectSize(theObj);
      
      /*fprintf(output, "theObj: 0x%x theObjectSize: 0x%x\n", theObj, theObjectSize);*/
      IOACheckObject (theObj);
      theObj = (ref(Object)) Offset(theObj, theObjectSize);
    }
}

void IOACheckObject (theObj)
     ref(Object) theObj;
{
    ref(ProtoType) theProto;
    
    theProto = theObj->Proto;

    /* DEBUG_IOA(printf("IOACheckObject: theObj = %x\n", theObj)); */
    Claim( !inBetaHeap(theProto),"#IOACheckObject: !inBetaHeap(theProto)");
    
    if( (long) theProto < 0 ){  
	switch( (long) theProto ){
	  case (long) ByteRepPTValue:
	  case (long) WordRepPTValue:
	  case (long) DoubleRepPTValue:
	  case (long) ValRepPTValue:
	    /* No references in the type of object, so do nothing*/
	    return;
	    
	  case (long) RefRepPTValue:
	    /* Scan the repetition and follow all entries */
	    { ptr(long) pointer;
	      register long size, index;
	      
	      size = toRefRep(theObj)->HighBorder;
	      pointer =  (ptr(long)) &toRefRep(theObj)->Body[0];
	      
	      for(index=0; index<size; index++) 
#ifdef RTLAZY
		if( *pointer > 0) IOACheckReference( pointer++ );
#else
	        if( *pointer != 0) IOACheckReference( pointer++ );
#endif
		else pointer++;
	  }
	    
	    return;
	    
	  case (long) ComponentPTValue:
	    { ref(Component) theComponent;
	      
	      theComponent = Coerce( theObj, Component);
	      if (theComponent->StackObj == (ref(StackObject))-1) {
		  /*  printf("\nIOACheckObject: theComponent->StackObj=-1, skipped!\n"); */
	      } else {
		  IOACheckReference( &theComponent->StackObj);
	      }
	      IOACheckReference( &theComponent->CallerComp);
	      IOACheckReference( &theComponent->CallerObj);
	      IOACheckObject( ComponentItem( theComponent));
	  }
	    return;
	    
	  case (long) StackObjectPTValue:
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
	    
	  case (long) StructurePTValue:
	    IOACheckReference( &(toStructure(theObj))->iOrigin );
	    return;
	  case (long) DopartObjectPTValue:
	    IOACheckReference( &(cast(DopartObject)(theObj))->Origin );
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
#ifdef RTLAZY
	    if (*theCell > 0) IOACheckReference(theCell);
#else
	    if (*theCell != 0) IOACheckReference(theCell);
#endif
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

#endif /* RTDEBUG */
