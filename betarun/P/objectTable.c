#include "objectTable.h"
#include "beta.h"
#include "PException.h"
#include "misc.h"
#include "crossStoreTable.h"
#include "PExport.h"
#include "referenceTable.h"
#include "objectSet.h"

void objt_dummy() {
#ifdef sparc
  USE();
#endif /* sparc */
}

#ifdef PERSIST

/* LOCAL TYPES */
typedef struct OTEntry { /* Object Table Entry */
  char GCAttr;           /* The GC state of this entry. */
  StoreID store;         /* The store in which this object is saved */
  u_long offset;         /* The byte offset in the store of the object */  
  Object *theObj;        /* The object in memory */       
} OTEntry;

typedef struct ObjectTable {
  u_long maxIndex;        /* number of indices allocated for this table */
  u_long nextFree;        /* Index of the next free entry */
  OTEntry body[1];
} ObjectTable;

/* LOCAL DEFINITIONS */
#define INITIALTABLELENGTH 128 /* Initial size of the objectTable */

/* LOCAL MACROS */
#define TABLESIZE(length) (sizeof(struct ObjectTable) + sizeof(struct OTEntry) * ((length) - 1))

/* LOCAL VARIABLES */
static ObjectTable *currentTable = NULL;

/* LOCAL FUNCTION DECLARATIONS */
static void OTRealloc(void);
   
/* FUNCTIONS */
void initObjectTable(void)
{
  u_long newSize;
  
  newSize = TABLESIZE(INITIALTABLELENGTH);
  
  currentTable = (ObjectTable *)calloc(TABLESIZE(INITIALTABLELENGTH), 1);
  currentTable -> maxIndex = INITIALTABLELENGTH;
  currentTable -> nextFree = 0;
}

static void OTRealloc(void)
{
  u_long newLength;
  ObjectTable *newTable;
  
  Claim(currentTable != NULL, "OTRealloc: currentTable is NULL");
  Claim(currentTable -> maxIndex > 0, "OTRealloc: length must be non zero before realloc");
  
  newLength = currentTable -> maxIndex * 2;
  newTable = (ObjectTable *)calloc(TABLESIZE(newLength), 1);
  memcpy(newTable, currentTable, TABLESIZE(currentTable -> maxIndex));
  newTable -> maxIndex = newLength;
  newTable -> nextFree = currentTable -> nextFree;
  free(currentTable);
  currentTable = newTable;
}

u_long OTSize(void)
{
  return currentTable -> maxIndex;
}

u_long insertObject(char GCAttr,
		    StoreID store,
		    u_long offset,
		    Object *theObj)
{
  u_long inx;
  static u_long once = 0;
  
  Claim(currentTable != NULL, "insertObject: currentTable is NULL");
  
  while ((currentTable -> nextFree < currentTable -> maxIndex) &&
	 (currentTable -> body[currentTable -> nextFree].GCAttr != ENTRYDEAD)) {
    currentTable -> nextFree = currentTable -> nextFree + 1;
  }
  
  inx = currentTable -> nextFree;
  if (inx < currentTable -> maxIndex) {
    OTEntry *body;
    body = &(currentTable -> body[0]);
    body[inx].GCAttr = GCAttr;
    body[inx].store = store;
    body[inx].offset = offset;
    body[inx].theObj = theObj;
    return inx;
  } else {
    if (once) {
      OTRealloc();
      once = 0;
      return insertObject(GCAttr, store, offset, theObj);
    } else {
      once = 1;
      currentTable -> nextFree = 0;
      return insertObject(GCAttr, store, offset, theObj);
    }
  }
}

/* Looks up GCAttr, store, offset and object based on index into table */
void objectLookup(u_long inx,
		  char *GCAttr,
		  StoreID *store,
		  u_long *offset,
		  Object **theObj)
{
  OTEntry *body;
  
  Claim(inx < currentTable -> maxIndex, "objectLookup: Illegal inx");
  
  body = &(currentTable -> body[0]);
  
  *GCAttr = body[inx].GCAttr;
  *store = body[inx].store;
  *offset = body[inx].offset;
  *theObj = body[inx].theObj;
}

/* Returns inx of entry containing (??, store, object, ??). Returns -1 if
   not found. */
u_long indexLookupOT(StoreID store, u_long offset)
{
  u_long inx;
  OTEntry *body;
  
  body = &(currentTable -> body[0]);
  for (inx = 0; inx < currentTable -> maxIndex; inx++) {
    if (body[inx].store == store) {
      if (body[inx].offset <= offset) {
	if ( offset < body[inx].offset + 4*ObjectSize(body[inx].theObj)) {
	  return inx;
	}
      }
    }
  }
  
  return -1;
}

/* Marks all entries as potentially dead. */
void OTStartGC(void)
{
  u_long inx;
  OTEntry *body;
  
  body = &(currentTable -> body[0]);
  for (inx = 0; inx < currentTable -> maxIndex; inx++) {
    if (body[inx].GCAttr == ENTRYALIVE) {
      body[inx].GCAttr = POTENTIALLYDEAD;
    } else {
      Claim(body[inx].GCAttr == ENTRYDEAD, "What is GCAttr ?");
    }
  }
}

void objectAlive(Object *theObj)
{
  OTEntry *body;
  u_long inx;
  
  inx = getPUID((void *)(theObj -> GCAttr));
  
  Claim(inx < currentTable -> maxIndex, "objectAlive: Illegal inx");
  
  body = &(currentTable -> body[0]);
  
  Claim(((body[inx].GCAttr == ENTRYALIVE) || (body[inx].GCAttr == POTENTIALLYDEAD)),
	"What is GCAttr ?");
  
  body[inx].GCAttr = ENTRYALIVE;
}

void OTEndGC(void)
{
  u_long inx;
  OTEntry *body;
  
  body = &(currentTable -> body[0]);
  for (inx = 0; inx < currentTable -> maxIndex; inx++) {
    if (body[inx].GCAttr == POTENTIALLYDEAD) {
      body[inx].theObj -> GCAttr = DEADOBJECT;
      
      body[inx].GCAttr = ENTRYDEAD;
      body[inx].store = 0;
      body[inx].offset = 0;
      body[inx].theObj = NULL;
      
      INFO_PERSISTENCE(numD++);
    } else if (body[inx].GCAttr == ENTRYALIVE) {
      INFO_PERSISTENCE(numP++);
    } else {
      Claim(body[inx].GCAttr == ENTRYDEAD, "What is GCAttr ?");
    }
  }
}

/* Miscellaneous functions */

void flushDelayedEntries(void)
{
  u_long count;
  u_long max;
  
  if (currentTable == NULL) {
    initObjectTable();
  }
  
  max = currentTable -> maxIndex;
  for (count=0; count<max; count++) {
    if (currentTable -> body[count].GCAttr == DELAYEDENTRYALIVE) {
      Object *theObj;
      theObj = currentTable -> body[count].theObj;
      currentTable -> body[count].GCAttr = ENTRYDEAD;
      currentTable -> body[count].theObj = NULL;
      newPersistentObject(theObj);
      INFO_PERSISTENCE(numDE++);
    }
  }  
}

/* Collects the transitive closure of the persistent objects */
void updatePersistentObjects(void)
{
  Object *root;
  u_long count;
  u_long max;
  
  /* All objects referred from persistent objects shall be made
     persistent as well */
  
  clearTail();
  
  Claim(currentTable != NULL, "updatePersistentObjects: CurrentTable is NULL");
  
  max = currentTable -> maxIndex;
  for (count=0; count<max; count++) {
    OTEntry *body;
    body = &(currentTable -> body[0]);
    if (body[count].GCAttr == ENTRYALIVE) {
      Claim(inAOA(body[count].theObj), "Where is theObj?");      
      Claim(AOAISPERSISTENT(body[count].theObj), "not persistent??");
      
      scanObject(body[count].theObj,
		 markReachableObjects,
		 TRUE);
      INFO_PERSISTENCE(numPB++);
    } else {
      Claim(body[count].GCAttr == ENTRYDEAD, "What is GCAttr ?");
    }
  }
  
  /* All new persistent objects have now been linked together. */
  if ((root = getHead())) {
    /* OSclear(); */
    scanList(root, handleNewPersistentObject);
    /* OSscan(handleNewPersistentObject); */
  } else {
    /* No new persistent objects */
    ;
  }
}

/* After GC all unused objects cuurently in memory should be
   checkpointed and removed */
void removeUnusedObjects()
{
  u_long count;
  u_long max;
  
  /* All objects in the ObjectTable that are marked as POTENTIALLYDEAD
     are no longer referred from this process and can be updated in
     the store and released. */
  
  /* All persistent objects marked as ENTRYALIVE are not removed, so
     references from alive persistent objects to POTENTIALLYDEAD (DEAD at
     this point) persistent objects must be unswizzled as well. 
  */
  
  /* If an object is alive and kept in memory we cannot move its
     origin, so we have to mark the origin alive as well. */
  
  Claim(currentTable != NULL, "updatePersistentObjects: CurrentTable is NULL");
  
  max = currentTable -> maxIndex;
  objectAction = markOriginsAlive;
  for (count=0; count<max; count++) {
    OTEntry *body;
    body = &(currentTable -> body[0]);
    if (body[count].GCAttr == ENTRYALIVE) {
      Claim(inAOA(body[count].theObj), "Where is theObj?");      
      Claim(AOAISPERSISTENT(body[count].theObj), "not persistent??");
      /* handle origin */
      scanObject(body[count].theObj,
		 NULL,
		 TRUE);
    }       
  }
  objectAction = NULL;
  
  /* Handle references from live to dead persistent objects */
  max = currentTable -> maxIndex;
  for (count=0; count<max; count++) {
    OTEntry *body;
    body = &(currentTable -> body[0]);
    if (body[count].GCAttr == ENTRYALIVE) {
      Claim(inAOA(body[count].theObj), "Where is theObj?");      
      Claim(AOAISPERSISTENT(body[count].theObj), "not persistent??");
      /* handle live entry */
      scanObject(body[count].theObj,
		 handlePersistentCell,
		 TRUE);
    }
  }
  
  /* Handles dead entries and exports dead objects */
  max = currentTable -> maxIndex;
  for (count=0; count<max; count++) {
    OTEntry *body;
    body = &(currentTable -> body[0]);
    if (body[count].GCAttr == POTENTIALLYDEAD) {
      Object *theObj;
      StoreID store;
      u_long offset;
      
      theObj = body[count].theObj;
      store = body[count].store;
      offset = body[count].offset;
      
      Claim(inAOA(theObj), "Where is theObj?");      
      Claim(AOAISPERSISTENT(theObj), "not persistent??");
      Claim(theObj == getRealObject(theObj), "Unexpected part object");
      
      setCurrentObjectStore(store);
      exportObject(theObj, store);
      
      if (setStoreObject(store, offset, theObj)) {
	/* Object has been updated */
	;
      } else {
	Claim(FALSE, "Could not update object");
      }
    }
  }
  
  /* mark dead objects dead and clean up tables */
  OTEndGC();
  RTEndGC();
  
  /* Save the cached values of the store */
  saveCurrentObjectStore();
  saveCurrentCrossStoreTable();
}

#endif /* PERSIST */
