#include "sequenceTable.h"

#include <memory.h>
#include <stdlib.h>
#ifdef sgi
#include <string.h>
#endif /* sgi */


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

unsigned long STtop(sequenceTable *currentTable)
{
  return currentTable -> nextFree;
}

unsigned long STInsert(sequenceTable **tableSite, void *elm)
{
  unsigned long inx;
  static unsigned long once = 0;
  sequenceTable *currentTable;
  
  currentTable = *tableSite;
  
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
  if (currentTable) {
    return (void *)((unsigned long)&(currentTable -> body[0]) + 
		    currentTable -> elemSize * inx);
  } else {
    return (void *)0;
  }
}

void STFree(sequenceTable **currentTable)
{
  free(*currentTable);
  *currentTable = (void *)0;
}
