/*
 * BETA C RUNTIME SYSTEM, Copyright (C) 1992-93 Mjolner Informatics Aps.
 * by Peter Andersen and Tommy Thorn.
 */

#define GCable_Module

#include "beta.h"
#include "crun.h"

asmlabel(CopyRR, "
        clr     %o3
	ba	_CCopyRR
        clr     %o4
");

#ifdef hppa
#  define CCopyRR CopyRR
#endif

void CCopyRR(ref(ValRep) theRep,
	    ref(Object) theObj,
	    unsigned offset /* in ints */
	    )
{
    DeclReference1(struct RefRep *, newRep);
    register unsigned range, i;
    
    GCable_Entry();
    
#ifdef sparc
    ClearCParams(); /* OK here: is not called from RT */
#endif
    
    Ck(theRep);Ck(theObj);
    newRep = NULL;
    
    range = theRep->HighBorder;

    Protect2(theObj, theRep,
	     newRep = cast(RefRep) IOAcalloc(RefRepSize(range)));
    
    Ck(theRep); Ck(theObj);

    newRep->Proto = theRep->Proto;
    newRep->GCAttr = 1;
    newRep->LowBorder = 1;
    newRep->HighBorder = range;
    
    /* Copy theRep to newRep */
    for (i = 0; i < range; ++i)
      newRep->Body[i] = theRep->Body[i];	/* Beautiful! */
    
    AssignReference((long *)theObj + offset, cast(Item) newRep);
}

