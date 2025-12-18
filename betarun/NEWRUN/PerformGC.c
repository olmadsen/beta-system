/*
 * BETA C RUNTIME SYSTEM, Copyright (C) Aarhus University
 * by Peter Andersen, Tommy Thorn, and Jacob Seligmann.
 */

#include "beta.h"
#include "crun.h"


void doGC(long *SP, Object *this, unsigned long NumLongs) /* The one called from IOAalloc */
{
  ReqObjectSize = NumLongs;
  CurrentObject = this;
  StackEnd = SP;
  IOAGc();
}

/* DoGC is now generated in betaenv */
