#include "misc.h"
#include "beta.h"
#include "PStore.h"
#include "objectTable.h"
#include "referenceTable.h"
#include "PException.h"
#include "unswizzle.h"
#include "specialObjectsTable.h"
#include "trie.h"
#include "../C/dot.h"

#ifdef PERSIST

/* IMPORTS */
extern int betaenvHandle; 
extern int programHandle;

/* LOCAL VARIABLES */

/* LOCAL FUNCTION DECLARATIONS */

/* FUNCTIONS */
void forceObjectToAOA(Object *theObj)
{
  Object *theRealObj;

  if (!inPIT(theObj)) {
    theRealObj = getRealObject(theObj);
    if (inIOA(theRealObj)) {
      theRealObj -> GCAttr = IOAMaxAge;
    }
  } else {
    /* theObj is a proxy reference. This means that the referred
       object is either in the store or AOA. */
    ;
  }
}

void markSpecialObject(unsigned long tag, Object *theObj)
{
  Object *realObj, *currentBetaenvObj, *currentProgramObj;

  currentBetaenvObj = DOThandleLookup(betaenvHandle);
  currentProgramObj = DOThandleLookup(programHandle);
  
  if (tag == BETAENVOBJ) {
    if (theObj != currentBetaenvObj) {
      fprintf(output, "markSpecialObject: Tag %d may only be used for BETAENV (this *will* cause problems soon, use another tag value for this object)\n", BETAENVOBJ);
    }
  }
  
  if (tag == PRGOBJ) {
    if (theObj != currentProgramObj) {
      fprintf(output, "markSpecialObject: Tag %d may only be used for PROGRAM (this *will* cause problems soon, use another tag value for this object)\n", PRGOBJ);
    }
  }
  
#ifndef sparc
  if (theObj != currentBetaenvObj) {
    if (theObj != currentProgramObj) {
      fprintf(output, "markSpecialObject: This platform does not support handling of user registered special objects");
    }
  }
#endif /* sparc */
  
  realObj = getRealObject(theObj);
  
  if (inIOA(realObj)) {
    realObj -> GCAttr = IOASpecial;
    saveTagForObject(realObj, tag);
  } else {
    insertSpecialObject(tag, realObj);
  }
}

/* 'theObj' is a new object just declared persistent. */
unsigned long newPersistentObject(unsigned long storeID, Object *theObj) 
{
  unsigned long inx, GCMark;
  StoreProxy *sp;
  
  /* 'storeID' is the context local store id of the store into which
     this objects should be saved. */

  Claim(theObj == getRealObject(theObj), "Unexpected part object");
  Claim(!inPIT((void *)(theObj -> GCAttr)), "Allready persistent?");
  
  /* We cannot save component. Rather they should be registered as
     special objects */

  if (isComponent(theObj)) {
    fprintf(output, "newPersistentObject: Saving component (should be registered as special object)\n");
  }
  
  if (repeatIOAGc) {
    GCMark = POTENTIALLYDEAD;
  } else {
    GCMark = ENTRYALIVE;
  }

  /* Create space for the object in which store ?? */
  sp = allocateObject(storeID, 4*ObjectSize(theObj));
  
  Claim(sp != NULL, "Could not create new object in store");
  
  /* Create new entry in the objectTable */
  /* The flag FLAG_INMEM indicates that this object is not loaded from
     the store. It has no copy following it */
  inx = insertObject((unsigned short)GCMark, FLAG_INMEM,
		     sp -> storeID,
		     sp -> offset,
		     theObj);
  theObj -> GCAttr = PERSISTENTMARK(inx);
  return sp -> offset;
}

unsigned long currentStoreID;

void markReachableObjects(REFERENCEACTIONARGSTYPE)
{
  Object *realObj;
  /* This function initially gets called for each object reachable
     from the persistent objects currently in the object table. */
  
  if (!inPIT((void *)*theCell)) {
    realObj = getRealObject(*theCell);
    if (!inPIT((void *)(realObj -> GCAttr))) {
      /* Dont follow references to special objects */
      if (inToSpace(realObj)) {
	if (realObj -> GCAttr != IOAPersist) {
	  Claim(realObj -> GCAttr != IOASpecial, 
		"markReachableObjects: There should not be any special objects in IOA at this point");
	  
	  /* We have encountered a new persistent object in IOA. It
	     cannot be made persistent all at once since it needs to be
	     moved to AOA first. In order to force a move to AOA we
	     insert in the GC field of the object an indication to the
	     IOA collector that it should force this object into IOA at
	     the next IOA GC. But we still insert the object in the
	     object table. The object table entry will point to the
	     object in IOA. This reference must be redirected when the
	     object is moved to AOA. */
	  
	  realObj -> GCAttr = IOAPersist;
	  
	  insertObject(DELAYEDENTRYALIVE, 
		       0, 
		       currentStoreID,
		       0,       /* Not assigned yet */
		       realObj);
	  
	  /* The referred object should be scanned as well */
	  scanObject(realObj,
		     markReachableObjects,
		     NULL,
		     TRUE);
	} else {
	  /* This object has been persistified already */
	  ;
	}
      } else {
	Claim(inAOA(realObj), "markReachableObjects: Where is theObj?");
	if (!(realObj -> GCAttr == AOASpecial)) {
	  /* We have encountered a new persistent object in AOA, and
             we can now proceed to allocate space for it in the store
             and in the object table. */
	  /* What is the store into which this object should be saved ?" */
	  newPersistentObject(currentStoreID, realObj);
	  
	  /* The referred object should be scanned as well */
	  scanObject(realObj,
		     markReachableObjects,
		     NULL,
		     TRUE);
	} else {
	  /* The referred object is marked as a special object and
             should not be followed */
	  ;
	}
      }
    } else {
      /* The referred object is marked as persistent already */
      ;
    }
  } else {
    /* The reference is in persistent format and can be skipped. */
    ;
  }
  
  /* AOAToIOATable need not be updated since all persistent objects in
     IOA will be moved to AOA at the next IOAGC. */
}

void markOfflineAndOriginObjectsAlive(REFERENCEACTIONARGSTYPE)
{
  Object *theObj, *theRealObj;
  unsigned long inx;
  unsigned short GCAttr;
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
	    Claim(FALSE, "markOfflineAndOriginObjectsAlive: Splitting up part (DynItemRepPTValue)");
	    break;
	  case SwitchProto(DynCompRepPTValue): 
	    Claim(FALSE, "markOfflineAndOriginObjectsAlive: Splitting up part (DynCompRepPTValue)");
	    break;
	  case SwitchProto(RefRepPTValue): 
	    Claim(FALSE, "markOfflineAndOriginObjectsAlive: Splitting up part (RefRepPTValue)");
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
  unsigned short GCAttr;
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
      } else {
	Claim(GCAttr == ENTRYALIVE, "What is GC mark ?");
      }
    } else {
      ;
    }
  }
}

/* Used by objectTable, transitObjectTable and referenceTable to map
   (store,offset) pairs to table entries. */
void insertStoreOffset(unsigned long store, 
		       unsigned long offset, 
		       unsigned long inx,
		       Trie **loadedObjects)
{
  Trie *loadedObjectsOFbefore, *loadedObjectsOFafter;
  
  /* Check if store is member */
  if ((loadedObjectsOFbefore = loadedObjectsOFafter = (Trie *)TILookup(store, *loadedObjects))
      == NULL) {
    /* insert new table for store */
    loadedObjectsOFafter = TInit();
  }
  
  /* insert inx in loadedObjectsOF */
  TInsert(offset, inx, &loadedObjectsOFafter, offset);
  
  /* */
  if (loadedObjectsOFbefore == loadedObjectsOFafter) {
    return;
  } else {
    TInsert(store, (unsigned long)loadedObjectsOFafter, loadedObjects, store);
  }
}

void resetStatistics(void)
{
  ;
}

void showStatistics(void)
{
  INFO_PERSISTENCE(fprintf(output, "[Statistics:\n"));
  INFO_PERSISTENCE(fprintf(output, " Traps              : %d\n", (int)numPF));
  INFO_PERSISTENCE(fprintf(output, " Objects Loaded     : %d\n", (int)objectsLoaded));
  INFO_PERSISTENCE(fprintf(output, " Objects Exported   : %d\n", (int)objectsExported));
  INFO_PERSISTENCE(fprintf(output, " Memory used(kB)    : %d\n", (int)totalAOASize/(int)1024));
  INFO_PERSISTENCE(fprintf(output, " Num IOA-GC         : %d\n", (int)NumIOAGc));
  INFO_PERSISTENCE(fprintf(output, " Mum AOA-GC         : %d]\n", (int)NumAOAGc));
}

/* */

void getKeyForObject(ObjectKey *ok, Object *theObj)
{
  unsigned long inx;
  unsigned short GCAttr;
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

void setForceAOAGG(void)
{
  forceAOAGC = TRUE;
}

#endif /* PERSIST */
