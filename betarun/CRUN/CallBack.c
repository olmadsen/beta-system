/*
 * BETA C RUNTIME SYSTEM, Copyright (C) 1992-94 Mjolner Informatics Aps.
 * by Peter Oerbaek, Peter Andersen, Tommy Thorn and Kim Jensen Moeller.
 */

#include "beta.h"
#include "crun.h"

#ifndef MT

#ifdef __powerc
#include <MixedMode.h>
#endif

#ifdef RTVALHALLA
#include "valhallaComm.h"
#endif /* RTVALHALLA */

/**************************** sparc **************************/
#ifdef sparc

#ifdef __svr4__
extern long HandleCB();
#else
extern long HandleCB() __asm__("HandleCB");
#endif

asmlabel(CopyCPP, 
	 "ba	"CPREF"CopyCPP; "
	 "mov	%i0, %o1; "
	 );

void *CCopyCPP(ref(Structure) theStruct, ref(Object) theObj)
{
    DEBUG_CODE(NumCopyCPP++);

    if (!theStruct) return (void *)0 /* NULL function pointer given to C */;

    MT_CODE(mutex_lock(&cbfa_lock));

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

    MT_CODE(mutex_unlock(&cbfa_lock));

    return (void *)&(CBFATop-1)->mov_o7_g1;
}


/* HandleCallBack is called from a CallBackEntry, setup like
   above. This means that the real return address is in %g1
   and our %i7 pointes to the call instruction in the
   CallBackEntry. */

long HandleCB(long a1, long a2, long a3, long a4, long a5, long a6)
{
    register long		 g1	       __asm__("%g1");

    /* A CallBackFrame: */
    register ref(CallBackFrame)  next	       __asm__("%l5");
    register long              * betaTop       __asm__("%l6");
    register long                tmp           __asm__("%l7");
    
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

    theObj = SPARC_AlloI(cb->theStruct->iOrigin, 0, cb->theStruct->iProto, 0, 0);

    /* Call the CallBack stub, with out first four args in %i1..%i4, and
       the rest on stack from %i5 and onwards */
    
    /* As usual, skip the first instruction */
    cbr = (long (*)()) ((long*)theObj->Proto->CBR+1);
    
#ifdef RTVALHALLA
    if (valhallaIsStepping)
      ValhallaOnProcessStop ((long *) cbr,0,0,0,RTS_CBFA);
#endif
    
    retval = cbr(theObj, a1, a2, a3, a4, &a5);

    /* Pop CallBackFrame */
    ActiveCallBackFrame = next;
    BetaStackTop        = betaTop;
    
    /* Fool gcc into believing that the address of a6 is taken, thus
       making it save it on stack. */
    
    __asm__(""::"r" (&a6), "r" (next), "r" (betaTop), "r" (tmp)) ;
    return retval;
}

#endif /* sparc */

/************************** snake ******************************/

#ifdef hppa
/*
 * these are used in the process of generating HP-PA machinecode. Now aren't
 * these lovely?
 */
static __inline__ unsigned long mangle21(unsigned long x)
{
  unsigned long bit20, bits9_19, bits5_6, bits0_4, bits7_8;

  bit20 =     (x >> 20) & 0x0001;
  bits9_19 =  (x >> 9)  & 0x07ff;
  bits5_6 =   (x >> 7)  & 0x0003;
  bits0_4 =   (x >> 2)  & 0x001f;
  bits7_8 =       x     & 0x0003;

  return (bits0_4<<16)|(bits5_6<<14)|(bits7_8<<12)|(bits9_19<<1)|bit20;
}

static __inline__ unsigned long bletch(unsigned long x)
{
  return (x << 1) & 0x03ffe;
}

#include <sys/cache.h>

void *CopyCPP(ref(Structure) theStruct, ref(Object) theObj)
{   register unsigned long hcb /* , savedSR0 */;

    if (!theStruct) return (void *)0 /* NULL function pointer given to C */;

    theObj = cast(Object) getThisReg();

    Ck(theObj);
    if (CBFATop+1 > CBFALimit) CBFArelloc();

    CBFATop->theStruct = theStruct;

    /* Get the address of HandleCB */
#if 0
    /* datpete: 10/10/96.
     * The following does not work because the function pointer
     * is NOT the function address, but a "Procedure Label"
     * as explained in "PA-RISC Procedure Calling Conventions 
     * Reference Manual", section 5.3.2 (i.e. because the
     * address is loaded with a P' fixup).
     * See, however, HACK below.
     */
    { 
      extern void HandleCB();
      hcb = (unsigned long) HandleCB;
      /* HACK:
       * The following extracts the address as described in section 
       * 5.3.2 in the Calling Conventions manual. It is, however,
       * too inefficient, and the solution below is chosen instead.
       */
      hcb = *(unsigned long *)(hcb & ~3);
    }
#else
    /* We do it ourselves */
    __asm__ volatile (".IMPORT HandleCB,CODE");
    __asm__ volatile ("LDIL L'HandleCB, %0"    : "=r" (hcb));
    __asm__ volatile ("LDO  R'HandleCB(%0),%0" : "=r" (hcb));
#endif

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

    /* Now flush the code from the data cache */

    /* Save SR0 */
    /* __asm__ volatile ("mfsp %%sr0,%0" : "=r" (savedSR0)); */

    /* Extract SID from address */
    __asm__ volatile ("ldsid\t(0,%0),%%r1" : : "r" (&CBFATop->code[0]) );

    /* SID -> SR0 */
    __asm__ volatile ("mtsp\t%r1,%sr0"); 

    /* flush data cache and synchronize */
    __asm__ volatile ("fdc\t0(0,%0)" : : "r" (&CBFATop->code[0]));
    __asm__ volatile ("fdc\t0(0,%0)" : : "r" (&CBFATop->code[2]));
    __asm__ volatile ("fdc\t0(0,%0)" : : "r" (&CBFATop->code[4]));
    __asm__ volatile ("fdc\t0(0,%0)" : : "r" (&CBFATop->code[6]));
    __asm__ volatile ("sync");

    /* Flush instruction cache and synchronize */
    __asm__ volatile ("fic\t0(%%sr0,%0)" : : "r" (&CBFATop->code[0]));
    __asm__ volatile ("fic\t0(%%sr0,%0)" : : "r" (&CBFATop->code[2]));
    __asm__ volatile ("fic\t0(%%sr0,%0)" : : "r" (&CBFATop->code[4]));
    __asm__ volatile ("fic\t0(%%sr0,%0)" : : "r" (&CBFATop->code[6]));
    __asm__ volatile ("sync");

    /* Assure cache has been flushed */
    __asm__ volatile ("nop");
    __asm__ volatile ("nop");
    __asm__ volatile ("nop");
    __asm__ volatile ("nop");
    __asm__ volatile ("nop");
    __asm__ volatile ("nop");
    __asm__ volatile ("nop");

    /* Restore SR0 */
    /* __asm__ volatile("mtsp\t%0,%%sr0" : : "r" (savedSR0)); */

    ++CBFATop;

    /* the following C call expects the function-pointer in arg1 - sic! */
    __asm__("COPY %0, %%r26" : /*no out*/ : "r" (&(CBFATop-1)->code[0]) : "r26");
    return((void *)&(CBFATop-1)->code[0]);
}

long CHandleCB(long a1, long a2, long a3, long a4, long FOR)
{
    struct CallBackFrame        cbf;
    ref(Structure)              theStruct;
    long                         retval;
    DeclReference1(struct Item *, theObj);

    /* First things first, get a grib on the struct pointer */
    __asm__ volatile ("LDW 0(%%r28),%0" : "=r" (theStruct));

    if (!theStruct) { freeCallbackCalled(); return 0; }

    /* Push CallBackFrame. */
    cbf.next    = ActiveCallBackFrame;
#ifndef UseRefStack
    cbf.betaTop = BetaStackTop;
#endif
    /* cbf.tmp     = (long) getSPReg();  so the GC can find it */
    ActiveCallBackFrame = &cbf;

    Ck(theStruct); Ck(theStruct->iOrigin);
    setCallReg(theStruct->iProto);
    setOriginReg(theStruct->iOrigin);
    theObj = AlloI();
    Ck(theObj);

    /* This is how the arguments will look to the callee:
     * The first 4 integer arguments are in registers 26 - 23 as always.
     * -52(sp) = pointer to the first of the rest of the args, call it 'ap'
     * (ap) = arg#4, -4(ap) = arg#5,...
     * Unfortunately this doesn't work for doubles :-(
     */

#ifdef RTVALHALLA
    if (valhallaIsStepping)
      ValhallaOnProcessStop ((long *) theObj->Proto->CBR,0,0,0,RTS_CBFA);
#endif

    /* setThisReg(0); To prevent pushing of garbage in the CallBackRoutine.
     * No longer necessary since registers are now cleared in 
     * SnakeAdditions.S (HandleCB). SBRANDT 25/7/94 */
    setCallReg(theObj);
    retval = theObj->Proto->CBR(a1, a2, a3, a4, &FOR - 128/4);

    BETA_CLOBBER();

    /* Pop CallBackFrame */
    ActiveCallBackFrame = cbf.next;
#ifndef UseRefStack
    BetaStackTop        = cbf.betaTop;
#endif

    return retval;
}
#endif /* hppa */

#endif /* MT */
