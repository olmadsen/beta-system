/*
 * BETA C RUNTIME SYSTEM, Copyright (C) 1992-94 Mjolner Informatics Aps.
 * by Peter Andersen and Tommy Thorn.
 */

#include "beta.h"
#include "crun.h"

void NewRR(struct Object *theObj,
	   long offset, /* in longs */
	   long range,
	   long *SP)
{
  DEBUG_CODE(NumNewRR++);
  Ck(theObj);
  AlloRR(offset*4, range, theObj, SP);
}


