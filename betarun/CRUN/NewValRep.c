/*
 * BETA C RUNTIME SYSTEM, Copyright (C) 1992-94 Mjolner Informatics Aps.
 * by Peter Andersen and Tommy Thorn.
 */

#define GCable_Module

#include "beta.h"
#include "crun.h"

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
#ifdef hppa
	    range = (long)getR2Reg();
	    pushReference(getThisReg());
	    setThisReg(theObj);
	    setD0Reg(offset * 4);
	    setD1Reg(range);
#endif
	    theRep = (casthandle(ValRep)theObj)[offset];
	    
	    switch( SwitchProto(theRep->Proto)){
#ifdef sparc
	    case SwitchProto(ByteRepPTValue):
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
	      CAlloORR(REP->iOrigin, theObj, 4*offset, REP->iProto, 0, range);
	      break;
	    case SwitchProto(DynCompRepPTValue):
	      CAlloORRC(REP->iOrigin, theObj, 4*offset, REP->iProto, 0, range);
	      break;
#ifdef STATIC_OBJECT_REPETITIONS
	    case SwitchProto(StatItemRepPTValue):
	      CAlloORG(REP->iOrigin, theObj, 4*offset, REP->iProto, 0, range);
	      break;
	    case SwitchProto(StatCompRepPTValue):
	      CAlloORGC(REP->iOrigin, theObj, 4*offset, REP->iProto, 0, range);
	      break;
#endif /* STATIC_OBJECT_REPETITIONS */
#else
	    case SwitchProto(ByteRepPTValue):
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
	      AlloORR(REP->iOrigin, theObj, 4*offset, REP->iProto, range);
	      break;
	    case SwitchProto(DynCompRepPTValue):
	      SetObjOriginProtoOffRange();
	      AlloORRC(REP->iOrigin, theObj, 4*offset, REP->iProto, range);
	      break;
#ifdef STATIC_OBJECT_REPETITIONS
	    case SwitchProto(StatItemRepPTValue):
	      SetObjOriginProtoOffRange();
	      AlloORG(REP->iOrigin, theObj, 4*offset, REP->iProto, range);
	      break;
	    case SwitchProto(StatCompRepPTValue):
	      SetObjOriginProtoOffRange();
	      AlloORGC(REP->iOrigin, theObj, 4*offset, REP->iProto, range);
	      break;
#endif /* STATIC_OBJECT_REPETITIONS */
#endif
	    default:
	      Notify("NewValRep: wrong prototype");
	      BetaExit(1);
	    }
#ifdef hppa
	    setThisReg(popReference());
#endif
	    );
    /* datpete 31-8-95: deleted check for AOAtoIOAinsert below:
     * it is handled by the AlloXXX above.
     */
}
