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
#include "crossStoreReferences.h"
#include "specialObjectsTable.h"

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
#define INITIALBUFFERSIZE 1024
#define SIZEOFPROTOANDGCATTRIBUTE 8

/* LOCAL VARIABLES */
static sequenceTable *currentTable = NULL;
static Trie *loadedObjectsST;
static char *temporaryObjectBuffer = NULL;
static unsigned long size;
static OTEntry *entryBuffer = NULL;

/* GLOBAL VARIABLES */

/* LOCAL FUNCTION DECLARATIONS */
static void updateObjectInStore(Object *theObj,
				unsigned long objSize,
				unsigned long store, 
				unsigned long offset,
				unsigned short Flags);
static void freeLoadedObjectsOF(unsigned long contents);

/* FUNCTIONS */
static int isFree(void *entry)
{
  Claim(entry != NULL, "isFree: entry is NULL");
  return (((OTEntry *)entry) -> GCAttr == ENTRYDEAD);
}

void initObjectTable(void)
{
  currentTable = STInit(INITIALTABLELENGTH, isFree, NULL, sizeof(OTEntry));
  loadedObjectsST = TInit();
  initTransitObjectTable();
  
  temporaryObjectBuffer = (char *)malloc(INITIALBUFFERSIZE);
  if (entryBuffer == NULL) {
    entryBuffer = (OTEntry *)malloc(sizeof(OTEntry));
  }
  size = INITIALBUFFERSIZE;
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
  unsigned long inx;

  Claim(theObj == getRealObject(theObj), "Unexpected part object");
  
  entryBuffer -> GCAttr = GCAttr;
  entryBuffer -> Flags = Flags;
  entryBuffer -> store = store;
  entryBuffer -> offset = offset;
  entryBuffer -> theObj = theObj;
  
  inx = STInsert(&currentTable, entryBuffer);
  
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
  Trie *loadedObjectsOF;
  
  /* Check if store is member of 'loadedObjects' */
  if ((loadedObjectsOF = (Trie *)TILookup(store, loadedObjectsST))) {
    unsigned long inx;
    if ((inx = TILookup(offset, loadedObjectsOF))) {
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
      Claim(((entry -> GCAttr == DELAYEDENTRYALIVE) || (entry -> GCAttr == ENTRYDEAD)) , 
	    "What is GCAttr ?");
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
  insertStoreOffset(store, offset, inx, &loadedObjectsST);
}

static void freeLoadedObjectsOF(unsigned long contents)
{
  TIFree((Trie *)contents, NULL);
}

void OTEndGC(void)
{
  unsigned long inx, maxIndex;
  OTEntry *entry;
  sequenceTable *newTable = NULL;
  Object *objcopy;
  unsigned long objSize;
  
  newTable = STInit(INITIALTABLELENGTH, isFree, NULL, sizeof(OTEntry));
  
  /* Free the current 'loadedObjectsST' */
  TIFree(loadedObjectsST, freeLoadedObjectsOF);
  loadedObjectsST = NULL;
  loadedObjectsST = TInit();
  
  maxIndex = STSize(currentTable);
  for (inx = 0; inx < maxIndex; inx++) {
    entry = STLookup(currentTable, inx);
    if (entry -> GCAttr == POTENTIALLYDEAD) {
      entry -> theObj -> GCAttr = DEADOBJECT;
      
      if (entry -> Flags & FLAG_INSTORE) {
	/* The object copy should be freeed as well */
	objSize = 4*ObjectSize(entry -> theObj);
	objcopy = (Object *)((char *)(entry -> theObj) + objSize);
	Claim(ObjectSize(entry -> theObj) == ObjectSize(objcopy), "Copy mismatch");
	objcopy -> GCAttr = DEADOBJECT;
	entry -> theObj = NULL;
      } else {
	;
      }
    } else if (entry -> GCAttr == ENTRYALIVE) {
      unsigned long newInx;

      memcpy(entryBuffer, entry, sizeof(OTEntry));
      
      newInx = STInsert(&newTable, entryBuffer);
      entry -> theObj -> GCAttr = (long)newPUID(newInx);
      registerObjectAndParts(entry -> store, entry -> offset, entry -> theObj, newInx + 1);

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

      Claim(inIOA(theObj), "flushDelayedEntries: Delayed object not in from space?");
      Claim(inAOA(theObj -> GCAttr), "flushDelayedEntries: Delayed object not moved to AOA ?");
      
      entry -> GCAttr = ENTRYDEAD;
      entry -> theObj = NULL;
      newPersistentObject(entry -> store, (Object *)(theObj -> GCAttr));
    }
  }  
}

extern unsigned long currentStoreID; /* defined in misc.c */

/* Collects the transitive closure of the persistent objects */
void updatePersistentObjects(void)
{
  unsigned long count;
  unsigned long maxIndex;
  OTEntry *entry;
  
  /* All objects referred from persistent objects shall be made
     persistent as well */
  clearTail();
  maxIndex = STSize(currentTable);
  for (count=0; count<maxIndex; count++) {
    entry = STLookup(currentTable, count);
    if (entry -> GCAttr == ENTRYALIVE 
	|| entry -> GCAttr == DELAYEDENTRYALIVE) {
      Claim(entry -> theObj == getRealObject(entry -> theObj), "Prt object in object table?");
#ifdef RTDEBUG
      if (!inToSpace(entry -> theObj)) {
	Claim(inAOA(entry -> theObj), "Where is theObj?");      
	Claim(AOAISPERSISTENT(entry -> theObj), "not persistent??");
      } else {
	Claim(entry -> theObj -> GCAttr == IOAPersist, "Object in IOA with unexpected GCAttr");
      }
#endif /* RTDEBUG */
      
      /* All new persistent objects reachable from this object will be
         assigned the same store as the referring object. */
      
      currentStoreID = entry -> store;
      
      scanObject(entry -> theObj,
		 markReachableObjects,
		 NULL,
		 TRUE);
    } else {
      Claim(entry -> GCAttr == ENTRYDEAD, "What is GCAttr ?");
    }
  }
}

static void updateObjectInStore(Object *theObj,
				unsigned long objSize,
				unsigned long store, 
				unsigned long offset,
				unsigned short Flags)
{
  int docopy = 0;
  Object *objcopy;
  
  Claim(inAOA(theObj), "Where is theObj?");      
  Claim(AOAISPERSISTENT(theObj), "not persistent??");
  Claim(theObj == getRealObject(theObj), "Unexpected part object");
  
  /* The object is exported. 'exportObject' does not export the proto
     types. */

  /* We need to set the current store since 'exportObject' might
     create new proxy objects in the store holding the exported object.
  */
  
  if (storeIsOpen(store)) {
    setCurrentPStore(store);
    exportObject(theObj, store);
    
    if ((!Flags & FLAG_INSTORE)) {
      docopy = TRUE;
    } else {
      objcopy = (Object*)((char*)theObj+objSize);
      /* We compare the objects disregarding the protypes and
	 GCattribute values */
      if (memcmp((char *)(theObj) + SIZEOFPROTOANDGCATTRIBUTE, 
	       (char *)(objcopy) + SIZEOFPROTOANDGCATTRIBUTE, 
		 objSize - SIZEOFPROTOANDGCATTRIBUTE)) {
	docopy = TRUE;
      }
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
  } else {
    /* The store is no longer open. Sometimes it is necessary to keep
       an object in memory eventhough the store is closed. This is
       because the object might be the origin of some other object
       which are retained in memory. */
    ;
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
			  4*ObjectSize(entry ->theObj),
			  entry ->store,
			  entry ->offset,
			  entry -> Flags);
      /* This object will be removed */
    } else if (entry ->GCAttr == ENTRYALIVE) {
      unsigned long objSize;
      /* The objects are kept in memory but updated on the store
         anyhow */
      
      objSize = 4*ObjectSize(entry ->theObj);
      
      /* The function 'updateObjectInStore' will change the first copy
	 of the object (remember that each object loaded is followed
	 by a copy of itself as it looked at load time), but since we
	 are keeping this object in memory we have to chage it
	 back. This is why the object is copied and restored from the
	 copy. Remember that benchmark programs indicate that only a
	 handfull of objects are kept in memory after each AOA-GC. */
      
      while (objSize > size) {
	free(temporaryObjectBuffer);
	temporaryObjectBuffer = (char *)malloc(size * 2);
	size = size * 2;
      }
      
      memcpy(temporaryObjectBuffer, entry ->theObj, objSize);
      updateObjectInStore(entry ->theObj,
			  objSize,
			  entry ->store,
			  entry ->offset,
			  entry ->Flags);
      memcpy(entry ->theObj, temporaryObjectBuffer, objSize);
    }
  }
  
  /* mark dead objects dead and clean up tables */
  OTEndGC();
  RTEndGC();
  SOEndGC();
  saveCurrentStore();
}

#endif /* PERSIST */
