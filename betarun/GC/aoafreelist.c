/*
 * BETA RUNTIME SYSTEM, Copyright (C) 1991-98 Mjolner Informatics Aps.
 * aoafreelist.c
 * Peter Andersen, Morten Grouleff, Stephan Korsholm
 */

#include "beta.h"

/************************ THE AOA FREE LIST ***************************
 * AOA freelist description:
 *   All chunks are multiples of 8 bytes.
 *   The freelist is organized as an array with 31 entries,
 *   each forming a list of free chunks of that size.
 *   One exception is index 31, which forms a list of chunks
 *   of variable size, the smallest being 256 bytes:
 *   ASSUMPTION: It is assumed that no objects of size 8
 *   are allocated. This is the case today!
 *         
 *   AOAFreeList:
 *           _____      ___     ___     ___
 *     0:   |     |--->|___|-->|___|-->|___| chunks size 8 (numbytes/8-1)
 *     1:   |     |--->...                   chunks size 16
 *     2:   |     |--->...                   chunks size 24  
 *     3:   |     |--->...                   chunks size 32  
 *     4:   |     |--->...                   chunks size 40  
 *         ...
 *     30:  |     |--->...                   chunks size 248
 *     31:  |_____|--->...                   chunks size 256 and above
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

#define FreeListMAX 31

/* LOCAL TYPES */
typedef struct AOAFreeChunk {
  struct AOAFreeChunk *next;
  unsigned long GCAttr /* Should be 0 when in free list or dead  */;
  unsigned long size   /* May never be accessed by objects less that
			* 16 bytes
			*/;
} AOAFreeChunk;

/* LOCAL FUNCTIONS */
static long AOAFreeListIndex(long numbytes);
static void AOAInsertFreeElement(AOAFreeChunk *freeChunk, long numbytes);
static AOAFreeChunk *AOAFindInFree(unsigned long numbytes);

/* LOCAL VARIABLES */
static AOAFreeChunk *AOAFreeList[FreeListMAX+1];
static long sizeOfObjectsInAOA = 0;
static long objectsInAOA = 0;

/* IMPLEMENTATION */

/* AOAFreeListIndex:
 *    finds an index in the AOAFreeList in the range [0..FreeListMAX]
 *    for the given size.
 */
static long AOAFreeListIndex(long numbytes)
{
  long index;
    
  index = numbytes / 8 - 1;
  if (index <= FreeListMAX) {
    return index;
  }
  return FreeListMAX;
}

/* AOAInsertFreeElement:
 *   adds a chunk to the AOAFreeList. 
 */
static void AOAInsertFreeElement(AOAFreeChunk *freeChunk, long numbytes)
{ 
  long index = AOAFreeListIndex(numbytes);
    
#ifdef RTDEBUG  
  if (!freeChunk) {
    fprintf(stdout,"AOAInsertFreeElement: Inserting NULL\n");
    BetaExit(1);
  }
#endif
  freeChunk -> next = AOAFreeList[index];
  AOAFreeList[index] = freeChunk;
  freeChunk -> GCAttr = FREECHUNK;
  freeChunk -> size = numbytes;
}

/* AOAScanMemoryArea:
 */
long AOAScanMemoryArea(long *start, long *end) 
{
  AOAFreeChunk *current;
  long size;
  long freeMemInBlock;
  DEBUG_CODE(long memoryAreaSize = 0);
  
  INFO_AOA(collectedMem = 0);
  DEBUG_AOA(largestFreeChunk = 0);
  
  freeMemInBlock = 0;
  current = (AOAFreeChunk *)start;
  while((long *)current < end) {
    if (AOAISALIVE(current)) {
      /* Leave as is */
      size = 4 * ObjectSize((Object *)current);
      DEBUG_AOA(memoryAreaSize += size);
      current->GCAttr = DEADOBJECT;
      current = (AOAFreeChunk *)((char *)current + size);
    } else {
      /* DEAD or FREE or Error */
      long freeChunkSize;
      AOAFreeChunk *freeChunkStart;
	  
      /* Group chunks together if possible */
      freeChunkStart = current;
      do {
#ifdef RTDEBUG
	if (!AOAISFREE(current) && !AOAISDEAD(current)) {
	  fprintf(output, "AOAScanMemoryArea: "
		  "Bogus GCAttr value in AOAFreeChunk:%d\n",
		  current->GCAttr);
	  DEBUG_CODE(Illegal());
	  BetaExit(1);
	}
#endif
	if (AOAISFREE(current)) {
	  size = current->size;
	} else {
	  size = 4 * ObjectSize((Object *)current);
	  DEBUG_AOA(objectsInAOA--);
	  DEBUG_AOA(sizeOfObjectsInAOA -= size);
	  INFO_AOA(collectedMem += size);
	}
	current = (AOAFreeChunk *)((char *)current + size);
                
      } while (((long *)current < end) &&
	       !AOAISALIVE(current));
	  
      freeChunkSize = (long)current - (long)freeChunkStart;
      freeMemInBlock += freeChunkSize;
            
      AOAInsertFreeElement(freeChunkStart, freeChunkSize);
            
      DEBUG_AOA(
          if (freeChunkSize > largestFreeChunk) {
              largestFreeChunk = freeChunkSize;
          });
      
      DEBUG_AOA(memoryAreaSize += freeChunkSize);
            
    }
  }
    
  return freeMemInBlock;
}

/* AOADisplayMemoryArea: */
void AOADisplayMemoryArea(long *start, long *end) 
{
  ;
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
 *      5. Search for chunk in last index.
 *    If unsuccessfull, the function returns 0.
 *    Should only be called from AOAAllocateFromFreeList.
 */

static AOAFreeChunk *AOAFindInFree(unsigned long numbytes)
{
  AOAFreeChunk *newChunk = NULL, *current, *bestFit;
  AOAFreeChunk *restChunk;
  AOAFreeChunk **previous, **bestFitPrevious;
  unsigned long index = AOAFreeListIndex(numbytes);
  unsigned long sizeOfRestChunk, sizeOfFoundChunk, stepSize, bestFitSize;

  /* We want to step sizes k*numbytes */
  /* stepSize = index + 1; */
  stepSize = 2;
    
  while (index < FreeListMAX) {
    if (AOAFreeList[index]) {
      /* A free chunk has been found. Now split it into two
       * pieces, the one is returned to hold the new object, the
       * rest (if any) is inserted in the freelist.
       */
      newChunk = AOAFreeList[index];
      sizeOfFoundChunk = newChunk -> size;
            
      restChunk = (AOAFreeChunk *)((char *)AOAFreeList[index] + numbytes);
      sizeOfRestChunk = sizeOfFoundChunk - numbytes;
            
      /* remove the chunk from the freelist */
      AOAFreeList[index] = AOAFreeList[index] -> next;
            
      /* insert the remaining chunk in the free list */
      if (sizeOfRestChunk) {
	AOAInsertFreeElement(restChunk, sizeOfRestChunk);
      }
      return newChunk;
    }
    index += stepSize;
    stepSize = 1;
        
    /* There should be a comment here explaining this, but there
     * aren't :-) */
  }
    
  /* No small free chunk was found, so we have to try the large
   * chunks. Since these might have different sizes, we need to
   * scan the entire freelist and cannot just look at the first
   * element as above.
   */
    
  current = AOAFreeList[FreeListMAX];
  previous = &AOAFreeList[FreeListMAX];
  bestFitPrevious = previous;
  bestFitSize = 0x7FFFFFFF;
  bestFit = NULL;
    
  while (current) {
    if ((current -> size >= numbytes) &&
	(current -> size - numbytes != 8) &&
	(current -> size < bestFitSize)) {
      bestFit = current;
      bestFitSize = current -> size;
      bestFitPrevious = previous;
    }
    previous = &(current -> next);
    current = current -> next;
  }
    
  if (bestFit) {
    /* A chunk large enough has been found, and it is split
     * into two parts as above.
     */
    sizeOfFoundChunk = bestFit -> size;
        
    restChunk = (AOAFreeChunk *)((char *)bestFit + numbytes);
    sizeOfRestChunk = sizeOfFoundChunk - numbytes;
        
    /* remove the chunk from the freelist */
    *bestFitPrevious = bestFit -> next;
        
    /* insert the remaining chunk in the free list */
    if (sizeOfRestChunk) {
      AOAInsertFreeElement(restChunk, sizeOfRestChunk);
    }
    return bestFit;
  }
    
  return NULL;
}


/* AOAAllocateFromFreeList:
 * Allocates a chunk of memory in AOA by searching the freelists
 */
Object *AOAAllocateFromFreeList(long numbytes) 
{
  Object *newObj = NULL;
    
  /* Only chunks of sizes that are multiples of 8 bytes may be
   * inserted in the free list.
   */

  if ((numbytes >= 16) && ((numbytes % 8) == 0)) {
    newObj = (Object *)AOAFindInFree(numbytes);
    DEBUG_AOA(
	      if (newObj) {
                objectsInAOA++;
                sizeOfObjectsInAOA += numbytes;
                memset(newObj, 0, numbytes);
	      });
        
  } else {
    fprintf(stdout, "AOAAllocateFromFreeList: Illegal size (0x%X)\n", (int)numbytes);
    BetaExit(1);
  }
    
  DEBUG_AOA(
	    if (newObj) {
	      if (!inAOA(newObj)) {
                fprintf(stdout, "AOAAllocateFromFreeList: Reference (0x%X) is not in AOA!\n", (int)newObj);
                BetaExit(1);
	      }
            
	      if (((unsigned)newObj & 7) != 0) {
                fprintf(stdout, "AOAAllocateFromFreeList: Reference (0x%X) is not alligned\n", (int)newObj);
                BetaExit(1);
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
    
  if ((numbytes >= 16) && ((numbytes % 8) == 0)) {
    AOAInsertFreeElement((AOAFreeChunk *)chunk, numbytes);
    DEBUG_AOA(objectsInAOA--);
    DEBUG_AOA(sizeOfObjectsInAOA -= numbytes);
        
  } else {
    fprintf(stdout, "AOAFreeInFreeList: Illegal size (0x%X)\n", (int)numbytes);
    BetaExit(1);
  }
}

/* AOAInsertFreeBlock:
 *   Inserts a block into the freelists.
 */
void AOAInsertFreeBlock(char *block, long numbytes) 
{
  if ((numbytes >= 16) && ((numbytes % 8) == 0)) {
    AOAInsertFreeElement((AOAFreeChunk *)block, numbytes);
  } else {
    fprintf(stdout, "AOAFreeInFreeList: Illegal size (0x%X)\n", (int)numbytes);
    BetaExit(1);
  }
}

/* AOACleanFreeList:
 *   initializes the AOAFreeList 
 */
void AOACleanFreeList(void)
{ 
  long index;
  for (index=0; index<=FreeListMAX; index++) {
    AOAFreeList[index] = (AOAFreeChunk *)NULL;
  }
}

void AOADisplayFreeList(void)
{ 
  long index, freeSpace;
  AOAFreeChunk *current;
    
  freeSpace=0;
  fprintf(output, "(AOAFreelist:\n");
  fprintf(output, "  [size][ freespace ] (entries)\n");    
  for(index=0;index<=FreeListMAX; index++) {
    long numEntries;
    long freeOfSize;
        
    numEntries=0;
    freeOfSize=0;
        
    current = AOAFreeList[index];
    while(current) {
      freeOfSize += current -> size;
      current = current -> next;
      numEntries += 1;
    }
        
    fprintf(output, "  [%4lu][0x%8X] ( %5lu ) ",
	    (unsigned long)((index + 1) * 8),
	    (int)freeOfSize,
	    (unsigned long)numEntries);
        
    if (numEntries > 40) {
      numEntries = 40;
    }
        
    while (numEntries) {
      fprintf(output, "*");
      numEntries--;
    }
        
    fprintf(output, "\n");
    freeSpace += freeOfSize;
  }
  fprintf(output, "        [0x%8X])\n", (int)freeSpace);
}

void GCInfo(void) 
{
  fprintf(output,"GCInfo:\n");
  fprintf(output,"  %8lu (IOAGC)\n", NumIOAGc);
  fprintf(output,"  %8lu (AOAGC)\n", NumAOAGc);
  fprintf(output,"  %8lu (AOABlocks)\n", AOABlocks);
  fprintf(output,"  %8lu (objectsInAOA)\n", objectsInAOA);
  fprintf(output,"  %8lu (sizeOfObjectsInAOA)\n", sizeOfObjectsInAOA);
  fprintf(output,"  %8lu (AOABlockSize)\n", AOABlockSize);
}
    
