/*
 * BETA RUNTIME SYSTEM, Copyright (C) 1991-93 Mjolner Informatics Aps.
 * sighandler.c
 * by Lars Bak, Peter Andersen, Peter Orbaek and Tommy Thorn
 */
#include "beta.h"

#ifdef UNIX
#include <signal.h>
#endif

#ifdef sun4s
#include <siginfo.h>
#include <sys/regset.h>
#include <sys/ucontext.h>

void ExitHandler (sig)
  long sig;
{
  BetaExit(-1);
}

void SignalHandler (sig, info, ucon)
  long sig;
  siginfo_t *info;
  ucontext_t *ucon;
{
  handle(Object) theCell;
  ref(Object)    theObj = 0;

  /* Setup signal handlers for the Beta system */
  signal( SIGFPE,  ExitHandler);
  signal( SIGILL,  ExitHandler);
  signal( SIGBUS,  ExitHandler);
  signal( SIGSEGV, ExitHandler);
  signal( SIGEMT,  ExitHandler);

  
  /* Set StackEnd to the stack pointer just before trap. */
  StackEnd = (long *) ucon->uc_mcontext.gregs[REG_SP];
  
  /* Try to fetch the address of current Beta object from i0.*/
  theCell = casthandle(Object) &(cast(RegWin)StackEnd)->i0;
  if( inIOA( *theCell)) if( isObject( *theCell)) theObj  = *theCell;

  switch( sig){
  case SIGFPE: 
    switch(info->si_code){
    case FPE_INTDIV: /* div by zero */
      DisplayBetaStack( ZeroDivErr, theObj); break;
    default: /* arithmetic exception */
      DisplayBetaStack( ArithExceptErr, theObj);
    }
    break;
  case SIGEMT:
    DisplayBetaStack( EmulatorTrapErr, theObj); break;
  case SIGILL: /* Illegal instruction or trap */
    if (info->_data._fault._trapno - 0x80 == 17)
      /* tle 17 trap => ref none */
      DisplayBetaStack( RefNoneErr, theObj);
    else
      DisplayBetaStack( IllegalInstErr, theObj);
    break;
  case SIGBUS: /* Bus error */
    DisplayBetaStack( BusErr, theObj); break;
  case SIGSEGV: /* Segmentation fault */
    DisplayBetaStack( SegmentationErr, theObj); break;
  default:  /* Unknown signal */
    DisplayBetaStack( UnknownSigErr, theObj);  
  }

}
  

#else

/* This procedure is called if a nasty signal is recieved
 * during execution of SignalHandler.
 * Please Exit nicely.
 */
static void ExitHandler(sig, code, scp, addr)
  long sig, code;
  struct sigcontext *scp;
  char *addr;
{ 
  BetaExit(-1); 
}

void SignalHandler(sig, code, scp, addr)
  long sig, code;
  struct sigcontext *scp;
  char *addr;
{
  handle(Object) theCell;
  ref(Object)    theObj = 0;

  /* Setup signal handles for the Beta system */
  signal( SIGFPE,  ExitHandler);
  signal( SIGILL,  ExitHandler);
  signal( SIGBUS,  ExitHandler);
  signal( SIGSEGV, ExitHandler);
  signal( SIGEMT,  ExitHandler);
#ifdef apollo
  signal( SIGINT,  ExitHandler);
  signal( SIGQUIT, ExitHandler);
#endif

  /* Set StackEnd to the stack pointer just before trap. */
  StackEnd = (long *) scp->sc_sp;

#ifdef sun3
  /* Try to fetch the address of current Beta object in a0.*/
  theCell = (handle(Object)) (((long) scp) - ((long) 24));
  if( inIOA( *theCell)) if( isObject( *theCell)) theObj  = *theCell;

  switch( sig){
    case SIGFPE: 
      switch(code){
      case FPE_TRAPV_TRAP:
	DisplayBetaStack( RefNoneErr, theObj); break;
      case FPE_CHKINST_TRAP:
	DisplayBetaStack( RepRangeErr, theObj); break;
      case FPE_INTDIV_TRAP:
	DisplayBetaStack( ZeroDivErr, theObj); break;
      default:
        DisplayBetaStack( ArithExceptErr, theObj);
      }
      break;
    case SIGEMT:
      DisplayBetaStack( EmulatorTrapErr, theObj); break;
    case SIGILL:
      DisplayBetaStack( IllegalInstErr, theObj); break;
    case SIGBUS:
      DisplayBetaStack( BusErr, theObj); break;
    case SIGSEGV:
      DisplayBetaStack( SegmentationErr, theObj); break;
    default: 
      DisplayBetaStack( UnknownSigErr, theObj);  
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
      DisplayBetaStack( ZeroDivErr, theObj); break;
    default: /* arithmetic exception */
      DisplayBetaStack( ArithExceptErr, theObj);
    }
    break;
  case SIGEMT:
    DisplayBetaStack( EmulatorTrapErr, theObj); break;
  case SIGILL: /* Illegal instruction of trap */
    switch (code){
    case ILL_TRAP_FAULT(17): /* tle 17 trap => ref none */
      DisplayBetaStack( RefNoneErr, theObj);
      break;
    default:
      DisplayBetaStack( IllegalInstErr, theObj);
      break;
    }
    break;
  case SIGBUS: /* Bus error */
    DisplayBetaStack( BusErr, theObj); break;
  case SIGSEGV: /* Segmentation fault */
    DisplayBetaStack( SegmentationErr, theObj); break;
  default:  /* Unknown signal */
    DisplayBetaStack( UnknownSigErr, theObj);  
  }
#endif

#if defined(hpux) && !defined(hppa)
  /* Try to fetch the address of current Beta object in a0.*/
  theCell = (handle(Object)) (((long) &scp) + ((long) 72));
  if( inIOA( *theCell))
    if( isObject( *theCell)) theObj  = *theCell;

  switch( sig){
    case SIGFPE: 
      if( code == 5 ) /* Only documented in 'man signal' */
        DisplayBetaStack(ZeroDivErr, theObj);
      else
        DisplayBetaStack( ArithExceptErr, theObj);  
      break;
    case SIGEMT:
      DisplayBetaStack( EmulatorTrapErr, theObj); break;
    case SIGILL:
      switch(code){
      case 6: /* Only documented in 'man signal' */
	/* if code == 6 then it has been a chk instruction => index error. */
        DisplayBetaStack( RepRangeErr, theObj);
	break;
      case 7: /* Only documented in 'man signal' */
	/* if code == 7 then it has been a trap instruction => reference is none. */
        DisplayBetaStack( RefNoneErr, theObj);
	break;
      default:
        DisplayBetaStack( IllegalInstErr, theObj);
        break;
      }
      break;
    case SIGBUS:
      DisplayBetaStack( BusErr, theObj); break;
    case SIGSEGV:
      DisplayBetaStack( SegmentationErr, theObj); break;
    default: 
      DisplayBetaStack( UnknownSigErr, theObj);  
  }
#endif

#ifdef hppa
  /* Try to fetch the address of current Beta object in %r3 (This).*/
  theCell = (handle(Object)) &scp->sc_gr3;
  if( inIOA( *theCell))
    if( isObject( *theCell)) theObj  = *theCell;

  switch( sig){
    case SIGFPE:
      DisplayBetaStack( ArithExceptErr, theObj);
      break;
    case SIGEMT:
      DisplayBetaStack( EmulatorTrapErr, theObj); break;
    case SIGILL:
      DisplayBetaStack( IllegalInstErr, theObj);
      break;
    case SIGBUS:
      DisplayBetaStack( BusErr, theObj); break;
    case SIGSEGV:
      DisplayBetaStack( SegmentationErr, theObj); break;
    default:
      DisplayBetaStack( UnknownSigErr, theObj);
  }
#endif

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
	DisplayBetaStack( RepRangeErr, theObj); break;
      case FPE_INTDIV_TRAP:
	DisplayBetaStack( ZeroDivErr, theObj); break;
      default:
        DisplayBetaStack( ArithExceptErr, theObj);
      }
      break;
    case SIGEMT:
      DisplayBetaStack( EmulatorTrapErr, theObj); break;
    case SIGILL:
      DisplayBetaStack( IllegalInstErr, theObj); break;
    case SIGBUS:
      DisplayBetaStack( BusErr, theObj); break;
    case SIGSEGV:
      DisplayBetaStack( SegmentationErr, theObj); break;
    default: 
      DisplayBetaStack( UnknownSigErr, theObj);  
  }
#endif

  BetaExit(-1);
}

#endif /* sun4s */
