/*
 * BETA C RUNTIME SYSTEM, Copyright (C) 1990,91,92 Mjolner Informatics Aps.
 * Mod: $RCSfile: Misc.c,v $, rel: %R%, date: $Date: 1992-07-21 17:16:32 $, SID: $Revision: 1.5 $
 * by Peter Andersen and Tommy Thorn.
 */

#include "beta.h"
#include "crun.h"

asmlabel(Return, "retl; nop");

void RefNone(ref(Object) theObj)
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
