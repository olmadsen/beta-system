#include "beta.h"
#include "domain.h"

/* */
void dom_dummy() {
#ifdef sparc
  USE();
#endif /* sparc */
}

#ifdef PERSIST

/* LOCAL TYPES */
typedef struct DomainTable {
  unsigned long maxIndex;
  unsigned long nextFree;
  ProtoType *body[1];
} DomainTable;

/* LOCAL DEFINITIONS */
#define INITIALTABLELENGTH 128 /* Initial size of the ReferenceTable */

/* LOCAL MACROS */
#define TABLESIZE(length) (sizeof(struct DomainTable) + sizeof(ProtoType *) * ((length) - 1))

/* LOCAL VARIABLES */
static DomainTable *currentTable = NULL;

/* LOCAL FUNCTION DECLARATIONS */
static void DTRealloc(void);
static void initDomainTable(void);

/* FUNCTIONS */
static void initDomainTable(void)
{
  unsigned long newSize;
  
  newSize = TABLESIZE(INITIALTABLELENGTH);
  
  currentTable = (DomainTable *)calloc(TABLESIZE(INITIALTABLELENGTH), 1);
  currentTable -> maxIndex = INITIALTABLELENGTH;
  currentTable -> nextFree = 0;

}

static void DTRealloc(void)
{
  unsigned long newLength;
  DomainTable *newTable;
  
  Claim(currentTable != NULL, "DTRealloc: currentTable is NULL");
  Claim(currentTable -> maxIndex > 0, "DTRealloc: length must be non zero before realloc");
  
  newLength = currentTable -> maxIndex * 2;
  newTable = (DomainTable *)calloc(TABLESIZE(newLength), 1);
  memcpy(newTable, currentTable, TABLESIZE(currentTable -> maxIndex));
  newTable -> maxIndex = newLength;
  newTable -> nextFree = currentTable -> nextFree;
  free(currentTable);
  currentTable = newTable;
}

unsigned long newDomain(Structure *structure)
{
  ProtoType *theProto;
  unsigned long inx;
  
  if (currentTable == NULL) {
    initDomainTable();
  }
  theProto = structure -> iProto;
  
  Claim(IsPrototypeOfProcess((long)theProto), "newDomain: What is theProto ?");
  
  inx = currentTable -> nextFree;
  if (inx < currentTable -> maxIndex) {
    currentTable -> body[inx] = theProto;
    return inx;
  } else {
    DTRealloc();
    return newDomain(structure);
  }
  
}

unsigned long getDomain(Object *theObj)
{
  unsigned long inx, max;
  ProtoType *theProto;
  
  theProto = GETPROTO(theObj);
  max = currentTable -> nextFree;
  for (inx = 0; inx < max; inx++) {
    if (currentTable -> body[inx] == theProto) {
      return inx;
    }
  }
  /* The object belongs to the default domain */
  return DEFAULTDOMAIN;
}

#endif /* PERSIST */
