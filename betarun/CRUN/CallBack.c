/*
 * BETA C RUNTIME SYSTEM, Copyright (C) 1990,91,92 Mjolner Informatics Aps.
 * Mod: $RCSfile: CallBack.c,v $, rel: %R%, date: $Date: 1992-08-27 15:40:17 $, SID: $Revision: 1.18 $
 * by Peter Andersen and Tommy Thorn.
 */

#include "beta.h"
#include "crun.h"

int HandleCB();

asmlabel(CopyCPP, "
	ba	_CCopyCPP
	mov	%i0, %o1
");

void *CCopyCPP(ref(Structure) theStruct, ref(Object) theObj)
{
    /* Find a free entry in the Call Back Functions Area.		*/
    /* This area is defined by 
     * [ lastCBFABlock->entries <= CBFATop <= CBFALimit ].	
     */

    if (CBFATop+1 > CBFALimit){
      CBFArelloc();
      return CCopyCPP(theStruct, theObj);
    }

    Ck(theStruct);Ck(theObj);
    CBFATop->theStruct = theStruct;
    CBFATop->mov_o7_g1 = MOV_O7_G1;
    MK_CALL(&CBFATop->call_HandleCallBack, HandleCB);
    CBFATop->nop       = NOP;
    ++CBFATop;
    return (void *)&(CBFATop-1)->mov_o7_g1;
}

extern int HandleCB() asm("HandleCB");

/* HandleCallBack is called from a CallBackEntry, setup like
   above. This means that the real return address is in %g1
   and our %i7 pointes to the call instruction in the
   CallBackEntry. */

int HandleCB(int a1, int a2, int a3, int a4, int a5, int a6)
{
    register long		 g1	       asm("%g1");

    /* A CallBackFrame: */
    register ref(CallBackFrame)  next	       asm("%l5");
    register long              * betaTop       asm("%l6");
    register long                tmp           asm("%l7");
    
    ref(Item) 		         theObj;
    ref(CallBackEntry) cb;
    int retval;
    int (*cbr)();

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
    next    = ActiveCallBackFrame;
    betaTop = BetaStackTop;
    tmp     = 0;
    ActiveCallBackFrame = cast(CallBackFrame) StackPointer;

    theObj = CAlloI(cb->theStruct->iOrigin, cb->theStruct->iProto);

    /* Call the CallBack stub, with out first four args in %i1..%i4, and
       the rest on stack from %i5 and onwards */
    
    /* As usual, skip the first instruction */
    cbr = (int (*)()) ((int*)theObj->Proto->CallBackRoutine+1);
    retval = cbr(theObj, a1, a2, a3, a4, &a5);

    /* Pop CallBackFrame */
    ActiveCallBackFrame = next;
    BetaStackTop        = betaTop;
    
    /* Fool gcc into believing that the address of a6 is taken, thus
       making it save it on stack. */
    
    asm(""::"r" (&a6), "r" (next), "r" (betaTop), "r" (tmp)) ;
    return retval;
}
