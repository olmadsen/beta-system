/*
 * BETA C RUNTIME SYSTEM, Copyright (C) 1990,91,92 Mjolner Informatics Aps.
 * Mod: $RCSfile: HandleIndexErr.c,v $, rel:$R$, date: $Date: 1992-09-04 07:47:51 $,
 * SID: $Revision: 1.1 $
 * by Peter Orbaek
 */

#include "beta.h"
#include "crun.h"

HandleIndexErr(struct ValRep *rep)
{
    struct Object *this;

#ifdef hppa
    this = (struct Object *)getThisReg();
#endif

    DisplayBetaStack(-3, this);
    BetaExit(-1);
}
