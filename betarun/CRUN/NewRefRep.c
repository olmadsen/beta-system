/*
 * BETA C RUNTIME SYSTEM, Copyright (C) 1990,91,92 Mjolner Informatics Aps.
 * Mod: $RCSfile: NewRefRep.c,v $, rel: %R%, date: $Date: 1992-08-31 21:58:28 $, SID: $Revision: 1.8 $
 * by Peter Andersen and Tommy Thorn.
 */

#define GCable_Module

#include "beta.h"
#include "crun.h"

asmlabel(NewRR, "
	b	_CNewRR
	mov	%l7, %o2
");

#ifdef hppa
void NewRR(ref(Object) theObj, int offset, int range)
#else
void CNewRR(ref(Object) theObj, int offset /* in ints */, int range)
#endif
{
    GCable_Entry();

    Ck(theObj);
#ifdef hppa
    range = (int)getR2Reg();

    pushReference(theObj);
    setThisReg(theObj);
    setD0Reg(offset * 4);
    setD1Reg(range);
    AlloRR();
    theObj = popReference();
#else
    CAlloRR(theObj, offset*4, range); /* MP MP MP MP!!! */
#endif
    if (!inIOA((long *)theObj+offset))
      CCheckRefAsgn((struct Object **)theObj+offset);
}


