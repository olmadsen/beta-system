/*
 * BETA C RUNTIME SYSTEM, Copyright (C) 1990,91,92 Mjolner Informatics Aps.
 * Mod: $RCSfile: CopyValRep.c,v $, rel: %R%, date: $Date: 1992-07-20 11:48:04 $, SID: $Revision: 1.4 $
 * by Peter Andersen and Tommy Thorn.
 */

#include "beta.h"
#include "crun.h"

void CopyVR(ref(ValRep) theRep,
	    ref(Object) theObj,
	    unsigned offset /* i ints */
	    )
{
    register unsigned range, i;
    register ref(ValRep) newRep = NULL;

    range = theRep->HighBorder;
    if (range > LARGE_REP_SIZE)
      switch(theRep->Proto){
      case ByteRepPTValue:
	newRep = cast(ValRep) LVRAByteAlloc(range);
	break;
      default:
	newRep = cast(ValRep) LVRAAlloc(range);
      }
    if (newRep) {
	/* Make the LVRA-cycle: theCell -> newRep.Age */
	newRep->GCAttr = (int) ((int *) theObj + offset);
      }
    else
      {
	bodysize = (theRep->Proto==ByteRepPTValue)? ((range+4)/4)*4 : range*4;
	newRep = cast(ValRep) IOAcalloc(bodysize + headsize(ValRep));

	newRep->Proto = theRep->Proto;
	newRep->GCAttr = 1;
	newRep->LowBorder = 1;
	newRep->HighBorder = range;
      }

    /* Copy theRep to newRep */
    for (i = 0; i < range; ++i)
      newRep->Body[i] = theRep->Body[i];	/* Beautiful! */

    (casthandle(ValRep) theObj)[offset] = newRep;

    if (!inIOA((int *)theObj + offset))
      ChkRA((int *)theObj + offset);
}

