/*
 * BETA RUNTIME SYSTEM, Copyright (C) 1991-93 Mjolner Informatics Aps.
 * sighandler.c
 * by Lars Bak, Peter Andersen, Peter Orbaek and Tommy Thorn
 */
#include "beta.h"

#ifdef UNIX
#include <signal.h>
#endif

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
      case FPE_CHKINST_TRAP:
	DisplayBetaStack( RepRangeErr, theObj); break;
      case FPE_INTDIV_TRAP:
	DisplayBetaStack( ZeroDivErr, theObj); break;
      default:
	fprintf(stderr, "code: %d", code); fflush(stderr);
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
      /*case FPE_CHKINST_TRAP: // Index error (chk2) //
       *DisplayBetaStack( RepRangeErr, theObj); break;
       */
      case FPE_INTDIV_TRAP: /* div by zero */
	DisplayBetaStack( ZeroDivErr, theObj); break;
      default: /* arithmetic exception */
        DisplayBetaStack( ArithExceptErr, theObj);
      }
      break;
    case SIGEMT:
      DisplayBetaStack( EmulatorTrapErr, theObj); break;
    case SIGILL: /* Illegal instruction */
      DisplayBetaStack( IllegalInstErr, theObj); break;
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
      if( code == 5 )
        DisplayBetaStack(ZeroDivErr, theObj);
      else
        DisplayBetaStack( ArithExceptErr, theObj);  
      break;
    case SIGEMT:
      DisplayBetaStack( EmulatorTrapErr, theObj); break;
    case SIGILL:
      switch(code){
      case 6:
	/* if code == 6 then it has been a chk instruction => index error. */
        DisplayBetaStack( RepRangeErr, theObj);
	break;
      case 7:
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

