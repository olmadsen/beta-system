/*
 * BETA RUNTIME SYSTEM, Copyright (C) 1990-98 Mjolner Informatics Aps.
 * aoa.c
 * by Stephan Erbs Korsholm and Morten Grouleff.
 */
#include "beta.h"

#ifdef PERSIST
#include "PException.h"
#include "objectTable.h"
#include "referenceTable.h"

/* Get definition of ntohl */
#if defined(sun4s) || defined(sgi) || defined(linux)
#include <sys/types.h>
#include <netinet/in.h>
#else
#if defined(nti)
#include "winsock.h"
#else

#ifndef ntohl
#define ntohl(x) x
#endif

#endif
#endif 
#endif /* PERSIST */

#ifdef ALLOC_TRACE
#include "trace-types.h"
#endif

#ifndef MIN
# define MIN(x, y) (((x) < (y)) ? (x) : (y))
# define MAX(x, y) (((x) > (y)) ? (x) : (y))
#endif

/* Policy regarding when to perform a GC rather than extending AOA:
 *
 * AOA may fail in delivering a block upon allocation, if
 * there is no sufficiently large block available. 
 * 1) if AOA is not overfull, do a GC.
 * 2) if the allocation still fails after that, extend AOA sufficiently
 *    and remember that the GC did not free enough space.
 *
 * Policy:
 * 
 * Keep a flag of whether AOA is considered OverFull.
 * Upon failure of an allocation, the action depends on the flag:
 * OverFull==True -> 
 * 	if the heap has been extended enough, do a GC.
 *	otherwise, extend the heap.
 * OverFull==False ->
 *	Do a GC.
 *
 * Rules for changing the value of OverFull:
 *
 * If the GC did not free enough space (say freed less than X 
 * percent of the size of AOA), set OverFull=True, otherwise 
 * set it to False. It can thus only change to False after a GC.
 *
 * If an allocation fails, try a GC if OverFull==False, or
 * if OverFull==True and the heap has been extended enough
 * (say more than X percent of the size of AOA or Y MB)
 *
 * [ One could take AOAPercentage for Y ]
 *
 * There is a minor caveat here: even if the heap has been
 * extended enough, and one does the GC, that does not guarantee
 * that there is sufficient  room. If there isn't, then the heap
 * has to be extended even though it had already been extended
 * enough...
 */



#define REP ((ObjectRep *)theObj)

/* LOCAL FUNCTIONS */
#ifdef USEMMAP
static Object* ExtendBaseBlock(unsigned long numbytes);
#else
static void AOANewBlock(long newBlockSize);
/* static void AOAMaybeNewBlock(long minNewBlockSize); */
#endif

#ifdef RTDEBUG
#ifdef FASTDEBUG
#else
static void AOACheckObjectRefSpecial(REFERENCEACTIONARGSTYPE);
#endif /* FASTDEBUG */
void scanPartObjects(Object *obj, void (*)(Object *));
#endif /* RTDEBUG */

/* LOCAL VARIABLES */
static long totalFree = 0;
static long lastAOAGCAt = -1000;  /* NumIOAGc of last AOAGC */

static unsigned long AOASizeAtGC = 0;
static unsigned long AOAFreeAtGC = 0;

/*  We allocate 4Mbyte at a time in AOA so try to do an AOAGc
 *  before the first time we have to expand
 */

/* actually set in AOANewBlock */
static unsigned long AOAMinSizeForGC = 1000000;

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
  Claim(tempAOAroots!=NULL, "tempAOArootsFree: tempAOAroots allocated");
  MCHECK();
  FREE(tempAOAroots);
  MCHECK();
  tempAOAroots = NULL;
  INFO_IOA(fprintf(output, "freed temporary AOAroots table\n"));
}

/* AOAfree:
 */
void AOAfree(void)
{
  /* Free everything allocated by AOA */
  Block *aoa, *next;
  aoa = AOABaseBlock;
  while (aoa){    
      next = aoa->next;
      freeBlock(aoa);
      aoa = next;
  }
  if (tempAOAroots) tempAOArootsFree();
  return;
}

#ifdef USEMMAP
static Object *ExtendBaseBlock(unsigned long numbytes)
{
  char *newspace = (char*)AOABaseBlock->top;
  char *oldlimit; 
  unsigned long extend = numbytes;

  if (numbytes <= (unsigned long)((char*)AOABaseBlock->limit - (char*)AOABaseBlock->top)) {
    AOABaseBlock->top = (long*)((char*)AOABaseBlock->top+numbytes);
    totalAOASize = (char*)AOABaseBlock->top-(char*)BlockStart(AOABaseBlock);
    ((Object*)newspace)->GCAttr = DEADOBJECT;
    return (Object*)newspace;
  }

  extend = (extend+16*MMAPPageSize-1) & ~(16*MMAPPageSize-1);
  if (AOABaseBlock->limit == BlockStart(AOABaseBlock)) {
    /* No memory available, first time.  
     * Block.c allocates an entire page to hold the blockheader,
     * but none of it is available yet. 
     * Use rest of that block, too */
    extend += MMAPPageSize-sizeof(Block);
  }
  oldlimit = (char*)AOABaseBlock->limit;
  extendBlock(AOABaseBlock, extend);
  extend = (char*)AOABaseBlock->limit - oldlimit;
  AOABaseBlock->top = (long*)((char*)AOABaseBlock->top+numbytes);
  totalAOASize = (char*)AOABaseBlock->top-(char*)BlockStart(AOABaseBlock);
  ((Object*)newspace)->GCAttr = DEADOBJECT;
  return (Object*)newspace;
}

#else /* ndef USEMMAP */

static Block *sector_map[SECTOR_COUNT*2];

static void
mark_sector(unsigned long addr, Block *block)
{
  int i = SECTOR_INDEX(addr) * 2;
  Claim(!sector_map[i] || !sector_map[i + 1], "No space in sector map");
  Claim(sector_map[i] || !sector_map[i + 1], "Wrong entry unused in sector map");
  Claim(sector_map[i] != block, "Block already in sector map");
  if (sector_map[i])
    sector_map[i + 1] = block;
  else
    sector_map[i] = block;
}

static void
insert_block_in_sector_map(
    Block *block,
    unsigned long addr,
    unsigned long len)
{
  for ( ;
       len > SECTOR_SIZE;
       addr += SECTOR_SIZE, len -= SECTOR_SIZE) {
    mark_sector(addr, block);
  }
  mark_sector(addr, block);
  if (SECTOR_ROUND_DOWN(addr + len - 1) != SECTOR_ROUND_DOWN(addr))
  mark_sector(addr+len, block);
}

/* This is as fast as possible */

int
SectorBasedInAOA(Object *o)
{
  Block *b;
  b = sector_map[SECTOR_INDEX(o) * 2];
  if (!b)
    return 0;         /* Fast path exits here for objects not in AOA */
  if (inBlock(b, o))
    return 1;
  b = sector_map[SECTOR_INDEX(o) * 2 + 1];
  if (!b)
    return 0;
  if (inBlock(b, o))
      return 1;
  return 0;
}

int
SectorBasedInAOAUnused(Object *o)
{
  Block *b;
  b = sector_map[SECTOR_INDEX(o) * 2];
  if (!b)
    return 0;
  if (inBlockUnused(b, o))
    return 1;
  b = sector_map[SECTOR_INDEX(o) * 2 + 1];
  if (!b)
    return 0;
  if (inBlockUnused(b, o))
      return 1;
  return 0;
}

static void AOANewBlock(long newBlockSize) 
{
  Block * newblock;
  if (newBlockSize > SECTOR_SIZE) {
    INFO_AOA(fprintf(output, 
		     "\n#AOANewBlock: Allocating large new block %d (0x%08x) bytes / %dMb\n",
		     (int)newBlockSize,
		     (int)newBlockSize,
		     (int)newBlockSize/(1024*1024)
		     );
	     fflush(output);
	     );
  }
  if (newBlockSize < SECTOR_SIZE) {
    /* See comments in macro.h
     */
    newBlockSize = SECTOR_SIZE;
  }
  newBlockSize = ObjectAlign(newBlockSize);
  if ((newblock = newBlock(newBlockSize))) {

    insert_block_in_sector_map(newblock,
                               (unsigned long)BlockStart(newblock),
                               newBlockSize);

    /* Insert the new block in the freelist */
    AOAInsertFreeBlock((char *)newblock->top,
                 (char *)newblock->limit - (char *)newblock->top);

    newblock->top = newblock->limit;  /* Mark this block as already used */
    totalFree += newBlockSize;
    totalAOASize += newBlockSize;

        
    AOABlocks++;
    if (!AOABaseBlock) {
      AOAMinSizeForGC = AOAMinFree;
      AOABaseBlock = newblock;
      AOATopBlock = newblock;
      AOATopBlock -> next = NULL;
      /* Check if the AOAtoIOAtable is allocated. If not then allocate it. */
      if (AOAtoIOAtable == 0)
      if (AOAtoIOAalloc() == 0) {
	  fprintf(output,
		"#(AOA: AOAtoIOAtable allocation %d failed!.)\n",
		 (int)AOAtoIOAtableSize);
		BetaExit(1);
      }
    } else {
      AOATopBlock -> next = newblock;
      AOATopBlock = newblock;
    }
    INFO_AOA({
      fprintf(output,"AOA: Allocated new block of %dkb\n", 
	      (int)newBlockSize/1024);
      fflush(output);
    });
  } else {
    fprintf(output,"MallocExhausted\n");
    BetaExit(1);
  }
}

#endif /* ndef USE_MMAP */

/* AOAallocate allocate 'size' number of bytes in the Adult object area.
 * If the allocation succeeds the function returns a reference to the allocated
 * object, 0 otherwise.  */
Object *AOAallocate(long numbytes, int forceAOAAllocation)
{
  Object *newObj;
    
  Claim(numbytes > 0, "AOAallocate: numbytes > 0");

  /*
   * Note we compare the size _before the allocation_ with the size
   * where the next GC is scheduled.  This means that one huge allocation
   * can go through even though it busts through the boundary (which is
   * just a heuristic anyway
   */
  if ((unsigned long)(totalAOASize - totalFree) > AOAMinSizeForGC) {
      if (totalAOASize && !noAOAGC && !(IOALooksFullCount > 1)
#ifdef PERSIST
	  && !forceAOAAllocation
#endif
	 )
      {
	  AOANeedCompaction = 1;
	  return NULL;
      }
  }

  /* Try to find a chunk of memory in the freelist */
  newObj = AOAAllocateFromFreeList(numbytes);
  if (newObj) {
    newObj->GCAttr = DEADOBJECT;
    totalFree -= numbytes;
    return newObj;
  }

  DEBUG_CODE({
    if (!IOAActive) {
      INFO_AOA(fprintf(output,"AOAallocate failed: "
		       "numbytes=%d\n",
		       (int)numbytes));
    }
  }); 
  
#ifdef USEMMAP
  return ExtendBaseBlock(numbytes);
#else
  AOANewBlock(numbytes);
  return AOAallocate(numbytes, forceAOAAllocation);
#endif
}

Object *AOAalloc(long numbytes)
{
  DEBUG_CODE(NumAOAAlloc++);
  return AOAallocate(numbytes, FALSE);
}

Object *AOAcalloc(long numbytes)
{
  Object *theObj;
  long gca;

  theObj = AOAalloc(numbytes);
  if (theObj) {
    gca = theObj->GCAttr;
    memset(theObj, 0, numbytes);
    theObj->GCAttr = gca;
  }
  return theObj;
}

/* CopyObjectToAOA:
 *  move an object to AOA and return the address of the new location
 *  If the allocation in AOA failed the function returns 0;
 */
Object *CopyObjectToAOA(Object *theObj, Object *newObj, int forceAOAAllocation)
{
  long        size;
  register long * src;
  register long * dst;
  register long * theEnd;
  
  size = 4*ObjectSize(theObj); 
  Claim(ObjectSize(theObj) > 0, "#ToAOA: ObjectSize(theObj) > 0");
  Claim((size&7)==0, "#ToAOA: (size&7)==0 ");

  if (!newObj) {       
    newObj = AOAallocate(size, forceAOAAllocation);
    if (!newObj) {
      return NULL;
    }
  }

# ifdef ALLOC_TRACE
  if(alloc_trace_handle) {
      int i = TRACE_MOVE_OBJECT_TO_AOA;
      fwrite(&i, 4, 1, alloc_trace_handle);
      fwrite(&theObj, 4, 1, alloc_trace_handle);
      fwrite(&newObj, 4, 1, alloc_trace_handle);
  }
# endif
  
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
    numbytes += BlockNumBytes(current);
    current = current->next;
  }

  return numbytes;
}

static void AOARefStackHack(void)
{
  /*
   * Dreadful hack. We have to remove the tag bits from those references
   * in stackobjects that have them, so the Follow*() can handle them,
   * but we have to save them somewhere. They are saved in the LSB of
   * the pointers in the AOAroots table. They are restored just
   * before the AOAGc finishes.
   */
#ifdef UseRefStack
  long *pointer, *cellptr;

  pointer = (long*)AOArootsPtr;
  while (pointer < (long*)AOArootsLimit) {
    cellptr = (long*)*pointer;
    if (*cellptr & 1) {
      *cellptr &= ~1;
      *pointer |= 1;
    }
    pointer++;
  }
#endif
}

static void AOARefStackUnHack(void)
{
#ifdef UseRefStack
  long *pointer, *cellptr;

  pointer = (long*)AOArootsPtr;
  while (pointer < (long*)AOArootsLimit) {
    if (*pointer & 1) {
      /* clear tag bit in table */
      *pointer &= ~1; 
      cellptr = (long*)*pointer;
      *cellptr |= 1;
    }
    pointer++;
  }
#endif

}

/*
 *  AOAGc: perform a mark/sweep garbagecollection on the AOA heap.
 *  Should be called after IOAGc when AOANeedCompaction == TRUE;
 */

void AOAGc()
{
   long *pointer;
   long *cellptr;
   Object *target;
   Block *currentBlock;
   long starttime = 0;
   unsigned long freeAtStart = totalFree;
   unsigned long freed;
   int expand_percent;

   if (!AOABaseBlock)
      return;

   NumAOAGc++;
  
   TIME_AOA(starttime = getmilisectimestamp());
  
   INFO_AOA({
      starttime = getmilisectimestamp();
      fprintf(output,"\n#(AOA-%d[ioa#%d]:", (int)NumAOAGc, (int)NumIOAGc);
   });

   MAC_CODE(RotateTheCursorBack());
  
   AOARefStackHack();
  
   AOAFreeListAnalyze1();
   STAT_AOA(AOADisplayFreeList());
  
   /* Based on the AOARoots all objects reachable from those roots
    * are collected in a linked list. After that AOA is scanned and
    * objects not in the list are considered dead and inserted in the
    * free lists.
    */
  
   pointer = AOArootsPtr;
  
   /* Clear AOAtoIOAtable. It will be rebuild by 
    * extend- and initialCollectList. */
   AOAtoIOAClear();
   
   /* AOAGc clears the free list and rebuilds it during the scan of the
      live objects. Because AOA skips the scan of persistent objects,
      references from such objects into IOA are not inserted in
      AOAToIOATable. But this is not a problem, since there are no
      references from persistent AOA objects to IOA at this point. The
      entire transitive closure of the persistent objects have been
      moved to AOA. */
   MAC_CODE(RotateTheCursorBack());
  
   DEBUG_AOA(fprintf(output,"[Marking all Live Objects in AOA]\n"));
   if (pointer < AOArootsLimit) {
      /* Clear old tail (if any) */
      clearTail();
    
      while (pointer < AOArootsLimit) {
         cellptr = (long*)(*pointer & ~1);
#ifdef PERSIST
         Claim(!inPIT((void *)*cellptr), "What ??");
#endif /* PERSIST */
         target = getRealObject((Object *)*cellptr);
#ifdef PERSIST
         if (!AOAISPERSISTENT(target)) {
            collectList(target, prependToListInAOA);
         } else {
            objectAlive(target);
         }
#else
         collectList(target, prependToListInAOA);
#endif /* PERSIST */
         pointer++;
      }
   }
  
   /* The object pointed to by root is now the head of the linked list
    * of all live objects in AOA.  */
  
#ifdef PERSIST
   /* All persistent objects not directly referred by live objects are
      now marked as DEAD in their object info object . They should be
      checkpointed to the store and declared DEAD so that the ensuing
      sweep will collect them.
   */
   phaseFive();
#endif /* PERSIST */

   /* Scan AOA and insert dead objects in the freelist */
  
   MAC_CODE(RotateTheCursorBack());
  
   INFO_AOA({
      fprintf(output, "AOA-%d startsweep, marktime=%dms\n", 
              (int)NumAOAGc, (int)(getmilisectimestamp() - starttime));
   });
  
   /* Clear the free lists */
   DEBUG_AOA(fprintf(output,"[AOACleanFreeList]\n"));
   AOACleanFreeList();
  
   /* All space is alive until proven dead */
   totalFree = 0;
  
   DETAILEDSTAT_AOA(fprintf(output,"[Blocks: freed/free/total:\n"));
  
   /* Scan each block in AOA. */
   LVRSizeSum = 0;
   currentBlock = AOABaseBlock;
   while (currentBlock) {
      long freeInBlock;
      /* Then each chunk in the block is examined */
    
      freeInBlock = AOAScanMemoryArea(BlockStart(currentBlock),
                                      currentBlock -> top);
      totalFree += freeInBlock;

      DETAILEDSTAT_AOA(fprintf(output,"[0x%08x/0x%08x/0x%08x] ",
                               (int)collectedMem, (int)freeInBlock, (int)BlockNumBytes(currentBlock)));
    
      currentBlock = currentBlock -> next;
   }
   freed = totalFree-freeAtStart;

   DETAILEDSTAT_AOA(fprintf(output,"]\n"));

   AOARefStackUnHack();

   /* 0-8Mbyte    expand by 40%  (AOAPercentage * 4)
    * 8-32Mbyte   expand by 20%  (AOAPercentage * 2)
    * 32+ Mbyte   expand by 10%  (AOAPercentage    )
    */
   if (totalAOASize - totalFree < (8 << 20))
       expand_percent = AOAPercentage * 4;
   else if (totalAOASize - totalFree < (32 << 20))
       expand_percent = AOAPercentage * 2;
   else
       expand_percent = AOAPercentage;

   AOAMinSizeForGC = ((totalAOASize - totalFree) / 100) *
                                 (100 + expand_percent);

   INFO_AOA(fprintf(output, "Lettting heap expand by %d%%\n", expand_percent););

   if ((long)AOAMinSizeForGC < (long)AOAMinFree)
           AOAMinSizeForGC = AOAMinFree;

   AOASizeAtGC = totalAOASize;
   AOAFreeAtGC = totalFree;

   STAT_AOA(AOADisplayFreeList());

   /* Now all blocks have been scanned and all dead objects inserted
    * in the freelists. 
    * Analyze freelists to determine the strategy for allocation. 
    */
      
   MAC_CODE(RotateTheCursorBack());

   AOAFreeListAnalyze2();
   STAT_AOA({
      fprintf(output, "AOA-%d aoasize=0x%08x aoafree=0x%08x\n",
              (int)NumAOAGc, (int)totalAOASize, (int)totalFree);
      fflush(output);
   });
   DETAILEDSTAT_AOA({
      fprintf(output, "AOA-%d VR=0x%08x numobjects=0x%08x\n",
              (int)NumAOAGc, (int)LVRSizeSum,  (int)objectsInAOA);
      fflush(output);
   });
  
   INFO_AOA({
      fprintf(output, "AOA-%d done, freed 0x%x (%d%%), free 0x%x, size 0x%x,\n"
              "used = 0x%08x, aoatime=%dms, AOAMinSizeForGC=0x%x)\n", 
              (int)NumAOAGc, (int)freed,
	      (int)((freed) / ((freed + totalAOASize - totalFree) / 100 + 1)),
	      (int)totalFree, (int)totalAOASize,
	      (int)(totalAOASize - totalFree),
              (int)(getmilisectimestamp() - starttime),
	      (int)AOAMinSizeForGC);
   });

   AOANeedCompaction = FALSE;
   forceAOAGC = FALSE;
   TIME_AOA(aoatime += (int)(getmilisectimestamp() - starttime));

   lastAOAGCAt = NumIOAGc;
}

 
#ifdef RTDEBUG

Object * lastAOAObj=0;

#ifdef FASTDEBUG
#else
static FILE *dump_aoa_file=NULL;
#endif /* FASTDEBUG */

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
#ifdef FASTDEBUG
  return;
#else
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
    theObj = (Object *) BlockStart(theBlock);
    while( (long *) theObj < theBlock->top ){
      if (AOAISFREE(theObj)) {
	theObjectSize = ((AOAFreeChunk*)theObj)->size;
      } else {
	theObjectSize = 4*ObjectSize(theObj);
	Claim((theObjectSize&7)==0, "#AOACheck: (TheObjectSize&7)==0 ");
	Claim(ObjectSize(theObj) > 0, "#AOACheck: ObjectSize(theObj) > 0");
	AOACheckObject( theObj);
	lastAOAObj=theObj;
      }
      theObj = (Object *) Offset( theObj, theObjectSize);
    }
    theBlock = theBlock->next;
  }
  dump_aoa = 0;
#endif /* FASTDEBUG */
} 


/* AOACheckObject: Consistency check on AOA object */
void AOACheckObject(Object *theObj)
{ 
#ifdef FASTDEBUG
  return;
#else
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
	     NULL,
	     TRUE);
#endif /* FASTDEBUG */
}

/* AOACheckReference: Consistency check on AOA reference */
void AOACheckReference(Object **theCell, long refType)
{
#ifdef FASTDEBUG
  return;
#else
  long i; long * pointer = BlockStart( AOAtoIOAtable);
  long found = FALSE;

  Claim((inAOA(theCell) || inIOA(theCell)),
	"AOACheckReference: theCell in IOA, AOA");
  if (inIOA(*theCell)) {
      for (i=0; i < AOAtoIOAtableSize; i++){
	if (*pointer) {
	  if (*pointer == (long) theCell) {
	    found = TRUE;
	    break;
	  }
	}
	pointer++;
      }
      if (!found){
	char buf[512];
	sprintf(buf, 
		"AOACheckReference: *theCell [*(0x%x)] in IOA but not in AOAtoIOAtable",
		(int)theCell);
	Claim(found, buf);
      }
  }
#endif /* FASTDEBUG */
}

/* */
#ifdef FASTDEBUG
#else
static void AOACheckObjectRefSpecial(REFERENCEACTIONARGSTYPE)
{
  return;
}
#endif /* FASTDEBUG */

/* AOACheckObjectSpecial: Weak consistency check on AOA object */
void AOACheckObjectSpecial(Object *theObj)
{
#ifdef FASTDEBUG
  return;
#else
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
	     NULL,
	     TRUE);
#endif /* FASTDEBUG */
}

static void originAction(Object **theCell) {
  ;
}

static void checkOrigin(Object *theObj)
{
  scanOrigins(theObj, originAction);
}

void checkOrigins(Object *theObj, void *generic)
{
  scanPartObjects(theObj, checkOrigin);
}

void scanPartObjects(Object *obj, void (*objectAction)(Object *))
{
  ProtoType * theProto;
  
  theProto = GETPROTO(obj);
  
  if (objectAction) {
    objectAction(obj);
  }
  
  if (!isSpecialProtoType(theProto)) {
    GCEntry *tab =
      (GCEntry *) ((char *) theProto + theProto->GCTabOff);
        
    /* Handle all the static objects. 
     *
     * The static table, tab[0], tab[1], ..., 0,
     * contains all static objects on all levels.
     * We call recursively on every one, is we're told
     * to do so. When we do so, we make sure that there is no 
     * further recursion going on.
     */
    for (;tab->StaticOff; ++tab) {
      if (objectAction) {
	objectAction((Object *)((long *)obj + tab->StaticOff));
      }
    }
    
  } else {
    switch (SwitchProto(theProto)) {
    case SwitchProto(ByteRepPTValue):
    case SwitchProto(ShortRepPTValue):
    case SwitchProto(DoubleRepPTValue):
    case SwitchProto(LongRepPTValue): 
    case SwitchProto(DynItemRepPTValue):
    case SwitchProto(DynCompRepPTValue):
    case SwitchProto(RefRepPTValue): 
      break;
      
    case SwitchProto(ComponentPTValue):
      {
	Component * theComponent;
	
	theComponent = ((Component*)obj);
	scanPartObjects((Object *)ComponentItem( theComponent), objectAction);
	break;
      }
    case SwitchProto(StackObjectPTValue):
      break;
      
    case SwitchProto(StructurePTValue):
      break;
              
    case SwitchProto(DopartObjectPTValue):
      break;
    default:
      Claim( FALSE, "scanObject: theObj must be KNOWN.");
      
    }
  } 
}

#endif /* RTDEBUG */

/* Functions below are used to build a linked list of all objects
 * reachable from some root in the GCfield of the objects.  
 */

static Object * head;        /* Head of list build by collectList */
static Object * insertPoint; /* insertpoint of list build by collectList */
static Object * tail;        /* Tail of list build by collectList */
static long totalsize;

void clearTail(void)
{
  head = NULL;
  insertPoint = NULL;
  totalsize = 0;
  tail = NULL;
}

Object *getHead(void)
{
  return head;
}

/* static */ void (*StackRefAction)(REFERENCEACTIONARGSTYPE) = NULL;
void StackRefActionWrapper(Object **theCell,Object *theObj)
{
  if (theObj
      && inBetaHeap(theObj)
      && isObject(theObj)) {
    StackRefAction(theCell, REFTYPE_DYNAMIC);
  }
}

Object * getRealObject(Object * obj)
{
  long Distance;
  Object * AutObj;

#ifdef PERSIST
  Claim(!inPIT(obj), "getRealObject: Object in PIT");
#endif /* PERSIST */

  if (obj -> GCAttr < 0) {
    GetDistanceToEnclosingObject(obj, Distance);
    AutObj = (Object *) Offset(obj, Distance);
    return AutObj;
  } else {
    return obj;
  }
}

#ifdef PERSIST
Object * getRealStoreObject(Object * obj)
{
   long Distance;
   Object * AutObj;

#ifdef PERSIST
   Claim(!inPIT(obj), "getRealStoreObject: Object in PIT");
#endif /* PERSIST */

   if (obj -> GCAttr < 0) {
      GetDistanceToEnclosingStoreObject(obj, Distance);
      AutObj = (Object *) Offset(obj, Distance);
      return AutObj;
   } else {
      return obj;
   }
}
#endif /* PERSIST */

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
    
/* Prepend objects to the list, assuming they are in ToSpace. */
static void prependToListInIOA(Object *target)
{
  long GCAttribute;

  Claim(inToSpace(target), "inToSpace(target) (Where is the object)?");

  GCAttribute = target -> GCAttr;  
  
  Claim(GCAttribute > -1, "Trying to insert partobject");
  
  if (GCAttribute <= IOAMaxAge) {
    target->GCAttr = insertPoint->GCAttr;
    insertPoint->GCAttr = (long)target;
    totalsize += 4 * ObjectSize(target);
  } else if (GCAttribute == LISTEND) {
    ;
  } else {
    /* 'target' has a reference in it's GCField.  Thus it is already
     * in the list. */
    Claim(isLink((long)target), "Target is not in the list");
  }
}

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

  target = getRealObject(target);

  Claim(IOAActive, "IOAGC not active");
  Claim(!inIOA(target), "!inIOA(target)");

  if (inToSpace(target)) {
    prependToListInIOA(target);
  } else if (inAOA(target)) {
    /* Object is in AOA */
    Claim(inAOA(target), "Where is the object?");
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
    } else {
      /* 'target' has a reference in it's GCField. 
       * Thus it is already in the list. */
      Claim(isLink((long)target), "Target is not in the list");
    }
  } else {
    /* target is outside the heap. Okay for e.g. COM objects. */
    DEBUG_CODE({
      fprintf(output, "[prependToList: warning, target outside betaheaps: 0x%x]\n", 
	      (int)target);
    });
  }
}

/* Prepend objects to the list including only objects in AOA. */
void prependToListInAOA(REFERENCEACTIONARGSTYPE)
{
   Object *realObj, *theObj;

   DEBUG_CODE({
     char buf[200];
     sprintf(buf, "prependToListInAOA: inAOA(theCell == 0x%08x)", (int)theCell);
     Claim(inAOA(theCell), buf);
     sprintf(buf, "prependToListInAOA: *theCell!=0, theCell=0x%08x", (int)theCell);
     Claim((int)*theCell, buf);
     sprintf(buf, "prependToListInAOA: !inIOA(*theCell), theCell=0x%08x, *theCell=0x%08x", (int)theCell, (int)*theCell);
     Claim(!inIOA(*theCell), buf);
   });

   theObj = *theCell;
#ifdef PERSIST
   if (!inPIT((void *)theObj)) {
      realObj = getRealObject(theObj);
    
      if (inToSpace(realObj)) {
         AOAtoIOAInsert(theCell);
      } else if (inAOA(realObj)) {
         if (AOAISPERSISTENT(realObj)) {
            /* The object is marked as persistent. */
            objectAlive(realObj);
         } else { 
            prependToList(realObj);
         }
      }
   } else {
      /* This reference is a proxy reference */
      referenceCheck(theCell);
   }
#else
   realObj = getRealObject(theObj);
  
   if (inToSpace(realObj)) {
      AOAtoIOAInsert(theCell);
   } else if (inAOA(realObj)) {
      prependToList(realObj);
   } else {
      /* target is outside the heap. Okay for e.g. COM objects. */
      DEBUG_CODE({
         fprintf(output, "[prependToListInAOA: warning, target outside betaheaps: *0x%x=0x%x]\n", 
                 (int)theCell, (int)theObj);
      });
   }
#endif /* PERSIST */
}

static void initialCollectList(Object * root,
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

  /* InsertPoint is where new objects are inserted in the list.
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
    scanObject(insertPoint, referenceAction, NULL, TRUE);
    if (!isEnd(insertPoint->GCAttr)) {
      insertPoint=(Object *)(insertPoint->GCAttr);
    } else {
      break;
    }
  }
}

void collectList(Object *root,
		 void (*referenceAction)(REFERENCEACTIONARGSTYPE))
{
  /* set_start_time("extendCollectList"); */
  
  if (!tail) {
    initialCollectList(root, referenceAction);
    return;
  }
  
  prependToList(root);
  
  /* root has now been prepended to the list, if not already
   * there.
   */
  
  if (!isEnd(insertPoint->GCAttr)) {
    insertPoint=(Object*)(insertPoint->GCAttr);
    while (1) {
      scanObject(insertPoint, referenceAction, NULL, TRUE);
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

Object *isCellInObjectInList(Object **theCell, Object *root) 
{
  Object * cur;
  Object * next;
  
  cur = root;
  while (!isEnd((long)cur)) {
    next = (Object *)(cur->GCAttr);
    if ((long) cur <= (long) theCell) {
      if ((long) theCell < (long) cur + 4*ObjectSize(cur)) {
	return cur;
      }
    }
    cur = next;
  }
  return NULL;
}

/* scanObject: */
void scanObject(Object *obj,
		void (*referenceAction)(REFERENCEACTIONARGSTYPE),
		void (*objectAction)(Object *),
		int doPartObjects)
{
   ProtoType * theProto;
  
   theProto = GETPROTO(obj);

#ifdef PERSIST
#ifdef RTDEBUG
   if (!dontCheckProtoTypes) {
     if (!IsPrototypeOfProcess((long)theProto)){
       fprintf(output,"scanObject: proto of object 0x%08x is not in process: 0x%08x (vtbl=0x%08x)\n", (int)obj, (int)theProto, (int)obj->vtbl);
       ILLEGAL;
     }
   }
#endif /* RTDEBUG */
#endif /* PERSIST */

   if (objectAction) {
      objectAction(obj);
   }

#ifdef PERSIST
   if (dontCheckProtoTypes) {
      theProto = GETPROTO(obj);
   }
#endif /* PERSIST */
  
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
                       referenceAction, objectAction, FALSE);
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
         long refType = (*refs_ofs) & 3;
         /* sbrandt 24/1/1994: 2 least significant bits in prototype 
          * dynamic offset table masked out. As offsets in this table are
          * always multiples of 4, these bits may be used to distinguish
          * different reference types.
          REFTYPE_DYNAMIC: (# exit 0 #);
          REFTYPE_OFFLINE: (# exit 1 #);
          REFTYPE_ORIGIN: (# exit 2 #);
         */ 
         if (*pointer) {
            if (referenceAction) {
               referenceAction((Object **)pointer, refType);
            }
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
           if (referenceAction) {
              referenceAction(&(((ObjectRep *)obj) -> iOrigin), REFTYPE_ORIGIN);
              
              /* Process rest of repetition */
              size = ((ObjectRep *)obj)->HighBorder;
              pointer = (long *)&((ObjectRep *)obj)->Body[0];
        
              for (index=0; index<size; index++) {
                 if (*pointer) {
                    referenceAction((Object **)pointer, REFTYPE_OFFLINE);
                 }
                 pointer++;
              }
           }
           break;
        }
          
        case SwitchProto(RefRepPTValue): 
           /* Scan the repetition and apply referenceAction */
        {
           long *pointer;
           long offset, offsetTop;
              
           if (referenceAction) {
              offset =  (char*)(&((RefRep*)(obj))->Body[0]) - (char*)obj;
              offsetTop = offset + 4 * ((RefRep*)(obj))->HighBorder;
           
              while (offset < offsetTop) {
                 pointer = (long *)((long)obj + offset);
                 if (*pointer) {     
                    referenceAction((Object **)pointer, REFTYPE_DYNAMIC);
                 }
                 offset += 4;
              }
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
              if (referenceAction) {
                 referenceAction((Object **)&(theComponent->StackObj), REFTYPE_DYNAMIC);
              }
           }
           if (theComponent->CallerComp) {
              if (referenceAction) {
                 referenceAction((Object **)&(theComponent->CallerComp), REFTYPE_DYNAMIC);
              }
           }
           if (theComponent->CallerObj) {
              if (referenceAction) {
                 referenceAction(&(theComponent->CallerObj), REFTYPE_DYNAMIC);
              }
           }
           if (doPartObjects) { 
              scanObject((Object *)ComponentItem( theComponent),
                         referenceAction, objectAction, TRUE);
           }
           break;
        }
        case SwitchProto(StackObjectPTValue):
        {
           if (referenceAction) {
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
        }
        break;
              
        case SwitchProto(StructurePTValue):
           if (referenceAction) {
              referenceAction(&(((Structure*)(obj))->iOrigin), REFTYPE_ORIGIN);
           }
           break;
              
        case SwitchProto(DopartObjectPTValue):
           if (referenceAction) {
              referenceAction(&(((DopartObject *)(obj))->Origin), REFTYPE_ORIGIN);
           }
           break;
#ifdef PERSIST
        case SwitchProto(ObjInfoPTValue):
        case SwitchProto(RefInfoPTValue):
          break;
#endif
        default:
#ifdef RTDEBUG
          fprintf(output,
                  "\nscanObject: Prototype unknown. 0x%08x\n", (int)theProto);
#endif
          Claim( FALSE, "scanObject: theObj must be KNOWN.");
          
      }
   } 
}

/* scanOrigins: Scans all origin-references in theObj. For each origin
   reference, the cell containing the reference is supplied to the
   function 'originAction' */
void scanOrigins(Object *theObj, void (*originAction)(Object **theCell)) 
{
  ProtoType *theProto;
  Object **theCell = NULL;
  unsigned short originOffset;
  
  theProto = GETPROTO(theObj);
  
  while (1) {
    Claim(IsPrototypeOfProcess((long)theProto), 
	  "IsPrototypeOfProcess(theProto)");
    
    if (!isSpecialProtoType(theProto)) {
      originOffset = (unsigned short)(4 * (long) (theProto -> OriginOff));
      theCell = (Object **)((long) theObj + originOffset);
      originAction(theCell);
      
      if (theProto == theProto -> Prefix) {
	return;
      } else {
	theProto = theProto -> Prefix;
      }
    } else {
      switch (SwitchProto(theProto)){
      case SwitchProto(ByteRepPTValue):
      case SwitchProto(ShortRepPTValue):
      case SwitchProto(DoubleRepPTValue):
      case SwitchProto(LongRepPTValue): 
	/* Has no origin ?? */
	return;
	break; 
	
      case SwitchProto(DynItemRepPTValue):
      case SwitchProto(DynCompRepPTValue): 
	theCell = &(((struct _ObjectRep *)theObj)->iOrigin);
	originAction(theCell);
	
	/* No more ?? */
	return;
	break; 
	
      case SwitchProto(RefRepPTValue): 
	/* Has no origin ?? */
	return;
	break; 
	
      case SwitchProto(ComponentPTValue):
	/* The origins of the component is the origins of the item */
	scanOrigins((Object *)(&(((struct _Component*)theObj)->Body[0])), originAction);
	return;
	break; 
	
      case SwitchProto(StackObjectPTValue):
	Claim(FALSE,"scanOrigins: What are origins in ??");
	return;
	break; 
	
      case SwitchProto(StructurePTValue):
	theCell = &(((struct _Structure *)theObj)->iOrigin);
	originAction(theCell);
	
	/* No more ? */
	return;
	break;
	
      case SwitchProto(DopartObjectPTValue):
	theCell = &(((struct _DopartObject *)theObj)->Origin);
	originAction(theCell);
	
	/* No more ? */
	return;
	break;
	
      default:
	Claim(FALSE, "scanOrigins: theObj must be KNOWN.");
	return;
      }
    }
  }
}
