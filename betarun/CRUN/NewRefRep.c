/*
 * BETA C RUNTIME SYSTEM, Copyright (C) Aarhus University
 * by Peter Andersen and Tommy Thorn.
 */

#include "beta.h"
#include "crun.h"

#ifndef MT

ParamObjOffRange(NewRR)
{
    FetchObjOffRange();

    DEBUG_CODE(NumNewRR++);
    Ck(theObj);

#ifdef sparc
    Protect(theObj,if (range<0) range=0; CAlloRR(theObj, 0, offset*4, 0, 0, range));
#endif
#ifdef hppa
    Protect(theObj,if (range<0) range=0; CAlloRR(offset*4, range, theObj));
#endif
}

#endif /* MT */

