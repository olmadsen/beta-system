#include "referenceTable.h"
#include "PException.h"
#include "objectTable.h"
#include "sequenceTable.h"
#include "trie.h"
#include "proto.h"
#include "transitObjectTable.h"

void reft_dummy() {
#ifdef sparc
  USE();
#endif /* sparc */
}

#ifdef PERSIST

/* LOCAL TYPES */

typedef struct RTEntry {          /* Reference Table Entry */
  char GCAttr;                    /* The GC state of this entry. */
  BlockID store;                  /* The store in which this object is saved */
  u_long offset;                  /* The byte offset in the store of the object */  
  Array *IOAclients, *AOAclients; /* List of cells referring this reference */
} RTEntry;

/* LOCAL DEFINITIONS */
#define INITIALTABLELENGTH 128 /* Initial size of the ReferenceTable */

/* LOCAL MACROS */

/* LOCAL VARIABLES */
static sequenceTable *currentTable = NULL;
static Node *loadedObjectsST;

/* LOCAL FUNCTION DECLARATIONS */
static void insertStoreOffsetRT(BlockID store, u_long offset, u_long inx);

static Array *newArray(void);
static void Arealloc(Array *array);
static void Aappend(Array *array, u_long theCell);

/* FUNCTIONS */
static Array *newArray(void)
{
  return (Array *)calloc(1, sizeof(struct Array));
}

static void Arealloc(Array *array)
{
  u_long *new;
  u_short newMax;
  
  newMax = 2*array -> max + 1;
  new = (u_long *)malloc(sizeof(u_long)*newMax);
  if (array -> theCells) {
    memcpy(new, array -> theCells, array -> max * sizeof(u_long));
    free(array -> theCells);
    array -> theCells = 0;
  }
  array -> theCells = new;
  array -> max = newMax;
}

static void Aappend(Array *array, u_long theCell)
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

  free(elm);
}

void initReferenceTable(void)
{
  currentTable = STInit(INITIALTABLELENGTH, isFree, Free, sizeof(RTEntry));
  initProxyTrapHandler();
  loadedObjectsST = TInit();
  initProtoHandling();
}

void newIOAclient(u_long inx, Object **theCell)
{
  RTEntry *entry;
  
  Claim(inToSpace(theCell), "Where is the client");
  
  entry = STLookup(currentTable, inx);
  
  Claim(entry -> GCAttr == ENTRYALIVE, "What is GCAttr");

  if (entry -> IOAclients == NULL) {
    entry -> IOAclients = newArray();
  }
  
  Aappend(entry -> IOAclients, (u_long)theCell);
}

void newAOAclient(u_long inx, Object **theCell)
{
  RTEntry *entry;
  
  Claim(inAOA(theCell), "Where is the client");
  
  entry = STLookup(currentTable, inx);
  
  Claim(entry -> GCAttr == ENTRYALIVE, "What is GCAttr");
  
  if (entry -> AOAclients == NULL) {
    entry -> AOAclients = newArray();
  }
  Aappend(entry -> AOAclients, (u_long)theCell);
}

void inxToObject(u_long inx)
{
  RTEntry *entry;
  
  entry = STLookup(currentTable, inx);
}

void clearAOAclients(void)
{
  u_long maxIndex, inx;
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
  u_long maxIndex, inx;
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

u_long insertReference(char GCAttr,
		       BlockID store,
		       u_long offset)
{
  RTEntry *newEntry;
  u_long inx;
  
  newEntry = (RTEntry *)malloc(sizeof(RTEntry));
  newEntry -> GCAttr = GCAttr;
  newEntry -> store = store;
  newEntry -> offset = offset;
  newEntry -> IOAclients = newArray();
  newEntry -> AOAclients = newArray();
  
  inx = STInsert(&currentTable, newEntry);
  
  /* Insert (store, offset) in loadedObjectsST */
  insertStoreOffsetRT(store, offset, inx + 1);
  
  return inx;
}

static void insertStoreOffsetRT(BlockID store, u_long offset, u_long inx)
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

/* Looks up GCAttr, store and offset based on index into table */
void referenceLookup(u_long inx,
		     char *GCAttr,
		     BlockID *store,
		     u_long *offset,
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
u_long indexLookupRT(BlockID store, u_long offset)
{
  Node *loadedObjectsOF;
  
  /* Check if store is member of 'loadedObjects' */
  if ((loadedObjectsOF = TILookup(store, loadedObjectsST))) {
    u_long inx;
    if ((inx = (u_long)TILookup(offset, loadedObjectsOF))) {
      return inx - 1;
    }
  }
  return -1;
}

/* Marks all entries as potentially dead. */
void RTStartGC(void)
{
  u_long inx, maxIndex;
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
  u_long inx;
  
  inx = getPUID(ip);
  entry = STLookup(currentTable, inx);
  
  Claim(((entry -> GCAttr == ENTRYALIVE) || (entry -> GCAttr == POTENTIALLYDEAD)),
	"What is GCAttr ?");
  
  entry -> GCAttr = ENTRYALIVE;
}

static void freeLoadedObjectsOF(void *contents)
{
  TIFree((Node *)contents, NULL);
}

void RTEndGC(void)
{
  u_long inx, maxIndex;
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
      if (!closingGC) {
	u_long newInx;
	RTEntry *newEntry;
	
	newEntry = (RTEntry *)malloc(sizeof(RTEntry));
	newEntry -> GCAttr = ENTRYALIVE;
	newEntry -> store = entry -> store;
	newEntry -> offset = entry -> offset;
	newEntry -> IOAclients = entry -> IOAclients;
	newEntry -> AOAclients = entry -> AOAclients;
	entry -> IOAclients = NULL;
	entry -> AOAclients = NULL;
	
	newInx = STInsert(&newTable, newEntry);
	
	redirectCells(newEntry -> IOAclients, 
		      (Object *)newPUID(inx), 
		      (Object *)newPUID(newInx));

	redirectCells(newEntry -> AOAclients, 
		      (Object *)newPUID(inx), 
		      (Object *)newPUID(newInx));
	
	
	insertStoreOffsetRT(newEntry -> store, newEntry -> offset, newInx + 1);
      } else {
	clearCells(entry -> IOAclients);
	clearCells(entry -> AOAclients);
      }
    } else {
      Claim((entry -> GCAttr == ENTRYDEAD), "What is GCAttr ?");
    }
  }
  
  STFree(&currentTable);
  currentTable = newTable;
  
}

#endif /* PERSIST */
