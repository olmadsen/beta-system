/*
 * BETA C RUNTIME SYSTEM, Copyright (C) 1992-94 Mjolner Informatics Aps.
 * by Peter Andersen and Tommy Thorn.
 */

#define GCable_Module

#include "beta.h"
#include "crun.h"

#ifdef hppa
#define HPPA_CODE(code) code;
#else
#define HPPA_CODE(code)
#endif

#ifdef sparc
#define SPARC_CODE(code) code
#define NON_SPARC_CODE(code)
#else
#define SPARC_CODE(code)
#define NON_SPARC_CODE(code) code
#endif

#define REP ((struct ObjectRep *)theRep)

#ifdef hppa
#define SetObjOriginProtoOffRange() \
  setD1Reg(range);                  \
  setOriginReg(REP->iOrigin);       \
  setCallReg(REP->iProto);          \
  setThisReg(theObj);               \
  setD0Reg(4*offset);
#else
#define SetObjOriginProtoOffRange() 
#endif

#ifdef sparc
asmlabel(NewVR, "
	mov	%o1, %o2
	mov	%l7, %o5
        clr     %o1
        clr     %o3
	ba	"CPREF"NewVR
        clr     %o4
");
void CNewVR(ref(Object) theObj,
	    int i1,
	    long offset /* in ints */,
	    int i3,
	    int i4,
	    long range)
#else
void NewVR(ref(Object) theObj, 
	   long offset /* in ints */,
	   long range)
#endif
{
    DeclReference1(struct ValRep *, theRep);
    GCable_Entry();

    DEBUG_CODE(NumNewVR++);
    
    Ck(theObj);

    Protect(theObj, 
	    HPPA_CODE(range = (long)getR2Reg();
		      pushReference(getThisReg());
		      setThisReg(theObj);
		      setD0Reg(offset * 4);
		      setD1Reg(range));
	    theRep = (casthandle(ValRep)theObj)[offset];
	    
	    switch( SwitchProto(theRep->Proto)){
	      SPARC_CODE(case SwitchProto(ByteRepPTValue):
			 CAlloVR1(theObj, 0, offset*4, 0, 0, range);
			 break;
			 case SwitchProto(WordRepPTValue):
			 CAlloVR2(theObj, 0, offset*4, 0, 0, range); 
			 break;
			 case SwitchProto(ValRepPTValue):
			 CAlloVR4(theObj, 0, offset*4, 0, 0, range);
			 break;
			 case SwitchProto(DoubleRepPTValue):
			 CAlloVR8(theObj, 0, offset*4, 0, 0, range); 
			 break;
			 case SwitchProto(DynItemRepPTValue):
			 CAlloVRI(REP->iOrigin, theObj, 4*offset, REP->iProto, 0, range);
			 break;
			 case SwitchProto(DynCompRepPTValue):
			 CAlloVRC(REP->iOrigin, theObj, 4*offset, REP->iProto, 0, range);
			 break);
	      
	      NON_SPARC_CODE(case SwitchProto(ByteRepPTValue):
			     AlloVR1(theObj, offset*4, range);
			     break;
			     case SwitchProto(WordRepPTValue):
			     AlloVR2(theObj, offset*4, range); 
			     break;
			     case SwitchProto(ValRepPTValue):
			     AlloVR4(theObj, offset*4, range);
			     break;
			     case SwitchProto(DoubleRepPTValue):
			     AlloVR8(theObj, offset*4, range); 
			     break;
			     case SwitchProto(DynItemRepPTValue):
			     SetObjOriginProtoOffRange();
			     AlloVRI(REP->iOrigin, theObj, 4*offset, REP->iProto, range);
			     break;
			     case SwitchProto(DynCompRepPTValue):
			     SetObjOriginProtoOffRange();
			     AlloVRC(REP->iOrigin, theObj, 4*offset, REP->iProto, range);
			     break);
	    default:
	      Notify("NewValRep: wrong prototype");
	      BetaExit(1);
	    }
	    HPPA_CODE(setThisReg(popReference()));
	    );
}
