/*
 * BETA C RUNTIME SYSTEM, Copyright (C) 1992-94 Mjolner Informatics Aps.
 * by Peter Andersen and Tommy Thorn.
 */

#define GCable_Module

#include "beta.h"
#include "crun.h"

ParamObjOffRange(NewRR)
{
    GCable_Entry();

#ifdef hppa
    range = (long)getR2Reg();

    if (range<0) range=0;
    pushReference(theObj);
    pushReference(getThisReg());
    setThisReg(theObj);
    setD0Reg(offset * 4);
    setD1Reg(range);
    AlloRR(theObj, offset, range);
    setThisReg(popReference());
    theObj = popReference();
#endif

    DEBUG_CODE(NumNewRR++);
    Ck(theObj);

#ifdef sparc
    Protect(theObj,if (range<0) range=0; CAlloRR(theObj, 0, offset*4, 0, 0, range));
#endif
#ifdef crts
    Protect(theObj,if (range<0) range=0; AlloRR(theObj, offset*4, range));
#endif
}


