/*
 * BETA C RUNTIME SYSTEM, Copyright (C) 1992-94 Mjolner Informatics Aps.
 * by Peter Andersen and Tommy Thorn.
 */

#define GCable_Module

#include "beta.h"
#include "crun.h"

#ifndef MT

ParamThisOffRange(AlloRR)
{
    DeclReference1(struct RefRep *, theRep);
    GCable_Entry();
    FetchThisOffRange();

    DEBUG_CODE(NumAlloRR++);

    Ck(theObj);
    Protect(theObj, theRep = cast(RefRep) IOAalloc(RefRepSize(range)));

    theRep->Proto = RefRepPTValue;
    theRep->GCAttr = 1;
    theRep->LowBorder = 1;
    theRep->HighBorder = range;

    AssignReference((long *)((char *)theObj + offset), cast(Item) theRep);
    Ck(theObj); Ck(theRep); 
}

#endif /* MT */
