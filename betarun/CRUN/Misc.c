/*
 * BETA C RUNTIME SYSTEM, Copyright (C) 1990,91,92 Mjolner Informatics Aps.
 * Mod: $Id: Misc.c,v 1.10 1992-09-03 12:56:14 beta Exp $
 * by Peter Andersen and Tommy Thorn.
 */

#define GCable_Module

#include "beta.h"
#include "crun.h"

#ifdef hppa
void Return() {}
#endif
#ifdef sparc
asmlabel(Return, "retl; nop");
#endif

void
RefNone(ref(Object) theObj)
{
    BetaError(-1, theObj);
}

#ifdef hppa
SetArgValues(int argc, char *argv[])
{
  ArgCount = argc;
  ArgVector = argv;
}
#endif
#ifdef sparc
/* Need to do this in assembler, as the arguments to
   my caller normally isn't accesseable */
asmlabel(SetArgValues, "
	set _ArgCount, %g1
	st %i0, [%g1]
	set _ArgVector, %g1
	retl
	st %i1, [%g1]
");
#endif

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
#ifdef hppa
  setIOATopoffReg(getIOATopoffReg() + size);
#else
  IOATopoff += size;
#endif

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
#ifdef hppa
  setIOATopoffReg(getIOATopoffReg() + size);
#else
  IOATopoff += size;
#endif

  int_clear(p, size);
  return p;
}

