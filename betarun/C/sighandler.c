/*
 * BETA RUNTIME SYSTEM, Copyright (C) 1991 Mjolner Informatics Aps.
 * Mod: $RCSfile: sighandler.c,v $, rel: %R%, date: $Date: 1991-01-30 10:55:30 $, SID: $Revision: 1.1 $
 * by Lars Bak
 */
#include "beta.h"

void SignalHandler(sig, code, scp, addr)
  int sig, code;
  struct sigcontext *scp;
  char *addr;
{
  handle(Object) theCell;
  ref(Object)    theObj = 0;


  /* Set StackEnd to the stack pointer just before trap. */
  StackEnd = (long *) scp->sc_sp;

#ifdef sun-3
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

#ifdef hpux
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

