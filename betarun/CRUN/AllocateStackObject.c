/* File: AllocateStackObject.c
 * $Id: AllocateStackObject.c,v 1.1 1992-06-06 03:36:32 beta Exp $
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


