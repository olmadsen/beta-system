/*
 * BETA RUNTIME SYSTEM, Copyright (C) 1990-94 Mjolner Informatics Aps.
 * block.c
 * by Lars Bak, Peter Andersen, Peter Orbaek, Tommy Thorn, and Jacob Seligmann
 */

#include "beta.h"

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

#ifdef RTDEBUG
long inUnusedArea( theBlock, theObj )
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

