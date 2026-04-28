/*
 * BETA C RUNTIME SYSTEM, Copyright (C) Aarhus University
 * by Peter Andersen and Tommy Thorn.
 */

#include "beta.h"
#include "crun.h"

void AlloRR(unsigned offset /* in bytes */, 
	    int range, 
	    Object* theObj, 
	    long *SP)
{
    RefRep *theRep=0;
    unsigned long size;

    DEBUG_CODE(NumAlloRR++);

    Ck(theObj);
    if (range<0) range=0; 

    push(theObj);
    size = RefRepSize(range);
    do {
      if (range>LARGE_REP_SIZE || size>IOAMAXSIZE){
	DEBUG_AOA(fprintf(output, "AlloRR allocates in AOA\n"));
	theRep = (RefRep *)AOAcalloc(size);
	DEBUG_AOA(if (!theRep) fprintf(output, "AOAcalloc failed\n"));
      }
      if (!theRep) {
	theRep = (RefRep *)IOATryAlloc(size, SP);
	if (theRep && IOAMinAge!=0) theRep->GCAttr = IOAMinAge;
      }
    } while (!theRep);
    pop(theObj);

    SETPROTO(theRep, RefRepPTValue);
    /* theRep->GCAttr set above if in IOA */
    theRep->LowBorder = 1;
    theRep->HighBorder = range;

    AssignReference((long *)((char *)theObj + offset), (Item *)theRep);

    Ck(theObj);
    Ck(theRep);

}
