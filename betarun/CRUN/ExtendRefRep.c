/*
 * BETA C RUNTIME SYSTEM, Copyright (C) 1990,91,92 Mjolner Informatics Aps.
 * Mod: $RCSfile: ExtendRefRep.c,v $, rel: %R%, date: $Date: 1992-08-19 15:44:57 $, SID: $Revision: 1.6 $
 * by Peter Andersen and Tommy Thorn.
 */

#define GCable_Module

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
    long newRange, copyRange, i;

    GCable_Entry

#define theRep (cast(RefRep) GCreg2)
#define newRep (cast(RefRep) GCreg3)

    Ck(theObj);
    theRep = *casthandle(RefRep) ((long *) theObj + offset);
    newRange = theRep->HighBorder + add;
    copyRange = (add < 0) ? newRange : theRep->HighBorder;

    if (newRange < 0)
      newRange = 0;
    
    newRep = cast(RefRep) IOAcalloc(RefRepSize(newRange));
    
    newRep->Proto = RefRepPTValue;
    newRep->GCAttr = 1;
    newRep->LowBorder = 1;
    newRep->HighBorder = newRange;
    
    for (i = 0; i < copyRange; ++i)
      newRep->Body[i] = theRep->Body[i];

    AssignReference((long *)theObj + offset, cast(Item) newRep);
}

