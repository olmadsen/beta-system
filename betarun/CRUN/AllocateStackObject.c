/*
 * BETA C RUNTIME SYSTEM, Copyright (C) 1990,91,92 Mjolner Informatics Aps.
 * Mod: $RCSfile: AllocateStackObject.c,v $, rel: %R%, date: $Date: 1992-06-06 03:57:15 $, SID: $Revision: 1.2 $
 * by Peter Andersen and Tommy Thorn.
 */

#include "beta.h"
#include "crun.h"

ref(StackObject)
AllocateStackObject(unsigned size)
{
  register ref(StackObject) theStack;

  theStack = cast(StackObject) IOAalloc(size*4 + headsize(StackObject));

  theStack->Proto = cast(ProtoType) -2;
  theStack->GCAttr = 1;
  theStack->ObjectSize = size;
  theStack->StackSize = 0;

  return theStack;
}


