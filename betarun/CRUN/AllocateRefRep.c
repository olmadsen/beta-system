/* File: AllocateRefRep.c
 * $Id: AllocateRefRep.c,v 1.1 1992-06-06 03:36:32 beta Exp $
 */

#include "beta.h"
#include "crun.h"

/* MP */

/* ?? Parameters */

asmlabel(AllocateRefRep, "
	mov %i0, %o0
        mov %l0, %o1
        ba _CAllocateRefRep
        mov %l1, %o2
");

ref(RefRep) CAllocateRefRep(ref(Object) theObj,
			   unsigned offset, /* i bytes */
			   unsigned range
			   )
{
    register ref(RefRep) theRep;

    theRep = cast(RefRep) IOAcalloc(range*4 + headsize(RefRep));

    theRep->Proto = cast(ProtoType) -4;
    theRep->GCAttr = 1;
    theRep->LowBorder = 1;
    theRep->HighBorder = range;

    *casthandle(RefRep)((char *)theObj + offset) = theRep;
    return theRep;
}


