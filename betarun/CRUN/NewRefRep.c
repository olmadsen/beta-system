/*
 * BETA C RUNTIME SYSTEM, Copyright (C) 1990,91,92 Mjolner Informatics Aps.
 * Mod: $RCSfile: NewRefRep.c,v $, rel: %R%, date: $Date: 1992-08-19 15:45:09 $, SID: $Revision: 1.4 $
 * by Peter Andersen and Tommy Thorn.
 */

#define GCable_Module

#include "beta.h"
#include "crun.h"

/* MP */

asmlabel(NewRR, "
	ba	_CNewRR
	mov	%l7, %o0
");

void CNewRR(int range,
		int dummy,
		ref(Object) theObj,
		int offset /* in ints */
		)
{
    GCable_Entry

    Ck(theObj);
    CAlloRR(theObj, offset*4, range); /* MP MP MP MP!!! */
    if (!inIOA((long *)theObj+offset)) CCheckRefAsgn((long *)theObj+offset);
}


