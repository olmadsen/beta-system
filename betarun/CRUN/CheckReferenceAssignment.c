/*
 * BETA C RUNTIME SYSTEM, Copyright (C) 1990,91,92 Mjolner Informatics Aps.
 * Mod: $Id: CheckReferenceAssignment.c,v 1.9 1992-10-02 16:55:47 poe Exp $
 * by Peter Andersen and Tommy Thorn.
 */

#include "beta.h"
#include "crun.h"

/* This is called with target in %g1, which is a super temp. */
void ChkRA()
{
#ifdef sparc
  register handle(Object) theObjHandle asm("%g1");
#endif
#ifdef hppa
  struct Object **theObjHandle;

  asm volatile ("COPY %%r28,%0" : "=r" (theObjHandle));
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
