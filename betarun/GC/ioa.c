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

#ifdef hpux
/* #include <sys/cache.h> */
#endif

#define REP ((ObjectRep *)theObj)

#ifndef MT
GLOBAL(static int IOALooksFullCount) = 0; /* consecutive unsuccessful IOAGc's */
#endif

/* GLOBAL FUNCTIONS, defined in C/function.h
 *
 *   void IOAGc()
 *   void ProcessReference(Object ** theCell)
 *   void ProcessObject(Object * theObj)
 *   void CompleteScavenging()
 *
 *   #ifndef KEEP_STACKOBJ_IN_IOA
 *   void DoIOACell(Object **theCell,Object *theObj)
 *   #endif 
 *
 *   #ifdef RTDEBUGGC/
 *   void IOACheck()
 *   void IOACheckObject (Object *theObj)
 *   void IOACheckReference(REFERENCEACTIONARGSTYPE)
 *   #endif 
 */

/* LOCAL FUNTIONS */
static void ProcessAOAReference(Object ** theCell);
static void ProcessAOAObject(Object * theObj);

#ifndef KEEP_STACKOBJ_IN_IOA
static void DoAOACell(Object **theCell,Object *theObj);
#endif /* KEEP_STACKOBJ_IN_IOA */

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
#if defined(MAC)
    RotateTheCursor();
#endif
  
    DEBUG_IOA(
        fprintf(output,
                "\nBefore: IOA: 0x%x, IOATop: 0x%x, IOALimit: 0x%x\n",
                (int)GLOBAL_IOA, (int)GLOBAL_IOATop, (int)GLOBAL_IOALimit);
        fprintf(output,
                "Before: ToSpace: 0x%x, ToSpaceTop: 0x%x, ToSpaceLimit: 0x%x\n", 
                (int)ToSpace, (int)ToSpaceTop, (int)ToSpaceLimit);
        );

    /* Clear ToSpace to trigger errors earlier */
    DEBUG_CODE(memset(ToSpace, 0, IOASize));
  
    NumIOAGc++;

    DEBUG_CODE(if (NumIOAGc==DebugStackAtGcNum) DebugStack=1);
    
    INFO_IOA(fprintf(output, "#(IOA-%d, %d bytes requested,", 
                     (int)NumIOAGc, (int)ReqObjectSize*4));
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
  
#ifdef KEEP_STACKOBJ_IN_IOA
    IOAStackObjectSum = IOAStackObjectNum = 0;
#endif

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
                DEBUG_IOA(Claim(inAOA(*pointer), "AOAtoIOAtable has a cell outside AOA"));
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
#ifdef MAC
        EnlargeMacHeap(buf);
#else
        Notify(buf);
#endif
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
  DEBUG_IOA(fprintf(output, " #(IOA: Roots: ReferenceStack"); fflush(output));
  ProcessRefStack();
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
            for (;;) {
                Object *nextHead;
                
                ProcessAOAObject(HandledInAOAHead);
                CompleteScavenging();

                nextHead = (Object *)HandledInAOAHead->GCAttr;
                HandledInAOAHead->GCAttr = DEADOBJECT;

                if (HandledInAOAHead == HandledInAOATail) {
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
    
    if (AOANeedCompaction || forceAOAGC) {
        AOAGc();
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
        long * Tmp; long * TmpTop; 
    
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
    
        if (limit && (IOAtoAOAtreshold < IOAMaxAge))
            IOAtoAOAtreshold +=1;
        DEBUG_CODE(Claim(IOAtoAOAtreshold <= IOAMaxAge, "IOAtoAOAtreshold <= IOAMaxAge"));
    }
    DEBUG_IOA( fprintf(output, " treshold=%d", (int)IOAtoAOAtreshold));
    DEBUG_IOA( fprintf(output, " AOAroots=%d", 
                       (int)areaSize(AOArootsPtr,AOArootsLimit)));
  
    INFO_IOA(fprintf(output," %d%% used)\n",
                     (int)((100 * areaSize(GLOBAL_IOA,GLOBAL_IOATop))/areaSize(GLOBAL_IOA,GLOBAL_IOALimit))));
  
    /* Clear all of the unused part of IOA (i.e. [IOATop..IOALimit[), 
     * so that allocation routines do not need to clear cells.
     */
    memset(GLOBAL_IOATop, 0, (long)GLOBAL_IOALimit-(long)GLOBAL_IOATop);

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

#ifndef KEEP_STACKOBJ_IN_IOA
/* DoIOACell:
 *  Used by the routines in stack.c, that traverse the stack and
 *  stackobjects.
 */
void DoIOACell(Object **theCell,Object *theObj)
{    
    if (!theObj) {
        return;
    }
    if(inBetaHeap(theObj)){
        if (isObject(theObj)) {
	    DEBUG_CODE(if (!CheckHeap) Ck(theObj));
            ProcessReference(theCell);
            CompleteScavenging();
        } else {
#ifdef RTLAZY
            if (isLazyRef(theObj)) {
                DEBUG_LAZY(fprintf(output, 
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
#if defined(RTDEBUG) && defined(NEWRUN)
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
static void DoAOACell(Object **theCell,Object *theObj)
{
  if (theObj
      && inBetaHeap(theObj)
      && isObject(theObj)) {
    ProcessAOAReference((Object **)theCell);
  }
}

#endif /* KEEP_STACKOBJ_IN_IOA */

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
     Object ** theCell;
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
  }
}

/*
 * ProcessObject:
 *  Takes as input a reference to an object residing in the ToSpace.
 *  It traverses the object and processes all the references in it.    
 */

void ProcessObject(theObj)
     Object * theObj;
{ 
    ProtoType * theProto;
  

    theProto = theObj->Proto;

#ifdef MT
    /* The way part objects are allocated in V-entries
     * may leave part objects with uninitialized prototypes.
     */
    if (!theProto) return;
#endif
  
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
              ProcessReference( (Object **)(&REP->iOrigin) );
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
                    ProcessReference( (Object **)(pointer++) );
                }
                }
                }
                break;
              }
              return;

          case SwitchProto(RefRepPTValue):
              /* Scan the repetition and follow all entries */
          { long * pointer;
          register long size, index;
      
          size = ((RefRep*)(theObj))->HighBorder;
          pointer =  (long *) &((RefRep*)(theObj))->Body[0];
      
          for(index=0; index<size; index++) 
              if( *pointer != 0 ) ProcessReference( (Object **)(pointer++) );
              else pointer++;
          }
          return;
    
          case SwitchProto(ComponentPTValue):
          { Component * theComponent;
      
          theComponent = ((Component*)theObj);
          ProcessReference( (Object **)(&theComponent->StackObj));
          ProcessReference( (Object **)(&theComponent->CallerComp));
          ProcessReference( &theComponent->CallerObj);
          ProcessObject( (Object *)ComponentItem( theComponent));
          }
          return;
    
          case SwitchProto(StackObjectPTValue):
#if !defined(KEEP_STACKOBJ_IN_IOA)
              ProcessStackObj((StackObject *)theObj, DoIOACell);
#else
              ProcessStackObj((StackObject *)theObj);
#endif
	      CompleteScavenging();
              return;
      
          case SwitchProto(StructurePTValue):
              ProcessReference( &((Structure*)theObj)->iOrigin );
              return;
      
          case SwitchProto(DopartObjectPTValue):
              ProcessReference( &((DopartObject *)(theObj))->Origin );
              return;
        }
    }else{
        GCEntry *tab =
            (GCEntry *) ((char *) theProto + theProto->GCTabOff);
        short *refs_ofs;
        Object **theCell;
    
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
                ProcessObject((Object *)((long *)theObj + tab->StaticOff));
    
        /* Handle all the references in the Object. */
        for (refs_ofs = (short *)&tab->StaticOff + 1; *refs_ofs; ++refs_ofs) {
            theCell = (Object **) ((char *) theObj + ((*refs_ofs) & (short) ~3));
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
static void ProcessAOAReference(Object ** theCell)
{
    Object * theObj;
    long GCAttribute;

    /*fprintf(output, "ProcessAOAReference: 0x%x\n", *theCell);*/
  
    DEBUG_AOA( Claim( inAOA( theCell),"#ProcessAOAReference: theCell inside AOA\n"));
    theObj = *theCell; /* the object referenced from the cell */
  
    if( inIOA(theObj)){ /* theObj is inside IOA */
        GCAttribute = theObj->GCAttr;
        if( isForward(GCAttribute) ){ /* theObj has a forward pointer. */
            *theCell = (Object *) GCAttribute;
        }else{
            if( isAutonomous(GCAttribute) ){ 
                /* theObj is an autonomous object. Move it from IOA to AOA */
                *theCell = NewCopyObject( theObj, 0);
            }else{ /* theObj is a part object. */
                long Distance;
                Object * newObj;
                Object * AutObj;
	
                GetDistanceToEnclosingObject(theObj, Distance);
                AutObj = (Object *) Offset( theObj, Distance);
		/* FIXME: was !isAutonomous(AutObj->GCAttr). Why? */
                if (isForward(AutObj->GCAttr)) {
                    newObj = (Object *) AutObj->GCAttr;
                } else {
                    newObj = NewCopyObject( AutObj, 0);
		}
                *theCell = (Object *) Offset( newObj, -Distance); 
            }
        }
    }
    
    DEBUG_AOA( Claim( !inIOA(*theCell),"ProcessAOAReference: !inIOA(*theCell)"));
    DEBUG_AOA( if( inAOA( *theCell)){ AOACheckObjectSpecial( *theCell); } );
  
    /* Insert 'theCell' in the AOAtoIOAtable iff *theCell is inToSpace. */
    /* Otherwise, if *theCell is a dangling (negative) reference, insert it in
     * negAOArefs */
    if( inToSpace( *theCell ) ) {
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
}

/*
 * ProcessAOAObject:
 *  Takes as input a reference to an object residing in the AOA.
 *  It traverse the object and process all the references in it.    
 */

static void ProcessAOAObject(Object * theObj)
{ ProtoType * theProto;

 theProto = theObj->Proto;

#ifdef MT
/* The way part objects are allocated in V-entries
 * may leave part objects with uninitialized prototypes.
 */
 if (!theProto) return;
#endif

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
           ProcessAOAReference( (Object **)(&REP->iOrigin) );
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
                 ProcessAOAReference( (Object **)(pointer++) );
             }
             }
             }
             break;
           }
           return;

       case SwitchProto(RefRepPTValue):
           /* Scan the repetition and follow all entries */
       { long * pointer;
       register long size, index;
    
       size = ((RefRep*)(theObj))->HighBorder;
       pointer =  (long *) &((RefRep*)(theObj))->Body[0];
       for(index=0; index<size; index++) 
           if(*pointer) 
               ProcessAOAReference( (Object **)(pointer++) );
           else pointer++;
       }
       return;
       case SwitchProto(ComponentPTValue):
       { Component * theComponent;
       theComponent = ((Component*)theObj);
       ProcessAOAReference( (Object **)(&theComponent->StackObj));
       ProcessAOAReference( (Object **)(&theComponent->CallerComp));
       ProcessAOAReference( (Object **)(&theComponent->CallerObj));
       ProcessAOAObject( (Object *)(ComponentItem( theComponent)));
       }
       return;
       case SwitchProto(StackObjectPTValue):
#ifdef KEEP_STACKOBJ_IN_IOA
           Claim( FALSE, "ProcessAOAObject: No StackObject in AOA");
#else
           /* Machine dependant traversal of stackobj */
           ProcessStackObj((StackObject *)theObj, DoAOACell);
#endif /* KEEP_STACKOBJ_IN_IOA */
	   CompleteScavenging();
           return;
       case SwitchProto(StructurePTValue):
           ProcessAOAReference( &(((Structure*)(theObj)))->iOrigin );
           return;
       case SwitchProto(DopartObjectPTValue):
           ProcessAOAReference( &((DopartObject *)(theObj))->Origin );
           return;
     }
 }else{
     short *  Tab;
     long *   theCell;
  
     /* Calculate a pointer to the GCTabel inside the ProtoType. */
     Tab = (short *) ((long) ((long) theProto) + ((long) theProto->GCTabOff));
  
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
             ProcessAOAObject( (Object *)(Offset( theObj, *Tab * 4)));
         Tab += 4;
     }
     Tab++;
  
     /* Handle all the references in the Object. */
     while( *Tab != 0 ){
         theCell = (long *) Offset( theObj, ((*Tab++) & (short) ~3) );
         /* sbrandt 24/1/1994: 2 least significant bits in prototype 
          * dynamic offset table masked out. As offsets in this table are
          * always multiples of 4, these bits may be used to distinguish
          * different reference types. */ 
         if(*theCell) ProcessAOAReference( (Object **)theCell );
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
  Object * theObj;
  DEBUG_CODE(static int NumCompleteScavenging=0; NumCompleteScavenging++);
  
  /* CompleteScavenging should NOT be called by functions, that
   * just *check* heaps. One way to ensure this is that
   * IOAActive is true.
   * (This is debug code only)
   */
  Claim(IOAActive, "CompleteScavenging: IOAActive");
  while( HandledInToSpace < ToSpaceTop){
    theObj = (Object *) HandledInToSpace;
    HandledInToSpace = (long *) (((long) HandledInToSpace)
				    + 4*ObjectSize(theObj));
    DEBUG_CODE(Claim(ObjectSize(theObj)>0, "CompleteScavenging: ObjectSize(theObj)>0"));
    ProcessObject( theObj);
  }
  DEBUG_CODE( Claim( HandledInToSpace == ToSpaceTop,
		     "CompleteScavenging: HandledInToSpace == ToSpaceTop"));
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
        Claim((long)(theObj->Proto), "IOACheck: theObj->Proto");
#endif /* MT */

        IOACheckPrintTheObj(theObj);

        Claim(inIOA(theObj), "IOACheck: theObj in IOA");
        theObjectSize = 4*ObjectSize(theObj);
        Claim(ObjectSize(theObj) > 0, "#IOACheck: ObjectSize(theObj) > 0");
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
            Claim( inIOA(*theCell) || 
                   inAOA(*theCell)
#ifdef MT
                   || (long)*theCell==16 /* dreadfull hack (see AlloBC) */
#endif
                   ,
                   "IOACheckReference: *theCell lazy ref or inside IOA, AOA");
        }
    }
}

void IOACheckObject (Object *theObj)
{
    scanObject(theObj, IOACheckReference, TRUE);
}

#endif /* RTDEBUG */
