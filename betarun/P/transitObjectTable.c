#include "beta.h"
#include "referenceTable.h"
#include "sequenceTable.h"
#include "trie.h"
#include "objectTable.h"
#include "PException.h"

void tobjt_dummy() {
#ifdef sparc
  USE();
#endif /* sparc */
}

#ifdef PERSIST
/* LOCAL TYPES */
typedef struct TOTEntry { /* Object Table Entry */
  BlockID store;
  u_long offset;
  Object *theObj;         /* The object in memory */       
} TOTEntry;

/* LOCAL DEFINITIONS */
#define INITIALTABLELENGTH 128 /* Initial size of the objectTable */

/* LOCAL VARIABLES */
static sequenceTable *currentTable = NULL;
static Node *loadedObjectsST;

/* LOCAL FUNCTION DECLARATIONS */
static int isFree(void *entry);
static void Free(void *entry);
static void freeLoadedObjectsOF(void *contents);
static void insertStoreOffsetTOT(BlockID store, u_long offset, u_long inx);

/* FUNCTIONS */
static int isFree(void *entry)
{
  Claim(entry != NULL, "isFree: entry is NULL");
  return (((TOTEntry *)entry) -> theObj == NULL);
}

static void Free(void *entry)
{
  free((TOTEntry *)entry);
}

void initTransitObjectTable(void)
{
  currentTable = STInit(INITIALTABLELENGTH, isFree, Free, sizeof(TOTEntry));
  loadedObjectsST = TInit();
}

u_long TOTSize(void)
{
  return STSize(currentTable);
}

u_long insertObjectInTransit(BlockID store,
			     u_long offset,
			     Object *theObj)
{
  TOTEntry *newEntry;
  u_long inx;
  
  newEntry = (TOTEntry *)malloc(sizeof(TOTEntry));
  newEntry -> store = store;
  newEntry -> offset = offset;
  newEntry -> theObj = theObj;
  inx = STInsert(&currentTable, newEntry);
  
  insertStoreOffsetTOT(store, offset, inx + 1);
  
  return inx;
}

Object *indexLookupTOT(BlockID store, u_long offset)
{
  Node *loadedObjectsOF;
  
  /* Check if store is member of 'loadedObjects' */
  if ((loadedObjectsOF = TILookup(store, loadedObjectsST))) {
    u_long inx;
    if ((inx = (u_long)TILookup(offset, loadedObjectsOF))) {
      TOTEntry *entry;
      
      entry = STLookup(currentTable, inx - 1);
      return entry -> theObj;
    }
  }
  return NULL;
}

static void insertStoreOffsetTOT(BlockID store, u_long offset, u_long inx)
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

void redirectCells(Array *clients, Object *from, Object *to)
{
  u_long max, count;
  Object **theCell;
  
  if (clients) {
    max = clients -> top;
    
    for (count = 0; count < max; count++) {
      theCell = (Object **)(clients -> theCells[count]);
      if (*theCell == from) {
	*theCell = to;
      }
    }
  }
}

void TOTFlush(void)
{
  u_long inx, maxIndex, inserted = 0;
  TOTEntry *entry;
  
  maxIndex = STSize(currentTable);
  
  for (inx = 0; inx < maxIndex; inx++) {
    entry = STLookup(currentTable, inx);
    if (entry -> theObj != NULL) {
      u_long RTinx;
      Object *theObj;
      
      theObj = entry -> theObj;
      if ((RTinx = indexLookupRT(entry -> store, entry -> offset)) != -1) {
	Array *IOAclients, *AOAclients;
	char GCAttr;
	BlockID store;
	u_long offset;

	referenceLookup(RTinx,
			&GCAttr,
			&store,
			&offset,
			&IOAclients,
			&AOAclients);

	Claim(store == entry -> store, "Table mismatch?");
	Claim(offset == entry -> offset, "Table mismatch?");
	Claim(GCAttr == ENTRYALIVE, "Entry is dead ?");
	
	redirectCells(IOAclients, (Object *)newPUID(RTinx), theObj);
	redirectCells(AOAclients, (Object *)newPUID(RTinx), theObj);

	
      } else {
	/* Object is not referred from memory */
	;
      }
      
      if (theObj == getRealObject(theObj)) {
	u_long OTinx;
	
	OTinx = insertObject(ENTRYALIVE,
			     entry -> store,
			     entry -> offset,
			     theObj);
	
	inserted++;

	theObj -> GCAttr = PERSISTENTMARK(OTinx);
      }
      entry -> theObj = NULL;
    } else {
      break;
    }
  }
  TIFree(loadedObjectsST, freeLoadedObjectsOF);
  loadedObjectsST = NULL;
  loadedObjectsST = TInit();
  STFree(&currentTable);
  initTransitObjectTable();
}

#endif /* PERSIST */
