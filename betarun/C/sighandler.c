/*
 * BETA RUNTIME SYSTEM, Copyright (C) 1991-94 Mjolner Informatics Aps.
 * sighandler.c
 * by Lars Bak, Peter Andersen, Peter Orbaek, Tommy Thorn, Jacob Seligmann and S|ren Brandt
 */
#include "beta.h"

/***************************************************************************/
/************************ INCLUDES and DEFINITIONS *************************/
/***************************************************************************/

#if defined(UNIX)
#include <signal.h>
#endif /* UNIX  */

#ifdef sun4s
#include <siginfo.h>
#include <sys/regset.h>
#include <sys/ucontext.h>
#endif

/***************************************************************************/
/******************** Handlers for various platforms  **********************/
/***************************************************************************/


/******************** BEGIN general UNIX handler ***************************/
#if defined(UNIX) && !defined(sun4s)

#ifdef linux 
#define GetPCandSP() { PC = (long *) scp.eip; StackEnd = (long *) scp.esp_at_signal; }
#endif

#ifdef hppa
#ifdef UseRefStack
#define GetPCandSP() { \
  PC = (long *) (scp->sc_pcoq_head & (~3)); \
  /* StackEnd not used */\
}
#else /* UseRefStack */
#define GetPCandSP() { \
  PC = (long *) (scp->sc_pcoq_head & (~3)); \
  StackEnd = (long *) scp->sc_sp; \
}
#endif /* UseRefStack */
#endif /* hppa */

#ifdef sgi
#define GetPCandSP() { /* handled as a special case below */ }
#endif

#ifndef GetPCandSP
#error GetPCandSP should be defined
#endif

/* This procedure is called if a nasty signal is received
 * during execution of BetaSignalHandler.
 * Please Exit nicely.
 */
static void ExitHandler(sig, code, scp, addr)
  long sig, code;
  struct sigcontext *scp;
  char *addr;
{ 
#ifdef UNIX
  DEBUG_CODE(fprintf(stderr, 
		     "ExitHandler: Caught signal %d during signal handling\n",
		     (int)sig);
	     fflush(stderr);
	     );
#endif
  BetaExit(1); 
}

#if defined(linux)
#include <asm/sigcontext.h> 
void BetaSignalHandler(long sig, struct sigcontext_struct scp)
#else
void BetaSignalHandler(long sig, long code, struct sigcontext * scp, char *addr)
#endif
{
#ifndef linux
  handle(Object) theCell;
#endif
  ref(Object)    theObj = 0;
  long *PC;
  long todo = 0;

#ifdef RTDEBUG
  fprintf(output, 
	  "\nBetaSignalHandler: Caught signal %d, code %d\n", 
	  (int)sig, 
#ifdef linux
	  0
#else
	  (int)code
#endif /* linux */
	  );
#endif /* RTDEBUG */

  /* Setup signal handles for the Beta system */
  signal( SIGFPE,  ExitHandler);
  signal( SIGILL,  ExitHandler);
  signal( SIGBUS,  ExitHandler);
  signal( SIGSEGV, ExitHandler);
#ifdef SIGEMT
  signal( SIGEMT,  ExitHandler);
#endif

  /* Set StackEnd to the stack pointer just before trap. */
  GetPCandSP();

#ifdef sgi
  { 
    PC = (long *) scp->sc_pc;
    theObj = CurrentObject = (struct Object *) scp->sc_regs[30];
    if (IsBetaCodeAddr((long)PC)){ 
      long SPoff;
      GetSPoff(SPoff, CodeEntry(theObj->Proto, (long)PC)); 
      StackEnd = (long *) ((long)scp->sc_regs[29]+SPoff);
    }
    if( !(inBetaHeap(theObj) && isObject(theObj))) theObj  = 0;
    switch( sig){
    case SIGFPE: 
      if (code==7){
	/* break 7 instruction: integer division by zero */
	todo=DisplayBetaStack(ZeroDivErr , theObj, PC, sig); break;
      } else if (scp->sc_fpc_csr & (1<<15)){
	/* Floating point division by zero cause bit set */
	todo=DisplayBetaStack(FpZeroDivErr , theObj, PC, sig); break;
      } else {
	todo=DisplayBetaStack(FpExceptErr, theObj, PC, sig); break;
      }
    case SIGEMT:
      todo=DisplayBetaStack( EmulatorTrapErr, theObj, PC, sig); break;
    case SIGILL:
      todo=DisplayBetaStack( IllegalInstErr, theObj, PC, sig); break;
    case SIGBUS:
      todo=DisplayBetaStack( BusErr, theObj, PC, sig); break;
    case SIGSEGV:
      todo=DisplayBetaStack( SegmentationErr, theObj, PC, sig); break;
    case SIGTRAP:
#if 0
      DEBUG_CODE(fprintf(stderr, "SIGTRAP caught; code is %d\n", code);
		 fflush(stderr));
      switch(code){
      case 14:
	todo=DisplayBetaStack( RefNoneErr, theObj, PC, sig); break;
      default:
	todo=DisplayBetaStack( EmulatorTrapErr, theObj, PC, sig); break;
      }
#endif
      /* code can be various different things even for refnone */
      todo=DisplayBetaStack( RefNoneErr, theObj, PC, sig); break;
      break;
#ifdef RTDEBUG
    case SIGINT: /* Interrupt */
      todo=DisplayBetaStack( InterruptErr, theObj, PC, sig); break;
#endif
    default: 
      todo=DisplayBetaStack( UnknownSigErr, theObj, PC, sig);  
    }
  }
#endif

#if defined(linux)
#define fpu_sw scp.fpstate->status
  /* see <asm/sigcontext.h> */
  theObj = cast(Object) scp.edx;
  if ( ! (inIOA(theObj) && isObject (theObj)))
    theObj  = 0;

  switch(sig){
  case SIGFPE: 
    /* scp.trapno matches hardware numbers, see table 9-1 in 
     * Intel486 Microprocessor Family Programmer's Reference Manual
     */
    switch(scp.trapno){
    case 0: /* Divide Error */
      if (theObj==0) {
	/* IDIV uses %edx (i.e. current object register) for divisor.
	 * If this is 0, theObj will be 0 when trap is taken.
	 * Use the fact that current object is pushed before IDIV,
	 * and take it from the stack.
	 */
	theObj = (struct Object *) *StackEnd++;
	todo=DisplayBetaStack( ZeroDivErr, theObj, PC, sig); break;
      } else {
	todo=DisplayBetaStack( FpExceptErr, theObj, PC, sig); break;
      }
      break;
    case 16: /* Floating Point Error */
      /* See figure 15-2 in
       * Intel486 Microprocessor Family Programmer's Reference Manual
       */
      if (fpu_sw & (1L<<6)){
	/* SF: floating point stack fault */
	if (fpu_sw & (1L<<9)){
	  /* C1=1: overflow */
	  todo=DisplayBetaStack( FpStackOflowErr, theObj, PC, sig); break;
	} else {
	  /* C1=0: underflow */
	  todo=DisplayBetaStack( FpStackUflowErr, theObj, PC, sig); break;
	}
      }
      if (fpu_sw & (1L<<2)){
	/* ZE: zero divide */
	todo=DisplayBetaStack( FpZeroDivErr, theObj, PC, sig); break;
      }
      /* Fall back: report general FP error */
      todo=DisplayBetaStack( FpExceptErr, theObj, PC, sig); break;
    default:	
      todo=DisplayBetaStack( ArithExceptErr, theObj, PC, sig); break;
    }
    break;
  case SIGILL:
    todo=DisplayBetaStack( IllegalInstErr, theObj, PC, sig); break;
  case SIGBUS:
    todo=DisplayBetaStack( BusErr, theObj, PC, sig); break;
#ifdef RTDEBUG
  case SIGINT: /* Interrupt */
    todo=DisplayBetaStack( InterruptErr, theObj, PC, sig); break;
#endif /* RTDEBUG */
  case SIGTRAP: 
    if ( (*((char*)PC-1)) == (char)0xcc ){
      /* int3 break */
      scp.eip -= 1; /* PC points just after int3 instruction */
      PC = (long *) scp.eip;
      DEBUG_VALHALLA(fprintf(output, "sighandler: adjusting PC to 0x%x\n", (int)PC));
    }
    todo=DisplayBetaStack( EmulatorTrapErr, theObj, PC, sig); break;
  case SIGSEGV:
    switch (scp.trapno) {
    case 5: /* Interrupt 5 generated by boundl */
      todo=DisplayBetaStack(RepRangeErr, theObj, PC, sig);
    case 12: /* Stack Fault */
      /* FIXME: does not work */
      todo=DisplayBetaStack(StackErr, theObj, PC, sig); break;
    default:
      todo=DisplayBetaStack(SegmentationErr, theObj, PC, sig); break;
    }
    break;
  default: 
    todo=DisplayBetaStack( UnknownSigErr, theObj, PC, sig);  
  }
#undef fpu_sw
#endif /* defined(linux) */

#ifdef hppa
  /* Try to fetch the address of current Beta object in %r3 (This).*/
  /* See /usr/include/sys/signal.h and /usr/include/machine/save_state.h */
  theCell = (handle(Object)) &scp->sc_gr3;
  if( inIOA( *theCell))
    if( isObject( *theCell)) theObj  = *theCell;

  switch( sig){
    case SIGFPE:
      /* We can't use code for dispatching, c.f. signal(2):
       * For SIGFPE, code has the following values:
       *    12      overflow trap;
       *    13      conditional trap;
       *    14      assist exception trap;
       *    22      assist emulation trap.
       *
       * FIXME:
       * By inspection using debugger, I have determined, that
       * code is 0xd for integer division by zero and 0xe
       * for floating point division by zero.
       * I use this below.
       * Other possibilities might be to look at the VZOUIC flags of
       * the floating point status register. But the manual says, that
       * the architecture need not set these bits, when the trap is
       * *taken*.
       * A more thorough method might be to fetch the instruction 
       * address from the context, and decode the instruction found at that
       * address to determine what has happened.
       */
      switch(code){
      case 0xd: /* int div by zero */
	/* The current BETA compiler calls the leaf routine IDiv with r31 
	 * as return register. 
	 * Thus the actual BETA code address is in r31. However, the two
	 * LSB seems to be used for some tagging, so we mask them off.
	 */
	PC = (long*)((scp->sc_gr31 & (~3)) - 8);
	todo=DisplayBetaStack( ZeroDivErr, theObj, PC, sig); break;
      case 0xe: /* fp div by zero */
	todo=DisplayBetaStack( FpZeroDivErr, theObj, PC, sig); break;
      default: /* other floating point exception */
	todo=DisplayBetaStack( FpExceptErr, theObj, PC, sig);
      }
      break;
    case SIGEMT:
      todo=DisplayBetaStack( EmulatorTrapErr, theObj, PC, sig); break;
    case SIGILL:
      todo=DisplayBetaStack( IllegalInstErr, theObj, PC, sig);
      break;
    case SIGBUS:
      todo=DisplayBetaStack( BusErr, theObj, PC, sig); break;
    case SIGSEGV:
      todo=DisplayBetaStack( SegmentationErr, theObj, PC, sig); break;
#ifdef RTDEBUG
    case SIGINT: /* Interrupt */
      todo=DisplayBetaStack( InterruptErr, theObj, PC, sig); break;
#endif   
    default:
      todo=DisplayBetaStack( UnknownSigErr, theObj, PC, sig);
  }
#endif /* hppa */

  if (!todo) BetaExit(1);
}

#endif /* UNIX, !sun4s */
/******************** END general UNIX handler ****************************/


/******************************** BEGIN sun4s *****************************/
#ifdef sun4s

static void ExitHandler(int sig)
{
  DEBUG_CODE(fprintf(stderr, 
		     "ExitHandler: Caught signal %d during signal handling\n",
		     (int)sig);
	     fflush(stderr);
	     );
  BetaExit(1);
}

void BetaSignalHandler (long sig, siginfo_t *info, ucontext_t *ucon)
{
  handle(Object) theCell;
  ref(Object)    theObj = 0;
  long *PC;
  long todo = 0;

  /* Setup signal handlers for the Beta system */
  signal( SIGFPE,  ExitHandler);
  signal( SIGILL,  ExitHandler);
  signal( SIGBUS,  ExitHandler);
  signal( SIGSEGV, ExitHandler);
  signal( SIGEMT,  ExitHandler);

  
  /* Set StackEnd to the stack pointer just before trap. 
   * REG_PC etc. are in /usr/include/sys/regset.h.
   */
#ifndef MT
  StackEnd = (long *) ucon->uc_mcontext.gregs[REG_SP];
#endif
  PC = (long *) ucon->uc_mcontext.gregs[REG_PC];

#ifndef MT
  DEBUG_VALHALLA(fprintf(output,"BetaSignalHandler: StackEnd set to 0x%x\n",(int) StackEnd));
#endif /* MT */

  /* Try to fetch the address of current Beta object from i0.*/
  theCell = (struct Object **) &((struct RegWin*)ucon->uc_mcontext.gregs[REG_SP])->i0;
  if( inIOA( *theCell)) if( isObject( *theCell)) theObj  = *theCell;

  switch(sig){
  case SIGFPE: 
    switch(info->si_code){
    case FPE_INTDIV: /* int div by zero */
      /* The current BETA compiler generates calls to the (leaf) routine
       * .idiv to handle integer division. Thus we need to fix the PC value.
       */
      PC = (long*) ucon->uc_mcontext.gregs[REG_O7];
      todo=DisplayBetaStack( ZeroDivErr, theObj, PC, sig); break;
    case FPE_FLTDIV: /* fp div by zero */
      todo=DisplayBetaStack( FpZeroDivErr, theObj, PC, sig); break;
    default: /* arithmetic exception */
      todo=DisplayBetaStack( FpExceptErr, theObj, PC, sig);
    }
    break;
  case SIGEMT:
    todo=DisplayBetaStack( EmulatorTrapErr, theObj, PC, sig); break;
  case SIGILL: /* Illegal instruction or trap */
    switch(info->si_code){
    case ILL_ILLTRP:
      switch(info->si_trapno-16){
#ifdef MT
      case 0x80: /* Solaris 2.3, 2.4, 2.5 */
      case 0x100: /* Solaris 2.5.1 */
	/* tle 16 trap => component stack overflow */
	todo=DisplayBetaStack( StackErr, theObj, PC, sig); break;
#endif
      case 0x81: /* Solaris 2.3, 2.4, 2.5 */
      case 0x101: /* Solaris 2.5.1 */
	/* tle 17 trap => ref none */
	todo=DisplayBetaStack( RefNoneErr, theObj, PC, sig); break;
      default:
	todo=DisplayBetaStack( IllegalInstErr, theObj, PC, sig); break;
      }
      break;
    default:
      todo=DisplayBetaStack( IllegalInstErr, theObj, PC, sig); break;
    }
    break;
  case SIGBUS: /* Bus error */
    todo=DisplayBetaStack( BusErr, theObj, PC, sig); break;
  case SIGSEGV: /* Segmentation fault */
    todo=DisplayBetaStack( SegmentationErr, theObj, PC, sig); break;
#ifdef RTDEBUG
  case SIGINT: /* Interrupt */
    todo=DisplayBetaStack( InterruptErr, theObj, PC, sig); break;
#endif
  default:  /* Unknown signal */
    todo=DisplayBetaStack( UnknownSigErr, theObj, PC, sig);  
  }

  if (!todo) BetaExit(1);
}
  
#endif /* sun4s */
/***************************** END sun4s ********************************/


/***************************** BEGIN nti ********************************/
#ifdef nti
#include <float.h>

int BetaSignalHandler ( LPEXCEPTION_POINTERS lpEP )
{ 
  EXCEPTION_RECORD SavedExceptRec;
  CONTEXT SavedContextRec;
  struct Object *theObj = 0;
  long *PC;
  long todo = 0;
  long sig;

  if (NoCatchException) return EXCEPTION_CONTINUE_SEARCH;

  SavedExceptRec =  *(lpEP)->ExceptionRecord;  
  SavedContextRec = *(lpEP)->ContextRecord;
  
  if (SavedContextRec.ContextFlags & CONTEXT_CONTROL){
    PC       = (long *)SavedContextRec.Eip;
    StackEnd = (long *)SavedContextRec.Esp;
  } else {
    /* Can't display stack if SP unknown */
    return EXCEPTION_CONTINUE_SEARCH;
  }
  if (SavedContextRec.ContextFlags & CONTEXT_INTEGER){
    theObj = (struct Object *)SavedContextRec.Edx;
  }
  sig = (long)SavedExceptRec.ExceptionCode;
  switch (SavedExceptRec.ExceptionCode){
  case EXCEPTION_ACCESS_VIOLATION:  
  case EXCEPTION_DATATYPE_MISALIGNMENT:  
    todo=DisplayBetaStack( SegmentationErr, theObj, PC, sig); break;
  case EXCEPTION_STACK_OVERFLOW:
    todo=DisplayBetaStack( StackErr, theObj, PC, sig); break;
  case EXCEPTION_BREAKPOINT:
    fprintf(output, "breakpoint at PC 0x%x\n", PC); fflush(output);
    todo=DisplayBetaStack( EmulatorTrapErr, theObj, PC, sig);
  case EXCEPTION_ARRAY_BOUNDS_EXCEEDED:
    todo=DisplayBetaStack( RepRangeErr, theObj, PC, sig);
  case EXCEPTION_ILLEGAL_INSTRUCTION:
  case EXCEPTION_PRIV_INSTRUCTION:
    todo=DisplayBetaStack( IllegalInstErr, theObj, PC, sig); break;
  case EXCEPTION_INT_DIVIDE_BY_ZERO:
    /* Fix current object: It was pushed before the idiv instruction,
     * but will be zero in this case.
     */
    theObj = *(struct Object **)StackEnd++;
    todo=DisplayBetaStack( ZeroDivErr, theObj, PC, sig); break;
  case EXCEPTION_FLT_DIVIDE_BY_ZERO:
    todo=DisplayBetaStack( FpZeroDivErr, theObj, PC, sig); break;
  case EXCEPTION_FLT_STACK_CHECK:
    if (SavedContextRec.ContextFlags & CONTEXT_FLOATING_POINT){
      if (SavedContextRec.FloatSave.StatusWord & (1L<<9)){
	/* C1=1: overflow */
	todo=DisplayBetaStack( FpStackOflowErr, theObj, PC, sig); break;
      } else {
	/* C1=0: underflow */
	todo=DisplayBetaStack( FpStackUflowErr, theObj, PC, sig); break;
      }
    } else {
      /* lets guess on overflow */
      todo=DisplayBetaStack( FpStackOflowErr, theObj, PC, sig); break;
    }
  case EXCEPTION_FLT_DENORMAL_OPERAND:
  case EXCEPTION_FLT_INEXACT_RESULT:
  case EXCEPTION_FLT_OVERFLOW:
  case EXCEPTION_FLT_UNDERFLOW:
  case EXCEPTION_FLT_INVALID_OPERATION:
    todo=DisplayBetaStack( FpExceptErr, theObj, PC, sig); break;
  default:
    todo=DisplayBetaStack( UnknownSigErr, theObj, PC, sig);  
  }
  
  if (todo) {
    /* continue after ValhallaOnProcessStop */
    DEBUG_VALHALLA(fprintf(output,"BetaSignalHandler: EXCEPTION_CONTINUE_EXECUTION\n"));
    return EXCEPTION_CONTINUE_EXECUTION;
  } else {
    BetaExit(1);
    /* return EXCEPTION_CONTINUE_SEARCH; */
  }
}

/* beta_main: called from _AttBC */
void beta_main(void (*AttBC)(struct Component *), struct Component *comp)
{
  /* Set up structured exception handling for rest of execution */
  __try 
    { 
      /* Start BETA execution */
      AttBC(comp);
    }
  __except ( BetaSignalHandler(GetExceptionInformation()))
    {
    }
}

#endif /* nti */
/***************************** END nti ********************************/


/***************************** BEGIN ppcmac ********************************/
#ifdef ppcmac

#include <MachineExceptions.h>

OSStatus BetaSignalHandler(ExceptionInformation *info)
{
  ref(Object) theObj;
  long *PC;
  long todo = 0;
  ExceptionKind sig = info->theKind;

  /* Set StackEnd to the stack pointer just before exception */
  StackEnd = (long *)info->registerImage->R1.lo;
  PC = (long *) info->machineState->PC.lo;

  /* Try to fetch the address of current Beta object from i0.*/
  theObj = cast(Object) info->registerImage->R31.lo;
  if( !inIOA(theObj) || !isObject(theObj)) theObj = 0;

  switch(sig){
#if 0 /* Not used on PPC */
  case integerException:
    todo=DisplayBetaStack( ArithExceptErr, theObj, PC, sig); break;
#endif
  case trapException:
    /* FIXME: possibly some details in the exception records can determine
     * if it is a refnone or another trap. E.g. one could check if the
     * instruction at PC is "twlei reg,0".
     */
    todo=DisplayBetaStack( RefNoneErr, theObj, PC, sig); break;
  case illegalInstructionException:
    todo=DisplayBetaStack( IllegalInstErr, theObj, PC, sig);break;
  case accessException: 
  case unmappedMemoryException: 
  case excludedMemoryException: 
  case readOnlyMemoryException: 
  case unresolvablePageFaultException: 
    todo=DisplayBetaStack( SegmentationErr, theObj, PC, sig); break;
  case stackOverflowException:
    todo=DisplayBetaStack( StackErr, theObj, PC, sig); break;
  case floatingPointException:
    /* FIXME: handle zerodiv (int+fp) */
    todo=DisplayBetaStack( FpExceptErr, theObj, PC, sig); break;
  default:
    todo=DisplayBetaStack( UnknownSigErr, theObj, PC, sig); break;
  }

  if (!todo) BetaExit(1);

  return noErr;
}

#endif /* ppcmac */
/***************************** END ppcmac ********************************/




/************************************************************************/ 
/************ InstallSigHandler: install a handler for sig **************/
/************************************************************************/ 

void InstallSigHandler (int sig)
{
#ifndef sun4s
#ifdef UNIX
     signal (sig, (void (*)(int))BetaSignalHandler);
#endif
#else /* sun4s */
  { struct sigaction sa;
    sa.sa_flags = SA_SIGINFO | SA_RESETHAND;
    sigemptyset(&sa.sa_mask); 
    sa.sa_handler = BetaSignalHandler;
    sigaction(sig,&sa,0);
  }
#endif /* sun4s */
}

/* 
 * SetupBetaSignalHandlers: install standard sig handlers for BETA.
 * Called from Initialize().
 */
void SetupBetaSignalHandlers(void)
{

#ifdef ppcmac
  InstallExceptionHandler((ExceptionHandler)BetaSignalHandler);
#else /* ppcmac */
#ifndef sun4s
#if defined(UNIX)
  { /* Setup signal handles for the Beta system */
#ifdef SIGTRAP
#ifdef sgi
    signal( SIGTRAP, (void (*)(int))BetaSignalHandler);
#endif
#ifdef linux
    signal( SIGTRAP, (void (*)(int))BetaSignalHandler);
#endif
#endif
#ifdef SIGFPE
    signal( SIGFPE,  (void (*)(int))BetaSignalHandler);
#endif
#ifdef SIGILL
    signal( SIGILL,  (void (*)(int))BetaSignalHandler);
#endif
#ifdef SIGBUS
    signal( SIGBUS,  (void (*)(int))BetaSignalHandler);
#endif
#ifdef SIGSEGV
    signal( SIGSEGV, (void (*)(int))BetaSignalHandler);
#endif
#ifdef SIGEMT
    signal( SIGEMT,  (void (*)(int))BetaSignalHandler);
#endif
#ifdef RTDEBUG
#ifdef SIGINT
    signal( SIGINT,  (void (*)(int))BetaSignalHandler);
#endif
#endif
  }
#endif /* UNIX */
  
#else /* sun4s */
  
  /* This is solaris */
  
#ifdef MT
  SetupVirtualTimerHandler(); /* interrupt every 0.1 second */
#endif

  /* sbrandt 9/7 93. See man sigaction and <sys/signal.h>. */
  { /* Setup signal handlers for the Beta system */
    struct sigaction sa;
    
    /* Specify that we want full info about the signal, and that
     * the handled signal should not be blocked while being handled: */
    sa.sa_flags = SA_SIGINFO | SA_NODEFER;
    
    /* No further signals should be blocked while handling the specified
     * signals. */
    sigemptyset(&sa.sa_mask); 
    
    /* Specify handler: */
    sa.sa_handler = BetaSignalHandler;
    
    sigaction( SIGFPE,  &sa, 0);
    sigaction( SIGILL,  &sa, 0);
    sigaction( SIGBUS,  &sa, 0);
    sigaction( SIGSEGV, &sa, 0);
    sigaction( SIGEMT,  &sa, 0);
#ifdef RTDEBUG
    sigaction( SIGINT,  &sa, 0);
#endif
  }
#endif /* sun4s */
#endif /* ppcmac */

} /* SetupBetaSignalHandlers */
