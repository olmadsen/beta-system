/*
 * BETA C RUNTIME SYSTEM, Copyright (C) 1990,91,92 Mjolner Informatics Aps.
 * Mod: $RCSfile: ExtendRefRep.c,v $, rel: %R%, date: $Date: 1992-07-21 17:19:04 $, SID: $Revision: 1.4 $
 * by Peter Andersen and Tommy Thorn.
 */

#include "beta.h"
#include "crun.h"

asmlabel(ExtRR, "
	ba	_CExtRR
	mov	%l7, %o2
");

void CExtRR(ref(Object) theObj,
		   unsigned offset, /* in longs */
		   long add
		   )
{
    ref(RefRep) theRep = *casthandle(RefRep) ((long *) theObj + offset);
    ref(RefRep) newRep;
    long newRange = theRep->HighBorder + add;
    long copyRange = (add < 0) ? newRange : theRep->HighBorder;
    int i;

    if (newRange < 0)
      newRange = 0;
    
    newRep = cast(RefRep) IOAcalloc(newRange*4 + headsize(RefRep));
    
    newRep->Proto = RefRepPTValue;
    newRep->GCAttr = 1;
    newRep->LowBorder = 1;
    newRep->HighBorder = newRange;
    
    for (i = 0; i < copyRange; ++i)
      newRep->Body[i] = theRep->Body[i];

    AssignReference((long *)theObj + offset, cast(Item) newRep);
}

