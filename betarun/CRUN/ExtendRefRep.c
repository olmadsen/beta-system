/*
 * BETA C RUNTIME SYSTEM, Copyright (C) Aarhus University
 * by Peter Andersen and Tommy Thorn.
 */

#ifdef hppa
register long _dummyx __asm__("r16");
#endif

#include "beta.h"
#include "crun.h"

ParamObjOffRange(ExtRR)
{
    unsigned long size;
    long add = range;
    long newRange, copyRange, i;

    DeclReference1(RefRep *, theRep);
    DeclReference2(RefRep *, newRep);
    
    FetchObjOffRange();

    DEBUG_CODE(NumExtRR++);

    Ck(theObj);
    
    newRep=NULL;
    theRep = *(RefRep **) ((long *) theObj + offset);
    newRange = theRep->HighBorder + add;
    copyRange = (add < 0) ? newRange : theRep->HighBorder;
    
    if (newRange < 0) newRange = 0;

    push(theObj);
    push(theRep);
    size = RefRepSize(newRange);
    do {
      if (newRange>LARGE_REP_SIZE || size>IOAMAXSIZE){
	DEBUG_AOA(fprintf(output, "ExtRR allocates in AOA(newRange=%d)\n", (int)newRange));
	newRep = (RefRep *)AOAcalloc(size);
	DEBUG_AOA(if (!newRep) fprintf(output, "AOAcalloc failed\n"));
      }
      if (!newRep) {
	newRep = (RefRep *)IOATryAlloc(size);
	if (newRep && IOAMinAge!=0) newRep->GCAttr = IOAMinAge;
      }
    } while (!newRep);
    pop(theRep);
    pop(theObj);
    
    SETPROTO(newRep,RefRepPTValue);
    /* newRep->GCAttr set above if in IOA */
    newRep->LowBorder = 1;
    newRep->HighBorder = newRange;
    
    for (i = 0; i < copyRange; ++i){
      AssignReference(&newRep->Body[i], (Item*)theRep->Body[i]);
    }
   
    AssignReference((long *)theObj + offset, (Item *) newRep);

    Ck(theRep); Ck(newRep); Ck(theObj);

}

