/*
 * BETA RUNTIME SYSTEM, Copyright (C) 1990-94 Mjolner Informatics Aps.
 * ioa.c (was: scavenging.c)
 * by Lars Bak, Peter Andersen, Peter Orbaek, Tommy Thorn, Jacob Seligmann and S|ren Brandt
 */

#ifdef RTDEBUG
#define IOAGC_START_TRACE 100000
#endif

#include "beta.h"
#include "dot.h"

#ifdef sparc
#include "../CRUN/crun.h"
#endif

#define REP ((ObjectRep *)theObj)

/* LOCAL FUNTIONS */
static void ProcessAOAReference(Object ** theCell);
static void ProcessAOAObject(Object * theObj);
static void DoAOACell(Object **theCell,Object *theObj);

#ifdef RTDEBUG
static void IOACheckPrintTheObj(Object *theObj);
static void IOACheckPrintSkipped(long *ptr, Object *theObj);
static void IOACheckPrintIOA(void);
#endif /* RTDEBUG */

/*
 * IOAGc:
 *  Called from doGC in Misc.c / PerformGC.run.
 *  Make a scavenging garbage collection on IOA.
 */
void IOAGc()
{
  long starttime = 0;

  MAC_CODE(RotateTheCursor());
  
  DEBUG_IOA({
    fprintf(output,
	    "\nBefore: IOA: 0x%x, IOATop: 0x%x, IOALimit: 0x%x\n",
	    (int)GLOBAL_IOA, (int)GLOBAL_IOATop, (int)GLOBAL_IOALimit);
    fprintf(output,
	    "Before: ToSpace: 0x%x, ToSpaceTop: 0x%x, ToSpaceLimit: 0x%x\n", 
	    (int)ToSpace, (int)ToSpaceTop, (int)ToSpaceLimit);
  });
  
  NumIOAGc++;
  
  INFO_IOA({
    starttime = getmilisectimestamp();
    fprintf(output, "#(IOA-%d, %d bytes requested,", 
	    (int)NumIOAGc, (int)ReqObjectSize*4);
  });
  
  /* Clear ToSpace to trigger errors earlier */
  DEBUG_CODE(memset(ToSpace, 0, IOASize));
  DEBUG_CODE(if (NumIOAGc==DebugStackAtGcNum) DebugStack=1);
  
  InfoS_LabA();
  
  /* Initialize the ToSpace */
  ToSpaceTop       = ToSpace;
  HandledInToSpace = ToSpace;
  
  DEBUG_MT(TSDCheck());
  DEBUG_CBFA(CBFACheck());
  DEBUG_IOA(IOACheck());
  DEBUG_AOAtoIOA(AOAtoIOACheck()); 
  DEBUG_AOA(AOACheck());
  
  IOAActive = TRUE;
  
  /* AOA roots start out by residing in upper part of ToSpace */
  AOArootsLimit = AOArootsPtr = ToSpaceLimit;
  
  /* Clear IOAAgeTable */
  { long i; for(i=0; i < IOAMaxAge; i++) IOAAgeTable[i] = 0; }

  /* */
  HandledInAOAHead = HandledInAOATail = NULL;
  
  /* Process AOAtoIOAtable */
  DEBUG_IOA(fprintf(output, " #(IOA: Roots: AOAtoIOAtable"); fflush(output));
  AOAtoIOACount = 0;
  if( AOAtoIOAtable ){ 
    long i; long * pointer = BlockStart( AOAtoIOAtable);
    for(i=0; i<AOAtoIOAtableSize; i++){ 
      if(*pointer){
	AOAtoIOACount++;
	Claim(inAOA(*pointer), "AOAtoIOAtable has a cell outside AOA");
	ProcessAOAReference( (Object **)*pointer);
      }
      pointer++;
    }
  }
  DEBUG_IOA(fprintf(output, ")\n"); fflush(output));

  DEBUG_AOAtoIOA( AOAtoIOAReport() );
  DEBUG_AOA( AOAcopied = 0; IOAcopied = 0; );
  
  /* Follow ActiveComponent */ 
#ifndef MT
  if (!ActiveComponent && NumIOAGc == 1) {
    char buf[512];
    sprintf(buf, "Could not allocate basic component");
    MAC_CODE(EnlargeMacHeap(buf));
    Notify(buf);
    BetaExit(1);
  }
#endif /* not MT */

#ifndef NEWRUN
  /* NEWRUN: stackObj is already 0 (cleared at Attach) */
#ifndef MT
  /* MT: active component's stack should be preserved */
  ActiveComponent->StackObj = 0;  /* the stack is not valid anymore. */
#endif /* MT */
#endif /* NEWRUN */
  DEBUG_IOA(fprintf(output, " #(IOA: Root: ActiveComponent"); fflush(output));
  ProcessReference( (Object **)&ActiveComponent);
  DEBUG_IOA(fprintf(output, ")\n"); fflush(output));

  DEBUG_IOA(fprintf(output, " #(IOA: Root: BasicItem"); fflush(output));
  ProcessReference( (Object **)&BasicItem );
  DEBUG_IOA(fprintf(output, ")\n"); fflush(output));

#ifdef INTERPRETER
  /* Only used by Jawahar's interpreter */
  if (InterpretItem[0]) {
    DEBUG_IOA(fprintf(output, " #(IOA: Root: InterpretItem[0]"); fflush(output));
    ProcessReference( (Object **)(&InterpretItem[0]) );
    DEBUG_IOA(fprintf(output, ")\n"); fflush(output));
  }
  if (InterpretItem[1]) {
    DEBUG_IOA(fprintf(output, " #(IOA: Root: InterpretItem[1]"); fflush(output));
    ProcessReference( (Object **)(&InterpretItem[1]) );
    DEBUG_IOA(fprintf(output, ")\n"); fflush(output));
  }
#endif /* INTERPRETER */

#ifdef RTLAZY
  if (LazyItem) {
    DEBUG_IOA(fprintf(output, " #(IOA: Root: LazyItem"); fflush(output));
    ProcessReference( (Object **)(&LazyItem) );
    DEBUG_IOA(fprintf(output, ")\n"); fflush(output));
  }
#endif /* RTLAZY */

  CompleteScavenging();
  
#ifdef MT
  DEBUG_IOA(fprintf(output, " #(IOA: Roots: TSD"); fflush(output));
  ProcessTSD();
  DEBUG_IOA(fprintf(output, ")\n"); fflush(output));
#else
  DEBUG_IOA(fprintf(output, " #(IOA: Roots: Stack"); fflush(output));
  ProcessStack();
  DEBUG_IOA(fprintf(output, ")\n"); fflush(output));
#endif

#if (defined(RTVALHALLA) && defined(intel))
  DEBUG_IOA(fprintf(output, " #(IOA: Roots: Valhalla ReferenceStack"); fflush(output));
  ProcessValhallaRefStack();
  DEBUG_IOA(fprintf(output, ")\n"); fflush(output));
#endif /* RTVALHALLA && intel */
  
  DEBUG_IOA(fprintf(output, " #(IOA: Roots: CBFA"); fflush(output));
  ProcessCBFA();
  DEBUG_IOA(fprintf(output, ")\n"); fflush(output));
  
  /* Objects copied til AOA until now has not been proceesed. 
   * During proceesing these objects, new objects may be copied to
   * ToSpace and AOA, therefore we must alternate between handeling
   * objects in ToSpace and AOA until no more objects is to procees.
   */
  if (AOABaseBlock) {
    if (HandledInAOAHead) {
      while (1) {
	Object *nextHead;
	
	ProcessAOAObject(HandledInAOAHead);
	CompleteScavenging();
	
	nextHead = (Object *)HandledInAOAHead->GCAttr;
	HandledInAOAHead->GCAttr = DEADOBJECT;
	
	if (HandledInAOAHead == HandledInAOATail) {
	  HandledInAOAHead = NULL;
	  break;
	} else {
	  HandledInAOAHead = nextHead;
	}
      }
    }
  }

  DEBUG_IOA(fprintf(output, " #(IOA: Weak roots: DOT"); fflush(output));
  ProcessDOT();
  DEBUG_IOA(fprintf(output, ")\n"); fflush(output)); 

  DEBUG_CODE(dump_aoa=(AOANeedCompaction && DumpAOA));
  
#ifdef RTSTAT
  if (StatAOA && AOABaseBlock) {
    AOANeedCompaction = TRUE;
  }
#endif

  if (AOANeedCompaction || forceAOAGC) {
    if (!noAOAGC) {
      AOAGc();
    }
    forceAOAGC = FALSE;
  }
  
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
    long * Tmp; 
    
    Tmp    = GLOBAL_IOA; 
    
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
    ToSpaceTop = ToSpace; 
    ToSpaceLimit = (long*)((long)ToSpace+IOASize);
  }
  
  IOAActive = FALSE;
  
  /* Determine new tenuring threshold */
  {
    long limit;
    long sum = 0;
    limit = areaSize(GLOBAL_IOA,GLOBAL_IOALimit) / 10;
    IOAtoAOAtreshold = 0;
    do
      {
	sum += IOAAgeTable[IOAtoAOAtreshold++];
      } while ((sum < limit) && (IOAtoAOAtreshold < IOAMaxAge));
    
    if (limit && (IOAtoAOAtreshold < IOAMaxAge))
      IOAtoAOAtreshold +=1;
    Claim(IOAtoAOAtreshold <= IOAMaxAge, "IOAtoAOAtreshold <= IOAMaxAge");
  }
  DEBUG_IOA( fprintf(output, " treshold=%d", (int)IOAtoAOAtreshold));
  DEBUG_IOA( fprintf(output, " AOAroots=%d", 
		     (int)areaSize(AOArootsPtr,AOArootsLimit)));
  
  /* Clear all of the unused part of IOA (i.e. [IOATop..IOALimit[), 
   * so that allocation routines do not need to clear cells.
   */
  memset(GLOBAL_IOATop, 0, (long)GLOBAL_IOALimit-(long)GLOBAL_IOATop);

  INFO_IOA({
    fprintf(output," %d%% used, ioatime=%dms)\n",
	    (int)((100*areaSize(GLOBAL_IOA,GLOBAL_IOATop))
		  / areaSize(GLOBAL_IOA,GLOBAL_IOALimit)),
	    (int)(getmilisectimestamp() - starttime));
  });

#ifdef MT
  DEBUG_IOA({ 
    /* If there is only one thread, IOACheck will only check the range
     * IOA..IOATop (not gIOA..gIOATop). To make this possible at this point,
     * we must set the thread specific IOATop already here.
     * It will be reassigned, when the object requested is allocated in
     * doGC, but the assignment below should cause no harm.
     */
    if (NumTSD==1) IOATop = GLOBAL_IOATop; 
  });

  /* Make sure there is enough slices in IOA for all threads.
   * As the amount fo free heap has changed, recalculate slicesize.
   * Forthcoming threads will use the smaller slice size, 
   * whereas running threads will
   * use the previous (larger) slice size) until they are forced to
   * take a new slice (after a GC).
   */
  CalculateSliceSize();
#endif

  DEBUG_MT(TSDCheck());
  DEBUG_IOA(IOACheck());
  DEBUG_CBFA(CBFACheck());
  DEBUG_AOAtoIOA(AOAtoIOACheck());
  DEBUG_AOA(AOACheck());
  DEBUG_CODE(if (dump_aoa) AOACheck());

  InfoS_LabB();
  
#ifdef MT
  /* doGC checks for this */
#else
  if ((long)IOATop+4*(long)ReqObjectSize > (long)IOALimit) {
    /* Not enough freed by this GC */
    if (IOALooksFullCount > 2) {
      char buf[512];
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
	IOAtoAOAtreshold=IOAMinAge+1;
	DEBUG_IOA(fprintf(output, "Forcing all to AOA in next IOAGc\n"));
      }
      IOALooksFullCount++;
    }
    INFO_IOA(fprintf(output, "[%d]\n", IOALooksFullCount));
  } else {
    IOALooksFullCount = 0;
  }
#endif /* MT */
  
  DEBUG_CODE(memset(ToSpace, 0, IOASize));

  DEBUG_IOA(
	    fprintf(output,
		    "\nAfter: IOA: 0x%x, IOATop: 0x%x, IOALimit: 0x%x\n",
		    (int)GLOBAL_IOA, 
		    (int)GLOBAL_IOATop,
		    (int)GLOBAL_IOALimit);
	    fprintf(output,
		    "After: ToSpace: 0x%x, ToSpaceTop: 0x%x, ToSpaceLimit: 0x%x\n", 
		    (int)ToSpace, 
		    (int)ToSpaceTop, 
		    (int)ToSpaceLimit);
	    );
  INFO_HEAP_USAGE(PrintHeapUsage("after IOA GC"));

} /* End IOAGc */



/* DoStackCell:
 *  Used by the routines in stack.c, that traverse the stack.
 */
void DoStackCell(Object **theCell,Object *theObj)
{    
  if (!theObj) {
    return;
  }
  if (inBetaHeap(theObj)) {
    if (isObject(theObj)){
      DEBUG_CODE(if (!CheckHeap) Ck(theObj));
      ProcessReference(theCell);
      CompleteScavenging();
    } else {
      DEBUG_CODE({
	fprintf(output, "[DoStackCell: ***Illegal: 0x%x: 0x%x]\n", 
		(int)theCell,
		(int)theObj);
	Illegal();
      });
    }
  } else {
#ifdef RTLAZY
    if (isLazyRef(theObj)) {
      DEBUG_LAZY(fprintf(output, 
			 "DoStackCell: Lazy ref: %d\n", (int)theObj));
      ProcessReference(theCell);
    } 
#endif /* RTLAZY */
#if defined(RTDEBUG) && defined(NEWRUN)
    /* Because of the very well-defined structure of stackframes
     * there should be no GC-able cells, that refer outside BETA heaps.
     */
    else {
      if ((theObj!=CALLBACKMARK)&&(theObj!=GENMARK)){
	fprintf(output, 
		"DoStackCell: 0x%x: 0x%x is outside BETA heaps!\n", theCell, theObj);
	Illegal();
      }
    }
#endif
  }
}

/* DoAOACell:
 *  Used to process stackobject in AOA.
 */
static void DoAOACell(Object **theCell,Object *theObj)
{
  if (!theObj) {
    return;
  }
  if (inBetaHeap(theObj)) {
    if (isObject(theObj)) {
      DEBUG_CODE(if (!CheckHeap) Ck(theObj));
      ProcessAOAReference(theCell);
    } else {
      DEBUG_CODE({
	fprintf(output, "[DoStackCell: ***Illegal: 0x%x: 0x%x]\n", 
		(int)theCell,
		(int)theObj);
	Illegal();
      });
    }
  } else {
#ifdef RTLAZY
    if (isLazyRef(theObj)) {
      DEBUG_LAZY(fprintf(output, 
			 "DoAOACell: Lazy ref: %d\n", (int)theObj));
      ProcessAOAReference(theCell);
    }
#endif /* RTLAZY */
#if defined(RTDEBUG) && defined(NEWRUN)
    /* Because of the very well-defined structure of stackframes
     * there should be no GC-able cells, that refer outside BETA heaps.
     */
    else {
      if ((theObj!=CALLBACKMARK)&&(theObj!=GENMARK)){
	fprintf(output, 
		"DoAOACell: 0x%x: 0x%x is outside BETA heaps!\n", theCell, theObj);
	Illegal();
      }
    }
#endif
  }
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
 *  FIXME: use theObj instead of newObj
 */

void ProcessReference(Object ** theCell)
{
  Object * theObj;
  long GCAttribute;
  
  theObj = *theCell;
  
  if( inIOA(theObj)){
    /* 'theObj' is inside IOA */
#ifdef RTDEBUG
    {
        char buf[512];
        DEBUG_IOA(sprintf(buf, 
                          "ProcessReference: theObj (0x%x) is consistent.", 
                          (int)theObj); 
                  Claim(isObject(theObj),buf));
    }
#endif
    GCAttribute = theObj->GCAttr;
    if( isForward(GCAttribute) ){ 
      /* theObj has a forward pointer, i.e has already been moved */
      *theCell = (Object *) GCAttribute; /* update cell to reference forward obj */
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
      if( isAutonomous(GCAttribute) ){ 
	/* '*theCell' is an autonomous object. */
	*theCell = NewCopyObject( *theCell, theCell);
      }else{
	/* theObj is a part object. */
	long Distance;
	Object * newObj;
	Object * AutObj;
	
	GetDistanceToEnclosingObject(theObj, Distance);
	AutObj = (Object *) Offset(theObj, Distance);
	if( isForward(AutObj->GCAttr) ){
	  newObj = (Object *) AutObj->GCAttr;
	  /* If the forward pointer refers an AOA object, insert
	   * theCell in AOAroots table.
	   */
	  if( !inToSpace( AutObj->GCAttr))
	    if( inAOA( AutObj->GCAttr)){
	      MCHECK();
	      saveAOAroot(theCell);
	      MCHECK();
	    }
	}else{
            newObj = NewCopyObject( AutObj, theCell);
        }
        *theCell = (Object *) Offset( newObj, -Distance);
      }
    }
    Claim(!inIOA(*theCell),"ProcessReference: !inIOA(*theCell)");
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
  }
#ifdef PERSIST 
  if (inProxy((long) *theCell)) {
    proxyAlive(theCell);
  }
#endif /* PERSIST */
}

/*
 * ProcessObject:
 *  Takes as input a reference to an object residing in the ToSpace.
 *  It traverses the object and processes all the references in it.    
 */

void ProcessObject(theObj)
     Object * theObj;
{ 
  scanObject(theObj,
	     ProcessReference,
	     TRUE);
  /* CompleteScavenging();*/
}

/*
 * ProcessAOAReference:
 *  Takes as input a reference to a cell residing inside AOA.
 *  If the cell refers an object residing in IOA, the 
 *  object is copied to ToSpace/AOA and the cell is updated.
 *  Furthermore a forward reference in the most enclosing
 *  object is inserted in the GC-attribute.
 */
static void ProcessAOAReference(Object ** theCell)
{
  Object * theObj;
  long GCAttribute;
  
  /*fprintf(output, "ProcessAOAReference: 0x%x\n", *theCell);*/
  
  Claim(inAOA(theCell),"inAOA(theCell)");
  if (*theCell) {
    Claim(inBetaHeap(*theCell), "inBetaHeap(*theCell)");
  }
  theObj = *theCell; /* the object referenced from the cell */
  
  if (inIOA(theObj)) { /* theObj is inside IOA */
    GCAttribute = theObj->GCAttr;
    if (isForward(GCAttribute)) { 
      /* The object has already been moved to ToSpace or AOA. */
      *theCell = (Object *) GCAttribute;
    } else {
      if (isAutonomous(GCAttribute)) { 
	/* theObj is an autonomous object. 
	 * Move it from IOA to ToSpace/AOA */
	*theCell = NewCopyObject(theObj, 0);
      } else { 
	/* theObj is a part object. */
	long Distance;
	Object * newObj;
	Object * AutObj;
	
	Claim(isStatic(GCAttribute), "isStatic(GCAttribute)");
	GetDistanceToEnclosingObject(theObj, Distance);
	AutObj = (Object *) Offset(theObj, Distance);
	Claim(!isStatic(AutObj->GCAttr), "!isStatic(AutObj->GCAttr)");
	if (isForward(AutObj->GCAttr)) {
	  newObj = (Object *) AutObj->GCAttr;
	} else {
	  newObj = NewCopyObject(AutObj, 0);
	}
	*theCell = (Object *) Offset(newObj, -Distance); 
      }
    }
  }
  
  Claim(!inIOA(*theCell),"!inIOA(*theCell)");
  DEBUG_AOA(if(inAOA(*theCell)) { AOACheckObjectSpecial(*theCell); });
  
  /* Insert 'theCell' in the AOAtoIOAtable iff *theCell is inToSpace. */
  /* Otherwise, if *theCell is a dangling (negative) reference, insert it in
   * negAOArefs */
  if (inToSpace(*theCell)) {
#ifdef MT
    MT_AOAtoIOAInsert( theCell);
#else /* MT */
    AOAtoIOAInsert( theCell);
#endif /* MT */
  }
#ifdef RTLAZY
  else if (isLazyRef(*theCell)) {
    negAOArefsINSERT((long) theCell);
  }
#endif
#ifdef PERSIST 
  if (inProxy((long) *theCell)) {
    proxyAlive(theCell);
  }
#endif /* PERSIST */
}

/*
 * ProcessAOAObject:
 *  Takes as input a reference to an object residing in the AOA.
 *  It traverse the object and process all the references in it.    
 */

static void ProcessAOAObject(Object * theObj)
{ 
  scanObject(theObj,
	     ProcessAOAReference,
	     TRUE);
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
  Object * theObj;
  DEBUG_CODE(static int NumCompleteScavenging=0; NumCompleteScavenging++);
  
  
  
  /* CompleteScavenging should NOT be called by functions, that
   * just *check* heaps. One way to ensure this is that
   * IOAActive is true.
   * (This is debug code only)
   */
  Claim(IOAActive, "CompleteScavenging: IOAActive");
  while (HandledInToSpace < ToSpaceTop) {
    theObj = (Object *) HandledInToSpace;
    HandledInToSpace = (long *) (((long) HandledInToSpace)
				    + 4*ObjectSize(theObj));
    Claim(ObjectSize(theObj)>0, "CompleteScavenging: ObjectSize(theObj)>0");
    ProcessObject(theObj);
  }
  Claim( HandledInToSpace == ToSpaceTop,
		     "CompleteScavenging: HandledInToSpace == ToSpaceTop");

}

#ifdef RTDEBUG

static void IOACheckPrintTheObj(Object *theObj)
{
    long i;
    if (NumIOAGc>=IOAGC_START_TRACE){
      fprintf(output, 
	      "IOACheck: 0x%x (size 0x%x)\n", 
	      (int)theObj, 
	      (int)(4*ObjectSize(theObj)));
      for (i=0; i<ObjectSize(theObj); i++){
        fprintf(output, 
                "  0x%x: 0x%x\n",
                (int)((long *)theObj+i), 
                (int)(*((long *)theObj+i)));
      }
      fflush(output);
    }
}

static void IOACheckPrintSkipped(long *ptr, Object *theObj)
{
    if (NumIOAGc>=IOAGC_START_TRACE) {
        fprintf(output, 
                "Skipped %d longs\n",
                (int)((long)ptr-(long)theObj)/4);
        fflush(output);
    }
}

static void IOACheckPrintIOA(void)
{
    ;
}

#ifdef MT
#define TheIOATOP ((NumTSD==1)?IOATop:GLOBAL_IOATop)
#else
#define TheIOATOP (GLOBAL_IOATop)
#endif


Object * lastObj=0;

/* IOACheck:
 *   Scan through entire IOA heap and check every object encountered.
 */
void IOACheck()
{
    Object * theObj;
    long        theObjectSize;
    
    theObj = (Object *) GLOBAL_IOA;
    
    lastObj=0;
    IOACheckPrintIOA();
    
    if ((long *)theObj == TheIOATOP) return;
    
    while ((long *)theObj < TheIOATOP) {
#ifdef MT
        /* Skip blank cells in beginning of objects */
        {
            long *ptr = (long *)theObj;
            while ( (ptr<(long*)TheIOATOP) && (*ptr==0) ) ptr++;
            if (ptr==TheIOATOP) break;
            if ((long*)theObj<ptr){
                IOACheckPrintSkipped(ptr, theObj);
                if (NumIOASlices==1) {
                    Claim(FALSE, "No skip should be needed when only one thread");
                }
            }
            theObj = (Object *)ptr;
        }
#else /* Not MT */
        Claim((long)(GETPROTO(theObj)), "IOACheck: GETPROTO(theObj)");
	Claim(IsPrototypeOfProcess((long)(GETPROTO(theObj))),
				   "IsPrototypeOfProcess(Proto)");
#endif /* MT */

        IOACheckPrintTheObj(theObj);

        Claim(inIOA(theObj), "IOACheck: theObj in IOA");
	Claim(isObject(theObj), "isObject(theObj)");
        Claim(ObjectSize(theObj) > 0, "#IOACheck: ObjectSize(theObj) > 0");
        theObjectSize = 4*ObjectSize(theObj);
	Claim(ObjectAlign(theObjectSize)==(unsigned)theObjectSize,
	      "ObjectSize aligned");
        IOACheckObject (theObj);
        lastObj = theObj;
        theObj = (Object *) Offset(theObj, theObjectSize);
    }
    return;
}


void IOACheckReference(REFERENCEACTIONARGSTYPE)
{
    if (*theCell && inBetaHeap(*theCell) && isObject(*theCell)) {
        if (isLazyRef(*theCell)){
            fprintf(output, "Lazy in IOA: 0x%x: %d\n", (int)theCell, (int)*theCell);
            return;
        }
        if (!(inIOA(*theCell) || inAOA(*theCell))) {
            fprintf (output, "theCell = 0x%x, *theCell = 0x%x\n", 
                     (int)theCell, (int)(*theCell));
            Claim(inIOA(*theCell) || 
                  inAOA(*theCell),
		  "IOACheckReference: *theCell lazy ref or inside IOA, AOA");
        }
    }
}

void IOACheckObject (Object *theObj)
{
    scanObject(theObj, IOACheckReference, TRUE);
}

#endif /* RTDEBUG */
