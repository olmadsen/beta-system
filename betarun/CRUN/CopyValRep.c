/*
 * BETA C RUNTIME SYSTEM, Copyright (C) 1990,91,92 Mjolner Informatics Aps.
 * Mod: $RCSfile: CopyValRep.c,v $, rel: %R%, date: $Date: 1992-08-31 21:57:40 $, SID: $Revision: 1.9 $
 * by Peter Andersen and Tommy Thorn.
 */

#define GCable_Module

#include "beta.h"
#include "crun.h"

void CopyVR(ref(ValRep) theRep,
	    ref(Object) theObj,
	    unsigned offset /* i ints */
	    )
{
    DeclReference1(struct ValRep *, newRep);
    register unsigned range, i;
    
    GCable_Entry();
    
    Ck(theRep); Ck(theObj);
    newRep = NULL;
    
    range = theRep->HighBorder;
    if (range > LARGE_REP_SIZE) {
	Protect2(theRep, theObj,
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
		 });
    }
    if (newRep) {
	/* Make the LVRA-cycle: theCell -> newRep.Age */
	newRep->GCAttr = (int) ((int *) theObj + offset);
    }
    else
      {
	  Protect2(theObj, theRep,
		   newRep = cast(ValRep) 
		   IOAcalloc(DispatchValRepSize(theRep,range))
		   );
	  
	  Ck(theObj);
	  newRep->Proto = theRep->Proto;
	  newRep->GCAttr = 1;
	  newRep->LowBorder = 1;
	  newRep->HighBorder = range;
      }
    
    /* Copy theRep to newRep */
    for (i = 0; i < range; ++i)
      newRep->Body[i] = theRep->Body[i];
    
    AssignReference((long *)theObj + offset, cast(Item) newRep);
}

