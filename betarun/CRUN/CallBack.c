/*
 * BETA C RUNTIME SYSTEM, Copyright (C) 1990,91,92 Mjolner Informatics Aps.
 * Mod: $RCSfile: CallBack.c,v $, rel: %R%, date: $Date: 1992-06-29 15:01:04 $, SID: $Revision: 1.9 $
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
    /* Find a free entry in the Call Back Functions Area.		*/
    /* This area is defined by [ CBFA <= CBFATop <= CBFALimit ].	*/

    if (CBFATop+1 > CBFALimit){
      CBFArelloc();
      return CCopyCProcPar(theStruct, theObj);
    }

    CBFATop->theStruct = theStruct;
    CBFATop->mov_o7_g1 = MOV_O7_G1;
    MK_CALL(&CBFATop->call_HandleCallBack, HandleCallBack);
    CBFATop->nop       = NOP;
    ++CBFATop;
    return (void *)&(CBFATop-1)->mov_o7_g1;
}

extern int HandleCallBack() asm("HandleCallBack");

/* HandleCallBack is called from a CallBackEntry, setup like
   above. This means that the real return address is in %g1
   and our %i7 pointes to the call instruction in the
   CallBackEntry. */

int HandleCallBack(int a1, int a2, int a3, int a4, int a5, int a6)
{
    register long		 g1	       asm("%g1");
    register ref(CallBackFrame)  callBackFrame asm("%l5");
    register long              * nextCompBlock asm("%l6");
    register long                level         asm("%l7");
    ref(Item) 		         theObj;
    ref(CallBackEntry) cb;

    /* Calculate the address of the CallBackEntry. As our return
       address points to the call in the middle of the CallBackEntry,
       we subtract the offset (notice that the value of cb is not used.)
       THIS NEED TO BE DONE HERE AT FRONT AS %g1 HOLDS OUR REAL RETURN-
       ADDRESS, AND WE NEED TO RESTORE THIS VALUE BEFORE ANYTHING HAPPENS
       TO IT. (%g1 is not generally safe to use, but ok here. (I hope :^) */

    cb = cast(CallBackEntry)
      ((char *) retAddress - ((char *)&cb->call_HandleCallBack - (char *)cb));
    retAddress = g1;

    /* Push CallBackFrame. See StackLayout.doc */

    /* This is properbly wrong ?? */
    level         = 0;
    nextCompBlock = (long *) lastCompBlock;
    callBackFrame = ActiveCallBack;

    lastCompBlock = cast(ComponentBlock) StackPointer;
    ActiveCallBackFrame = StackPointer;

    theObj = AllocateItem(cb->theStruct->iProto, cb->theStruct->iOrigin);

    /* Call the CallBack stub, with out first four args in %i1..%i4, and
       the rest on stack from %i5 and onwards */
    
    return theObj->Proto->CallBackRoutine(theObj, a1, a2, a3, a4, &a5);

    /* Fool gcc into believing that the address of a6 is taken, thus
       making it save it on stack. */
    
    asm(""::"m" (&a6));
}
