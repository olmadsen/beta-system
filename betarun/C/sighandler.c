/*
 * BETA RUNTIME SYSTEM, Copyright (C) 1991-93 Mjolner Informatics Aps.
 * sighandler.c
 * by Lars Bak, Peter Andersen, Peter Orbaek and Tommy Thorn
 */
#include "beta.h"

#ifdef UNIX
#include <signal.h>
#endif /* UNIX */

#ifdef linux
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
      DisplayBetaStack( ZeroDivErr, theObj, PC); break;
    default: /* arithmetic exception */
      DisplayBetaStack( ArithExceptErr, theObj, PC);
    }
    break;
  case SIGEMT:
    DisplayBetaStack( EmulatorTrapErr, theObj, PC); break;
  case SIGILL: /* Illegal instruction or trap */
    if (info->_data._fault._trapno - 0x80 == 17)
      /* tle 17 trap => ref none */
      DisplayBetaStack( RefNoneErr, theObj, PC);
    else
      DisplayBetaStack( IllegalInstErr, theObj, PC);
    break;
  case SIGBUS: /* Bus error */
    DisplayBetaStack( BusErr, theObj, PC); break;
  case SIGSEGV: /* Segmentation fault */
    DisplayBetaStack( SegmentationErr, theObj, PC); break;
  default:  /* Unknown signal */
    DisplayBetaStack( UnknownSigErr, theObj, PC);  
  }

}
  
/***** END sun4s ****/

#else /* sun4s */

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

#ifdef linux
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
  handle(Object) theCell;
  ref(Object)    theObj = 0;
  long *PC;

  /* Setup signal handles for the Beta system */
  signal( SIGFPE,  ExitHandler);
  signal( SIGILL,  ExitHandler);
  signal( SIGBUS,  ExitHandler);
  signal( SIGSEGV, ExitHandler);
#ifdef SIGEMT
  signal( SIGEMT,  ExitHandler);
#endif
#ifdef apollo
  signal( SIGINT,  ExitHandler);
  signal( SIGQUIT, ExitHandler);
#endif

  /* Set StackEnd to the stack pointer just before trap. */
#ifndef linux
  StackEnd = (long *) scp->sc_sp;
#ifndef hppa
  PC = (long *) scp->sc_pc;
#endif /* hppa */
#endif /* linux */

#ifdef sun3
  /* Try to fetch the address of current Beta object in a0.*/
  theCell = (handle(Object)) (((long) scp) - ((long) 24));
  if( inIOA( *theCell)) if( isObject( *theCell)) theObj  = *theCell;

  switch( sig){
    case SIGFPE: 
      switch(code){
      case FPE_TRAPV_TRAP:
	DisplayBetaStack( RefNoneErr, theObj, PC); break;
      case FPE_CHKINST_TRAP:
	DisplayBetaStack( RepRangeErr, theObj, PC); break;
      case FPE_INTDIV_TRAP:
	DisplayBetaStack( ZeroDivErr, theObj, PC); break;
      default:
        DisplayBetaStack( ArithExceptErr, theObj, PC);
      }
      break;
    case SIGEMT:
      DisplayBetaStack( EmulatorTrapErr, theObj, PC); break;
    case SIGILL:
      DisplayBetaStack( IllegalInstErr, theObj, PC); break;
    case SIGBUS:
      DisplayBetaStack( BusErr, theObj, PC); break;
    case SIGSEGV:
      DisplayBetaStack( SegmentationErr, theObj, PC); break;
    default: 
      DisplayBetaStack( UnknownSigErr, theObj, PC);  
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
      DisplayBetaStack( ZeroDivErr, theObj, PC); break;
    default: /* arithmetic exception */
      DisplayBetaStack( ArithExceptErr, theObj, PC);
    }
    break;
  case SIGEMT:
    DisplayBetaStack( EmulatorTrapErr, theObj, PC); break;
  case SIGILL: /* Illegal instruction of trap */
    switch (code){
    case ILL_TRAP_FAULT(17): /* tle 17 trap => ref none */
      DisplayBetaStack( RefNoneErr, theObj, PC);
      break;
    default:
      DisplayBetaStack( IllegalInstErr, theObj, PC);
      break;
    }
    break;
  case SIGBUS: /* Bus error */
    DisplayBetaStack( BusErr, theObj, PC); break;
  case SIGSEGV: /* Segmentation fault */
    DisplayBetaStack( SegmentationErr, theObj, PC); break;
  default:  /* Unknown signal */
    DisplayBetaStack( UnknownSigErr, theObj, PC);  
  }
#endif

#ifdef linux

  theObj = cast(Object) scp.edx;
  if ( ! (inIOA(theObj) && isObject (theObj)))
    theObj  = 0;
  PC = (long *) scp.eip;
  StackEnd = (long *) scp.esp_at_signal;

  switch(sig){
    case SIGFPE: 
      DisplayBetaStack( ArithExceptErr, theObj, PC); break;
    case SIGILL:
      DisplayBetaStack( IllegalInstErr, theObj, PC); break;
    case SIGBUS:
      DisplayBetaStack( BusErr, theObj, PC); break;
    case SIGSEGV:
      DisplayBetaStack( SegmentationErr, theObj, PC); break;
    default: 
      DisplayBetaStack( UnknownSigErr, theObj, PC);  
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
        DisplayBetaStack(ZeroDivErr, theObj, PC);
      else
        DisplayBetaStack( ArithExceptErr, theObj, PC);  
      break;
    case SIGEMT:
      DisplayBetaStack( EmulatorTrapErr, theObj, PC); break;
    case SIGILL:
      switch(code){
      case 6: /* Only documented in 'man signal' */
	/* if code == 6 then it has been a chk instruction => index error. */
        DisplayBetaStack( RepRangeErr, theObj, PC);
	break;
      case 7: /* Only documented in 'man signal' */
	/* if code == 7 then it has been a trap instruction => reference is none. */
        DisplayBetaStack( RefNoneErr, theObj, PC);
	break;
      default:
        DisplayBetaStack( IllegalInstErr, theObj, PC);
        break;
      }
      break;
    case SIGBUS:
      DisplayBetaStack( BusErr, theObj, PC); break;
    case SIGSEGV:
      DisplayBetaStack( SegmentationErr, theObj, PC); break;
    default: 
      DisplayBetaStack( UnknownSigErr, theObj, PC);  
  }
#endif

#ifdef hppa
  /* Try to fetch the address of current Beta object in %r3 (This).*/
  /* See /usr/include/sys/signal.h and /usr/include/machine/save_state.h */
  PC = (long *) scp->sc_ret1;
  theCell = (handle(Object)) &scp->sc_gr3;
  if( inIOA( *theCell))
    if( isObject( *theCell)) theObj  = *theCell;

  switch( sig){
    case SIGFPE:
      DisplayBetaStack( ArithExceptErr, theObj, PC);
      break;
    case SIGEMT:
      DisplayBetaStack( EmulatorTrapErr, theObj, PC); break;
    case SIGILL:
      DisplayBetaStack( IllegalInstErr, theObj, PC);
      break;
    case SIGBUS:
      DisplayBetaStack( BusErr, theObj, PC); break;
    case SIGSEGV:
      DisplayBetaStack( SegmentationErr, theObj, PC); break;
    default:
      DisplayBetaStack( UnknownSigErr, theObj, PC);
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
	DisplayBetaStack( RepRangeErr, theObj, PC); break;
      case FPE_INTDIV_TRAP:
	DisplayBetaStack( ZeroDivErr, theObj, PC); break;
      default:
        DisplayBetaStack( ArithExceptErr, theObj, PC);
      }
      break;
    case SIGEMT:
      DisplayBetaStack( EmulatorTrapErr, theObj, PC); break;
    case SIGILL:
      DisplayBetaStack( IllegalInstErr, theObj, PC); break;
    case SIGBUS:
      DisplayBetaStack( BusErr, theObj, PC); break;
    case SIGSEGV:
      DisplayBetaStack( SegmentationErr, theObj, PC); break;
    default: 
      DisplayBetaStack( UnknownSigErr, theObj, PC);  
  }
#endif

  BetaExit(-1);
}

#endif /* sun4s */
