/*
 * BETA C RUNTIME SYSTEM, Copyright (C) 1992-94 Mjolner Informatics Aps.
 * by Peter Orbaek, Tommy Thorn, Peter Andersen, and Jacob Seligmann
 */

#include "beta.h"
#include "crun.h"

void HandleIndexErr(long *SP, struct Object *this)
{
    Ck(this);
    BetaError(RepRangeErr, this, SP);
}
