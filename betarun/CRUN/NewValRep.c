/*
 * BETA C RUNTIME SYSTEM, Copyright (C) 1990,91,92 Mjolner Informatics Aps.
 * Mod: $RCSfile: NewValRep.c,v $, rel: %R%, date: $Date: 1992-07-21 17:18:44 $, SID: $Revision: 1.3 $
 * by Peter Andersen and Tommy Thorn.
 */

#include "beta.h"
#include "crun.h"

asmlabel(NewVR, "
	ba	_CNewVR
	mov	%l7, %o0
");

void CNewVR(int range,
	    int dummy,
	    ref(Object) theObj,
	    int offset /* in ints */
	    )
{
  register long *theCell = (long *)theObj+offset;
  register ref(ValRep) theRep = cast(ValRep)(*theCell);
  
  switch( (int) theRep->Proto){
  case (int) ByteRepPTValue:
    CAlloVR1(theObj, offset, range);
    break;
  case (int) WordRepPTValue:
    CAlloVR2(theObj, offset, range);
    break;
  case (int) ValRepPTValue:
    CAlloVR4(theObj, offset, range);
    break;
  case (int) DoubleRepPTValue:
    CAlloVR8(theObj, offset, range);
    break;
  default:
    fprintf(output, "NewValRep: wrong prototype\n");
    exit(1);
  }
  
  theCell = (long *)theObj+offset;
  if (!inIOA(theCell)) ChkRA(theCell);
}
  
