/*
 * BETA C RUNTIME SYSTEM, Copyright (C) 1990,91,92 Mjolner Informatics Aps.
 * Mod: $RCSfile: HandleIndexErr.c,v $, rel:$R$, date: $Date: 1992-09-04 14:34:58 $,
 * SID: $Revision: 1.2 $
 * by Peter Orbaek
 */

#include "beta.h"
#include "crun.h"

ParamThisComp(HandleIndexErr)
{
#ifdef hppa
    struct Object *this;
    this = (struct Object *)getThisReg();
#endif

    DisplayBetaStack(-3, this);
    BetaExit(-1);
}
