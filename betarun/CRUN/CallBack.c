/*
 * BETA C RUNTIME SYSTEM, Copyright (C) 1992-94 Mjolner Informatics Aps.
 * by Peter Oerbaek, Peter Andersen, Tommy Thorn and Kim Jensen Moeller.
 */

#include "beta.h"
#include "crun.h"

/*************************** crts ***************************/
#ifdef crts
void *CopyCPP(ref(Structure) theStruct, ref(Object) theObj)
{
  fprintf(output, "CRTS: CopyCPP NYI\n");
  fflush(output);
  return NULL;
}
#endif /* crts */

/**************************** sparc **************************/
#ifdef sparc

extern long HandleCB() asm("HandleCB");

asmlabel(CopyCPP, "
	ba	"CPREF"CopyCPP
	mov	%i0, %o1
");

void *CCopyCPP(ref(Structure) theStruct, ref(Object) theObj)
{
    /* Take the next free entry in the Call Back Functions Area.	*/
    /* This area is defined by 
     * [ lastCBFABlock->entries <= CBFATop < CBFALimit ].
     */

    if (CBFATop+1 > CBFALimit){
      CBFArelloc();
      /* return CCopyCPP(theStruct, theObj); */
    }

    Ck(theStruct);Ck(theObj);
    CBFATop->theStruct = theStruct;
    CBFATop->mov_o7_g1 = MOV_O7_G1;
    MK_CALL(&CBFATop->call_HandleCallBack, HandleCB);
    CBFATop->nop       = NOP;
    /* Flush the Instruction Cache, not nessesary I think [tthorn] */
    __asm__("iflush %0"::"r" (&CBFATop->mov_o7_g1));
    __asm__("iflush %0"::"r" (&CBFATop->call_HandleCallBack));
    __asm__("iflush %0"::"r" (&CBFATop->nop));
    ++CBFATop;
    return (void *)&(CBFATop-1)->mov_o7_g1;
}


/* HandleCallBack is called from a CallBackEntry, setup like
   above. This means that the real return address is in %g1
   and our %i7 pointes to the call instruction in the
   CallBackEntry. */

long HandleCB(long a1, long a2, long a3, long a4, long a5, long a6)
{
    register long		 g1	       asm("%g1");

    /* A CallBackFrame: */
    register ref(CallBackFrame)  next	       asm("%l5");
    register long              * betaTop       asm("%l6");
    register long                tmp           asm("%l7");
    
    ref(Item) 		         theObj;
    ref(CallBackEntry) cb;
    long retval;
    long (*cbr)();

    /* Calculate the address of the CallBackEntry. As our return
       address points to the call in the middle of the CallBackEntry,
       we subtract the offset (notice that the value of cb is not used.)
       THIS NEED TO BE DONE HERE AT FRONT AS %g1 HOLDS OUR REAL RETURN-
       ADDRESS, AND WE NEED TO RESTORE THIS VALUE BEFORE ANYTHING HAPPENS
       TO IT. (%g1 is not generally safe to use, but ok here. (I hope :^) */

    cb = cast(CallBackEntry)
      ((char *) retAddress - ((char *)&cb->call_HandleCallBack - (char *)cb));
    retAddress = g1;

    if (!cb->theStruct) { freeCallbackCalled(); return 0; }

    /* Push CallBackFrame. See StackLayout.doc */
    next    = ActiveCallBackFrame;
    betaTop = BetaStackTop;
    tmp     = 0;
    ActiveCallBackFrame = cast(CallBackFrame) StackPointer;

    theObj = CAlloI(cb->theStruct->iOrigin, 0, cb->theStruct->iProto, 0, 0);

    /* Call the CallBack stub, with out first four args in %i1..%i4, and
       the rest on stack from %i5 and onwards */
    
    /* As usual, skip the first instruction */
    cbr = (long (*)()) ((long*)theObj->Proto->CallBackRoutine+1);
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
/*
 * these are used in the process of generating HP-PA machinecode. Now aren't
 * these lovely?
 */
static inline unsigned long mangle21(unsigned long x)
{
  unsigned long bit20, bits9_19, bits5_6, bits0_4, bits7_8;

  bit20 =     (x >> 20) & 0x0001;
  bits9_19 =  (x >> 9)  & 0x07ff;
  bits5_6 =   (x >> 7)  & 0x0003;
  bits0_4 =   (x >> 2)  & 0x001f;
  bits7_8 =       x     & 0x0003;

  return (bits0_4<<16)|(bits5_6<<14)|(bits7_8<<12)|(bits9_19<<1)|bit20;
}

static inline unsigned long bletch(unsigned long x)
{
  return (x << 1) & 0x03ffe;
}

extern void HandleCB();

void *CopyCPP(ref(Structure) theStruct, ref(Object) theObj)
{   register unsigned long hcb;
    theObj = cast(Object) getThisReg();

    Ck(theObj);
    if (CBFATop+1 > CBFALimit) CBFArelloc();

    CBFATop->theStruct = theStruct;

    hcb = (unsigned long) HandleCB; /* this does not work, but imports the symbol !!!! */
    asm volatile ("LDIL L'HandleCB, %0
                   LDO  R'HandleCB(%0),%0": "=r" (hcb));

    /* Construct the following code in the CBF:
     * 0 LDIL L'HandleCB, %r1
     * 1 MFSP %sr4,%r31
     * 2 LDO  R'HandleCB(%r1),%r1
     * 3 MTSP %r31,%sr0
     * 4 LDIL L'<&CBFATop->theStruct>,%r28
     * 5 BE   0(%sr4,%r1)
     * 6 LDO  R'<&CBFATop->theStruct>(%r28),%r28
     */
    CBFATop->code[0] = (8<<26)|(1<<21)
      |mangle21(((unsigned long)hcb >> 11) & 0x1fffff);
    CBFATop->code[1] = (1<<13)|(0x25<<5)|31;
    CBFATop->code[2] = (0xd<<26)|(1<<21)|(1<<16)
      |bletch((unsigned long)hcb & 0x7ff);
    CBFATop->code[3] = (31<<16)|(0xc1<<5);
    CBFATop->code[4] = (8<<26)|(28<<21)
      |mangle21(((unsigned long)&CBFATop->theStruct >> 11) & 0x1fffff);
    CBFATop->code[5] = (0x38<<26)|(1<<21)|(1<<13); /* really sr4 - sic! */
    CBFATop->code[6] = (0xd<<26)|(28<<21)|(28<<16)
      |bletch((unsigned long)&CBFATop->theStruct & 0x7ff);

    /* now flush the code from the data cache */
    asm volatile ("fdc\t0(0,%0)" : /* no out */
                  : "r" (&CBFATop->theStruct));
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

long CHandleCB(long a1, long a2, long a3, long a4, long FOR)
{
    struct CallBackFrame        cbf;
    ref(Structure)              theStruct;
    long                         retval;
    DeclReference1(struct Item *, theObj);

    /* First things first, get a grib on the struct pointer */
    asm volatile ("LDW 0(%%r28),%0" : "=r" (theStruct));

    if (!theStruct) { freeCallbackCalled(); return 0; }

    /* Push CallBackFrame. */
    cbf.next    = ActiveCallBackFrame;
    cbf.betaTop = BetaStackTop;
    /* cbf.tmp     = (long) getSPReg();  so the GC can find it */
    ActiveCallBackFrame = &cbf;

#if 0
    setIOAReg(savedIOA);
    setIOATopoffReg(savedIOATopoff);
    setRefSP(savedRefSP);
#endif

    Ck(theStruct); Ck(theStruct->iOrigin);
    setCallReg(theStruct->iProto);
    setOriginReg(theStruct->iOrigin);
    theObj = AlloI();

    /* This is how the arguments will look to the callee:
     * The first 4 integer arguments are in registers 26 - 23 as always.
     * -52(sp) = pointer to the first of the rest of the args, call it 'ap'
     * (ap) = arg#4, -4(ap) = arg#5,...
     * Unfortunately this doesn't work for doubles :-(
     */
    setThisReg(0); /* To prevent pushing of garbage in the CallBackRoutine */
    setCallReg(theObj);
    retval = theObj->Proto->CallBackRoutine(a1, a2, a3, a4, &FOR - 128/4);

    BETA_CLOBBER;

    /* Pop CallBackFrame */
    ActiveCallBackFrame = cbf.next;
    BetaStackTop        = cbf.betaTop;

#if 0
    asm ("LDIL\tLR'savedIOA,%r1");
    asm ("STW\t%r17,RR'savedIOA(0,%r1)");
    asm ("LDIL\tLR'savedIOATopoff,%r1");
    asm ("STW\t%r18,RR'savedIOATopoff(0,%r1)");
    asm ("LDIL\tLR'savedRefSP,%r1");
    asm ("STW\t%r14,RR'savedRefSP(0,%r1)");

/*
    savedIOA       = getIOAReg();
    savedIOATopoff = getIOATopoffReg();
    savedRefSP     = getRefSP();
*/
#endif

    return retval;
}
#endif /* hppa */
