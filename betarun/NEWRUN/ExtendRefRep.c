/*
 * BETA C RUNTIME SYSTEM, Copyright (C) Aarhus University
 * by Peter Andersen and Tommy Thorn.
 */
#include "beta.h"
#include "crun.h"

void ExtRR(Object *theObj,
	   unsigned offset, /* in longs */
	   long add,
	   long *SP
	   )
{
    RefRep * theRep;
    RefRep * newRep=0;
    long newRange, copyRange, i;
    unsigned long size;
    
    DEBUG_CODE(NumExtRR++);
    
    Ck(theObj);
    theRep = *(RefRep **)((long *) theObj + offset);
    Ck(theRep);
    newRange = theRep->HighBorder + add;
    if (newRange < 0) newRange = 0;

    copyRange = (RefRepBodySize((add < 0) ? newRange : theRep->HighBorder))>>2;

    push(theObj);
    push(theRep);
    size = RefRepSize(newRange);
    do {
      if (newRange>LARGE_REP_SIZE || size>IOAMAXSIZE){
	DEBUG_AOA(fprintf(output, "ExtRR allocates in AOA\n"));
	newRep = (RefRep *)AOAcalloc(size);
	DEBUG_AOA(if (!newRep) fprintf(output, "AOAcalloc failed\n"));
      }
      if (!newRep) {
	newRep = (RefRep *)IOATryAlloc(size, SP);
	if (newRep && IOAMinAge!=0) newRep->GCAttr = IOAMinAge;
      }
    } while (!newRep);
    pop(theRep);
    pop(theObj);

    SETPROTO(newRep, RefRepPTValue);
    /* newRep->GCAttr set above if in IOA */
    newRep->LowBorder = 1;
    newRep->HighBorder = newRange;
    
    for (i = 0; i < copyRange; ++i){
      AssignReference(&newRep->Body[i], (long*)(theRep->Body[i]));
    }
    
    AssignReference((long *)theObj + offset, (Item *)newRep);

    Ck(theObj); Ck(theRep); Ck(newRep);
}

