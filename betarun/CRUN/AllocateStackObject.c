/*
 * BETA C RUNTIME SYSTEM, Copyright (C) 1990,91,92 Mjolner Informatics Aps.
 * Mod: $RCSfile: AllocateStackObject.c,v $, rel: %R%, date: $Date: 1992-08-19 15:44:12 $, SID: $Revision: 1.6 $
 * by Peter Andersen and Tommy Thorn.
 */

#define GCable_Module

#include "beta.h"
#include "crun.h"

ref(StackObject)
AlloSO(unsigned size)
{
  GCable_Entry

#define theStack (cast(StackObject) GCreg3)

  theStack = cast(StackObject) IOAalloc(StackObjectSize(size));

  theStack->Proto = StackObjectPTValue;
  theStack->GCAttr = 1;
  theStack->ObjectSize = size;
  theStack->StackSize = 0;

  return theStack;
}


