/*
 * BETA RUNTIME SYSTEM, Copyright (C) 1991 Mjolner Informatics Aps.
 * Mod: $Id: sighandler.c,v 1.8 1992-09-03 12:54:29 beta Exp $
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
  int sig, code;
  struct sigcontext *scp;
  char *addr;
{ 
  BetaExit(-1); 
}

void SignalHandler(sig, code, scp, addr)
  int sig, code;
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
	DisplayBetaStack( -3, theObj); break;
      case FPE_INTDIV_TRAP:
	DisplayBetaStack( -10, theObj); break;
      default:
        DisplayBetaStack( -4, theObj);
      }
      break;
    case SIGILL:
      DisplayBetaStack( -30, theObj); break;
    case SIGBUS:
      DisplayBetaStack( -31, theObj); break;
    case SIGSEGV:
      DisplayBetaStack( -32, theObj); break;
    default: 
      DisplayBetaStack( -100, theObj);  
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
       *DisplayBetaStack( -3, theObj); break;
       */
      case FPE_INTDIV_TRAP: /* div by zero */
	DisplayBetaStack( -10, theObj); break;
      default: /* arithmetic exception */
        DisplayBetaStack( -4, theObj);
      }
      break;
    case SIGILL: /* Illegal instruction */
      DisplayBetaStack( -30, theObj); break;
    case SIGBUS: /* Bus error */
      DisplayBetaStack( -31, theObj); break;
    case SIGSEGV: /* Segmentation fault */
      DisplayBetaStack( -32, theObj); break;
    default:  /* Unknown signal */
      DisplayBetaStack( -100, theObj);  
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
        DisplayBetaStack(-10, theObj);
      else
        DisplayBetaStack( -4, theObj);  
      break;
    case SIGILL:
      /* if code == 6 then it has been a chk instruction => index error. */
      if( code == 6 )
        DisplayBetaStack( -3, theObj);
      else
        DisplayBetaStack( -30, theObj);        
      break;
    case SIGBUS:
      DisplayBetaStack( -31, theObj); break;
    case SIGSEGV:
      DisplayBetaStack( -32, theObj); break;
    default: 
      DisplayBetaStack( -100, theObj);  
  }
#endif

#ifdef hppa
  /* Try to fetch the address of current Beta object in %r3 (This).*/
  theCell = (handle(Object)) &scp->sc_gr3;
  if( inIOA( *theCell))
    if( isObject( *theCell)) theObj  = *theCell;

  switch( sig){
    case SIGFPE:
      DisplayBetaStack( -4, theObj);
      break;
    case SIGILL:
      DisplayBetaStack( -30, theObj);
      break;
    case SIGBUS:
      DisplayBetaStack( -31, theObj); break;
    case SIGSEGV:
      DisplayBetaStack( -32, theObj); break;
    default:
      DisplayBetaStack( -100, theObj);
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
	DisplayBetaStack( -3, theObj); break;
      case FPE_INTDIV_TRAP:
	DisplayBetaStack( -10, theObj); break;
      default:
        DisplayBetaStack( -4, theObj);
      }
      break;
    case SIGILL:
      DisplayBetaStack( -30, theObj); break;
    case SIGBUS:
      DisplayBetaStack( -31, theObj); break;
    case SIGSEGV:
      DisplayBetaStack( -32, theObj); break;
    default: 
      DisplayBetaStack( -100, theObj);  
  }
#endif

  BetaExit(-1);
}

