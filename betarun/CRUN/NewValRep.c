/*
 * BETA C RUNTIME SYSTEM, Copyright (C) 1990,91,92 Mjolner Informatics Aps.
 * Mod: $RCSfile: NewValRep.c,v $, rel: %R%, date: $Date: 1992-06-06 03:57:36 $, SID: $Revision: 1.2 $
 * by Peter Andersen and Tommy Thorn.
 */

#include "beta.h"
#include "crun.h"

asmlabel(NewValRep, "
	ba	_CNewValRep
	mov	%l7, %o0
");

void CNewValRep(int range,
		int dummy,
		ref(Object) theObj,
		int offset /* in ints */
		)
{
    CAllocateValRep(theObj, offset/4, range);
}

