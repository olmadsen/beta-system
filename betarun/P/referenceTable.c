#include "referenceTable.h"
#include "PException.h"
#include "objectTable.h"
#include "sequenceTable.h"
#include "trie.h"
#include "proto.h"
#include "transitObjectTable.h"
#include "misc.h"

#ifdef PERSIST

/* LOCAL TYPES */

typedef struct RTEntry {          /* Reference Table Entry */
  unsigned short GCAttr;                    /* The GC state of this entry. */
  unsigned long store;            /* The store in which this object is saved */
  unsigned long offset;           /* The byte offset in the store of the object */  
  Array *IOAclients, *AOAclients; /* List of cells referring this reference */
  Object *objInTransit;           /* See comment LLL in 'unswizzle.c' */
} RTEntry;

/* LOCAL DEFINITIONS */
#define INITIALTABLELENGTH 128 /* Initial size of the ReferenceTable */

/* LOCAL MACROS */

/* LOCAL VARIABLES */
static sequenceTable *currentTable = NULL;
static Trie *loadedObjectsST;
static RTEntry *entryBuffer = NULL;

/* LOCAL FUNCTION DECLARATIONS */
static void insertStoreOffsetRT(unsigned long store, unsigned long offset, unsigned long inx);

static Array *newArray(void);
static void Arealloc(Array *array);
static void Aappend(Array *array, unsigned long theCell);

/* FUNCTIONS */
static Array *newArray(void)
{
  return (Array *)calloc(1, sizeof(struct Array));
}

static void Arealloc(Array *array)
{
  unsigned long *new;
  unsigned short newMax;
  
  newMax = 2*array -> max + 1;
  new = (unsigned long *)malloc(sizeof(unsigned long)*newMax);
  if (array -> theCells) {
    memcpy(new, array -> theCells, array -> max * sizeof(unsigned long));
    free(array -> theCells);
    array -> theCells = 0;
  }
  array -> theCells = new;
  array -> max = newMax;
}

static void Aappend(Array *array, unsigned long theCell)
{
  if (array -> top < array -> max) {
    array -> theCells[array -> top] = theCell;
    array -> top = array -> top + 1;
  } else {
    Arealloc(array);
    Aappend(array, theCell);
  }
}

static int isFree(void *entry)
{
  Claim(entry != NULL, "isFree: entry is NULL");
  return (((RTEntry *)entry) -> GCAttr == ENTRYDEAD);
}

static void Free(void *entry)
{
  RTEntry *elm;
  
  Claim(entry != NULL, "Free: entry is NULL");
  
  elm = (RTEntry *)entry;

  if (elm -> IOAclients) {
    if (elm -> IOAclients -> theCells) {
      free(elm -> IOAclients -> theCells);
      elm -> IOAclients -> theCells = 0;
    }
    free(elm -> IOAclients);
    elm -> IOAclients = 0;
  }

  if (elm -> AOAclients) {
    if (elm -> AOAclients -> theCells) {
      free(elm -> AOAclients -> theCells);
      elm -> AOAclients -> theCells = 0;
    }
    free(elm -> AOAclients);
    elm -> AOAclients = 0;
  }
}

void initReferenceTable(void)
{
  currentTable = STInit(INITIALTABLELENGTH, isFree, Free, sizeof(RTEntry));
#ifdef UNIX
  initProxyTrapHandler();
#endif

  /* Allocate indirection table */
  PITAlloc();

  loadedObjectsST = TInit();
  initProtoHandling();
  
  if (entryBuffer == NULL) {
    entryBuffer = (RTEntry *)malloc(sizeof(RTEntry));
  }
}

void setObjInTransit(unsigned long inx, Object *theObj)
{
  RTEntry *entry;

  Claim(!inIOA(theObj), "setObjInTransit: Where is theObj?");
  
  entry = STLookup(currentTable, inx);

#ifdef RTDEBUG
  if (entry -> objInTransit) {
    Claim(entry -> objInTransit == theObj, "setObjInTransit: Entry taken");
  }
#endif /* RTDEBUG */
  
  entry -> objInTransit = theObj;
}

Object *getObjInTransit(unsigned long inx)
{
  RTEntry *entry;
  
  entry = STLookup(currentTable, inx);
  return entry -> objInTransit;
}

void newIOAclient(unsigned long inx, Object **theCell)
{
  RTEntry *entry;
  
  Claim(inToSpace(theCell), "Where is the client");
  
  entry = STLookup(currentTable, inx);
  
  Claim(entry -> GCAttr == ENTRYALIVE, "What is GCAttr");

  if (entry -> IOAclients == NULL) {
    entry -> IOAclients = newArray();
  }
  
  Aappend(entry -> IOAclients, (unsigned long)theCell);
}

void newAOAclient(unsigned long inx, Object **theCell)
{
  RTEntry *entry;
  
  Claim(inAOA(theCell), "Where is the client");
  
  entry = STLookup(currentTable, inx);
  
  Claim(entry -> GCAttr == ENTRYALIVE, "What is GCAttr");
  
  if (entry -> AOAclients == NULL) {
    entry -> AOAclients = newArray();
  }
  Aappend(entry -> AOAclients, (unsigned long)theCell);
}

void clearAOAclients(void)
{
  unsigned long maxIndex, inx;
  RTEntry *entry;

  maxIndex = STSize(currentTable);
  
  for (inx = 0; inx < maxIndex; inx++) {
    entry = STLookup(currentTable, inx);
    if (entry -> AOAclients) {
      if (entry -> AOAclients -> theCells) {
	free(entry -> AOAclients -> theCells);
	entry -> AOAclients -> theCells = NULL;
      }
      free(entry -> AOAclients);
      entry -> AOAclients = NULL;
    }
  }
}

void clearIOAclients(void)
{
  unsigned long maxIndex, inx;
  RTEntry *entry;

  maxIndex = STSize(currentTable);
  
  for (inx = 0; inx < maxIndex; inx++) {
    entry = STLookup(currentTable, inx);
    if (entry -> IOAclients) {
      if (entry -> IOAclients -> theCells) {
	free(entry -> IOAclients -> theCells);
	entry -> IOAclients -> theCells = NULL;
      } 
      free(entry -> IOAclients);
      entry -> IOAclients = NULL;
    }
  }
}

unsigned long insertReference(unsigned short GCAttr,
			      unsigned long store,
			      unsigned long offset)
{
  unsigned long inx;
  
  entryBuffer -> GCAttr = GCAttr;
  entryBuffer -> store = store;
  entryBuffer -> offset = offset;
  entryBuffer -> IOAclients = newArray();
  entryBuffer -> AOAclients = newArray();
  entryBuffer -> objInTransit = NULL;

  inx = STInsert(&currentTable, entryBuffer);
  
  /* Insert (store, offset) in loadedObjectsST */
  insertStoreOffsetRT(store, offset, inx + 1);
  
  return inx;
}

static void insertStoreOffsetRT(unsigned long store, unsigned long offset, unsigned long inx)
{
    insertStoreOffset(store, offset, inx, &loadedObjectsST);
}

/* Looks up GCAttr, store and offset based on index into table */
void referenceLookup(unsigned long inx,
		     unsigned short *GCAttr,
		     unsigned long *store,
		     unsigned long *offset,
		     Array **IOAclients,
		     Array **AOAclients)
{
  RTEntry *entry;
  
  entry = STLookup(currentTable, inx);
  
  *GCAttr = entry -> GCAttr;
  *store = entry -> store;
  *offset = entry -> offset;
  *IOAclients = entry -> IOAclients;
  *AOAclients = entry -> AOAclients;
}

/* Returns inx of entry containing (??, store, object). Returns -1 if
   not found. */
unsigned long indexLookupRT(unsigned long store, unsigned long offset)
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

/* Marks all entries as potentially dead. */
void RTStartGC(void)
{
  unsigned long inx, maxIndex;
  RTEntry *entry;
  
  if (currentTable == NULL) {
    initReferenceTable();
  }
  
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

void referenceAlive(void *ip)
{
  RTEntry *entry;
  unsigned long inx;
  
  inx = getPUID(ip);
  entry = STLookup(currentTable, inx);
  
  Claim(((entry -> GCAttr == ENTRYALIVE) || (entry -> GCAttr == POTENTIALLYDEAD)),
	"What is GCAttr ?");
  
  entry -> GCAttr = ENTRYALIVE;
}

static void freeLoadedObjectsOF(unsigned long contents)
{
  TIFree((Trie *)contents, NULL);
}

void RTEndGC(void)
{
  unsigned long inx, maxIndex;
  RTEntry *entry;
  sequenceTable *newTable = NULL;
  
  newTable = STInit(INITIALTABLELENGTH, isFree, Free, sizeof(RTEntry));
  
  /* Free the current 'loadedObjectsST' */
  TIFree(loadedObjectsST, freeLoadedObjectsOF);
  loadedObjectsST = NULL;
  loadedObjectsST = TInit();
  
  maxIndex = STSize(currentTable);
  
  for (inx = 0; inx < maxIndex; inx++) {
    entry = STLookup(currentTable, inx);
    if (entry -> GCAttr == POTENTIALLYDEAD) {
      entry -> offset = 0;
      entry -> store = 0;
      
    } else if (entry -> GCAttr == ENTRYALIVE) {
      unsigned long newInx;

      entryBuffer -> GCAttr = ENTRYALIVE;
      entryBuffer -> store = entry -> store;
      entryBuffer -> offset = entry -> offset;
      entryBuffer -> IOAclients = entry -> IOAclients;
      entryBuffer -> AOAclients = entry -> AOAclients;
      entryBuffer -> objInTransit = NULL;
      
      entry -> IOAclients = NULL;
      entry -> AOAclients = NULL;
      
      newInx = STInsert(&newTable, entryBuffer);
      
      redirectCells(entryBuffer -> IOAclients, 
		    (Object *)newPUID(inx), 
		    (Object *)newPUID(newInx));
      
      redirectCells(entryBuffer -> AOAclients, 
		    (Object *)newPUID(inx), 
		    (Object *)newPUID(newInx));
      
      
      insertStoreOffsetRT(entryBuffer -> store, entryBuffer -> offset, newInx + 1);
    } else {
      Claim((entry -> GCAttr == ENTRYDEAD), "What is GCAttr ?");
    }
  }
  
  STFree(&currentTable);
  currentTable = newTable;
  
}

#endif /* PERSIST */

#ifdef RUN
void CheckForNewAOAclient(Object **theCell)
{
#ifdef PERSIST
  newAOAclient(getPUID((void *)*theCell), theCell);
#endif /* PERSIST */
}
#endif /* RUN */

