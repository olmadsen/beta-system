/*
 * BETA C RUNTIME SYSTEM, Copyright (C) 1990,91,92 Mjolner Informatics Aps.
 * Mod: $RCSfile: ExtendValRep.c,v $, rel: %R%, date: $Date: 1992-07-21 17:16:01 $, SID: $Revision: 1.4 $
 * by Peter Andersen and Tommy Thorn.
 */

#include "beta.h"
#include "crun.h"

asmlabel(ExtVR, "
	ba	_CExtVR
	mov	%l7, %o2
");

void CExtVR(ref(Object) theObj,
	    unsigned offset, /* in longs */
	    long add /* What to extend the range with */
	    )
{
  long *theCell = (long *) theObj + offset;
  ref(ValRep) theRep = *casthandle(ValRep) theCell;
  ref(ValRep) newRep;
  long newRange = theRep->HighBorder + add; /* Range of new repetition */
  long copyRange; /* Range to copy from old rep */
  int i;
  
  if (newRange < 0) newRange = 0;
  copyRange = DispatchValRepBodySize(theRep, (add < 0) ? newRange : theRep->HighBorder) >> 2;
  
  if (newRange > LARGE_REP_SIZE) {
    switch((int) theRep->Proto){
    case (int) ByteRepPTValue:
      newRep = cast(ValRep) LVRAByteAlloc(newRange);
      break;
    case (int) WordRepPTValue:
      newRep = cast(ValRep) LVRAWordAlloc(newRange);
      break;
    case (int) ValRepPTValue:
      newRep = cast(ValRep) LVRAAlloc(newRange);
      break;
    case (int) DoubleRepPTValue:
      newRep = cast(ValRep) LVRADoubleAlloc(newRange);
      break;
    default:
      newRep = cast(ValRep) 0;
    }
    
    if (newRep) {
      /* Make the LVRA-cycle: theCell -> theRep.GCAttr */
      theCell = (long *) theObj + offset; /* Recalculation may be needed */
      newRep->GCAttr = (int) theCell;
      *casthandle(ValRep) theCell = newRep;
      int_clear((char*)newRep->Body, newRange*4);
      for (i = 0; i < copyRange; ++i)
	newRep->Body[i] = theRep->Body[i];
      return;
    }
  }
  
  /* Allocate and nullify new repetition: There is a little overhead here;
   * only extension needs to be nullified
   */
  newRep = cast(ValRep) IOAcalloc(DispatchValRepSize(theRep, newRange));
  
  /* Assign structural part of new repetition */
  newRep->Proto = theRep->Proto;
  newRep->GCAttr = 1;
  newRep->LowBorder = theRep->LowBorder;
  newRep->HighBorder = newRange;
  
  /* Assign into theObj */
  theCell = (long *) theObj + offset; /* Recalculation may be needed */

  AssignReference(theCell, cast(Item) newRep);

  /* Copy contents of old rep to new rep */
  for (i = 0; i < copyRange; ++i)
    newRep->Body[i] = theRep->Body[i];
}

