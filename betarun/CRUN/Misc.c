/*
 * BETA C RUNTIME SYSTEM, Copyright (C) 1990,91,92 Mjolner Informatics Aps.
 * Mod: $RCSfile: Misc.c,v $, rel: %R%, date: $Date: 1992-08-27 15:49:00 $, SID: $Revision: 1.7 $
 * by Peter Andersen and Tommy Thorn.
 */

#define GCable_Module

#include "beta.h"
#include "crun.h"

asmlabel(Return, "retl; nop");

void
RefNone(ref(Object) theObj)
{
    BetaError(-1, theObj);
}

/* Need to do this in assembler, as the arguments to
   my caller normally isn't accesseable */
asmlabel(SetArgValues, "
	set _ArgCount, %g1
	st %i0, [%g1]
	set _ArgVector, %g1
	retl
	st %i1, [%g1]
");

char *
IOAalloc(unsigned size)
{
  register char *p;

  GCable_Entry();

  while ((char *)IOATop+size > (char *)IOALimit) {
      ReqObjectSize = size / 4;
      DoGC();
  }

  p = (char *)IOATop;
  IOATopoff += size;

  return p;
}

char *IOAcalloc(unsigned size)
{
  register char *p;

  GCable_Entry();

  while ((char *) IOATop+size > (char *)IOALimit) {
      ReqObjectSize = size / 4;
      DoGC();
  }

  p = (char *)IOATop;
  IOATopoff += size;

  int_clear(p, size);
  return p;
}

