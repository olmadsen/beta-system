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

#define REP ((struct ObjectRep *)theObj)

#ifdef MT
void ProcessStackObj(struct StackObject *sObj)
{
  struct Object **handle = (struct Object **)&sObj->Body;
  struct Object **last   = (struct Object **)((long)&sObj->Proto + sObj->refTopOff);
  while (handle<=last) {
    DEBUG_MT(fprintf(output, 
		     "ProcessStackObj: processing cell 0x%x (%s) in stackobject 0x%x\n",
		     (int)handle, ProtoTypeName((*handle)->Proto),
		     (int)sObj));
    ProcessReference(handle++);
  }
}
#else
GLOBAL(static IOALooksFullCount) = 0; /* consecutive unsuccessful IOAGc's */
#endif

/*
 * IOAGc:
 *  Called from doGC in Misc.c / PerformGC.run.
 *  Make a scavenging garbage collection on IOA.
 */
void IOAGc()
{
#if defined(MAC)
  RotateTheCursor();
#endif
  
  DEBUG_IOA(
	    fprintf(output,
		    "Before: IOA: 0x%x, IOATop: 0x%x, IOALimit: 0x%x\n",
		    (int)GLOBAL_IOA, (int)GLOBAL_IOATop, (int)GLOBAL_IOALimit);
	    fprintf(output,
		    "Before: ToSpace: 0x%x, ToSpaceTop: 0x%x, ToSpaceLimit: 0x%x\n", 
		    (int)ToSpace, (int)ToSpaceTop, (int)ToSpaceLimit);
	    );

  DEBUG_CODE(memset(ToSpace, 0, IOASize));
  
  NumIOAGc++;

  DEBUG_CODE(if (NumIOAGc==DebugStackAtGcNum) DebugStack=1);
  
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

#ifdef KEEP_STACKOBJ_IN_IOA
  IOAStackObjectSum = IOAStackObjectNum = 0;
#endif

  /* AOA roots start out by residing in upper part of ToSpace */
  AOArootsLimit = AOArootsPtr = ToSpaceLimit;

  /* Clear IOAAgeTable */
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
      if(*pointer){
	AOAtoIOACount++;
	ProcessAOAReference( (handle(Object))*pointer);
      }
      pointer++;
    }
  }

  DEBUG_AOA( AOAtoIOAReport() );
  DEBUG_AOA( AOAcopied = 0; IOAcopied = 0; );
  
  /* Follow ActiveComponent */ 
  if (!ActiveComponent && NumIOAGc == 1) {
    char buf[300];
    sprintf(buf, "Could not allocate basic component");
#ifdef MAC
    EnlargeMacHeap(buf);
#endif
    Notify(buf);
    BetaExit(1);
  }
#ifndef NEWRUN
  /* NEWRUN: stackObj is already 0 (cleared at Attach) */
#ifndef MT
  /* MT: active component's stack should be preserved */
  ActiveComponent->StackObj = 0;  /* the stack is not valid anymore. */
#endif
#endif
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
  
#ifdef MT
  {
    int i;
    for (i = 0; i < NumTSD; i++) {
      ProcessReference((handle(Object))(&TSDlist[i]->_CurrentObject));
      ProcessReference((handle(Object))(&TSDlist[i]->_Origin));
      ProcessReference((handle(Object))(&TSDlist[i]->_ActiveStack));
      ProcessReference((handle(Object))(&TSDlist[i]->_ActiveComponent));
    }
    CompleteScavenging();
  }
#else
  ProcessStack();
#endif
    
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
	  /*DEBUG_CBFA(fprintf(output, "ProcessCBFA: current=0x%x\n", current));*/
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
		GetDistanceToEnclosingObject(theObj,enclDist);
		enclObj = cast(Object) Offset(theObj,enclDist);
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
       * Free the table that was allocated by saveAOAroot().
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
      ptr(long) Tmp; ptr(long) TmpTop; 
      
      Tmp    = GLOBAL_IOA; 
      TmpTop = GLOBAL_IOATop; 
      
      GLOBAL_IOA       = ToSpace;                          
      GLOBAL_IOALimit  = ToSpaceLimit;

#if defined(NEWRUN) || defined(sparc)
#ifdef MT
      gIOATop    = ToSpaceTop; 
#else /* MT */
      IOATopOff = (char *) ToSpaceTop - (char *) IOA;
#endif /* MT */
#else
      IOATop    = ToSpaceTop; 
#endif
      
      ToSpace = Tmp; 
      ToSpaceTop = TmpTop; 
      ToSpaceLimit = (long*)((long)ToSpace+IOASize);
    }
    
    IOAActive = FALSE;
    
    /* Determine new tenuring threshold */
    {
      long limit;
      long sum = 0;
      limit = areaSize(GLOBAL_IOA,GLOBAL_IOALimit) / 10;
#ifdef KEEP_STACKOBJ_IN_IOA
      limit -= IOAStackObjectSum;
      if (limit < 0) {
	DEBUG_IOA( fprintf(output, 
			   "#IOA: %d StackObjects fill up more than 10%% of IOA (%d)\n", 
			   (int)IOAStackObjectNum, 
			   (int)IOAStackObjectSum));
	limit = 0;
      }
#endif
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
		     (int)((100 * areaSize(GLOBAL_IOA,GLOBAL_IOATop))/areaSize(GLOBAL_IOA,GLOBAL_IOALimit))));
	
    DEBUG_IOA( IOACheck() );
    DEBUG_CBFA( CBFACheck() );
    DEBUG_AOA( AOACheck() );
    DEBUG_LVRA( LVRACheck() );

    /* Clear all of the unused part of IOA, so that RT routines does
     * not need to clear cells.
     */

    InfoS_LabB();
    
#ifdef MT
    /* doGC checks for this */
#else
    if ((long)IOATop+4*(long)ReqObjectSize > (long)IOALimit) {
      /* Not enough freed by this GC */
      if (IOALooksFullCount > 2) {
	char buf[100];
	sprintf(buf, "Sorry, IOA is full: cannot allocate %d bytes.\n\
Program terminated.\n", (int)(4*ReqObjectSize));
	Notify(buf);
#ifdef NEWRUN
	BetaError(IOAFullErr, CurrentObject, StackEnd, 0);
#else
	BetaError(IOAFullErr, 0);
#endif
      } else {
	if (IOALooksFullCount==2) {
	  /* Have now done two IOAGc's without freeing enough space.
	   * Make sure that all objects go to AOA in the next GC.
	   */
	  IOAtoAOAtreshold=2;
	  DEBUG_IOA(fprintf(output, "Forcing all to AOA in next IOAGc\n"));
	}
	IOALooksFullCount++;
      }
      INFO_IOA(fprintf(output, "[%d]\n", IOALooksFullCount));
    } else {
      IOALooksFullCount = 0;
    }
#endif /* MT */
    
    DEBUG_IOA(
		fprintf(output,
			"After: IOA: 0x%x, IOATop: 0x%x, IOALimit: 0x%x\n",
			(int)GLOBAL_IOA, 
			(int)GLOBAL_IOATop,
			(int)GLOBAL_IOALimit);
		fprintf(output,
			"After: ToSpace: 0x%x, ToSpaceTop: 0x%x, ToSpaceLimit: 0x%x\n", 
			(int)ToSpace, 
			(int)ToSpaceTop, 
			(int)ToSpaceLimit);
		)
      

#ifdef hpux
      /*    cachectl(CC_FLUSH, 0, 0); */
#endif
  }

#ifndef KEEP_STACKOBJ_IN_IOA
/* DoIOACell:
 *  Used by the routines in stack.c, that traverse the stack and
 *  stackobjects.
 */
void DoIOACell(struct Object **theCell,struct Object *theObj)
{
  DEBUG_CODE(if (!CheckHeap) Ck(theObj));
  if (!theObj) return;
  if(inBetaHeap(theObj)){
    if(inLVRA(theObj)){
#ifdef RTDEBUG
      fprintf(output, "[DoIOACell: ***InLVRA: 0x%x: 0x%x]\n", 
	      (int)theCell, 
	      (int)theObj);
#endif
    } else {
      if (isObject(theObj)) {
	ProcessReference(theCell);
	CompleteScavenging();
      } else {
#ifdef RTLAZY
	if (isLazyRef(theObj)) {
	  DEBUG_IOA(fprintf(output, 
			    "DoIOACell: Lazy ref: %d\n", (int)theObj));
	  ProcessReference(theCell);
	} else {
#ifdef RTDEBUG
	  fprintf(output, "[DoIOACell: ***Illegal: 0x%x: 0x%x]\n", 
		  (int)theCell,
		  (int)theObj);
	  Illegal();
#endif /* RTDEBUG */
	}
#endif /* RTLAZY */
      }
    }
  }
#ifdef RTDEBUG
  else {
    if ((theObj!=CALLBACKMARK)&&(theObj!=GENMARK)){
      fprintf(output, 
	      "DoIOACell: 0x%x: 0x%x is outside BETA heaps!\n", theCell, theObj);
      Illegal();
    }
  }
#endif
}

/* DoAOACell:
 *  Used to process stackobject in AOA.
 */
static void DoAOACell(struct Object **theCell,struct Object *theObj)
{
  if (*theCell) ProcessAOAReference((handle(Object))theCell);
}

#ifdef RTDEBUG
static void CheckIOACell(struct Object **theCell,struct Object *theObj)
{
  IOACheckReference(theCell);
}
#endif

#endif /* NEWRUN */

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
 *  FIXME: use theObj instead of newObj
 */

void ProcessReference( theCell)
  handle(Object) theCell;
{
  ref(Object) theObj;
  long GCAttribute;
  
  theObj = *theCell;
  
  if( inIOA(theObj)){
    /* 'theObj' is inside IOA */
#ifdef RTDEBUG
    { char buf[100];
      DEBUG_IOA(sprintf(buf, 
			"ProcessReference: theObj (0x%x) is consistent.", 
			(int)theObj); 
		Claim(isObject(theObj),buf));
    }
#endif
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
	  MCHECK();
	  saveAOAroot(theCell);
	  MCHECK();
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
	
	GetDistanceToEnclosingObject(theObj, Distance);
	AutObj = (ref(Object)) Offset(theObj, Distance);
	if( isForward(AutObj->GCAttr) ){
	  newObj = (ref(Object)) AutObj->GCAttr;
	  /* If the forward pointer refers an AOA object, insert
	   * theCell in AOAroots table.
	   */
	  if( !inToSpace( AutObj->GCAttr))
	    if( inAOA( AutObj->GCAttr)){
	      MCHECK();
	      saveAOAroot(theCell);
	      MCHECK();
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
      MCHECK();
      saveAOAroot(theCell);
      MCHECK();
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
  
  if( isSpecialProtoType(theProto) ){  
    switch( SwitchProto(theProto) ){
    case SwitchProto(ByteRepPTValue):
    case SwitchProto(ShortRepPTValue):
    case SwitchProto(DoubleRepPTValue):
    case SwitchProto(LongRepPTValue): 
      return; /* No references in the type of object, so do nothing*/
      
    case SwitchProto(DynItemRepPTValue):
    case SwitchProto(DynCompRepPTValue):
      /* Process iOrigin */
      ProcessReference( (handle(Object))(&REP->iOrigin) );
      /* Process rest of repetition */
      switch(SwitchProto(theProto)){
      case SwitchProto(DynItemRepPTValue):
      case SwitchProto(DynCompRepPTValue):
	{ long *pointer;
	  register long size, index;
	  
	  /* Scan the repetition and follow all entries */
	  { size = REP->HighBorder;
	    pointer = (long *)&REP->Body[0];
	    
	    for (index=0; index<size; index++) {
	      ProcessReference( (handle(Object))(pointer++) );
	    }
	  }
	}
	break;
      }
      return;

    case SwitchProto(RefRepPTValue):
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
      
    case SwitchProto(ComponentPTValue):
      { ref(Component) theComponent;
	
	theComponent = Coerce( theObj, Component);
	ProcessReference( (handle(Object))(&theComponent->StackObj));
	ProcessReference( (handle(Object))(&theComponent->CallerComp));
	ProcessReference( &theComponent->CallerObj);
	ProcessObject( (ref(Object))ComponentItem( theComponent));
      }
      return;
      
    case SwitchProto(StackObjectPTValue):
#ifdef NEWRUN
      ProcessStackObj((struct StackObject *)theObj, DoIOACell);
#else
      ProcessStackObj((struct StackObject *)theObj);
#endif
      return;
      
    case SwitchProto(StructurePTValue):
      ProcessReference( &(toStructure(theObj))->iOrigin );
      return;
      
    case SwitchProto(DopartObjectPTValue):
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
  theObj = *theCell; /* the object referenced from the cell */
  
  if( inIOA(theObj)){ /* theObj is inside IOA */
    GCAttribute = theObj->GCAttr;
    if( GCAttribute > 2048 ){ /* theObj has a forward pointer. */
      *theCell = (ref(Object)) GCAttribute;
      DEBUG_LVRA( Claim( !inLVRA((ref(Object))GCAttribute),
			"ProcessAOAReference: Forward ValRep"));
    }else{
      if( GCAttribute >= 0 ){ 
	/* theObj is an autonomous object. */
	/* Move it from IOA to AOA/LVRA */
	*theCell = NewCopyObject( theObj, 0);
	if( !inToSpace( *theCell)){ /* cheap */
	  if( inLVRA( *theCell)){   /* expensive */
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
	
	GetDistanceToEnclosingObject(theObj, Distance);
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
  
  if( isSpecialProtoType(theProto) ){  
    switch( SwitchProto(theProto) ){
    case SwitchProto(ByteRepPTValue): 
    case SwitchProto(ShortRepPTValue): 
    case SwitchProto(DoubleRepPTValue): 
    case SwitchProto(LongRepPTValue): 
      return; /* No references in the type of object, so do nothing*/

    case SwitchProto(DynItemRepPTValue):
    case SwitchProto(DynCompRepPTValue):
      /* Process iOrigin */
      ProcessAOAReference( (handle(Object))(&REP->iOrigin) );
      /* Process rest of repetition */
      switch(SwitchProto(theProto)){
      case SwitchProto(DynItemRepPTValue):
      case SwitchProto(DynCompRepPTValue):
	{ long *pointer;
	  register long size, index;
	  
	  /* Scan the repetition and follow all entries */
	  { size = REP->HighBorder;
	    pointer = (long *)&REP->Body[0];
	    
	    for (index=0; index<size; index++) {
	      ProcessAOAReference( (handle(Object))(pointer++) );
	    }
	  }
	}
	break;
      }
      return;

    case SwitchProto(RefRepPTValue):
      /* Scan the repetition and follow all entries */
      { ptr(long) pointer;
	register long size, index;
	
	size = toRefRep(theObj)->HighBorder;
	pointer =  (ptr(long)) &toRefRep(theObj)->Body[0];
	for(index=0; index<size; index++) 
	  if(*pointer) 
	    ProcessAOAReference( (handle(Object))(pointer++) );
	  else pointer++;
      }
      return;
    case SwitchProto(ComponentPTValue):
      { ref(Component) theComponent;
	theComponent = Coerce( theObj, Component);
	ProcessAOAReference( (handle(Object))(&theComponent->StackObj));
	ProcessAOAReference( (handle(Object))(&theComponent->CallerComp));
	ProcessAOAReference( (handle(Object))(&theComponent->CallerObj));
	ProcessAOAObject( (ref(Object))(ComponentItem( theComponent)));
      }
      return;
    case SwitchProto(StackObjectPTValue):
#ifdef KEEP_STACKOBJ_IN_IOA
      Claim( FALSE, "ProcessAOAObject: No StackObject in AOA");
#else
      /* Machine dependant traversal of stackobj */
#ifdef crts
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
	  if(*theCell) {
	    ProcessAOAReference((handle(Object))stackptr);
	  }
          if (isTagged) { /* reset tagging */
	     *theCell = (struct Object *)((unsigned)*theCell | 1);
	  }
        }
      }
#endif /* crts */
#ifdef NEWRUN
      ProcessStackObj((struct StackObject *)theObj, DoAOACell);
#endif
#endif /* KEEP_STACKOBJ_IN_IOA */
      return;
    case SwitchProto(StructurePTValue):
      ProcessAOAReference( &(toStructure(theObj))->iOrigin );
      return;
    case SwitchProto(DopartObjectPTValue):
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
      if(*theCell) ProcessAOAReference( (handle(Object))theCell );
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
    /*DEBUG_IOA( fprintf(output, "CompleteScavenging: theObj=0x%x proto=0x%x\n", theObj, theObj->Proto));*/
    /*DEBUG_IOA( fprintf(output, "CompleteScavenging: HandledInToSpace=0x%x\n", HandledInToSpace));*/
    DEBUG_CODE( Claim(ObjectSize(theObj) > 0, "#CompleteScavenging: ObjectSize(theObj) > 0") );
    ProcessObject( theObj);
  }
  /*DEBUG_IOA( fprintf(output, "CompleteScavenging: ToSpaceTop=0x%x\n", ToSpaceTop));*/
  DEBUG_CODE( Claim( HandledInToSpace == ToSpaceTop,
		   "CompleteScavenging: HandledInToSpace == ToSpaceTop"));
}

#ifdef RTDEBUG

ref(Object) lastObj=0;

void IOACheck()
{
  ref(Object) theObj;
  long        theObjectSize;
  
  theObj = (ref(Object)) GLOBAL_IOA;

  lastObj=0;
  while ((long *) theObj < GLOBAL_IOATop) {
#ifdef MT
    /* Skip blank cells in beginning of objects */
    {
      long *ptr = (long *)theObj;
      while ( (ptr<(long*)GLOBAL_IOATop) && (*ptr==0) ) ptr++;
      if (ptr == (long*)GLOBAL_IOATop) return;
      theObj = (struct Object *)ptr;
    }
#else
    Claim((long)(theObj->Proto), "IOACheck: theObj->Proto");
#endif /* MT */

#if 0
    {
      long i;
      fprintf(output, "IOACheck: 0x%x\n", (int)theObj);
#if 0
      for (i=0; i<ObjectSize(theObj); i++){
	fprintf(output, 
		"  0x%x: 0x%x\n",
		(int)((long *)theObj+i), 
		(int)(*((long *)theObj+i)));
      }
      fflush(output);
#endif
    }
#endif

    theObjectSize = 4*ObjectSize(theObj);
    Claim(ObjectSize(theObj) > 0, "#IOACheck: ObjectSize(theObj) > 0");
    IOACheckObject (theObj);
    lastObj = theObj;
    theObj = (ref(Object)) Offset(theObj, theObjectSize);
  }
}
  
void IOACheckObject (struct Object *theObj)
{
  ref(ProtoType) theProto;
  
  theProto = theObj->Proto;
  
#if 0
  fprintf(output, "IOACheckObject: theObj = 0x%x\n", (int)theObj);
#endif

#ifdef MT
  if (!theProto){
    /* Prottypes of part objects may be zero during allocation
     * when using V entries. We have to skip this object (:-(
     */
    return;
  }
#else
  Claim( (int)theProto, "#IOACheckObject: theProto!=0");
#endif

  Claim( !inBetaHeap((ref(Object))theProto),
	 "#IOACheckObject: !inBetaHeap(theProto)");
  
  if( isSpecialProtoType(theProto) ){  
    switch( SwitchProto(theProto) ){
    case SwitchProto(ByteRepPTValue):
    case SwitchProto(ShortRepPTValue):
    case SwitchProto(DoubleRepPTValue):
    case SwitchProto(LongRepPTValue):
      /* No references in the type of object, so do nothing*/
      return;
    
    case SwitchProto(DynItemRepPTValue):
    case SwitchProto(DynCompRepPTValue):
      /* Check iOrigin */
      IOACheckReference( (handle(Object))(&REP->iOrigin) );
    /* Check rest of repetition */
    switch(SwitchProto(theProto)){
    case SwitchProto(DynItemRepPTValue):
    case SwitchProto(DynCompRepPTValue):
      { long *pointer;
      register long size, index;
      
      /* Scan the repetition and follow all entries */
      { 
	size = REP->HighBorder;
	pointer = (long *)&REP->Body[0];
	
	for (index=0; index<size; index++) {
	  IOACheckReference( (handle(Object))(pointer++) );
	}
      }
      }
    break;
    }
    return;
    
    case SwitchProto(RefRepPTValue):
      /* Scan the repetition and follow all entries */
      { ptr(long) pointer;
      register long size, index;
      
      size = toRefRep(theObj)->HighBorder;
      pointer =  (ptr(long)) &toRefRep(theObj)->Body[0];
      
      for(index=0; index<size; index++) {
	IOACheckReference( (handle(Object))(pointer) );
	pointer++;
      }
      }
    
    return;
    
    case SwitchProto(ComponentPTValue):
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
    
    case SwitchProto(StackObjectPTValue):
      { 
#ifdef mc68020
	ref(StackObject) theStackObject;
	ptr(long)        stackptr; 
	handle(Object)   theCell; 
	ptr(long)        theEnd;
	theStackObject = Coerce(theObj, StackObject);
	/* printf("sobj=0x%x\n", theStackObject);
	 * printf("sobj: StackSize=0x%x\n", theStackObject->StackSize);
	 */
	theEnd = &theStackObject->Body[0] + theStackObject->StackSize;
	
	for( stackptr = &theStackObject->Body[0]; stackptr < theEnd; stackptr++){
	  if( inIOA( *stackptr)){
	    theCell = (handle(Object)) stackptr;
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
#ifdef NEWRUN
	ProcessStackObject((struct StackObject *)theObj, CheckIOACell);
#else
	fprintf(output, 
		"IOACheckObject: no check of stackobject 0x%x\n", theObj);
#endif
#endif
      }
    return;
    
    case SwitchProto(StructurePTValue):
      IOACheckReference( &(toStructure(theObj))->iOrigin );
    return;
    case SwitchProto(DopartObjectPTValue):
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
      if( *Tab == -Tab[1] ) {
#if 0
	fprintf(output, 
		"IOACheckObject(0x%x): part object at offset 0x%x\n",
		(int)theObj,
		(int)(*Tab*4));
#endif
	IOACheckObject( (ref(Object))(Offset( theObj, *Tab * 4)));
      }
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
      IOACheckReference((handle(Object))theCell);
    }
  }
}

void IOACheckReference(theCell)
     handle(Object) theCell;
{
  if( *theCell ){
    if (isLazyRef(*theCell)){
      fprintf(output, "Lazy in IOA: 0x%x: %d\n", (int)theCell, (int)*theCell);
      return;
    }
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
