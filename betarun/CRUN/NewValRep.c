/*
 * BETA C RUNTIME SYSTEM, Copyright (C) 1992-94 Mjolner Informatics Aps.
 * by Peter Andersen and Tommy Thorn.
 */

#define GCable_Module

#include "beta.h"
#include "crun.h"

asmlabel(NewVR, "
	mov	%o1, %o2
	mov	%l7, %o5
        clr     %o1
        clr     %o3
	ba	"CPREF"NewVR
        clr     %o4
");

#ifdef hppa
void NewVR(ref(Object) theObj, 
	   long offset /* in ints */,
	   long range)
#else
void CNewVR(ref(Object) theObj,
	    int i1,
	    long offset /* in ints */,
	    int i3,
	    int i4,
	    long range)
#endif
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
#ifdef sparc
	    case (long) ByteRepPTValue:
	      CAlloVR1(theObj, 0, offset*4, 0, 0, range);
	      break;
	    case (long) WordRepPTValue:
	      CAlloVR2(theObj, 0, offset*4, 0, 0, range); 
	      break;
	    case (long) ValRepPTValue:
	      CAlloVR4(theObj, 0, offset*4, 0, 0, range);
	      break;
	    case (long) DoubleRepPTValue:
	      CAlloVR8(theObj, 0, offset*4, 0, 0, range); 
	      break;
#else
	    case (long) ByteRepPTValue:
	      AlloVR1(theObj, offset*4, range);
	      break;
	    case (long) WordRepPTValue:
	      AlloVR2(theObj, offset*4, range); 
	      break;
	    case (long) ValRepPTValue:
	      AlloVR4(theObj, offset*4, range);
	      break;
	    case (long) DoubleRepPTValue:
	      AlloVR8(theObj, offset*4, range); 
	      break;
#endif
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
