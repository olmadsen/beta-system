#include <sys/types.h>

#include "beta.h"

#ifdef PERSIST

/* LOCAL prototypes */

/* LOCAL VARIABLES */
static Block *AOAPersistentBaseBlock;
static Block *AOAPersistentTopBlock;

/* IMPLEMENTATION */

Block *inPersistentAOA(Object *theObj) 
{
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

static void bringHome(Object **theCell) 
{
  if (!inProxy((long)*theCell)) {
    if (!inProxy((*theCell) -> GCAttr)) {
      /* Copy to persistent AOA, leave forward and redirect */
      *theCell = CopyObjectToPersistentAOA(*theCell);
      
    } else {
      /* Redirect */
      *theCell = (Object *)((*theCell) -> GCAttr);
      proxyAlive(theCell);

    }
  } 
}

void checkpoint(void)
{
  
  Block *current;
  Object *theObj;
  
  USE(); /* Not important */
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

  current = AOAPersistentBaseBlock;
  
  while(current) {
    theObj = (Object *)BlockStart(current);
    while ((long)theObj < (long)current -> top) {
      static long size;

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

Object *CopyObjectToPersistentAOA(Object *theObj)
{  
  long size;
  Object *realObj, *newObj;
  
  realObj = getRealObject(theObj);
  
  size = 4*ObjectSize(realObj); 
  if (AOAPersistentTopBlock) {
    if (size + (long)  AOAPersistentTopBlock -> top <= 
	(long) AOAPersistentTopBlock -> limit) {
      if (realObj == theObj) {
	newObj = (Object *)AOAPersistentTopBlock -> top;
	memcpy(newObj, theObj, size);
	
	/* Leave forward pointer in 'theObj' */
	theObj -> GCAttr = newProxy(AOAPersistentTopBlock, newObj);
	newObj -> GCAttr = theObj -> GCAttr;
	AOAPersistentTopBlock -> top = (long *)((long) newObj + size);
      } else {
	if (!inProxy(realObj -> GCAttr)) {
	  /* copy the enclosing object too. */
	  newObj = (Object *)AOAPersistentTopBlock -> top;	
	  memcpy(newObj, realObj, size);
	  
	  /* Leave forward pointer in enclosing object */
	  realObj -> GCAttr = newProxy(AOAPersistentTopBlock, newObj);
	  newObj -> GCAttr = realObj -> GCAttr;
	  
	  /* Leave forward pointer in 'theObj' */
	  theObj -> GCAttr = newProxy(AOAPersistentTopBlock, 
				      (Object *)((long)newObj +
						 (long)theObj - (long)realObj));
	  AOAPersistentTopBlock -> top = (long *)((long) newObj + size);
	  
	} else {
	  /* the enclosing object has been copied allready. */
	  theObj -> GCAttr = addConstantToProxy(realObj -> GCAttr,
						(long)theObj - (long)realObj);

	}
      }
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

static Block *lookupBlockId(long id) 
{
  Block *current;
  
  current = AOAPersistentBaseBlock;
  
  while (current) {
    if (current -> id == id) {
      return current;
    }
    current = current -> next;
    
  }
  return current;
}

Object *lookUpObject(void *dummy, long id, long offset) 
{
  Block *AOABlock;
  
  if ((AOABlock = lookupBlockId(id))) {
    if (offset < (long) AOABlock -> limit - (long)BlockStart(AOABlock)) {
      return (Object *)((long) BlockStart(AOABlock) + offset);
    } else {
      fprintf(output, "lookUpObject: "
	      "offset (0x%X) out of bounds\n", (int)offset);
      DEBUG_CODE(Illegal());
      BetaExit(1);
    }
    fprintf(output, "lookUpObject: "
	    "Block (0x%X) not in memory, load not supported yet\n", (int)id);
    DEBUG_CODE(Illegal());
    BetaExit(1);
  }
  return NULL;
}
  
void dumpObject(long obj) 
{
  ;
}

#endif /* PERSIST */
