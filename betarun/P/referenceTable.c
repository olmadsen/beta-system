#include "referenceTable.h"
#include "PException.h"
#include "objectTable.h"

void reft_dummy() {
#ifdef sparc
  USE();
#endif /* sparc */
}

#ifdef PERSIST

/* LOCAL TYPES */
typedef struct RTEntry { /* Reference Table Entry */
  char GCAttr;                  /* The GC state of this entry. */
  StoreID store;                /* The store in which this object is saved */
  u_long offset;                /* The byte offset in the store of the object */  
} RTEntry;

typedef struct ReferenceTable {
  u_long maxIndex;        /* number of indices allocated for this table */
  u_long nextFree;        /* Index of the next free entry */
  RTEntry body[1];
} ReferenceTable;

/* LOCAL DEFINITIONS */
#define INITIALTABLELENGTH 128 /* Initial size of the ReferenceTable */

/* LOCAL MACROS */
#define TABLESIZE(length) (sizeof(struct ReferenceTable) + sizeof(struct RTEntry) * ((length) - 1))

/* LOCAL VARIABLES */
static ReferenceTable *currentTable = NULL;

/* LOCAL FUNCTION DECLARATIONS */
static void RTRealloc(void);

/* FUNCTIONS */
void initReferenceTable(void)
{
  u_long newSize;
  
  newSize = TABLESIZE(INITIALTABLELENGTH);
  
  currentTable = (ReferenceTable *)calloc(TABLESIZE(INITIALTABLELENGTH), 1);
  currentTable -> maxIndex = INITIALTABLELENGTH;
  currentTable -> nextFree = 0;
  
  initProxyTrapHandler();
}

static void RTRealloc(void)
{
  u_long newLength;
  ReferenceTable *newTable;
  
  Claim(currentTable != NULL, "RTRealloc: currentTable is NULL");
  Claim(currentTable -> maxIndex > 0, "RTRealloc: length must be non zero before realloc");
  
  newLength = currentTable -> maxIndex * 2;
  newTable = (ReferenceTable *)calloc(TABLESIZE(newLength), 1);
  memcpy(newTable, currentTable, TABLESIZE(currentTable -> maxIndex));
  newTable -> maxIndex = newLength;
  newTable -> nextFree = currentTable -> nextFree;
  free(currentTable);
  currentTable = newTable;
}

u_long insertReference(char GCAttr,
		       StoreID store,
		       u_long offset)
{
  u_long inx;
  static u_long once = 0;
  
  Claim(currentTable != NULL, "insertReference: currentTable is NULL");
  
  while ((currentTable -> nextFree < currentTable -> maxIndex) &&
	 (currentTable -> body[currentTable -> nextFree].GCAttr != ENTRYDEAD)) {
    currentTable -> nextFree = currentTable -> nextFree + 1;
  }
  
  inx = currentTable -> nextFree;
  if (inx < currentTable -> maxIndex) {
    RTEntry *body;
    body = &(currentTable -> body[0]);
    body[inx].GCAttr = GCAttr;
    body[inx].store = store;
    body[inx].offset = offset;
    return inx;
  } else {
    if (once) {
      RTRealloc();
      once = 0;
      return insertReference(GCAttr, store, offset);
    } else {
      once = 1;
      currentTable -> nextFree = 0;
      return insertReference(GCAttr, store, offset);
    }
  }
}

/* Looks up GCAttr, store and offset based on index into table */
void referenceLookup(u_long inx,
		     char *GCAttr,
		     StoreID *store,
		     u_long *offset)
{
  RTEntry *body;
  
  Claim(inx < currentTable -> maxIndex, "referenceLookup: Illegal inx");
  
  body = &(currentTable -> body[0]);
  
  *GCAttr = body[inx].GCAttr;
  *store = body[inx].store;
  *offset = body[inx].offset;
}

/* Returns inx of entry containing (??, store, object). Returns -1 if
   not found. */
u_long indexLookupRT(StoreID store, u_long offset)
{
  u_long inx;
  RTEntry *body;
  
  body = &(currentTable -> body[0]);
  for (inx = 0; inx < currentTable -> maxIndex; inx++) {
    if (body[inx].store == store) {
      if (body[inx].offset == offset) {
	return inx;
      }
    }
  }
  
  return -1;
}

/* Marks all entries as potentially dead. */
void RTStartGC(void)
{
  u_long inx;
  RTEntry *body;
  
  if (currentTable == NULL) {
    initReferenceTable();
  }
  
  body = &(currentTable -> body[0]);
  for (inx = 0; inx < currentTable -> maxIndex; inx++) {
    if (body[inx].GCAttr == ENTRYALIVE) {
      body[inx].GCAttr = POTENTIALLYDEAD;
    } else {
      Claim(body[inx].GCAttr == ENTRYDEAD, "What is GCAttr ?");
    }
  }
}

void referenceAlive(void *ip)
{
  RTEntry *body;
  u_long inx;
  
  inx = getPUID(ip);
  
  Claim(inx < currentTable -> maxIndex, "referenceAlive: Illegal inx");
  
  body = &(currentTable -> body[0]);
  
  Claim(((body[inx].GCAttr == ENTRYALIVE) || (body[inx].GCAttr == POTENTIALLYDEAD)),
	"What is GCAttr ?");
  
  body[inx].GCAttr = ENTRYALIVE;
}

void RTEndGC(void)
{
  u_long inx;
  RTEntry *body;
  
  body = &(currentTable -> body[0]);
  for (inx = 0; inx < currentTable -> maxIndex; inx++) {
    if (body[inx].GCAttr == POTENTIALLYDEAD) {
      body[inx].GCAttr = ENTRYDEAD;
      body[inx].store = 0;
      body[inx].offset = 0;
    } else {
      Claim(((body[inx].GCAttr == ENTRYALIVE) || (body[inx].GCAttr == ENTRYDEAD)),
	    "What is GCAttr ?");
    }
  }
}

#endif /* PERSIST */
