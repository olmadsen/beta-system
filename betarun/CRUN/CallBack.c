/*
 * BETA C RUNTIME SYSTEM, Copyright (C) 1990,91,92 Mjolner Informatics Aps.
 * Mod: $Id: CallBack.c,v 1.24 1992-09-21 17:04:55 tthorn Exp $
 * by Peter Andersen and Tommy Thorn.
 */

#include "beta.h"
#include "crun.h"

int HandleCB();

#ifdef hppa
/*
 * these are used in the process of generating HP-PA machinecode. Now aren't
 * these lovely?
 */
static unsigned long mangle21(unsigned long x)
{
  unsigned long bit20, bits9_19, bits5_6, bits0_4, bits7_8;

  bit20 =     (x >> 20) & 0x0001;
  bits9_19 =  (x >> 9)  & 0x07ff;
  bits5_6 =   (x >> 7)  & 0x0003;
  bits0_4 =   (x >> 2)  & 0x001f;
  bits7_8 =       x     & 0x0003;

  return (bits0_4<<16)|(bits5_6<<14)|(bits7_8<<12)|(bits9_19<<1)|bit20;
}

static unsigned long bletch(unsigned long x)
{
  return (x << 1) & 0x03ffe;
}

void *CopyCPP(ref(Structure) theStruct, ref(Object) theObj)
{
    theObj = cast(Object) getThisReg();

    Ck(theObj);
    if (CBFATop+1 > CBFALimit) CBFArelloc();

    CBFATop->theStruct = theStruct;

    /* Construct the following code in the CBF:
     * 0 LDIL L'HandleCB, %r1
     * 1 MFSP %sr4,%r31
     * 2 LDO  R'HandleCB(%r1),%r1
     * 3 MTSP %r31,%sr0
     * 4 LDIL L'theStruct,%r28
     * 5 BE   0(%sr4,%r1)
     * 6 LDO  R'theStruct(%r28),%r28
     */
    CBFATop->code[0] = (8<<26)|(1<<21)
      |mangle21(((unsigned long)HandleCB >> 11) & 0x1fffff);
    CBFATop->code[1] = (1<<13)|(0x25<<5)|31;
    CBFATop->code[2] = (0xd<<26)|(1<<21)|(1<<16)
      |bletch((unsigned long)HandleCB & 0x7ff);
    CBFATop->code[3] = (31<<16)|(0xc1<<5);
    CBFATop->code[4] = (8<<26)|(28<<21)
      |mangle21(((unsigned long)theStruct >> 11) & 0x1fffff);
    CBFATop->code[5] = (0x38<<26)|(1<<21)|(1<<13); /* really sr4 - sic! */
    CBFATop->code[6] = (0xd<<26)|(28<<21)|(28<<16)
      |bletch((unsigned long)theStruct & 0x7ff);

    /* now flush the code from the data cache */
    asm volatile ("fdc\t0(0,%0)" : /* no out */
                  : "r" (&CBFATop->code[0]));
    asm volatile ("fdc\t0(0,%0)" : /* no out */
                  : "r" (&CBFATop->code[2]));
    asm volatile ("fdc\t0(0,%0)" : /* no out */
                  : "r" (&CBFATop->code[4]));
    asm volatile ("fdc\t0(0,%0)\n\tsync" : /* no out */
                  : "r" (&CBFATop->code[6]));

    ++CBFATop;

    /* the following C call expects the function-pointer in arg1 - sic! */
    asm("COPY %0, %%r26" : /*no out*/ : "r" (&(CBFATop-1)->code[0]) : "r26");
    return((void *)&(CBFATop-1)->code[0]);
}

#endif /* hppa */

/**************************** sparc **************************/
#ifdef sparc

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

#endif /* sparc */

/************************** snake ******************************/

#ifdef hppa

/* HandleCallBack is called from a CallBackEntry, setup like
   above. This means that %r28 points to the struct.
 */

asm("\t.EXPORT HandleCB,CODE\n"
    "HandleCB\tstw %r2,-20(%r30)\n"
    "\tldo 128(%r30),%r30\n"
    "\tstw %r3,-128(%r30)\n"
    "\tstw %r4,-124(%r30)\n"
    "\tstw %r5,-120(%r30)\n"
    "\tstw %r6,-116(%r30)\n"
    "\tstw %r7,-112(%r30)\n"
    "\tstw %r8,-108(%r30)\n"
    "\tstw %r9,-104(%r30)\n"
    "\tstw %r10,-100(%r30)\n"
    "\tstw %r11,-96(%r30)\n"
    "\tstw %r12,-92(%r30)\n"
    "\tstw %r13,-88(%r30)\n"
    "\tstw %r14,-84(%r30)\n"
    "\tstw %r15,-80(%r30)\n"
    "\tstw %r17,-72(%r30)\n"
    "\tstw %r18,-68(%r30)\n"
    "\tbl CHandleCB,%r2\n"
    "\tstw %r16,-76(%r30)\n"
    "\tldw -68(%r30),%r18\n"
    "\tldw -72(%r30),%r17\n"
    "\tldw -76(%r30),%r16\n"
    "\tldw -80(%r30),%r15\n"
    "\tldw -84(%r30),%r14\n"
    "\tldw -88(%r30),%r13\n"
    "\tldw -92(%r30),%r12\n"
    "\tldw -96(%r30),%r11\n"
    "\tldw -100(%r30),%r10\n"
    "\tldw -104(%r30),%r9\n"
    "\tldw -108(%r30),%r8\n"
    "\tldw -112(%r30),%r7\n"
    "\tldw -116(%r30),%r6\n"
    "\tldw -120(%r30),%r5\n"
    "\tldw -124(%r30),%r4\n"
    "\tldw -128(%r30),%r3\n"
    "\tldw -20-128(%r30),%r2\n"
    "\tbv %r0(%r2)\n"
    "\tldo -128(%r30),%r30\n");

int CHandleCB(int a1, int a2, int a3, int a4, int FOR)
{
    struct CallBackFrame        cbf;
    ref(Structure)              theStruct;
    int                         retval;
    DeclReference1(struct Item *, theObj);

    /* First things first, get a grib on the struct pointer */
    asm volatile ("COPY %%r28,%0" : "=r" (theStruct));

    /* Push CallBackFrame. */
    cbf.next    = ActiveCallBackFrame;
    cbf.betaTop = BetaStackTop;
    /* cbf.tmp     = (long) getSPReg();  so the GC can find it */
    ActiveCallBackFrame = &cbf;

    setIOAReg(savedIOA);
    setIOATopoffReg(savedIOATopoff);

    setCallReg(theStruct->iProto);
    setOriginReg(theStruct->iOrigin);
    theObj = AlloI();

    /* This is how the arguments will look to the callee:
     * The first 4 integer arguments are in registers 26 - 23 as always.
     * -52(sp) = pointer to the first of the rest of the args, call it 'ap'
     * (ap) = arg#4, -4(ap) = arg#5,...
     * Unfortunately this doesn't work for doubles :-(
     */
    setCallReg(theObj);
    retval = theObj->Proto->CallBackRoutine(a1, a2, a3, a4, &FOR);

    BETA_CLOBBER;

    /* Pop CallBackFrame */
    ActiveCallBackFrame = cbf.next;
    BetaStackTop        = cbf.betaTop;

    return retval;
}
#endif /* hppa */
