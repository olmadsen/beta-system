/*
 * BETA C RUNTIME SYSTEM, Copyright (C) 1992-93 Mjolner Informatics Aps.
 * by Peter Andersen and Tommy Thorn.
 */

#define GCable_Module

#ifdef hppa
register long _dummyx asm("r16");
#endif

#include "beta.h"
#include "crun.h"

asmlabel(ExtRR, "
	ba	_CExtRR
	mov	%l7, %o2
");

#ifdef hppa
#  define CExtRR ExtRR
#endif

void CExtRR(ref(Object) theObj,
	    unsigned offset, /* in longs */
	    long add
	    )
{
    DeclReference1(struct RefRep *, theRep);
    DeclReference2(struct RefRep *, newRep);
    
    long newRange, copyRange, i;
    
    GCable_Entry();

#ifdef hppa
    add = (long) getR2Reg(); /* sic! */
#endif

    Ck(theObj);
    theRep = *casthandle(RefRep) ((long *) theObj + offset);
    newRange = theRep->HighBorder + add;
    copyRange = (add < 0) ? newRange : theRep->HighBorder;
    
    if (newRange < 0)
      newRange = 0;

    Protect2(theRep, theObj,
	     newRep = cast(RefRep) IOAcalloc(RefRepSize(newRange)));
   
    Ck(theObj);

    newRep->Proto = RefRepPTValue;
    newRep->GCAttr = 1;
    newRep->LowBorder = 1;
    newRep->HighBorder = newRange;
    
    for (i = 0; i < copyRange; ++i)
      newRep->Body[i] = theRep->Body[i];
    
    AssignReference((long *)theObj + offset, cast(Item) newRep);
}

