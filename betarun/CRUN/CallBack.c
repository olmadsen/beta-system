/*
 * BETA C RUNTIME SYSTEM, Copyright (C) 1990,91,92 Mjolner Informatics Aps.
 * Mod: $RCSfile: CallBack.c,v $, rel: %R%, date: $Date: 1992-06-15 15:25:18 $, SID: $Revision: 1.7 $
 * by Peter Andersen and Tommy Thorn.
 */

#include "beta.h"
#include "crun.h"

int HandleCallBack();

asmlabel(CopyCProcPar, "
	ba	_CCopyCProcPar
	mov	%i0, %o1
");

void *CCopyCProcPar(ref(Structure) theStruct, ref(Object) theObj)
{
    ref(CallBackEntry) theCBStruct = CBFATop;

    /* Find a free entry in the Call Back Functions Area.		*/
    /* This area is defined by [ CBFA <= CBFATop <= CBFALimit ].	*/

    if (theCBStruct+1 > CBFALimit){
      CBFArelloc();
      return CCopyCProcPar(theStruct, theObj);
    }

    CBFATop++;
    CBFATop->theStruct = theStruct;
    CBFATop->mov_o7_g1 = MOV_O7_G1;
    MK_CALL(&CBFATop->call_HandleCallBack, HandleCallBack);
    CBFATop->nop       = NOP;
    return (void *)&CBFATop->mov_o7_g1;
}

extern int HandleCallBack() asm("HandleCallBack");

/* HandleCallBack is called from a CallBackEntry, setup like
   above. This means that the real return address is in %g1
   and our %i7 pointes to the call instruction in the
   CallBackEntry. */

int HandleCallBack(int i0, int i1, int i2, int i3,
		    int i4, int i5)
{
    register long		 g1	       asm("%g1");
    register ref(CallBackFrame)  callBackFrame asm("%l5");
    register long              * nextCompBlock asm("%l6");
    register long                level         asm("%l7");
    ref(Item) 		         theObj;

    ref(CallBackEntry) cb = 0;
    cb = cast(CallBackEntry)
      ((char *) retAddress - ((char *)&cb->call_HandleCallBack - (char *)cb));
    retAddress = g1;

    callBackFrame = 0;
    nextCompBlock = 0;
    level         = 0;

    theObj = AllocateItem(cb->theStruct->iProto, cb->theStruct->iOrigin);
    return theObj->Proto->CallBackRoutine(theObj, i0, i1, i2, i3, i4);
}
