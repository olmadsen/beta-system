/*
 * BETA C RUNTIME SYSTEM, Copyright (C) 1990,91,92 Mjolner Informatics Aps.
 * Mod: $RCSfile: CopyRefRep.c,v $, rel: %R%, date: $Date: 1992-08-19 15:44:37 $, SID: $Revision: 1.2 $
 * by Peter Andersen and Tommy Thorn.
 */

#define GCable_Module

#include "beta.h"
#include "crun.h"

void CopyRR(ref(ValRep) theRep,
	    ref(Object) theObj,
	    unsigned offset /* i ints */
	    )
{
  register unsigned range, i;
 
  GCable_Entry
#define newRep (cast(RefRep) GCreg3)

    Ck(theRep);Ck(theObj);
  newRep = NULL;
  
  range = theRep->HighBorder;
  newRep = cast(RefRep) IOAcalloc(RefRepSize(range));
  
  newRep->Proto = theRep->Proto;
  newRep->GCAttr = 1;
  newRep->LowBorder = 1;
  newRep->HighBorder = range;
  
  /* Copy theRep to newRep */
  for (i = 0; i < range; ++i)
    newRep->Body[i] = theRep->Body[i];	/* Beautiful! */
  
  AssignReference((long *)theObj + offset, cast(Item) newRep);
}

