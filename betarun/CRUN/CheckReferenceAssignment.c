/*
 * BETA C RUNTIME SYSTEM, Copyright (C) 1990,91,92 Mjolner Informatics Aps.
 * Mod: $RCSfile: CheckReferenceAssignment.c,v $, rel: %R%, date: $Date: 1992-08-19 15:44:31 $, SID: $Revision: 1.6 $
 * by Peter Andersen and Tommy Thorn.
 */

#include "beta.h"
#include "crun.h"

/* This is called from outside with target in %g1, which is a super temp. */

void ChkRA()
{
  register handle(Object) theObjHandle asm("%g1");

  /* The Assignment *theObjHandle = theObj has just been
   * done. We know the theObjHandle is in AOA, now check if
   * *theObjHandle is in IOA.
   */
   
  if (!inIOA(*theObjHandle))
    return; /* It wasn't. */

  /* Remember this target cell. */
  AOAtoIOAInsert(theObjHandle);
}
