#include "beta.h"
#include "sequenceTable.h"

#ifdef PERSIST

/* LOCAL MACROS */
#define TABLESIZE(st) (sizeof(struct sequenceTable) + st -> elemSize * st -> maxIndex)

static void clearTable(sequenceTable *currentTable, 
		       unsigned long start, 
		       unsigned long end)
{
  /* starting from 'start' the elements up to but not including 'end'
     are cleared.  */
  
  memset((char *)((unsigned long)(&(currentTable -> body[0])) + (start * currentTable -> elemSize)), 
	 0,
	 (end - start) * currentTable -> elemSize);
}

sequenceTable *STInit(unsigned long NoElems, 
		      int (*isFree)(void *), 
		      void (*Free)(void *), 
		      unsigned long elemSize)
{
  sequenceTable *new;
  
  new = (sequenceTable *)malloc(sizeof(struct sequenceTable) + elemSize * NoElems);
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
  newTable = (sequenceTable *)malloc(sizeof(struct sequenceTable) + 
				     currentTable -> elemSize * newLength);
  memcpy(newTable, 
	 currentTable, 
	 sizeof(struct sequenceTable) + currentTable -> elemSize * currentTable -> maxIndex);

  newTable -> maxIndex = newLength;

  /* Next free is inherited from the old table */
  
  /* Clear rest of new table */
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
	 (!(currentTable -> isFree)((void *)((unsigned long)&(currentTable -> body[0]) + 
					     currentTable -> nextFree * 
					     currentTable -> elemSize)))) {
    currentTable -> nextFree = currentTable -> nextFree + 1;
  }
  
  inx = currentTable -> nextFree;
  if (inx < currentTable -> maxIndex) {
    memcpy((char *)((unsigned long)&(currentTable -> body[0]) + 
		    currentTable -> elemSize * inx), 
	   elm, 
	   currentTable -> elemSize);
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
    return (void *)((unsigned long)&(currentTable -> body[0]) + 
		    currentTable -> elemSize * inx);
  } else {
    return NULL;
  }
}

void STFree(sequenceTable **currentTable)
{
  unsigned long count, maxIndex;
  void **body;
  
  if ((*currentTable) -> Free) {
    maxIndex = (*currentTable) -> maxIndex;
    body = &((*currentTable) -> body[0]);
    
    for (count = 0; count < maxIndex; count++) {
      ((*currentTable) -> Free)((void *)((unsigned long)body + 
					 count * (*currentTable) -> elemSize)); 
      /* Respect to Ice-T */
    }
  }
  free(*currentTable);
  *currentTable = NULL;
}

#endif /* PERSIST */
