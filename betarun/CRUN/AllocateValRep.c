/*
 * BETA C RUNTIME SYSTEM, Copyright (C) 1990,91,92 Mjolner Informatics Aps.
<<<<<<< AllocateValRep.c
 * Mod: $Id: AllocateValRep.c,v 1.12 1992-09-03 12:55:32 beta Exp $
=======
 * Mod: $Id: AllocateValRep.c,v 1.12 1992-09-03 12:55:32 beta Exp $
>>>>>>> 1.11
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

    if (range > LARGE_REP_SIZE) {
	theRep = cast(ValRep) LVRAByteAlloc(range);
	if (theRep) {
	    /* Make the LVRA-cycle: theCell -> theRep.GCAttr */
	    theRep->GCAttr = (int) ((char *) theObj + offset);
	    *casthandle(ValRep)((char *)theObj + offset) = theRep;
	    int_clear((char*)theRep->Body, Size - headsize(ValRep));
	    RETURN(theRep);
	}
    }

  
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

    if (range > LARGE_REP_SIZE) {
	theRep = cast(ValRep) LVRAWordAlloc(range);
	if (theRep) {
	    /* Make the LVRA-cycle: theCell -> theRep.GCAttr */
	    theRep->GCAttr = (int) ((char *) theObj + offset);
	    *casthandle(ValRep)((char *)theObj + offset) = theRep;
	    int_clear((char*)theRep->Body, Size - headsize(ValRep));
	    RETURN(theRep);
	}
    }

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

    if (range > LARGE_REP_SIZE) {
	theRep = cast(ValRep) LVRAAlloc(range);
	if (theRep) {
	    /* Make the LVRA-cycle: theCell -> theRep.GCAttr */
	    theRep->GCAttr = (int) ((char *) theObj + offset);
	    *casthandle(ValRep)((char *)theObj + offset) = theRep;
	    int_clear((char*)theRep->Body, Size - headsize(ValRep));
	    RETURN(theRep);
	}
    }

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

    if (range > LARGE_REP_SIZE) {
	theRep = cast(ValRep) LVRADoubleAlloc(range);
	if (theRep) {
	    /* Make the LVRA-cycle: theCell -> theRep.GCAttr */
	    theRep->GCAttr = (int) ((char *) theObj + offset);
	    *casthandle(ValRep)((char *)theObj + offset) = theRep;
	    int_clear((char*)theRep->Body, Size - headsize(ValRep));
	    RETURN(theRep);
	}
    }

    Protect(theObj, theRep = cast(ValRep) IOAcalloc(Size));
    Ck(theObj);

    theRep->Proto = DoubleRepPTValue;
    theRep->GCAttr = 1;
    theRep->LowBorder = 1;
    theRep->HighBorder = range;

    AssignReference((long *)((char *)theObj + offset), cast(Item) theRep);
    RETURN(theRep);
}
