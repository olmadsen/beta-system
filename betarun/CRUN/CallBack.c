/*
 * BETA C RUNTIME SYSTEM, Copyright (C) 1992-94 Mjolner Informatics Aps.
 * by Peter Oerbaek, Peter Andersen, Tommy Thorn and Kim Jensen Moeller.
 */

#include "beta.h"
#include "crun.h"
#ifdef __powerc
#include <MixedMode.h>
#endif

#ifdef RTVALHALLA
#include "valhallaComm.h"
#endif /* RTVALHALLA */

/*************************** crts ***************************/
#ifdef crts

/* HandleCallBack is called from a CallBackEntry, setup like below. */ 

long * oldSP;
extern long a0;

#ifdef __powerc
long HandleCB(long arg1, long arg2, long arg3, long arg4, long arg5, long arg6, long arg7, long arg8)
#else
long HandleCB(long arg1, long arg2, long arg3, long arg4, long arg5, long arg6)
#endif  
{
  struct Item * theObj;
  struct CallBackEntry * cb;
  long retval;
  long (*cbr)();
  long retAddr, *FP;
  
  getret_CB(retAddr); /* Get return address */
  GetFramePointer(FP); /* Get framepointer */
  /* Calculate the address of the CallBackEntry. As our return
     address points to the call in the middle of the CallBackEntry,
     we subtract the offset (notice that the value of cb is not used.)
   */
  cb = cast(CallBackEntry) (retAddr - NUMBER_TO_STRUCT);

  if (!cb->theStruct) { freeCallbackCalled(); return 0; }
  
  Ck(cb->theStruct); Ck(cb->theStruct->iOrigin);

  theObj = AlloI(cb->theStruct->iOrigin, cb->theStruct->iProto);

  /* Call the CallBack stub. Gcc push the necessary parameters to stack */
  cbr = (long (*)()) ((long*)theObj->Proto->CBR);
  a0=(long)theObj; /* set current object */
#ifdef __powerc
  retval = cbr(arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8);  
#else
  retval = cbr(arg1, arg2, arg3, arg4, arg5, arg6);  
#endif  
  return retval;
}

#ifdef __powerc
long pascal HandlePCB(long arg1, long arg2, long arg3, long arg4, long arg5, long arg6, long arg7, long arg8)
{
  struct Item * theObj;
  struct CallBackEntry * cb;
  long retval,*PCB_SP;
  long pascal (*cbr)();
  long retAddr, *FP;
  
  GetStackPointer(PCB_SP);
  getret_CB(retAddr); /* Get return address */
  GetFramePointer(FP); /* Get framepointer */
  /* Calculate the address of the CallBackEntry. As our return
     address points to the call in the middle of the CallBackEntry,
     we subtract the offset (notice that the value of cb is not used.)
   */
  cb = cast(CallBackEntry) (retAddr - NUMBER_TO_STRUCT);

  if (!cb->theStruct) { freeCallbackCalled(); return 0; }
  
  Ck(cb->theStruct); Ck(cb->theStruct->iOrigin);

  theObj = AlloI(cb->theStruct->iOrigin, cb->theStruct->iProto);

  /* Call the CallBack stub. Pascal parameters on stack */
  cbr = (long (*)()) ((long*)theObj->Proto->CBR);
  a0=(long)theObj; /* set current object */
  retval = cbr(arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8);  
  //retval = cbr(PCB_SP+HandlePCB_Frame_Size+24);  
  
  return retval;
}
#endif

#if 0
/* DO NOT REMOVE!!! Used to create code for new call back stubs to fill in CBFA->code[x] */
long CBstub(long arg1, long arg2, long arg3, long arg4, long arg5, long arg6)
{
  GetStackPointer(oldSP);
  return HandleCB(arg1, arg2, arg3, arg4, arg5, arg6);
}
#endif


void *CopyCPP(ref(Structure) theStruct, ref(Object) theObj)
{
  if (!theStruct) return (void *)0 /* NULL function pointer given to C */;

  /* Take the next free entry in the Call Back Functions Area.	*/
  /* This area is defined by 
   * [ lastCBFABlock->entries <= CBFATop < CBFALimit ].
   */
  
  if (CBFATop+1 > CBFALimit){
    CBFArelloc();
  }
  
  Ck(theStruct); Ck(theObj);
  CBFATop->theStruct = theStruct;
  MK_CALL( HandleCB);
  FlushCache;
  ++CBFATop;
#ifdef MAC
    return (void *)(&(CBFATop-1)->code[0]);
#else
    return (void *)(&(CBFATop-1)->code[0]);
#endif
}

#ifdef __powerc

void *CopyPPP(ref(Structure) theStruct, long size, ref(Object) theObj, long univProcInfo)
{

  int res_size = size & 0xff;
  int par_size = (size & 0xff00)>>8;
  int i;
  unsigned long * code;                       
  unsigned long * func = (unsigned long *) HandlePCB; 
  UniversalProcPtr myCallBack;             

  /* Take the next free entry in the Call Back Functions Area.	*/
  /* This area is defined by 
   * [ lastCBFABlock->entries <= CBFATop < CBFALimit ].
   */
  
  if (CBFATop+1 > CBFALimit){
    CBFArelloc();
  }
  
  Ck(theStruct);
  Ck(theObj);
  CBFATop->theStruct = theStruct;
  
  code = (unsigned long *) NewPtr(4*18);                        
  *(code++) = (unsigned long) CBFATop->theStruct;               
  CBFATop->code[0] = (unsigned long*) code;                
  CBFATop->code[1] = (unsigned long*) *(func+1); /* TOC ?? */    
  *(code++) = 0x7C0802A6; /* mflr      r0;  				*/ 
  *(code++) = 0xBF41FFE8; /* stmw      r26,-0x0018(SP) 	    */ 
  *(code++) = 0x90010008; /* stw       r0,0x0008(SP) 		*/ 
  *(code++) = 0x9421FFB0; /* stwu      SP,-0x0050(SP) 	    */ 
  *(code++) = 0x3F400000 | (((unsigned) &oldSP & 0xffff0000)>>16); /* lis       r26,oldSP		*/ 
  *(code++) = 0x635A0000 | ((unsigned) &oldSP & 0xffff);           /* ori       r26,r26,oldSP 	*/ 
  *(code++) = 0x903A0000; /* stw       SP,0x0000(r26) 	    */ 
  *(code++) = 0x3F400000 | ((*func & 0xffff0000)>>16); 	   /* lis       r26,func		*/ 
  *(code++) = 0x635A0000 |  (*func & 0xffff);              /* ori       r26,r26,func 	*/ 
  *(code++) = 0x7F4803A6; /* mtlr      r26;  				*/ 
  *(code++) = 0x4E800021; /* blrl 						    */ 
  *(code++) = 0x60000000; /* nop 							*/ 
  *(code++) = 0x80010058; /* lwz       r0,0x0058(SP) 		*/ 
  *(code++) = 0x30210050; /* addic     SP,SP,80 			*/ 
  *(code++) = 0x7C0803A6; /* mtlr      r0   				*/ 
  *(code++) = 0xBB41FFE8; /* lmw       r26,-0x0018(SP) 	    */ 
  *(code++) = 0x4E800020; /* blr 							*/ 

  univProcInfo |= kPascalStackBased | RESULT_SIZE(SIZE_CODE(res_size));
  //for (i=1; par_size>0; i++, par_size -= 4) 
  //   univProcInfo |= STACK_ROUTINE_PARAMETER(i, SIZE_CODE(4));
  myCallBack = NewRoutineDescriptor((ProcPtr)&CBFATop->code[0], univProcInfo, GetCurrentISA()); 

  //myCallBack = NewRoutineDescriptor((ProcPtr)HandlePCB, univProcInfo, GetCurrentISA());
  //return (void *)myCallBack;


  FlushCache;
  ++CBFATop;
  return (void *)(myCallBack);
}
#endif
#endif /* crts */

/**************************** sparc **************************/
#ifdef sparc

#ifdef __svr4__
extern long HandleCB();
#else
extern long HandleCB() asm("HandleCB");
#endif

asmlabel(CopyCPP, "
	ba	"CPREF"CopyCPP
	mov	%i0, %o1
");

void *CCopyCPP(ref(Structure) theStruct, ref(Object) theObj)
{
    DEBUG_CODE(NumCopyCPP++);

    if (!theStruct) return (void *)0 /* NULL function pointer given to C */;

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
#if 0
    if (next)
      BetaStackTop        = betaTop;
    else
      BetaStackTop        = 0; /* Valhalla assumes BetaStackTop is zero
				* if no C on stack */
#else
    BetaStackTop        = betaTop;
#endif
    
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

#include <sys/cache.h>

void *CopyCPP(ref(Structure) theStruct, ref(Object) theObj)
{   register unsigned long hcb /* , savedSR0 */;

    if (!theStruct) return (void *)0 /* NULL function pointer given to C */;

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

    /* Now flush the code from the data cache */

    /* Save SR0 */
    /* asm volatile ("mfsp %%sr0,%0" : "=r" (savedSR0)); */

    /* Extract SID from address */
    asm volatile ("ldsid\t(0,%0),%%r1" : : "r" (&CBFATop->code[0]) );

    /* SID -> SR0 */
    asm volatile ("mtsp\t%r1,%sr0"); 

    /* flush data cache and synchronize */
    asm volatile ("fdc\t0(0,%0)" : : "r" (&CBFATop->code[0]));
    asm volatile ("fdc\t0(0,%0)" : : "r" (&CBFATop->code[2]));
    asm volatile ("fdc\t0(0,%0)" : : "r" (&CBFATop->code[4]));
    asm volatile ("fdc\t0(0,%0)" : : "r" (&CBFATop->code[6]));
    asm volatile ("sync");

    /* Flush instruction cache and synchronize */
    asm volatile ("fic\t0(%%sr0,%0)" : : "r" (&CBFATop->code[0]));
    asm volatile ("fic\t0(%%sr0,%0)" : : "r" (&CBFATop->code[2]));
    asm volatile ("fic\t0(%%sr0,%0)" : : "r" (&CBFATop->code[4]));
    asm volatile ("fic\t0(%%sr0,%0)" : : "r" (&CBFATop->code[6]));
    asm volatile ("sync");

    /* Assure cache has been flushed */
    asm volatile ("nop");
    asm volatile ("nop");
    asm volatile ("nop");
    asm volatile ("nop");
    asm volatile ("nop");
    asm volatile ("nop");
    asm volatile ("nop");

    /* Restore SR0 */
    /* asm volatile("mtsp\t%0,%%sr0" : : "r" (savedSR0)); */

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
#ifndef UseRefStack
    cbf.betaTop = BetaStackTop;
#endif
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

    BETA_CLOBBER;

    /* Pop CallBackFrame */
    ActiveCallBackFrame = cbf.next;
#ifndef UseRefStack
    BetaStackTop        = cbf.betaTop;
#endif

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
