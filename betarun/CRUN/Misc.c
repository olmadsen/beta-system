/*
 * BETA C RUNTIME SYSTEM, Copyright (C) 1990,91,92 Mjolner Informatics Aps.
 * Mod: $RCSfile: Misc.c,v $, rel: %R%, date: $Date: 1992-06-08 23:54:46 $, SID: $Revision: 1.3 $
 * by Peter Andersen and Tommy Thorn.
 */

#include "beta.h"
#include "crun.h"

asmlabel(Return, "retl; nop");

void ReferenceIsNone(ref(Object) theObj)
{
    BetaError(-1, theObj);
}

