/*
 * BETA C RUNTIME SYSTEM, Copyright (C) Aarhus University
 * by Peter Andersen and Tommy Thorn.
 */

#include "beta.h"
#include "crun.h"

void AlloVR1(unsigned offset /* in bytes */, 
	     int range, 
	     Object* theObj, 
	     long *SP)
{
    ValRep *theRep=0;
    register unsigned size;

    DEBUG_CODE(NumAlloVR1++);

    if (range < 0) range = 0;

    Ck(theObj);
    size = ByteRepSize(range);

    do {
      if (range > LARGE_REP_SIZE || size>IOAMAXSIZE) {
	theRep = (ValRep *)LVRACAlloc(ByteRepPTValue, range);
	if (theRep) {
	  *(ValRep **)((char *)theObj + offset) = theRep;
	  return;
	}
      }
      
      push(theObj);
      theRep = (ValRep *)IOATryAlloc(size, SP);
      if (theRep && IOAMinAge!=0) theRep->GCAttr = IOAMinAge;
      pop(theObj);
    } while (!theRep);
  
    SETPROTO(theRep, ByteRepPTValue);
    /* theRep->GCAttr set above if in IOA */
    theRep->LowBorder = 1;
    theRep->HighBorder = range;
    
    AssignReference((long *)((char *)theObj + offset), (Item *)theRep);

    Ck(theObj);

}

void AlloVR2(unsigned offset /* in bytes */, 
	     int range, 
	     Object* theObj, 
	     long *SP)
{
    ValRep *theRep=0;
    register unsigned size;

    DEBUG_CODE(NumAlloVR2++);
    Ck(theObj);

    if (range < 0) range = 0;

    size = ShortRepSize(range);

    do {
      if (range > LARGE_REP_SIZE || size>IOAMAXSIZE) {
	theRep = (ValRep *)LVRACAlloc(ShortRepPTValue, range);
	if (theRep) {
	  *(ValRep **)((char *)theObj + offset) = theRep;	   
	  return;
	}
      }
      
      push(theObj);
      theRep = (ValRep *)IOATryAlloc(size, SP);
      if (theRep && IOAMinAge!=0) theRep->GCAttr = IOAMinAge;
      pop(theObj);
    } while (!theRep);

    SETPROTO(theRep, ShortRepPTValue);
    /* theRep->GCAttr set above if in IOA */
    theRep->LowBorder = 1;
    theRep->HighBorder = range;
    
    AssignReference((long *)((char *)theObj + offset), (Item *)theRep);

    Ck(theObj);
}

void AlloVR4(unsigned offset /* in bytes */, 
	     int range, 
	     Object* theObj, 
	     long *SP)
{
    ValRep *theRep=0;
    register unsigned size;

    DEBUG_CODE(NumAlloVR4++);
    Ck(theObj);

    if (range < 0) range = 0;

    size = LongRepSize(range);

    do {
      if (range > LARGE_REP_SIZE || size>IOAMAXSIZE) {
	theRep = (ValRep *)LVRACAlloc(LongRepPTValue, range);
	if (theRep) {
	  *(ValRep **)((char *)theObj + offset) = theRep;
	  return;
	}
      }
      
      push(theObj);
      theRep = (ValRep *)IOATryAlloc(size, SP);
      if (theRep && IOAMinAge!=0) theRep->GCAttr = IOAMinAge;
      pop(theObj);
    } while (!theRep);

    
    SETPROTO(theRep, LongRepPTValue);
    /* theRep->GCAttr set above if in IOA */
    theRep->LowBorder = 1;
    theRep->HighBorder = range;

    AssignReference((long *)((char *)theObj + offset), (Item *)theRep);

    Ck(theObj);
}


void AlloVR8(unsigned offset /* in bytes */, 
	     int range, 
	     Object* theObj, 
	     long *SP)
{
    ValRep *theRep=0;
    register unsigned size;

    DEBUG_CODE(NumAlloVR8++);
    Ck(theObj);

    if (range < 0) range = 0;

    size = DoubleRepSize(range);

    do {
      if (range > LARGE_REP_SIZE) {
	theRep = (ValRep *)LVRACAlloc(DoubleRepPTValue, range);
	if (theRep) {
	  *(ValRep **)((char *)theObj + offset) = theRep;
	  return;
	}
      }
      
      push(theObj);
      theRep = (ValRep *)IOATryAlloc(size, SP);
      if (theRep && IOAMinAge!=0) theRep->GCAttr = IOAMinAge;
      pop(theObj);
    } while (!theRep);


    SETPROTO(theRep, DoubleRepPTValue);
    /* theRep->GCAttr set above if in IOA */
    theRep->LowBorder = 1;
    theRep->HighBorder = range;

    AssignReference((long *)((char *)theObj + offset), (Item *)theRep);

    Ck(theObj);
}
