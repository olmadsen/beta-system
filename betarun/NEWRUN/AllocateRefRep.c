/*
 * BETA C RUNTIME SYSTEM, Copyright (C) 1992-94 Mjolner Informatics Aps.
 * by Peter Andersen and Tommy Thorn.
 */

#include "beta.h"
#include "crun.h"

void AlloRR(unsigned offset /* in bytes */, 
	    int range, 
	    struct Object* theObj, 
	    long *SP)
{
    struct RefRep *theRep=0;
    unsigned long size;

    DEBUG_CODE(NumAlloRR++);

    Ck(theObj);
    if (range<0) range=0; 

    push(theObj);
    size = RefRepSize(range);
    if (size>IOAMAXSIZE){
      DEBUG_AOA(fprintf(output, "AlloRR allocates in AOA\n"));
      theRep = (struct RefRep *)AOAcalloc(size, SP);
      DEBUG_AOA(if (!theRep) fprintf(output, "AOAcalloc failed\n"));
    }
    if (!theRep) {
      theRep = (struct RefRep *)IOAalloc(size, SP);
      if (IOAMinAge!=0) theRep->GCAttr = IOAMinAge;
    }
    pop(theObj);

    theRep->Proto = RefRepPTValue;
    /* theRep->GCAttr set above if in IOA */
    theRep->LowBorder = 1;
    theRep->HighBorder = range;

    AssignReference((long *)((char *)theObj + offset), (struct Item *)theRep);

    Ck(theObj);
    Ck(theRep);

}
