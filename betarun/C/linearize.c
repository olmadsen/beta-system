#include <sys/types.h>

#include "beta.h"

void lin_dummy() {

#ifdef sparc
  USE();
#endif /* sparc */

}

#ifdef PERSIST

/* LOCAL FUNCTION DECLARATIONS */
static void bringHome(Object **theCell);
static void bringHomeAction(Object *theObj, void *generic);
static void unmarkOriginAction(Object *theObj, void *dummy);
static void updateTables(Object **theCell);
static void rebuildTableObj(Object *theObj,
			    void *generic);
static Block *allocatePersistentBlock(long minSize);
static Block *lookupBlockId(long id);
#ifdef RTDEBUG
static void CheckPersistentCell(Object **theCell);
static void CheckPersistentCellAfterIOA(Object **theCell);
static void checkPersistentOrigin(Object *theObj);
static void checkPersistentObject(Object *theObj, void *generic);
static void checkPersistentObjectInAOAAfterIOA(Object *theObj, void *generic);
#endif /* RTDEBUG */

/* LOCAL TYPES */
/* Mapping the BETA roots to C */
typedef struct charRep {
  u_long Proto;
  u_long GCAttr;
  u_long LowBorder;
  u_long HighBorder;
  char elements[1];
} charRep;

typedef struct Text {
  u_long Proto;
  u_long GCAttr;
  u_long Origin;
  charRep *theRep;
} Text;

typedef struct root {
  u_long Proto;
  u_long GCAttr;
  u_long Origin;
  Object *theObj;
  Text *name;
} root;

typedef struct rootRep {
  u_long Proto;
  u_long GCAttr;
  u_long LowBorder;
  u_long HighBorder;
  long elements[1];
} rootRep;

/* LOCAL VARIABLES */
#ifdef RTINFO
u_long numPersistentBlocks;
u_long numObjects;
u_long sizeOfObjects;
#endif /* RTINFO */

/* IMPLEMENTATION */

/* inPersistentAOA: Returns the persistent AOA block in wich theObj is
   located. Returns NULL if theObj is not in any persistent
   AOABlock. */
Block *inPersistentAOA(long theObj) 
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

/* bringHome: Takes a reference to a cell in persistent AOA, and
   copies the referred object to persistent AOA if not allready there.  */
static void bringHome(Object **theCell) 
{
  
  Claim(NULL != inPersistentAOA((long)theCell),"theCell is not in persistent AOA");
  
  if (!inProxy((long)*theCell)) {
    if (!inProxy((*theCell) -> GCAttr)) {
      /* Copy to persistent AOA, leave forward and redirect */
      *theCell = CopyObjectToPersistentAOA(*theCell);
    } else {
      /* Redirect */
      *theCell = (Object *)((*theCell) -> GCAttr);
      proxyAlive(theCell);
    }
  } else {
    proxyAlive(theCell);
  }
}

/* bringHomeAction: Is called for every object in persistent AOA. */
static void bringHomeAction(Object *theObj, void *generic) 
{
  scanObject(theObj,
	     bringHome,
	     TRUE);
}

/* unmarkOriginAction: Is called for every object not in persistent
   AOA, just after all objects that are to be moved to persistent AOA
   have been marked. If the object has a origin reference to an object
   that has been marked to be moved, then the origin object is
   unmarked. Any marked object has allready been copied to persistent
   AOA, and unmarking the original will result in references to it
   from outside persistent AOA not being redirected. Thus such objects
   are in effect cloned. */
static void unmarkOriginAction(Object *theObj, void *dummy)
{
  Object *origin;
  long GCAttribute;
  long originOffset;
  
  Claim(!inPersistentAOA((long)theObj), "inPersistentAOA(theObj)");
  
  if (!inProxy(theObj -> GCAttr)) {
    /* This object is not persistent. Check that origin is not
       persistent */
    
    if ((origin = getOrigin(theObj, &originOffset))) {
      
      if (inProxy((long) origin)) {
	void *dummy;
	u_long id;
	u_long offset;
	static u_long once = 1;
	
	getProxyAttributes(*(long *)((long) theObj + originOffset), &dummy, &id, &offset);
	
	origin = lookUpObject(dummy, id, offset);
	
	if (once) {
	  fprintf(output, "Warning, theObj has origin in persistent object\n");
	  once = 0;
	}
      } else {
	/* check if the origin object has been marked to be moved. */
	Object *realOriginObj;
	
	realOriginObj = getRealObject(origin);
	
	GCAttribute = realOriginObj -> GCAttr;
	
	Claim(!isStatic(GCAttribute), "Is static?");
	
	if (inIOA(realOriginObj)) {
	  /* unmark origin object in IOA */
	  
	  if (isForward(GCAttribute)) { 
	    if (inProxy(GCAttribute)) {
	      /* Origin object has been marked to be moved. Unmark
		 origin object */
	      realOriginObj -> GCAttr = IOAMinAge;
	      unmarkOriginAction(realOriginObj, NULL);
	    } else {
	      Claim(FALSE, "Wierd GCAttribute in IOA");
	    }
	  }
	} else if (!inPersistentAOA((long)realOriginObj)) {
	  /* unmark origin object in AOA  */
	  
	  if (!inProxy(GCAttribute)) { 
	    Claim(GCAttribute == DEADOBJECT, "AOA object not marked DEAD?");
	  } else {
	    realOriginObj -> GCAttr = DEADOBJECT;
	    unmarkOriginAction(realOriginObj, NULL);
	  }
	} else {
	  static u_long once = 1;
	  /* We have an object !inPersistentAOA that has a direct
             origin reference to a persistent object. */
	  if (once) {
	    fprintf(output,"Warning, transient object has origin in persistent object\n");
	    once = 0;
	  }
	}
      }
    }
  }
}

/* checkpoint: All objects reachabel from the persistent blocks are
   copied into persistent blocks. All objects, except those in which
   non-persistent objects have origins are marked, and all references
   to marked objects will be swizzled at the next GC. */
void _checkpoint(Object *roots)
{
  rootRep *croots;
  root *currentRoot;
  Object *currentObj;
  Text *currentText;
  charRep *theRep;
  char *name;
  u_long i,j;
  
  /* 'roots' is a pointer to a BETA repetition of (object, name)
     pairs. All these roots should be scanned and copied to persistent
     AOA before the transitive closure is brought home. */
  
  croots = (rootRep *) roots;
  for (i = croots -> LowBorder; i <= croots -> HighBorder; i++) {
    if ((currentRoot = (root *)(croots -> elements)[i - 1])) {
      currentObj = currentRoot -> theObj;
      currentText = currentRoot -> name;
      theRep = currentText -> theRep;
      
      {
	name = (char *)malloc(sizeof(char)*(theRep -> HighBorder - theRep -> LowBorder + 1 + 1));
	
	for (j = theRep -> LowBorder; j <= theRep -> HighBorder; j++) {
	  name[j - theRep -> LowBorder] = theRep -> elements[j - 1];
	}
	
	name[j - 1] = '\0';
	
	/* Now we have the object, name pair to insert */
	
	if (inIOA(currentObj) || inAOA(currentObj)) {
	  currentObj = CopyObjectToPersistentAOA(currentObj);
	  putName(currentObj, name);
	  free(name);
	  name = NULL;
	  
	} else {
	  Claim(FALSE, "checkpoint: Where is root ?");
	}
      }
    }
  }
  
  forceAOAGC = TRUE;

  /* The transitive closure of all objects in the persistent block are
     copied into persistent blocks, and forward references are left in
     the GCAttribute of the originals. */
  foreachObjectInBlocks(AOAPersistentBaseBlock,
			bringHomeAction,
			NULL);
  
  /* If there are objects in IOA and non persistent AOA that have
     origins in some of these objects just moved, then we cannot move
     them anyway. In such a case we only copy the object to persistent
     storage and does not actually move it. All objects have been
     copied to persistent AOA at this point, now we just need to
     unmark the origin-objects. */
  
  foreachObjectInIOA(unmarkOriginAction,
		     NULL);
  
  foreachObjectInBlocks(AOABaseBlock,
			unmarkOriginAction,
			NULL);

  /* Return to BETA and do GC 
     doGCFrom(BetaStackTop);
     
     _exportPersistentAOABlocks();
  */
  
  return;
  
}

/* exportPersistentAOABlocks: Dumps all persistent AOA blocks to
   external storage. It is assumed that all references within and to
   persistent blocks have been swizzled. */
void _exportPersistentAOABlocks(void) 
{
  Block *current, *next;
  current = AOAPersistentBaseBlock;
  
  while(current) {
    next = current -> next;
    INFO_PERSISTENTSTORE(fprintf(output,"[Export: dumping block 0x%X -> 0x%X \n", 
				 (int)BlockStart(current), (int)(current -> limit)));
    savePersistentAOABlock(current);
    INFO_PERSISTENTSTORE(fprintf(output,"]\n"));
    free(current);
    current = NULL;
    current = next;
  }
  
  AOAPersistentBaseBlock = NULL;
  AOAPersistentTopBlock = NULL;
  
  INFO_PERSISTENTSTORE(numPersistentBlocks=0);
  INFO_PERSISTENTSTORE(sizeOfObjects=0);
  INFO_PERSISTENTSTORE(numObjects=0);
}

/* unpersistifyAOABlocks: Not implemented yet. */
void _unpersistifyAOABlocks(void) 
{
  ;
}

/* get: Looks up the object based on the name in the name -> object map
   associated with the current persistent store. */
long _get(char *name) 
{
  void *dummy;
  long GCAttr;
  long id;    
  long offset;
  
  Object *theObj;
  
  getName(name, &dummy, &GCAttr, &id, &offset);
  
  theObj = lookUpObject(dummy, id, offset);
  
  /* The block containing the object has been loaded and we have an
   * absolute reference to the object. */
  
  return (long)theObj;
}

/* put: Registers theObj as being a root for the persistent
   objects. */
void _put(Object *theObj, char *name)
{

  theObj = CopyObjectToPersistentAOA(theObj);
  putName(theObj, name);
  
}

/* The following three functions scans all objects in persistent AOA
   and inserts in AOAtoIOATable whenever necessary. This should be
   done at every AOAGC. */
static void updateTables(Object **theCell) 
{
  
  Claim((long)inPersistentAOA((long)theCell), "Not in persistent AOA");
  
  if (inToSpace(*theCell)) {
#ifdef MT
    MT_AOAtoIOAInsert( theCell);
#else /* MT */
    AOAtoIOAInsert( theCell);
#endif /* MT */
  } else if (inAOA(*theCell)) {
    MCHECK();
    saveAOAroot(theCell);
    MCHECK();
  }
}

static void rebuildTableObj(Object *theObj,
			    void *generic)
{
  scanObject(theObj,
	     updateTables,
	     TRUE);
}

void rebuildAOAtoIOATable(void) 
{
  foreachObjectInBlocks(AOAPersistentBaseBlock,
			rebuildTableObj,
			NULL);
}

/* foreachObjectInBlocks: Activates a function for every object in b
   and the successors of b. */
void foreachObjectInBlocks(Block *b, 		
			   void (*objectAction)(Object *, void *),
			   void *generic)
{
  Block *current;
  Object *theObj;
  
  current = b;
  
  while(current) {
    theObj = (Object *)BlockStart(current);
    while ((long)theObj < (long)current -> top) {
      static long size;
      
      objectAction(theObj, generic);
      
      size = 4 * ObjectSize((Object *)theObj);
      theObj = (Object *)((long) theObj + (long)size);
    }
    current = current -> next;
  }
}

/* allocatePersistentBlock: Allocates a new persistent AOA block, but
   does not link it to the others. */
static Block *allocatePersistentBlock(long minSize) 
{
  Block *newblock;
  long newBlockSize;
  
  newBlockSize = (AOABlockSize < minSize) ? minSize : AOABlockSize;
  
  newblock = newBlock(newBlockSize);
  newblock->top   = BlockStart(newblock);
  
  INFO_PERSISTENTSTORE(numPersistentBlocks++);
  
  return newblock;
}

/* CopyObjectToPersistentAOA: Copies theObj to a persistent AOAblock
   and returns a proxy reference to it. */
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
	INFO_PERSISTENTSTORE(numObjects++);
	INFO_PERSISTENTSTORE(sizeOfObjects += size);

	/* Leave forward pointer in 'theObj' */
	theObj -> GCAttr = newProxy(AOAPersistentTopBlock, newObj);
	newObj -> GCAttr = theObj -> GCAttr;
	AOAPersistentTopBlock -> top = (long *)((long) newObj + size);
	return (Object *)(theObj -> GCAttr);
	
      } else {
	if (!inProxy(realObj -> GCAttr)) {
	  /* copy the enclosing object too. */
	  newObj = (Object *)AOAPersistentTopBlock -> top;	
	  memcpy(newObj, realObj, size);
	  INFO_PERSISTENTSTORE(numObjects++);	  
	  INFO_PERSISTENTSTORE(sizeOfObjects += size);
	  
	  /* Leave forward pointer in enclosing object */
	  realObj -> GCAttr = newProxy(AOAPersistentTopBlock, newObj);
	  newObj -> GCAttr = realObj -> GCAttr;
	  
	  AOAPersistentTopBlock -> top = (long *)((long) newObj + size);
	  
	} else {
	  /* the enclosing object has been copied allready. */
	  ;
	}
	return (Object *)addConstantToProxy(realObj -> GCAttr,
					    (long)theObj - (long)realObj);
	
      }
      
    } else {
      AOAPersistentTopBlock -> next = allocatePersistentBlock(size);
      AOAPersistentTopBlock = AOAPersistentTopBlock -> next;
      
    }
  } else {
    INFO_PERSISTENTSTORE(numPersistentBlocks=0);
    INFO_PERSISTENTSTORE(sizeOfObjects=0);
    INFO_PERSISTENTSTORE(numObjects=0);
    
    if (!AOAtoIOAtable) {
      if( AOAtoIOAalloc() == 0 ){
	fprintf(output, "CopyObjectToPersistentAOA: "
		"#(AOA: AOAtoIOAtable allocation %d failed!.)\n",
		(int)AOAtoIOAtableSize);
	DEBUG_CODE(Illegal());
	BetaExit(1);
      }
    }
    
    AOAPersistentBaseBlock = allocatePersistentBlock(size);
    AOAPersistentTopBlock = AOAPersistentBaseBlock;
    
  }
  
  /* Assign id and store to new persistent top block */
  AOAPersistentTopBlock -> dummy = (void *)getStoreOfProcess();
  AOAPersistentTopBlock -> id = getNextStoreId();
  
  return CopyObjectToPersistentAOA(theObj);
}

/* lookupBlockId: Returns the persistent block whoes id is 'id'. */
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

/* lookUpObject: Given the proxy attributes of a persistent object an
   absolute reference to its current position is returned. This might
   result in loading an AOAblock if the block containing the object is
   not present in memory. */
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
  } else {
    AOABlock = loadPersistentAOABlock(id);
    if (AOAPersistentBaseBlock) {
      AOAPersistentTopBlock -> next = AOABlock;
      AOAPersistentTopBlock = AOABlock;
      AOAPersistentTopBlock -> next = NULL;
    } else {
      AOAPersistentBaseBlock = AOABlock;
      AOAPersistentBaseBlock -> next = NULL;
      AOAPersistentTopBlock = AOAPersistentBaseBlock;
    }
    if (!AOAtoIOAtable) {
      if( AOAtoIOAalloc() == 0 ){
	fprintf(output, "lookUpObject: "
		"#(AOA: AOAtoIOAtable allocation %d failed!.)\n",
		(int)AOAtoIOAtableSize);
	DEBUG_CODE(Illegal());
	BetaExit(1);
      }
    }
    
    /* The block that has just been loaded needs to have its origin
       references unproxyfied. This might result in loading of any
       number of additional blocks. */
    
    unswizzleOrigins(AOABlock);
    
    DEBUG_PERSISTENCE(checkPersistentAOA());
    
    return lookUpObject(dummy, id, offset);
  }
  return NULL;
}

#ifdef RTDEBUG

/* The functions below are not necessarily correct, but left there
   since some of them might be needed again. */
static void CheckPersistentCell(Object **theCell) 
{
  if (*theCell) {
    if (inProxy((long)*theCell)) {
      if (proxyIsAlive((long)*theCell)) {
	return;
      } else {
	fprintf(output, "CheckPersistentCell: proxy is not alive\n");
	Illegal();
	BetaExit(1);
      }
    } else {
      ;
    }
  }
}

static void CheckPersistentCellAfterIOA(Object **theCell) 
{
  return;

  if (*theCell) {
    if (inProxy((long)*theCell)) {
      if (proxyIsAlive((long)*theCell)) {
	return;
      } else {
	fprintf(output, "CheckPersistentCell: proxy is not alive\n");
	Illegal();
	BetaExit(1);
      }
    } else {
      if (inAOA(*theCell)) {
	return;
      } else {
	if (IOAActive) {
	  if (inToSpace(*theCell)) {
	    return;
	  } else {
	    fprintf(output, "CheckPersistentCell: *theCell is in FromSpace\n");
	    Illegal();
	    BetaExit(1);
	  }
	} else {
	  if (inToSpace(*theCell)) {
	    fprintf(output, "CheckPersistentCell: *theCell is in ToSpace\n");
	    Illegal();
	    BetaExit(1);
	  } else {
	    return;
	  }
	}
      }
    }
  }
}

static void checkPersistentOrigin(Object *theObj)
{
  Object **theCell;
  Object *origin;
  long originOffset;

  if ((origin = getOrigin(theObj, &originOffset))) {
    theCell = (Object **)((long)theObj + originOffset);
    Claim(!inProxy((long)*theCell), "Persistent object with proxy origin\n");
  }
}

static void checkPersistentObject(Object *theObj, void *generic)
{
  if (inProxy(theObj -> GCAttr)) {
    void *dummy;
    static u_long id, offset;
    
    getProxyAttributes(theObj -> GCAttr, 
		       &dummy,
		       &id,
		       &offset);
    
    if (lookUpObject(dummy, id, offset) == theObj) {
      objectAction = checkPersistentOrigin;

      scanObject(theObj,
		 CheckPersistentCell,
		 TRUE);
      
      objectAction = NULL;
    } else {
      fprintf(output, "checkPersistentAOA: theObj -> GCAttr is *not* a self reference\n");
      Illegal();
      BetaExit(1);
    }
  } else {
    fprintf(output, "checkPersistentAOA: theObj -> GCAttr is *not* a proxy\n");
    Illegal();
    BetaExit(1);
  }
}

void checkPersistentAOA(void) 
{
  foreachObjectInBlocks(AOAPersistentBaseBlock,
			checkPersistentObject,
			NULL);
}

static void checkPersistentObjectInAOAAfterIOA(Object *theObj, void *generic) 
{ 
  if (inProxy(theObj -> GCAttr)) {
    void *dummy;
    static u_long id, offset;
    
    getProxyAttributes(theObj -> GCAttr, 
		       &dummy,
		       &id,
		       &offset);
    
    if (lookUpObject(dummy, id, offset) == theObj) {
      objectAction = checkPersistentOrigin;
      scanObject(theObj,
		 CheckPersistentCellAfterIOA,
		 TRUE);
      objectAction = NULL;
    } else {
      fprintf(output, "checkPersistentAOA: theObj -> GCAttr is *not* a self reference\n");
      Illegal();
      BetaExit(1);
    }
  } else {
    fprintf(output, "checkPersistentAOA: theObj -> GCAttr is *not* a proxy\n");
    Illegal();
    BetaExit(1);
  }
}

void checkPersistentAOAAfterIOA(void) 
{
  foreachObjectInBlocks(AOAPersistentBaseBlock,
			checkPersistentObjectInAOAAfterIOA,
			NULL);
}

#endif /* RTDEBUG */

#ifdef RTINFO
void showPersistenceStatistics(void) {
  fprintf(output, "[Persistence statistics:\n");
  fprintf(output, "  numPersistentBlocks = 0x%X\n", (int)numPersistentBlocks);
  fprintf(output, "  numObjects          = 0x%X\n", (int)numObjects);
  fprintf(output, "  sizeOfObjects       = 0x%X bytes]\n", (int)sizeOfObjects);
}
#endif /* RTINFO */

void dumpObject(long obj) 
{
  USE();
}

#endif /* PERSIST */
