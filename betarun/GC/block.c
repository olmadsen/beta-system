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

#define inBlock( theB, addr) (((BlockStart( theB)) <= (ptr(long)) addr) \
                              && ((ptr(long)) addr < theB->top) )

#define inBlockUnused( theB, addr) ((theB->top <= (ptr(long)) addr) \
                              && ((ptr(long)) addr < theB->limit) )

ref(Block) newBlock( size )
  long size;
{
  ref(Block) theBlock;

  theBlock = (ref(Block)) MALLOC( sizeof(struct Block) + size );
  INFO_ALLOC(sizeof(struct Block) + size);
  
  
  if( theBlock != 0 ){
    theBlock->next  = 0;
    theBlock->top   = BlockStart( theBlock );
    theBlock->limit = (ptr(long)) ((long) BlockStart( theBlock) + (long) size);
  }
  return theBlock;
}

void freeBlock(theBlock)
     ref(Block) theBlock;
{
  FREE(theBlock);
}

long inArea( theBlock, theObj )
  ref(Block)  theBlock;
  ref(Object) theObj;
{
  while( theBlock != 0 ){
    if( inBlock( theBlock, theObj) ) return TRUE;
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
  int fd;
  int mmapflags;
  signed long startadr;
  Claim(!mmapHeap, "mmapInitial: mmapHeap!=0, calling twice?\n");
  Claim(!mmapHeapTop, "mmapInitial: mmapHeapTop!=0, calling twice?\n");
  Claim(!mmapHeapLimit, "mmapInitial: mmapHeapLimit!=0, calling twice?\n");
  INFO(fprintf(output, "(#mmapInitial(%08X))", (int)numbytes));
#if defined(hppa) || defined(sun4s) || defined(linux) || defined(sgi)
#ifdef sgi
  mmapflags = MAP_AUTORESRV | MAP_PRIVATE | MAP_FIXED;
#else
#ifdef linux
  mmapflags = MAP_PRIVATE | MAP_FIXED;
#else
  mmapflags = MAP_NORESERVE | MAP_PRIVATE | MAP_FIXED;
#endif
#endif
#define MMAPSTART 0x10000000
#define MMAPINCR  0x10000000
  fd = open("/dev/zero", O_RDWR);
  startadr = MMAPSTART;
  while (!mmapHeap && (!((startadr+numbytes) & (1<<31)))) {
    mmapHeap = mmap((void*)startadr, numbytes, PROT_NONE, mmapflags, fd,0);
    if (mmapHeap == MAP_FAILED) {
      mmapHeap = NULL;
      startadr += MMAPINCR;
    }
  }
  close(fd);
  if (mmapHeap == MAP_FAILED) {
    mmapHeap = 0;
    fprintf(output, "mmapInitial failed with errno %d\n", errno);
    BetaExit(1);
  }
#else
#ifdef nti
#define MMAPSTART 0x10000000
#define MMAPINCR  0x10000000
  startadr = MMAPSTART;
  while (!mmapHeap && (!((startadr+numbytes) & (1<<31)))) {
    mmapHeap = VirtualAlloc(startadr, numbytes, MEM_RESERVE, PAGE_NOACCESS);
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
}

void InsertGuardPage(void)
{
  mmapHeapTop = (char*)mmapHeapTop + MMAPPageSize;
}

ref(Block) reserveBlock(long numbytes)
{
  ref(Block) theBlock;
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

int extendBlock(ref(Block) theBlock, long numbytes)
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

  theBlock->limit = (ptr(long))((char*)theBlock + newnumbytes);
  INFO(fprintf(output, "Block at %08X-%08X)", 
	       (int)theBlock, (int)theBlock->limit));

  return 0;  
}

ref(Block) AllocateBlock(long numbytes)
{
  ref(Block) blk;
  long size = (numbytes+sizeof(Block)+MMAPPageSize-1) & ~(MMAPPageSize-1);
  blk = reserveBlock(size);
  if (!blk)
    return NULL;
  extendBlock(blk, numbytes);

  return blk;
}
#endif /* USEMMAP */

#ifdef RTDEBUG
long inAreaUnused( theBlock, theObj )
  ref(Block)  theBlock;
  ref(Object) theObj;
{
  while( theBlock != 0 ){
    if( inBlockUnused( theBlock, theObj) ) return TRUE;
    theBlock = theBlock->next;
  }
  return FALSE;
}
#endif

