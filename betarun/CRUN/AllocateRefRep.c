/*
 * BETA C RUNTIME SYSTEM, Copyright (C) Aarhus University
 * by Peter Andersen and Tommy Thorn.
 */

#include "beta.h"
#include "crun.h"

#ifndef MT

ParamThisOffRange(AlloRR)
{
    unsigned long size;

    DeclReference1(RefRep *, theRep);
    FetchThisOffRange();

    DEBUG_CODE(NumAlloRR++);

    theRep = NULL;
    do {
      Ck(theObj);
      
      push(theObj);
      size = RefRepSize(range);
      if (range>LARGE_REP_SIZE || size>IOAMAXSIZE){
	DEBUG_AOA(fprintf(output, "AlloRR allocates in AOA\n"));
	theRep = (RefRep *)AOAcalloc(size);
	DEBUG_AOA(if (!theRep) fprintf(output, "AOAcalloc failed\n"));
      }
      if (!theRep) {
	theRep = (RefRep *)IOATryAlloc(size);
	if (theRep) {
	  if (IOAMinAge!=0) theRep->GCAttr = IOAMinAge;
	}
      }
      pop(theObj);

      if (theRep) {
	SETPROTO(theRep,RefRepPTValue);
	/* theRep->GCAttr set above if in IOA */
	theRep->LowBorder = 1;
	theRep->HighBorder = range;
	
	AssignReference((long *)((char *)theObj + offset), (Item *) theRep);
	Ck(theObj); Ck(theRep); 
      }
    } while (!theRep);
}

#endif /* MT */
