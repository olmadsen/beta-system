/*
 * BETA RUNTIME SYSTEM, Copyright (C) 1990-94 Mjolner Informatics Aps.
 * ioa.c (was: scavenging.c)
 * by Lars Bak, Peter Andersen, Peter Orbaek, Tommy Thorn, Jacob Seligmann and S|ren Brandt
 */

#ifdef RTDEBUG
#define IOAGC_START_TRACE 100000
#endif /* RTDEBUG */

#include "beta.h"
#include "dot.h"

#ifdef PERSIST
#include "objectTable.h"
#include "referenceTable.h"
#include "PException.h"
#include "transitObjectTable.h"
#include "specialObjectsTable.h"
#endif /* PERSIST */

#define REP ((ObjectRep *)theObj)

/* LOCAL FUNTIONS */
static void ProcessAOAReference(Object ** theCell, long refType);
static void ProcessAOAObject(Object * theObj);

#ifdef RTDEBUG
static void IOACheckPrintTheObj(Object *theObj);
#ifdef MT
static void IOACheckPrintSkipped(long *ptr, Object *theObj);
#endif
#endif /* RTDEBUG */


/* OID Impl.  --mg */
typedef struct {
  Object *objInIOA;
  Object *objInAOA;
  unsigned long OID;
} OIDCacheElm;

static OIDCacheElm *OIDCache = NULL;
static long OIDCacheSize = 0;
static long OIDCacheMax = 0;

Object *getObjectByOID(unsigned long OID)
{
  int i;
  Object *obj;

  for (i=0; i < OIDCacheSize; i++) {
    if (OID == OIDCache[i].OID) {
      return OIDCache[i].objInIOA;
    }
  }

  obj = (Object*)(OID<<3);
  Claim(inAOA(obj), "getObjectByOID: object outside AOA");

  return obj;
}

unsigned long getOIDforObject(Object *obj)
{
  if (inAOA(obj)) {
    return ((unsigned long)obj)>>3;
  }

  if (inIOA(obj)) {
    /* Reserve room in AOA, but postpone move until next IOAGc. */
    Object *autObj, *newpos;
    unsigned long size, OID;
    int i;
    autObj = getRealObject(obj);

    for (i=0; i < OIDCacheSize; i++) {
      if (autObj == OIDCache[i].objInIOA) {
	newpos = OIDCache[i].objInAOA;
	OID = (unsigned long)((long)newpos+(long)obj-(long)autObj);
	OIDCache[OIDCacheSize].objInIOA = autObj;
	OIDCache[OIDCacheSize].objInAOA = NULL;
	OIDCache[OIDCacheSize].OID = OID;
	OIDCacheSize++;
	return OID>>3;
      }
    }

    size = 4*ObjectSize(autObj);
    newpos = AOAalloc(size);

    if (OIDCacheSize == OIDCacheMax) {
      if (!OIDCacheMax) {
	OIDCacheMax = 128;
      } else {
	OIDCacheMax *= 2;
      }
      OIDCache = REALLOC(OIDCache, OIDCacheMax*sizeof(OIDCacheElm));
    }
    OID = (unsigned long)((long)newpos+(long)obj-(long)autObj);

    OIDCache[OIDCacheSize].objInIOA = autObj;
    OIDCache[OIDCacheSize].objInAOA = newpos;
    OIDCache[OIDCacheSize].OID = OID;
    OIDCacheSize++;
    return OID>>3;
  }

  fprintf(output, "getOIDforObject(obj=0x%08x): Object is outside heaps\n",
	  (int)obj);
  return 0;
}

static void HandlePostponedIODs(void)
{
  int i;

  for (i=0; i < OIDCacheSize; i++) {
    if (OIDCache[i].objInAOA) {
      CopyObjectToAOA(OIDCache[i].objInIOA, OIDCache[i].objInAOA, TRUE);
    }
  }
  OIDCacheSize = 0;
}

/* IOAfree:
 */
void IOAfree(void)
{
  /* Free everything allocated by IOA */
#ifndef nti
  if (GLOBAL_IOA) FREE(GLOBAL_IOA);
  if (ToSpace) FREE(ToSpace);
#endif
#if defined(NEWRUN) || (defined(RTVALHALLA) && defined(intel))
  if (ReferenceStack) FREE(ReferenceStack);
#endif
#ifdef NEWRUN
  if (CompStack) FREE(CompStack);
#endif

  return;
}

/*
 * IOAGc:
 *  Called from doGC in Misc.c / PerformGC.run.
 *  Make a scavenging garbage collection on IOA.
 *  
 *  SPARC note: See requirements for stack setup before
 *  IOAGc is called in ProcessSPARCStack in stack.c.
 */
void IOAGc()
{
   long starttime;

   inIOAGc = TRUE;
   starttime = 0;
  
#ifdef PERSIST
   repeatIOAGc = 0;
  
  IOAGCstart:
#endif /* PERSIST */
  
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
  
   TIME_IOA(starttime = getmilisectimestamp());

   INFO_IOA({
      starttime = getmilisectimestamp();
      fprintf(output, "#(IOA-%d, %d bytes requested,", 
              (int)NumIOAGc, (int)ReqObjectSize*4);
   });
  
   DEBUG_CODE({
      if (!NoHeapClear) {
         /* Clear ToSpace to trigger errors earlier */
         memset(ToSpace, 0, IOASize);
      }
      if (NumIOAGc==DebugStackAtGcNum) {
         DebugStack=1;
      }
   });
  
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
  
   HandlePostponedIODs();

   /* Process AOAtoIOAtable */
   DEBUG_IOA(fprintf(output, " #(IOA: Roots: AOAtoIOAtable"); fflush(output));
   AOAtoIOACount = 0;
   if (AOAtoIOAtable) { 
      long i;
      int fakes = 0;
      long * pointer = BlockStart( AOAtoIOAtable);
      for(i=0; i<AOAtoIOAtableSize; i++){ 
         if(*pointer){
            AOAtoIOACount++;
            Claim(inAOA(*pointer), "AOAtoIOAtable has a cell outside AOA");
            ProcessAOAReference( (Object **)*pointer, REFTYPE_DYNAMIC);
            if (!((inIOA(**(long**)pointer) || inToSpace(**(long**)pointer)))) {
               *pointer = 0;  // Null out entries we don't need any more
            }
         }
         pointer++;
      }
      if (AOAtoIOACount>AOAtoIOAtableSize/(100/20) && fakes/(AOAtoIOACount/2)) {
         /* More than 20% of the cells in AOAtoIOAtable are in use
          * and more than 50% of the used cells point outside IOA/ToSpace.  
          * That wastes space, and also time on each IOAGc.
          */
         if (!AOANeedCompaction) {
            /* AOA also cleans it, so skip it in that case. */
            AOAtoIOACleanup();
         }
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
   ProcessReference( (Object **)&ActiveComponent, REFTYPE_DYNAMIC);
   DEBUG_IOA(fprintf(output, ")\n"); fflush(output));

   DEBUG_IOA(fprintf(output, " #(IOA: Root: BasicItem"); fflush(output));
   ProcessReference( (Object **)&BasicItem, REFTYPE_DYNAMIC);
   DEBUG_IOA(fprintf(output, ")\n"); fflush(output));

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
  
   CompleteScavenging();
  
   /* Objects copied til AOA until now has not been proceesed. 
    * During proceesing these objects, new objects may be copied to
    * ToSpace and AOA, therefore we must alternate between handling
    * objects in ToSpace and AOA until no more objects is to procees.
    */
   if (AOABaseBlock && HandledInAOAHead) {
      while (1) {
         Object *nextHead;
      
         ProcessAOAObject(HandledInAOAHead);
         CompleteScavenging();
      
         nextHead = (Object *)HandledInAOAHead->GCAttr;
         HandledInAOAHead->GCAttr = DEADOBJECT;
      
         if (HandledInAOAHead != HandledInAOATail) {
            HandledInAOAHead = nextHead;
         } else {
            HandledInAOAHead = NULL;
            break;
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

#ifdef PERSIST
   
   if (!BETAREENTERED) {
      /* Will update reference info on all persistent objects in IOA
       * that has now been moved to AOA.
       */
      phaseThree();
      
#endif /* PERSIST */
      
      if (!noAOAGC) {
#ifdef PERSIST
         if (AOANeedCompaction || forceAOAGC) {
            /* before we do AOAGC we need to do an additional IOAGC */
            if (repeatIOAGc || !callRebinderC) {
               /* We have done the extra IOAGC, or we are not using PS */

               /* All persistent objects have now been moved to AOA
                * and inserted in the PObjects table. All persistent
                * references in IOA have been marked ALIVE.
                */
               AOAGc();
	
               repeatIOAGc = 0;
            } else {
               /* There are no longer any special objects in IOA */
               freeSOTags();
               
               /* Mark special objects moved to AOA as special */
               remarkSpecialObjects();
               
               phaseOne();
               /* All new persistent objects in AOA have been
                * registered in the PObjectsTable and assigned a
                * store. Any new persistent object in IOA has been
                * marked as IOAPersist and will be moved to AOA during
                * the ensuing IOAGc.
                */
               repeatIOAGc = 1;
	
               SOStartGC();

               /* Clears the structure containing all reference info
                * objects. This is rebuild during the ensuing IOAGc
                * and AOAGc.
                */
               RTStartGC();
            }
         } else {
            /* XXX: Unswizzle all flushed references in AOA */
         }   
#else 
         if (AOANeedCompaction || forceAOAGC) {
            AOAGc();
         }
#endif /* PERSIST */
      }
      
#ifdef PERSIST
   } /* BETAREENTERED */
#endif /* PERSIST */
   
   if (tempAOAroots) {
      /* ToSpace was not big enough to hold both objects and table.
       * Free the table that was allocated by saveAOAroot().  */
      tempAOArootsFree();
   }    
  
#ifdef RTDEBUG
   else {
      /* Clear the part of ToSpace used for AOArootstable */
      if (!NoHeapClear) {
         memset(AOArootsPtr, 0, AOArootsLimit-AOArootsPtr);
      };
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
      ALLOC_TRACE_CODE(
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
      limit = IOAPercentage*areaSize(GLOBAL_IOA,GLOBAL_IOALimit) / 100;
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
   {
       long * ioaclear = (long *)GLOBAL_IOATop;
       long * ioatop = ioaclear + (((long)GLOBAL_IOALimit-(long)GLOBAL_IOATop) >> 2);
       for ( ; ioaclear < ioatop; ioaclear++) {
	   *ioaclear = 0;
	   beta_prefetchw512(ioaclear);
	}
   }
  
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
   if (4*ReqObjectSize < (char*)IOALimit-(char*)IOA) {
     /* For an object, that would fit in IOA, actually. */
     if ((long)IOATop+4*(long)ReqObjectSize > (long)IOALimit) {
       /* Not enough freed by this GC. */
       if (IOALooksFullCount > 6) {
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
         if (IOALooksFullCount > 1) {
	   /* Have now done two IOAGc's without freeing enough space.
	    * Make sure that all objects go to AOA in the next GC.
	    */
	   IOAtoAOAtreshold=IOAMinAge+1;
	   DEBUG_IOA(fprintf(output, "Forcing all to AOA in next IOAGc\n"));
         }
         IOALooksFullCount++;
       }
       INFO_IOA(fprintf(output, "[IOALooksFullCount=%d]\n", IOALooksFullCount));
     } else {
       if (FALSE && ((long)IOATop-(long)IOA)/(((long)IOALimit-(long)IOA)/100+1) > 70) {
         IOALooksFullCount = 1;
       } else {
	 if (IOALooksFullCount) {
	   INFO_IOA(fprintf(output, "[IOALooksFullCount=0, was %d]\n",
			    IOALooksFullCount));
	 }
	 IOALooksFullCount = 0;
       }
     }
   }
#endif /* MT */
  
   INFO_IOA({
      fprintf(output," %d%% used, ioatime=%dms)\n",
              (int)((100*areaSize(GLOBAL_IOA,GLOBAL_IOATop))
                    / areaSize(GLOBAL_IOA,GLOBAL_IOALimit)),
              (int)(getmilisectimestamp() - starttime));
   });

   DEBUG_CODE(if (!NoHeapClear) { memset(ToSpace, 0, IOASize); });

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
      fflush(output);
      );
   INFO_HEAP_USAGE(PrintHeapUsage("after IOA GC"));
  
#ifdef PERSIST
   if (repeatIOAGc) {
      goto IOAGCstart;
      /* Yuhuuu!!!! */
   }
#endif /* PERSIST */

   TIME_IOA(ioatime += (getmilisectimestamp() - starttime));

   INFO_AOAUSE({
      fprintf(output, "(AOAUSE:IOA-%d: 0x%08x/0x%08x free, 0x%08x used (%d%%))\n", 
              (int)NumIOAGc, (int)AOAFreeListTotalFree(),
              (int)totalAOASize, (int)(totalAOASize - AOAFreeListTotalFree()),
	      (int)AOAFreeListTotalFree() / ((int)totalAOASize / 100));
   });
   inIOAGc = FALSE;
} /* End IOAGc */

static void IOAUpdateAOARoots(Object **theCell, long GCAttribute)
{
  if (!inToSpace(GCAttribute)) {
    if (inAOA(GCAttribute)) {
      MCHECK();
      Claim(!inAOA(theCell), "!inAOA(theCell)");
      saveAOAroot(theCell);
      MCHECK();
    }
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

void ProcessReference(Object ** theCell, long refType)
{
   Object * theObj;
   long GCAttribute;
  
   theObj = *theCell;
  
   if (inIOA(theObj)) {
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
    
      if (isForward(GCAttribute)) { 
         /* theObj has a forward pointer, i.e has already been moved */
      
         *theCell = (Object *) GCAttribute; /* update cell to reference forward obj */

         /* If the forward pointer refers an AOA object, insert
          * theCell in AOAroots table.
          */
      
         IOAUpdateAOARoots(theCell, GCAttribute);
	
      } else {
         if (isAutonomous(GCAttribute)) { 
            /* '*theCell' is an autonomous object. */
            *theCell = NewCopyObject( *theCell, theCell, FALSE);
	
         } else {
            /* theObj is a part object. */
            long Distance;
            Object * newObj;
            Object * AutObj;
	
            Claim(isStatic(GCAttribute), "Is not static?");
            GetDistanceToEnclosingObject(theObj, Distance);
            AutObj = (Object *) Offset(theObj, Distance);
	
            if (isForward(AutObj->GCAttr)) {
               newObj = (Object *) AutObj->GCAttr;
	  
               /* If the forward pointer refers an AOA object, insert
                * theCell in AOAroots table.
                */
               IOAUpdateAOARoots(theCell, AutObj->GCAttr);
	      
            } else {
               newObj = NewCopyObject( AutObj, theCell, FALSE);
            }
            *theCell = (Object *) Offset( newObj, -Distance);
         }
      }
      
      /* The referred object must have been copied to ToSpace */
      Claim(!inIOA(*theCell),"ProcessReference: !inIOA(*theCell)");
      
      /* End inIOA(theObj) */
      
   } else {
      /* '*theCell' is pointing outside IOA */
      /* If the forward pointer refers an AOA object, insert
       * theCell in AOAroots table.
       */
      Claim(!inToSpace(*theCell), "*theCell is in to space ??");
    
      if (inAOA(*theCell)) {
         MCHECK();
         Claim(!inAOA(theCell), "!inAOA(theCell)");
         saveAOAroot(theCell);
         MCHECK();
         return;
      } 
#ifdef PERSIST
      else 
         if (inPIT((void *)*theCell)) {
            referenceCheck(theCell);
         } 
#endif /* PERSIST */
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
  scanObject(theObj,
             ProcessReference,
	     NULL,
             TRUE);
}

/*
 * ProcessAOAReference:
 *  Takes as input a reference to a cell residing inside AOA.
 *  If the cell refers an object residing in IOA, the 
 *  object is copied to ToSpace/AOA and the cell is updated.
 *  Furthermore a forward reference in the most enclosing
 *  object is inserted in the GC-attribute.
 */

static void ProcessAOAReference(Object ** theCell, long refType)
{
  Object * theObj;
  long GCAttribute;

#ifndef PERSIST
  if (*theCell) {
    /* This Claim assumes that the StackObj is at offset 8 in
     * the Component struct. --mg
     */
    Claim(inBetaHeap(*theCell) ||
          ((long)*theCell==-1 && GETPROTO((Object *)(theCell-2))==ComponentPTValue),
	  "inBetaHeap(*theCell)");
  } else {
    return;
  }
#endif /* PERSIST */

  Claim(inAOA(theCell), "ProcessAOAReference: Where is theCell ?");
  
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
	*theCell = NewCopyObject(theObj, NULL, FALSE);

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
	  newObj = NewCopyObject(AutObj, 0, FALSE);
	}
	*theCell = (Object *) Offset(newObj, -Distance); 
      }
    }
  } 
  
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
#ifdef PERSIST
  else if (inPIT((void *)*theCell)) {
     referenceCheck(theCell);
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
	     NULL,
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

  /* If ToSpace is filled more than half, there won't be much space
   * left for new objects
   * Make sure AOA accepts allocationrequests, even if it means
   * allocating more memory
   */
  if (((long)ToSpaceTop-(long)ToSpace*2)/((long)ToSpaceLimit-(long)ToSpace)
      && !IOALooksFullCount) {
    IOALooksFullCount = 1;
  }
  
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

#ifdef MT
#define TheIOATOP ((NumTSD==1)?IOATop:GLOBAL_IOATop)
#else
#define TheIOATOP (GLOBAL_IOATop)
#endif

Object * lastObj=0;

void foreachObjectInIOA(void (*objectAction)(Object *, void *),
			void *generic)
{
  Object * theObj;
  long        theObjectSize;
  
  theObj = (Object *) GLOBAL_IOA;
  
  lastObj=0;
  
  if ((long *)theObj == TheIOATOP) return;
  
  while ((long *)theObj < TheIOATOP) {
    
    objectAction(theObj, generic);
    
    theObjectSize = 4*ObjectSize(theObj);
    theObj = (Object *) Offset(theObj, theObjectSize);
  }
}

void setForceAOAGC(void)
{
  forceAOAGC = TRUE;
}

#ifdef RTDEBUG

void saveAOArootDebug(Object **cell)
{
   if ((ToSpaceTop == AOArootsPtr) || (tempAOAroots==AOArootsPtr)) {
      tempAOArootsAlloc();   
   }
   TRACE_SAVE_AOA_ROOT();                                            
   *--AOArootsPtr = (long) (cell);
}

static void IOACheckPrintTheObj(Object *theObj)
{
#ifdef FASTDEBUG
  return;
#else
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
#endif /* FASTDEBUG */
}

#ifdef MT
static void IOACheckPrintSkipped(long *ptr, Object *theObj)
{
  if (NumIOAGc>=IOAGC_START_TRACE) {
    fprintf(output, 
	    "Skipped %d longs\n",
	    (int)((long)ptr-(long)theObj)/4);
    fflush(output);
  }
}
#endif

/* IOACheck:
 *   Scan through entire IOA heap and check every object encountered.
 */
void checkObjectAction(Object *theObj, void *generic) 
{
#ifdef FASTDEBUG
  return;
#else
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
  
  { 
    long theObjectSize;

    IOACheckPrintTheObj(theObj);
    
    Claim(inIOA(theObj), "IOACheck: theObj in IOA");
    Claim(isObject(theObj), "isObject(theObj)");
    Claim(ObjectSize(theObj) > 0, "#IOACheck: ObjectSize(theObj) > 0");
    theObjectSize = 4*ObjectSize(theObj);
    Claim(ObjectAlign(theObjectSize)==(unsigned)theObjectSize,
	  "ObjectSize aligned");
  }
  IOACheckObject (theObj);
#endif /* FASTDEBUG */
}  

void IOACheck()
{
  foreachObjectInIOA(checkObjectAction, NULL);
}

void IOACheckReference(REFERENCEACTIONARGSTYPE)
{
  if (*theCell && inBetaHeap(*theCell) && isObject(*theCell)) {
    if (!(inIOA(*theCell) || inAOA(*theCell))) {
      fprintf (output, "[IOACheckReference: Warning, target outside heap:"
	       " theCell=0x%x, *theCell=0x%x]\n", (int)theCell, (int)(*theCell));
    }
  } 
#ifdef PERSIST
  else {
     if (*theCell && inPIT(*theCell)) {
        ;
     }
  }
#endif /* PERSIST */
}

void IOACheckObject (Object *theObj)
{
  scanObject(theObj, IOACheckReference, NULL, TRUE);
}

#endif /* RTDEBUG */


