#include <sys/types.h>

#include "beta.h"

void lin_dummy() {

#ifdef sparc
  USE();
#endif /* sparc */

}

#ifdef PERSIST

extern void unswizzleOrigins(Block *b);
extern void (*objectAction)(Object *theObj);

/* LOCAL prototypes */

/* LOCAL VARIABLES */
#ifdef RTINFO
u_long numPersistentBlocks;
u_long numObjects;
u_long sizeOfObjects;
#endif /* RTINFO */

static void unmarkOriginAction(Object *theObj);

/* IMPLEMENTATION */

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
  } else {
    proxyAlive(theCell);
  }
}

void bringHomeAction(Object *theObj, void *generic) 
{
  scanObject(theObj,
	     bringHome,
	     TRUE);
}

Object *getOrigin(Object *theObj, long *originOffset) 
{
  ProtoType *theProto;
  Object *origin = NULL;
  
  theProto = GETPROTO(theObj);
  
  Claim(IsPrototypeOfProcess((long)theProto), "IsPrototypeOfProcess(theProto)");
  
  if (!isSpecialProtoType(theProto)) {
    *originOffset = 4 * (long) (theProto -> OriginOff);
    origin = *(Object **)((long) theObj + *originOffset);
    
  } else {
    switch (SwitchProto(theProto)) {
    case SwitchProto(ByteRepPTValue):
    case SwitchProto(ShortRepPTValue):
    case SwitchProto(DoubleRepPTValue):
    case SwitchProto(LongRepPTValue): 
      /* Has no origin ?? */
      *originOffset = -1;
      return NULL;
      break; 
      
    case SwitchProto(DynItemRepPTValue):
    case SwitchProto(DynCompRepPTValue): 
      origin = ((struct _ObjectRep *)theObj)->iOrigin;
      *originOffset = (long)&(((struct _ObjectRep *)theObj)->iOrigin) - (long) theObj;
      break; 
      
    case SwitchProto(RefRepPTValue): 
      /* Has no origin ?? */
      *originOffset = -1;
      return NULL;
      break; 
      
    case SwitchProto(ComponentPTValue):
      /* The origin the component is the origin of the item */
      return getOrigin((Object *)(&(((struct _Component*)theObj)->Body)), originOffset);
      break; 
      
    case SwitchProto(StackObjectPTValue):
      Claim(FALSE,"getOrigin: What is origin of ??");
      break; 
      
    case SwitchProto(StructurePTValue):
      origin = ((struct _Structure *)theObj)->iOrigin;
      *originOffset = (long)&(((struct _Structure *)theObj)->iOrigin) - (long) theObj;
      break;
      
    case SwitchProto(DopartObjectPTValue):
      origin = ((struct _DopartObject *)theObj)->Origin;
      *originOffset = (long)&(((struct _DopartObject *)theObj)->Origin) - (long) theObj;
      break;
      
    default:
      Claim( FALSE, "getOrigin: theObj must be KNOWN.");
    }
  }
  
  return origin;
}

static void unmarkOriginAction(Object *theObj)
{
  Object *origin;
  long GCAttribute;
  long originOffset;
  
  if (!inProxy(theObj -> GCAttr)) {
    /* This object is not persistent. Check that origin is not
       persistent */
    
    if ((origin = getOrigin(theObj, &originOffset))) {
      
      if (inProxy((long) origin)) {
	void *dummy;
	u_long id;
	u_long offset;
	
	getProxyAttributes(*(long *)((long) theObj + originOffset), &dummy, &id, &offset);
	
	origin = lookUpObject(dummy, id, offset);
	
	Claim(FALSE, "theObj has origin in persistent object ");
	
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
	      unmarkOriginAction(realOriginObj);
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
	    unmarkOriginAction(realOriginObj);
	  }
	} else {
	  Claim(inArea(AOABaseBlock, realOriginObj), "Object not in AOA ?");
	}
      }
    }
  }
}

static void noReferenceAction(Object ** theCell) 
{
  ;
}

static void scannerWrapper(Object *theObj, void *generic)
{
  
  scanObject(theObj,
	     noReferenceAction,
	     TRUE);
  
}

void _checkpoint(void)
{
  if (0) {
    USE(); /* Not important */
  }
  
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
  
  objectAction = unmarkOriginAction;

  foreachObjectInIOA(scannerWrapper,
		     NULL);
  
  foreachObjectInBlocks(AOABaseBlock,
			scannerWrapper,
			NULL);
  objectAction = NULL;
  
  return;
  
  /* return to BETACODE and do GC. */
}

static void _updateTables(Object **theCell) 
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

#ifdef RTDEBUG
static void checkOriginAction(Object *theObj) 
{
  Object *origin;
  long originOffset;
  
  if ((origin = getOrigin(theObj, &originOffset))) {
    /* Check that origin is not persistent */
    if (inProxy(*(long *)((long) theObj + originOffset))) {
      void *dummy;
      u_long id;
      u_long offset;
      
      getProxyAttributes(*(long *)((long) theObj + originOffset), &dummy, &id, &offset);
      
      origin = lookUpObject(dummy, id, offset);
      
      Claim(FALSE, "origin in persistent object ");
    }
  }
}
#endif /* RTDEBUG */

void _exportPersistentAOABlocks(void) 
{
  Block *current, *next;
  current = AOAPersistentBaseBlock;
  
  DEBUG_PERSISTENCE(objectAction = checkOriginAction;
		    IOACheck();
		    AOACheck();
		    objectAction = NULL);
  
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

void _unpersistifyAOABlocks(void) 
{
  ;
}

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
  
void assignPersistentRef(Object *ref, Object **theCell) 
{
  *theCell = ref;
}

/* Called just before checkpoint */
void _put(Object *theObj, char *name)
{
  void *dummy;
  u_long id;
  u_long offset; 
  
  freeProxySpace();
  forceAOAGC = TRUE;
  
  if (theObj) {
    
    Claim(theObj == getRealObject(theObj), "Cannot but part object");
    theObj = CopyObjectToPersistentAOA(theObj);
    
    getProxyAttributes((long)theObj, &dummy, &id, &offset);
    
    putName(name, dummy, 0, id, offset);
  }

  return;
  
}

void rebuildTableObj(Object *theObj,
		     void *generic)
{
  scanObject(theObj,
	     _updateTables,
	     TRUE);
}

void rebuildAOAtoIOATable(void) 
{
  foreachObjectInBlocks(AOAPersistentBaseBlock,
			rebuildTableObj,
			NULL);
}

#ifdef RTDEBUG

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

void checkPersistentObject(Object *theObj, void *generic)
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

void checkPersistentObjectInAOAAfterIOA(Object *theObj, void *generic) 
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

#ifdef RTINFO
void showPersistenceStatistics(void) {
  fprintf(output, "[Persistence statistics:\n");
  fprintf(output, "  numPersistentBlocks = 0x%X\n", (int)numPersistentBlocks);
  fprintf(output, "  numObjects          = 0x%X\n", (int)numObjects);
  fprintf(output, "  sizeOfObjects       = 0x%X bytes]\n", (int)sizeOfObjects);
}
#endif /* RTINFO */

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

void dumpObject(long obj) 
{
  USE();
}


#endif /* PERSIST */
