/*
 * BETA C RUNTIME SYSTEM, Copyright (C) 1990,91,92 Mjolner Informatics Aps.
 * Mod: $RCSfile: AllocateRefRep.c,v $, rel: %R%, date: $Date: 1992-08-27 15:22:16 $, SID: $Revision: 1.8 $
 * by Peter Andersen and Tommy Thorn.
 */

#define GCable_Module

#include "beta.h"
#include "crun.h"

/* MP */

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
    DeclReference1(struct RefRep *theRep);
    GCable_Entry();

    Ck(theObj);
    theRep = cast(RefRep) IOAcalloc(RefRepSize(range));
    
    ForceVolatileRef(theObj);
    Ck(theObj);

    theRep->Proto = RefRepPTValue;
    theRep->GCAttr = 1;
    theRep->LowBorder = 1;
    theRep->HighBorder = range;

    AssignReference((long *)((char *)theObj + offset), cast(Item) theRep);
    return theRep;
}
