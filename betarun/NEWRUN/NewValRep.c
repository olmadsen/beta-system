/*
 * BETA C RUNTIME SYSTEM, Copyright (C) 1992-94 Mjolner Informatics Aps.
 * by Peter Andersen and Tommy Thorn.
 */

#include "beta.h"
#include "crun.h"

#define REP ((struct ObjectRep *)theRep)

void NewVR(struct Object *theObj, 
	   long offset /* in longs */,
	   long range,
	   long *SP)
{
  struct ValRep * theRep;
  
  DEBUG_CODE(NumNewVR++);
  Ck(theObj);
  
  push(theObj); 
	  theRep = ((struct ValRep **)theObj)[offset];
	  switch(SwitchProto(theRep->Proto)){
	  case SwitchProto(ByteRepPTValue):
	    AlloVR1(theObj, offset*4, range, SP);
	    break;
	  case SwitchProto(WordRepPTValue):
	    AlloVR2(theObj, offset*4, range, SP); 
	    break;
	  case SwitchProto(ValRepPTValue):
	    AlloVR4(theObj, offset*4, range, SP);
	    break;
	  case SwitchProto(DoubleRepPTValue):
	    AlloVR8(theObj, offset*4, range, SP); 
	    break;
	  case SwitchProto(DynItemRepPTValue):
	    AlloORR(REP->iOrigin, REP->iProto, theObj, 4*offset, range, SP);
	    break;
	  case SwitchProto(DynCompRepPTValue):
	    AlloORRC(REP->iOrigin, REP->iProto, theObj, 4*offset, range, SP);
	    break;
#ifdef RTDEBUG
	  default:
	    Notify("NewValRep: wrong prototype");
	    BetaExit(1);
#endif
	  }
	 pop(theObj);
  
}
