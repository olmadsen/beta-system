/*
 * BETA RUNTIME SYSTEM, Copyright (C) 1990-93 Mjolner Informatics Aps.
 * block.c
 * by Lars Bak, Peter Andersen, Peter Orbaek and Tommy Thorn
 */

#include "beta.h"

#define inBlock( theB, addr) (((BlockStart( theB)) <= (ptr(long)) addr) \
                              && ((ptr(long)) addr < theB->top) )

ref(Block) newBlock( size )
  long size;
{
  ref(Block) theBlock;

  theBlock = (ref(Block)) MALLOC( sizeof(struct Block) + size );
  
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

