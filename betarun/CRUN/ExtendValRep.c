/*
 * BETA C RUNTIME SYSTEM, Copyright (C) 1990,91,92 Mjolner Informatics Aps.
 * Mod: $Id: ExtendValRep.c,v 1.11 1992-09-07 15:38:40 beta Exp $
 * by Peter Andersen and Tommy Thorn.
 */

#define GCable_Module

#ifdef hppa
/* to keep Gcc's grappy little hand off this */
register long _dummyx asm("r16");
#endif

#include "beta.h"
#include "crun.h"

asmlabel(ExtVR, "
	ba	_CExtVR
	mov	%l7, %o2
");

#ifdef hppa
#  define CExtVR ExtVR
#endif

void CExtVR(ref(Object) theObj,
	    unsigned offset, /* in longs */
	    long add /* What to extend the range with */
	    )
{
    DeclReference1(struct ValRep *, theRep);
    DeclReference2(struct ValRep *, newRep);
    long newRange; /* Range of new repetition */
    long copyRange; /* Range to copy from old rep */
    int i;
    
    GCable_Entry();

#ifdef hppa
    add = (long) getR2Reg();
#endif

    Ck(theObj);
    theRep = *casthandle(ValRep) ((long *) theObj + offset);
    newRange = theRep->HighBorder + add; /* Range of new repetition */
    
    if (newRange < 0) newRange = 0;
    copyRange = DispatchValRepBodySize(theRep->Proto, (add < 0) ? newRange : theRep->HighBorder) >> 2;

#ifdef LVR_Area
    if (newRange > LARGE_REP_SIZE) newRep = LVRAAlloc(theRep->Proto, newRange);
    if (newRep) {
      /* Make the LVRA-cycle: theCell -> theRep.GCAttr */
      newRep->GCAttr = (int) ((long *) theObj + offset);
      *casthandle(ValRep) ((long *) theObj + offset) = newRep;
      int_clear((char*)newRep->Body, newRange*4);
      for (i = 0; i < copyRange; ++i)
	newRep->Body[i] = theRep->Body[i];
      return;
    }
#endif
    
    /* Allocate and nullify new repetition: There is a little overhead here;
     * only extension needs to be nullified
     */

    Protect2(theObj, theRep,
	     newRep = cast(ValRep) 
	                  IOAcalloc(DispatchValRepSize(theRep->Proto, newRange)));

    Ck(theRep);

    /* Assign structural part of new repetition */
    newRep->Proto = theRep->Proto;
    newRep->GCAttr = 1;
    newRep->LowBorder = theRep->LowBorder;
    newRep->HighBorder = newRange;
    
    /* Assign into theObj */
    AssignReference((long *) theObj + offset, cast(Item) newRep);
    
    /* Copy contents of old rep to new rep */
    for (i = 0; i < copyRange; ++i)
      newRep->Body[i] = theRep->Body[i];
}

