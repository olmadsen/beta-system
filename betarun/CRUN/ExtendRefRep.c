/*
 * BETA C RUNTIME SYSTEM, Copyright (C) 1990,91,92 Mjolner Informatics Aps.
 * Mod: $RCSfile: ExtendRefRep.c,v $, rel: %R%, date: $Date: 1992-06-09 15:19:23 $, SID: $Revision: 1.3 $
 * by Peter Andersen and Tommy Thorn.
 */

#include "beta.h"
#include "crun.h"

asmlabel(ExtendRefRep, "
	ba	_CExtendRefRep
	mov	%l7, %o2
");

void CExtendRefRep(ref(Object) theObj,
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
    
    *casthandle(RefRep)((long *)theObj + offset) = newRep;
    for (i = 0; i < copyRange; ++i)
      newRep->Body[i] = theRep->Body[i];
}

