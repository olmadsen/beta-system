/*
 * BETA RUNTIME SYSTEM, Copyright (C) 1990 Mjolner Informatics Aps.
 * Mod: $RCSfile: block.c,v $, rel: %R%, date: $Date: 1992-06-03 15:16:31 $, SID: $Revision: 1.2 $
 * by Lars Bak
 */

#include "beta.h"

#define inBlock( theB, addr) (((BlockStart( theB)) <= (ptr(long)) addr) \
                              && ((ptr(long)) addr < theB->top) )

ref(Block) newBlock( size )
  int size;
{
  ref(Block) theBlock;

  theBlock = (ref(Block)) malloc( sizeof(struct Block) + size );
  
  if( theBlock != 0 ){
    theBlock->next  = 0;
    theBlock->top   = BlockStart( theBlock );
    theBlock->limit = (ptr(long)) ((long) BlockStart( theBlock) + (long) size);
  }
  return theBlock;
}

freeBlock(theBlock)
  ref(Block) theBlock;
{
  /* here theBlock->top - theBlock->limit bytes should be freed */
  free(theBlock);
}

int inArea( theBlock, theObj )
  ref(Block)  theBlock;
  ref(Object) theObj;
{
  while( theBlock != 0 ){
    if( inBlock( theBlock, theObj) ) return TRUE;
    theBlock = theBlock->next;
  }
  return FALSE;
}

