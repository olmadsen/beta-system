/*
 * BETA C RUNTIME SYSTEM, Copyright (C) 1992-93 Mjolner Informatics Aps.
 * by Peter Andersen and Tommy Thorn.
 */

#define GCable_Module

#include "beta.h"
#include "crun.h"

asmlabel(NewRR, "
	mov	%o1, %o2
	mov	%l7, %o5
        clr     %o1
        clr     %o3
	ba	"CPREF"NewRR
        clr     %o4
");

#ifdef hppa
void NewRR(ref(Object) theObj,
	   long offset, 
	   long range)
#else
void CNewRR(ref(Object) theObj, 
	    int i1,
	    long offset /* in ints */,
	    int i3,
	    int i4,
	    long range)
#endif
{
    GCable_Entry();

    Ck(theObj);
#ifdef hppa
    range = (long)getR2Reg();

    if (range<0) range=0;
    pushReference(theObj);
    pushReference(getThisReg());
    setThisReg(theObj);
    setD0Reg(offset * 4);
    setD1Reg(range);
    AlloRR();
    setThisReg(popReference());
    theObj = popReference();
#else
    Protect(theObj,if (range<0) range=0; CAlloRR(theObj, 0, offset*4, 0, 0, range));
#endif
    if (! inIOA((struct Object **)theObj+offset) &&
	inIOA(*(struct Object **)theObj+offset))
      AOAtoIOAInsert((struct Object **)theObj+offset);
}


