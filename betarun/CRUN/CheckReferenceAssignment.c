/*
 * BETA C RUNTIME SYSTEM, Copyright (C) 1990,91,92 Mjolner Informatics Aps.
 * Mod: $RCSfile: CheckReferenceAssignment.c,v $, rel: %R%, date: $Date: 1992-07-21 17:15:08 $, SID: $Revision: 1.3 $
 * by Peter Andersen and Tommy Thorn.
 */

#include "beta.h"
#include "crun.h"

extern void CheckReferenceAssignment() asm("CheckReferenceAssignment"); /* Alias */
void CheckReferenceAssignment(handle(Object) theObjHandle)
{
  ChkRA(theObjHandle);
}

void ChkRA(handle(Object) theObjHandle)
{
  /* The assignment *theObjHandle = theObj has just been
   * done. We know the theObjHandle is in AOA, now check if
   * *theObjHandle is in IOA.
   */
   
  if (!inIOA(*theObjHandle))
    return; /* It wasn't. */

  /* Remember this target cell. */
  AOAtoIOAInsert(theObjHandle);
}
