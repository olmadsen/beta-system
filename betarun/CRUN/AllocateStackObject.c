/*
 * BETA C RUNTIME SYSTEM, Copyright (C) 1990,91,92 Mjolner Informatics Aps.
 * Mod: $RCSfile: AllocateStackObject.c,v $, rel: %R%, date: $Date: 1992-07-23 15:03:03 $, SID: $Revision: 1.5 $
 * by Peter Andersen and Tommy Thorn.
 */

#include "beta.h"
#include "crun.h"

ref(StackObject)
AlloSO(unsigned size)
{
  register ref(StackObject) theStack;

  theStack = cast(StackObject) IOAalloc(StackObjectSize(size));

  theStack->Proto = StackObjectPTValue;
  theStack->GCAttr = 1;
  theStack->ObjectSize = size;
  theStack->StackSize = 0;

  return theStack;
}


