/*
 * BETA C RUNTIME SYSTEM, Copyright (C) 1992-94 Mjolner Informatics Aps.
 * by Peter Andersen and Tommy Thorn.
 */

#include "beta.h"
#include "crun.h"

void AlloVR1(struct Object* theObj, 
	     unsigned offset /* in bytes */, 
	     int range, 
	     long *SP)
{
    struct ValRep *theRep;
    register unsigned Size;

    DEBUG_CODE(NumAlloVR1++);

    if (range < 0) range = 0;

    Ck(theObj);
    Size = ByteRepSize(range);

    if (range > LARGE_REP_SIZE) {
	theRep = (struct ValRep *)LVRACAlloc(ByteRepPTValue, range);
	if (theRep) {
	    DEBUG_CODE(Claim(theRep->HighBorder==range&&theRep->LowBorder==1, 
			     "AlloVR1: lvra structure ok"));
	    /* Make the LVRA-cycle: theCell -> theRep.GCAttr */
	    theRep->GCAttr = (long) ((char *) theObj + offset);
	    *(struct ValRep **)((char *)theObj + offset) = theRep;
	    return;
	}
    }

    Protect(theObj, theRep = (struct ValRep *)IOAcalloc(Size, SP));
    Ck(theObj);
  
    theRep->Proto = ByteRepPTValue;
    theRep->GCAttr = 1;
    theRep->LowBorder = 1;
    theRep->HighBorder = range;
    
    AssignReference((long *)((char *)theObj + offset), (struct Item *)theRep);
}

void AlloVR2(struct Object* theObj, 
	     unsigned offset /* in bytes */,
	     int range, 
	     long *SP)
{
    struct ValRep *theRep;
    register unsigned Size;

    DEBUG_CODE(NumAlloVR2++);

    if (range < 0) range = 0;

    Size = WordRepSize(range);

    if (range > LARGE_REP_SIZE) {
	theRep = (struct ValRep *)LVRACAlloc(WordRepPTValue, range);
	if (theRep) {
	    DEBUG_CODE(Claim(theRep->HighBorder==range&&theRep->LowBorder==1, 
			     "AlloVR2: lvra structure ok"));
	    /* Make the LVRA-cycle: theCell -> theRep.GCAttr */
	    theRep->GCAttr = (long) ((char *) theObj + offset);
	    *(struct ValRep **)((char *)theObj + offset) = theRep;	   
	    return;
	}
    }

    Protect(theObj, theRep = (struct ValRep *)IOAcalloc(Size, SP));
    Ck(theObj);

    theRep->Proto = WordRepPTValue;
    theRep->GCAttr = 1;
    theRep->LowBorder = 1;
    theRep->HighBorder = range;
    
    AssignReference((long *)((char *)theObj + offset), (struct Item *)theRep);
}

void AlloVR4(struct Object* theObj,
	     unsigned offset /* in bytes */,
	     int range, 
	     long *SP)
{
    struct ValRep *theRep;
    register unsigned Size;

    DEBUG_CODE(NumAlloVR4++);

    if (range < 0) range = 0;

    Size = ValRepSize(range);

    if (range > LARGE_REP_SIZE) {
	theRep = (struct ValRep *)LVRACAlloc(ValRepPTValue, range);
	if (theRep) {
	    DEBUG_CODE(Claim(theRep->HighBorder==range&&theRep->LowBorder==1, 
			     "AlloVR4: lvra structure ok"));
	    /* Make the LVRA-cycle: theCell -> theRep.GCAttr */
	    theRep->GCAttr = (long) ((char *) theObj + offset);
	    *(struct ValRep **)((char *)theObj + offset) = theRep;
	    return;
	}
    }

    Protect(theObj, theRep = (struct ValRep *)IOAcalloc(Size, SP));
    Ck(theObj);
    
    theRep->Proto = ValRepPTValue;
    theRep->GCAttr = 1;
    theRep->LowBorder = 1;
    theRep->HighBorder = range;

    AssignReference((long *)((char *)theObj + offset), (struct Item *)theRep);
}


void AlloVR8(struct Object* theObj,
	     unsigned offset /* in bytes */, 
	     int range, 
	     long *SP)
{
    struct ValRep *theRep;
    register unsigned Size;

    DEBUG_CODE(NumAlloVR8++);

    if (range < 0) range = 0;

    Size = DoubleRepSize(range);

    if (range > LARGE_REP_SIZE) {
	theRep = (struct ValRep *)LVRACAlloc(DoubleRepPTValue, range);
	if (theRep) {
	  DEBUG_CODE(Claim(theRep->HighBorder==range&&theRep->LowBorder==1, 
			    "AlloVR8: lvra structure ok"));
	   /* Make the LVRA-cycle: theCell -> theRep.GCAttr */
	   theRep->GCAttr = (long) ((char *) theObj + offset);
	   *(struct ValRep **)((char *)theObj + offset) = theRep;
	    return;
	}
    }

    Protect(theObj, theRep = (struct ValRep *)IOAcalloc(Size, SP));
    Ck(theObj);

    theRep->Proto = DoubleRepPTValue;
    theRep->GCAttr = 1;
    theRep->LowBorder = 1;
    theRep->HighBorder = range;

    AssignReference((long *)((char *)theObj + offset), (struct Item *)theRep);
}
