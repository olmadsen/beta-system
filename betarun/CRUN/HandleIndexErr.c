/*
 * BETA C RUNTIME SYSTEM, Copyright (C) 1990,91,92 Mjolner Informatics Aps.
 * Mod: $RCSfile: HandleIndexErr.c,v $, rel:$R$, date: $Date: 1992-09-21 17:04:57 $,
 * SID: $Revision: 1.5 $
 * by Peter Orbaek
 */

#include "beta.h"
#include "crun.h"

ParamThisComp(void, HandleIndexErr)
{
#ifdef hppa
    struct Object *this;
    this = (struct Object *)getThisReg();
#endif

    BetaError(-3, this);
}
