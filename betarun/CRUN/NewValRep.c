/*
 * BETA C RUNTIME SYSTEM, Copyright (C) 1990,91,92 Mjolner Informatics Aps.
 * Mod: $RCSfile: NewValRep.c,v $, rel: %R%, date: $Date: 1992-08-22 02:08:50 $, SID: $Revision: 1.5 $
 * by Peter Andersen and Tommy Thorn.
 */

#define GCable_Module

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
    GCable_Entry


#define theRep (cast(ValRep) GCreg3)
  
  Ck(theObj);
  theRep = (casthandle(ValRep)theObj)[offset];
  
  switch( (int) theRep->Proto){
  case (int) ByteRepPTValue:
    CAlloVR1(theObj, offset*4, range); /* MP MP !! */
    break;
  case (int) WordRepPTValue:
    CAlloVR2(theObj, offset*4, range); /* MP MP !! */
    break;
  case (int) ValRepPTValue:
    CAlloVR4(theObj, offset*4, range); /* MP MP !! */
    break;
  case (int) DoubleRepPTValue:
    CAlloVR8(theObj, offset*4, range); /* MP MP !! */
    break;
  default:
    fprintf(output, "NewValRep: wrong prototype\n");
    exit(1);
  }
  if (!inIOA((long *)theObj+offset))
    CCheckRefAsgn((struct Object **)theObj+offset);
}
  
