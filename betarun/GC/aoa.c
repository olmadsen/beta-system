/*
 * BETA RUNTIME SYSTEM, Copyright (C) 1990-98 Mjolner Informatics Aps.
 * aoa.c
 * by Stephan Erbs Korsholm and Morten Grouleff.
 */
#include "beta.h"

#define REP ((ObjectRep *)theObj)

/* LOCAL FUNCTIONS */
static long AllocateBaseBlock(void);
static void AOANewBlock(long newBlockSize);
static void AOAMaybeNewBlock(long minNewBlockSize);
#ifdef RTDEBUG
static void AOACheckObjectRefSpecial(REFERENCEACTIONARGSTYPE);
#endif /* RTDEBUG */

/* LOCAL VARIABLES */
static long totalFree = 0;
static long totalAOASize = 0;

/* tempAOArootsAlloc:
 *  Not enough room for the AOAroots table in ToSpace.
 *  Instead allocate offline and copy existing part of table over
 */
void tempAOArootsAlloc(void)
{
  long * oldPtr;        /* start of old table */
  long * oldlimitPtr;   /* points to end of old table */
  long size;
    
  if (tempAOAroots) {
    Claim(AOArootsPtr == tempAOAroots, "AOArootsPtr == tempAOAroots");
    oldPtr = AOArootsPtr;
    oldlimitPtr = AOArootsLimit;
    size = 2 * ((long)oldlimitPtr - (long)oldPtr);
        
    MCHECK();
        
    if (!(tempAOAroots = (long *) MALLOC(size))) {
      char buf[512];
      sprintf(buf, "Could not allocate temporary AOAroots table.");
#ifdef MAC
      EnlargeMacHeap(buf);
#else
      Notify(buf);
#endif
      BetaExit(1);
    } 
    AOArootsLimit = (long *) ((long)tempAOAroots + size);
    AOArootsPtr = AOArootsLimit; /* end of new table */
    INFO_IOA(fprintf(output, 
		     "\nReallocated temporary AOAroots table: %dKb, ",
		     (int)size/1024
		     ));
    DEBUG_IOA(fprintf(output, " [0x%x] ", (int)tempAOAroots));
        
    MCHECK();
    /* Copy old table backwards */
    while(oldlimitPtr > oldPtr) *--AOArootsPtr = *--oldlimitPtr; 
    MCHECK();
    FREE(oldPtr);
  } else {
    oldPtr = AOArootsPtr;
    oldlimitPtr = ToSpaceLimit; 
    size = 2 * ((long)oldlimitPtr - (long)oldPtr);
    if (size < IOASize) {
      size = IOASize;
    }
        
    MCHECK();
    if (!(tempAOAroots = (long *) MALLOC(size))) {
      char buf[512];
      sprintf(buf, "Could not allocate temporary AOAroots table.");
#ifdef MAC
      EnlargeMacHeap(buf);
#else
      Notify(buf);
#endif
      BetaExit(1);
    } 
    AOArootsLimit = (long *) ((long)tempAOAroots + size);
    INFO_IOA(fprintf(output, 
		     "\nallocated temporary AOAroots table: %dKb, ",
		     (int)size/1024
		     ));
    DEBUG_IOA(fprintf(output, " [0x%x] ", (int)tempAOAroots));
    oldPtr = AOArootsPtr; /* start of old table */
    AOArootsPtr = AOArootsLimit; /* end of new table */
        
    MCHECK();
    /* Copy old table backwards */
    while(oldlimitPtr > oldPtr) *--AOArootsPtr = *--oldlimitPtr; 
    MCHECK();
  }
}

void tempAOArootsFree(void)
{
#ifdef RTDEBUG
  long roots = (long)tempAOAroots;
  Claim(tempAOAroots!=NULL, "tempAOArootsFree: tempAOAroots allocated");
#endif
  MCHECK();
  FREE(tempAOAroots);
  MCHECK();
  tempAOAroots = NULL;
  INFO_IOA(fprintf(output, "freed temporary AOAroots table\n"));
  DEBUG_IOA(fprintf(output, " [0x%x]", (int)roots));
}


static void AOANewBlock(long newBlockSize) 
{
  Block * newblock;
  if (newBlockSize < totalAOASize/10) {
    /* Expand at least 10 percent each time.
     * This makes blocks bigger, which decreases fragmentation.
     */
    newBlockSize = totalAOASize/10;
  }
  newBlockSize = ObjectAlign(newBlockSize);
  if ((newblock = newBlock(newBlockSize))) {
    totalFree += newBlockSize;
    totalAOASize += newBlockSize;
        
    AOABlocks++;
    AOATopBlock -> next = newblock;
    AOATopBlock = newblock;
    /* Insert the new block in the freelist */
    AOAInsertFreeBlock((char *)AOATopBlock -> top, newBlockSize);
    INFO_AOA({
      fprintf(output,"Allocated new block of 0x%0X bytes\n", (int)newBlockSize);
      fflush(output);
    });
  } else {
    DEBUG_CODE(fprintf(output,"MallocExhausted\n"));
    INFO_AOA(fprintf(output,"MallocExhausted\n"));
    MallocExhausted = TRUE;
  }
}

static void AOAMaybeNewBlock(long minNewBlockSize) 
{
  long newBlockSize = minNewBlockSize;
  if (minNewBlockSize>0 && minNewBlockSize<AOABlockSize) {
    newBlockSize = AOABlockSize;
  }
  if (newBlockSize < AOAMinFree-totalFree) {
    newBlockSize = AOAMinFree-totalFree;
  }
  while (((totalFree+newBlockSize)/((totalAOASize+newBlockSize)/100) 
	  < AOAPercentage)) {
    newBlockSize += AOABlockSize;
  }
  if (newBlockSize >= AOABlockSize) {
    AOANewBlock(newBlockSize);
  }
}

/* AllocateBaseBlock:
 * Some of The functionality has been taken out of 'AOAallocate below
 * and put in a function by itself. This function is only called the
 * first time around where it allocates the first block in AOA. The
 * jump to this code is very rarely taken. In shuch cases it improves
 * both performance and readabillity to put such code in a function by
 * itself.
 */

static long AllocateBaseBlock(void)
{
  if( MallocExhausted || (AOABlockSize == 0) ) return 0;
  /* Check if the AOAtoIOAtable is allocated. If not then allocate it. */
  if( AOAtoIOAtable == 0 ) 
    if( AOAtoIOAalloc() == 0 ){
      MallocExhausted = TRUE;
      INFO_AOA( fprintf(output,
			"#(AOA: AOAtoIOAtable allocation %d failed!.)\n",
			(int)AOAtoIOAtableSize));
      return 1;
    }
  /* Try to allocate a new AOA block. */
  if( (AOABaseBlock = newBlock(AOABlockSize)) ){
    INFO_AOA( fprintf(output, "#(AOA: new block allocated %dKb.)\n",
		      (int)AOABlockSize/Kb));
    AOATopBlock  = AOABaseBlock;
    AOABlocks++;
    totalFree += AOABlockSize;
    totalAOASize += AOABlockSize;
        
    /* Insert the new block in the freelist */
    AOAInsertFreeBlock((char *)AOATopBlock -> top, AOABlockSize);
    INFO_HEAP_USAGE(PrintHeapUsage("after new AOA block"));
  }else{
    MallocExhausted = TRUE;
    INFO_AOA( fprintf(output, "#(AOA: block allocation failed %dKb.)\n",
		      (int)AOABlockSize/Kb));
    return 1;
  }
  return 0;
}

/* AOAallocate allocate 'size' number of bytes in the Adult object area.
 * If the allocation succeeds the function returns a reference to the allocated
 * object, 0 otherwise.  */
Object *AOAallocate(long numbytes)
{
  Object *newObj;
    
  Claim(numbytes > 0, "AOAallocate: numbytes > 0");
  STAT_AOA(fprintf(output,"#(AOAallocate(%d))", (int)numbytes));
   
  /* Try to find a chunk of memory in the freelist */
  newObj = AOAAllocateFromFreeList(numbytes);
  if (newObj) {
    totalFree -= numbytes;
    newObj->GCAttr = DEADOBJECT;
        
    if ((totalFree/(totalAOASize/100) < AOAPercentage) ||
	(totalFree < AOAMinFree)) {
      AOANeedCompaction = TRUE;
    }
    return newObj;
        
  }

  if (AOABaseBlock == 0) {
    if (AllocateBaseBlock()) {
      INFO_AOA({
	fprintf(output,"Could not allocate AOABaseBlock\n");
	fflush(output);
	  });

      return 0;
    }
    INFO_AOA(fprintf(output,"Allocated AOABaseBlock\n"));
    return AOAallocate(numbytes);
  } 

  /* IOA/NewCopyObject handles that we return 0
   * by just moving the object to ToSpace once more.
   */
  if (IOAActive && IOALooksFullCount==0) {
    AOANeedCompaction = TRUE;
    return 0;
  }

  /* Only get here is caller cannot handle a NULL result.
   * We add a new block and indicate that we want an AOAGC ASAP 
   */
  
  STAT_AOA(fprintf(output,"Could not allocate 0x%0X bytes, "
		   "allocating new block now\n"
		   "and requesting AOAGc from next IOAGc.\n",
		   (int)numbytes));
  AOAMaybeNewBlock(numbytes);
  AOANeedCompaction = TRUE;
  
  return AOAallocate(numbytes);
}

#ifdef NEWRUN
#define AOA_ALLOC_PARAMS long numbytes, long *SP
#else
#define AOA_ALLOC_PARAMS long numbytes
#endif 

Object *AOAalloc(AOA_ALLOC_PARAMS)
{
  Object *theObj;

  MT_CODE(mutex_lock(&aoa_lock));

  DEBUG_CODE(NumAOAAlloc++);
  theObj = AOAallocate(numbytes);
  if (theObj) {
    MT_CODE(mutex_unlock(&aoa_lock));
    return theObj;
  }

  fprintf(output, "AOAalloc: cannot allocate 0x%x bytes\n", (int)numbytes);
  BetaExit(1);
  return NULL;
}

Object *AOAcalloc(AOA_ALLOC_PARAMS)
{
  Object *theObj;
  long gca;
#ifdef NEWRUN
  theObj = AOAalloc(numbytes, SP);
#else
  theObj = AOAalloc(numbytes);
#endif
  /* No need to check theObj!=0 since this is done in AOAalloc */
  gca = theObj->GCAttr;
  memset(theObj, 0, numbytes);
  theObj->GCAttr = gca;
  return theObj;
}

/* CopyObjectToAOA:
 *  move an object to AOA and return the address of the new location
 *  If the allocation in AOA failed the function returns 0;
 */
Object *CopyObjectToAOA(Object *theObj)
{
  Object * newObj;
  long        size;
  register long * src;
  register long * dst;
  register long * theEnd;
  
  size = 4*ObjectSize(theObj); 
  Claim(ObjectSize(theObj) > 0, "#ToAOA: ObjectSize(theObj) > 0");
  Claim((size&7)==0, "#ToAOA: (size&7)==0 ");
       
  if( (newObj = AOAallocate( size)) == 0 ) return 0;
  
  theEnd = (long *) (((long) newObj) + size); 
  
  src = (long *) theObj; dst = (long *) newObj; 
  while( dst < theEnd) *dst++ = *src++; 
  
  if (!HandledInAOAHead) {
    /* Start new list */
    HandledInAOAHead = newObj;
    HandledInAOATail = newObj;
  } else {
    /* append new object to list */
    HandledInAOATail -> GCAttr = (long) newObj;
    HandledInAOATail = newObj;
  }
  newObj->GCAttr = LISTEND;
    
  /* Set the forward reference in theObj to newObj */
  theObj->GCAttr = (long) newObj;
  
  DEBUG_AOA(AOAcopied += size);

  DEBUG_STACKOBJ({ 
    if (isStackObject(theObj)) {
      fprintf(output, 
	      "CopyObjectToAOA: moved StackObject from 0x%0x to 0x%x\n",
	      (int)theObj, (int)newObj);
    }
  });
  
  /* Return the new object in AOA */
  return newObj;
}


long sizeOfAOA(void)
{
  Block *current;
  long numbytes = 0;
    
  current = AOABaseBlock;
    
  while(current) {
    Claim(BlockStart(current)==current->top, 
	  "BlockStart(current)==current->top");
    numbytes += BlockNumBytes(current);
    current = current->next;
  }

  return numbytes;
}

/*
 *  AOAGc: perform a mark/sweep garbagecollection on the AOA heap.
 *  Should be called after IOAGc when AOANeedCompaction == TRUE;
 */

void AOAGc()
{
  long *pointer;
  long * cellptr;
  Object * target;
  Object * root;
  Block * currentBlock;

  NumAOAGc++;
    
  INFO_AOA(fprintf(output,"#(AOA-%lu:", NumAOAGc));
  AOAFreeListAnalyze1();
  STAT_AOA(AOADisplayFreeList());
    

  /* Based on the AOARoots all objects reachable from those roots
   * are collected in a linked list. After that AOA is scanned and
   * objects not in the list are considered dead and inserted in the
   * free lists.
   */
    
  /* When collecting the list of live objects, only objects in AOA
   * are considered.
   */
    
  pointer = AOArootsPtr;
    
  root = NULL;

  /* Clear AOAtoIOAtable. It will be rebuild by 
   * extend- and initialCollectList. */
  AOAtoIOAClear();
    
  DEBUG_AOA(fprintf(output,"[Marking all Live Objects in AOA]\n"));
  if (pointer < AOArootsLimit) {
    /* Make cellptr point to the cell that contains an AOAroot. */
    cellptr = (long*)(*pointer & ~1);
        
    /* Make target point to the actual object in AOA. */
    root = target = (Object *)*cellptr;
        
    /* It is necessary to call a special collecter the first
     * time.
     */
    initialCollectList(target, prependToListInAOA);
        
    pointer++;
        
    /* Afterwards we call extendCollectList. */
    while (pointer < AOArootsLimit) {
      cellptr = (long*)(*pointer & ~1);
      target = (Object *)*cellptr;
      extendCollectList(target, prependToListInAOA);
      pointer++;
    }
  }
    
  /* The object pointed to by the first entry in AOArootsPtr is now
   * the head of the linked list of all live objects in AOA.
   */
    
  /* Scan AOA and insert dead objects in the freelist */
    
  /* Clear the free lists */
  DEBUG_AOA(fprintf(output,"[AOACleanFreeList]\n"));
  AOACleanFreeList();

  /* All space is alive until proven dead */
  totalFree = 0;

  STAT_AOA(fprintf(output,"[Blocks: freed/free/total:\n"));

  /* Scan each block in AOA. */
  LVRSizeSum = 0;
  currentBlock = AOABaseBlock;
  while (currentBlock) {
    long freeInBlock;
    Claim(BlockStart(currentBlock)==currentBlock->top, 
	  "BlockStart(currentBlock)==currentBlock->top");
    /* Then each chunk in the block is examined */

    freeInBlock = AOAScanMemoryArea(currentBlock -> top, 
				    currentBlock -> limit);
    totalFree += freeInBlock;
        
    STAT_AOA(fprintf(output,"[0x%08X/0x%08X/0x%08X] ",
		     (int)collectedMem, (int)freeInBlock, (int)BlockNumBytes(currentBlock)));
        
    currentBlock = currentBlock -> next;
  }
  
  STAT_AOA(fprintf(output,"]\n"));

  /* Make sure there is sufficient free memory */
  AOAMaybeNewBlock(0);
    
  INFO_AOA(fprintf(output,"AOAGC finished, free space 0x%X bytes\n",
		   (int)totalFree));
  STAT_AOA(AOADisplayFreeList());
      
  /* Now all blocks have been scanned and all dead objects inserted
   * in the freelists. 
   * Analyze freelists to determine the strategy for allocation. 
   */
      
  AOAFreeListAnalyze2();
  STAT_AOA({
    fprintf(output, "AOA-%d aoasize=0x%08X aoafree=0x%08X "
	    "VR=0x%08X objects=0x%08X\n",
	    (int)NumAOAGc, (int)totalAOASize, (int)totalFree,
	    (int)LVRSizeSum,  (int)objectsInAOA);
    fprintf(output, "AOA-%d)\n", (int)NumAOAGc);
    fflush(output);
  });

  AOANeedCompaction = FALSE;
}

    
#ifdef RTDEBUG
static void CheckAOACell(Object **theCell,Object *theObj)
{
  DEBUG_CODE(if (!CheckHeap) Ck(theObj));
  AOACheckReference(theCell);
}

Object * lastAOAObj=0;

static FILE *dump_aoa_file=NULL;
#define AOA_DUMP(code) { code; }
#define AOA_DUMP_TEXT(text) \
if (dump_aoa){ fprintf(dump_aoa_file, "%s", text); }
#define AOA_DUMP_LONG(num) \
if (dump_aoa){ fprintf(dump_aoa_file, "0x%08x", (int)num); }
#define AOA_DUMP_INT(num) \
if (dump_aoa){ fprintf(dump_aoa_file, "%d", (int)num); }

/* AOACheck: Consistency check on entire AOA area */
void AOACheck()
{
  Block *  theBlock  = AOABaseBlock;
  Object * theObj;
  long        theObjectSize;

  if (dump_aoa) {
    char name[16];
    if (dump_aoa_file) {
      fclose(dump_aoa_file);
    }
    sprintf(name,"aoa_dump%04d", (int)NumAOAGc);
    dump_aoa_file = fopen(name, "w+");
    if (!dump_aoa_file) {
      fprintf(output, "failed to open aoa_dump_file\n");
      dump_aoa=0;
    } else {
      AOA_DUMP_TEXT("========AOA-");
      AOA_DUMP_LONG(NumAOAGc);
      AOA_DUMP_TEXT("========\n");
      AOA_DUMP_TEXT(" Object   : Proto    : size     :GCAttr: Name :\n");
    }
  }  

  lastAOAObj=0;
  while( theBlock ){
    Claim(BlockStart(theBlock)==theBlock->top, 
	  "BlockStart(theBlock)==theBlock->top");
    theObj = (Object *) BlockStart(theBlock);
    while( (long *) theObj < theBlock->top ){
      theObjectSize = 4*ObjectSize(theObj);
      Claim((theObjectSize&7)==0, "#AOACheck: (TheObjectSize&7)==0 ");
      Claim(ObjectSize(theObj) > 0, "#AOACheck: ObjectSize(theObj) > 0");
      AOACheckObject( theObj);
      lastAOAObj=theObj;
      theObj = (Object *) Offset( theObj, theObjectSize);
    }
    theBlock = theBlock->next;
  }
  dump_aoa = 0;
} 

/* AOACheckObject: Consistency check on AOA object */
void AOACheckObject(Object *theObj)
{ 
  ProtoType * theProto;
  
  theProto = GETPROTO(theObj);

#ifdef MT
  /* The way part objects are allocated in V-entries
   * may leave part objects with uninitialized prototypes.
   */
  if (!theProto) return;
#endif

  Claim(IsPrototypeOfProcess((long)theProto), "IsPrototypeOfProcess(theProto)");

  AOA_DUMP_TEXT(":");
  AOA_DUMP_LONG(theObj);
  AOA_DUMP_TEXT(":");
  AOA_DUMP_LONG(theProto);
  AOA_DUMP_TEXT(":");
  AOA_DUMP_LONG(ObjectSize(theObj));
  AOA_DUMP_TEXT(":");
  AOA_DUMP_INT(theObj->GCAttr);
  AOA_DUMP_TEXT(":");
  AOA_DUMP_TEXT(ProtoTypeName(theProto));
  if (theProto==ComponentPTValue){
    AOA_DUMP_TEXT(" ");
    AOA_DUMP_TEXT(ProtoTypeName(GETPROTO(ComponentItem(theObj))));
  }
  AOA_DUMP_TEXT(":\n");
  
  scanObject(theObj,
	     AOACheckReference,
	     TRUE);
}

/* AOACheckReference: Consistency check on AOA reference */
void AOACheckReference(Object **theCell)
{
  long i; long * pointer = BlockStart( AOAtoIOAtable);
  long found = FALSE;

#ifdef RTLAZY
  if (isLazyRef(*theCell)) {
    int i;
    int found=0;
    for (i=0; i<negAOAsize; i++) {
      if ((*(long*)negAOArefs[i])==(long)*theCell){
	found=1; break;
      }
    }
    if (!found){
      fprintf(output, 
	      "Dangler in AOA, but NOT in negAOArefs table: 0x%x: %d\n", 
	      (int)theCell, 
	      (int)*theCell);
      Illegal();
    }
    return;
  }
#endif
  if (*theCell) {
    Claim(inAOA(*theCell) || inIOA(*theCell),
	  "AOACheckReference: *theCell in IOA, AOA");
    if (inIOA( *theCell)) {
      IOACheckObject( *theCell);
      for(i=0; (i < AOAtoIOAtableSize) && (!found); i++){
	if( *pointer ) found = (*pointer == (long) theCell);
	pointer++;
      }
      if (!found){
	char buf[512];
	sprintf(buf, 
		"AOACheckReference: *theCell [*(0x%x)] in IOA but not in AOAtoIOAtable",
		(int)theCell);
	Claim( found, buf);
      }
    }
  }
}

/* */
static void AOACheckObjectRefSpecial(REFERENCEACTIONARGSTYPE)
{
  return;
}

/* AOACheckObjectSpecial: Weak consistency check on AOA object */
void AOACheckObjectSpecial(Object *theObj)
{
  ProtoType * theProto;
  
  theProto = GETPROTO(theObj);
  
#ifdef MT
  /* The way part objects are allocated in V-entries
   * may leave part objects with uninitialized prototypes.
   */
  if (!theProto) return;
#endif
  
  Claim(IsPrototypeOfProcess((long)theProto), "IsPrototypeOfProcess(theProto)");

  scanObject(theObj,
	     AOACheckObjectRefSpecial,
	     TRUE);
  
}

#endif

/* Functions below are used to build a linked list of all objects
 * reachable from some root in the GCfield of the objects.  
 */

static Object * head;        /* Head of list build by collectList */
static Object * insertPoint; /* insertpoint of list build by collectList */
static Object * tail;        /* Tail of list build by collectList */
static long totalsize;

/* static */ void (*StackRefAction)(REFERENCEACTIONARGSTYPE) = NULL;
void StackRefActionWrapper(Object **theCell,Object *theObj)
{
  if (theObj
      && inBetaHeap(theObj)
      && isObject(theObj)) {
    StackRefAction(theCell);
  }
}

Object * getRealObject(Object * obj)
{
  long Distance;
  Object * AutObj;
  if (obj -> GCAttr < 0) {
    GetDistanceToEnclosingObject(obj, Distance);
    AutObj = (Object *) Offset(obj, Distance);
    return AutObj;
  } else {
    return obj;
  }
}

/* Checks whether an objects is in the list. This functions is only
   used for debugging purposes. */

void checkNotInList(Object *target) 
{
  Object *current;
  
  current = head;
  
  while ((long) current != LISTEND) {
    if (current == target) {
      fprintf(output, "checkNotInList: 0x%X is in list!\n", (int)(target));
    }
    current = (Object *)(current -> GCAttr);
  }
}
    
/* Append objects to the list regardless of where they are */
void appendToList(Object *target)
{
  long GCAttribute;
    
  /* We are about to append 'target' to the list. We will only do so
   * if target points to an object that is not already part of the
   * list. Whether this is the case can be inferred by looking at
   * the GC-Attribute. The GCAttribute can be,

   (1) Before AOAGc the value of the GCAttribute of all objects that
   is reachable should be DEADOBJECT. This goes for all autonomous
   objects, but not staticly inlined objects. The GCAttr of staticly
   inlined objects contains the offset to the enclosing object. This
   offset is a negative offset allways.

   (2) During AOAGc all live objects are linked together in their GC
   attribute. Of course only autonomous objects may be linked
   together. Thus if we have a reference to a staticly inlined
   object we should not link this object into the list but link the
   enclosing object into the list.

   */

  /* Since this is a highly central function for the GC'er, we do
     not check for NULL refrences in the normal case. It is the
     responsibillity of the caller. */

  GCAttribute = target -> GCAttr;
    
  if (GCAttribute == DEADOBJECT) {
    /* Normal case. All objects in AOA are initially dead and
     * not linked into the list.
     */
#ifdef RTDEBUG
    if (tail->GCAttr != LISTEND) {
      fprintf(output, 
	      "appendToList: List is not properly terminated!\n");
      Illegal();
    }
#endif
    tail->GCAttr = (long) target;
    tail=target;
    tail->GCAttr = LISTEND;
    totalsize += 4 * ObjectSize(target);
  } else if (GCAttribute == LISTEND) {
    /* target is already in the list (it is the tail actually) */
    ;
  } else if (GCAttribute < 0) {
    /* We have encountered a staticly inlined object or a component. */
    appendToList(getRealObject(target));
  } else {
    /* 'target' has a reference in it's GCField. 
     * Thus it is allready in the list. */
#ifdef RTDEBUG
    if ((GCAttribute == FREECHUNK) ||
	(GCAttribute == (long) NULL)) {
      fprintf(output,"appendToList: UNexpected GCAttribute\n");
      Illegal();
    }
#endif
  }
}

/* Append objects to the list not including objects in IOA */
void appendToListNoIOA(REFERENCEACTIONARGSTYPE)
{
#ifdef RTDEBUG
  if (!*theCell) {
    fprintf(output,"appendToListNoIOA: Target is NULL!\n");
    Illegal();
  }
#endif
    
  if (!inIOA(*theCell)) {
    appendToList(*theCell);
  }
}

/* Append objects to the list including only objects in AOA. */
void appendToListInAOA(REFERENCEACTIONARGSTYPE)
{
  Claim(inAOA(theCell), "appendToListInAOA:inAOA(theCell)");
  Claim((int)*theCell, "appendToListInAOA:*theCell");
  Claim(!inIOA(*theCell), "!inIOA(*theCell)");

  if (inToSpace(*theCell)) {
    /* insert theCell in AOAtoIOAtable. */
    AOAtoIOAInsert(theCell);
  } else {
    /* The cell is assumed to be in AOA if not in ToSpace. 
     * There should be nothing in IOA, as IOAGc has just completed,
     * and the semispaces have not been swapped yet.
     */
    Claim(inAOA(*theCell), "inAOA(*theCell)");
    appendToList(*theCell);
  }
}

/* Prepend objects to the list regardless of where they are */
void prependToList(Object *target)
{
  long GCAttribute;
    
  /* We are about to prepend 'target' to the list. We will only do so
   * if target points to an object that is not already part of the
   * list. Whether this is the case can be inferred by looking at
   * the GC-Attribute. The GCAttribute can be,

   (1) Before AOAGc the value of the GCAttribute of all objects that
   is reachable should be DEADOBJECT. This goes for all autonomous
   objects, but not staticly inlined objects. The GCAttr of staticly
   inlined objects contains the offset to the enclosing object. This
   offset is a negative offset allways.

   (2) During AOAGc all live objects are linked together in their GC
   attribute. Of course only autonomous objects may be linked
   together. Thus if we have a reference to a staticly inlined
   object we should not link this object into the list but link the
   enclosing object into the list.

   */

  /* Since this is a highly central function for the GC'er, we do
     not check for NULL refrences in the normal case. It is the
     responsibillity of the caller. */

  GCAttribute = target -> GCAttr;
    
  if (GCAttribute == DEADOBJECT) {
    /* Normal case. All objects in AOA are initially dead and
     * not linked into the list.
     */
    target->GCAttr = insertPoint->GCAttr;
    insertPoint->GCAttr = (long)target;
    totalsize += 4 * ObjectSize(target);
  } else if (GCAttribute == LISTEND) {
    /* target is already in the list (it is the tail actually) */
    ;
  } else if (GCAttribute < 0) {
    /* We have encountered a staticly inlined object or a component. */
    prependToList(getRealObject(target));
  } else {
    /* 'target' has a reference in it's GCField. 
     * Thus it is already in the list. */
#ifdef RTDEBUG
    if ((GCAttribute == FREECHUNK) ||
	(GCAttribute == (long) NULL)) {
      fprintf(output,"prependToList: Unexpected GCAttribute\n");
      Illegal();
    }
#endif
  }
}

/* Prepend objects to the list not including objects in IOA */
void prependToListNoIOA(REFERENCEACTIONARGSTYPE)
{
#ifdef RTDEBUG
  if (!*theCell) {
    fprintf(output,"prependToListNoIOA: Target is NULL!\n");
    Illegal();
  }
#endif
    
  if (!inIOA(*theCell)) {
    prependToList(*theCell);
  }
}

/* Prepend objects to the list including only objects in AOA. */
void prependToListInAOA(REFERENCEACTIONARGSTYPE)
{
  Claim(inAOA(theCell), "prependToListInAOA:inAOA(theCell)");
  Claim((int)*theCell, "prependToListInAOA:*theCell");
  Claim(!inIOA(*theCell), "!inIOA(*theCell)");
  
  if (!inToSpace(*theCell)) {
    if (!inProxy((long)*theCell)) {
      if (!inProxy((*theCell) -> GCAttr)) {
	/* Follow */
	Claim(inAOA(*theCell), "inAOA(*theCell)");
	prependToList(*theCell);
	
      } else {
	/* Redirect */
	*theCell = (Object *)((*theCell) -> GCAttr);
	proxyAlive(theCell);
	
      }
    } else {
      proxyAlive(theCell);
      
    }
  } else {
    /* insert theCell in AOAtoIOAtable. */
    AOAtoIOAInsert(theCell);
  }
}

void initialCollectList(Object * root,
                        void (*referenceAction)(REFERENCEACTIONARGSTYPE))
{
  /* If root is a pointer to a staticly inlined part object, then
   * 'getRealObject' will return the enclosing object.
   */

  root = getRealObject(root);
    
  /* If called with root=NULL, just initialize to empty list */
  if (!root) {
    totalsize = 0;
    head = tail = (Object *)LISTEND;
    insertPoint = head;
    return;
  }

  Claim(inAOA(root), "inAOA(root)");

  /* set_start_time("initialCollectList"); */
    
  /* point to self to end list.
   * Cannot be zero-term, as that would make it look unmarked
   * for the scanner.
   */
  /* This is not the case anymore, as append explicitly checks
   * that tail is not reinserted, tail=root until root->GCAttr is set.
   * root->GCAttr = (long)root; 
   */
    
  /* Tail is where new objects are appended to the list.
   * insertPoint is where new objects are inserted in the list.
   */
  tail = root;
  insertPoint = root;
  tail -> GCAttr = LISTEND;

  /* Head is the first object in the list. All objects in the
   * list may be reached through head.  
   */
  head = root;
    
  /* There are no objects in the list yet. */
  totalsize = 0;
    
  while (1) {
    scanObject(insertPoint, referenceAction, TRUE);
    if (!isEnd(insertPoint->GCAttr)) {
      insertPoint=(Object*)(insertPoint->GCAttr);
    } else {
      break;
    }
  }
}

void extendCollectList(Object *root,
                       void (*referenceAction)(REFERENCEACTIONARGSTYPE))
{
  /* set_start_time("extendCollectList"); */
    
  Claim((int)tail, "extendCollectList without initialCollectList");

  Claim(inAOA(root), "inAOA(root)");
  prependToList(root);
    
  /* root has now been prepended to the list, if not already
   * there.
   */
  
  if (!isEnd(insertPoint->GCAttr)) {
    insertPoint=(Object*)(insertPoint->GCAttr);
    while (1) {
      scanObject(insertPoint, referenceAction, TRUE);
      if (!isEnd(insertPoint->GCAttr)) {
	insertPoint=(Object*)(insertPoint->GCAttr);
      } else {
	break;
      }
    }
  }
}

void scanList(Object * root, void (foreach)(Object * current))
{
  Object * cur;
  Object * next;
    
  cur = root;
  while (!isEnd((long)cur)) {
    next = (Object *)(cur->GCAttr);
    foreach(cur);
    cur = next;
  }
}

/* scanObject: */
void scanObject(Object *obj,
		void (*referenceAction)(REFERENCEACTIONARGSTYPE),
		int doPartObjects)
{
  ProtoType * theProto;
    
  theProto = GETPROTO(obj);
  Claim(IsPrototypeOfProcess((long)theProto), "IsPrototypeOfProcess(theProto)");
  if (!isSpecialProtoType(theProto)) {
    GCEntry *tab =
      (GCEntry *) ((char *) theProto + theProto->GCTabOff);
    short * refs_ofs;
        
    /* Handle all the static objects. 
     *
     * The static table, tab[0], tab[1], ..., 0,
     * contains all static objects on all levels.
     * We call recursively on every one, is we're told
     * to do so. When we do so, we make sure that there is no 
     * further recursion going on.
     */
        
    if (doPartObjects) {
      for (;tab->StaticOff; ++tab) {
	scanObject((Object *)((long *)obj + tab->StaticOff),
		   referenceAction, FALSE);
      }
    }
    else {
      for (;tab->StaticOff; ++tab) {
	;
      }
    }
        
    /* Handle all the non-static references in the object. */
    for (refs_ofs = (short *)&tab->StaticOff+1; *refs_ofs; refs_ofs++) {
      long offset  = (*refs_ofs) & ~3;
      long *pointer = (long *)((long)obj + offset);
      /* long refType = (*refs_ofs) & 3; */
      /* sbrandt 24/1/1994: 2 least significant bits in prototype 
       * dynamic offset table masked out. As offsets in this table are
       * always multiples of 4, these bits may be used to distinguish
       * different reference types. */ 
      if (*pointer) {
	referenceAction((Object **)pointer);
      }
    }
  } else {
    switch (SwitchProto(theProto)) {
    case SwitchProto(ByteRepPTValue):
    case SwitchProto(ShortRepPTValue):
    case SwitchProto(DoubleRepPTValue):
    case SwitchProto(LongRepPTValue): 
      break; /* No references in this type of object, so do nothing */
              
    case SwitchProto(DynItemRepPTValue):
    case SwitchProto(DynCompRepPTValue): {
      long *pointer;
      long size, index;
              
      /* Process iOrigin */
      referenceAction(&(((ObjectRep *)obj) -> iOrigin));
              
      /* Process rest of repetition */
      size = ((ObjectRep *)obj)->HighBorder;
      pointer = (long *)&((ObjectRep *)obj)->Body[0];
              
      for (index=0; index<size; index++) {
	if (*pointer) {
	  referenceAction((Object **)pointer);
	}
	pointer++;
      }
      break;
    }
          
    case SwitchProto(RefRepPTValue): 
      /* Scan the repetition and apply referenceAction */
      {
	long *pointer;
	long offset, offsetTop;
              
	offset =  (char*)(&((RefRep*)(obj))->Body[0]) - (char*)obj;
	offsetTop = offset + 4 * ((RefRep*)(obj))->HighBorder;
              
	while (offset < offsetTop) {
	  pointer = (long *)((long)obj + offset);
	  if (*pointer) {
	    referenceAction((Object **)pointer);
	  }
	  offset += 4;
	}
	break;
      }
          
    case SwitchProto(ComponentPTValue):
      {
	Component * theComponent;
              
	theComponent = ((Component*)obj);
	if ((theComponent->StackObj) &&
	    (long)(theComponent->StackObj) != -1) {
	  DEBUG_STACKOBJ({
	    fprintf(output, 
		    "Processing stackobj 0x%08x of component 0x%08x "
		    "with func=0x%08x\n",
		    (int)theComponent->StackObj, (int)theComponent, 
		    (int)referenceAction);
	  });
	  referenceAction((Object **)&(theComponent->StackObj));
	}
	if (theComponent->CallerComp) {
	  referenceAction((Object **)&(theComponent->CallerComp));
	}
	if (theComponent->CallerObj) {
	  referenceAction(&(theComponent->CallerObj));
	}
	scanObject((Object *)ComponentItem( theComponent),
		   referenceAction, TRUE);
	break;
      }
    case SwitchProto(StackObjectPTValue):
      {
	void (*oldStackRefAction)(REFERENCEACTIONARGSTYPE);
	if (StackRefAction) {
	  fprintf(output, 
		  "\n[Note: Recursion in ScanObject on StackObject]\n");
	  if (StackRefAction != referenceAction) {
	    fprintf(output, 
		    "\n[Note: Recursion in ScanObject "
		    "Will change behaviour!!!]\n");
	  }
	}
	oldStackRefAction = StackRefAction;
	StackRefAction = referenceAction;
	ProcessStackObj((StackObject *)obj, StackRefActionWrapper);
	StackRefAction = oldStackRefAction;
      }
    break;
              
    case SwitchProto(StructurePTValue):
      referenceAction(&(((Structure*)(obj))->iOrigin));
      break;
              
    case SwitchProto(DopartObjectPTValue):
      referenceAction(&(((DopartObject *)(obj))->Origin));
      break;
    default:
      Claim( FALSE, "scanObject: theObj must be KNOWN.");
      
    }
  } 
}

ValRep *LVRAAlloc(ProtoType *proto, long range)
{
  ValRep *    newRep;
  long           size;

  Claim(isSpecialProtoType(proto), "isSpecialProtoType(proto)");

  size = DispatchValRepSize(proto, range);
  newRep = (ValRep *) AOAallocate(size);
  SETPROTO(newRep,proto);
  newRep->LowBorder  = 1;
  newRep->HighBorder = range; /* indexes */
  return newRep;
}


/* LVRACAlloc: allocate a Value repetition in the LVRA area 
 * and nullify the BODY of the repetition..
 */
ValRep * LVRACAlloc(ProtoType * proto, long range)     
{
  ValRep * newRep = LVRAAlloc(proto, range);
  if (newRep){
    /* Clear the body of newRep */
    memset(newRep->Body, 0, DispatchValRepBodySize(proto, range));
  }
  return newRep;
}

/* LVRAXAlloc: allocate a Value repetition in the LVRA area 
 * and nullify extension part of the BODY of the repetition
 * (i.e. the elements from ]oldrange..newrange]
 */
ValRep * LVRAXAlloc(ProtoType * proto, long oldrange, long newrange)  
{
  ValRep * newRep = LVRAAlloc(proto, newrange);
  if (newRep && (newrange>oldrange)){
    /* Clear the extension part of the body of newRep */
    long oldbodysize = DispatchValRepBodySize(proto, oldrange);
    long newbodysize = DispatchValRepBodySize(proto, newrange);
    memset((char*)(newRep->Body)+oldbodysize, 
	   0, 
	   newbodysize-oldbodysize);
  }
  return newRep;
}
