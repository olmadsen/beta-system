#include "objectTable.h"
#include "beta.h"
#include "PException.h"
#include "misc.h"
#include "PExport.h"
#include "referenceTable.h"
#include "sequenceTable.h"
#include "trie.h"
#include "proto.h"
#include "transitObjectTable.h"
#include "PStoreServer.h"
#include "PStore.h"

void objt_dummy() {
#ifdef sparc
  USE();
#endif /* sparc */
}

#ifdef PERSIST
/* LOCAL TYPES */
typedef struct OTEntry {  /* Object Table Entry */
  unsigned short GCAttr;  /* The GC state of this entry. */
  unsigned short Flags;   /* Misc. flags for this entry. */
  unsigned long store;    /* The store in which this object is saved */
  unsigned long offset;   /* The byte offset in the store of the object */  
  Object *theObj;         /* The object in memory */       
} OTEntry;

/* LOCAL DEFINITIONS */
#define INITIALTABLELENGTH 128 /* Initial size of the objectTable */

/* LOCAL VARIABLES */
static sequenceTable *currentTable = NULL;
static Node *loadedObjectsST;

/* GLOBAL VARIABLES */

/* LOCAL FUNCTION DECLARATIONS */
static void updateObjectInStore(Object *theObj, unsigned long store, unsigned long offset);
static void freeLoadedObjectsOF(void *contents);

/* FUNCTIONS */
static int isFree(void *entry)
{
  Claim(entry != NULL, "isFree: entry is NULL");
  return (((OTEntry *)entry) -> GCAttr == ENTRYDEAD);
}

static void Free(void *entry)
{
  Claim(entry != NULL, "Free: entry is NULL");
  free((OTEntry *)entry);
}

void initObjectTable(void)
{
  currentTable = STInit(INITIALTABLELENGTH, isFree, Free, sizeof(OTEntry));
  loadedObjectsST = TInit();
  initTransitObjectTable();
}

unsigned long OTSize(void)
{
  return STSize(currentTable);
}

static unsigned long currentStore;
static unsigned long currentOffset;
static Object *theRealObj;
static unsigned long OTinx;

static void registerReverse(Object *theObj)
{
  unsigned long distanceToPart;
  distanceToPart = (unsigned long)theObj - (unsigned long)theRealObj;
  insertStoreOffsetOT(currentStore,
		      currentOffset + distanceToPart,
		      OTinx);
}

static void registerObjectAndParts(unsigned long store, unsigned long offset, Object *theObj, unsigned long inx)
{  
  OTinx = inx;
  currentStore = store;
  currentOffset = offset;
  theRealObj = theObj;
  
  scanObject(theObj,
	     NULL,
	     registerReverse,
	     TRUE);
}

unsigned long insertObject(unsigned short GCAttr,
			   unsigned short Flags,
			   unsigned long store,
			   unsigned long offset,
			   Object *theObj)
{
  OTEntry *newEntry;
  unsigned long inx;

  Claim(theObj == getRealObject(theObj), "Unexpected part object");
  
  newEntry = (OTEntry *)malloc(sizeof(OTEntry));
  newEntry -> GCAttr = GCAttr;
  newEntry -> Flags = Flags;
  newEntry -> store = store;
  newEntry -> offset = offset;
  newEntry -> theObj = theObj;
  
  inx = STInsert(&currentTable, newEntry);
  
  /* register the object and the part objects to enable reverse lookup */
  registerObjectAndParts(store, offset, theObj, inx + 1);
  
  return inx;
}

/* Looks up GCAttr, store, offset and object based on index into table */
void objectLookup(unsigned long inx,
		  unsigned short *GCAttr,
		  unsigned long *store,
		  unsigned long *offset,
		  Object **theObj)
{
  OTEntry *entry;
  
  if ((entry = STLookup(currentTable, inx))) {
    *GCAttr = entry -> GCAttr;
    *store = entry -> store;
    *offset = entry -> offset;
    *theObj = entry -> theObj;
  }   
}

/* Returns inx of entry containing (??, store, object, ??). Returns -1 if
   not found. */
unsigned long indexLookupOT(unsigned long store, unsigned long offset)
{
  Node *loadedObjectsOF;
  
  /* Check if store is member of 'loadedObjects' */
  if ((loadedObjectsOF = TILookup(store, loadedObjectsST))) {
    unsigned long inx;
    if ((inx = (unsigned long)TILookup(offset, loadedObjectsOF))) {
      return inx - 1;
    }
  }
  return -1;
}

void OTCheck(void (*checkAction)(Object *theObj, void *generic))
{
  unsigned long inx, maxIndex;
  OTEntry *entry;
  
  maxIndex = STSize(currentTable);
  
  for (inx = 0; inx < maxIndex; inx++) {
    entry = STLookup(currentTable, inx);
    if (entry -> GCAttr == POTENTIALLYDEAD) {
      checkAction(entry -> theObj, NULL);
    }
  }
}

/* Marks all entries as potentially dead. */
void OTStartGC(void)
{
  unsigned long inx, maxIndex;
  OTEntry *entry;
  
  maxIndex = STSize(currentTable);

  for (inx = 0; inx < maxIndex; inx++) {
    entry = STLookup(currentTable, inx);
    if (entry -> GCAttr == ENTRYALIVE) {
      entry -> GCAttr = POTENTIALLYDEAD;
    } else {
      Claim(entry -> GCAttr == ENTRYDEAD, "What is GCAttr ?");
    }
  }
}

void objectAlive(Object *theObj)
{
  OTEntry *entry;
  unsigned long inx;
  
  inx = getPUID((void *)(theObj -> GCAttr));
  entry = STLookup(currentTable, inx);
  
  Claim(((entry -> GCAttr == ENTRYALIVE) || (entry -> GCAttr == POTENTIALLYDEAD)),
	"What is GCAttr ?");
  
  entry -> GCAttr = ENTRYALIVE;
}

void insertStoreOffsetOT(unsigned long store, unsigned long offset, unsigned long inx)
{
  Node *loadedObjectsOF;
  
  /* Check if store is member */
  if ((loadedObjectsOF = TILookup(store, loadedObjectsST)) == NULL) {
    /* insert new table for store */
    loadedObjectsOF = TInit();
    TInsert(store, (void *)loadedObjectsOF, loadedObjectsST, store);
  }
  
  /* insert inx in loadedObjectsOF */
  TInsert(offset, (void *)inx, loadedObjectsOF, offset);
}

static void freeLoadedObjectsOF(void *contents)
{
  TIFree((Node *)contents, NULL);
}

void OTEndGC(void)
{
  unsigned long inx, maxIndex;
  OTEntry *entry;
  sequenceTable *newTable = NULL;
  
  newTable = STInit(INITIALTABLELENGTH, isFree, Free, sizeof(OTEntry));
  
  /* Free the current 'loadedObjectsST' */
  TIFree(loadedObjectsST, freeLoadedObjectsOF);
  loadedObjectsST = NULL;
  loadedObjectsST = TInit();
  
  maxIndex = STSize(currentTable);
  for (inx = 0; inx < maxIndex; inx++) {
    entry = STLookup(currentTable, inx);
    if (entry -> GCAttr == POTENTIALLYDEAD) {
      entry -> theObj -> GCAttr = DEADOBJECT;
      entry -> theObj = NULL;
      
    } else if (entry -> GCAttr == ENTRYALIVE) {
      if (!closingGC) {
	unsigned long newInx;
	OTEntry *newEntry;
	
	newEntry = (OTEntry *)malloc(sizeof(OTEntry));
	memcpy(newEntry, entry, sizeof(OTEntry));
	
	newInx = STInsert(&newTable, newEntry);
	entry -> theObj -> GCAttr = (long)newPUID(newInx);
	registerObjectAndParts(entry -> store, entry -> offset, entry -> theObj, newInx + 1);
      }
    } else {
      Claim(entry -> theObj == NULL, "What is the object ??");
    }
  }
  STFree(&currentTable);
  currentTable = newTable;
}

/* Miscellaneous functions */

void flushDelayedEntries(void)
{
  unsigned long count;
  unsigned long maxIndex;
  OTEntry *entry;
  
  if (currentTable == NULL) {
    initObjectTable();
  }
  maxIndex = STSize(currentTable);
  for (count=0; count<maxIndex; count++) {
    entry = STLookup(currentTable, count);
    if (entry -> GCAttr == DELAYEDENTRYALIVE) {
      Object *theObj;
      theObj = entry -> theObj;
      entry -> GCAttr = ENTRYDEAD;
      entry -> theObj = NULL;
      newPersistentObject(theObj);
    }
  }  
}

/* Collects the transitive closure of the persistent objects */
void updatePersistentObjects(void)
{
  Object *root;
  unsigned long count;
  unsigned long maxIndex;
  OTEntry *entry;
  
  /* All objects referred from persistent objects shall be made
     persistent as well */
  clearTail();
  maxIndex = STSize(currentTable);
  for (count=0; count<maxIndex; count++) {
    entry = STLookup(currentTable, count);
    if (entry -> GCAttr == ENTRYALIVE) {
      Claim(inAOA(entry -> theObj), "Where is theObj?");      
      Claim(AOAISPERSISTENT(entry -> theObj), "not persistent??");
      
      scanObject(entry -> theObj,
		 markReachableObjects,
		 NULL,
		 TRUE);
    } else {
      Claim(entry -> GCAttr == ENTRYDEAD, "What is GCAttr ?");
    }
  }

  /* All new persistent objects have now been linked together. */
  if ((root = getHead())) {
    scanList(root, handleNewPersistentObject);
    repeatIOAGc = 1;
  } else {
    /* No new persistent objects */
    repeatIOAGc = 0;
  }
}

static void updateObjectInStore(Object *theObj, unsigned long store, unsigned long offset)
{
  long size;
  int docopy = 0;
  OTEntry *entry;  
  Object *objcopy;

  Claim(inAOA(theObj), "Where is theObj?");      
  Claim(AOAISPERSISTENT(theObj), "not persistent??");
  Claim(theObj == getRealObject(theObj), "Unexpected part object");
  
  entry = STLookup(currentTable, getPUID((void*)(theObj->GCAttr)));

  /* The object is exported. 'exportObject' does not export the proto
     types. */
  exportObject(theObj, store);
  
  if ((!entry->Flags & FLAG_INSTORE)) {
    docopy = TRUE;
  } else {
    size = 4*ObjectSize(theObj);
    objcopy = (Object*)((char*)theObj+size);
    objcopy->GCAttr = theObj->GCAttr;
    if (memcmp(theObj, objcopy, size)) {
      docopy = TRUE;
    }
    objcopy->GCAttr = DEADOBJECT;
  }
  
  if (docopy) {
    setCurrentPStore(store);
    if (setStoreObject(store, offset, theObj)) {
      /* Object has been updated */
      INFO_PERSISTENCE(objectsExported++);
    } else {
      Claim(FALSE, "Could not update object");
    }
  }
}

/* After GC all unused objects currently in memory should be
   checkpointed and removed */
void removeUnusedObjects()
{
  unsigned long count;
  unsigned long maxIndex;
  OTEntry *entry;  
  /* All objects in the ObjectTable that are marked as POTENTIALLYDEAD
     are no longer referred from this process and can be updated in
     the store and released. */
  
  /* All persistent objects marked as ENTRYALIVE are not removed, so
     references from alive persistent objects to POTENTIALLYDEAD (DEAD at
     this point) persistent objects must be unswizzled as well. 
  */
  
  /* If an object is alive and kept in memory we cannot move its
     origin or any references from within the object to offline
     allocated objects, so we have to mark the origin alive as well as
     offline allocated objects referred from within the object. */
  
  maxIndex = STSize(currentTable);
  for (count=0; count<maxIndex; count++) {
    entry = STLookup(currentTable, count);
    if (entry -> GCAttr == ENTRYALIVE) {
      Claim(inAOA(entry ->theObj), "Where is theObj?");      
      Claim(AOAISPERSISTENT(entry ->theObj), "not persistent??");
      /* handle origin and offline allocated objects */
      scanObject(entry ->theObj,
		 markOfflineAndOriginObjectsAlive,
		 NULL,
		 TRUE);
    }
  }
  /* Handle references from live to dead persistent objects */
  maxIndex = STSize(currentTable);
  for (count=0; count<maxIndex; count++) {
    entry = STLookup(currentTable, count);
    if (entry ->GCAttr == ENTRYALIVE) {
      Claim(inAOA(entry ->theObj), "Where is theObj?");      
      Claim(AOAISPERSISTENT(entry ->theObj), "not persistent??");
      /* handle live entry */
      scanObject(entry ->theObj,
		 handlePersistentCell,
		 NULL,
		 TRUE);
    }
  }
  
  /* Handles dead entries and exports dead objects */
  maxIndex = STSize(currentTable);
  for (count=0; count<maxIndex; count++) {
    entry = STLookup(currentTable, count);
    if (entry -> GCAttr == POTENTIALLYDEAD) {
      updateObjectInStore(entry ->theObj,
			  entry ->store,
			  entry ->offset);
    } else if (entry ->GCAttr == ENTRYALIVE) {
      if (closingGC) {
	Object *tmp;
	
	tmp = (Object *)malloc(sizeof(char) * 4*ObjectSize(entry ->theObj));
	memcpy(tmp, entry ->theObj, 4*ObjectSize(entry ->theObj));
	updateObjectInStore(entry ->theObj,
			    entry ->store,
			    entry ->offset);
	memcpy(entry ->theObj, tmp, 4*ObjectSize(entry ->theObj));
	
      }
    }
  }
  
  /* mark dead objects dead and clean up tables */
  OTEndGC();
  RTEndGC();
  
  if (closingGC) {
    closeExt();
    closingGC = FALSE;
  }
}

#endif /* PERSIST */
