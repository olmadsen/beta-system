/*
 * BETA C RUNTIME SYSTEM, Copyright (C) 1992-94 Mjolner Informatics Aps.
 * by Peter Andersen and Tommy Thorn.
 */

#include "beta.h"
#include "crun.h"

void CopyRR(struct ValRep *theRep,
	    struct Object *theObj,
	    unsigned offset /* in longs */,
	    long *SP
	    )
{
    struct RefRep * newRep;
    register unsigned range, i;
    
    DEBUG_CODE(NumCopyRR++);

    Ck(theRep); Ck(theObj);
    newRep = NULL;
    
    range = theRep->HighBorder;

    Protect2(theObj, theRep,
	     newRep = (struct RefRep *)IOAcalloc(RefRepSize(range), SP));
    
    Ck(theRep); Ck(theObj);

    newRep->Proto = theRep->Proto;
    newRep->GCAttr = 1;
    newRep->LowBorder = 1;
    newRep->HighBorder = range;
    
    /* Copy theRep to newRep */
    for (i = 0; i < range; ++i)
      /* AssignReference not needed:
       * only needed when dest may be in aoa and src may be in ioa.
       */
      newRep->Body[i] = theRep->Body[i];
    
    AssignReference((long *)theObj + offset, (struct Item *)newRep);
}

