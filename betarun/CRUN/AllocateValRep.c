/*
 * BETA C RUNTIME SYSTEM, Copyright (C) 1992-94 Mjolner Informatics Aps.
 * by Peter Andersen and Tommy Thorn.
 */

#define GCable_Module
#include "beta.h"
#include "crun.h"

ParamThisOffRange(ref(ValRep), AlloVR1)
{
    DeclReference1(struct ValRep *, theRep);
    register unsigned Size;

    GCable_Entry();

#ifdef hppa
   /* must be the first instr. in the proc. because D1 is not kept from GCC */
  range = (unsigned) getD1Reg();
  theObj = cast(Object) getThisReg();
  offset = (unsigned) getD0Reg();
#endif

    if (range < 0) range = 0;

    DEBUG_CODE(NumAlloVR1++);

    Ck(theObj);
    Size = ByteRepSize(range);

    if (range > LARGE_REP_SIZE) {
	theRep = cast(ValRep) LVRACAlloc(ByteRepPTValue, range);
	if (theRep) {
	    DEBUG_CODE(Claim(theRep->HighBorder==range&&theRep->LowBorder==1, 
			     "AlloVR1: lvra structure ok"));
	    /* Make the LVRA-cycle: theCell -> theRep.GCAttr */
	    theRep->GCAttr = (long) ((char *) theObj + offset);
	    *casthandle(ValRep)((char *)theObj + offset) = theRep;
	    
	    RETURN(theRep);
	}
    }

    Protect(theObj, theRep = cast(ValRep) IOAalloc(Size));

    theRep->Proto = ByteRepPTValue;
    theRep->GCAttr = 1;
    theRep->LowBorder = 1;
    theRep->HighBorder = range;
    
    AssignReference((long *)((char *)theObj + offset), cast(Item) theRep);

    Ck(theObj); Ck(theRep);
    RETURN(theRep);
}

ParamThisOffRange(ref(ValRep), AlloVR2)
{
    DeclReference1(struct ValRep *, theRep);
    register unsigned Size;

    GCable_Entry();

#ifdef hppa
  range = (unsigned) getD1Reg();
  theObj = cast(Object) getThisReg();
  offset = (unsigned) getD0Reg();
#endif

    DEBUG_CODE(NumAlloVR2++);
    Ck(theObj);

    if (range < 0) range = 0;

    Size = ShortRepSize(range);

    if (range > LARGE_REP_SIZE) {
	theRep = cast(ValRep) LVRACAlloc(ShortRepPTValue, range);
	if (theRep) {
	    DEBUG_CODE(Claim(theRep->HighBorder==range&&theRep->LowBorder==1, 
			     "AlloVR2: lvra structure ok"));
	    /* Make the LVRA-cycle: theCell -> theRep.GCAttr */
	    theRep->GCAttr = (long) ((char *) theObj + offset);
	    *casthandle(ValRep)((char *)theObj + offset) = theRep;
	    RETURN(theRep);
	}
    }

    Protect(theObj, theRep = cast(ValRep) IOAalloc(Size));

    theRep->Proto = ShortRepPTValue;
    theRep->GCAttr = 1;
    theRep->LowBorder = 1;
    theRep->HighBorder = range;
    
    AssignReference((long *)((char *)theObj + offset), cast(Item) theRep);
    Ck(theObj); Ck(theRep);
    RETURN(theRep);
}

ParamThisOffRange(ref(ValRep), AlloVR4)
{
    DeclReference1(struct ValRep *, theRep);
    register unsigned Size;

    GCable_Entry();

#ifdef hppa
  range = (unsigned) getD1Reg();
  theObj = cast(Object) getThisReg();
  offset = (unsigned) getD0Reg();
#endif

    DEBUG_CODE(NumAlloVR4++);
    Ck(theObj);

    if (range < 0)
      range = 0;

    Size = LongRepSize(range);

    if (range > LARGE_REP_SIZE) {
	theRep = cast(ValRep) LVRACAlloc(LongRepPTValue, range);
	if (theRep) {
	    DEBUG_CODE(Claim(theRep->HighBorder==range&&theRep->LowBorder==1, 
			     "AlloVR4: lvra structure ok"));
	    /* Make the LVRA-cycle: theCell -> theRep.GCAttr */
	    theRep->GCAttr = (long) ((char *) theObj + offset);
	    *casthandle(ValRep)((char *)theObj + offset) = theRep;
	    RETURN(theRep);
	}
    }

    Protect(theObj, theRep = cast(ValRep) IOAalloc(Size));
    
    theRep->Proto = LongRepPTValue;
    theRep->GCAttr = 1;
    theRep->LowBorder = 1;
    theRep->HighBorder = range;

    AssignReference((long *)((char *)theObj + offset), cast(Item) theRep);
    Ck(theObj); Ck(theRep);
    RETURN(theRep);
}

ParamThisOffRange(ref(ValRep), AlloVR8)
{
    DeclReference1(struct ValRep *, theRep);
    register unsigned Size;

    GCable_Entry();

#ifdef hppa
  range = (unsigned) getD1Reg();
  theObj = cast(Object) getThisReg();
  offset = (unsigned) getD0Reg();
#endif

    DEBUG_CODE(NumAlloVR8++);
    Ck(theObj);

    if (range < 0)
      range = 0;

    Size= DoubleRepSize(range);

    if (range > LARGE_REP_SIZE) {
	theRep = cast(ValRep) LVRACAlloc(DoubleRepPTValue, range);
	if (theRep) {
	  DEBUG_CODE(Claim(theRep->HighBorder==range&&theRep->LowBorder==1, 
			    "AlloVR8: lvra structure ok"));
	   /* Make the LVRA-cycle: theCell -> theRep.GCAttr */
	   theRep->GCAttr = (long) ((char *) theObj + offset);
	   *casthandle(ValRep)((char *)theObj + offset) = theRep;
	   RETURN(theRep);
	}
    }

    Protect(theObj, theRep = cast(ValRep) IOAalloc(Size));

    theRep->Proto = DoubleRepPTValue;
    theRep->GCAttr = 1;
    theRep->LowBorder = 1;
    theRep->HighBorder = range;

    AssignReference((long *)((char *)theObj + offset), cast(Item) theRep);
    Ck(theObj); Ck(theRep);
    RETURN(theRep);
}
