/*
 * BETA C RUNTIME SYSTEM, Copyright (C) 1992-94 Mjolner Informatics Aps.
 * by Peter Andersen and Tommy Thorn.
 */
#include "beta.h"
#include "crun.h"

void ExtRR(struct Object *theObj,
	   unsigned offset, /* in longs */
	   long add,
	   long *SP
	   )
{
    struct RefRep * theRep;
    struct RefRep * newRep=0;
    long newRange, copyRange, i;
    unsigned long size;
    
    DEBUG_CODE(NumExtRR++);
    
    Ck(theObj);
    theRep = *(struct RefRep **)((long *) theObj + offset);
    Ck(theRep);
    newRange = theRep->HighBorder + add;
    copyRange = (add < 0) ? newRange : theRep->HighBorder;
    
    if (newRange < 0) newRange = 0;

    push(theObj);
    push(theRep);
    size = RefRepSize(newRange);
    if (size>IOAMAXSIZE){
      DEBUG_AOA(fprintf(output, "ExtRR allocates in AOA\n"));
      newRep = (struct RefRep *)AOAcalloc(size, SP);
      DEBUG_AOA(if (!newRep) fprintf(output, "AOAcalloc failed\n"));
    }
    if (!newRep) {
      newRep = (struct RefRep *)IOAcalloc(size, SP);
      newRep->GCAttr = 1; 
    }
    pop(theRep);
    pop(theObj);

    Ck(theObj); Ck(theRep);

    newRep->Proto = RefRepPTValue;
    /* newRep->GCAttr set above if in IOA */
    newRep->LowBorder = 1;
    newRep->HighBorder = newRange;
    
    for (i = 0; i < copyRange; ++i){
      AssignReference(&newRep->Body[i], theRep->Body[i]);
    }
    
    AssignReference((long *)theObj + offset, (struct Item *)newRep);
}

