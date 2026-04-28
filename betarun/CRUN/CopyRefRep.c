/*
 * BETA C RUNTIME SYSTEM, Copyright (C) Aarhus University
 * by Peter Andersen and Tommy Thorn.
 */

#include "beta.h"
#include "crun.h"

ParamRepObjOff(CopyRR)
{
    DeclReference1(RefRep *, newRep);
    register unsigned range, i;
    unsigned long size;
    
    FetchRepObjOff();
    
    DEBUG_CODE(NumCopyRR++);

    Ck(theRep); Ck(theObj);
    newRep = NULL;
    
    range = theRep->HighBorder;

    push(theObj);
    push(theRep);
    size = RefRepSize(range);
    do {
      if (range>LARGE_REP_SIZE || size>IOAMAXSIZE){
	DEBUG_AOA(fprintf(output, "CopyRR allocates in AOA\n"));
	newRep = (RefRep *)AOAalloc(size);
	DEBUG_AOA(if (!newRep) fprintf(output, "AOAalloc failed\n"));
      }
      if (!newRep) {
	newRep = (RefRep *)IOATryAlloc(size);
	if (newRep && IOAMinAge!=0) newRep->GCAttr = IOAMinAge; /* In IOA */
      }
    } while (!newRep);

    pop(theRep);
    pop(theObj);

    SETPROTO(newRep,GETPROTO(theRep));
    /* newRep->GCAttr set above */
    newRep->LowBorder = 1;
    newRep->HighBorder = range;
    
    /* Copy theRep to newRep */
    for (i = 0; i < range; ++i){
      AssignReference(&newRep->Body[i], (Item*)theRep->Body[i]);
    }
    
    AssignReference((long *)theObj + offset, (Item *) newRep);

    Ck(newRep); Ck(theRep); Ck(theObj);
}

