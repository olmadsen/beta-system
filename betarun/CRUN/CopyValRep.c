/*
 * BETA C RUNTIME SYSTEM, Copyright (C) 1990,91,92 Mjolner Informatics Aps.
 * Mod: $RCSfile: CopyValRep.c,v $, rel: %R%, date: $Date: 1992-06-09 15:19:15 $, SID: $Revision: 1.3 $
 * by Peter Andersen and Tommy Thorn.
 */

#include "beta.h"
#include "crun.h"

void CopyValRep(ref(ValRep) theRep,
		ref(Object) theObj,
		unsigned offset /* i ints */
		)
{
    register unsigned range, i;
    register ref(ValRep) newRep = NULL;

    range = theRep->HighBorder;
    if (range > LARGE_REP_SIZE)
	newRep = cast(ValRep) LVRAAlloc(range);

    if (newRep) {
	/* Make the LVRA-cycle: theCell -> newRep.Age */
	newRep->GCAttr = (int) ((int *) theObj + offset);
      }
    else
      {
	  newRep = cast(ValRep) IOAcalloc(range*4 + headsize(ValRep));

	  newRep->Proto = ValRepPTValue;
	  newRep->GCAttr = 1;
	  newRep->LowBorder = 1;
	  newRep->HighBorder = range;
      }

    /* Copy theRep to newRep */
    for (i = 0; i < range; ++i)
      newRep->Body[i] = theRep->Body[i];	/* Beautiful! */

    (casthandle(ValRep) theObj)[offset] = newRep;
}

