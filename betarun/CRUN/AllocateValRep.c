/*
 * BETA C RUNTIME SYSTEM, Copyright (C) 1990,91,92 Mjolner Informatics Aps.
 * Mod: $RCSfile: AllocateValRep.c,v $, rel: %R%, date: $Date: 1992-08-27 15:38:14 $, SID: $Revision: 1.9 $
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

ref(ValRep) CAlloVR1(ref(Object) theObj,
		     unsigned offset, /* i bytes */
		     unsigned range
		     )
{
    DeclReference1(struct ValRep *theRep);
    register unsigned Size;

    GCable_Entry();

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
	    return theRep;
	}
    }

  
    theRep = cast(ValRep) IOAcalloc(Size);

    ForceVolatileRef(theObj);
    Ck(theObj);
  
    theRep->Proto = ByteRepPTValue;
    theRep->GCAttr = 1;
    theRep->LowBorder = 1;
    theRep->HighBorder = range;
    
    AssignReference((long *)((char *)theObj + offset), cast(Item) theRep);
    return theRep;
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
    DeclReference1(struct ValRep *theRep);
    register unsigned Size;

    GCable_Entry();

    if (range < 0) range = 0;

    Size = WordRepSize(range);

    if (range > LARGE_REP_SIZE) {
	theRep = cast(ValRep) LVRAWordAlloc(range);
	if (theRep) {
	    /* Make the LVRA-cycle: theCell -> theRep.GCAttr */
	    theRep->GCAttr = (int) ((char *) theObj + offset);
	    *casthandle(ValRep)((char *)theObj + offset) = theRep;
	    int_clear((char*)theRep->Body, Size - headsize(ValRep));
	    return theRep;
	}
    }

    theRep = cast(ValRep) IOAcalloc(Size);

    ForceVolatileRef(theObj);
    Ck(theObj);

    theRep->Proto = WordRepPTValue;
    theRep->GCAttr = 1;
    theRep->LowBorder = 1;
    theRep->HighBorder = range;
    
    AssignReference((long *)((char *)theObj + offset), cast(Item) theRep);
    return theRep;
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
    DeclReference1(struct ValRep *theRep);
    register unsigned Size;

    GCable_Entry();

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
	    return theRep;
	}
    }

    theRep = cast(ValRep) IOAcalloc(Size);

    ForceVolatileRef(theObj);
    Ck(theObj);
    
    theRep->Proto = ValRepPTValue;
    theRep->GCAttr = 1;
    theRep->LowBorder = 1;
    theRep->HighBorder = range;


    AssignReference((long *)((char *)theObj + offset), cast(Item) theRep);

    return theRep;
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
    DeclReference1(struct ValRep *theRep);
    register unsigned Size;

    GCable_Entry();

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
	    return theRep;
	}
    }

    theRep = cast(ValRep) IOAcalloc(Size);

    ForceVolatileRef(theObj);
    Ck(theObj);

    theRep->Proto = DoubleRepPTValue;
    theRep->GCAttr = 1;
    theRep->LowBorder = 1;
    theRep->HighBorder = range;

    AssignReference((long *)((char *)theObj + offset), cast(Item) theRep);
    return theRep;
}
