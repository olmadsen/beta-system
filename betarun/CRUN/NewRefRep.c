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
    FetchObjOffRange();

    DEBUG_CODE(NumNewRR++);
    Ck(theObj);

#ifdef sparc
    Protect(theObj,if (range<0) range=0; CAlloRR(theObj, 0, offset*4, 0, 0, range));
#endif
#ifdef hppa
    Protect(theObj,if (range<0) range=0; CAlloRR(offset*4, range, theObj));
#endif
#ifdef crts
    Protect(theObj,if (range<0) range=0; AlloRR(theObj, offset*4, range));
#endif
}


