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

#if defined(linux) 
/* Header files do not declare this! */
struct sigcontext {
  unsigned short gs, __gsh;
  unsigned short fs, __fsh;
  unsigned short es, __esh;
  unsigned short ds, __dsh;
  unsigned long edi;
  unsigned long esi;
  unsigned long ebp;
  unsigned long esp;
  unsigned long ebx;
  unsigned long edx;
  unsigned long ecx;
  unsigned long eax;
  unsigned long trapno;
  unsigned long err;
  unsigned long eip;
  unsigned short cs, __csh;
  unsigned long eflags;
  unsigned long esp_at_signal;
  unsigned short ss, __ssh;
  unsigned long i387;
  unsigned long oldmask;
  unsigned long cr2;
};
#endif /* linux */



/***************************************************************************/
/******************** Handlers for various platforms  **********************/
/***************************************************************************/


/******************** BEGIN general UNIX handler ***************************/
#if defined(UNIX) && !defined(sun4s) && !defined(crts)

#if (defined(linux) 
#define GetPCandSP() { PC = (long *) scp.eip; StackEnd = (long *) scp.esp_at_signal; }
#endif

#ifdef hppa
#ifdef UseRefStack
#define GetPCandSP() { PC = 0; /* StackEnd not used */ }
#else /* UseRefStack */
#define GetPCandSP() { PC = 0; StackEnd = (long *) scp->sc_sp; }
#endif /* UseRefStack */
#endif /* hppa */

#if defined(sun4) || defined(hpux9mc)
#define GetPCandSP() { PC = (long *) scp->sc_pc; StackEnd = (long *) scp->sc_sp; }
#endif

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
static static void ExitHandler(sig, code, scp, addr)
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
void BetaSignalHandler(long sig, struct sigcontext scp)
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

  DEBUG_CODE(fprintf(output, "\nBetaSignalHandler: Caught signal %d\n", (int)sig));

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
      todo=DisplayBetaStack( ArithExceptErr, theObj, PC, sig);break;
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

#ifdef sun4
  /* Try to fetch the address of current Beta object from i0.*/
  theCell = casthandle(Object) &(cast(RegWin)scp->sc_sp)->i0;
  if( inIOA( *theCell)) if( isObject( *theCell)) theObj  = *theCell;

  switch( sig){
  case SIGFPE: 
    switch(code){
    case FPE_INTDIV_TRAP: /* div by zero */
      todo=DisplayBetaStack( ZeroDivErr, theObj, PC, sig); break;
    default: /* arithmetic exception */
      todo=DisplayBetaStack( ArithExceptErr, theObj, PC, sig);
    }
    break;
  case SIGEMT:
    todo=DisplayBetaStack( EmulatorTrapErr, theObj, PC, sig); break;
  case SIGILL: /* Illegal instruction of trap */
    switch (code){
    case ILL_TRAP_FAULT(17): /* tle 17 trap => ref none */
      todo=DisplayBetaStack( RefNoneErr, theObj, PC, sig);
      break;
    default:
      todo=DisplayBetaStack( IllegalInstErr, theObj, PC, sig);
      break;
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
#endif

#if defined(linux)
  theObj = cast(Object) scp.edx;
  if ( ! (inIOA(theObj) && isObject (theObj)))
    theObj  = 0;

  switch(sig){
  case SIGFPE: 
    if (theObj==0 && scp.trapno==0) {
      /* IDIV uses %edx (i.e. current object register) for divisor.
       * If this is 0, theObj will be 0 when trap is taken.
       * Use the fact that current object is pushed before IDIV,
       * and take it from the stack.
       */
      theObj = (struct Object *) *StackEnd++;
      todo=DisplayBetaStack( ZeroDivErr, theObj, PC, sig); 
    } else {
      todo=DisplayBetaStack( ArithExceptErr, theObj, PC, sig); 
    }
    break;
  case SIGILL:
    todo=DisplayBetaStack( IllegalInstErr, theObj, PC, sig); break;
  case SIGBUS:
    todo=DisplayBetaStack( BusErr, theObj, PC, sig); break;
#ifdef RTDEBUG
  case SIGINT: /* Interrupt */
    todo=DisplayBetaStack( InterruptErr, theObj, PC, sig); break;
  case SIGTRAP: 
    if ( (*((char*)PC-1)) == (char)0xcc ){
      /* int3 break */
      scp.eip -= 1; /* PC points just after int3 instruction */
      PC = (long *) scp.eip;
      DEBUG_VALHALLA(fprintf(output, "sighandler: adjusting PC to 0x%x\n", (int)PC));
    }
    todo=DisplayBetaStack( EmulatorTrapErr, theObj, PC, sig); break;
#endif
  case SIGSEGV:
    if (scp.trapno == 5) /* Interrupt 5 generated by boundl */
      todo=DisplayBetaStack(RepRangeErr, theObj, PC, sig);
    else
      todo=DisplayBetaStack(SegmentationErr, theObj, PC, sig); 
    break;
  default: 
    todo=DisplayBetaStack( UnknownSigErr, theObj, PC, sig);  
  }
#endif /* defined(linux) */

#if defined(hpux9mc)
  /* Try to fetch the address of current Beta object in a0.
   * The numbers 68 and 72 have been found ad hoc!
   */
  theCell = (handle(Object)) (((long) &scp) + ((long) 68));
  if( inIOA( *theCell))
    if( isObject( *theCell)) 
      theObj  = *theCell;

  if (!theObj){
    theCell = (handle(Object)) (((long) &scp) + ((long) 72));
    if( inIOA( *theCell))
      if( isObject( *theCell)) {
	theObj  = *theCell;
      }
  }

  switch( sig){
    case SIGFPE: 
      if( code == 5 ) /* Only documented in 'man signal' */
        todo=DisplayBetaStack(ZeroDivErr, theObj, PC, sig);
      else
        todo=DisplayBetaStack( ArithExceptErr, theObj, PC, sig);  
      break;
    case SIGEMT:
      todo=DisplayBetaStack( EmulatorTrapErr, theObj, PC, sig); break;
    case SIGILL:
      switch(code){
      case 6: /* Only documented in 'man signal' */
	/* if code == 6 then it has been a chk instruction => index error. */
        todo=DisplayBetaStack( RepRangeErr, theObj, PC, sig);
	break;
      case 7: /* Only documented in 'man signal' */
	/* if code == 7 then it has been a trap instruction => reference is none. */
        todo=DisplayBetaStack( RefNoneErr, theObj, PC, sig);
	break;
      default:
        todo=DisplayBetaStack( IllegalInstErr, theObj, PC, sig);
        break;
      }
      break;
    case SIGBUS:
      todo=DisplayBetaStack( BusErr, theObj, PC, sig); break;
    case SIGSEGV:
      todo=DisplayBetaStack( SegmentationErr, theObj, PC, sig); break;
#if defined(RTDEBUG) && defined(linux)
    case SIGINT: /* Interrupt */
      todo=DisplayBetaStack( InterruptErr, theObj, PC, sig); break;
#endif
    default: 
      todo=DisplayBetaStack( UnknownSigErr, theObj, PC, sig);  
  }
#endif /* defined(hpux) && !defined(hppa) */

#ifdef hppa
  /* Try to fetch the address of current Beta object in %r3 (This).*/
  /* See /usr/include/sys/signal.h and /usr/include/machine/save_state.h */
  PC = (long *) scp->sc_ret1;
  theCell = (handle(Object)) &scp->sc_gr3;
  if( inIOA( *theCell))
    if( isObject( *theCell)) theObj  = *theCell;

  switch( sig){
    case SIGFPE:
      todo=DisplayBetaStack( ArithExceptErr, theObj, PC, sig);
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

#endif /* UNIX, !sun4s, !crts */
/******************** END general UNIX handler ****************************/



/***************************** BEGIN crts/b2c *****************************/
#ifdef crts
void BetaSignalHandler (long sig)
{
  fprintf(output, "\nBetaSignalHandler: Caught signal %d. Exiting.\n", sig);
  BetaExit(1);
}
#endif /* crts */
/***************************** END crts/b2c *******************************/



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

  
  /* Set StackEnd to the stack pointer just before trap. */
#ifndef MT
  StackEnd = (long *) ucon->uc_mcontext.gregs[REG_SP];
#endif
  PC = (long *) ucon->uc_mcontext.gregs[REG_PC];

#ifndef MT
  DEBUG_VALHALLA(fprintf(output,"BetaSignalHandler: StackEnd set to 0x%x\n",(int) StackEnd));
#endif /* MT */

  /* Try to fetch the address of current Beta object from i0.*/
  theCell = casthandle(Object) &(cast(RegWin)ucon->uc_mcontext.gregs[REG_SP])->i0;
  if( inIOA( *theCell)) if( isObject( *theCell)) theObj  = *theCell;

  switch(sig){
  case SIGFPE: 
    switch(info->si_code){
    case FPE_INTDIV: /* div by zero */
      todo=DisplayBetaStack( ZeroDivErr, theObj, PC, sig); break;
    default: /* arithmetic exception */
      todo=DisplayBetaStack( ArithExceptErr, theObj, PC, sig);
    }
    break;
  case SIGEMT:
    todo=DisplayBetaStack( EmulatorTrapErr, theObj, PC, sig); break;
  case SIGILL: /* Illegal instruction or trap */
    switch(info->si_code){
    case ILL_ILLTRP:
      switch(info->si_trapno-17){
      case 0x80: /* Solaris 2.3, 2.4, 2.5 */
      case 0x100: /* Solaris 2.5.1 */
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
  case EXCEPTION_ARRAY_BOUNDS_EXCEEDED:
    todo=DisplayBetaStack( RepRangeErr, theObj, PC, sig);
  case EXCEPTION_INT_DIVIDE_BY_ZERO:
    todo=DisplayBetaStack( ZeroDivErr, theObj, PC, sig); break;
  case EXCEPTION_ILLEGAL_INSTRUCTION:
  case EXCEPTION_PRIV_INSTRUCTION:
    todo=DisplayBetaStack( IllegalInstErr, theObj, PC, sig); break;
  case EXCEPTION_FLT_DENORMAL_OPERAND:
  case EXCEPTION_FLT_INEXACT_RESULT:
  case EXCEPTION_FLT_OVERFLOW:
  case EXCEPTION_FLT_UNDERFLOW:
  case EXCEPTION_FLT_STACK_CHECK:
    todo=DisplayBetaStack( UnorderedFval, theObj, PC, sig); break;
  case EXCEPTION_FLT_DIVIDE_BY_ZERO:
  case EXCEPTION_FLT_INVALID_OPERATION:
    todo=DisplayBetaStack( ArithExceptErr, theObj, PC, sig); break;
  default:
    todo=DisplayBetaStack( UnknownSigErr, theObj, PC, sig);  
  }
  
  if (!todo) BetaExit(1);
  
  return EXCEPTION_CONTINUE_SEARCH;
}

/* beta_main: called from _AttBC */
void beta_main(void (*AttBC)(struct Component *), struct Component *comp)
{
  /* enable floating point exceptions */
#ifdef nti_ms
  _controlfp(_EM_INVALID   | _EM_INEXACT | _EM_DENORMAL | _EM_OVERFLOW | 
	     _EM_UNDERFLOW | _EM_ZERODIVIDE, _MCW_EM);
#else
  _control87(EM_INVALID   | EM_INEXACT | EM_DENORMAL | EM_OVERFLOW | 
	     EM_UNDERFLOW | EM_ZERODIVIDE, MCW_EM);
#endif

  /* Set up structured exception handling for rest of execution */
  __try 
    { 
      /* Start BETA execution */
      AttBC(comp);
    }
  __except ( BetaSignalHandler( GetExceptionInformation()))
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
  case floatingPointException:
    todo=DisplayBetaStack( ArithExceptErr, theObj, PC, sig); break;
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
#if defined(UNIX) || defined(crts)
  { /* Setup signal handles for the Beta system */
#ifdef SIGTRAP
#ifdef sgi
    signal( SIGTRAP, (void (*)(int))BetaSignalHandler);
#endif
#if (defined(RTDEBUG) && defined(linux))
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
#endif /* UNIX || crts */
  
#else /* sun4s */
  
  /* This is solaris */
  
#ifdef MT
  SetupVirtualTimerHandler(100000); /* interrupt every 0.1 second */
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
