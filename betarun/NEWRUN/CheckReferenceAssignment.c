/*
 * BETA C RUNTIME SYSTEM, Copyright (C) 1992-94 Mjolner Informatics Aps.
 * by Peter Andersen and Tommy Thorn.
 */

#include "beta.h"
#include "crun.h"

#ifdef PERSIST
#include "PException.h"
#include "referenceTable.h"
#endif /* PERSIST */

void ChkRA(Object **theCell)
{
  /* The Assignment *theCell = theObj has just been
   * done. We know the theCell is in AOA, now check if
   * *theCell is in IOA.
   */

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
  AOAtoIOAInsert(theCell);

}
