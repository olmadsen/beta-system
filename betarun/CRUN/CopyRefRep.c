/*
 * BETA C RUNTIME SYSTEM, Copyright (C) 1992-94 Mjolner Informatics Aps.
 * by Peter Andersen and Tommy Thorn.
 */

#define GCable_Module

#include "beta.h"
#include "crun.h"

ParamRepObjOff(CopyRR)
{
    DeclReference1(struct RefRep *, newRep);
    register unsigned range, i;
    
    GCable_Entry();
    FetchRepObjOff();
    
    DEBUG_CODE(NumCopyRR++);

    Ck(theRep); Ck(theObj);
    newRep = NULL;
    
    range = theRep->HighBorder;

    Protect2(theObj, theRep,
	     newRep = cast(RefRep) IOAalloc(RefRepSize(range)));
    

    newRep->Proto = theRep->Proto;
    if (IOAMinAge!=0) newRep->GCAttr = IOAMinAge;
    newRep->LowBorder = 1;
    newRep->HighBorder = range;
    
    /* Copy theRep to newRep */
    for (i = 0; i < range; ++i)
      newRep->Body[i] = theRep->Body[i];	/* Beautiful! */
    
    AssignReference((long *)theObj + offset, cast(Item) newRep);

    Ck(newRep); Ck(theRep); Ck(theObj);
}

