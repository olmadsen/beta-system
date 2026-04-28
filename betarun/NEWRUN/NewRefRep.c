/*
 * BETA C RUNTIME SYSTEM, Copyright (C) Aarhus University
 * by Peter Andersen and Tommy Thorn.
 */

#include "beta.h"
#include "crun.h"

void NewRR(Object *theObj,
	   long offset, /* in longs */
	   long range,
	   long *SP)
{
  DEBUG_CODE(NumNewRR++);
  Ck(theObj);
  AlloRR(offset*4, range, theObj, SP);
}


