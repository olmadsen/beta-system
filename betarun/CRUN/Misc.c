/*
 * BETA C RUNTIME SYSTEM, Copyright (C) 1990,91,92 Mjolner Informatics Aps.
 * Mod: $RCSfile: Misc.c,v $, rel: %R%, date: $Date: 1992-06-06 03:57:34 $, SID: $Revision: 1.2 $
 * by Peter Andersen and Tommy Thorn.
 */

#include "beta.h"
#include "crun.h"

asmlabel(Return, "retl; nop");

void CheckReferenceAssignment(handle(Object) theObjHandle)
{
  /* The assignment *theObjHandle = theObj has just been
   * done. We know the theObjHandle is in AOA, now check if
   * *theObjHandle is in IOA.
   */
   
  if ((long *) *theObjHandle < IOA || (long *) *theObjHandle >= IOATop)
    return; /* It wasn't. */

  /* Remember this target cell. */
  AOAtoIOAInsert(theObjHandle);

/*    fprintf(stderr, "CheckReferenceAssignment: Unfinished code, doesn't work\n");
      See also AOAtoIOAInsert in aoatoioa.c, which does most of the work!
      I don't know why it isn't used in CheckReferenceAssignment.run, i'm trying to
      find out ...
      / peter
 */
  return;
}

void ReferenceIsNone(ref(Object) theObj)
{
    BetaError(-1, theObj);
}

