/*
 * BETA RUNTIME SYSTEM, Copyright (C) 1991-98 Mjolner Informatics Aps.
 * aoafreelist.c
 * by Lars Bak, Peter Andersen, Peter Orbaek, Tommy Thorn, 
 *    Jacob Seligmann, Morten Grouleff
 */
#include "beta.h"

#ifdef LIN

/************************ THE AOA FREE LIST ***************************
 * AOA freelist description:
 *   The smallest chunk of memory that can be in the freelist 
 *   is 16 bytes. 
 *   All chunks are multiples of 8 bytes.
 *   The freelist is organized as an array with 31 entries,
 *   each forming a list of free chunks of that size.
 *   One exception is index 31, which forms a list of chunks
 *   of variable size, the smallest being 260 bytes:
 *   ASSUMPTION: It is assumed that no objects of size 8
 *   are allocated. This is the case today!
 *         
 *   AOAFreeList:
 *           _____      ___     ___     ___
 *     0:   |     |--->|___|-->|___|-->|___| chunks size 16 (numbytes/8-2)
 *     1:   |     |--->...                   chunks size 24
 *     2:   |     |--->...                   chunks size 32  
 *     3:   |     |--->...                   chunks size 40  
 *     4:   |     |--->...                   chunks size 48  
 *         ...
 *     30:  |     |--->...                   chunks size 256
 *     31:  |_____|--->...                   chunks size 260 and above
 *
 *   FIXME: This is probably not the smartest algorithm for the large
 *   objects. Possibly a variant where objects of various size
 *   *ranges* are indexed for the large object (as in LVRA) should
 *   be adopted.
 *          
 *   The linked list elements each look like this:
 *         
 *   AOAFreeChunk:
 *      __________ 
 *     | numbytes |
 *     |   GC=0   |
 *     |   next   |-->
 *     | ........ |
 *         
 */

#define FreeListMAX 31

typedef struct AOAFreeChunk {
  unsigned long numbytes;
  unsigned long GCAttr /* Should be 0 when in free list or dead */;
  struct AOAFreeChunk *next;
} AOAFreeChunk;

static AOAFreeChunk *AOAFreeList[FreeListMAX+1];

/* AOAFreeListIndex:
 *    finds an index in the AOAFreeList in the range [0..FreeListMAX]
 *    for the given size.
 */

static long AOAFreeListIndex(unsigned long numbytes)
{ 
  long index = 0; 
  /* ... */
  return index; 
}


/* AOACleanFreeList:
 *   initializes the AOAFreeList 
 */
static void AOACleanFreeList(void)
{ 
  long index;
  for (index=0; index<=FreeListMAX; index++) 
    AOAFreeList[index] = 0;
}

/* AOAInsertFreeElement:
 *   adds an object to the AOAFreeList. 
 */
static void AOAInsertFreeElement(Object *freeObj)
{ 
  /* ... */
  return;
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
 */
Object *AOAFindInFree(unsigned long numbytes)
{
  Object *newObj = 0;
  /* ... */
  return newObj;
}

#ifdef RTDEBUG
static void AOADisplayFreeList(void)
{ 
  long index;

  fprintf(output, "#(Free chunks in AOAFreeList: ");
  for(index=0;index<=FreeListMAX; index++)
    /* ... */
    ;
  fprintf(output, ")\n");
}
#endif /* RTDEBUG */
#endif /* LIN */
