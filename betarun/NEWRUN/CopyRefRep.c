/*
 * BETA C RUNTIME SYSTEM, Copyright (C) 1992-94 Mjolner Informatics Aps.
 * by Peter Andersen and Tommy Thorn.
 */

#include "beta.h"
#include "crun.h"

void CopyRR(struct RefRep *theRep,
	    struct Object *theObj,
	    unsigned offset /* in longs */,
	    long *SP
	    )
{
    struct RefRep * newRep=0;
    register unsigned range, i;
    unsigned long size;
    
    DEBUG_CODE(NumCopyRR++);

    Ck(theRep); Ck(theObj);

    newRep = NULL;
    
    range = theRep->HighBorder;

    push(theObj);
    push(theRep);
    size = RefRepSize(range);
    if (size>IOAMAXSIZE){
      DEBUG_AOA(fprintf(output, "CopyRR allocates in AOA\n"));
      newRep = (struct RefRep *)AOAalloc(size, SP);
      DEBUG_AOA(if (!newRep) fprintf(output, "AOAalloc failed\n"));
    }
    if (newRep) {
      newRep->GCAttr = 0; /* In AOA */
    } else {
      newRep = (struct RefRep *)IOAalloc(size, SP);
      newRep->GCAttr = 1; /* In IOA */
    }
    pop(theRep);
    pop(theObj);

    newRep->Proto = theRep->Proto;
    /* newRep->GCAttr set above */
    newRep->LowBorder = 1;
    newRep->HighBorder = range;
    
    /* Copy theRep to newRep */
    for (i = 0; i < range; ++i){
      AssignReference(&newRep->Body[i], theRep->Body[i]);
    }
    
    AssignReference((long *)theObj + offset, (struct Item *)newRep);
    Ck(theRep); Ck(theObj); Ck(newRep);
}

