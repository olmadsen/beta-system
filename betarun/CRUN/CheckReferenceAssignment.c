/*
 * BETA C RUNTIME SYSTEM, Copyright (C) 1990,91,92 Mjolner Informatics Aps.
 * Mod: $Id: CheckReferenceAssignment.c,v 1.8 1992-09-03 12:55:45 beta Exp $
 * by Peter Andersen and Tommy Thorn.
 */

#include "beta.h"
#include "crun.h"

void
#ifdef sparc
/* This is called with target in %g1, which is a super temp. */
     ChkRA()
#else
/* On the snake we get the target in the ordinary argument register %r26 */
     ChkRA(handle(Object) theObjHandle)
#endif
{
#ifdef sparc
  register handle(Object) theObjHandle asm("%g1");
#endif

  /* The Assignment *theObjHandle = theObj has just been
   * done. We know the theObjHandle is in AOA, now check if
   * *theObjHandle is in IOA.
   */
   
  if (!inIOA(*theObjHandle))
    return; /* It wasn't. */

  /* Remember this target cell. */
  AOAtoIOAInsert(theObjHandle);
}
