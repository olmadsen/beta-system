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
  
  Protect(theObj, 
	  theRep = ((struct ValRep **)theObj)[offset];
	  switch( (long) theRep->Proto){
	  case (long) ByteRepPTValue:
	    AlloVR1(theObj, offset*4, range, SP);
	    break;
	  case (long) WordRepPTValue:
	    AlloVR2(theObj, offset*4, range, SP); 
	    break;
	  case (long) ValRepPTValue:
	    AlloVR4(theObj, offset*4, range, SP);
	    break;
	  case (long) DoubleRepPTValue:
	    AlloVR8(theObj, offset*4, range, SP); 
	    break;
	  case (long) DynItemRepPTValue:
	    AlloORR(REP->iOrigin, REP->iProto, theObj, 4*offset, range, SP);
	    break;
	  case (long) DynCompRepPTValue:
	    AlloORRC(REP->iOrigin, REP->iProto, theObj, 4*offset, range, SP);
	    break;
#ifdef RTDEBUG
	  default:
	    Notify("NewValRep: wrong prototype");
	    exit(1);
#endif
	  }
	  );
  
}
