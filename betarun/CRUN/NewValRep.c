/*
 * BETA C RUNTIME SYSTEM, Copyright (C) 1992-93 Mjolner Informatics Aps.
 * by Peter Andersen and Tommy Thorn.
 */

#define GCable_Module

#include "beta.h"
#include "crun.h"

asmlabel(NewVR, "
	ba	_CNewVR
	mov	%l7, %o2
");

#ifdef hppa
#  define CNewVR NewVR
#  define CAlloVR1 AlloVR1
#  define CAlloVR2 AlloVR2
#  define CAlloVR4 AlloVR4
#  define CAlloVR8 AlloVR8
#endif

void CNewVR(ref(Object) theObj, long offset /* in ints */, long range)
{
    DeclReference1(struct ValRep *, theRep);
    GCable_Entry();

    Ck(theObj);

    Protect(theObj, 
#ifdef hppa
	    range = (long)getR2Reg();
	    pushReference(getThisReg());
	    setThisReg(theObj);
	    setD0Reg(offset * 4);
	    setD1Reg(range);
#endif
	    if (range<0) range=0;
	    theRep = (casthandle(ValRep)theObj)[offset];
	    
	    switch( (long) theRep->Proto){
	    case (long) ByteRepPTValue:
	      CAlloVR1(theObj, offset*4, range); /* MP MP !! */
	      break;
	    case (long) WordRepPTValue:
	      CAlloVR2(theObj, offset*4, range); /* MP MP !! */
	      break;
	    case (long) ValRepPTValue:
	      CAlloVR4(theObj, offset*4, range); /* MP MP !! */
	      break;
	    case (long) DoubleRepPTValue:
	      CAlloVR8(theObj, offset*4, range); /* MP MP !! */
	      break;
	    default:
	      fprintf(output, "NewValRep: wrong prototype\n");
	      exit(1);
	    }
#ifdef hppa
	    setThisReg(popReference());
#endif
	    );
    if (! inIOA((struct Object **)theObj+offset) &&
	inIOA(*(struct Object **)theObj+offset))
      AOAtoIOAInsert((struct Object **)theObj+offset);
}
