/*
 * BETA C RUNTIME SYSTEM, Copyright (C) 1992-93 Mjolner Informatics Aps.
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
   
  if (!inIOA(*theObjHandle)) {
#ifdef RTLAZY
    /* It may be a dangling (negative) reference */
    if (isLazyRef(*theObjHandle))
      negAOArefsINSERT(theObjHandle);
#endif
    return; 
  }

  /* Remember this target cell. */
  AOAtoIOAInsert(theObjHandle);
}
