/*
 * BETA C RUNTIME SYSTEM, Copyright (C) 1992-94 Mjolner Informatics Aps.
 * by Peter Orbaek, Tommy Thorn, Peter Andersen, and Jacob Seligmann
 */

#include "beta.h"
#include "crun.h"

ParamThisComp(void, HandleIndexErr)
{
  FetchThisComp();
  Ck(this);
  BetaError(RepRangeErr, cast(Object)this);
}
