#include "beta.h"
#include "sequenceTable.h"

void st_dummy() {
#ifdef sparc
  USE();
#endif /* sparc */
}

#ifdef PERSIST

/* LOCAL MACROS */
#define TABLESIZE(length) (sizeof(struct sequenceTable) + sizeof(void *) * ((length) - 1))

static void clearTable(sequenceTable *currentTable, 
		       unsigned long start, 
		       unsigned long end)
{
  while(start < end) {
    currentTable -> body[start] = (void *)calloc(currentTable -> elemSize, 1);
    start++;
  }
}

sequenceTable *STInit(unsigned long NoElems, 
		      int (*isFree)(void *), 
		      void (*Free)(void *), 
		      unsigned long elemSize)
{
  sequenceTable *new;
  
  new = (sequenceTable *)calloc(TABLESIZE(NoElems), 1);
  new -> elemSize = elemSize;
  new -> isFree = isFree;
  new -> Free = Free;
  new -> maxIndex = NoElems;
  new -> nextFree = 0;
  clearTable(new, 0, NoElems);
  return new;
}

static sequenceTable *STRealloc(sequenceTable *currentTable)
{
  unsigned long newLength;
  sequenceTable *newTable;
  
  Claim(currentTable != NULL, "STRealloc: currentTable is NULL");
  Claim(currentTable -> maxIndex > 0, "STRealloc: length must be non zero before realloc");
  
  newLength = currentTable -> maxIndex * 2;
  newTable = (sequenceTable *)calloc(TABLESIZE(newLength), 1);
  memcpy(newTable, currentTable, TABLESIZE(currentTable -> maxIndex));
  newTable -> maxIndex = newLength;
  newTable -> nextFree = currentTable -> nextFree;
  clearTable(newTable, newTable -> nextFree, newTable -> maxIndex);
  
  free(currentTable);
  
  return newTable;
}

unsigned long STSize(sequenceTable *currentTable)
{
  return currentTable -> maxIndex;
}

unsigned long STInsert(sequenceTable **tableSite, void *elm)
{
  unsigned long inx;
  static unsigned long once = 0;
  sequenceTable *currentTable;
  
  Claim(elm != NULL, "STInsert: Trying to insert NULL element");
  Claim(tableSite != NULL, "STInsert:tableSite  is NULL");
  
  currentTable = *tableSite;
  
  Claim(currentTable != NULL, "STInsert: currentTable is NULL");
  
  while ((currentTable -> nextFree < currentTable -> maxIndex) &&
	 (currentTable -> body[currentTable -> nextFree] != NULL) &&
	 (!(currentTable -> isFree)(currentTable -> body[currentTable -> nextFree]))) {
    currentTable -> nextFree = currentTable -> nextFree + 1;
  }
  
  inx = currentTable -> nextFree;
  if (inx < currentTable -> maxIndex) {
    (currentTable -> Free)(currentTable -> body[inx]);
    currentTable -> body[inx] = elm;
    return inx;
  } else {
    if (once) {
      *tableSite = STRealloc(currentTable);
      once = 0;
      return STInsert(tableSite, elm);
    } else {
      once = 1;
      currentTable -> nextFree = 0;
      return STInsert(tableSite, elm);
    }
  }
}

void *STLookup(sequenceTable *currentTable, unsigned long inx)
{
  Claim(inx < currentTable -> maxIndex, "STLookup: Illegal inx");

  if (currentTable) {
    return currentTable -> body[inx];
  } else {
    return NULL;
  }
}

void STFree(sequenceTable **currentTable)
{
  unsigned long count, maxIndex;
  void **body;
  
  maxIndex = (*currentTable) -> maxIndex;
  body = &((*currentTable) -> body[0]);
  
  for (count = 0; count < maxIndex; count++) {
    ((*currentTable) -> Free)(body[count]);
  }
  free(*currentTable);
  *currentTable = NULL;
}

#endif /* PERSIST */
