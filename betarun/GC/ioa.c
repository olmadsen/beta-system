/*
 * BETA RUNTIME SYSTEM, Copyright (C) 1990-94 Mjolner Informatics Aps.
 * ioa.c (was: scavenging.c)
 * by Lars Bak, Peter Andersen, Peter Orbaek, Tommy Thorn, Jacob Seligmann and S|ren Brandt
 */

#include "beta.h"
#ifdef sparc
#include "../CRUN/crun.h"
#endif

#ifdef hpux
/* #include <sys/cache.h> */
#endif


/*
 * IOAGc:
 *  Called from doGC in Misc.c / PerformGC.run.
 *  Make a scavenging garbage collection on IOA.
 */
void IOAGc()
{
static IOALooksFullCount = 0; /* consecutive unsuccessful IOAGc's */

#if defined(macintosh) ||defined(MAC)
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
CPrompt(
"This program was compiled using the demo version of \
the Mj\277lner BETA System. The demo version is limited \
in the number of garbage collections allowed. ", 
"This limit will soon be reached; if you want to save your \
work, please do it now, and quit your program.",
"", 
"");
    
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
#endif /*macintosh*/
    
  } else
    if (NumIOAGc==30) {
      
#ifdef macintosh
CPrompt(
"This program was compiled using the demo version of \
the Mj\277lner BETA System. The demo version is limited \
in the number of garbage collections allowed.", 
"This limit has now been reached and your program will be \
terminated - sorry!\n\
You may order an unconstrained version from\n",
"\n\
Mj\277lner Informatics, Science Park Aarhus,\n\
Gustav Wieds Vej 10, DK-8000 Aarhus C, Denmark.\n",
"Phone: +45 86 20 20 00,  Fax: +45 86 20 12 22\n\
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
  *     Mjolner Informatics, Gustav Wieds Vej 10,        *\n\
  *     Science Park Aarhus, DK-8000 Aarhus C, Denmark,  *\n\
  *     Phone: +45 86 20 20 00,  Fax: +45 86 20 12 22    *\n\
  *     e-mail: support@mjolner.dk                       *\n\
  ********************************************************\n\
");
#endif /*macintosh*/
      
      exit(0);
    }
#endif /* DEMO */
  /***************** End of DEMO Limitation in IOAGc ****************************/
  
  IOAActive = TRUE;
  
  INFO_IOA(fprintf(output, "#(IOA-%d, %d bytes requested,", 
		   (int)NumIOAGc, (int)ReqObjectSize*4));
  InfoS_LabA();
  
  /* Initialize the ToSpace */
  ToSpaceTop       = ToSpace;
  HandledInToSpace = ToSpace;
  
  DEBUG_CBFA( CBFACheck() );
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
      if( isPositiveRef(*pointer) ){
#else
	if ( *pointer ){
#endif
	  AOAtoIOACount++;
	  ProcessAOAReference( (handle(Object))*pointer);
	}
	pointer++;
      }
    };
    DEBUG_AOA( AOAtoIOAReport() );
    DEBUG_AOA( AOAcopied = 0; IOAcopied = 0; );
    
    /* Follow ActiveComponent */ 
    if (!ActiveComponent && NumIOAGc == 1) {
      char buf[300];
      sprintf(buf, "Could not allocate basic component");
#ifdef macintosh
      EnlargeMacHeap(buf);
#endif
      Notify(buf);
      exit(1);
    }
    ActiveComponent->StackObj = 0;  /* the stack is not valid anymore. */
    ProcessReference( (handle(Object))&ActiveComponent);
    ProcessReference( (handle(Object))&BasicItem );
    if (InterpretItem[0]) {
      INFO_IOA(fprintf(output, " #(IOA: InterpretItem[0]"); fflush(output));
      ProcessReference( (handle(Object))(&InterpretItem[0]) );
      INFO_IOA(fprintf(output, ")"); fflush(output));
    }
    if (InterpretItem[1]) {
      INFO_IOA(fprintf(output, " #(IOA: InterpretItem[1]"); fflush(output));
      ProcessReference( (handle(Object))(&InterpretItem[1]) );
      INFO_IOA(fprintf(output, ")"); fflush(output));
    }
#ifdef RTLAZY
    if (LazyItem) {
      INFO_IOA(fprintf(output, " #(IOA: LazyItem"); fflush(output));
      ProcessReference( (handle(Object))(&LazyItem) );
      INFO_IOA(fprintf(output, ")"); fflush(output));
    }
#endif
    
    CompleteScavenging();
    
    ProcessStack();
    
    /* Follow all struct pointers in the Call Back Functions area. */
    if (CBFABlockSize){
      if( CBFATop != CBFA->entries ){
	ref(CallBackArea) cbfa = CBFA;
	ref(CallBackEntry) current = cbfa->entries;
	long limit = (long) cbfa->entries + CBFABlockSize;
	
	for (; current != CBFATop; 
	     current = (ref(CallBackEntry))((long)current+CallBackEntrySize)){
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
	    ProcessReference((handle(Object))(&current->theStruct));
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
	  DEBUG_CODE( Claim(ObjectSize((ref(Object)) HandledInAOA ) > 0,
			    "ObjectSize((ref(Object)) HandledInAOA ) > 0") );
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
	    { ref(Object) theObj;
	      ref(Object) enclObj;
	      int enclDist;

	      theObj = cast(Object)(*current);
	      if (isStatic(theObj->GCAttr)) {
		enclObj = cast(Object) 
		  Offset(theObj,enclDist=GetDistanceToEnclosingObject(theObj));
		if (isForward(enclObj->GCAttr))
		  theObj = cast(Object) Offset(enclObj->GCAttr,-enclDist);
		else
		  theObj = 0;	/* Enclosing object is dead */
	      } else {
		/* It it not a static part object, so either the GCAttr is a
		 * forward reference to the objects new position, or it is
		 * NONE if the object is dead. */
		if (isForward (theObj->GCAttr))
		  theObj =  cast(Object) theObj->GCAttr;
		else
		  theObj = 0;
	      }

	      INFO_DOT(fprintf(output, 
			       "#DOT: updating IOA reference 0x%x to 0x%x\n", 
			       (int)(*current), (int)theObj));
	      *current = (long) theObj;
	      if (!theObj) DOTSize--;
	  
	      DEBUG_IOA( Claim( (theObj == 0) || inToSpace (theObj) || inAOA (theObj) ,"DOT element NONE, in ToSpace, or in AOA "));

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
      
      Tmp = IOA; TmpTop = IOATop; TmpLimit = IOALimit; 
      
#ifdef sparc
      IOA       = ToSpace;                          
      IOATopoff = (char *) ToSpaceTop - (char *) IOA;
#endif
#ifdef hppa
      /*setIOAReg(ToSpace);
      setIOATopoffReg((char *) ToSpaceTop - (char *) IOA);*/
      IOA       = ToSpace;                          
      IOATop    = ToSpaceTop; 
#endif
#ifdef mc68020
      IOA       = ToSpace;                          
      IOATop    = ToSpaceTop; 
#endif
#ifdef crts
      IOA       = ToSpace;                          
      IOATop    = ToSpaceTop; 
#endif
#if defined(linux) || defined(nti)
      IOA       = ToSpace;                          
      IOATop    = ToSpaceTop; 
#endif
      IOALimit     = ToSpaceLimit;
      
      ToSpace = Tmp; ToSpaceTop = TmpTop; ToSpaceLimit = TmpLimit;
    }
    
    IOAActive = FALSE;
    
    {
      long limit = areaSize(IOA,IOALimit) / 10;long sum = 0;
      
      limit -= IOAStackObjectSum;
      if (limit < 0) {
	DEBUG_IOA( fprintf(output, 
			   "#IOA: %d StackObjects fill up more than 10%% of IOA (%d)\n", 
			   (int)IOAStackObjectNum, 
			   (int)IOAStackObjectSum));
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
    DEBUG_IOA( fprintf(output, " treshold=%d", (int)IOAtoAOAtreshold));
    DEBUG_IOA( fprintf(output, " AOAroots=%d", 
		       (int)areaSize(AOArootsPtr,AOArootsLimit)));
    
    INFO_IOA(fprintf(output," %d%% used)\n",
		      (int)((100 * areaSize(IOA,IOATop))/areaSize(IOA,IOALimit))));
    
    DEBUG_IOA( IOACheck() );
    DEBUG_CBFA( CBFACheck() );
    DEBUG_AOA( AOACheck() );
    DEBUG_LVRA( LVRACheck() );

    /* Clear all of the unused part of IOA, so that RT routines does
     * not need to clear cells.
     * This turned out to be slower or at best marginally faster than
     * using long_clear. I have disabled it to avoid having to
     * reimplement the RUN routines. /Peter
     */
    /*memset(IOATop, 0, IOASize - ((long)IOATop-(long)IOA) );*/

    InfoS_LabB();
    
    if (IOATop+4*ReqObjectSize > IOALimit)
      if (IOALooksFullCount > 2) {
	char buf[100];
	sprintf(buf, "Sorry, IOA is full: cannot allocate %d bytes.\n\
Program terminated.\n", (int)(4*ReqObjectSize));
	Notify(buf);
	BetaExit(1);
      } else
	IOALooksFullCount++;
    else
      IOALooksFullCount = 0;
    
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
      DEBUG_LVRA( Claim( !inLVRA((ref(Object))GCAttribute), 
			"ProcessReference: Forward ValRep"));
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
  
  if( isNegativeRef(theProto) ){  
    switch( (long) theProto ){
    case (long) ByteRepPTValue:
    case (long) WordRepPTValue:
    case (long) DoubleRepPTValue:
    case (long) ValRepPTValue: return; /* No references in the type of object, so do nothing*/
      
    case (long) ObjectRepPTValue:
      { struct ObjectRep *rep = (struct ObjectRep *)theObj;
	long *pointer;
	register long size, index;
	if (rep->isDynamic) {
	  /* Scan the repetition and follow all entries */
	  { 
	    size = rep->HighBorder;
	    pointer = (long *)&rep->Body[0];

	    for (index=0; index<size; index++) {
	      ProcessReference( (handle(Object))(pointer++) );
	    }
	  }
	}
      }
      return;

    case (long) RefRepPTValue:
      /* Scan the repetition and follow all entries */
      { ptr(long) pointer;
	register long size, index;
	
	size = toRefRep(theObj)->HighBorder;
	pointer =  (ptr(long)) &toRefRep(theObj)->Body[0];
	
	for(index=0; index<size; index++) 
	  if( *pointer != 0 ) ProcessReference( (handle(Object))(pointer++) );
	  else pointer++;
      }
      return;
      
    case (long) ComponentPTValue:
      { ref(Component) theComponent;
	
	theComponent = Coerce( theObj, Component);
	ProcessReference( (handle(Object))(&theComponent->StackObj));
	ProcessReference( (handle(Object))(&theComponent->CallerComp));
	ProcessReference( &theComponent->CallerObj);
	ProcessObject( (ref(Object))ComponentItem( theComponent));
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
	ProcessObject((ref(Object))((long *)theObj + tab->StaticOff));
    
    /* Handle all the references in the Object. */
    for (refs_ofs = (short *)&tab->StaticOff + 1; *refs_ofs; ++refs_ofs) {
      theCell = (struct Object **) ((char *) theObj + ((*refs_ofs) & (short) ~3));
      /* sbrandt 24/1/1994: 2 least significant bits in prototype 
       * dynamic offset table masked out. As offsets in this table are
       * always multiples of 4, these bits may be used to distinguish
       * different reference types. */ 
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

  /*fprintf(output, "ProcessAOAReference: 0x%x\n", *theCell);*/
  
  DEBUG_AOA( Claim( inAOA( theCell),"#ProcessAOAReference: theCell inside AOA\n"));
  theObj = *theCell;
  
  if( inIOA(theObj)){ /* theObj is inside IOA */
    GCAttribute = theObj->GCAttr;
    if( GCAttribute > 2048 ){ /* theObj has a forward pointer. */
      *theCell = (ref(Object)) GCAttribute;
      DEBUG_LVRA( Claim( !inLVRA((ref(Object))GCAttribute),
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
  
  if( isNegativeRef(theProto) ){  
    switch( (long) theProto ){
    case (long) ByteRepPTValue: 
    case (long) WordRepPTValue: 
    case (long) DoubleRepPTValue: 
    case (long) ValRepPTValue: 
      return; /* No references in the type of object, so do nothing*/
    case (long) ObjectRepPTValue:
      { struct ObjectRep *rep = (struct ObjectRep *)theObj;
	long *pointer;
	register long size, index;
	if (rep->isDynamic) {
	  /* Scan the repetition and follow all entries */
	  { 
	    size = rep->HighBorder;
	    pointer = (long *)&rep->Body[0];

	    for (index=0; index<size; index++) {
	      ProcessAOAReference( (handle(Object))(pointer++) );
	    }
	  }
	}
      }
      return;

    case (long) RefRepPTValue:
      /* Scan the repetition and follow all entries */
      { ptr(long) pointer;
	register long size, index;
	
	size = toRefRep(theObj)->HighBorder;
	pointer =  (ptr(long)) &toRefRep(theObj)->Body[0];
	for(index=0; index<size; index++) 
	  if( *pointer != 0 ) 
	    ProcessAOAReference( (handle(Object))(pointer++) );
	  else pointer++;
      }
      return;
    case (long) ComponentPTValue:
      { ref(Component) theComponent;
	theComponent = Coerce( theObj, Component);
	ProcessAOAReference( (handle(Object))(&theComponent->StackObj));
	ProcessAOAReference( (handle(Object))(&theComponent->CallerComp));
	ProcessAOAReference( (handle(Object))(&theComponent->CallerObj));
	ProcessAOAObject( (ref(Object))(ComponentItem( theComponent)));
      }
      return;
    case (long) StackObjectPTValue:
#ifndef crts
      Claim( FALSE, "ProcessAOAObject: No StackObject in AOA");
#else
      /* CRTS */
      /* Scan the StackObject for object references and follow all entries */
      { ref(StackObject) theStackObject;
        handle(Object)   theCell; 
        long             *stackptr; 
        long             size;
        long             isTagged;
	
        theStackObject = Coerce(theObj, StackObject);
        
        stackptr = &theStackObject->Body[1] + theStackObject->StackSize;
	size = theStackObject->BodySize-theStackObject->StackSize-1;
	for(; size > 0; size--, stackptr++) {
          theCell = (handle(Object)) stackptr;
	  isTagged = ((unsigned)*theCell & 1) ? 1 : 0; 
	  if (isTagged) { /* remove tagging */
	     *theCell = (struct Object *)((unsigned)*theCell & ~1);
	     DEBUG_IOA( fprintf( output, "ProcessAOAObject (theCell: 0x%x was tagged)\n", (int)*theCell));
	  }
	  if(inIOA(*theCell) || inAOA(*theCell) || inLVRA(*theCell)) {
	     if (isObject(*theCell))
               ProcessAOAReference((handle(Object))stackptr);
	  }
          if (isTagged) { /* reset tagging */
	     *theCell = (struct Object *)((unsigned)*theCell | 1);
	  }
        }
      }
#endif
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
	ProcessAOAObject( (ref(Object))(Offset( theObj, *Tab * 4)));
      Tab += 4;
    }
    Tab++;
    
    /* Handle all the references in the Object. */
    while( *Tab != 0 ){
      theCell = (ptr(long)) Offset( theObj, ((*Tab++) & (short) ~3) );
      /* sbrandt 24/1/1994: 2 least significant bits in prototype 
       * dynamic offset table masked out. As offsets in this table are
       * always multiples of 4, these bits may be used to distinguish
       * different reference types. */ 
      if( *theCell != 0 ) ProcessAOAReference( (handle(Object))theCell );
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
    DEBUG_CODE( Claim(ObjectSize(theObj) > 0, "#CompleteScavenging: ObjectSize(theObj) > 0") );
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

  ref(Object) lastObj=0;

  void IOACheck()
    {
      ref(Object) theObj;
      long        theObjectSize;
      
      theObj = (ref(Object)) IOA;
      while ((long *) theObj < IOATop) {
	Claim((long)(theObj->Proto), "IOACheck: theObj->Proto");
	theObjectSize = 4*ObjectSize(theObj);
	Claim(ObjectSize(theObj) > 0, "#IOACheck: ObjectSize(theObj) > 0");
	IOACheckObject (theObj);
	lastObj = theObj;
	theObj = (ref(Object)) Offset(theObj, theObjectSize);
      }
    }
  
  void IOACheckObject (theObj)
    ref(Object) theObj;
  {
    ref(ProtoType) theProto;
    
    theProto = theObj->Proto;
    
    /* DEBUG_IOA(printf("IOACheckObject: theObj = %x\n", theObj)); */
    Claim( !inBetaHeap((ref(Object))theProto),
	  "#IOACheckObject: !inBetaHeap(theProto)");
    
    if( isNegativeRef(theProto) ){  
      switch( (long) theProto ){
      case (long) ByteRepPTValue:
      case (long) WordRepPTValue:
      case (long) DoubleRepPTValue:
      case (long) ValRepPTValue:
	/* No references in the type of object, so do nothing*/
	return;
	
      case (long) ObjectRepPTValue:
	{ struct ObjectRep *rep = (struct ObjectRep *)theObj;
	  long *pointer;
	  register long size, index;
	  if (rep->isDynamic) {
	    /* Scan the repetition and follow all entries */
	    { 
	      size = rep->HighBorder;
	      pointer = (long *)&rep->Body[0];
	      
	      for (index=0; index<size; index++) {
		IOACheckReference( (handle(Object))(pointer++) );
	      }
	    }
	  }
	}
	return;

      case (long) RefRepPTValue:
	/* Scan the repetition and follow all entries */
	{ ptr(long) pointer;
	  register long size, index;
	  
	  size = toRefRep(theObj)->HighBorder;
	  pointer =  (ptr(long)) &toRefRep(theObj)->Body[0];
	  
	  for(index=0; index<size; index++) 
#ifdef RTLAZY
	    if( *pointer > 0) 
	      IOACheckReference( (handle(Object))(pointer++) );
#else
	  if( *pointer != 0) 
	    IOACheckReference( (handle(Object))(pointer++) );
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
	    IOACheckReference( (handle(Object))(&theComponent->StackObj));
	  }
	  IOACheckReference( (handle(Object))(&theComponent->CallerComp));
	  IOACheckReference( &theComponent->CallerObj);
	  IOACheckObject( (ref(Object))ComponentItem( theComponent));
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
	      if( isObject( *theCell ) ) 
		IOACheckReference( (handle(Object))stackptr);
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
	  IOACheckObject( (ref(Object))(Offset( theObj, *Tab * 4)));
	Tab += 4;
      }
      Tab++;
      
      /* Handle all the references in the Object. */
      while (*Tab != 0) {
	theCell = (long *) Offset(theObj, ((*Tab++) & (short) ~3));
	/* sbrandt 24/1/1994: 2 least significant bits in prototype 
	 * dynamic offset table masked out. As offsets in this table are
	 * always multiples of 4, these bits may be used to distinguish
	 * different reference types. */ 
#ifdef RTLAZY
	if (isPositiveRef(*theCell)) IOACheckReference((handle(Object))theCell);
#else
	if (*theCell != 0) IOACheckReference((handle(Object))theCell);
#endif
      }
    }
  }
  
void IOACheckReference(theCell)
     handle(Object) theCell;
{
  if( *theCell ){
    if (!(inIOA(*theCell) || inAOA(*theCell) || inLVRA(*theCell))) {
      fprintf (output, "theCell = 0x%x, *theCell = 0x%x\n", 
	       (int)theCell, (int)(*theCell));
      Claim( inIOA(*theCell) || inAOA(*theCell) || inLVRA(*theCell),
	    "IOACheckReference: *theCell lazy ref or inside IOA, AOA or LVRA");
    }
    if( inLVRA(*theCell) ){
      Claim( ((ref(ValRep)) *theCell)->GCAttr == (long) theCell,
	    "IOACheckReference:  ((ref(ValRep)) *theCell)->GCAttr == theCell");
      DEBUG_LVRA( Claim(isValRep(*theCell),
			"IOACheckReference: isValRep(*theCell)"));
    }
  }
}

#endif /* RTDEBUG */
