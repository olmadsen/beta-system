/* File: ExtendValRep.c
 * $Id: ExtendValRep.c,v 1.1 1992-06-06 03:36:44 beta Exp $
 */

#include "beta.h"
#include "crun.h"

asmlabel(ExtendValRep, "
	ba	_CExtendValRep
	mov	%l7, %o2
");

void CExtendValRep(ref(Object) theObj,
		   unsigned offset, /* in longs */
		   long add
		   )
{
    ref(ValRep) theRep = *casthandle(ValRep) ((long *) theObj + offset);
    ref(ValRep) newRep;
    long newRange = theRep->HighBorder + add;
    long copyRange = (add < 0) ? newRange : theRep->HighBorder;
    int i;

    if (newRange < 0)
      newRange = 0;
    
    if (newRange > LARGE_REP_SIZE) {
	newRep = cast(ValRep) LVRAAlloc(newRange);
	if (newRep) {
	    /* Make the LVRA-cycle: theCell -> theRep.GCAttr */
	    newRep->GCAttr = (int) ((long *) theObj + offset);
	    *casthandle(ValRep)((long *)theObj + offset) = newRep;
	    int_clear((char*)newRep->Body, newRange*4);
	    for (i = 0; i < copyRange; ++i)
	      newRep->Body[i] = theRep->Body[i];
	    return;
	}
    }
    
    newRep = cast(ValRep) IOAcalloc(newRange*4 + headsize(ValRep));
    
    newRep->Proto = cast(ProtoType) -3;
    newRep->GCAttr = 1;
    newRep->LowBorder = 1;
    newRep->HighBorder = newRange;
    
    *casthandle(ValRep)((long *)theObj + offset) = newRep;
    for (i = 0; i < copyRange; ++i)
      newRep->Body[i] = theRep->Body[i];
}

