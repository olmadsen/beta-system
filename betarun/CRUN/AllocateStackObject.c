/*
 * BETA C RUNTIME SYSTEM, Copyright (C) 1990,91,92 Mjolner Informatics Aps.
 * Mod: $RCSfile: AllocateStackObject.c,v $, rel: %R%, date: $Date: 1992-06-09 15:19:00 $, SID: $Revision: 1.3 $
 * by Peter Andersen and Tommy Thorn.
 */

#include "beta.h"
#include "crun.h"

ref(StackObject)
AllocateStackObject(unsigned size)
{
  register ref(StackObject) theStack;

  theStack = cast(StackObject) IOAalloc(size*4 + headsize(StackObject));

  theStack->Proto = StackObjectPTValue;
  theStack->GCAttr = 1;
  theStack->ObjectSize = size;
  theStack->StackSize = 0;

  return theStack;
}


