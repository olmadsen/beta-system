/* File: PerformGC.c
 * $Id: PerformGC.c,v 1.1 1992-06-06 03:36:47 beta Exp $
 */

#include "beta.h"
#include "crun.h"

void PerformGC()
{
    StackEnd = StackPointer;
    IOAGc();
}

asmlabel(_FailureExit, "
	mov	%i0, %o1
	call	_BetaError
	mov	-8, %o0
");
    
