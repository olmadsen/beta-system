/*
 * BETA RUNTIME SYSTEM, Copyright (C) 1990-2000 Mjolner Informatics Aps.
 * block.c
 * by Lars Bak, Peter Andersen, Peter Orbaek, Tommy Thorn, Jacob Seligmann
 * and Morten Grouleff.
 */
#include "beta.h"

#if defined(hppa) || defined(sun4s) || defined(linux) || defined(sgi) || defined(x86sol) || defined(macosx)
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <errno.h>
#endif


#ifdef MAC
Block * reserveProtectedBlock(long numbytes)
{
	return (Block *) 0x80000000;
}

#endif


#define inBlock( theB, addr) (((BlockStart( theB)) <= (long *) addr) \
                              && ((long *) addr < theB->limit) )
#define inBlockUnused( theB, addr) ((theB->top <= (long *) addr) \
                              && ((long *) addr < theB->limit) )

static long RoundToPage(long size)
{
  return (size+MMAPPageSize-1) & ~(MMAPPageSize-1);
}

Block *
newBlock(long size)
{
  Block * theBlock;
  int numbytes = sizeof(Block) + size;

#ifdef USEMMAP
  unsigned long sizeAlign;
  sizeAlign = RoundToPage(numbytes);
  theBlock = AllocateBlock(sizeAlign);
#else
#ifdef nti
  /* Windows sometimes gives you unaligned allocations.  
   */
  numbytes += 8;
  if ((theBlock = (Block *)MALLOC(numbytes)) != 0) {
    theBlock->orig_ptr = theBlock;
    theBlock = (Block *)ObjectAlign((unsigned long)(theBlock));
  }
#else
  theBlock = (Block *) MALLOC(numbytes);
  if (theBlock){
    theBlock->orig_ptr = theBlock;
  }
#endif /* nti */
#endif /* USEMMAP */
  INFO_ALLOC(numbytes);
  
  if( theBlock != 0 ){
    theBlock->next  = 0;
    theBlock->top   = BlockStart( theBlock );
    theBlock->limit = (long *) ((long) BlockStart( theBlock) + (long) size);
  }
  return theBlock;
}

/* You can't free a block obtained this way! 
 * Used by persistence!
 */

void *newProtectedArea(unsigned long size)
{
  /* Round to next page */
  unsigned long rsize = RoundToPage(size);

#ifdef UNIX
  /* Allocate one page of slop */
  unsigned long slopsize = RoundToPage(rsize+1);

  /* The actual allocation */
  void *theArea = (Block *)MALLOC(slopsize);

  /* If we failed! */
  if (!theArea)
      return theArea;

  /* Round up to next page boundary.  This is why we can't free again! */
  theArea = (void *)RoundToPage((unsigned long)theArea);

  if (mprotect(theArea, rsize, PROT_NONE)) {
    fprintf(output, "newProtectedArea: mprotect failed with errno %d\n", errno);
    return 0;
  }
#else
#ifdef nti
  void *theArea =
      VirtualAlloc(0, rsize, MEM_RESERVE | MEM_COMMIT, PAGE_NOACCESS);
  if (!theArea) {
     fprintf(output, "extendBlock: VirtualAlloc failed with GetLastError %ld\n", 
	    GetLastError());
    return (void *)1;
  }  
#else
#ifdef ppcmac
	void *theArea = (void *) 0x80000000;
#else
#ifdef macosx
    /* Allocate one page of slop */
  unsigned long slopsize = RoundToPage(rsize+1);

  /* The actual allocation */
  void *theArea = (Block *)MALLOC(slopsize);

  /* If we failed! */
  if (!theArea)
      return theArea;

  /* Round up to next page boundary.  This is why we can't free again! */
  theArea = (void *)RoundToPage((unsigned long)theArea);

  if (mprotect(theArea, rsize, PROT_NONE)) {
    fprintf(output, "newProtectedArea: mprotect failed with errno %d\n", errno);
    return 0;
  }
#else
#error Unknown architecture for mmap
#endif
#endif /* ppcmac/other */
#endif /* nti  */
#endif /* unix */
  
  return theArea;
}

void freeBlock(Block * theBlock)
{
#ifdef USEMMAP
#else
  FREE(theBlock->orig_ptr);
#endif /* USEMMAP */
}

#if 0
long inArea(Block *  theBlock, Object * theObj)
{
    while( theBlock != 0 ){
        
        if( inBlock( theBlock, theObj) ) {
            return TRUE;
        }
        theBlock = theBlock->next;
    }
    return FALSE;
}
#endif

#ifdef USEMMAP
/* Flags for mmap:
 * Use MAP_PRIVATE to make sure that children get their own copy.
 * Use MAP_NORESERVE so that no swapspace is reserved for pages not yet used.
 *
 * The program should mmap() a rather large area at startup, but protect it 
 * all so that it cannot be read/written/executed.
 *
 * Then use extendBlock to reserve some of that huge space using mprotect()
 * if theBlock is NULL, a new block is allocated.
 */

void mmapInitial(unsigned long numbytes)
{
#if defined(hppa) || defined(sun4s) || defined(linux) || defined(sgi)
  int fd = 0;
  int mmapflags = 0;
#endif
  signed long startadr = 0;
  Claim(mmapHeap == NULL, "mmapInitial: mmapHeap!=0, calling twice?\n");
  Claim(mmapHeapTop == NULL, "mmapInitial: mmapHeapTop!=0, calling twice?\n");
  Claim(mmapHeapLimit == NULL, "mmapInitial: mmapHeapLimit!=0, calling twice?\n");
  INFO(fprintf(output, "(#mmapInitial(%08X) ", (int)numbytes));

#define MMAPSTART 0x10000000
#define MMAPINCR  0x10000000

#if defined(hppa) || defined(sun4s) || defined(linux) || defined(sgi)
#ifdef sgi
  mmapflags = MAP_AUTORESRV | MAP_PRIVATE;
#endif /* sgi */

#ifdef linux
  mmapflags = MAP_PRIVATE;
#undef MMAPSTART
#define MMAPSTART 0x10000000
#ifndef MAP_FAILED
#define MAP_FAILED -1
#endif
#endif /* linux */

#ifdef hpux9pa
  mmapflags = MAP_PRIVATE | MAP_VARIABLE | MAP_ANONYMOUS;
#ifndef MAP_FAILED
#define MAP_FAILED -1
#endif
#endif /* hpux9pa */

#ifdef sun4s
#if MMAPANYADDR
  mmapflags = MAP_NORESERVE | MAP_PRIVATE;
#else
  mmapflags = MAP_NORESERVE | MAP_PRIVATE | MAP_FIXED;
#endif
#endif /* sun4s */

#ifndef hpux9pa
  fd = open("/dev/zero", O_RDWR);
#endif
  startadr = MMAPSTART;
  while (!mmapHeap && (!((startadr+numbytes-1) & (1<<31)))) {
#if 0
    DEBUG_CODE({
      fprintf(output, 
	      "Calling mmap(0x%08x,0x%08x,0x%08x,0x%08x,0x%08x,0x%08x\n",
	      (int)startadr, (int)numbytes, PROT_NONE, (int)mmapflags, fd,0);
    });
#endif
#if MMAPANYADDR
    mmapHeap = mmap(NULL, numbytes, PROT_NONE, mmapflags, fd,0);
#else
    mmapHeap = mmap((void*)startadr, numbytes, PROT_NONE, mmapflags, fd,0);
#endif
#if 0
    DEBUG_CODE(fprintf(output, "mmap returned 0x%08x\n", mmapHeap));
#endif
    if ((long)mmapHeap == (long)MAP_FAILED) {
      mmapHeap = NULL;
#if MMAPANYADDR
      numbytes /= 2;
#else
      startadr += MMAPINCR;
      if ((startadr+numbytes-1) & (1<<31)) {
	startadr = MMAPSTART;
	numbytes /= 2;
	if (!numbytes) {
	  exit(1);
	}
      }
#endif
    }
  }
#ifndef hpux9pa
  close(fd);
#endif
  if (!mmapHeap) {
    mmapHeap = 0;
    fprintf(output, "mmapInitial failed with errno %d:%s\n", 
	    errno, strerror(errno));
    BetaExit(1);
  }
#else
#ifdef nti
#define MMAPSTART 0x10000000
#define MMAPINCR  0x10000000
#if MMAPANYADDR
  while (!mmapHeap) {
    mmapHeap = VirtualAlloc(NULL, numbytes, 
			    MEM_RESERVE, PAGE_NOACCESS);
    if (!mmapHeap) {
      DEBUG_CODE({
	fprintf(output, "mmapInitial failed with GetLastError %d, "
		"trying half size %d\n", GetLastError(), numbytes);
      });
      numbytes /= 2;
      if (!numbytes) {
	exit(1);
      }
    }
  }
#else
  startadr = MMAPSTART;
  while (!mmapHeap && (!((startadr+numbytes-1) & (1<<31)))) {
    mmapHeap = VirtualAlloc((void*)startadr, numbytes, 
			    MEM_RESERVE, PAGE_NOACCESS);
    startadr += MMAPINCR;
  }
  while (!mmapHeap) {
    fprintf(output, "mmapInitial failed with GetLastError %d, "
	    "trying without placement\n", 
	    GetLastError());
    mmapHeap = VirtualAlloc(NULL, numbytes, 
			    MEM_RESERVE, PAGE_NOACCESS);
    numbytes /= 2;
    fprintf(output, "mmapInitial failed with GetLastError %d, "
	    "trying half size %d\n", GetLastError(), numbytes);
    if (!numbytes) {
      exit(1);
    }
  }
#endif
  if (!mmapHeap) {
    fprintf(output, "mmapInitial failed with GetLastError %d\n", 
	    GetLastError());
    BetaExit(1);
  }
#else
#ifdef ppcmac
  fprintf(output, "Not implemented yet!\n");
  BetaExit(1);
#else
#error Unknown architecture for mmap
#endif /* ppcmac/other */
#endif /* nti  */
#endif /* unix */

  mmapHeapTop   = mmapHeap;
  mmapHeapLimit = (void*)((char*)mmapHeap + numbytes);
  INFO(fprintf(output, "At %08X-%08X)", 
	       (int)mmapHeap, (int)mmapHeapLimit));
}

int InsertGuardPage(void)
{
  if ((void*)((char*)mmapHeapTop + MMAPPageSize) >= mmapHeapLimit) {
    /* Out of memory */
    return 0;
  }

  mmapHeapTop = (char*)mmapHeapTop + MMAPPageSize;
  return 1;
}

unsigned long mmapUnusedSize(void)
{
  return (char*)mmapHeapLimit - (char*)mmapHeapTop;
}

Block * reserveBlock(long numbytes)
{
  Block * theBlock;
  numbytes = RoundToPage(numbytes);
  INFO(fprintf(output, "(#reserveBlock(%08X) at %08X. ", 
	       (int)numbytes, (int)mmapHeapTop));
  Claim((long)mmapHeap, "reserveBlock: mmapHeap=0");
  Claim((long)mmapHeapTop, "reserveBlock: mmapHeapTop=0");
  Claim((long)mmapHeapLimit, "reserveBlock: mmapHeapLimit=0");
  Claim(numbytes >= 0, "reserveBlock: with negative numbytes");
  Claim(((numbytes & (MMAPPageSize-1))==0), "reserveBlock: numbytes must be aligned to MMAPPageSize");

  if ((void*)((char*)mmapHeapTop + numbytes) >= mmapHeapLimit) {
    /* Out of memory */
    return NULL;
  }

#if defined(hppa) || defined(sun4s) || defined(linux) || defined(sgi)
  if (mprotect(mmapHeapTop, MMAPPageSize, 
	       PROT_READ|PROT_WRITE|PROT_EXEC)) {
    fprintf(output, "reserveBlock: mprotect failed with errno %d\n", errno);
    return 0;
  }
#else
#ifdef nti
  if (mmapHeapTop != VirtualAlloc(mmapHeapTop, MMAPPageSize, MEM_COMMIT, 
			       PAGE_EXECUTE_READWRITE)) {
    fprintf(output, "reserveBlock: VirtualAlloc failed with GetLastError %d\n",
	    GetLastError());
    return 0;
  }  
#else
#ifdef ppcmac
  fprintf(output, "Not implemented yet!\n");
  BetaExit(1);
#else
#error Unknown architecture for mmap
#endif /* ppcmac/other */
#endif /* nti  */
#endif /* unix */

  theBlock = mmapHeapTop;
  mmapHeapTop = (void*)((char*)mmapHeapTop + numbytes);
  Claim(mmapHeapTop < mmapHeapLimit, 
	"reserveBlock: Reserved more than mmapInital got as maximum");
  theBlock->next         = NULL;
  theBlock->top          = BlockStart( theBlock );
  theBlock->limit        = theBlock->top;
  theBlock->mmaplimit    = (long*)((char*)theBlock + MMAPPageSize);
  theBlock->mmapmaxlimit = (long*)mmapHeapTop;

  INFO(fprintf(output, "Got block at %08X-%08X)", 
	       (int)theBlock, (int)theBlock->mmapmaxlimit));

  return theBlock;
}

Block * reserveProtectedBlock(long numbytes)
{
  Block * theBlock;
  numbytes = RoundToPage(numbytes);
  INFO(fprintf(output, "(#reserveBlock(%08X))", (int)numbytes));
  Claim((long)mmapHeap, "reserveBlock: mmapHeap=0");
  Claim((long)mmapHeapTop, "reserveBlock: mmapHeapTop=0");
  Claim((long)mmapHeapLimit, "reserveBlock: mmapHeapLimit=0");
  Claim(numbytes >= 0, "reserveBlock: with negative numbytes");
  Claim(((numbytes & (MMAPPageSize-1))==0), "reserveBlock: numbytes must be aligned to MMAPPageSize");

  if ((void*)((char*)mmapHeapTop + numbytes) >= mmapHeapLimit) {
    /* Out of memory */
    return NULL;
  }

  theBlock = mmapHeapTop;
  mmapHeapTop = (void*)((char*)mmapHeapTop + numbytes);
  Claim(mmapHeapTop < mmapHeapLimit, 
	"reserveBlock: Reserved more than mmapInital got as maximum");
  INFO(fprintf(output, "Got protected block at %08X)", (int)theBlock));

  return theBlock;
}

int extendBlock(Block * theBlock, long numbytes)
{
  int newnumbytes;
  Claim((long)mmapHeap, "extendBlock with mmapHeap=0");
  Claim((long)theBlock, "extendBlock with theBlock=0");
  Claim((long)numbytes >= 0, "extendBlock with negative numbytes");
  INFO(fprintf(output, "(#extendBlock(%08X) ", (int)numbytes));

  newnumbytes =  (char*)theBlock->limit - (char*)theBlock;
  newnumbytes += numbytes;
  if ((char*)theBlock + newnumbytes > (char*)theBlock->mmapmaxlimit) {
    fprintf(output, "extendBlock: Trying to extend beyond reserved space\n");
    return 1;
  }
#if defined(hppa) || defined(sun4s) || defined(linux) || defined(sgi)
  if (mprotect((void*)theBlock, newnumbytes, PROT_READ|PROT_WRITE|PROT_EXEC)) {
    fprintf(output, "extendBlock: mprotect failed with errno %d\n", errno);
    return 1;
  }
#else
#ifdef nti
  if (theBlock != VirtualAlloc(theBlock, newnumbytes, MEM_COMMIT , 
			       PAGE_EXECUTE_READWRITE)) {
    fprintf(output, "extendBlock: VirtualAlloc failed with GetLastError %d\n", 
	    GetLastError());
    return 1;
  }  
#else
#ifdef ppcmac
  fprintf(output, "Not implemented yet!\n");
  BetaExit(1);
#else
#error Unknown architecture for mmap
#endif /* ppcmac/other */
#endif /* nti  */
#endif /* unix */

  theBlock->limit = (long *)((char*)theBlock + newnumbytes);
  INFO(fprintf(output, "Block at %08X-%08X)", 
	       (int)theBlock, (int)theBlock->limit));

  return 0;  
}

Block * AllocateBlock(long numbytes)
{
  Block * blk;
  long size = (numbytes+sizeof(Block)+MMAPPageSize-1) & ~(MMAPPageSize-1);
  blk = reserveBlock(size);
  if (!blk)
    return NULL;
  extendBlock(blk, numbytes);

  return blk;
}
#endif /* USEMMAP */

#ifdef RTDEBUG
long inAreaUnused(Block *  theBlock, Object * theObj)
{
  while( theBlock != 0 ){
    if( inBlockUnused( theBlock, theObj) ) return TRUE;
    theBlock = theBlock->next;
  }
  return FALSE;
}
#endif

