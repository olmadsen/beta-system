#include "beta.h"
#include "referenceTable.h"
#include "sequenceTable.h"
#include "trie.h"
#include "objectTable.h"
#include "PException.h"
#include "misc.h"

#ifdef PERSIST
/* LOCAL TYPES */
typedef struct TOTEntry { /* Object Table Entry */
  unsigned long store;
  unsigned long offset;
  Object *theObj;         /* The object in memory */       
} TOTEntry;

/* LOCAL DEFINITIONS */
#define INITIALTABLELENGTH 128 /* Initial size of the objectTable */

/* LOCAL VARIABLES */
static sequenceTable *currentTable = NULL;
static Trie *loadedObjectsST = NULL;

/* LOCAL FUNCTION DECLARATIONS */
static int isFree(void *entry);
static void freeLoadedObjectsOF(void *contents);
static void insertStoreOffsetTOT(unsigned long store, unsigned long offset, unsigned long inx);

/* FUNCTIONS */
static int isFree(void *entry)
{
  Claim(entry != NULL, "isFree: entry is NULL");
  return (((TOTEntry *)entry) -> theObj == NULL);
}

void initTransitObjectTable(void)
{

  if (currentTable != NULL) {
    STFree(&currentTable);
  } 
  
  if (loadedObjectsST != NULL) {
    TIFree(loadedObjectsST, freeLoadedObjectsOF);
  }
  
  currentTable = STInit(INITIALTABLELENGTH, isFree, NULL, sizeof(TOTEntry));
  loadedObjectsST = TInit();
}

unsigned long TOTSize(void)
{
  return STSize(currentTable);
}

unsigned long insertObjectInTransit(unsigned long store,
				    unsigned long offset,
				    Object *theObj)
{
  TOTEntry *newEntry;
  unsigned long inx;
  
  newEntry = (TOTEntry *)malloc(sizeof(TOTEntry));
  newEntry -> store = store;
  newEntry -> offset = offset;
  newEntry -> theObj = theObj;
  inx = STInsert(&currentTable, newEntry);
  
  insertStoreOffsetTOT(store, offset, inx + 1);
  
  return inx;
}

Object *indexLookupTOT(unsigned long store, unsigned long offset)
{
  Trie *loadedObjectsOF;
  
  /* Check if store is member of 'loadedObjects' */
  if ((loadedObjectsOF = TILookup(store, loadedObjectsST))) {
    unsigned long inx;
    if ((inx = (unsigned long)TILookup(offset, loadedObjectsOF))) {
      TOTEntry *entry;
      
      entry = STLookup(currentTable, inx - 1);
      return entry -> theObj;
    }
  }
  return NULL;
}

static void insertStoreOffsetTOT(unsigned long store, unsigned long offset, unsigned long inx)
{
  insertStoreOffset(store, offset, inx, &loadedObjectsST);
}

static void freeLoadedObjectsOF(void *contents)
{
  TIFree((Trie *)contents, NULL);
}

void redirectCells(Array *clients, Object *from, Object *to)
{
  unsigned long max, count;
  Object **theCell;
  
  if (clients) {
    max = clients -> top;
    
    for (count = 0; count < max; count++) {
      theCell = (Object **)(clients -> theCells[count]);
      if (*theCell == from) {
	*theCell = to;
	Claim(*theCell != NULL, "Assigning NULL");
      }
    }
  }
}

void clearCells(Array *clients)
{
  unsigned long max, count;
  Object **theCell;
  
  if (clients) {
    max = clients -> top;
    
    for (count = 0; count < max; count++) {
      theCell = (Object **)(clients -> theCells[count]);
      if (inPIT((void *)(*theCell))) {
	*theCell = (Object *)NULL;
      }
    }
  }
}

void TOTFlush(void)
{
  unsigned long inx, maxIndex, inserted = 0, lookups = 0;
  TOTEntry *entry;
  
  maxIndex = STSize(currentTable);
  
  for (inx = 0; inx < maxIndex; inx++) {
    entry = STLookup(currentTable, inx);
    if (entry -> theObj != NULL) {
      unsigned long RTinx;
      Object *theObj;
      
      theObj = entry -> theObj;
      
      if (theObj -> GCAttr > 0) {
	RTinx = theObj -> GCAttr - 1;
      } else {
	INFO_PERSISTENCE(lookups++);
	RTinx = indexLookupRT(entry -> store, entry -> offset);
      }
      
      if (RTinx != -1) {
	Array *IOAclients, *AOAclients;
	unsigned short GCAttr;
	unsigned long store;
	unsigned long offset;
	
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
	if (theObj == getRealObject(theObj)) {
	  theObj -> GCAttr = DEADOBJECT;
	}
      }

      if (theObj == getRealObject(theObj)) {
	unsigned long OTinx;
	
	/* The FLAG_INSTORE flag indicates that this object is loaded
           from the store, thus it has a copy of itself following it */
	
	OTinx = insertObject(ENTRYALIVE, FLAG_INSTORE, 
			     entry -> store,
			     entry -> offset,
			     theObj);
	
	INFO_PERSISTENCE(inserted++);
	
	theObj -> GCAttr = PERSISTENTMARK(OTinx);
      }
      entry -> theObj = NULL;
    } else {
      break;
    }
  }
  initTransitObjectTable();
}

#endif /* PERSIST */
