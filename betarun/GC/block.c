/*
 * BETA RUNTIME SYSTEM, Copyright (C) 1990-94 Mjolner Informatics Aps.
 * block.c
 * by Lars Bak, Peter Andersen, Peter Orbaek, Tommy Thorn, and Jacob Seligmann
 */
#include "beta.h"

#if defined(hppa) || defined(sun4s) || defined(linux) || defined(sgi)
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <errno.h>
#endif

#define inBlock( theB, addr) (((BlockStart( theB)) <= (long *) addr) \
                              && ((long *) addr < theB->limit) )
#define inBlockUnused( theB, addr) ((theB->top <= (long *) addr) \
                              && ((long *) addr < theB->limit) )

Block * newBlock(long size)
{
  Block * theBlock;
  unsigned long sizeAlign;

#ifdef USEMMAP
  sizeAlign = (size + sizeof(Block) + 8191) & ~8191;
  theBlock = reserveBlock(sizeAlign);
#else
  theBlock = (Block *) MALLOC( sizeof(Block) + size );
#endif /* USEMMAP */
  INFO_ALLOC(sizeof(Block) + size);
  
  if( theBlock != 0 ){
    theBlock->next  = 0;
    theBlock->top   = BlockStart( theBlock );
    theBlock->limit = (long *) ((long) BlockStart( theBlock) + (long) size);
    theBlock -> dummy = (void *)UNKNOWNSTORE;
    theBlock -> id = UNKNOWNID;
  }
  return theBlock;
}

void freeBlock(Block * theBlock)
{
  FREE(theBlock);
}

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
  int fd = 0;
  int mmapflags = 0;
  signed long startadr = 0;
  Claim(mmapHeap == NULL, "mmapInitial: mmapHeap!=0, calling twice?\n");
  Claim(mmapHeapTop == NULL, "mmapInitial: mmapHeapTop!=0, calling twice?\n");
  Claim(mmapHeapLimit == NULL, "mmapInitial: mmapHeapLimit!=0, calling twice?\n");
  INFO(fprintf(output, "(#mmapInitial(%08X) ", (int)numbytes));

#define MMAPSTART 0x10000000
#define MMAPINCR  0x10000000

#if defined(hppa) || defined(sun4s) || defined(linux) || defined(sgi)
#ifdef sgi
  mmapflags = MAP_AUTORESRV | MAP_PRIVATE | MAP_FIXED;
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
  mmapflags = MAP_NORESERVE | MAP_PRIVATE | MAP_FIXED;
#endif /* sun4s */

#ifndef hpux9pa
  fd = open("/dev/zero", O_RDWR);
#endif
  startadr = MMAPSTART;
  while (!mmapHeap && (!((startadr+numbytes-1) & (1<<31)))) {
    mmapHeap = mmap((void*)startadr, numbytes, PROT_NONE, mmapflags, fd,0);
    if ((long)mmapHeap == (long)MAP_FAILED) {
      mmapHeap = NULL;
      startadr += MMAPINCR;
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
  startadr = MMAPSTART;
  while (!mmapHeap && (!((startadr+numbytes-1) & (1<<31)))) {
    mmapHeap = VirtualAlloc((void*)startadr, numbytes, 
			    MEM_RESERVE, PAGE_NOACCESS);
    startadr += MMAPINCR;
  }
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
  INFO(fprintf(output, "At %08X)", (int)mmapHeap));
}

void InsertGuardPage(void)
{
  mmapHeapTop = (char*)mmapHeapTop + MMAPPageSize;
}

Block * reserveBlock(long numbytes)
{
  Block * theBlock;
  INFO(fprintf(output, "(#reserveBlock(%08X))", (int)numbytes));
  Claim((long)mmapHeap, "reserveBlock: mmapHeap=0");
  Claim((long)mmapHeapTop, "reserveBlock: mmapHeapTop=0");
  Claim((long)mmapHeapLimit, "reserveBlock: mmapHeapLimit=0");
  Claim(numbytes >= 0, "reserveBlock: with negative numbytes");
  Claim((numbytes & 8191)==0, "reserveBlock: numbytes must be aligned to 8Kb");

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

  INFO(fprintf(output, "Got block at %08X)", (int)theBlock));

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

