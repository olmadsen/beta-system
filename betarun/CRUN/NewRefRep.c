/*
 * BETA C RUNTIME SYSTEM, Copyright (C) 1990,91,92 Mjolner Informatics Aps.
 * Mod: $RCSfile: NewRefRep.c,v $, rel: %R%, date: $Date: 1992-06-06 03:57:35 $, SID: $Revision: 1.2 $
 * by Peter Andersen and Tommy Thorn.
 */

#include "beta.h"
#include "crun.h"

/* MP */

asmlabel(NewRefRep, "
	ba	_CNewRefRep
	mov	%l7, %o0
");

void CNewRefRep(int range,
		int dummy,
		ref(Object) theObj,
		int offset /* in ints */
		)
{
    CAllocateRefRep(theObj, offset/4, range);
}


