/*
 * BETA C RUNTIME SYSTEM, Copyright (C) 1992-94 Mjolner Informatics Aps.
 * by Peter Andersen and Tommy Thorn.
 */

#include "beta.h"
#include "crun.h"

void AlloRR(struct Object* theObj, unsigned offset, int range, long *SP)
{
    struct RefRep *theRep;

    DEBUG_CODE(NumAlloRR++);

    Ck(theObj);
    if (range<0) range=0; 
    Protect(theObj, theRep = (struct RefRep *)IOAcalloc(RefRepSize(range), SP));
    Ck(theObj);

    theRep->Proto = RefRepPTValue;
    theRep->GCAttr = 1;
    theRep->LowBorder = 1;
    theRep->HighBorder = range;

    AssignReference((long *)((char *)theObj + offset), (struct Item *)theRep);
}
