/*
 * BETA C RUNTIME SYSTEM, Copyright (C) 1990,91,92 Mjolner Informatics Aps.
 * Mod: $RCSfile: HandleIndexErr.c,v $, rel:$R$, date: $Date: 1992-09-10 12:33:48 $,
 * SID: $Revision: 1.4 $
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
