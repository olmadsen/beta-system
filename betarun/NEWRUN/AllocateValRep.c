/*
 * BETA C RUNTIME SYSTEM, Copyright (C) 1992-94 Mjolner Informatics Aps.
 * by Peter Andersen and Tommy Thorn.
 */

#include "beta.h"
#include "crun.h"

void AlloVR1(unsigned offset /* in bytes */, 
	     int range, 
	     struct Object* theObj, 
	     long *SP)
{
    struct ValRep *theRep=0;
    register unsigned size;

    DEBUG_CODE(NumAlloVR1++);

    if (range < 0) range = 0;

    Ck(theObj);
    size = ByteRepSize(range);

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

    push(theObj);
    if (size>IOAMAXSIZE){
      DEBUG_AOA(fprintf(output, "AlloVR1 allocates in AOA\n"));
      theRep = (struct ValRep *)AOAcalloc(size, SP);
      DEBUG_AOA(if (!theRep) fprintf(output, "AOAcalloc failed\n"));
    }
    if (!theRep) {
      theRep = (struct ValRep *)IOAalloc(size, SP);
      theRep->GCAttr = 1;
    }
    pop(theObj);
  
    theRep->Proto = ByteRepPTValue;
    /* theRep->GCAttr set above if in IOA */
    theRep->LowBorder = 1;
    theRep->HighBorder = range;
    
    AssignReference((long *)((char *)theObj + offset), (struct Item *)theRep);

    Ck(theObj);

}

void AlloVR2(unsigned offset /* in bytes */, 
	     int range, 
	     struct Object* theObj, 
	     long *SP)
{
    struct ValRep *theRep=0;
    register unsigned size;

    DEBUG_CODE(NumAlloVR2++);
    Ck(theObj);

    if (range < 0) range = 0;

    size = ShortRepSize(range);

    if (range > LARGE_REP_SIZE) {
	theRep = (struct ValRep *)LVRACAlloc(ShortRepPTValue, range);
	if (theRep) {
	    DEBUG_CODE(Claim(theRep->HighBorder==range&&theRep->LowBorder==1, 
			     "AlloVR2: lvra structure ok"));
	    /* Make the LVRA-cycle: theCell -> theRep.GCAttr */
	    theRep->GCAttr = (long) ((char *) theObj + offset);
	    *(struct ValRep **)((char *)theObj + offset) = theRep;	   
	    return;
	}
    }

    push(theObj);
    if (size>IOAMAXSIZE){
      DEBUG_AOA(fprintf(output, "AlloVR2 allocates in AOA\n"));
      theRep = (struct ValRep *)AOAcalloc(size, SP);
      DEBUG_AOA(if (!theRep) fprintf(output, "AOAcalloc failed\n"));
    }
    if (!theRep) {
      theRep = (struct ValRep *)IOAalloc(size, SP);
      theRep->GCAttr = 1;
    }
    pop(theObj);

    theRep->Proto = ShortRepPTValue;
    /* theRep->GCAttr set above if in IOA */
    theRep->LowBorder = 1;
    theRep->HighBorder = range;
    
    AssignReference((long *)((char *)theObj + offset), (struct Item *)theRep);

    Ck(theObj);
}

void AlloVR4(unsigned offset /* in bytes */, 
	     int range, 
	     struct Object* theObj, 
	     long *SP)
{
    struct ValRep *theRep=0;
    register unsigned size;

    DEBUG_CODE(NumAlloVR4++);
    Ck(theObj);

    if (range < 0) range = 0;

    size = LongRepSize(range);

    if (range > LARGE_REP_SIZE) {
	theRep = (struct ValRep *)LVRACAlloc(LongRepPTValue, range);
	if (theRep) {
	    DEBUG_CODE(Claim(theRep->HighBorder==range&&theRep->LowBorder==1, 
			     "AlloVR4: lvra structure ok"));
	    /* Make the LVRA-cycle: theCell -> theRep.GCAttr */
	    theRep->GCAttr = (long) ((char *) theObj + offset);
	    *(struct ValRep **)((char *)theObj + offset) = theRep;
	    return;
	}
    }

    push(theObj);
    if (size>IOAMAXSIZE){
      DEBUG_AOA(fprintf(output, "AlloVR4 allocates in AOA\n"));
      theRep = (struct ValRep *)AOAcalloc(size, SP);
      DEBUG_AOA(if (!theRep) fprintf(output, "AOAcalloc failed\n"));
    }
    if (!theRep) {
      theRep = (struct ValRep *)IOAalloc(size, SP);
      theRep->GCAttr = 1;
    }
    pop(theObj);
    
    theRep->Proto = LongRepPTValue;
    /* theRep->GCAttr set above if in IOA */
    theRep->LowBorder = 1;
    theRep->HighBorder = range;

    AssignReference((long *)((char *)theObj + offset), (struct Item *)theRep);

    Ck(theObj);
}


void AlloVR8(unsigned offset /* in bytes */, 
	     int range, 
	     struct Object* theObj, 
	     long *SP)
{
    struct ValRep *theRep=0;
    register unsigned size;

    DEBUG_CODE(NumAlloVR8++);
    Ck(theObj);

    if (range < 0) range = 0;

    size = DoubleRepSize(range);

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

    push(theObj);
    if (size>IOAMAXSIZE){
      DEBUG_AOA(fprintf(output, "AlloVR8 allocates in AOA\n"));
      theRep = (struct ValRep *)AOAcalloc(size, SP);
      DEBUG_AOA(if (!theRep) fprintf(output, "AOAcalloc failed\n"));
    }
    if (!theRep) {
      theRep = (struct ValRep *)IOAalloc(size, SP);
      theRep->GCAttr = 1;
    }
    pop(theObj);

    theRep->Proto = DoubleRepPTValue;
    /* theRep->GCAttr set above if in IOA */
    theRep->LowBorder = 1;
    theRep->HighBorder = range;

    AssignReference((long *)((char *)theObj + offset), (struct Item *)theRep);

    Ck(theObj);
}
