/* File: NewValRep.c
 * $Id: NewValRep.c,v 1.1 1992-06-06 03:36:47 beta Exp $
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

