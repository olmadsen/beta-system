#include "beta.h"
#include "objectSet.h"

/* */
void objs_dummy() {
#ifdef sparc
  USE();
#endif /* sparc */
}

#ifdef PERSIST

/* LOCAL TYPES */
typedef struct OSTable {
  u_long maxIndex;
  u_long nextFree;
  Object *body[1];
} OSTable;

/* LOCAL DEFINITIONS */
#define INITIALTABLELENGTH 128 /* Initial size of the ReferenceTable */

/* LOCAL MACROS */
#define TABLESIZE(length) (sizeof(struct OSTable) + sizeof(Object *) * ((length) - 1))

/* LOCAL VARIABLES */
static OSTable *currentTable = NULL;

/* LOCAL FUNCTION DECLARATIONS */
static void OSRealloc(void);
static void initOSTable(void);

/* FUNCTIONS */
static void initOSTable(void)
{
  u_long newSize;
  
  newSize = TABLESIZE(INITIALTABLELENGTH);
  
  currentTable = (OSTable *)calloc(TABLESIZE(INITIALTABLELENGTH), 1);
  currentTable -> maxIndex = INITIALTABLELENGTH;
  currentTable -> nextFree = 0;
  
}

static void OSRealloc(void)
{
  u_long newLength;
  OSTable *newTable;
  
  Claim(currentTable != NULL, "OSRealloc: currentTable is NULL");
  Claim(currentTable -> maxIndex > 0, "OSRealloc: length must be non zero before realloc");
  
  newLength = currentTable -> maxIndex * 2;
  newTable = (OSTable *)calloc(TABLESIZE(newLength), 1);
  memcpy(newTable, currentTable, TABLESIZE(currentTable -> maxIndex));
  newTable -> maxIndex = newLength;
  newTable -> nextFree = currentTable -> nextFree;
  free(currentTable);
  currentTable = newTable;
}

void OSinsert(Object *theObj)
{
  u_long inx;
  
  Claim(currentTable != NULL, "OSinsert: currentTable is NULL");
  Claim(theObj != NULL, "Inserting NULL");
  
  inx = currentTable -> nextFree;
  if (inx < currentTable -> maxIndex) {
    currentTable -> body[inx] = theObj;
    currentTable -> nextFree = currentTable -> nextFree + 1;
  } else {
    OSRealloc();
    OSinsert(theObj);
  }
}

void OSscan(void (*foreach)(Object *theObj))
{
  u_long inx, max;
  
  max = currentTable -> nextFree;
  for (inx = 0; inx < max; inx++) {
    if (currentTable -> body[inx]) {
      foreach(currentTable -> body[inx]);
    } else {
      return;
    }
  }
}

void OSclear(void)
{
  if (currentTable) {
    free(currentTable);
    currentTable = NULL;
  }
  initOSTable();
}

#endif /* PERSIST */
