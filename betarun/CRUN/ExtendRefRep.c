/* File: ExtendRefRep.c
 * $Id: ExtendRefRep.c,v 1.1 1992-06-06 03:36:43 beta Exp $
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
    
    newRep->Proto = cast(ProtoType) -3;
    newRep->GCAttr = 1;
    newRep->LowBorder = 1;
    newRep->HighBorder = newRange;
    
    *casthandle(RefRep)((long *)theObj + offset) = newRep;
    for (i = 0; i < copyRange; ++i)
      newRep->Body[i] = theRep->Body[i];
}

