/*
 * BETA C RUNTIME SYSTEM, Copyright (C) 1990,91,92 Mjolner Informatics Aps.
 * Mod: $Id: AllocateRefRep.c,v 1.11 1992-09-03 12:55:27 beta Exp $
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

#ifdef hppa
#  define CAlloRR AlloRR
#endif

ref(RefRep) CAlloRR(ref(Object) theObj,
		    unsigned offset, /* i bytes */
		    unsigned range
		    )
{
    DeclReference1(struct RefRep *, theRep);
    GCable_Entry();
#ifdef hppa
    range  = (unsigned) getD1Reg();
    theObj = cast(Object) getThisReg();
    offset = (unsigned) getD0Reg();
#endif

    Ck(theObj);
    Protect(theObj, theRep = cast(RefRep) IOAcalloc(RefRepSize(range)));
    Ck(theObj);

    theRep->Proto = RefRepPTValue;
    theRep->GCAttr = 1;
    theRep->LowBorder = 1;
    theRep->HighBorder = range;

    AssignReference((long *)((char *)theObj + offset), cast(Item) theRep);
    RETURN(theRep);
}
