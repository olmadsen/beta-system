#include "misc.h"
#include "beta.h"
#include "objectTable.h"
#include "crossStoreTable.h"
#include "referenceTable.h"
#include "PException.h"
#include "unswizzle.h"

void miscp_dummy() {
#ifdef sparc
  USE();
#endif /* sparc */
}

#ifdef PERSIST

/* LOCAL VARIABLES */

/* LOCAL FUNCTION DECLARATIONS */
static void markOriginAlive(Object **theCell);
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

/* 'theObj' is a new object just declared persistent. */
void newPersistentObject(Object *theObj) 
{
  u_long inx, GCMark;
  StoreProxy *sp;
  
  Claim(theObj == getRealObject(theObj), "Unexpected part object");
  Claim(!inPIT((void *)(theObj -> GCAttr)), "Allready persistent?");
  
  if (repeatIOAGc) {
    GCMark = POTENTIALLYDEAD;
  } else {
    GCMark = ENTRYALIVE;
  }
  /* Create space for the object in the current store */
  sp = newStoreObject(theObj);
  
  Claim(sp != ILLEGALSTOREPROXY, "Could not create new object in store");
  
  /* Create new entry in the objectTable */
  inx = insertObject(GCMark,
		     sp -> store,
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
      /* New persistent Object */
      collectList(realObj, prependToListRegardless);
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
      prependToList(*theCell);
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

static void markOriginAlive(Object **theCell)
{
  Object *theOrigin, *theRealOrigin;
  u_long inx;
  char GCAttr;
  BlockID store;
  u_long offset;
  Object *theObj;

  if ((theOrigin = *theCell)) {
    theRealOrigin = getRealObject(theOrigin);
    
    Claim(inAOA(theRealOrigin), "Where is the origin ?");
    Claim(AOAISPERSISTENT(theRealOrigin), "Origin object not persistent ??");
    
    inx = getPUID((void *)(theRealOrigin -> GCAttr));
    objectLookup(inx,
		 &GCAttr,
		 &store,
		 &offset,
		 &theObj);
    
    Claim(GCAttr != ENTRYDEAD, "Origin is dead ??");
    Claim(theObj == theRealOrigin, "Table mismatch ?");

    if (GCAttr != ENTRYALIVE) {
      objectAlive(theRealOrigin);
      Claim(objectAction == markOriginsAlive, "What is the object action?");
      /* Call recursively on the origin object */
      scanObject(theRealOrigin,
		 NULL,
		 TRUE);
    }
  }
}

void markOriginsAlive(Object *theObj)
{
  scanOrigins(theObj, markOriginAlive);
}

void handlePersistentCell(REFERENCEACTIONARGSTYPE)
{
  Object *realObj, *theObj;
  u_long inx;
  char GCAttr;
  BlockID store;
  u_long offset;
  
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
      u_long newEntryInx, distanceToPart;
      
      realObj = getRealObject(theObj);
      distanceToPart = (u_long)theObj - (u_long)realObj;
      
      Claim(inAOA(realObj), "Where is the object?");
      Claim(AOAISPERSISTENT(realObj), 
	    "Reference from persistent to non persistent object");
      
      inx = getPUID((void *)(realObj -> GCAttr));
      objectLookup(inx,
		   &GCAttr,
		   &store,
		   &offset,
		   &theObj);
      
      if (GCAttr == POTENTIALLYDEAD) {
	/* The referred object will be removed so we need to unswizzle
	   the reference to it. */
	if ((newEntryInx = indexLookupRT(store, offset + distanceToPart)) == -1) {
	  /* A new entry is created */
	  newEntryInx = insertReference(ENTRYALIVE,
					store,
					offset + distanceToPart);
	}
	*theCell = newPUID(newEntryInx);
	referenceAlive((void *)*theCell);
	newAOAclient(newEntryInx, theCell);
	INFO_PERSISTENCE(PtoD++);
      } else {
	Claim(GCAttr == ENTRYALIVE, "What is GC mark ?");
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
     fprintf(output, "]\n"));
  */

  printObjectStoreStatistics();
  printCrossStoreStatistics();
  printProxyStatistics();
}

/* */

void getKeyForObject(ObjectKey *ok, Object *theObj)
{
  u_long inx;
  char GCAttr;
  BlockID store;
  u_long offset;
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

void keyToObject(ObjectKey *ok, Object **theCell)
{
  *theCell = lookUpReferenceEntry(ok -> store, ok -> offset);
}

#endif /* PERSIST */
