#include "misc.h"
#include "beta.h"
#include "PStore.h"
#include "objectTable.h"
#include "referenceTable.h"
#include "PException.h"
#include "unswizzle.h"
#include "specialObjectsTable.h"

void miscp_dummy() {
#ifdef sparc
  USE();
#endif /* sparc */
}

#ifdef PERSIST

/* LOCAL VARIABLES */

/* LOCAL FUNCTION DECLARATIONS */
static void prependToListRegardless(REFERENCEACTIONARGSTYPE);

/* FUNCTIONS */
void delayedInsert(Object *theObj) 
{
  Claim(theObj == getRealObject(theObj), "Unexpected part object");
  
  insertObject(DELAYEDENTRYALIVE,
	       0,       /* Not used */
	       0,       /* Not used */
	       theObj);
}

void markPersistentObject(Object *theObj)
{
  Object *realObj;
  
  realObj = getRealObject(theObj);
  
  if (inIOA(realObj)) {
    realObj -> GCAttr = IOAPersist;
  } else {
    newPersistentObject(realObj);
  }
}

void markSpecialObject(unsigned long tag, Object *theObj)
{
  Object *realObj;
  
  realObj = getRealObject(theObj);
  
  if (inIOA(realObj)) {
    realObj -> GCAttr = IOASpecial;
    saveTagForObject(realObj, tag);
  } else {
    insertSpecialObject(tag, realObj);
  }
}

/* 'theObj' is a new object just declared persistent. */
void newPersistentObject(Object *theObj) 
{
  unsigned long inx, GCMark;
  StoreProxy *sp;
  
  Claim(theObj == getRealObject(theObj), "Unexpected part object");
  Claim(!inPIT((void *)(theObj -> GCAttr)), "Allready persistent?");
  
  if (repeatIOAGc) {
    GCMark = POTENTIALLYDEAD;
  } else {
    GCMark = ENTRYALIVE;
  }
  /* Create space for the object in the current store */
  sp = allocateObject(4*ObjectSize(theObj));
  
  Claim(sp != NULL, "Could not create new object in store");
  
  /* Create new entry in the objectTable */
  inx = insertObject(GCMark,
		     sp -> storeID,
		     sp -> offset,
		     theObj);
  free(sp);
  theObj -> GCAttr = PERSISTENTMARK(inx);
  
  INFO_PERSISTENCE(persistentBytes+= 4*ObjectSize(theObj));
  INFO_PERSISTENCE(newObjects+=1);
}

/* Given a cell in a persistent object, all objects referred
   (transitively) are appended to the list of persistent objects. */
void markReachableObjects(REFERENCEACTIONARGSTYPE)
{
  Object *realObj;
  Claim(inAOA(theCell), "Where is theCell ?");
  
  if (!inPIT((void *)*theCell)) {
    realObj = getRealObject(*theCell);
    if (!inPIT((void *)(realObj -> GCAttr))) {
      /* Dont follow references to special objects */
      if (inToSpace(realObj)) {
	if (!(realObj -> GCAttr == IOASpecial)) {
	  /* New persistent Object */
	  collectList(realObj, prependToListRegardless);
	}
      } else {
	Claim(inAOA(realObj), "markReachableObjects: Where is theObj?");
	if (!(realObj -> GCAttr == AOASpecial)) {
	  /* New persistent Object */
	  collectList(realObj, prependToListRegardless);
	}
      }
    }
  }
  
  /* AOAToIOATable need not be updated since all persistent objects in
     IOA will be moved to AOA at the next IOAGC. */
  
  /* collectList can handle references to part objects */
}

static void prependToListRegardless(REFERENCEACTIONARGSTYPE)
{
  Object *realObj;

  if (!inPIT((void *)*theCell)) {
    realObj = getRealObject(*theCell);
    if (!inPIT((void *)(realObj -> GCAttr))) {
      /* Dont follow references to special objects. There is no
         special objects in IOA at this point since we have just
         finished an IOAGC */
      if ((!inToSpace(realObj) /* inAOA */) && (realObj -> GCAttr == AOASpecial)) {
	Claim(inAOA(realObj), "prependToListRegardless: Where is theObj?");
	;
      } else {
	prependToList(*theCell);
      }
    }
  }
}

void handleNewPersistentObject(Object *theObj)
{
  Claim(theObj == getRealObject(theObj), "Unexpected part object");
  
  if (inToSpace(theObj)) {
    theObj -> GCAttr = IOAPersist;
  } else {
    Claim(inAOA(theObj), "Where is theObj ??");
    newPersistentObject(theObj);
  }
}

void markOfflineAndOriginObjectsAlive(REFERENCEACTIONARGSTYPE)
{
  Object *theObj, *theRealObj;
  unsigned long inx;
  char GCAttr;
  unsigned long store;
  unsigned long offset;
  
  if (!inPIT(*theCell)) {
    if (refType == REFTYPE_DYNAMIC) {
#ifdef RTDEBUG
      if ((theObj = *theCell)) {
	ProtoType * theProto;
	theProto = GETPROTO(theObj);
	
	if (isSpecialProtoType(theProto)) {
	  switch (SwitchProto(theProto)) {
	  case SwitchProto(DynItemRepPTValue):
	  case SwitchProto(DynCompRepPTValue): 
	  case SwitchProto(RefRepPTValue): 
	    Claim(FALSE, "markOfflineAndOriginObjectsAlive: Splitting up part");
	    break;
	  }
	}
      }
#endif /* RTDEBUG */
      return;
    } else {
      if ((theObj = *theCell)) {
	
	theRealObj = getRealObject(theObj);
	
	if (AOAISPERSISTENT(theRealObj)) {
	  Claim(inAOA(theRealObj), "Where is the origin ?");
	  
	  inx = getPUID((void *)(theRealObj -> GCAttr));
	  objectLookup(inx,
		       &GCAttr,
		       &store,
		       &offset,
		       &theObj);
	  
	  Claim(GCAttr != ENTRYDEAD, "Obj is dead ??");
	  Claim(theObj == theRealObj, "Table mismatch ?");
	  
	  if (GCAttr != ENTRYALIVE) {
	    objectAlive(theRealObj);
	    /* Call recursively on the origin or offline object */
	    scanObject(theRealObj,
		       markOfflineAndOriginObjectsAlive,
		       NULL,
		       TRUE);
	  }
	} else {
	  /* Origin is special object and not in table */
	  ;
	}
      }
    }
  }
}

void handlePersistentCell(REFERENCEACTIONARGSTYPE)
{
  Object *realObj, *theObj;
  unsigned long inx;
  char GCAttr;
  unsigned long store;
  unsigned long offset;
  
  theObj = *theCell;
  
  /* If this is the closing GC, then the live object containing this
     reference is retained in memory after close. This is because it
     might be the origin of some transient object. All persistent
     objects referred by the object containing this reference should
     no longer be reachable, since the store is closed. The reference
     is set to NULL. */
  
  if (inPIT((void *)theObj)) {
    /* The reference is in proper format already */
    referenceAlive((void *)theObj);
    newAOAclient(getPUID((void *)theObj), theCell);
    INFO_PERSISTENCE(PtoD++);
    return;
  } else {
    unsigned long newEntryInx, distanceToPart;
    
    realObj = getRealObject(theObj);
    distanceToPart = (unsigned long)theObj - (unsigned long)realObj;
    
    if (AOAISPERSISTENT(realObj)) {
      Claim(inAOA(realObj), "Where is the object?");
      inx = getPUID((void *)(realObj -> GCAttr));
      objectLookup(inx,
		   &GCAttr,
		   &store,
		   &offset,
		   &theObj);
      
      if (GCAttr == POTENTIALLYDEAD) {
	
	Claim(refType == REFTYPE_DYNAMIC, "handlePersistentCell: Illegal referencetype");
	
	/* The referred object will be removed so we need to unswizzle
	   the reference to it. */
	
	if ((newEntryInx = indexLookupRT(store, offset + distanceToPart)) == -1) {
	  /* A new entry is created */
	  newEntryInx = insertReference(ENTRYALIVE,
					store,
					offset + distanceToPart);
	} else {
	  /* An indirect reference exists to the object that this cell
	     refers directly. This is unsafe since reference
	     comparison could be compromised. This can happen if the
	     reference type is offline or origin, since offline/origin
	     allocated objects are fetched and unswizzled immidiately
	     where as dynamic references are unswizzled at IOAGc
	     only. */
	  
	  /* If this reference type is offline or origin, we know
             about the problem. If it is not, an offline/origin
             reference has been copied to a dynamic cell. */
	  
	  /* The problem can be fixed by generating a refnon check on
	     both arguments to a reference comparison iff either
	     reference has type offline/origin. This is not
	     transparent as all programs would suffer. Thus this
	     approach is only feasible if such reference comparisons
	     are seldom. */

	  /* In other words: the 'indexLookupRT' above should not be
             necessary */
	  ;
	}
	*theCell = newPUID(newEntryInx);
	Claim(*theCell != NULL, "Assigning NULL");
	referenceAlive((void *)*theCell);
	newAOAclient(newEntryInx, theCell);
	INFO_PERSISTENCE(PtoD++);
      } else {
	Claim(GCAttr == ENTRYALIVE, "What is GC mark ?");
      }
    } else {
      ;
    }
  }
}

void resetStatistics(void)
{
  TtoP = 0;
  numP = 0;
  PtoD = 0;
  numD = 0;
  numPB = 0;
  numDE = 0;
}

void showStatistics(void)
{
  /* INFO_PERSISTENCE(fprintf(output, "[Persistence statistics\n");
     fprintf(output, " Pers. before GC         : %d\n", numPB);
     fprintf(output, " Delayed entries used    : %d\n", numDE);
     fprintf(output, " Trans. to Pers. refs    : %d\n", TtoP);
     fprintf(output, " Persistent Objects      : %d\n", numP);
     fprintf(output, " Pers. alive to dead refs: %d\n", PtoD);
     fprintf(output, " Dead pers. objects      : %d\n", numD);
     fprintf(output, "\n");
     fprintf(output, " Block loads             : %d\n", numSL);
     fprintf(output, "\n");
     fprintf(output, " OT size                 : %d\n", (int)OTSize());
     fprintf(output, "]\n")); */

  printObjectStoreStatistics();
  printProxyStatistics();
  showUnswizzleStatistics();
}

/* */

void getKeyForObject(ObjectKey *ok, Object *theObj)
{
  unsigned long inx;
  char GCAttr;
  unsigned long store;
  unsigned long offset;
  Object *theObjInTable;
  
  Claim(getRealObject(theObj) == theObj, "Cannot get key for part object");
  Claim(AOAISPERSISTENT(theObj), "Cannot get key for transient object");
  
  if (inPIT((void *)(theObj -> GCAttr))) {
    inx = getPUID((void *)(theObj -> GCAttr));
    
    
    objectLookup(inx,
		 &GCAttr,
		 &store,
		 &offset,
		 &theObjInTable);
  } else {
    store = -1;
    offset = -1;
  }
  
  Claim(GCAttr != ENTRYDEAD, "theObj is dead ??");
  Claim(theObj == theObjInTable, "Table mismatch ??");
  
  ok -> store = store;
  ok -> offset = offset;
  
}

void setClosingGC(void)
{
  forceAOAGC = TRUE;
  closingGC = TRUE;
}

void setForceAOAGG(void)
{
  forceAOAGC = TRUE;
}

#endif /* PERSIST */
