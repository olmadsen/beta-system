/*
 * BETA C RUNTIME SYSTEM, Copyright (C) 1992-94 Mjolner Informatics Aps.
 * by Peter Andersen and Tommy Thorn.
 */

#include "beta.h"
#include "crun.h"
void ChkRA(Object **theObjHandle)
{
  /* The Assignment *theObjHandle = theObj has just been
   * done. We know the theObjHandle is in AOA, now check if
   * *theObjHandle is in IOA.
   */

  DEBUG_CODE(NumChkRA++);

  if (!inIOA(*theObjHandle)) {
    return; 
  }

  /* Remember this target cell. */
  AOAtoIOAInsert(theObjHandle);

}
