/*
 * BETA C RUNTIME SYSTEM, Copyright (C) 1990,91,92 Mjolner Informatics Aps.
 * Mod: $Id: NewRefRep.c,v 1.12 1992-09-03 16:09:01 tthorn Exp $
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
    Protect(theObj,CAlloRR(theObj, offset*4, range)); /* MP MP MP MP!!! */
#endif
    if (! inIOA((struct Object **)theObj+offset) &&
	inIOA(*(struct Object **)theObj+offset))
      AOAtoIOAInsert((struct Object **)theObj+offset);
}


