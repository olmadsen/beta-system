/* File: NewRefRep.c
 * $Id: NewRefRep.c,v 1.1 1992-06-06 03:36:46 beta Exp $
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


