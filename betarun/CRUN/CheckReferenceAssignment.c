/*
 * BETA C RUNTIME SYSTEM, Copyright (C) 1992-94 Mjolner Informatics Aps.
 * by Peter Andersen and Tommy Thorn.
 */

#include "beta.h"
#include "crun.h"

/* The Assignment *theCell = theObj has just been
 * done. We know the theCell is in AOA, now check if
 * *theCell is in IOA.
 */

void ChkRA()
{
#ifdef sparc
  /* Called with theCell in %g1, which is a super temp. */
  register struct Object **theCell __asm__("%g1");
#endif
#ifdef hppa
  struct Object **theCell;
  __asm__ volatile ("COPY %%r28,%0" : "=r" (theCell));
#endif

  DEBUG_CODE(NumChkRA++);
   
  if (!inIOA(*theCell)) {
#ifdef RTLAZY
    /* It may be a dangling (negative) reference */
    if (isLazyRef(*theCell))
      negAOArefsINSERT((long)theCell);
#endif
    return; 
  }

  /* Remember this target cell. */
#ifdef MT
  MT_AOAtoIOAInsert(theCell);
#else /* MT */
  AOAtoIOAInsert(theCell);
#endif /* MT */
}
