/*
 * BETA C RUNTIME SYSTEM, Copyright (C) 1990,91,92 Mjolner Informatics Aps.
 * Mod: $RCSfile: CheckReferenceAssignment.c,v $, rel: %R%, date: $Date: 1992-08-31 10:04:18 $, SID: $Revision: 1.7 $
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
