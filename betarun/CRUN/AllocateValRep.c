/*
 * BETA C RUNTIME SYSTEM, Copyright (C) 1990,91,92 Mjolner Informatics Aps.
 * Mod: $Id: AllocateValRep.c,v 1.19 1992-11-06 16:55:03 beta Exp $
 * by Peter Andersen and Tommy Thorn.
 */

#define GCable_Module
#include "beta.h"
#include "crun.h"

asmlabel(AlloVR1, "
	mov %i0, %o0
        mov %l0, %o1
	ba _CAlloVR1
	mov %l1, %o2
");

#ifdef hppa
#define CAlloVR1 AlloVR1
#define CAlloVR2 AlloVR2
#define CAlloVR4 AlloVR4
#define CAlloVR8 AlloVR8
#endif

ref(ValRep) CAlloVR1(ref(Object) theObj,
		     unsigned offset, /* i bytes */
		     unsigned range
		     )
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

    Ck(theObj);
    Size = ByteRepSize(range);

#ifdef LVR_Area
    if (range > LARGE_REP_SIZE) {
	theRep = cast(ValRep) LVRACAlloc(ByteRepPTValue, range);
	if (theRep) {
	    Claim(theRep->HighBorder==range&&theRep->LowBorder==1, 
		  "AlloVR1: lvra structure ok");
	    /* Make the LVRA-cycle: theCell -> theRep.GCAttr */
	    theRep->GCAttr = (long) ((char *) theObj + offset);
	    *casthandle(ValRep)((char *)theObj + offset) = theRep;
	    
	    RETURN(theRep);
	}
    }
#endif

  
    Protect(theObj, theRep = cast(ValRep) IOAcalloc(Size));

    Ck(theObj);
  
    theRep->Proto = ByteRepPTValue;
    theRep->GCAttr = 1;
    theRep->LowBorder = 1;
    theRep->HighBorder = range;
    
    AssignReference((long *)((char *)theObj + offset), cast(Item) theRep);
    RETURN(theRep);
}

asmlabel(AlloVR2, "
	mov %i0, %o0
        mov %l0, %o1
	ba _CAlloVR2
	mov %l1, %o2
");

ref(ValRep) CAlloVR2(ref(Object) theObj,
		     unsigned offset, /* in bytes */
		     unsigned range
		     )
{
    DeclReference1(struct ValRep *, theRep);
    register unsigned Size;

    GCable_Entry();

#ifdef hppa
  range = (unsigned) getD1Reg();
  theObj = cast(Object) getThisReg();
  offset = (unsigned) getD0Reg();
#endif

    if (range < 0) range = 0;

    Size = WordRepSize(range);

#ifdef LVR_Area
    if (range > LARGE_REP_SIZE) {
	theRep = cast(ValRep) LVRACAlloc(WordRepPTValue, range);
	if (theRep) {
	    Claim(theRep->HighBorder==range&&theRep->LowBorder==1, 
		  "AlloVR2: lvra structure ok");
	    /* Make the LVRA-cycle: theCell -> theRep.GCAttr */
	    theRep->GCAttr = (long) ((char *) theObj + offset);
	    *casthandle(ValRep)((char *)theObj + offset) = theRep;
	    RETURN(theRep);
	}
    }
#endif

    Protect(theObj, theRep = cast(ValRep) IOAcalloc(Size));
    Ck(theObj);

    theRep->Proto = WordRepPTValue;
    theRep->GCAttr = 1;
    theRep->LowBorder = 1;
    theRep->HighBorder = range;
    
    AssignReference((long *)((char *)theObj + offset), cast(Item) theRep);
    RETURN(theRep);
}

asmlabel(AlloVR4, "
	mov %i0, %o0
        mov %l0, %o1
	ba _CAlloVR4
	mov %l1, %o2
");

ref(ValRep) CAlloVR4(ref(Object) theObj,
			   unsigned offset, /* i bytes */
			   unsigned range
			   )
{
    DeclReference1(struct ValRep *, theRep);
    register unsigned Size;

    GCable_Entry();

#ifdef hppa
  range = (unsigned) getD1Reg();
  theObj = cast(Object) getThisReg();
  offset = (unsigned) getD0Reg();
#endif

    if (range < 0)
      range = 0;

    Size = ValRepSize(range);

#ifdef LVR_Area
    if (range > LARGE_REP_SIZE) {
	theRep = cast(ValRep) LVRACAlloc(ValRepPTValue, range);
	if (theRep) {
	    Claim(theRep->HighBorder==range&&theRep->LowBorder==1, 
		  "AlloVR4: lvra structure ok");
	    /* Make the LVRA-cycle: theCell -> theRep.GCAttr */
	    theRep->GCAttr = (long) ((char *) theObj + offset);
	    *casthandle(ValRep)((char *)theObj + offset) = theRep;
	    RETURN(theRep);
	}
    }
#endif

    Protect(theObj, theRep = cast(ValRep) IOAcalloc(Size));
    Ck(theObj);
    
    theRep->Proto = ValRepPTValue;
    theRep->GCAttr = 1;
    theRep->LowBorder = 1;
    theRep->HighBorder = range;


    AssignReference((long *)((char *)theObj + offset), cast(Item) theRep);

    RETURN(theRep);
}


asmlabel(AlloVR8, "
	mov %i0, %o0
        mov %l0, %o1
	ba _CAlloVR8
	mov %l1, %o2
");

ref(ValRep) CAlloVR8(ref(Object) theObj,
		     unsigned offset, /* i bytes */
		     unsigned range
		     )
{
    DeclReference1(struct ValRep *, theRep);
    register unsigned Size;

    GCable_Entry();

#ifdef hppa
  range = (unsigned) getD1Reg();
  theObj = cast(Object) getThisReg();
  offset = (unsigned) getD0Reg();
#endif

    if (range < 0)
      range = 0;

    Size= DoubleRepSize(range);

#ifdef LVR_Area
    if (range > LARGE_REP_SIZE) {
	theRep = cast(ValRep) LVRACAlloc(DoubleRepPTValue, range);
	if (theRep) {
	   Claim(theRep->HighBorder==range&&theRep->LowBorder==1, 
		 "AlloVR8: lvra structure ok");
	    /* Make the LVRA-cycle: theCell -> theRep.GCAttr */
	    theRep->GCAttr = (long) ((char *) theObj + offset);
	    *casthandle(ValRep)((char *)theObj + offset) = theRep;
	    RETURN(theRep);
	}
    }
#endif

    Protect(theObj, theRep = cast(ValRep) IOAcalloc(Size));
    Ck(theObj);

    theRep->Proto = DoubleRepPTValue;
    theRep->GCAttr = 1;
    theRep->LowBorder = 1;
    theRep->HighBorder = range;

    AssignReference((long *)((char *)theObj + offset), cast(Item) theRep);
    RETURN(theRep);
}
