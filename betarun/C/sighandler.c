/*
 * BETA RUNTIME SYSTEM, Copyright (C) 1991-94 Mjolner Informatics Aps.
 * sighandler.c
 * by Lars Bak, Peter Andersen, Peter Orbaek, Tommy Thorn, and Jacob Seligmann
 */
#include "beta.h"

#ifdef crts
void BetaSignalHandler (sig)
  long sig;
{
  fprintf(output, "\nBetaSignalHandler: Caught signal %d. Exiting.\n", sig);
  exit(1);
}
#endif

#if defined(UNIX) || defined(nti)
#include <signal.h>
#endif /* UNIX || nti */

#ifdef sun4s

/****** BEGIN sun4s *****/

#include <siginfo.h>
#include <sys/regset.h>
#include <sys/ucontext.h>

void ExitHandler (sig)
  long sig;
{
  BetaExit(-1);
}

void BetaSignalHandler (sig, info, ucon)
  long sig;
  siginfo_t *info;
  ucontext_t *ucon;
{
  handle(Object) theCell;
  ref(Object)    theObj = 0;
  long *PC;

  /* Setup signal handlers for the Beta system */
  signal( SIGFPE,  ExitHandler);
  signal( SIGILL,  ExitHandler);
  signal( SIGBUS,  ExitHandler);
  signal( SIGSEGV, ExitHandler);
  signal( SIGEMT,  ExitHandler);

  
  /* Set StackEnd to the stack pointer just before trap. */
  StackEnd = (long *) ucon->uc_mcontext.gregs[REG_SP];
  PC = (long *) ucon->uc_mcontext.gregs[REG_PC];

  /* Try to fetch the address of current Beta object from i0.*/
  theCell = casthandle(Object) &(cast(RegWin)StackEnd)->i0;
  if( inIOA( *theCell)) if( isObject( *theCell)) theObj  = *theCell;

  switch( sig){
  case SIGFPE: 
    switch(info->si_code){
    case FPE_INTDIV: /* div by zero */
      DisplayBetaStack( ZeroDivErr, theObj, PC, sig); break;
    default: /* arithmetic exception */
      DisplayBetaStack( ArithExceptErr, theObj, PC, sig);
    }
    break;
  case SIGEMT:
    DisplayBetaStack( EmulatorTrapErr, theObj, PC, sig); break;
  case SIGILL: /* Illegal instruction or trap */
    if (info->_data._fault._trapno - 0x80 == 17)
      /* tle 17 trap => ref none */
      DisplayBetaStack( RefNoneErr, theObj, PC, sig);
    else
      DisplayBetaStack( IllegalInstErr, theObj, PC, sig);
    break;
  case SIGBUS: /* Bus error */
    DisplayBetaStack( BusErr, theObj, PC, sig); break;
  case SIGSEGV: /* Segmentation fault */
    DisplayBetaStack( SegmentationErr, theObj, PC, sig); break;
  default:  /* Unknown signal */
    DisplayBetaStack( UnknownSigErr, theObj, PC, sig);  
  }

}
  
/***** END sun4s ****/

#else /* sun4s */
#ifndef crts

/* This procedure is called if a nasty signal is recieved
 * during execution of BetaSignalHandler.
 * Please Exit nicely.
 */
static void ExitHandler(sig, code, scp, addr)
  long sig, code;
  struct sigcontext *scp;
  char *addr;
{ 
  BetaExit(-1); 
}

#if defined(linux) || defined(nti)
void BetaSignalHandler(sig, scp)
     long sig;
     struct sigcontext scp;
#else
void BetaSignalHandler(sig, code, scp, addr)
     long sig, code;
     struct sigcontext *scp;
     char *addr;
#endif
{
#if !(defined(linux) || defined(nti))
  handle(Object) theCell;
#endif /* !(linux || nti)*/
  ref(Object)    theObj = 0;
  long *PC;

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
#ifdef apollo
  signal( SIGINT,  ExitHandler);
  signal( SIGQUIT, ExitHandler);
#endif

  /* Set StackEnd to the stack pointer just before trap. */
#if !(defined(linux) || defined(nti))
  StackEnd = (long *) scp->sc_sp;
#ifndef hppa
  PC = (long *) scp->sc_pc;
#endif /* !hppa */
#endif /* !(linux || nti) */

#ifdef sun3
  /* Try to fetch the address of current Beta object in a0.*/
  theCell = (handle(Object)) (((long) scp) - ((long) 24));
  if( inIOA( *theCell)) if( isObject( *theCell)) theObj  = *theCell;

  switch( sig){
    case SIGFPE: 
      switch(code){
      case FPE_TRAPV_TRAP:
	DisplayBetaStack( RefNoneErr, theObj, PC, sig); break;
      case FPE_CHKINST_TRAP:
	DisplayBetaStack( RepRangeErr, theObj, PC, sig); break;
      case FPE_INTDIV_TRAP:
	DisplayBetaStack( ZeroDivErr, theObj, PC, sig); break;
      default:
        DisplayBetaStack( ArithExceptErr, theObj, PC, sig);
      }
      break;
    case SIGEMT:
      DisplayBetaStack( EmulatorTrapErr, theObj, PC, sig); break;
    case SIGILL:
      DisplayBetaStack( IllegalInstErr, theObj, PC, sig); break;
    case SIGBUS:
      DisplayBetaStack( BusErr, theObj, PC, sig); break;
    case SIGSEGV:
      DisplayBetaStack( SegmentationErr, theObj, PC, sig); break;
    default: 
      DisplayBetaStack( UnknownSigErr, theObj, PC, sig);  
  }
#endif

#ifdef sparc
  /* Try to fetch the address of current Beta object from i0.*/
  theCell = casthandle(Object) &(cast(RegWin)scp->sc_sp)->i0;
  if( inIOA( *theCell)) if( isObject( *theCell)) theObj  = *theCell;

  switch( sig){
  case SIGFPE: 
    switch(code){
    case FPE_INTDIV_TRAP: /* div by zero */
      DisplayBetaStack( ZeroDivErr, theObj, PC, sig); break;
    default: /* arithmetic exception */
      DisplayBetaStack( ArithExceptErr, theObj, PC, sig);
    }
    break;
  case SIGEMT:
    DisplayBetaStack( EmulatorTrapErr, theObj, PC, sig); break;
  case SIGILL: /* Illegal instruction of trap */
    switch (code){
    case ILL_TRAP_FAULT(17): /* tle 17 trap => ref none */
      DisplayBetaStack( RefNoneErr, theObj, PC, sig);
      break;
    default:
      DisplayBetaStack( IllegalInstErr, theObj, PC, sig);
      break;
    }
    break;
  case SIGBUS: /* Bus error */
    DisplayBetaStack( BusErr, theObj, PC, sig); break;
  case SIGSEGV: /* Segmentation fault */
    DisplayBetaStack( SegmentationErr, theObj, PC, sig); break;
  default:  /* Unknown signal */
    DisplayBetaStack( UnknownSigErr, theObj, PC, sig);  
  }
#endif

#if defined(linux) || defined(nti)
  theObj = cast(Object) scp.edx;
  if ( ! (inIOA(theObj) && isObject (theObj)))
    theObj  = 0;
  PC = (long *) scp.eip;
  StackEnd = (long *) scp.esp_at_signal;

  switch(sig){
    case SIGFPE: 
      DisplayBetaStack( ArithExceptErr, theObj, PC, sig); break;
    case SIGILL:
      DisplayBetaStack( IllegalInstErr, theObj, PC, sig); break;
#ifndef nti
    case SIGBUS:
      DisplayBetaStack( BusErr, theObj, PC, sig); break;
#endif
    case SIGSEGV:
      if (scp.trapno == 5) /* Interrupt 5 generated by boundl */
	DisplayBetaStack(RepRangeErr, theObj, PC, sig);
      else
	DisplayBetaStack(SegmentationErr, theObj, PC, sig); 
      break;
    default: 
      DisplayBetaStack( UnknownSigErr, theObj, PC, sig);  
  }
#endif /* defined(linux) || defined(nti) */

#if defined(hpux) && !defined(hppa)
  /* Try to fetch the address of current Beta object in a0.*/
  theCell = (handle(Object)) (((long) &scp) + ((long) 72));
  if( inIOA( *theCell))
    if( isObject( *theCell)) theObj  = *theCell;

  switch( sig){
    case SIGFPE: 
      if( code == 5 ) /* Only documented in 'man signal' */
        DisplayBetaStack(ZeroDivErr, theObj, PC, sig);
      else
        DisplayBetaStack( ArithExceptErr, theObj, PC, sig);  
      break;
    case SIGEMT:
      DisplayBetaStack( EmulatorTrapErr, theObj, PC, sig); break;
    case SIGILL:
      switch(code){
      case 6: /* Only documented in 'man signal' */
	/* if code == 6 then it has been a chk instruction => index error. */
        DisplayBetaStack( RepRangeErr, theObj, PC, sig);
	break;
      case 7: /* Only documented in 'man signal' */
	/* if code == 7 then it has been a trap instruction => reference is none. */
        DisplayBetaStack( RefNoneErr, theObj, PC, sig);
	break;
      default:
        DisplayBetaStack( IllegalInstErr, theObj, PC, sig);
        break;
      }
      break;
    case SIGBUS:
      DisplayBetaStack( BusErr, theObj, PC, sig); break;
    case SIGSEGV:
      DisplayBetaStack( SegmentationErr, theObj, PC, sig); break;
    default: 
      DisplayBetaStack( UnknownSigErr, theObj, PC, sig);  
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
      DisplayBetaStack( ArithExceptErr, theObj, PC, sig);
      break;
    case SIGEMT:
      DisplayBetaStack( EmulatorTrapErr, theObj, PC, sig); break;
    case SIGILL:
      DisplayBetaStack( IllegalInstErr, theObj, PC, sig);
      break;
    case SIGBUS:
      DisplayBetaStack( BusErr, theObj, PC, sig); break;
    case SIGSEGV:
      DisplayBetaStack( SegmentationErr, theObj, PC, sig); break;
    default:
      DisplayBetaStack( UnknownSigErr, theObj, PC, sig);
  }
#endif /* hppa */

#ifdef apollo
  /* Try to fetch the address of current Beta object in a0.*/
  theCell = (handle(Object)) (((long) scp) - ((long) 24));
  if( inIOA( *theCell)) if( isObject( *theCell)) theObj  = *theCell;

  switch( sig){
    case SIGQUIT:
      break;
    case SIGINT:
      break;
    case SIGFPE: 
      switch(code){
      case FPE_SUBRNG_TRAP:
	DisplayBetaStack( RepRangeErr, theObj, PC, sig); break;
      case FPE_INTDIV_TRAP:
	DisplayBetaStack( ZeroDivErr, theObj, PC, sig); break;
      default:
        DisplayBetaStack( ArithExceptErr, theObj, PC, sig);
      }
      break;
    case SIGEMT:
      DisplayBetaStack( EmulatorTrapErr, theObj, PC, sig); break;
    case SIGILL:
      DisplayBetaStack( IllegalInstErr, theObj, PC, sig); break;
    case SIGBUS:
      DisplayBetaStack( BusErr, theObj, PC, sig); break;
    case SIGSEGV:
      DisplayBetaStack( SegmentationErr, theObj, PC, sig); break;
    default: 
      DisplayBetaStack( UnknownSigErr, theObj, PC, sig);  
  }
#endif /* apollo */

  BetaExit(-1);
}

#endif /* crts */
#endif /* sun4s */
