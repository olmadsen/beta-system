/*
 * BETA C RUNTIME SYSTEM, Copyright (C) 1992-94 Mjolner Informatics Aps.
 * by Peter Andersen and Tommy Thorn.
 */

#define GCable_Module

#ifdef hppa
register long _dummyx __asm__("r16");
#endif

#include "beta.h"
#include "crun.h"

ParamObjOffRange(ExtRR)
{
    DeclReference1(RefRep *, theRep);
    DeclReference2(RefRep *, newRep);
    
    long add = range;
    long newRange, copyRange, i;
    
    GCable_Entry();
    FetchObjOffRange();

    DEBUG_CODE(NumExtRR++);

    Ck(theObj);
    theRep = *(RefRep **) ((long *) theObj + offset);
    newRange = theRep->HighBorder + add;
    copyRange = (add < 0) ? newRange : theRep->HighBorder;
    
    if (newRange < 0)
      newRange = 0;

    Protect2(theRep, theObj,
	     newRep = (RefRep *) IOAalloc(RefRepSize(newRange)));
   
    SETPROTO(newRep,RefRepPTValue);
    if (IOAMinAge!=0) newRep->GCAttr = IOAMinAge;
    newRep->LowBorder = 1;
    newRep->HighBorder = newRange;
    
    for (i = 0; i < copyRange; ++i)
      newRep->Body[i] = theRep->Body[i];
    
    AssignReference((long *)theObj + offset, (Item *) newRep);

    Ck(theRep); Ck(newRep); Ck(theObj);

}

