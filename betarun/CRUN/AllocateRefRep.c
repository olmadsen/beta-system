/*
 * BETA C RUNTIME SYSTEM, Copyright (C) 1990,91,92 Mjolner Informatics Aps.
 * Mod: $RCSfile: AllocateRefRep.c,v $, rel: %R%, date: $Date: 1992-07-23 15:03:21 $, SID: $Revision: 1.5 $
 * by Peter Andersen and Tommy Thorn.
 */

#include "beta.h"
#include "crun.h"

/* MP */

/* ?? Parameters */

asmlabel(AlloRR, "
	mov %i0, %o0
        mov %l0, %o1
        ba _CAlloRR
        mov %l1, %o2
");

ref(RefRep) CAlloRR(ref(Object) theObj,
			   unsigned offset, /* i bytes */
			   unsigned range
			   )
{
    register ref(RefRep) theRep;

    theRep = cast(RefRep) IOAcalloc(RefRepSize(range));

    theRep->Proto = RefRepPTValue;
    theRep->GCAttr = 1;
    theRep->LowBorder = 1;
    theRep->HighBorder = range;

    *casthandle(RefRep)((char *)theObj + offset) = theRep;
    return theRep;
}


