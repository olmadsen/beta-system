/*
 * BETA RUNTIME SYSTEM, Copyright (C) 1991-94 Mjolner Informatics Aps.
 * sighandler.c
 * by Lars Bak, Peter Andersen, Peter Orbaek, Tommy Thorn, Jacob Seligmann and S|ren Brandt
 */
#include "beta.h"

#ifdef crts
void BetaSignalHandler (long sig)
{
  fprintf(output, "\nBetaSignalHandler: Caught signal %d. Exiting.\n", sig);
  BetaExit(1);
}
#endif

#ifdef sun4s

/****** BEGIN sun4s *****/

#ifdef MT

#include <errno.h>

struct S_PreemptionLevel {
  unsigned lock;
  unsigned value;
  unsigned inGC;
};

struct S_PreemptionLevel PreemptionLevel;

void SetupVirtualTimer(unsigned usec);
int AlarmOccured = 0;
void AlarmHandler(int sig, siginfo_t *sip, void *uap)
{
  AlarmOccured++;
  
  /* FIXME: should be a tryLock. */
  if (!PreemptionLevel.lock && !PreemptionLevel.value) { 
    if (!PreemptionLevel.inGC) { /* We cannot reset IOALimit while GC'ing */
      IOALimit = 0;
      IOALimitReg = 0;
      DEBUG_MT(fprintf(output,
		       "IOALimit=0x%x, IOALimitReg=0x%x\n",
		       (int)IOALimit,
		       (int)IOALimitReg));
    }
  }
}

void SetupVirtualTimerHandler(unsigned usec)
{
  struct sigaction act;

  PreemptionLevel.lock = 0;
  PreemptionLevel.value = 1;
  act.sa_handler = NULL;            /* Unused */
  act.sa_sigaction = &AlarmHandler; /* the handler */
  act.sa_flags = SA_SIGINFO;        /* Use sa_sigaction, not sa_handler */ 
  sigemptyset(&act.sa_mask);        /* Block no other signals in handler */

  if (sigaction(SIGVTALRM, &act, NULL)) {
    printf("sigaction failed. Errno=%d (%s)\n", errno, strerror(errno));
    BetaExit(1);
  }
  SetupVirtualTimer(usec);
}

void SetupVirtualTimer(unsigned usec)
{
  struct itimerval interval;

  /* setup timer tu trigger each usec microseconds */
  interval.it_value.tv_sec = 0;
  interval.it_value.tv_usec = usec;
  interval.it_interval.tv_sec = 0;
  interval.it_interval.tv_usec = usec;

  if (setitimer(ITIMER_VIRTUAL, &interval, NULL)) {
    printf("setitimer failed. Errno=%d (%s)\n", errno, strerror(errno));
    BetaExit(1);
  }  
}

#endif /* MT */

void ExitHandler(int sig)
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
  StackEnd = (long *) ucon->uc_mcontext.gregs[REG_SP];
  PC = (long *) ucon->uc_mcontext.gregs[REG_PC];

  DEBUG_VALHALLA(fprintf(output,"BetaSignalHandler: StackEnd set to 0x%x\n",(int) StackEnd));

  /* Try to fetch the address of current Beta object from i0.*/
  theCell = casthandle(Object) &(cast(RegWin)StackEnd)->i0;
  if( inIOA( *theCell)) if( isObject( *theCell)) theObj  = *theCell;

  switch( sig){
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
    if (info->_data._fault._trapno - 0x80 == 17)
      /* tle 17 trap => ref none */
      todo=DisplayBetaStack( RefNoneErr, theObj, PC, sig);
    else
      todo=DisplayBetaStack( IllegalInstErr, theObj, PC, sig);
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
  
/***** END sun4s ****/

#else /* sun4s */
#ifndef crts

/***** BetaSignalHandler: the one used for all but sun4s and crts *****/

#if (defined(linux) || defined(nti))
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

#if defined(linux) || defined(nti)
void BetaSignalHandler(long sig, struct sigcontext scp)
#else
void BetaSignalHandler(long sig, long code, struct sigcontext * scp, char *addr)
#endif
{
#if !(defined(linux) || defined(nti))
  handle(Object) theCell;
#endif /* !(linux || nti)*/
  ref(Object)    theObj = 0;
  long *PC;
  long todo = 0;

  DEBUG_CODE(fprintf(output, "\nBetaSignalHandler: Caught signal %d\n", (int)sig));

  /* Setup signal handles for the Beta system */
  signal( SIGFPE,  ExitHandler);
  signal( SIGILL,  ExitHandler);
#ifndef nti
  signal( SIGBUS,  ExitHandler);
#endif
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

#if defined(linux) || defined(nti)
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
#ifndef nti
  case SIGBUS:
    todo=DisplayBetaStack( BusErr, theObj, PC, sig); break;
#endif
#ifdef RTDEBUG
  case SIGINT: /* Interrupt */
    todo=DisplayBetaStack( InterruptErr, theObj, PC, sig); break;
#ifndef nti
  case SIGTRAP: 
    if ( (*((char*)PC-1)) == (char)0xcc ){
      /* int3 break */
      scp.eip -= 1; /* PC points just after int3 instruction */
      PC = (long *) scp.eip;
      DEBUG_VALHALLA(fprintf(output, "sighandler: adjusting PC to 0x%x\n", (int)PC));
    }
    todo=DisplayBetaStack( EmulatorTrapErr, theObj, PC, sig); break;
#endif
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
#endif /* defined(linux) || defined(nti) */

#if defined(hpux9mc)
  /* Try to fetch the address of current Beta object in a0.
   * The numbers 68 and 72 have been found ad hoc!
   */
#if 0
  fprintf(output, "BetaSignalHandler: &scp: 0x%x\n", (int)&scp);
  fprintf(output, "BetaSignalHandler: &scp+68: 0x%x\n", (int)&scp+72);
  fprintf(output, 
	  "BetaSignalHandler: *(&scp+68): 0x%x\n", 
	  (int)*(long *)((long)&scp+68));
#endif

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

#endif /* crts */
#endif /* sun4s */
