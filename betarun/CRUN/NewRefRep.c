/*
 * BETA C RUNTIME SYSTEM, Copyright (C) 1990,91,92 Mjolner Informatics Aps.
 * Mod: $RCSfile: NewRefRep.c,v $, rel: %R%, date: $Date: 1992-07-21 17:18:35 $, SID: $Revision: 1.3 $
 * by Peter Andersen and Tommy Thorn.
 */

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
    CAlloRR(theObj, offset, range);
    if (!inIOA((long *)theObj+offset)) ChkRA((long *)theObj+offset);
}


