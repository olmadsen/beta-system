/*
 * BETA RUNTIME SYSTEM, Copyright (C) 1991-94 Mjolner Informatics Aps.
 * sighandler.c
 * by Lars Bak, Peter Andersen, Peter Orbaek, Tommy Thorn, 
 * Jacob Seligmann and S|ren Brandt
 */
#include "beta.h"

/***************************************************************************/
/************************ LOCAL INCLUDES and DEFINITIONS********************/
/***************************************************************************/
#include "rtsighandler.h"
#ifdef UNIX
#include <unistd.h>
#include "PException.h"
#endif /* UNIX */

/***************************************************************************/
/*************************** HELPER FUNCTIONS ******************************/
/***************************************************************************/

#ifdef UNIX
static void NotifySignalDuringDump(int sig)
{
  BetaErr err;
  switch ((int)sig){
  case SIGINT: err=InterruptErr; break;
  case SIGSEGV: err=SegmentationErr; break;
  case SIGBUS: err=BusErr; break;
  case SIGILL: err=IllegalInstErr; break;
  default: err=UnknownSigErr;
  }
  NotifyErrorDuringDump((BetaErr)isMakingDump, err);
}

/* This procedure is called if a nasty signal is received
 * during execution of BetaSignalHandler.
 * Exit nicely.
 */
static void ExitHandler(int sig)
{ 
  output = stderr;
  DEBUG_CODE({
    fprintf(output, "\nExitHandler: Caught signal %d", (int)sig);
    PrintSignal((int)sig);
    fprintf(output, " during signal handling.\n");
    fflush(output);
  });
  if (isMakingDump || isHandlingException) {
    NotifySignalDuringDump((int)sig);
  }
  BetaExit(1); 
}

static int HandleInterrupt(Object *theObj, pc_t pc, int sig)
{
#ifdef RTDEBUG
  return DisplayBetaStack( InterruptErr, theObj, pc, sig);
#else
  if (Info0){
    fprintf(stderr, "\n# Beta execution interrupted by user.\n");
  } 
  if (isMakingDump){
    fprintf(stderr, "# Creating dump. Please wait for this to complete.\n");
    fprintf(stderr, "# [To kill use: kill -9 %d].\n", (int)getpid());
    fflush(stderr);
    if (output != stderr){
      fprintf(output, "\n[User attempted interrupt].\n");
      fflush(output);
    }
    return 1;
  } else {
    BetaExit(0);
    return 0;
  }
#endif
}
#endif /* UNIX */

/*
 * Since valhalla may now trigger
 * GC in scripts evaluated in the context of debuggee, we have
 * to make sure that Reference registers are updated during these
 * GC's. So we fetch EDX, EDI, EBP and ESI from the scp and put them 
 * on a reference stack (which is GC'ed). We then put the (updated) values
 * back after completing DisplayBetaStack (which calls 
 * valhallaOnProcessStop).
 */
/* FIXME: The SaveXXXRegisters and RestoreXXXRegisters functions
 * may easily be abstracted into a general set of two functions
 * SaveTrapRegisters/RestoreTrapRegisters using appropriate defines from
 * registers.h like REG_A1, REG_A1_TXT, Reg_D0, ... (not yet there)
 * See http://www.daimi.au.dk/~beta/doc/betarun/internal/trapcallbacks.html
 * for details.
 */

void set_BetaStackTop(long *sp)
{
  DEBUG_STACK(fprintf(output, "set_BetaStackTop: BetaStackTop=0x%08x\n", (int)sp));
#if defined(sparc) || defined(intel)
  BetaStackTop = sp;
#else 
#ifdef NEWRUN
  BetaStackTop[0] = sp;
#else
  fprintf(output, "set_BetaStackTop: Not implemented for this platform\n");
#endif /* NEWRUN */
#endif /* sparc || intel */
}

/***************************************************************************/
/******************** Handlers for various platforms  **********************/
/***************************************************************************/

/******************** BEGIN sgi ********************************************/
#ifdef sgi

/*
 * Since valhalla may now trigger
 * GC in scripts evaluated in the context of debuggee, we have
 * to make sure that Reference registers are updated during these
 * GC's. So we fetch s0, s1, s2, s8 and a1 from the scp and put them 
 * on a refence stack (which is GC'ed). We then put the (updated) values
 * back after completing DisplayBetaStack (which calls 
 * valhallaOnProcessStop).
 */

void SaveSGIRegisters(SIGNAL_CONTEXT scp, 
		      register_handles *handles)
{
  DEBUG_VALHALLA({
    fprintf(output, 
	    "Sighandler: Saving registers (at PC=0x%08x) on ReferenceStack:\n",
	    (int)scp->sc_pc);
  });
  if (scp->sc_regs[5] && inBetaHeap((Object*)scp->sc_regs[5]) && isObject((Object*)scp->sc_regs[5])){
    DEBUG_VALHALLA({
      fprintf(output, "\ta1/r5:  "); PrintObject((Object*)scp->sc_regs[5]);
      fprintf(output, "\n"); fflush(output);
    });
    SaveVar(scp->sc_regs[5]); handles->a1=1;
  }
  if (scp->sc_regs[16] && inBetaHeap((Object*)scp->sc_regs[16]) && isObject((Object*)scp->sc_regs[16])){
    DEBUG_VALHALLA({
      fprintf(output, "\ts0/r16: "); PrintObject((Object*)scp->sc_regs[16]);
      fprintf(output, "\n"); fflush(output);
    });
    SaveVar(scp->sc_regs[16]); handles->s0=1;
  }
  if (scp->sc_regs[17] && inBetaHeap((Object*)scp->sc_regs[17]) && isObject((Object*)scp->sc_regs[17])){
    DEBUG_VALHALLA({
      fprintf(output, "\ts1/r17: "); PrintObject((Object*)scp->sc_regs[17]);
      fprintf(output, "\n"); fflush(output);
    });
    SaveVar(scp->sc_regs[17]); handles->s1=1;
  }
  if (scp->sc_regs[18] && inBetaHeap((Object*)scp->sc_regs[18]) && isObject((Object*)scp->sc_regs[18])){
    DEBUG_VALHALLA({
      fprintf(output, "\ts2/r18: "); PrintObject((Object*)scp->sc_regs[18]);
      fprintf(output, "\n"); fflush(output);
    });
    SaveVar(scp->sc_regs[18]); handles->s2=1;
  }
  if (scp->sc_regs[30] && inBetaHeap((Object*)scp->sc_regs[30]) && isObject((Object*)scp->sc_regs[30])){
    DEBUG_VALHALLA({
      fprintf(output, "\ts8/r30: "); PrintObject((Object*)scp->sc_regs[30]);
      fprintf(output, "\n"); fflush(output);
    });
    SaveVar(scp->sc_regs[30]); handles->s8=1;
  }
  DEBUG_VALHALLA({
    fprintf(output, "Saving completed. ReferenceStack is:\n");
    PrintRefStack();
  });

}

void RestoreSGIRegisters(SIGNAL_CONTEXT scp, 
			 register_handles *handles)
{
  DEBUG_VALHALLA({
    fprintf(output, "Sighandler: Restoring registers (at PC=0x%08x) from ReferenceStack:\n", (int)scp->sc_pc);
  });
  DEBUG_VALHALLA({
    fprintf(output, "ReferenceStack is:\n");
    PrintRefStack();
  });
  if (handles->s8>=0) {
    RestoreIntVar(scp->sc_regs[30]);
    DEBUG_VALHALLA({
      fprintf(output, "\ts8/r30: "); PrintObject((Object*)scp->sc_regs[30]);
      fprintf(output, "\n"); fflush(output);
    });
  }
  if (handles->s2>=0) {
    RestoreIntVar(scp->sc_regs[18]);
    DEBUG_VALHALLA({
      fprintf(output, "\ts2/r18: "); PrintObject((Object*)scp->sc_regs[18]);
      fprintf(output, "\n"); fflush(output);
    });
  }
  if (handles->s1>=0) {
    RestoreIntVar(scp->sc_regs[17]);
    DEBUG_VALHALLA({
      fprintf(output, "\ts1/r17: "); PrintObject((Object*)scp->sc_regs[17]);
      fprintf(output, "\n"); fflush(output);
    });
  }
  if (handles->s0>=0) {
    RestoreIntVar(scp->sc_regs[16]);
    DEBUG_VALHALLA({
      fprintf(output, "\ts0/r16: "); PrintObject((Object*)scp->sc_regs[16]);
      fprintf(output, "\n"); fflush(output);
    });
  }
  if (handles->a1>=0) {
    RestoreIntVar(scp->sc_regs[5]);
    DEBUG_VALHALLA({
      fprintf(output, "\ta1/r5:  "); PrintObject((Object*)scp->sc_regs[5]);
      fprintf(output, "\n"); fflush(output);
    });
  }
}

void BetaSignalHandler(long sig, long code, struct sigcontext * scp, char *addr)
{
  Object ** theCell;
  Object *    theObj = 0;
  pc_t pc;
  long todo = 0;

  DEBUG_CODE({
    fprintf(output, "\nBetaSignalHandler: Caught signal %d", (int)sig);
    PrintSignal((int)sig);
    fprintf(output, " code %d", (int)code);
    fprintf(output, ".\n");
  });

  /* Setup signal handles for the Beta system */
  signal( SIGFPE,  ExitHandler);
  signal( SIGILL,  ExitHandler);
  signal( SIGBUS,  ExitHandler);
  signal( SIGSEGV, ExitHandler);
#ifdef SIGEMT
  signal( SIGEMT,  ExitHandler);
#endif

  /* Set StackEnd to the stack pointer just before trap. */
  GetPCandSP(*scp);

  { 
    pc = (pc_t) scp->sc_pc;
    theObj = CurrentObject = (Object *) scp->sc_regs[30];
    StackEndAtSignal = StackEnd = (long*) scp->sc_regs[29];
    if( !(inBetaHeap(theObj) && isObject(theObj))) theObj  = 0;
    switch( sig){
    case SIGFPE: 
      /* From <sys/signal.h>:
       * #define BRK_USERBP      0       //user bp (used by debuggers)
       * #define BRK_OVERFLOW    6       //overflow check
       * #define BRK_DIVZERO     7       //divide by zero check
       * #define BRK_RANGE       8       //range error check
       * #define BRK_MULOVF      1023    //multiply overflow detected
       */
      switch((int)code){
      case BRK_DIVZERO:
	todo=DisplayBetaStack(ZeroDivErr , theObj, pc, sig); break;
      case BRK_OVERFLOW:
      case BRK_MULOVF:
	todo=DisplayBetaStack(ArithExceptErr , theObj, pc, sig); break;
      default:
	if (scp->sc_fpc_csr & (1<<15)){
	  /* Floating point division by zero cause bit set.
	   * <sys/fpu.h>: ((union fpc_csr)scp->sc_fpc_csr).fc_struct.ex_divide0
	   */
	  todo=DisplayBetaStack(FpZeroDivErr , theObj, pc, sig); break;
	} else {
	  todo=DisplayBetaStack(FpExceptErr, theObj, pc, sig); break;
	};
      }
      break;
    case SIGEMT:
      todo=DisplayBetaStack( EmulatorTrapErr, theObj, pc, sig); break;
    case SIGILL:
      todo=DisplayBetaStack( IllegalInstErr, theObj, pc, sig); break;
    case SIGBUS:
      todo=DisplayBetaStack( BusErr, theObj, pc, sig); break;
    case SIGSEGV:
      /* Either a segmentation fault in BETA or external code or
       * a refnone in BETA code.
       */
      if (IsBetaCodeAddrOfProcess(pc)){
	/* Could still be a segmentation fault. Would need to
	 * do a disassembly to make a better guess.
	 * Here we just guess that it is a refnone.
	 */
	todo=DisplayBetaStack( RefNoneErr, theObj, pc, sig); 
      } else {
	todo=DisplayBetaStack( SegmentationErr, theObj, pc, sig); 
      }
      break;
    case SIGTRAP:
      {
	register_handles handles = {-1, -1, -1, -1, -1};
	DEBUG_VALHALLA(fprintf(output, "debuggee: SIGTRAP\n"); fflush(output));
	SaveSGIRegisters(scp, &handles);
	/* Hit breakpoint */
	todo=DisplayBetaStack( IllegalInstErr, theObj, pc, sig); 
	RestoreSGIRegisters(scp, &handles);
      } 
      break;
    case SIGINT: /* Interrupt */
      todo=HandleInterrupt(theObj, pc, sig); break;
    default: 
      todo=DisplayBetaStack( UnknownSigErr, theObj, pc, sig);  
    }
  }
  if (!todo) BetaExit(1);
}

#endif /* sgi */
/******************** END sgi **********************************************/


/******************** BEGIN linux ******************************************/
#ifdef linux
#include <fpu_control.h>
#define fpu_sw scp.fpstate->status
#include <sys/ucontext.h>
#define GetPCandSP(scp) { pc = (pc_t) (scp).eip; StackEnd = (long *) (scp).esp_at_signal; }

void SaveLinuxRegisters(SIGNAL_CONTEXT scp, 
			register_handles *handles)
{
  DEBUG_VALHALLA({
    fprintf(output, 
	    "Sighandler: Saving registers (at PC=0x%08x) ",
	    (int)scp->eip);
  });
  DEBUG_VALHALLA(fprintf(output, "on ReferenceStack:\n"));    

  if (scp->edx && inBetaHeap((Object*)scp->edx) && isObject((Object*)scp->edx)){
    DEBUG_VALHALLA(fprintf(output, "edx: 0x%08x", (int)scp->edx));
    SaveVar(scp->edx); handles->edx=1;
  }
  if (scp->edi && inBetaHeap((Object*)scp->edi) && isObject((Object*)scp->edi)){
    DEBUG_VALHALLA(fprintf(output, ", edi: 0x%08x", (int)scp->edi));
    SaveVar(scp->edi); handles->edi=1;
  }
  if (scp->ebp && inBetaHeap((Object*)scp->ebp) && isObject((Object*)scp->ebp)){
    DEBUG_VALHALLA(fprintf(output, ", ebp: 0x%08x", (int)scp->ebp));
    SaveVar(scp->ebp); handles->ebp=1;
  }
  if (scp->esi && inBetaHeap((Object*)scp->esi) && isObject((Object*)scp->esi)){
    DEBUG_VALHALLA(fprintf(output, ", esi: 0x%08x", (int)scp->esi));
    SaveVar(scp->esi); handles->esi=1;
  }
  DEBUG_VALHALLA(fprintf(output, "\n"));
}

static void RestoreLinuxRegisters(SIGNAL_CONTEXT scp, 
				  register_handles *handles)
{
  DEBUG_VALHALLA({
    fprintf(output, "Sighandler: Restoring registers ");
  });
  DEBUG_VALHALLA(fprintf(output, "from ReferenceStack:\n"));
  if (handles->esi>=0) {
    RestoreIntVar(scp->esi);
    DEBUG_VALHALLA(fprintf(output, ", esi: 0x%08x", (int)scp->esi));
  }
  if (handles->ebp>=0) {
    RestoreIntVar(scp->ebp);
    DEBUG_VALHALLA(fprintf(output, ", ebp: 0x%08x", (int)scp->ebp));
  }
  if (handles->edi>=0) {
    RestoreIntVar(scp->edi);
    DEBUG_VALHALLA(fprintf(output, ", edi: 0x%08x", (int)scp->edi));
  }
  if (handles->edx>=0) {
    RestoreIntVar(scp->edx);
    DEBUG_VALHALLA(fprintf(output, "edx: 0x%08x", (int)scp->edx));
  }
  DEBUG_VALHALLA(fprintf(output, "\n"));
}

#if defined(BOUND_BASED_AOA_TO_IOA)
void BoundSignalHandler(long sig, struct sigcontext_struct *scp)
{
  pc_t pc;

  DEBUG_CODE({
    fprintf(output, "\nBoundSignalHandler: Caught signal %d", (int)sig);
    PrintSignal((int)sig);
    fprintf(output, ".\n");
  });

  /* Setup signal handles for the Beta system */
  DEBUG_CODE({
    Object *theObj;
    theObj = (Object *) scp->edx;
    if ( ! (inIOA(theObj) && isObject (theObj)))
	theObj  = 0;
    if (sig != SIGSEGV) {
        fprintf(output, "\nWrong signal caught by BoundSignalHandler");
        DisplayBetaStack( UnknownSigErr, theObj, pc, sig);  
        BetaExit(1);
    }
  });

  /* Set StackEnd to the stack pointer just before trap. */
  GetPCandSP(*scp);

  Claim(*pc == 0x62, "Bound trap not caused by bound insn");

  /* See Mod R/M overview at http://www.sandpile.org/ia32/opc_rm32.htm */
  Claim((pc[1] & 0xc7) == 0x05, "Unknown boundl instruction hit");

  {
      int regnum = 7 - ((pc[1] & 0x38) >> 3);
      /* Assume regs are in order edi, esi, ebp, esp, ebx, edx, ecx, eax */
      Object **reg = ((Object ***)(&scp->edi))[regnum];
      /* fprintf(stderr, "AOA addr = 0x%08x\n", (int)reg); */
      if (inIOA(*reg))
	  AOAtoIOAInsert(reg);
      scp->eip += 6;
  }
}

#endif /* BOUND_BASED_AOA_TO_IOA */


void BetaSignalHandler(long sig, struct sigcontext_struct scp)
{
  Object *    theObj = 0;
  pc_t pc;
  long todo = 0;

  DEBUG_CODE({
    fprintf(output, "\nBetaSignalHandler: Caught signal %d", (int)sig);
    PrintSignal((int)sig);
    fprintf(output, ".\n");
  });

  /* Setup signal handles for the Beta system */
  signal( SIGFPE,  ExitHandler);
  signal( SIGILL,  ExitHandler);
  signal( SIGBUS,  ExitHandler);
  signal( SIGSEGV, ExitHandler);
#ifdef SIGEMT
  signal( SIGEMT,  ExitHandler);
#endif

  /* Set StackEnd to the stack pointer just before trap. */
  GetPCandSP(scp);

#if defined(BOUND_BASED_AOA_TO_IOA)
  if (*pc == 0x62 &&              /* bound insn */
      ((pc[1] & 0xf8) == 0x28)) { /* absolute address, used by aoatoioa check */
      BoundSignalHandler(sig, &scp);
  }
#endif
  /* see <asm/sigcontext.h> */
  theObj = (Object *) scp.edx;
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
	theObj = (Object *) *StackEnd++;
	todo=DisplayBetaStack( ZeroDivErr, theObj, pc, sig); break;
      } else {
	todo=DisplayBetaStack( FpExceptErr, theObj, pc, sig); break;
      }
      break;
    case 16: /* Floating Point Error */
      /* See figure 15-2 in
       * Intel486 Microprocessor Family Programmer's Reference Manual
       */
      DEBUG_CODE({
	fprintf(output, 
		"Linux sighandler: Floating Point Error, fpu_sw=0x%08x\n",
		(int)fpu_sw);
      });
      if (fpu_sw & (1L<<6)){
	/* SF: floating point stack fault */
	if (fpu_sw & (1L<<9)){
	  /* C1=1: overflow */
	  todo=DisplayBetaStack( FpStackOflowErr, theObj, pc, sig); break;
	} else {
	  /* C1=0: underflow */
	  todo=DisplayBetaStack( FpStackUflowErr, theObj, pc, sig); break;
	}
      }
      if (fpu_sw & _FPU_MASK_ZM /*(1L<<2)*/ ){
	/* ZE: zero divide. Hmmm, apparerently x/0.0 gives IE instead (:-( */
	todo=DisplayBetaStack( FpZeroDivErr, theObj, pc, sig); break;
      }
      /* Fall back: report general FP error */
      todo=DisplayBetaStack( FpExceptErr, theObj, pc, sig); break;
    default:	
      todo=DisplayBetaStack( ArithExceptErr, theObj, pc, sig); break;
    }
    break;
  case SIGILL:
    todo=DisplayBetaStack( IllegalInstErr, theObj, pc, sig); break;
  case SIGBUS:
    todo=DisplayBetaStack( BusErr, theObj, pc, sig); break;
  case SIGINT: /* Interrupt */
    todo=HandleInterrupt(theObj, pc, sig); break;
  case SIGTRAP: 
    if (pc[-1] == (unsigned char)0xcc) {
      /* int3 break */
      scp.eip -= 1; /* pc points just after int3 instruction */
      pc = (pc_t)scp.eip;
      DEBUG_VALHALLA(fprintf(output, "sighandler: adjusting PC to 0x%x\n", (int)pc));
    }
    {
      register_handles handles = {-1, -1, -1, -1};
      SaveLinuxRegisters(&scp, &handles);
      todo=DisplayBetaStack( EmulatorTrapErr, theObj, pc, sig); 
      RestoreLinuxRegisters(&scp, &handles);
    }
    break;
   case SIGSEGV:
    switch (scp.trapno) {
    case 5: /* Interrupt 5 generated by boundl */
      todo=DisplayBetaStack(RepRangeErr, theObj, pc, sig); break;
    case 12: /* Stack Fault */
      /* FIXME: does not work */
      todo=DisplayBetaStack(StackErr, theObj, pc, sig); break;
    default:
      todo=DisplayBetaStack(SegmentationErr, theObj, pc, sig); break;
    }
    break;
  default: 
    todo=DisplayBetaStack( UnknownSigErr, theObj, pc, sig);  
  }
#undef fpu_sw

  if (!todo) BetaExit(1);
}

#endif /* linux */
/******************************** END linux **********************************/


/******************************** BEGIN sun4s/sparc **************************/
#ifdef sun4s

void BetaSignalHandler (long sig, siginfo_t *info, ucontext_t *ucon)
{
  Object ** theCell;
  Object *    theObj = 0;
  pc_t pc;
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
  pc = (pc_t) ucon->uc_mcontext.gregs[REG_PC];

#ifndef MT
  DEBUG_VALHALLA(fprintf(output,"BetaSignalHandler: StackEnd set to 0x%x\n",(int) StackEnd));
#endif /* MT */

  /* Try to fetch the address of current Beta object from i0.*/
  theCell = (Object **) &((RegWin*)ucon->uc_mcontext.gregs[REG_SP])->i0;
  if( inIOA( *theCell)) if( isObject( *theCell)) theObj  = *theCell;

  switch(sig){
  case SIGFPE: 
    switch(info->si_code){
    case FPE_INTDIV: /* int div by zero */
      /* The current BETA compiler generates calls to the (leaf) routine
       * .idiv to handle integer division. Thus we need to fix the PC value.
       */
      pc = (pc_t) ucon->uc_mcontext.gregs[REG_O7];
      todo=DisplayBetaStack( ZeroDivErr, theObj, pc, sig); break;
    case FPE_FLTDIV: /* fp div by zero */
      todo=DisplayBetaStack( FpZeroDivErr, theObj, pc, sig); break;
    default: /* arithmetic exception */
      todo=DisplayBetaStack( FpExceptErr, theObj, pc, sig);
    }
    break;
  case SIGEMT:
    todo=DisplayBetaStack( EmulatorTrapErr, theObj, pc, sig); break;
  case SIGILL: /* Illegal instruction or trap */
    switch(info->si_code){
    case ILL_ILLTRP:
      switch(info->si_trapno-16){
#ifdef MT
      case 0x80: /* Solaris 2.3, 2.4, 2.5 */
      case 0x100: /* Solaris 2.5.1 */
	/* tle 16 trap => component stack overflow */
	todo=DisplayBetaStack( StackErr, theObj, pc, sig); break;
#endif
      case 0x81: /* Solaris 2.3, 2.4, 2.5 */
      case 0x101: /* Solaris 2.5.1 */
	/* tle 17 trap => ref none */
	todo=DisplayBetaStack( RefNoneErr, theObj, pc, sig); break;
      default:
	todo=DisplayBetaStack( IllegalInstErr, theObj, pc, sig); break;
      }
      break;
    default:
      todo=DisplayBetaStack( IllegalInstErr, theObj, pc, sig); break;
    }
    break;
  case SIGBUS: /* Bus error */
    todo=DisplayBetaStack( BusErr, theObj, pc, sig); break;
  case SIGSEGV: /* Segmentation fault */
    if (IsBetaCodeAddrOfProcess(pc)){
      todo=DisplayBetaStack( RefNoneErr, theObj, pc, sig);
    } else {
      todo=DisplayBetaStack( SegmentationErr, theObj, pc, sig);
    }
    break;
  case SIGINT: /* Interrupt */
    todo=HandleInterrupt(theObj, pc, sig); break;
  default:  /* Unknown signal */
    todo=DisplayBetaStack( UnknownSigErr, theObj, pc, sig);  
  }

  if (todo) {
    /* We have been through valhalla, and should continue execution.
     * With the introduction of dynamic compilation into debuggee, the 
     * debuggee may have allocated in IOA and even caused GC.
     * That is, the current value (right here in the signal handler)
     * of the two global sparc registers holding IOA and IOATopOff
     * MUST be written back into the ucontext to prevent the signal-
     * handler from restoring these registers to the old values.
     * Otherwise objects allocated during valhalla evaluators will
     * be forgotten!.
     * See register binding in registers.h.
     */
    ucon->uc_mcontext.gregs[REG_IOA] = (long)IOA;
    ucon->uc_mcontext.gregs[REG_IOATOPOFF] = (long)IOATopOff;
  } else {
    BetaExit(1);
  }
}
  
#endif /* sun4s */
/***************************** END sun4s ********************************/

/***************************** BEGIN x86sol *****************************/
#ifdef x86sol
void SaveX86SolRegisters(SIGNAL_CONTEXT scp, 
			 register_handles *handles)
{
  DEBUG_VALHALLA({
    fprintf(output, 
	    "Sighandler: Saving registers (at PC=0x%08x) ",
	    (int)scp->uc_mcontext.gregs[PC]);
  });
  DEBUG_VALHALLA(fprintf(output, "on ReferenceStack:\n"));    

  if (scp->uc_mcontext.gregs[EDX] && inBetaHeap((Object*)scp->uc_mcontext.gregs[EDX]) && isObject((Object*)scp->uc_mcontext.gregs[EDX])){
    DEBUG_VALHALLA(fprintf(output, "edx: 0x%08x", (int)scp->uc_mcontext.gregs[EDX]));
    SaveVar(scp->uc_mcontext.gregs[EDX]); handles->edx=1;
  }
  if (scp->uc_mcontext.gregs[EDI] && inBetaHeap((Object*)scp->uc_mcontext.gregs[EDI]) && isObject((Object*)scp->uc_mcontext.gregs[EDI])){
    DEBUG_VALHALLA(fprintf(output, ", edi: 0x%08x", (int)scp->uc_mcontext.gregs[EDI]));
    SaveVar(scp->uc_mcontext.gregs[EDI]); handles->edi=1;
  }
  if (scp->uc_mcontext.gregs[EBP] && inBetaHeap((Object*)scp->uc_mcontext.gregs[EBP]) && isObject((Object*)scp->uc_mcontext.gregs[EBP])){
    DEBUG_VALHALLA(fprintf(output, ", ebp: 0x%08x", (int)scp->uc_mcontext.gregs[EBP]));
    SaveVar(scp->uc_mcontext.gregs[EBP]); handles->ebp=1;
  }
  if (scp->uc_mcontext.gregs[ESI] && inBetaHeap((Object*)scp->uc_mcontext.gregs[ESI]) && isObject((Object*)scp->uc_mcontext.gregs[ESI])){
    DEBUG_VALHALLA(fprintf(output, ", esi: 0x%08x", (int)scp->uc_mcontext.gregs[ESI]));
    SaveVar(scp->uc_mcontext.gregs[ESI]); handles->esi=1;
  }
  DEBUG_VALHALLA(fprintf(output, "\n"));
}

static void RestoreX86SolRegisters(SIGNAL_CONTEXT scp, 
				   register_handles *handles)
{
  DEBUG_VALHALLA({
    fprintf(output, "Sighandler: Restoring registers ");
  });
  DEBUG_VALHALLA(fprintf(output, "from ReferenceStack:\n"));
  if (handles->esi>=0) {
    RestoreIntVar(scp->uc_mcontext.gregs[ESI]);
    DEBUG_VALHALLA(fprintf(output, ", esi: 0x%08x", (int)scp->uc_mcontext.gregs[ESI]));
  }
  if (handles->ebp>=0) {
    RestoreIntVar(scp->uc_mcontext.gregs[EBP]);
    DEBUG_VALHALLA(fprintf(output, ", ebp: 0x%08x", (int)scp->uc_mcontext.gregs[EBP]));
  }
  if (handles->edi>=0) {
    RestoreIntVar(scp->uc_mcontext.gregs[EDI]);
    DEBUG_VALHALLA(fprintf(output, ", edi: 0x%08x", (int)scp->uc_mcontext.gregs[EDI]));
  }
  if (handles->edx>=0) {
    RestoreIntVar(scp->uc_mcontext.gregs[EDX]);
    DEBUG_VALHALLA(fprintf(output, "edx: 0x%08x", (int)scp->uc_mcontext.gregs[EDX]));
  }
  DEBUG_VALHALLA(fprintf(output, "\n"));
}

void BetaSignalHandler (long sig, siginfo_t *info, ucontext_t *ucon)
{
  Object *    theObj = 0;
  pc_t pc;
  long todo = 0;

  DEBUG_CODE({
    fprintf(output, "\nBetaSignalHandler: Caught signal %d", (int)sig);
    PrintSignal((int)sig);
    fprintf(output, ".\n");
  });

  /* Setup signal handlers for the Beta system */
  signal( SIGFPE,  ExitHandler);
  signal( SIGILL,  ExitHandler);
  signal( SIGBUS,  ExitHandler);
  signal( SIGSEGV, ExitHandler);
  signal( SIGEMT,  ExitHandler);

  
  /* Set StackEnd to the stack pointer just before trap. 
   * PC etc. are in /usr/include/sys/reg.h.
   */
  StackEnd = (long *) ucon->uc_mcontext.gregs[UESP]; /* not SP */
  pc = (pc_t) ucon->uc_mcontext.gregs[PC];

  DEBUG_VALHALLA(fprintf(output,"BetaSignalHandler: StackEnd set to 0x%x\n",(int) StackEnd));

  /* Fetch the address of current Beta object from context.*/
  theObj = (Object *) ucon->uc_mcontext.gregs[EDX];

  switch(sig){
  case SIGFPE: 
    switch(info->si_code){
    case FPE_INTDIV: /* int div by zero */
      /* IDIV uses %edx (i.e. current object register) for divisor.
       * If this is 0, theObj will be 0 when trap is taken.
       * Use the fact that current object is pushed before IDIV,
       * and take it from the stack.
       */
      theObj = (Object *) *StackEnd++;
      todo=DisplayBetaStack( ZeroDivErr, theObj, pc, sig); break;
    case FPE_FLTOVF: /* fp stack overflow*/
      todo=DisplayBetaStack( FpStackOflowErr, theObj, pc, sig); break;
    case FPE_FLTUND: /* fp stack underflow*/
      todo=DisplayBetaStack( FpStackUflowErr, theObj, pc, sig); break;
    case FPE_FLTDIV: /* fp div by zero (but: is reported as invalid instaed (:-()*/
      todo=DisplayBetaStack( FpZeroDivErr, theObj, pc, sig); break;
    default: 
      if (ucon->uc_mcontext.gregs[TRAPNO]==16){
	/* floating point exception */
	todo=DisplayBetaStack( FpExceptErr, theObj, pc, sig);
      } else {
	/* arithmetic exception reported by fpu */
	todo=DisplayBetaStack( ArithExceptErr, theObj, pc, sig);
      }
    }
    break;
  case SIGEMT:
    {
      register_handles handles = {-1, -1, -1, -1};
      SaveX86SolRegisters(ucon, &handles);
      todo=DisplayBetaStack( EmulatorTrapErr, theObj, pc, sig); 
      RestoreX86SolRegisters(ucon, &handles);
    }
    break;
  case SIGILL: /* Illegal instruction or trap */
    todo=DisplayBetaStack( IllegalInstErr, theObj, pc, sig); break;
  case SIGBUS: /* Bus error */
    todo=DisplayBetaStack( BusErr, theObj, pc, sig); break;
  case SIGSEGV: /* Segmentation fault */
    switch (ucon->uc_mcontext.gregs[TRAPNO]) {
    case 5: /* Interrupt 5 generated by boundl */
      todo=DisplayBetaStack(RepRangeErr, theObj, pc, sig); break;
    case 12: /* Stack Fault */
      /* FIXME: does not work */
      todo=DisplayBetaStack(StackErr, theObj, pc, sig); break;
    default:
      if (IsBetaCodeAddrOfProcess(pc)){
	todo=DisplayBetaStack( RefNoneErr, theObj, pc, sig);
      } else {
	todo=DisplayBetaStack( SegmentationErr, theObj, pc, sig);
      }
    }
    break;
  case SIGTRAP: 
    if ( pc[-1] == (unsigned char)0xcc ){
      /* int3 break */
      ucon->uc_mcontext.gregs[EIP] -= 1; /* pc points just after int3 instruction */
      pc = (pc_t) ucon->uc_mcontext.gregs[EIP];
      DEBUG_VALHALLA(fprintf(output, "sighandler: adjusting PC to 0x%x\n", (int)pc));
    }
    {
      register_handles handles = {-1, -1, -1, -1};
      SaveX86SolRegisters(ucon, &handles);
      todo=DisplayBetaStack( EmulatorTrapErr, theObj, pc, sig); 
      RestoreX86SolRegisters(ucon, &handles);
    }
    break;
  case SIGINT: /* Interrupt */
    todo=HandleInterrupt(theObj, pc, sig); break;
  default:  /* Unknown signal */
    todo=DisplayBetaStack( UnknownSigErr, theObj, pc, sig);  
  }

  if (!todo) {
    BetaExit(1);
  }
}
  
#endif /* x86sol */
/***************************** END x86sol ********************************/



#ifdef macosx
/***************************** BEGIN macosx ********************************/
void BetaSignalHandler (signal_context *scp)
{
  Object ** theCell;
  Object *    theObj;
  pc_t pc;
  long todo = 0;
  int sig = scp->signal_number;

  DEBUG_CODE({
    fprintf(output, "\nBetaSignalHandler: Caught signal %d", (int)sig);
    PrintSignal((int)sig);
    fprintf(output, ".\n");
  });

  /* Setup exit handlers */
  signal( SIGFPE,  ExitHandler);
  signal( SIGILL,  ExitHandler);
  signal( SIGBUS,  ExitHandler);
  signal( SIGSEGV, ExitHandler);
  signal( SIGEMT,  ExitHandler);

  pc = (pc_t)scp->pc_at_signal; 
  StackEndAtSignal=StackEnd=(long*)scp->GPR[1];
  theObj = (Object *)scp->GPR[31];

  if( !(inBetaHeap(theObj) && isObject(theObj))) theObj  = 0;

  switch (sig){
  case SIGFPE: 
    todo=DisplayBetaStack( FpExceptErr, theObj, pc, sig); break;
  case SIGEMT:
    todo=DisplayBetaStack( EmulatorTrapErr, theObj, pc, sig); break;
  case SIGILL:
    todo=DisplayBetaStack( IllegalInstErr, theObj, pc, sig); break;
  case SIGBUS:
    todo=DisplayBetaStack( BusErr, theObj, pc, sig); break;
  case SIGSEGV:
    todo=DisplayBetaStack( SegmentationErr, theObj, pc, sig); break;
  case SIGTRAP:
    /* Could be:
     *    - An illegal instruction in BETA or external code?
     *    - refnone in BETA code.
     *    - breakpoint trap?
     */
    if (IsBetaCodeAddrOfProcess(pc)){
      /* Could still be a segmentation fault. Would need to
       * do a disassembly to make a better guess.
       * Here we just guess that it is a refnone.
       */
      todo=DisplayBetaStack( RefNoneErr, theObj, pc, sig); 
    } else {
      todo=DisplayBetaStack( IllegalInstErr, theObj, pc, sig); 
    }
    break;
  case SIGINT: /* Interrupt */
    todo=HandleInterrupt( theObj, pc, sig); break;
  default: 
    todo=DisplayBetaStack( UnknownSigErr, theObj, pc, sig);  
  }
  if (!todo) {
    BetaExit(1);
  }
  return;
}

void proxyTrapHandler(signal_context *scp)
{
  /* All signals go through here on macosx */

  DEBUG_CODE({
    int sig = (int)scp->signal_number;
    fprintf(output, "\nproxyTrapHandler: Caught signal %d", sig);
    PrintSignal((int)sig);
    fprintf(output, ".\n");
  });
#ifdef PERSIST
  if (scp->signal_number == SIGTRAP){
    /* May be a dangler trap */
    pc_t pc;
    unsigned long instruction;
    
    int opcode;
    int TO;
    int reg;
    long *proxy;
    Object *real;
    
    pc = (pc_t)scp->pc_at_signal;	
    instruction = *pc;
    
    /* fprintf(output, "0x%08X\n", instruction); */
    
    /* FIXME: should verify that instruction = TWLEI Rxx 0 */
    
    opcode = (instruction >> 26);
    TO = (instruction >> 21) & (0xFF >> 3);
    reg = (instruction >> 16) & (0xFF >> 3);
    
    /* fprintf(output, "register = %d\n", reg);
       fprintf(output, "address = 0x%08X\n", scp->GPR[reg]); */
    proxy = (long *) scp->GPR[reg];
    
    if(inPIT(proxy)) {
      real = (Object *)unswizzleReference(proxy);
      /* fprintf(output, "address = 0x%08X\n", real);
	 proto = GETPROTO(real);
	 fprintf(output, "proto = %s\n", ProtoTypeName(proto)); */
      scp->GPR[reg] = (long) real;
      return;
    }
  }
#endif /* PERSIST */
  /* Exception not handled, let sighandler decide what to do.  */
  BetaSignalHandler(scp);
}

/*
 * The current MacOSX sigcontext does not contain a publically available 
 * register save structure.
 * However, Lars Bak suggested a general mechanism that can
 * be used if the signal context is polite enough (:-) to give at least the
 * program counter for the trapping instruction. In the MacOSX case, this is
 * just what you get (and ALL that you get!).
 * In short the principle goes as follows:
 *   1. Set up the usual signal handler.
 *   2. Inside this signal handler, save the PC indicating the origin of the
 *      signal
 *   3. Then (here comes the trick) modify the given sigcontext's PC by letting
 *      it point to a routine you supply. I call this the "wrapper".
 *   4. Now simply return from the signal handler.
 *      Because of (3) the program continues execution at your "wrapper".
 *      But besides this different program counter, the state of the machine
 *      will be exactly as when the signal occurred.
 *   5. Inside your "wrapper" you can now read all registers as they looked
 *      when the signal occurred. You will have to write this routine in
 *      assembler to avoid the standard C prologue to change anything before
 *      you get your hands at it. If you set up a new stack frame, you can even
 *      call a C routine to do the actual work of handling the signal (e.g.
 *      switching on the signal number, reading and/or modifying register
 *      contents). You could pass this C routine a pointer to the saved state.
 *   6. When control returns to the wrapper, you restore all registers from the
 *      context (thus also writing back any registers that were changed inside
 *      the context by the C routine).
 *   7. The final step is to set the return address of the wrapper to the
 *      original PC as saved by (2) and then returning to your code.
 */

void SignalWrapper(); /* written in assembler - see below */
asm(
".set linkagesize,  (6*4) \n"
".set paramsize,    (2*4)  ; actually only one used (2 to ensure double align of FR) \n"
".set localsize,    (2*4)  ; signal_number, pc_at_signal \n"
".set registersize, (32*4 + 32*8 + 8 + 4 + 4 + 4 + 4)   ; sizeof(signal_context) \n"
".set framesize,    (((linkagesize + paramsize + localsize + registersize)+15)&-16) \n"
" \n"
".set linkageoff,   0 \n"
".set paramoff,     linkageoff+linkagesize \n"
".set localoff,     paramoff+paramsize \n"
".set registeroff,  localoff+localsize \n"
" \n"
".set froff,        registeroff + 4*32 \n"
".set fpscroff,     froff + 8*32 \n"
".set xeroff,       froff + 8 \n"
".set croff,        xeroff + 4 \n"
".set lroff,        croff + 4 \n"
".set ctroff,       lroff + 4 \n"
" \n"
".globl _SignalWrapper  \n"
"_SignalWrapper:  \n"
"    ; entered upon return from UNIX signal handler \n"
"    ; Machine state is completely as when signal was raised, except for \n"
"    ; the instruction pointer (PC), whose original value is stored in  \n"
"    ; global variable pc_at_signal \n"
" \n"
"    ; create frame \n"
"    stwu r1,-framesize(r1) \n"
" \n"
"    ; save registers \n"
"    ; general registers \n"
"    stw	r0,    registeroff+4*0(r1)  \n"
"    ; r1 already changed. Fetch from saved location in linkage field (saved by stwu above) \n"
"    lwz r0,    0(r1) \n"
"    stw r0,    registeroff+4*1(r1) ; r1 = SP \n"
"    stw r2,    registeroff+4*2(r1) \n"
"    stw r3,    registeroff+4*3(r1) \n"
"    stw r4,    registeroff+4*4(r1) \n"
"    stw r5,    registeroff+4*5(r1) \n"
"    stw r6,    registeroff+4*6(r1) \n"
"    stw r7,    registeroff+4*7(r1) \n"
"    stw r8,    registeroff+4*8(r1) \n"
"    stw r9,    registeroff+4*9(r1) \n"
"    stw r10,   registeroff+4*10(r1) \n"
"    stw r11,   registeroff+4*11(r1) \n"
"    stw r12,   registeroff+4*12(r1) \n"
"    stw r13,   registeroff+4*13(r1) \n"
"    stw r14,   registeroff+4*14(r1) \n"
"    stw r15,   registeroff+4*15(r1) \n"
"    stw r16,   registeroff+4*16(r1) \n"
"    stw r17,   registeroff+4*17(r1) \n"
"    stw r18,   registeroff+4*18(r1) \n"
"    stw r19,   registeroff+4*19(r1) \n"
"    stw r20,   registeroff+4*20(r1) \n"
"    stw r21,   registeroff+4*21(r1) \n"
"    stw r22,   registeroff+4*22(r1) \n"
"    stw r23,   registeroff+4*23(r1) \n"
"    stw r24,   registeroff+4*24(r1) \n"
"    stw r25,   registeroff+4*25(r1) \n"
"    stw r26,   registeroff+4*26(r1) \n"
"    stw r27,   registeroff+4*27(r1) \n"
"    stw r28,   registeroff+4*28(r1) \n"
"    stw r29,   registeroff+4*29(r1) \n"
"    stw r30,   registeroff+4*30(r1) \n"
"    stw r31,   registeroff+4*31(r1) \n"
" \n"
"    ; Condition register \n"
"    mfcr        r0 \n"
"    stw	r0,     croff(r1) \n"
" \n"
"    ; Fixed point exception register \n"
"    mfxer       r0 \n"
"    stw	r0,     xeroff(r1) \n"
"   \n"
"    ; Link register \n"
"    mflr        r0 \n"
"    stw	r0,     lroff(r1) \n"
" \n"
"    ; Count register \n"
"    mfctr       r0 \n"
"    stw	r0,     ctroff(r1) \n"
" \n"
"    ; Floating point registers - 8 byte aligned */ \n"
"    stfd f0,    froff+8*0(r1) \n"
"    stfd f1,    froff+8*1(r1) \n"
"    stfd f2,    froff+8*2(r1) \n"
"    stfd f3,    froff+8*3(r1) \n"
"    stfd f4,    froff+8*4(r1) \n"
"    stfd f5,    froff+8*5(r1) \n"
"    stfd f6,    froff+8*6(r1) \n"
"    stfd f7,    froff+8*7(r1) \n"
"    stfd f8,    froff+8*8(r1) \n"
"    stfd f9,    froff+8*9(r1) \n"
"    stfd f10,   froff+8*10(r1) \n"
"    stfd f11,   froff+8*11(r1) \n"
"    stfd f12,   froff+8*12(r1) \n"
"    stfd f13,   froff+8*13(r1) \n"
"    stfd f14,   froff+8*14(r1) \n"
"    stfd f15,   froff+8*15(r1) \n"
"    stfd f16,   froff+8*16(r1) \n"
"    stfd f17,   froff+8*17(r1) \n"
"    stfd f18,   froff+8*18(r1) \n"
"    stfd f19,   froff+8*19(r1) \n"
"    stfd f20,   froff+8*20(r1) \n"
"    stfd f21,   froff+8*21(r1) \n"
"    stfd f22,   froff+8*22(r1) \n"
"    stfd f23,   froff+8*23(r1) \n"
"    stfd f24,   froff+8*24(r1) \n"
"    stfd f25,   froff+8*25(r1) \n"
"    stfd f26,   froff+8*26(r1) \n"
"    stfd f27,   froff+8*27(r1) \n"
"    stfd f28,   froff+8*28(r1) \n"
"    stfd f29,   froff+8*29(r1) \n"
"    stfd f30,   froff+8*30(r1) \n"
"    stfd f31,   froff+8*31(r1) \n"
" \n"
"    ; Floating point status register \n"
"    mffs        f0 \n"
"    stfd f0,    fpscroff(r1) \n"
" \n"
"    ; save global variables signal_number and pc_at_signal on stack \n"
"    ; (in local variable section) to allow for nested signals \n"
"    bcl 20,31,L1$SignalWrapper \n"
"L1$SignalWrapper: \n"
"    mflr r13 \n"
"    addis r3,r13,ha16(_signal_number-L1$SignalWrapper) \n"
"    lwz r3,lo16(_signal_number-L1$SignalWrapper)(r3) \n"
"    stw r3,localoff(r1) \n"
"    addis r3,r13,ha16(_pc_at_signal-L1$SignalWrapper) \n"
"    lwz r3,lo16(_pc_at_signal-L1$SignalWrapper)(r3) \n"
"    stw r3,localoff+4(r1) \n"
" \n"
"    ; call actual handler \n"
"    la r3,linkagesize+paramsize(r1) ; address of signal_context on stack \n"
"    bl _proxyTrapHandler  \n"
" \n"
"    ; [we only get here if proxyTrapHandler returns after handling the signal] \n"
" \n"
"    ; set link register (return address) to original pc_at_signal \n"
"    lwz r0,localoff+4(r1) \n"
"    mtlr r0 \n"
" \n"
"    ; restore state (except link register) from stack \n"
"    ; general registers \n"
"    ; do not yet restore r0 and r1 \n"
"    lwz r2,    registeroff+4*2(r1) \n"
"    lwz r3,    registeroff+4*3(r1) \n"
"    lwz r4,    registeroff+4*4(r1) \n"
"    lwz r5,    registeroff+4*5(r1) \n"
"    lwz r6,    registeroff+4*6(r1) \n"
"    lwz r7,    registeroff+4*7(r1) \n"
"    lwz r8,    registeroff+4*8(r1) \n"
"    lwz r9,    registeroff+4*9(r1) \n"
"    lwz r10,   registeroff+4*10(r1) \n"
"    lwz r11,   registeroff+4*11(r1) \n"
"    lwz r12,   registeroff+4*12(r1) \n"
"    lwz r13,   registeroff+4*13(r1) \n"
"    lwz r14,   registeroff+4*14(r1) \n"
"    lwz r15,   registeroff+4*15(r1) \n"
"    lwz r16,   registeroff+4*16(r1) \n"
"    lwz r17,   registeroff+4*17(r1) \n"
"    lwz r18,   registeroff+4*18(r1) \n"
"    lwz r19,   registeroff+4*19(r1) \n"
"    lwz r20,   registeroff+4*20(r1) \n"
"    lwz r21,   registeroff+4*21(r1) \n"
"    lwz r22,   registeroff+4*22(r1) \n"
"    lwz r23,   registeroff+4*23(r1) \n"
"    lwz r24,   registeroff+4*24(r1) \n"
"    lwz r25,   registeroff+4*25(r1) \n"
"    lwz r26,   registeroff+4*26(r1) \n"
"    lwz r27,   registeroff+4*27(r1) \n"
"    lwz r28,   registeroff+4*28(r1) \n"
"    lwz r29,   registeroff+4*29(r1) \n"
"    lwz r30,   registeroff+4*30(r1) \n"
"    lwz r31,   registeroff+4*31(r1) \n"
" \n"
"    ; Floating point status register \n"
"    lfd f0,    fpscroff(r1) \n"
"    mtfs       f0 \n"
" \n"
"    ; Floating point registers - 8 byte aligned */ \n"
"    lfd f0,    froff+8*0(r1) \n"
"    lfd f1,    froff+8*1(r1) \n"
"    lfd f2,    froff+8*2(r1) \n"
"    lfd f3,    froff+8*3(r1) \n"
"    lfd f4,    froff+8*4(r1) \n"
"    lfd f5,    froff+8*5(r1) \n"
"    lfd f6,    froff+8*6(r1) \n"
"    lfd f7,    froff+8*7(r1) \n"
"    lfd f8,    froff+8*8(r1) \n"
"    lfd f9,    froff+8*9(r1) \n"
"    lfd f10,   froff+8*10(r1) \n"
"    lfd f11,   froff+8*11(r1) \n"
"    lfd f12,   froff+8*12(r1) \n"
"    lfd f13,   froff+8*13(r1) \n"
"    lfd f14,   froff+8*14(r1) \n"
"    lfd f15,   froff+8*15(r1) \n"
"    lfd f16,   froff+8*16(r1) \n"
"    lfd f17,   froff+8*17(r1) \n"
"    lfd f18,   froff+8*18(r1) \n"
"    lfd f19,   froff+8*19(r1) \n"
"    lfd f20,   froff+8*20(r1) \n"
"    lfd f21,   froff+8*21(r1) \n"
"    lfd f22,   froff+8*22(r1) \n"
"    lfd f23,   froff+8*23(r1) \n"
"    lfd f24,   froff+8*24(r1) \n"
"    lfd f25,   froff+8*25(r1) \n"
"    lfd f26,   froff+8*26(r1) \n"
"    lfd f27,   froff+8*27(r1) \n"
"    lfd f28,   froff+8*28(r1) \n"
"    lfd f29,   froff+8*29(r1) \n"
"    lfd f30,   froff+8*30(r1) \n"
"    lfd f31,   froff+8*31(r1) \n"
" \n"
"    ; Fixed point exception register \n"
"    lwz	r0,     xeroff(r1) \n"
"    mtxer       r0 \n"
"   \n"
"    ; Link register already set above \n"
" \n"
"    ; Count register \n"
"    lwz	r0,     ctroff(r1) \n"
"    mtctr       r0 \n"
" \n"
"    ; Condition register \n"
"    lwz	r0,     croff(r1) \n"
"    mtcr        r0 \n"
" \n"
"    ; Finally restore r1 and r0 \n"
"    lwz	r0,    registeroff+4*0(r1) \n"
"    la r1,     framesize(r1) \n"
" \n"
"    ; return (to where signal was raised) \n"
"    blr  \n"
);

static long signal_number;
static unsigned long pc_at_signal;

void BetaSignalCatcher (long sig, /*siginfo_t*/ void *info, struct sigcontext *scp)
{
  DEBUG_CODE({
    fprintf(output, "\nBetaSignalCatcher:\n");
    fprintf(output, "  Signal %d caught at PC=0x%x\n", (int)sig, (int)scp->sc_ir);
  });

  /* Save signal number and PC in global variables */
  signal_number = sig;
  pc_at_signal = scp->sc_ir;

  DEBUG_CODE(fprintf(output, "  [returning through SignalWrapper]\n"));
  scp->sc_ir = (long)&SignalWrapper; /* go to SignalWrapper upon return */
  return; /* via system signal handler to SignalWrapper */
}

#endif /* macosx */
/***************************** END macosx ********************************/



/***************************** BEGIN nti ********************************/
#ifdef nti
#ifdef PERSIST
extern int proxyTrapHandler(CONTEXT* pContextRecord); 
#endif

void SaveWin32Registers(SIGNAL_CONTEXT scp, 
			register_handles *handles)
{
  DEBUG_VALHALLA({
    fprintf(output, 
	    "Sighandler: Saving registers (at PC=0x%08x) ",
	    (int)scp->Eip);
  });
  DEBUG_VALHALLA(fprintf(output, "on ReferenceStack:\n"));    

  if (scp->Edx && inBetaHeap((Object*)scp->Edx) && isObject((Object*)scp->Edx)){
    DEBUG_VALHALLA(fprintf(output, "edx: 0x%08x", (int)scp->Edx));
    SaveVar(scp->Edx); handles->edx=1;
  }
  if (scp->Edi && inBetaHeap((Object*)scp->Edi) && isObject((Object*)scp->Edi)){
    DEBUG_VALHALLA(fprintf(output, ", edi: 0x%08x", (int)scp->Edi));
    SaveVar(scp->Edi); handles->edi=1;
  }
  if (scp->Ebp && inBetaHeap((Object*)scp->Ebp) && isObject((Object*)scp->Ebp)){
    DEBUG_VALHALLA(fprintf(output, ", ebp: 0x%08x", (int)scp->Ebp));
    SaveVar(scp->Ebp); handles->ebp=1;
  }
  if (scp->Esi && inBetaHeap((Object*)scp->Esi) && isObject((Object*)scp->Esi)){
    DEBUG_VALHALLA(fprintf(output, ", esi: 0x%08x", (int)scp->Esi));
    SaveVar(scp->Esi); handles->esi=1;
  }
  DEBUG_VALHALLA(fprintf(output, "\n"));
}

static void RestoreWin32Registers(SIGNAL_CONTEXT scp, 
				  register_handles *handles)
{
  DEBUG_VALHALLA({
    fprintf(output, "Sighandler: Restoring registers ");
  });
  if (handles->esi>=0) {
    RestoreIntVar(scp->Esi);
    DEBUG_VALHALLA(fprintf(output, ", esi: 0x%08x", (int)scp->Esi));
  }
  if (handles->ebp>=0) {
    RestoreIntVar(scp->Ebp);
    DEBUG_VALHALLA(fprintf(output, ", ebp: 0x%08x", (int)scp->Ebp));
  }
  DEBUG_VALHALLA(fprintf(output, "from ReferenceStack:\n"));
  if (handles->edi>=0) {
    RestoreIntVar(scp->Edi);
    DEBUG_VALHALLA(fprintf(output, ", edi: 0x%08x", (int)scp->Edi));
  }
  if (handles->edx>=0) {
    RestoreIntVar(scp->Edx);
    DEBUG_VALHALLA(fprintf(output, "edx: 0x%08x", (int)scp->Edx));
  }
  DEBUG_VALHALLA(fprintf(output, "\n"));
}

#ifdef nti_gnu
EXCEPTION_DISPOSITION 
BetaSignalHandler_GNU(EXCEPTION_RECORD* pExceptionRec,
		      void* pEstablisherFrame,
		      CONTEXT* pContextRecord,
		      void* pDispatcherContext) 
#else  /* !nti_gnu */
int BetaSignalHandler(LPEXCEPTION_POINTERS lpEP)
#endif /* nti_gnu */
{
#ifdef nti_ms
  EXCEPTION_RECORD* pExceptionRec =  lpEP->ExceptionRecord;
  CONTEXT* pContextRecord = lpEP->ContextRecord;
#endif /* nti_ms */
  Object *theObj = 0;
  pc_t pc;
  long todo = 0;
  long sig;

  if (NoCatchException) return OUR_EXCEPTION_CONTINUE_SEARCH;
  
  if (pContextRecord->ContextFlags & CONTEXT_CONTROL){
    pc       = (pc_t)pContextRecord->Eip;
    StackEnd = (long *)pContextRecord->Esp;
  } else {
    /* Can't display stack if SP unknown */
    return OUR_EXCEPTION_CONTINUE_SEARCH;
  }
  if (pContextRecord->ContextFlags & CONTEXT_INTEGER){
    theObj = (Object *)pContextRecord->Edx;
  }
  sig = (long)pExceptionRec->ExceptionCode;
  switch (pExceptionRec->ExceptionCode){
  case EXCEPTION_ACCESS_VIOLATION:
#ifdef PERSIST
    todo = proxyTrapHandler(pContextRecord);
    if (!todo) {
      return OUR_EXCEPTION_CONTINUE_EXECUTION;
    } else if (todo == 2) {
      todo=DisplayBetaStack(RefNoneErr, theObj, pc, sig); break;
    } else {
      todo=DisplayBetaStack(SegmentationErr, theObj, pc, sig); break;
    }
#endif
  case EXCEPTION_DATATYPE_MISALIGNMENT:
    todo=DisplayBetaStack( SegmentationErr, theObj, pc, sig); break;
  case EXCEPTION_STACK_OVERFLOW:
    todo=DisplayBetaStack( StackErr, theObj, pc, sig); break;
  case EXCEPTION_BREAKPOINT:
    DEBUG_VALHALLA(fprintf(output, "sighandler: breakpoint at PC 0x%x\n", (int)pc); fflush(output));
    if (!isWinNT()) {
      /* Fix the problem with win95 returning PC after the int3 break
	 instruction. NT returns PC pointing at the int3 instruction. */
      pc = (pc_t) (--pContextRecord->Eip);
      DEBUG_VALHALLA(fprintf(output, "sighandler: adjusting PC to 0x%x\n", (int)pc); fflush(output));
    }
    {
      /* We are running under valhalla. */
      register_handles handles = {-1, -1, -1, -1};
      SaveWin32Registers(pContextRecord, &handles);
      todo=DisplayBetaStack( EmulatorTrapErr, theObj, pc, sig); 
      RestoreWin32Registers(pContextRecord, &handles);
    } 
    break;
  case EXCEPTION_ARRAY_BOUNDS_EXCEEDED:
    todo=DisplayBetaStack( RepRangeErr, theObj, pc, sig); break;
  case STATUS_ILLEGAL_INSTRUCTION /* was: EXCEPTION_ILLEGAL_INSTRUCTION */:
  case EXCEPTION_PRIV_INSTRUCTION:
    todo=DisplayBetaStack( IllegalInstErr, theObj, pc, sig); break;
  case EXCEPTION_INT_DIVIDE_BY_ZERO:
    /* Fix current object: It was pushed before the idiv instruction,
     * but will be zero in this case.
     */
    theObj = *(Object **)StackEnd++;
    todo=DisplayBetaStack( ZeroDivErr, theObj, pc, sig); break;
  case EXCEPTION_FLT_DIVIDE_BY_ZERO:
    todo=DisplayBetaStack( FpZeroDivErr, theObj, pc, sig); break;
  case EXCEPTION_FLT_STACK_CHECK:
    if (pContextRecord->ContextFlags & CONTEXT_FLOATING_POINT){
      if (pContextRecord->FloatSave.StatusWord & (1L<<9)){
	/* C1=1: overflow */
	todo=DisplayBetaStack( FpStackOflowErr, theObj, pc, sig); break;
      } else {
	/* C1=0: underflow */
	todo=DisplayBetaStack( FpStackUflowErr, theObj, pc, sig); break;
      }
    } else {
      /* lets guess on overflow */
      todo=DisplayBetaStack( FpStackOflowErr, theObj, pc, sig); break;
    }
  case EXCEPTION_FLT_DENORMAL_OPERAND:
  case EXCEPTION_FLT_INEXACT_RESULT:
  case EXCEPTION_FLT_OVERFLOW:
  case EXCEPTION_FLT_UNDERFLOW:
  case EXCEPTION_FLT_INVALID_OPERATION:
    todo=DisplayBetaStack( FpExceptErr, theObj, pc, sig); break;
  default:
    todo=DisplayBetaStack( UnknownSigErr, theObj, pc, sig);  
  }
  
  if (todo) {
    /* continue after ValhallaOnProcessStop */
    DEBUG_VALHALLA(fprintf(output,"BetaSignalHandler: EXCEPTION_CONTINUE_EXECUTION\n"));
    return OUR_EXCEPTION_CONTINUE_EXECUTION;
  } else {
    BetaExit(1);
    /* return OUR_EXCEPTION_CONTINUE_SEARCH; */
  }
  return OUR_EXCEPTION_CONTINUE_SEARCH;
}

/* beta_main: called from _AttBC */
void beta_main(void (*AttBC)(Component *), Component *comp)
{
  /* Set up structured exception handling for rest of execution */
#ifdef nti_gnu
  __try1 (BetaSignalHandler_GNU)
      /* Start BETA execution */
      AttBC(comp);
  __except1

#else
  __try 
    { 
      /* Start BETA execution */
      AttBC(comp);
    }
  __except ( BetaSignalHandler(GetExceptionInformation()))
    {
    }
#endif
}

#endif /* nti */
/***************************** END nti ********************************/


/***************************** BEGIN ppcmac ********************************/
#ifdef ppcmac
#ifdef PERSIST


int proxyTrapHandler(ExceptionInformation *info)
{
	pc_t pc;
	unsigned long instruction;
	
	int opcode;
	int TO;
	int reg;
	long *proxy;
	Object *real;
	ProtoType   *proto;
	UnsignedWide *registers;
	
	
	registers = &info->registerImage->R0;
	pc = (pc_t) info->machineState->PC.lo;
	instruction = *pc;
	
	/* fprintf(output, "0x%08X\n", instruction); */
	
	/* FIXME: should verify that instruction = TWLEI Rxx 0 */
	
	opcode = (instruction >> 26);
	TO = (instruction >> 21) & (0xFF >> 3);
	reg = (instruction >> 16) & (0xFF >> 3);

	/* fprintf(output, "register = %d\n", reg);
	   fprintf(output, "address = 0x%08X\n", info->registerImage->R28.lo); */
	proxy = (long *) registers[reg].lo;
		
	if(inPIT(proxy)) {
		real = (Object *)unswizzleReference(proxy);
		/* fprintf(output, "address = 0x%08X\n", real);
		   proto = GETPROTO(real);
		   fprintf(output, "proto = %s\n", ProtoTypeName(proto)); */
		registers[reg].lo = (long) real;
		return 1;
	}
	
	
	return 0;
}

#endif


static int entered = 0;

OSStatus BetaSignalHandler(ExceptionInformation *info)
{
  Object * theObj;
  pc_t pc;
  long todo = 0;
  ExceptionKind sig = info->theKind;
  
  
  if(entered) {
  	ExitToShell();
  }
  
  entered = 1;
  
  
  /* Set StackEnd to the stack pointer just before exception */
  StackEnd = StackEndAtSignal = (long *)info->registerImage->R1.lo;
  pc = (pc_t) info->machineState->PC.lo;
  /* Try to fetch the address of current Beta object from i0.*/
  theObj = (Object *) info->registerImage->R31.lo;
  if( !inIOA(theObj) || !isObject(theObj)) theObj = 0;
  
  DEBUG_CODE({
    fprintf(output, "\nBetaSignalHandler: Caught signal %d", (int)sig);
    PrintSignal((int)sig);
    fprintf(output, ", PC = 0x%08x, StackEnd = 0x%08x, obj = ", (int) pc, (int) StackEnd);
	fflush(output);
	PrintObject(theObj);
	fprintf(output, ".\n");
  });


  switch(sig){
#if 0 /* Not used on PPC */
  case integerException:
    todo=DisplayBetaStack( ArithExceptErr, theObj, pc, sig); break;
#endif
  case trapException:
    /* FIXME: possibly some details in the exception records can determine
     * if it is a refnone or another trap. E.g. one could check if the
     * instruction at PC is "twlei reg,0".
     */
	 
	todo = 0;
#ifdef PERSIST
	todo=proxyTrapHandler(info);
#endif
	if(!todo) {
    	todo=DisplayBetaStack( RefNoneErr, theObj, pc, sig); 
	}
	break;
		
  case illegalInstructionException:
    todo=DisplayBetaStack( IllegalInstErr, theObj, pc, sig);break;
  case accessException: 
  case unmappedMemoryException: 
  case excludedMemoryException: 
  case readOnlyMemoryException: 
  case unresolvablePageFaultException: 
    todo=DisplayBetaStack( SegmentationErr, theObj, pc, sig); break;
  case stackOverflowException:
    todo=DisplayBetaStack( StackErr, theObj, pc, sig); break;
  case floatingPointException:
    /* FIXME: handle zerodiv (int+fp) */
    todo=DisplayBetaStack( FpExceptErr, theObj, pc, sig); break;
  default:
    todo=DisplayBetaStack( UnknownSigErr, theObj, pc, sig); break;
  }

  if (!todo) BetaExit(1);

  entered = 0;
  return noErr;
}

ExceptionHandler default_exceptionhandler;

#endif /* ppcmac */
/***************************** END ppcmac ********************************/




/************************************************************************/ 
/************ InstallSigHandler: install a handler for sig **************/
/************************************************************************/ 

void InstallSigHandler (int sig, void (handler)(int))
{
#ifndef nti
  DEBUG_CODE({
    fprintf(output, "InstallSigHandler: ");
    PrintSignal(sig);
    fprintf(output, "\n");
  });
#if defined(linux) || defined(sgi)
    signal (sig, handler);
#else /* linux || sgi */
  { struct sigaction sa;
    /* Specify that we want full info about the signal, and that
     * the handled signal should not be blocked while being handled: 
     */
    sa.sa_flags = SA_SIGINFO | SA_RESETHAND;
    /* No further signals should be blocked while handling the specified
     * signals. 
     */
    sigemptyset(&sa.sa_mask); 
    /* Specify handler */
#ifdef macosx
    sa.sa_sigaction = handler;
#else
    sa.sa_handler = handler;
#endif
    sigaction(sig,&sa,0);
  }
#endif  /* linux || sgi */
#endif  /* !nti */
}

/* 
 * SetupBetaSignalHandlers: install standard sig handlers for BETA.
 * Called from Initialize().
 */
void SetupBetaSignalHandlers(void)
{
  /* Setup signal handlers for the Beta system */
#ifdef ppcmac
  default_exceptionhandler = InstallExceptionHandler((ExceptionHandler)BetaSignalHandler);
#endif /* ppcmac */
  
#if defined(UNIX)
  void (*handler)(int);
#ifdef macosx
  /* All signals go through 
   *   SignalCatcher -> SignalWrapper -> proxyTrapHandler -> BetaSignalHandler
   */
  handler = (void (*)(int))BetaSignalCatcher;
#else
  handler = (void (*)(int))BetaSignalHandler;
#endif /* macosx */

#ifdef SIGTRAP
  InstallSigHandler(SIGTRAP, handler);
#endif
#ifdef SIGFPE
  InstallSigHandler(SIGFPE,  handler);
#endif
#ifdef SIGILL
  InstallSigHandler(SIGILL,  handler);
#endif
#ifdef SIGBUS
  InstallSigHandler(SIGBUS,  handler);
#endif
#ifdef SIGSEGV
  InstallSigHandler(SIGSEGV, handler);
#endif
#ifdef SIGEMT
  InstallSigHandler(SIGEMT,  handler);
#endif
#ifdef SIGINT
  InstallSigHandler(SIGINT,  handler);
#endif

#ifdef MT
  SetupVirtualTimerHandler(); /* interrupt every 0.1 second */
#endif

#if defined(PERSIST)
  /* Install Proxy Trap Handler to catch RefNone correctly
   * independently of whether Persistence is enabled or not.
   */
#ifndef macosx /* all signals already go through proxyTrapHandler on macosx */
   initProxyTrapHandler();
#endif /* macosx */
#endif /* PERSIST */
#endif /* UNIX */
} /* SetupBetaSignalHandlers */

#ifdef RTDEBUG
void PrintSignal(int sig)
{
  switch (sig){
#ifdef UNIX
  case SIGFPE:  fprintf(output, " <SIGFPE>"); break;
  case SIGILL:  fprintf(output, " <SIGILL>"); break;
  case SIGBUS:  fprintf(output, " <SIGBUS>"); break;
  case SIGSEGV: fprintf(output, " <SIGSEGV>"); break;
#ifdef SIGTRAP
  case SIGTRAP: fprintf(output, " <SIGTRAP>"); break;
#endif
#ifdef SIGEMT
  case SIGEMT:  fprintf(output, " <SIGEMT>"); break;
#endif
  case SIGINT:  fprintf(output, " <SIGINT>"); break;
#endif /* UNIX */
#ifdef nti
  case EXCEPTION_ACCESS_VIOLATION:
    fprintf(output, " <EXCEPTION_ACCESS_VIOLATION>"); break;
  case EXCEPTION_DATATYPE_MISALIGNMENT:
    fprintf(output, " <EXCEPTION_DATATYPE_MISALIGNMENT>"); break;
  case EXCEPTION_STACK_OVERFLOW:
    fprintf(output, " <EXCEPTION_STACK_OVERFLOW>"); break;
  case EXCEPTION_BREAKPOINT:
    fprintf(output, " <EXCEPTION_BREAKPOINT>"); break;
  case EXCEPTION_ARRAY_BOUNDS_EXCEEDED:
    fprintf(output, " <EXCEPTION_ARRAY_BOUNDS_EXCEEDED>"); break;
  case STATUS_ILLEGAL_INSTRUCTION:
    fprintf(output, " <STATUS_ILLEGAL_INSTRUCTION>"); break;
  case EXCEPTION_PRIV_INSTRUCTION:
    fprintf(output, " <EXCEPTION_PRIV_INSTRUCTION>"); break;
  case EXCEPTION_INT_DIVIDE_BY_ZERO:
    fprintf(output, " <EXCEPTION_INT_DIVIDE_BY_ZERO>"); break;
  case EXCEPTION_FLT_DIVIDE_BY_ZERO:
    fprintf(output, " <EXCEPTION_FLT_DIVIDE_BY_ZERO>"); break;
  case EXCEPTION_FLT_STACK_CHECK:
    fprintf(output, " <EXCEPTION_FLT_STACK_CHECK>"); break;
  case EXCEPTION_FLT_DENORMAL_OPERAND:
    fprintf(output, " <EXCEPTION_FLT_DENORMAL_OPERAND>"); break;
  case EXCEPTION_FLT_INEXACT_RESULT:
    fprintf(output, " <EXCEPTION_FLT_INEXACT_RESULT>"); break;
  case EXCEPTION_FLT_OVERFLOW:
    fprintf(output, " <EXCEPTION_FLT_OVERFLOW>"); break;
  case EXCEPTION_FLT_UNDERFLOW:
    fprintf(output, " <EXCEPTION_FLT_UNDERFLOW>"); break;
  case EXCEPTION_FLT_INVALID_OPERATION:
    fprintf(output, " <EXCEPTION_FLT_INVALID_OPERATION>"); break;
#endif /* nti */
#ifdef ppcmac
  case integerException:
    fprintf(output, " <integerException>"); break;
  case trapException:
    fprintf(output, " <trapException>"); break;
  case illegalInstructionException:
    fprintf(output, " <illegalInstructionException>"); break;
  case accessException:
    fprintf(output, " <accessException>"); break; 
  case unmappedMemoryException:
    fprintf(output, " <unmappedMemoryException>"); break; 
  case excludedMemoryException:
    fprintf(output, " <excludedMemoryException>"); break; 
  case readOnlyMemoryException:
    fprintf(output, " <readOnlyMemoryException>"); break; 
  case unresolvablePageFaultException:
    fprintf(output, " <unresolvablePageFaultException>"); break; 
  case stackOverflowException:
    fprintf(output, " <stackOverflowException>"); break;
  case floatingPointException:
    fprintf(output, " <floatingPointException>"); break;
#endif /* ppcmac */
  }
}
#endif /* RTDEBUG */

#ifndef nti
#ifdef RTDEBUG
void sighandler_use(void)
{
  NotifySignalDuringDump(0);
}
#endif /* RTDEBUG */
#endif /* nti */
