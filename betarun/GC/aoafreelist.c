/*
 * BETA RUNTIME SYSTEM, Copyright (C) 1991-98 Mjolner Informatics Aps.
 * aoafreelist.c
 * Peter Andersen, Morten Grouleff, Stephan Korsholm
 */

#include "beta.h"

#ifdef PERSIST
#include "PException.h"
#include "objectTable.h"
#include "pit.h"
#endif /* PERSIST */

/************************ THE AOA FREE LIST ***************************
 * AOA freelist description:
 *   All chunks are multiples of 8 bytes.
 *   The freelist is organized as an array with FreeListSmallMAX entries,
 *   each forming a list of free chunks of that size.
 *   One exception is index FreeListSmallMAX, which forms a list of chunks
 *   of variable larger sizes.
 *   ASSUMPTION: It is assumed that no objects of size 8
 *   are allocated. This is the case today!
 *         
 *   AOAFreeList:
 *           _____      ___     ___     ___
 *     0:   |     |--->|___|-->|___|-->|___| chunks size 0 (numbytes/8)
 *     1:   |     |--->...                   chunks size 8
 *     2:   |     |--->...                   chunks size 16  
 *     3:   |     |--->...                   chunks size 24  
 *     4:   |     |--->...                   chunks size 32  
 *         ...
 *     30:  |     |--->...                   chunks size 240
 *     31:  |_____|--->...                   chunks size 248
 *     32:  |_____|--->...                   chunks size 256 - 511
 *     33:  |_____|--->...                   chunks size 512 - 1024
 *         ...
 *  32+24:  |_____|--->...                   chunks size 2^31 - 2^32
 *
 *   FIXME: This is probably not the smartest algorithm for the large
 *   objects. Possibly a variant where objects of various size
 *   *ranges* are indexed for the large object (as in LVRA) should
 *   be adopted.
 *          
 *   To avoid using extra space the freelist can be the objects
 *   themselves linked together. This has the drawback that other
 *   parts of the AOAGC also links objects together, and uses the link
 *   to see if the object is dead or not. Thus the freelist link
 *   cannot be placed in the same word as the GC-link. For now we will
 *   use the proto field for freelist links and the GC-field for live
 *   links. The GC also needs the size of the objects to scan the heap
 *   looking for dead objects. The size is put in the 3rd word. This
 *   means that all chunks must be at least 12 bytes long. Since all
 *   BETA-objects have a size thats k*8, all objects must be at least
 *   16 bytes.
 *         
 *   AOAFreeChunk:
 *      __________ 
 *     |   next   |-->
 *     |   GC=0   |
 *     |   size   |
 *     | ........ |
 *
 *          */

#define FreeListSmallMAX 32  /* Sizes 0 through 8*FreeListSmallMAX */
#define FreeListLargeMAX 24  /* Sizes in ranges:
			      *	1*8*FreeListSmallMAX - 2*8*FreeListSmallMAX, 
			      *	2*8*FreeListSmallMAX - 4*8*FreeListSmallMAX,
			      * etc.
			      * Make sure there are enough to handle 2^31.
			      */

/* Controls when a block is split into a freelist for the small blocks:
 * If there are less than AOAFreeListPleaseMoreBytes in the freelist for a 
 * given restsize, it is okay to split a block generating one of that size
 * even if that freelistindex is below MinGap.
 * If there are more than AOAFreeListTooManyBytes in a freelist, MinGap is
 * set so that no chunks are inserted through splitting blocks in the
 * freelist.
 */
#define AOAFreeListPleaseMoreBytes 8192
#define AOAFreeListTooManyBytes  (2*8192)


/* LOCAL FUNCTIONS */
static long AOAFreeListIndexComplex(long numbytes);
static void AOAInsertFreeElement(AOAFreeChunk *freeChunk, long numbytes);
static AOAFreeChunk *AOAFindInFree(unsigned long numbytes);
static long AOALargeIndex2Size(long index);
static long AOAAnyIndex2Size(long index);
static int AOAWantsMore(long numbytes);

/* LOCAL VARIABLES */
static AOAFreeChunk *AOAFreeList[FreeListSmallMAX+FreeListLargeMAX+1];
static unsigned long AOAFreeListSize[FreeListSmallMAX+FreeListLargeMAX+1];
static unsigned long AOAInUseCount[FreeListSmallMAX+FreeListLargeMAX+1];
static unsigned long AOAInUseSize[FreeListSmallMAX+FreeListLargeMAX+1];
static unsigned long AOAMinGap = 16;          /* Must be at least 16 */
/* IMPLEMENTATION */

/* AOAFreeListIndex:
 *    finds an index in the AOAFreeList in the range [0..FreeListSmallMAX]
 *    for the given size.
 */

static unsigned long AOAFreeListIndex(unsigned long n)
{
  if (n <= FreeListSmallMAX*8) return n/8;
  return AOAFreeListIndexComplex(n);
}

#ifdef RTDEBUG
static unsigned long AOASmallIndex2Size(unsigned long index)
{
  Claim(0 <= index && index <= FreeListSmallMAX, 
	"0 <= index && index <= FreeListSmallMAX");
  return 8 * index;
}
#else
# define AOASmallIndex2Size(i) ((i) * 8)
#endif


static long AOAFreeListIndexComplex(long numbytes)
{
  long index, blksizemax;
    
  index = FreeListSmallMAX;
  blksizemax = 2*8*FreeListSmallMAX; /* Max size of blocks at index */
  if (numbytes < (blksizemax << 8)) {
    while (blksizemax <= numbytes) {
      blksizemax *= 2;
      index++;
    }
    return index;
  }
   
  blksizemax <<= 8;
  index += 8;
  
  while (blksizemax <= numbytes) {
    blksizemax *= 2;
    index++;
  }
  return index;
}

static long AOALargeIndex2Size(long index)
{
  Claim(FreeListSmallMAX <= index 
	&& index <= FreeListSmallMAX+FreeListLargeMAX, 
	"FreeListSmallMAX <= index "
	"&& index <= FreeListSmallMAX+FreeListLargeMAX");
  
  return (AOASmallIndex2Size(FreeListSmallMAX)<<(index-FreeListSmallMAX));
}

static long AOAAnyIndex2Size(long index)
{
  if (index <= FreeListSmallMAX) {
    return AOASmallIndex2Size(index);
  } else {
    return AOALargeIndex2Size(index);
  }
}


/* AOAWantsMore:
 *   Returns true, iff the list a block of size numbytes 
 *   would end up in, is not too crowded already.
 */
static int AOAWantsMore(long numbytes)
{
  long index;

  if (numbytes < 16)
    return 0;

  /* The large lists are never too crowded.  
   * That could lead to significantly increased memuse.
   */
  if (8*FreeListSmallMAX <= numbytes)
    return 1;
  
  index = (long)AOAFreeListIndex(numbytes);

  return (AOAFreeListSize[index]*numbytes < AOAFreeListPleaseMoreBytes);
}

/* AOAInsertFreeElement:
 *   adds a chunk to the AOAFreeList. 
 */
static void AOAInsertFreeElement(AOAFreeChunk *freeChunk, long numbytes)
{ 
  long index = (long) AOAFreeListIndex(numbytes);
    
#ifdef RTDEBUG  
  if (!freeChunk) {
    fprintf(stdout,"AOAInsertFreeElement: Inserting NULL\n");
    BetaExit(1);
  } else if (((unsigned)freeChunk & 7) != 0) {
    fprintf(stdout, "AOAInsertFreeElement: Reference (0x%X) is not alligned\n", (int)freeChunk);
    ILLEGAL;
  }
#endif
  freeChunk->next = AOAFreeList[index];
  AOAFreeList[index] = freeChunk;
  freeChunk->GCAttr = FREECHUNK;
  freeChunk->size = numbytes;
  AOAFreeListSize[index]++;
}

/* AOAFindInFree:
 *    tries to find space for an object with the given size.
 *    Strategy:
 *      1. Try to find chunk of size numbytes.
 *         If found, return it.
 *      2. Otherwise look in list of objects being size 2*numbytes.
 *         If found, split chunk in two, put the free half into
 *         free list of size numbytes, and return the other half.
 *      3. Otherwise look in list of objects being size 3*numbytes.
 *         If found, split chunk in two, put the free part into
 *         free list of size 2*numbytes, and return the other part.
 *      4. Repeat with freelists 4*numbytes, 5*numbytes until
 *         size 256 is superseeded.
 *      EC: This is out of date.  The new strategy is:
 *         2. Otherwise look in list of objects being size numbytes + 16.
 *            If found, split chunk in two, put the free part into
 *            free list of size 16, and return the other half.
 *         3. Otherwise look in list of objects being size numbytes + 24.
 *            If found, split chunk in two, put the free part into
 *            free list of size 24, and return the other part.
 *         4. Repeat with freelists numbytes + 32, numbytes + 40 etc. until
 *            size 256 is superseeded.
 *      5. Search for chunk in the large block lists.
 *         This search finds the best match.  What best is is hard
 *         to determine. Currently, the smallest possible match is found,
 *         except that is must leave no gap or a gap larger than AOAMinGap.
 *         Also, if the chunk we are allocating is very small then we just
 *         take the first match.
 *    If unsuccessfull, the function returns 0.
 *    Should only be called from AOAAllocateFromFreeList.
 */

static AOAFreeChunk *AOAFindInFree(unsigned long numbytes)
{
  AOAFreeChunk *newChunk = NULL, *current, *bestFit;
  AOAFreeChunk *restChunk;
  AOAFreeChunk **previous, **bestFitPrevious = NULL;
  int counter = 0;
  unsigned long index, startindex, bestFitIndex = 0;
  unsigned long sizeOfRestChunk, sizeOfFoundChunk, stepSize, bestFitSize;

  index = startindex = (unsigned long)AOAFreeListIndex(numbytes);
  if (index < FreeListSmallMAX && AOAFreeList[index]) {
    /* Exact match. Perfect */
    newChunk = AOAFreeList[index];
    /* remove the chunk from the freelist */
    AOAFreeList[index] = AOAFreeList[index]->next;
    AOAFreeListSize[index]--;
    AOAInUseCount[index]++;
    AOAInUseSize[index] += numbytes;
    return newChunk;
  }

  /* Minimum left over chunk is 16 bytes */
  index += 2;
  
  stepSize = 1;
 
  while (index < FreeListSmallMAX) {
    if (AOAFreeList[index]
	&& ((AOASmallIndex2Size(index) - numbytes) >= AOAMinGap 
	    || AOAWantsMore(AOASmallIndex2Size(index) - numbytes))) {
      /* A free chunk has been found. Now split it into two
       * pieces, the one is returned to hold the new object, the
       * rest (if any) is inserted in the freelist.
       */
      newChunk = AOAFreeList[index];
      sizeOfFoundChunk = newChunk->size;
      
      restChunk = (AOAFreeChunk *)((char *)newChunk + numbytes);
      sizeOfRestChunk = sizeOfFoundChunk - numbytes;
      
      /* remove the chunk from the freelist */
      AOAFreeList[index] = AOAFreeList[index]->next;
      AOAFreeListSize[index]--;
      AOAInUseCount[startindex]++;
      AOAInUseSize[startindex] += numbytes;

      /* insert the remaining chunk in the free list */
      /* There must be a rest, as this is not a perfect match -mg */
      /* if (sizeOfRestChunk) */
      { 
	AOAInsertFreeElement(restChunk, sizeOfRestChunk);
      }
      return newChunk;
    }
    index += stepSize;
  }
    
  /* No small free chunk was found, so we have to try the large
   * chunks. Since these might have different sizes, we need to
   * scan the entire freelist and cannot just look at the first
   * element as above.  Otherwise there will be more fragmentation.
   */
    
  bestFit = NULL;
  bestFitSize = 0x7FFFFFFF;
  /* the MAX() makes sure we don't try to scan the small lists, they can be
   * very long and they only contain objects of one size so it's totally
   * pointless.
   */
  index = bMAX(startindex, FreeListSmallMAX);
  
  do {
    if (AOAFreeList[index]) {
      current = AOAFreeList[index];
      previous = &AOAFreeList[index];

      /*
       * If the current block is more than 8 times larger than the size
       * we need then don't bother scanning the whole list for the best
       * fit, just return the first.  Fixes silly behaviour observed
       * while compiling mjolnertool. -EC
       * (Note also that we always put the 'rest' in at the beginning
       * of the list, so the first element will often be the smallest.)
       */
      if (current &&
          (current->size >> 3) > numbytes) {
        bestFit = current;
        bestFitSize = current->size;
        bestFitPrevious = previous;
        bestFitIndex = index;
        goto bestfitfound;
      }
      
      while (current) {
	if (current->size == numbytes) {
	  /* Exact match. Perfect */
	  /* remove the chunk from the freelist */
	  *previous = current->next;
	  AOAFreeListSize[index]--;
	  AOAInUseCount[index]++;
	  AOAInUseSize[index] += numbytes;
	  return current;
	}
	if ((current->size > numbytes) &&
	    (current->size < bestFitSize) &&
	    ((current->size - numbytes >= AOAMinGap) 
	     || AOAWantsMore(current->size - numbytes))) {
	  bestFit = current;
	  bestFitSize = current->size;
	  bestFitPrevious = previous;
	  bestFitIndex = index;
	}
	previous = &(current->next);
	current = current->next;
	counter++;
      }

bestfitfound:
      if (bestFit) {

	/* A chunk large enough has been found, and it is split
	 * into two parts as above.
	 */
	sizeOfFoundChunk = bestFit->size;
      
	restChunk = (AOAFreeChunk *)((char *)bestFit + numbytes);
	sizeOfRestChunk = sizeOfFoundChunk - numbytes;
	
	/* remove the chunk from the freelist */
	*bestFitPrevious = bestFit->next;
	AOAFreeListSize[bestFitIndex]--;
	AOAInUseCount[startindex]++;
	AOAInUseSize[startindex] += numbytes;

	/* insert the remaining chunk in the free list */
	/* There must be a rest, as this is not a perfect match -mg */
	/* if (sizeOfRestChunk) */
	{
	  AOAInsertFreeElement(restChunk, sizeOfRestChunk);
	}
      return bestFit;
      }
    }
    index++;
  } while (index < FreeListSmallMAX+FreeListLargeMAX);
  /* do-while */
  
  return NULL;
}


/* AOAAllocateFromFreeList:
 * Allocates a chunk of memory in AOA by searching the freelists
 */
Object *AOAAllocateFromFreeList(long numbytes) 
{
  Object *newObj = NULL;
    
  /* Only chunks of sizes that are multiples of 8 bytes may be
   *  in the free list.
   */

#ifdef RTDEBUG
  if (!((numbytes >= 16) && ((numbytes % 8) == 0))) {
    fprintf(stdout, "AOAAllocateFromFreeList: Illegal size (0x%X)\n", (int)numbytes);
    BetaExit(1);
  }
#endif
  newObj = (Object *)AOAFindInFree(numbytes);
#if 0
  DETAILEDSTAT_AOA({
    fprintf(output, "AOAalloc:%08x:%06x\n", (int)newObj, (int)numbytes);
    if (newObj) {
      objectsInAOA++;
      sizeOfObjectsInAOA += numbytes;
    }
  });
#endif
  DEBUG_AOA({
    if (newObj) {
      if (!inAOA(newObj)) {
	fprintf(stdout, "AOAAllocateFromFreeList: Reference (0x%X) is not in AOA!\n", (int)newObj);
	BetaExit(1);
      }
      
      if (((unsigned)newObj & 7) != 0) {
	fprintf(stdout, "AOAAllocateFromFreeList: Reference (0x%X) is not alligned\n", (int)newObj);
	BetaExit(1);
      }
    }
  });
  
  return newObj;
}

/* AOAFree:
 *   Frees the space in AOA by inserting it in the freelists.
 */
void AOAFreeInFreeList(Object *chunk) 
{
  long numbytes = 4*ObjectSize(chunk);
    
#ifdef RTDEBUG
  if (!((numbytes >= 16) && ((numbytes % 8) == 0))) {
    fprintf(stdout, "AOAFreeInFreeList: Illegal size (0x%X)\n", (int)numbytes);
    BetaExit(1);
  } else if (((unsigned)chunk & 7) != 0) {
    fprintf(stdout, "AOAFreeInFreeList: Reference (0x%X) is not aligned\n", 
	    (int)chunk);
    BetaExit(1);
  }
#endif
  AOAInsertFreeElement((AOAFreeChunk *)chunk, numbytes);
  DETAILEDSTAT_AOA({
    objectsInAOA--;
    sizeOfObjectsInAOA -= numbytes;
  });
}

/* AOAInsertFreeBlock:
 *   Inserts a block into the freelists.
 */
void AOAInsertFreeBlock(char *block, long numbytes) 
{
#ifdef RTDEBUG
  if (!((numbytes >= 16) && ((numbytes % 8) == 0))) {
    fprintf(stdout, "AOAFreeInFreeList: Illegal size (0x%X)\n", (int)numbytes);
    BetaExit(1);
  }
#endif
  AOAInsertFreeElement((AOAFreeChunk *)block, numbytes);
}

/* AOAInit:
 *   Initializes AOA.
 */
void AOAInit(void)
{
  long index;
  for (index=0; index <= FreeListSmallMAX+FreeListLargeMAX; index++) {
    AOAInUseCount[index] = 0;
    AOAInUseSize[index] = 0;
  }
  AOACleanFreeList();
}

/* AOACleanFreeList:
 *   initializes the AOAFreeList 
 */
void AOACleanFreeList(void)
{ 
  long index;
  for (index=0; index <= FreeListSmallMAX+FreeListLargeMAX; index++) {
    AOAFreeList[index] = (AOAFreeChunk *)NULL;
    AOAFreeListSize[index] = 0;
    /* AOAInUseCount/Size should not be cleaned, as it is updated on the fly */
  }
}

static long doAnalysis(void)
{
  /* Find the largest freelist before GC.
   * Chunks of this size are not that usefull, it seems, 
   * so we want the allocations to avoid using making them
   * by only leaving gaps that are larger.
   */

  unsigned long index = 0, maxindex = 0, addsize = 0;
  unsigned long mingap;

  for (index = 0; index < FreeListSmallMAX ; index++) {
    addsize /= 2;
    addsize += AOAFreeListSize[index];;
    if (addsize*AOASmallIndex2Size(index) > AOAFreeListTooManyBytes) {
      maxindex = index;
    }
  }

  if (maxindex) {
    if (maxindex+1 > FreeListSmallMAX) {
      mingap = AOASmallIndex2Size(FreeListSmallMAX);
    } else {
     mingap  = AOASmallIndex2Size(maxindex+1);
    }
  } else {
    mingap = 16;
  }
  return mingap;
}

/* AOAFreeListAnalyze1:  AOAFreeListAnalyze2:
 *   Analyses the freelists to find the minimum size of gaps to leave
 *   when splitting blocks during allocation.
 */
void AOAFreeListAnalyze1(void)
{
  AOAMinGap = doAnalysis();
  DETAILEDSTAT_AOA(fprintf(output, "[Analyze1:AOAMinGap=0x%02x]\n", (int)AOAMinGap));
}

void AOAFreeListAnalyze2(void)
{
  unsigned long step1gap = AOAMinGap;
  AOAMinGap = doAnalysis();
  DETAILEDSTAT_AOA(fprintf(output, "[Analyze2:AOAMinGap=0x%02x]\n", (int)AOAMinGap));
  if (step1gap < AOAMinGap)
    AOAMinGap = step1gap;
  DETAILEDSTAT_AOA(fprintf(output, "[Final:AOAMinGap=0x%02x]\n", (int)AOAMinGap));
}


/* AOAScanMemoryArea:
 */
long AOAScanMemoryArea(long *start, long *end) 
{
  AOAFreeChunk *current;
  long size;
  long freeMemInBlock;
  DEBUG_CODE(long memoryAreaSize = 0);
  
  collectedMem = 0;
  
  freeMemInBlock = 0;
  current = (AOAFreeChunk *)start;
  while((long *)current < end) {
    if (AOAISALIVE(current)) {
      /* Leave as is */
      size = 4 * ObjectSize((Object *)current);
      DETAILEDSTAT_AOA({
	if (isValRep((Object *)current)) {
	  LVRSizeSum += size;
	}
      });
      DEBUG_AOA(memoryAreaSize += size);
#ifdef PERSIST
      /* We do not want to clear the persistent mark in persistent
         objects */
      if (AOAISPERSISTENT(current)) {
         /* Skip the clearing of the GCAttribute, since it contains a
          * reference to the object info object. Persistent objects
          * are explicitly killed elsewhere
          */
         ;
      } else {
         current->GCAttr = DEADOBJECT;
      }
#else 
      current->GCAttr = DEADOBJECT;
#endif /* PERSIST */
      current = (AOAFreeChunk *)((char *)current + size);
    } else {
      /* DEAD or FREE or Error */
      long freeChunkSize;
      AOAFreeChunk *freeChunkStart;
      
      /* Group chunks together if possible (merge/coalesce) */
      freeChunkStart = current;
      do {
#ifdef RTDEBUG
	if (!AOAISFREE(current) && !AOAISDEAD(current)) {
	  fprintf(output, "AOAScanMemoryArea: "
		  "Bogus GCAttr value in AOAFreeChunk:%d\n",
		  (int)(current->GCAttr));
	  ILLEGAL;
	  BetaExit(1);
	}
#endif
	if (AOAISFREE(current)) {
	  size = current->size;
	} else {
	  size = 4 * ObjectSize((Object *)current);
	  {
	    long index = (long)AOAFreeListIndex(size);
	    AOAInUseCount[index]--;
	    AOAInUseSize[index] -= size;
	  }
	  DETAILEDSTAT_AOA({
	    if (freeChunkStart == current) {
	      fprintf(output, "AOAfree:%d:%d\n", (int)current, (int)size);
     	    } else {
	      fprintf(output, "AOAfree:%d:%d:C:%d \n",
		      (int)current, (int)size, (int)freeChunkStart);
	    }
	    objectsInAOA--;
	    sizeOfObjectsInAOA -= size;
	    collectedMem += size;
	  });
#ifdef PERSIST
          if (GETPROTO((Object *)current) == RefInfoPTValue) {
             PITfree((RefInfo *)current);
          }
#endif /* PERSIST */
	}
#ifdef PERSIST
	current -> GCAttr = FREECHUNK;
#endif /* PERSIST */
	current = (AOAFreeChunk *)((char *)current + size);
	
      } while (((long *)current < end) &&
	       !AOAISALIVE(current));
	  
      freeChunkSize = (long)current - (long)freeChunkStart;
      freeMemInBlock += freeChunkSize;
            
      AOAInsertFreeElement(freeChunkStart, freeChunkSize);
            
      DEBUG_CODE(memoryAreaSize += freeChunkSize);
            
    }
  }
    
  return freeMemInBlock;
}


void GCInfo(void) 
{
  fprintf(output,"GCInfo:\n");
  fprintf(output,"  %8lu (IOAGC)\n", NumIOAGc);
  fprintf(output,"  %8lu (AOAGC)\n", NumAOAGc);
  fprintf(output,"  %8lu (AOABlocks)\n", AOABlocks);
  fprintf(output,"  %8lu (AOAKb)\n", totalAOASize/1024);

  DETAILEDSTAT_AOA({
    fprintf(output,"  %8lu (objectsInAOA)\n", objectsInAOA);
    fprintf(output,"  %8lu (sizeOfObjectsInAOA)\n", sizeOfObjectsInAOA);
  });
}

#if defined(RTDEBUG)
/* AOADisplayMemoryArea: */
void AOADisplayMemoryArea(long *start, long *end) 
{
  ;
}
#endif /* RTDEBUG */

void AOADisplayFreeList(void)
{ 
  long index, freeSpace;
  AOAFreeChunk *current;
  unsigned long live, dead;
  long freeOfSize;
  long blksize;

  freeSpace=0;
  fprintf(output, "(AOAFreelist:\n");
  fprintf(output, "    size  freespace   free    live  livesize  deadgraph\n");
  for (index=0; index < FreeListSmallMAX+FreeListLargeMAX; index++) {
    freeOfSize=0;
    
    if (AOAFreeListSize[index] || AOAInUseCount[index]) {
      if (index <= FreeListSmallMAX) {
	blksize = AOASmallIndex2Size(index);
	dead = AOAFreeListSize[index];
	live = AOAInUseCount[index];
	freeOfSize = dead*blksize;
      } else {
	blksize = AOASmallIndex2Size(FreeListSmallMAX) 
	  << (index-FreeListSmallMAX);
	dead = AOAFreeListSize[index];
	live = AOAInUseCount[index];
	current = AOAFreeList[index];
	while (current) {
	  freeOfSize += current->size;
	  current = current->next;
	}
      }

      fprintf(output, "0x%07X 0x%07X  %5lu %7lu 0x%07X ",
	      (int)blksize,
	      (int)freeOfSize,
	      dead, live, (int)AOAInUseSize[index]);
      
      dead = (dead+10-1)/10;  /* Scale graph by 10 */
      if (dead > 24) {
	dead = 24;
      }
      
      while (dead) {
	fprintf(output, "*");
	dead--;
      }
      
      fprintf(output, "\n");
      freeSpace += freeOfSize;
    }
  }
  fprintf(output, "   Total  0x%08X)\n", (int)freeSpace);

  fprintf(output, "Size of blocks in largelist:\n");
  for (index=FreeListSmallMAX; 
       index < FreeListSmallMAX+FreeListLargeMAX; 
       index++) {
    current = AOAFreeList[index];
    if (current) {
      fprintf(output, "[%d: ", (int)index);
      while (current) {
	fprintf(output, " 0x%08X", (int)(current->size));
	current = current->next;
      }
      fprintf(output, "]\n");
    }
  }
}


long AOAFreeListTotalFree(void)
{
  long res = 0;
  long blksize;
  int index;
  AOAFreeChunk *current;

  for (index=0; index < FreeListSmallMAX+FreeListLargeMAX; index++) {
    if (index <= FreeListSmallMAX) {
      blksize = AOASmallIndex2Size(index);
      res += blksize*AOAFreeListSize[index];
    } else {
      current = AOAFreeList[index];
      while (current) {
	res += current->size;
	current = current->next;
      }
    }
  }
  return res;
}

long AOAFreeListIndexGetStat(long index, long *min, long *max, 
			     long *usecount, long *usesize, 
			     long *freecount, long *freesize)
{
  AOAFreeChunk *current;

  if (!AOABaseBlock || 
      index < 0 || index >= FreeListSmallMAX+FreeListLargeMAX) {
    return 0;
  }

  *min = AOAAnyIndex2Size(index);
  *max = AOAAnyIndex2Size(index+1)-8;
  *usecount = AOAInUseCount[index];
  *usesize = AOAInUseSize[index];
  *freecount = AOAFreeListSize[index];
  *freesize = 0;
  current = AOAFreeList[index];
  while (current) {
    *freesize += current->size;
    current = current->next;
  }

  return 1;
}
