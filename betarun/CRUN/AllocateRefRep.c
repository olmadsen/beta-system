/*
 * BETA C RUNTIME SYSTEM, Copyright (C) 1992-94 Mjolner Informatics Aps.
 * by Peter Andersen and Tommy Thorn.
 */

#define GCable_Module

#include "beta.h"
#include "crun.h"

ParamObjOffRange(ref(RefRep), AlloRR)
{
    DeclReference1(struct RefRep *, theRep);
    GCable_Entry();
#ifdef hppa
    range  = (unsigned) getD1Reg();
    theObj = cast(Object) getThisReg();
    offset = (unsigned) getD0Reg();
#endif

    Ck(theObj);
    Protect(theObj, theRep = cast(RefRep) IOAcalloc(RefRepSize(range)));
    Ck(theObj);

    theRep->Proto = RefRepPTValue;
    theRep->GCAttr = 1;
    theRep->LowBorder = 1;
    theRep->HighBorder = range;

    AssignReference((long *)((char *)theObj + offset), cast(Item) theRep);
    RETURN(theRep);
}
