#include <sys/types.h>

#include "beta.h"

/* LOCAL prototypes */
static Object *CopyObjectToPersistentAOA(Object *theObj);

/* Global prototypes */
void checkpoint(void);

/* LOCAL VARIABLES */
static Block *AOAPersistentBaseBlock;
static Block *AOAPersistentTopBlock;

/* IMPLEMENTATION */

static Block *inPersistentAOA(Object *theObj) {
  Block *current;
  
  current = AOAPersistentBaseBlock;
  
  while (current) {
    if (((long) BlockStart(current) <= (long) theObj) &&
	((long) theObj < (long) current -> limit)) {
      return current;
    }
    current = current -> next;
    
  }
  return current;
  
}

static void bringHome(Object **theCell) {
  if (!inProxy((long)*theCell)) {
    if (!inProxy((*theCell) -> GCAttr)) {
      /* Copy to persistent AOA, leave forward and redirect */
      *theCell = CopyObjectToPersistentAOA(*theCell);
      
    } else {
      /* Redirect */
      *theCell = (Object *)((*theCell) -> GCAttr);

    }
  } 
  
  proxyAlive(theCell);
}

void checkpoint(void)
{
  
  Block *current;
  Object *theObj;
  
  initProxySpace();
  
  freeProxySpace();
  
  current = AOAPersistentBaseBlock;
  
  while(current) {
    theObj = (Object *)BlockStart(current);
    while ((long)theObj < (long)current -> top) {
      static long size;
      
      scanObject(theObj,
		 bringHome,
		 TRUE);
      
      size = 4 * ObjectSize((Object *)theObj);
      theObj = (Object *)((long) theObj + (long)size);
    }
    current = current -> next;
    
  }
  
  forceAOAGC = TRUE;
  
  return;
  
  /* return to BETACODE and do GC. */
}

static Block *allocatePersistentBlock(long minSize) 
{
  Block *newblock;
  long newBlockSize;
  
  newBlockSize = (AOABlockSize < minSize) ? minSize : AOABlockSize;
  
  newblock = newBlock(newBlockSize);
  newblock->top   = BlockStart(newblock);
  
  return newblock;
}

static Object *CopyObjectToPersistentAOA(Object *theObj)
{  
  long size;
  Object *realObj, *newObj;
  
  realObj = getRealObject(theObj);
  
  size = 4*ObjectSize(realObj); 
  if (AOAPersistentTopBlock) {
    if (size + (long)  AOAPersistentTopBlock -> top <= 
	(long) AOAPersistentTopBlock -> limit) {
      
      newObj = (Object *)AOAPersistentTopBlock -> top;
      if (realObj == theObj) {
	memcpy(newObj, theObj, size);
	
	/* Leave forward pointer in 'theObj' */
	theObj -> GCAttr = newProxy(AOAPersistentTopBlock, newObj);
      } else {
	memcpy(newObj, realObj, size);
	
	/* Leave forward pointer in 'theObj' */
	theObj -> GCAttr = newProxy(AOAPersistentTopBlock, (Object *)((long)newObj +
								      (long)theObj - (long)realObj));
      }
      AOAPersistentTopBlock -> top = (long *)((long) newObj + size);
      return (Object *)(theObj -> GCAttr);
      
    } else {
      AOAPersistentTopBlock -> next = allocatePersistentBlock(size);
      AOAPersistentTopBlock = AOAPersistentTopBlock -> next;
      
    }
  } else {
    AOAPersistentBaseBlock = allocatePersistentBlock(size);
    AOAPersistentTopBlock = AOAPersistentBaseBlock;
    
  }
  
  /* Assign id and store to new persistent top block */
  AOAPersistentTopBlock -> dummy = (void *)getStoreOfProcess();
  AOAPersistentTopBlock -> id = getNextStoreId();
  
  return CopyObjectToPersistentAOA(theObj);
}
