/*
 * BETA C RUNTIME SYSTEM, Copyright (C) 1992-94 Mjolner Informatics Aps.
 * by Peter Andersen and Tommy Thorn.
 */

#include "beta.h"
#include "crun.h"

#ifdef PERSIST
#include "../P/PException.h"
#include "../P/referenceTable.h"
#endif /* PERSIST */

/* The Assignment *theCell = theObj has just been
 * done. We know the theCell is in AOA, now check if
 * *theCell is in IOA.
 */

void ChkRA()
{
#ifdef sparc
   /* Called with theCell in %g1, which is a super temp. */
   register Object **g1 __asm__("%g1");
   Object **theCell = g1;
#endif
#ifdef hppa
   Object **theCell;
   __asm__ volatile ("COPY %%r28,%0" : "=r" (theCell));
#endif
   
   DEBUG_CODE(NumChkRA++);
   
   if (!inIOA(*theCell)) {  
#ifdef PERSIST
      Claim(!inPIT(theCell), "ChkRA: theCell in PIT??");
      if (inPIT((void *)*theCell)) {
         newAOAcell(*theCell, theCell);
      }
#endif /* PERSIST */
      return; 
   }
  
   /* Remember this target cell. */
#ifdef MT
   MT_AOAtoIOAInsert(theCell);
#else /* MT */
   AOAtoIOAInsert(theCell);
#endif /* MT */
}
