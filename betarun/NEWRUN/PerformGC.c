/*
 * BETA C RUNTIME SYSTEM, Copyright (C) 1992-94 Mjolner Informatics Aps.
 * by Peter Andersen, Tommy Thorn, and Jacob Seligmann.
 */

#include "beta.h"
#include "crun.h"

void DoGC(long *SP) /* The one called directly from betaenv */
{
  doGC(SP, GetThis(SP), 0);
}

void doGC(long *SP, struct Object *this, unsigned long NumLongs) /* The one called from IOA(c)alloc */
{
  ReqObjectSize = NumLongs;
  CurrentObject = this;
  StackEnd = SP;
  IOAGc();
}
