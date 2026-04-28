#ifdef hppa
#undef RTDEBUG /* Sorry. The new gcc complains about getR2Reg()  */
#endif

/*
 * BETA C RUNTIME SYSTEM, Copyright (C) Aarhus University
 * by Peter Andersen, Tommy Thorn, and Jacob Seligmann
 */

#define REP ((ObjectRep *)theRep)
#define NEWREP ((ObjectRep *)newRep)

#ifdef hppa
register long _dummy8 __asm__("%r15"); /* really tmp data 1 */
register long _dummy9 __asm__("%r16"); /* really tmp data 2 */
#endif

#include "beta.h"
#include "crun.h"

ParamRepObjOffLowHigh(CopySVR1)
{
    DeclReference1(ValRep *, newRep);
    register long i, size, range;
    
    FetchRepObjOffLowHigh();

    DEBUG_CODE(NumCopySVR1++);
    Ck(theObj); Ck(theRep);

    /* Copy a slice of a Value Repetition. */
    
    /* Check that low and high are usable. */
    if ( (low < theRep->LowBorder) /* || (theRep->HighBorder < low) */ ) {
      SubRangeErrLow = low;
      SubRangeErrHigh = high;
      RangeMax = theRep->HighBorder;
      BetaError(RepLowRangeErr, (Object *)theObj);
    }
    if ( /* (high < theRep->LowBorder) || */ (theRep->HighBorder < high) ) {
      SubRangeErrLow = low;
      SubRangeErrHigh = high;
      RangeMax = theRep->HighBorder;
      BetaError(RepHighRangeErr, (Object *)theObj);
    }
    
    /* Calculate the range of the new repetition. */
    range =  (high - low) + 1;
    if (range < 0) range = 0;

    while (1) {
      Ck(theObj);

      if (range > LARGE_REP_SIZE) {
        newRep = (ValRep *) LVRAAlloc(ByteRepPTValue, range);
        if (newRep) {
	  Claim(newRep->HighBorder==range&&newRep->LowBorder==1, "LVRA structure ok");
	  break;
        }
      }

      size = ByteRepSize(range);
      Protect2(theRep, theObj, newRep = (ValRep *)IOATryAlloc(size));

      if (newRep) {
	/* Initialize the structual part of the repetition. */
	SETPROTO(newRep,ByteRepPTValue);
	if (IOAMinAge!=0) newRep->GCAttr = IOAMinAge;
	newRep->LowBorder = 1;
	newRep->HighBorder = range;
	break;
      }
    } 

    /* Copy the body part of the repetition. */
    { /* Since the slice may start on any byte we copy it byte by byte */
      char *newBody = (char *)(newRep->Body);
      char *oldBody = (char*)(theRep->Body) + (low-theRep->LowBorder);
      for (i = 0;  i < range; ++i){
	newBody[i] = oldBody[i];
      }
      /* Null termination: */
      newBody[range] = 0 ;
    }

    AssignReference((long *)theObj + offset, (Item *) newRep);

    Ck(newRep); Ck(theRep); Ck(theObj);

}

ParamRepObjOffLowHigh(CopySVR2)
{
    DeclReference1(ValRep *, newRep);
    register long i, size, range;
    
    FetchRepObjOffLowHigh();

    DEBUG_CODE(NumCopySVR2++);
    Ck(theObj); Ck(theRep);

    /* Copy a slice of a Value Repetition. */
    
    /* Check that low and high are usable. */
    if ( (low < theRep->LowBorder) /* || (theRep->HighBorder < low) */ ) {
      SubRangeErrLow = low;
      SubRangeErrHigh = high;
      RangeMax = theRep->HighBorder;
      BetaError(RepLowRangeErr, (Object *)theObj);
    }
    if ( /* (high < theRep->LowBorder) || */ (theRep->HighBorder < high) ) {
      SubRangeErrLow = low;
      SubRangeErrHigh = high;
      RangeMax = theRep->HighBorder;
      BetaError(RepHighRangeErr, (Object *)theObj);
    }
    
    /* Calculate the range of the new repetition. */
    range =  (high - low) + 1;
    if (range < 0) range = 0;

    while (1) {
      Ck(theObj);

      if (range > LARGE_REP_SIZE) {
        newRep = (ValRep *) LVRAAlloc(ShortRepPTValue, range);
        if (newRep) {
	  Claim(newRep->HighBorder==range&&newRep->LowBorder==1, "LVRA structure ok");
	  break;
        }
      }

      size = ShortRepSize(range);
      Protect2(theRep, theObj, newRep = (ValRep *)IOATryAlloc(size));

      if (newRep) {
	/* Initialize the structual part of the repetition. */
	SETPROTO(newRep, ShortRepPTValue);
	if (IOAMinAge!=0) newRep->GCAttr = IOAMinAge;
	newRep->LowBorder = 1;
	newRep->HighBorder = range;
	break;
      }
    } 
    
    /* Copy the body part of the repetition. */
    { /* Since the slice may start on any word we copy it word by word */
      short *newBody = (short *)newRep->Body;
      short *oldBody = (short *)(theRep->Body) + (low-theRep->LowBorder);
      for (i = 0;  i < range; ++i){
	newBody[i] = oldBody[i];
      }
    }
        
    AssignReference((long *)theObj + offset, (Item *) newRep);

    Ck(newRep); Ck(theRep); Ck(theObj);

}

ParamRepObjOffLowHigh(CopySVR4)
{
    DeclReference1(ValRep *, newRep);
    register long i, size, range;
    
    FetchRepObjOffLowHigh();
    
    DEBUG_CODE(NumCopySVR4++);
    Ck(theObj); Ck(theRep);

    /* Copy a slice of a Value Repetition. */
    
    /* Check that low and high are usable. */
    if ( (low < theRep->LowBorder) /* || (theRep->HighBorder < low) */ ) {
      SubRangeErrLow = low;
      SubRangeErrHigh = high;
      RangeMax = theRep->HighBorder;
      BetaError(RepLowRangeErr, (Object *)theObj);
    }
    if ( /* (high < theRep->LowBorder) || */ (theRep->HighBorder < high) ) {
      SubRangeErrLow = low;
      SubRangeErrHigh = high;
      RangeMax = theRep->HighBorder;
      BetaError(RepHighRangeErr, (Object *)theObj);
    }
    
    /* Calculate the range of the new repetition. */
    range =  (high - low) + 1;
    if (range < 0) range = 0;

    while (1) {
      Ck(theObj);

      if (range > LARGE_REP_SIZE) {
        newRep = (ValRep *) LVRAAlloc(LongRepPTValue, range);
        if (newRep) {
	  Claim(newRep->HighBorder==range&&newRep->LowBorder==1, "LVRA structure ok");
	  break;
        }
      }
      
      size = LongRepSize(range);
      Protect2(theRep, theObj, newRep = (ValRep *)IOATryAlloc(size));

      if (newRep) {
	/* Initialize the structual part of the repetition. */
	SETPROTO(newRep,LongRepPTValue );
	if (IOAMinAge!=0) newRep->GCAttr = IOAMinAge;
	newRep->LowBorder = 1;
	newRep->HighBorder = range;
	break;
      }
    } 

    /* Copy the body part of the repetition. */
    for (i = 0; i < range; ++i){
      newRep->Body[i] = theRep->Body[i+low-theRep->LowBorder];
    } 
        
    AssignReference((long *)theObj + offset, (Item *) newRep);

    Ck(newRep); Ck(theRep); Ck(theObj);

}

ParamRepObjOffLowHigh(CopySVR8)
{
    DeclReference1(ValRep *, newRep);
    register long i, size, range;
    
    FetchRepObjOffLowHigh();
   
    DEBUG_CODE(NumCopySVR8++);
    Ck(theObj); Ck(theRep);

    /* Copy a slice of a Value Repetition. */
    
    /* Check that low and high are usable. */
    if ( (low < theRep->LowBorder) /* || (theRep->HighBorder < low) */ ) {
      SubRangeErrLow = low;
      SubRangeErrHigh = high;
      RangeMax = theRep->HighBorder;
      BetaError(RepLowRangeErr, (Object *)theObj);
    }
    if ( /* (high < theRep->LowBorder) || */ (theRep->HighBorder < high) ) {
      SubRangeErrLow = low;
      SubRangeErrHigh = high;
      RangeMax = theRep->HighBorder;
      BetaError(RepHighRangeErr, (Object *)theObj);
    }

    /* Calculate the range of the new repetition. */
    range =  (high - low) + 1;
    if (range < 0) range = 0;

    while (1) {
      Ck(theObj);

      if (range > LARGE_REP_SIZE) {
        newRep = (ValRep *) LVRAAlloc(DoubleRepPTValue, range);
        if (newRep) {
	  Claim(newRep->HighBorder==range&&newRep->LowBorder==1, "LVRA structure ok");
	  break;
        }
      }
      
      size = DoubleRepSize(range);
      Protect2(theRep, theObj, newRep = (ValRep *)IOATryAlloc(size));

      if (newRep) {
	/* Initialize the structual part of the repetition. */
	SETPROTO(newRep, DoubleRepPTValue);
	if (IOAMinAge!=0) newRep->GCAttr = IOAMinAge;
	newRep->LowBorder = 1;
	newRep->HighBorder = range;
	break;
      }
    } 

    /* Copy the body part of the repetition. */
    { double *newBody = (double *)newRep->Body;
      double *oldBody = (double *)(theRep->Body) + (low-theRep->LowBorder);
      for (i=0; i<range; ++i){
	newBody[i] = oldBody[i];
      }
    }
        
    AssignReference((long *)theObj + offset, (Item *) newRep);

    Ck(newRep); Ck(theRep); Ck(theObj);

}

ParamORepObjOffLowHigh(CopySVRI)
{
    DeclReference1(ObjectRep *, newRep);
    register long i, size, range;
    
    FetchORepObjOffLowHigh();
   
    DEBUG_CODE(NumCopySVRI++);
    Ck(theObj); Ck(theRep);

    /* Copy a slice of an Object Repetition. */
    
    /* Check that low and high are usable. */
    if ( (low < theRep->LowBorder) /* || (theRep->HighBorder < low) */ ) {
      SubRangeErrLow = low;
      SubRangeErrHigh = high;
      RangeMax = theRep->HighBorder;
      BetaError(RepLowRangeErr, (Object *)theObj);
    }
    if ( /* (high < theRep->LowBorder) || */ (theRep->HighBorder < high) ) {
      SubRangeErrLow = low;
      SubRangeErrHigh = high;
      RangeMax = theRep->HighBorder;
      BetaError(RepHighRangeErr, (Object *)theObj);
    }
  
    /* Calculate the range of the new repetition. */
    range =  (high - low) + 1;
    if (range < 0) range = 0;

    size = DynObjectRepSize(range);

    /* FIXME: AOA alloc missing */

    Protect2(theRep,theObj,newRep = (ObjectRep *) IOAalloc(size));
    
    /* Initialize the structual part of the repetition. */
    SETPROTO(newRep,DynItemRepPTValue);
    if (IOAMinAge!=0) newRep->GCAttr = IOAMinAge;
    newRep->LowBorder = 1;
    newRep->HighBorder = range;
    newRep->iOrigin = theRep->iOrigin;
    newRep->iProto = theRep->iProto;

    /* Copy the body part of the repetition. */
    for (i = 0; i < range; ++i){
      newRep->Body[i] = theRep->Body[i+low-theRep->LowBorder];
      /* No need to use AssignReference: newRep is in IOA */
    }

    AssignReference((long *)theObj + offset, (Item *) newRep);

    Ck(newRep); Ck(theRep); Ck(theObj);

}

ParamORepObjOffLowHigh(CopySVRC)
{
    DeclReference1(ObjectRep *, newRep);
    register long i, size, range;
    
    FetchORepObjOffLowHigh();
  
    DEBUG_CODE(NumCopySVRC++);
    Ck(theObj); Ck(theRep);

    /* Copy a slice of an Object Repetition. */
    
    /* Check that low and high are usable. */
    if ( (low < theRep->LowBorder) /* || (theRep->HighBorder < low) */ ) {
      SubRangeErrLow = low;
      SubRangeErrHigh = high;
      RangeMax = theRep->HighBorder;
      BetaError(RepLowRangeErr, (Object *)theObj);
    }
    if ( /* (high < theRep->LowBorder) || */ (theRep->HighBorder < high) ) {
      SubRangeErrLow = low;
      SubRangeErrHigh = high;
      RangeMax = theRep->HighBorder;
      BetaError(RepHighRangeErr, (Object *)theObj);
    }
    
    /* Calculate the range of the new repetition. */
    range =  (high - low) + 1;
    if (range < 0) range = 0;

    size = DynObjectRepSize(range);

    /* FIXME: AOA alloc missing */

    Protect2(theRep,theObj,newRep = (ObjectRep *) IOAalloc(size));
    
    /* Initialize the structual part of the repetition. */
    SETPROTO(newRep,DynCompRepPTValue);
    if (IOAMinAge!=0) newRep->GCAttr = IOAMinAge;
    newRep->LowBorder = 1;
    newRep->HighBorder = range;
    newRep->iOrigin = theRep->iOrigin;
    newRep->iProto = theRep->iProto;

    /* Copy the body part of the repetition. */
    for (i = 0; i < range; ++i){
      newRep->Body[i] = theRep->Body[i+low-theRep->LowBorder];
      /* No need to use AssignReference: newRep is in IOA */
    }

    AssignReference((long *)theObj + offset, (Item *) newRep);

    Ck(newRep); Ck(theRep); Ck(theObj);

}


