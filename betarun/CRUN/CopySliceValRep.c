#ifdef hppa
#undef RTDEBUG /* Sorry. The new gcc complains about getR2Reg()  */
#endif

/*
 * BETA C RUNTIME SYSTEM, Copyright (C) 1992-94 Mjolner Informatics Aps.
 * by Peter Andersen, Tommy Thorn, and Jacob Seligmann
 */

#define REP ((struct ObjectRep *)theRep)
#define NEWREP ((struct ObjectRep *)newRep)

#ifdef hppa
register long _dummy8 __asm__("%r15"); /* really tmp data 1 */
register long _dummy9 __asm__("%r16"); /* really tmp data 2 */
#endif

#define GCable_Module

#include "beta.h"
#include "crun.h"

ParamRepObjOffLowHigh(CopySVR1)
{
    DeclReference1(struct ValRep *, newRep);
    register long i, size, range;
    
    GCable_Entry();
   
    FetchRepObjOffLowHigh();

    DEBUG_CODE(NumCopySVR1++);
    Ck(theObj); Ck(theRep);

    /* Copy a slice of a Value Repetition. */
    
    /* Check that low and high are usable. */
    if ( (low < theRep->LowBorder) /* || (theRep->HighBorder < low) */ ) 
      BetaError(RepLowRangeErr, cast(Object)theObj);
    if ( /* (high < theRep->LowBorder) || */ (theRep->HighBorder < high) ) 
       BetaError(RepHighRangeErr, cast(Object)theObj);
    
    /* Calculate the range of the new repetition. */
    range =  (high - low) + 1;
    if (range < 0) range = 0;

    size = ByteRepSize(range);

    /* LVRA missing */
    
    Protect2(theRep,theObj,newRep = cast(ValRep) IOAalloc(size));
    
    /* Initialize the structual part of the repetition. */
    newRep->Proto = ByteRepPTValue;
    if (IOAMinAge!=0) newRep->GCAttr = IOAMinAge;
    newRep->LowBorder = 1;
    newRep->HighBorder = range;

    /* Copy the body part of the repetition. */
    { /* Since the slice may start on any byte we copy it byte by byte */
      unsigned char *newBody = (unsigned char *)newRep->Body;
      unsigned char *oldBody = (unsigned char *)((unsigned)theRep->Body+(low-theRep->LowBorder));
      for (i = 0;  i < range; ++i){
	*(unsigned char *)((unsigned)newBody+i) = *(unsigned char *)((unsigned)oldBody+i);
      }
      /* Null termination: */
      *(unsigned char *)((unsigned)newBody+range) = 0 ;
    }
        
    AssignReference((long *)theObj + offset, cast(Item) newRep);

    Ck(newRep); Ck(theRep); Ck(theObj);

}

ParamRepObjOffLowHigh(CopySVR2)
{
    DeclReference1(struct ValRep *, newRep);
    register long i, size, range;
    
    GCable_Entry();

    FetchRepObjOffLowHigh();

    DEBUG_CODE(NumCopySVR2++);
    Ck(theObj); Ck(theRep);

    /* Copy a slice of a Value Repetition. */
    
    /* Check that low and high are usable. */
    if ( (low < theRep->LowBorder) /* || (theRep->HighBorder < low) */ ) 
      BetaError(RepLowRangeErr, cast(Object)theObj);
    if ( /* (high < theRep->LowBorder) || */ (theRep->HighBorder < high) ) 
       BetaError(RepHighRangeErr, cast(Object)theObj);
    
    /* Calculate the range of the new repetition. */
    range =  (high - low) + 1;
    if (range < 0) range = 0;

    size = ShortRepSize(range);

    /* LVRA missing */
    
    Protect2(theRep,theObj,newRep = cast(ValRep) IOAalloc(size));
    
    /* Initialize the structual part of the repetition. */
    newRep->Proto = ShortRepPTValue;
    if (IOAMinAge!=0) newRep->GCAttr = IOAMinAge;
    newRep->LowBorder = 1;
    newRep->HighBorder = range;

    /* Copy the body part of the repetition. */
    { /* Since the slice may start on any word we copy it word by word */
      short *newBody = (short *)newRep->Body;
      short *oldBody = (short *)((unsigned)theRep->Body+2*(low-theRep->LowBorder));
      for (i = 0;  i < range; ++i){
	*(short *)((unsigned)newBody+2*i) = *(short *)((unsigned)oldBody+2*i);
      }
    }
        
    AssignReference((long *)theObj + offset, cast(Item) newRep);

    Ck(newRep); Ck(theRep); Ck(theObj);

}

ParamRepObjOffLowHigh(CopySVR4)
{
    DeclReference1(struct ValRep *, newRep);
    register long i, size, range;
    
    GCable_Entry();

    FetchRepObjOffLowHigh();
    
    DEBUG_CODE(NumCopySVR4++);
    Ck(theObj); Ck(theRep);

    /* Copy a slice of a Value Repetition. */
    
    /* Check that low and high are usable. */
    if ( (low < theRep->LowBorder) /* || (theRep->HighBorder < low) */ ) 
      BetaError(RepLowRangeErr, cast(Object)theObj);
    if ( /* (high < theRep->LowBorder) || */ (theRep->HighBorder < high) ) 
       BetaError(RepHighRangeErr, cast(Object)theObj);
    
    /* Calculate the range of the new repetition. */
    range =  (high - low) + 1;
    if (range < 0) range = 0;

    size = LongRepSize(range);

    /* LVRA missing */
    
    Protect2(theRep,theObj,newRep = cast(ValRep) IOAalloc(size));
    
    /* Initialize the structual part of the repetition. */
    newRep->Proto = LongRepPTValue;
    if (IOAMinAge!=0) newRep->GCAttr = IOAMinAge;
    newRep->LowBorder = 1;
    newRep->HighBorder = range;

    /* Copy the body part of the repetition. */
    for (i = 0; i < range; ++i){
      newRep->Body[i] = theRep->Body[i+low-theRep->LowBorder];
    } 
        
    AssignReference((long *)theObj + offset, cast(Item) newRep);

    Ck(newRep); Ck(theRep); Ck(theObj);

}

ParamRepObjOffLowHigh(CopySVR8)
{
    DeclReference1(struct ValRep *, newRep);
    register long i, size, range;
    
    GCable_Entry();

    FetchRepObjOffLowHigh();
   
    DEBUG_CODE(NumCopySVR8++);
    Ck(theObj); Ck(theRep);

    /* Copy a slice of a Value Repetition. */
    
    /* Check that low and high are usable. */
    if ( (low < theRep->LowBorder) /* || (theRep->HighBorder < low) */ ) 
      BetaError(RepLowRangeErr, cast(Object)theObj);
    if ( /* (high < theRep->LowBorder) || */ (theRep->HighBorder < high) ) 
       BetaError(RepHighRangeErr, cast(Object)theObj);
    
    /* Calculate the range of the new repetition. */
    range =  (high - low) + 1;
    if (range < 0) range = 0;

    size = DoubleRepSize(range);

    /* LVRA missing */
    
    Protect2(theRep,theObj,newRep = cast(ValRep) IOAalloc(size));
    
    /* Initialize the structual part of the repetition. */
    newRep->Proto = DoubleRepPTValue;
    if (IOAMinAge!=0) newRep->GCAttr = IOAMinAge;
    newRep->LowBorder = 1;
    newRep->HighBorder = range;

    /* Copy the body part of the repetition. */
    { double *newBody= (double *)newRep->Body;
      double *oldBody= (double *)((unsigned)theRep->Body+8*(low-theRep->LowBorder));
      for (i=0; i<range; ++i){
	*(double *)((unsigned)newBody+8*i)=*(double *)((unsigned)oldBody+8*i);
      }
    }
        
    AssignReference((long *)theObj + offset, cast(Item) newRep);

    Ck(newRep); Ck(theRep); Ck(theObj);

}

ParamORepObjOffLowHigh(CopySVRI)
{
    DeclReference1(struct ObjectRep *, newRep);
    register long i, size, range;
    
    GCable_Entry();

    FetchORepObjOffLowHigh();
   
    DEBUG_CODE(NumCopySVRI++);
    Ck(theObj); Ck(theRep);

    /* Copy a slice of an Object Repetition. */
    
    /* Check that low and high are usable. */
    if ( (low < theRep->LowBorder) /* || (theRep->HighBorder < low) */ ) 
      BetaError(RepLowRangeErr, cast(Object)theObj);
    if ( /* (high < theRep->LowBorder) || */ (theRep->HighBorder < high) ) 
       BetaError(RepHighRangeErr, cast(Object)theObj);
    
    /* Calculate the range of the new repetition. */
    range =  (high - low) + 1;
    if (range < 0) range = 0;

    size = DynObjectRepSize(range);

    Protect2(theRep,theObj,newRep = cast(ObjectRep) IOAalloc(size));
    
    /* Initialize the structual part of the repetition. */
    newRep->Proto = DynItemRepPTValue;
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

    AssignReference((long *)theObj + offset, cast(Item) newRep);

    Ck(newRep); Ck(theRep); Ck(theObj);

}

ParamORepObjOffLowHigh(CopySVRC)
{
    DeclReference1(struct ObjectRep *, newRep);
    register long i, size, range;
    
    GCable_Entry();

    FetchORepObjOffLowHigh();
  
    DEBUG_CODE(NumCopySVRC++);
    Ck(theObj); Ck(theRep);

    /* Copy a slice of an Object Repetition. */
    
    /* Check that low and high are usable. */
    if ( (low < theRep->LowBorder) /* || (theRep->HighBorder < low) */ ) 
      BetaError(RepLowRangeErr, cast(Object)theObj);
    if ( /* (high < theRep->LowBorder) || */ (theRep->HighBorder < high) ) 
       BetaError(RepHighRangeErr, cast(Object)theObj);
    
    /* Calculate the range of the new repetition. */
    range =  (high - low) + 1;
    if (range < 0) range = 0;

    size = DynObjectRepSize(range);

    Protect2(theRep,theObj,newRep = cast(ObjectRep) IOAalloc(size));
    
    /* Initialize the structual part of the repetition. */
    newRep->Proto = DynCompRepPTValue;
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

    AssignReference((long *)theObj + offset, cast(Item) newRep);

    Ck(newRep); Ck(theRep); Ck(theObj);

}


