/*
 * BETA C RUNTIME SYSTEM, Copyright (C) 1992-94 Mjolner Informatics Aps.
 * by Peter Andersen, Tommy Thorn, and Jacob Seligmann.
 */

#include "beta.h"
#include "crun.h"

#if 0
/* generated in betaenv */
void DoGC(long *SP) /* The one called directly from betaenv */
{
  /* Notice: SP points to *bottom* of frame */
  doGC(SP, GetThis(SP), 0);
}
#endif

void doGC(long *SP, struct Object *this, unsigned long NumLongs) /* The one called from IOA(c)alloc */
{
  ReqObjectSize = NumLongs;
  CurrentObject = this;
  StackEnd = SP;
  IOAGc();
}
