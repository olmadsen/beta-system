/*
 * BETA C RUNTIME SYSTEM, Copyright (C) 1992-93 Mjolner Informatics Aps.
 * by Peter Orbaek, Tommy Thorn and Peter Andersen
 */

#include "beta.h"
#include "crun.h"

ParamThisComp(void, HandleIndexErr)
{
#ifdef hppa
    /* struct Item *this; */
    this = (struct Item *)getThisReg();
#endif

    BetaError(RepRangeErr, this);
}
