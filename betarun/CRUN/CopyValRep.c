/*
 * BETA C RUNTIME SYSTEM, Copyright (C) 1990,91,92 Mjolner Informatics Aps.
 * Mod: $RCSfile: CopyValRep.c,v $, rel: %R%, date: $Date: 1992-07-21 17:17:56 $, SID: $Revision: 1.5 $
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
    switch( (int) theRep->Proto){
    case (int) ByteRepPTValue:
      newRep = cast(ValRep) LVRAByteAlloc(range);
      break;
    case (int) WordRepPTValue:
      newRep = cast(ValRep) LVRAWordAlloc(range);
      break;
    case (int) ValRepPTValue:
      newRep = cast(ValRep) LVRAAlloc(range);
      break;
    case (int) DoubleRepPTValue:
      newRep = cast(ValRep) LVRADoubleAlloc(range);
      break;
    default:
      fprintf(output, "CopyValRep: wrong prototype\n");
      exit(1);
    }
  if (newRep) {
    /* Make the LVRA-cycle: theCell -> newRep.Age */
    newRep->GCAttr = (int) ((int *) theObj + offset);
  }
  else
    {
      newRep = cast(ValRep) IOAcalloc(DispatchValRepSize(theRep,range));
      
      newRep->Proto = theRep->Proto;
      newRep->GCAttr = 1;
      newRep->LowBorder = 1;
      newRep->HighBorder = range;
    }
  
  /* Copy theRep to newRep */
  for (i = 0; i < range; ++i)
    newRep->Body[i] = theRep->Body[i];	/* Beautiful! */
  
  AssignReference((long *)theObj + offset, cast(Item) newRep);
}

