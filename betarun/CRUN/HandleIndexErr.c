/*
 * BETA C RUNTIME SYSTEM, Copyright (C) Aarhus University
 * by Peter Orbaek, Tommy Thorn, Peter Andersen, and Jacob Seligmann
 */

#include "beta.h"
#include "crun.h"

ParamThisComp(void, HandleIndexErr)
{
  FetchThisComp();
  Ck(this);
  BetaError(RepRangeErr, (Object *)this);
}
