/*
 * BETA C RUNTIME SYSTEM, Copyright (C) 1990,91,92 Mjolner Informatics Aps.
 * Mod: $RCSfile: PerformGC.c,v $, rel: %R%, date: $Date: 1992-08-27 15:50:32 $, SID: $Revision: 1.5 $
 * by Peter Andersen and Tommy Thorn.
 */

#define GCable_Module

#include "beta.h"
#include "crun.h"

void DoGC()
{
    GCable_Entry();

    StackEnd = StackPointer;
    IOAGc();
}

asmlabel(_FailureExit, "
	mov	%i0, %o1
	call	_BetaError
	mov	-8, %o0
");
    
