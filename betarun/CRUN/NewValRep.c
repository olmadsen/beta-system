/*
 * BETA C RUNTIME SYSTEM, Copyright (C) 1990,91,92 Mjolner Informatics Aps.
 * Mod: $RCSfile: NewValRep.c,v $, rel: %R%, date: $Date: 1992-08-31 10:04:54 $, SID: $Revision: 1.7 $
 * by Peter Andersen and Tommy Thorn.
 */

#define GCable_Module

#include "beta.h"
#include "crun.h"

asmlabel(NewVR, "
	ba	_CNewVR
	mov	%l7, %o0
");

#ifdef hppa
#  define CNewVR NewVR
#  define CAlloVR1 AlloVR1
#  define CAlloVR2 AlloVR2
#  define CAlloVR4 AlloVR4
#  define CAlloVR8 AlloVR8
#endif

void CNewVR(ref(Object) theObj,
            int offset, /* in ints */
            int range
            )
{
    DeclReference1(struct ValRep *, theRep);
    GCable_Entry();

    Ck(theObj);

    Protect(theObj, 
#ifdef hppa
	    range = (int)getR2Reg();
	    setThisReg(theObj);
	    setD0Reg(offset * 4);
	    setD1Reg(range);
#endif

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
	    );
    if (!inIOA((long *)theObj+offset))
      CCheckRefAsgn((struct Object **)theObj+offset);
}

