/* File: CopyValRep.c
 * $Id: CopyValRep.c,v 1.1 1992-06-06 03:36:41 beta Exp $
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

	  newRep->Proto = cast(ProtoType) -3;
	  newRep->GCAttr = 1;
	  newRep->LowBorder = 1;
	  newRep->HighBorder = range;
      }

    /* Copy theRep to newRep */
    for (i = 0; i < range; ++i)
      newRep->Body[i] = theRep->Body[i];	/* Beautiful! */

    (casthandle(ValRep) theObj)[offset] = newRep;
}

