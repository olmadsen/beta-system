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
#endif
#ifdef linux
#include <fpu_control.h>
#endif

/***************************************************************************/
/*************************** HELPER FUNCTIONS ******************************/
/***************************************************************************/

#ifdef RTDEBUG

static void NotifySignalDuringDump(int sig)
{
  BetaErr err;
  switch ((int)sig){
#ifdef UNIX
  case SIGINT: err=InterruptErr; break;
  case SIGSEGV: err=SegmentationErr; break;
  case SIGBUS: err=BusErr; break;
  case SIGILL: err=IllegalInstErr; break;
#endif /* UNIX */
  default: err=UnknownSigErr;
  }
  NotifyErrorDuringDump((BetaErr)isMakingDump, err);
}
#endif /* RTDEBUG */


#ifdef UNIX
static int HandleInterrupt(Object *theObj, long *pc, int sig)
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


/* FIXME: The SaveXXXRegisters and RestoreXXXRegisters functions
 * may easily be abstracted into a general set of two functions
 * SaveTrapRegisters/RestoreTrapRegisters using appropriate defines from
 * registers.h like REG_A1, REG_A1_TXT, Reg_D0, ... (not yet there)
 * See http://www.daimi.au.dk/~beta/doc/betarun/internal/trapcallbacks.html
 * for details.
 */

#ifdef intel

/*
 * Since valhalla may now trigger
 * GC in scripts evaluated in the context of debuggee, we have
 * to make sure that Reference registers are updated during these
 * GC's. So we fetch EDX, EDI, EBP and ESI from the scp and put them 
 * on a reference stack (which is GC'ed). We then put the (updated) values
 * back after completing DisplayBetaStack (which calls 
 * valhallaOnProcessStop).
 */

#ifdef linux

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

#endif /* linux */


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

#endif /* x86sol */


#ifdef nti
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
#endif /* nti */

#endif /* intel */

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
#endif /* sgi */

void set_BetaStackTop(long *sp)
{
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


/******************** BEGIN general UNIX handler ***************************/
#if defined(UNIX) && !(defined(sun4s) || defined(x86sol))

#ifdef linux 
#define GetPCandSP() { pc = (long *) scp.eip; StackEnd = (long *) scp.esp_at_signal; }
#endif

#ifdef hppa
/* FIXME: There is a bug in the HP-UX 10 signal.h file. It still
 * defines sc_gr31 as 
 *    #define       sc_gr31 sc_sl.sl_ss.ss_gr31
 * despite that the save_state (ss) structure in machine/save_state.h
 * is very much reorganized.
 * Here we try to work around it by checking if SS_WIDEREGS is defined.
 * This flag has appeared in HP-UX10 and can thus be used to identify
 * the buggy gr31 etc macros. 
 */
#ifdef SS_WIDEREGS
/* HP-UX 10 */
/* The following will work with SS_WIDEREGS set in ss_flags, which is
 * always the case on "our" HP's (HPPA 1.1). See large comment in the 
 * beginning of /usr/include/machine/save_state.h.
 */
#undef sc_gr31
#define sc_gr31 sc_sl.sl_ss.ss_narrow.ss_gr31
#undef sc_gr3
#define sc_gr3 sc_sl.sl_ss.ss_narrow.ss_gr3
#undef sc_pcoq_head
#define sc_pcoq_head sc_sl.sl_ss.ss_narrow.ss_pcoq_head
#endif /* SS_WIDEREGS */

#ifdef UseRefStack
#define GetPCandSP() { \
  pc = (long *) (scp->sc_pcoq_head & (~3)); \
  /* StackEnd not used */\
}
#else /* UseRefStack */
#define GetPCandSP() { \
  pc = (long *) (scp->sc_pcoq_head & (~3)); \
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
  output = stderr;
  DEBUG_CODE({
    fprintf(output, "\nExitHandler: Caught signal %d", (int)sig);
    PrintSignal((int)sig);
    fprintf(output, " during signal handling.\n");
    fflush(output);
  });
#endif
  if (isMakingDump) {
#if 0
    NotifySignalDuringDump((int)sig);
#endif 
  }
  BetaExit(1); 
}

#if defined(linux)
void BetaSignalHandler(long sig, struct sigcontext_struct scp)
#else
void BetaSignalHandler(long sig, long code, struct sigcontext * scp, char *addr)
#endif
{
#ifndef linux
  Object ** theCell;
#endif
  Object *    theObj = 0;
  long *pc;
  long todo = 0;

  DEBUG_CODE({
    fprintf(output, "\nBetaSignalHandler: Caught signal %d", (int)sig);
    PrintSignal((int)sig);
    NON_LINUX_CODE(fprintf(output, " code %d", (int)code));
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
  GetPCandSP();

#ifdef sgi
  { 
    pc = (long *) scp->sc_pc;
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
      if (IsBetaCodeAddrOfProcess((unsigned long)pc)){
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
#endif

#if defined(linux)
#define fpu_sw scp.fpstate->status
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
    if ( (*((char*)pc-1)) == (char)0xcc ){
      /* int3 break */
      scp.eip -= 1; /* pc points just after int3 instruction */
      pc = (long *) scp.eip;
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
#endif /* defined(linux) */

#ifdef hppa
  /* Try to fetch the address of current Beta object in %r3 (This).*/
  /* See /usr/include/sys/signal.h and /usr/include/machine/save_state.h */
  theCell = (Object **) &scp->sc_gr3;
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
	pc = (long*)((scp->sc_gr31 & (~3)) - 8);
	todo=DisplayBetaStack( ZeroDivErr, theObj, pc, sig); break;
      case 0xe: /* fp div by zero */
	todo=DisplayBetaStack( FpZeroDivErr, theObj, pc, sig); break;
      default: /* other floating point exception */
	todo=DisplayBetaStack( FpExceptErr, theObj, pc, sig);
      }
      break;
    case SIGEMT:
      todo=DisplayBetaStack( EmulatorTrapErr, theObj, pc, sig); break;
    case SIGILL:
      todo=DisplayBetaStack( IllegalInstErr, theObj, pc, sig);
      break;
    case SIGBUS:
      todo=DisplayBetaStack( BusErr, theObj, pc, sig); break;
    case SIGSEGV:
      todo=DisplayBetaStack( SegmentationErr, theObj, pc, sig); break;
    case SIGINT: /* Interrupt */
      todo=HandleInterrupt(theObj, pc, sig); break;
    default:
      todo=DisplayBetaStack( UnknownSigErr, theObj, pc, sig);
  }
#endif /* hppa */

  if (!todo) BetaExit(1);
}

#endif /* UNIX, !sun4s */
/******************** END general UNIX handler ****************************/


/******************************** BEGIN sun4s/sparc **************************/
#ifdef sun4s

static void ExitHandler(int sig)
{
  DEBUG_CODE({
    fprintf(output, "\nExitHandler: Caught signal %d", (int)sig);
    PrintSignal((int)sig);
    fprintf(output, " during signal handling.\n");
    fflush(output);
  });
  if (isMakingDump) {
#if 0
    NotifySignalDuringDump((int)sig);
#endif
  }
  BetaExit(1);
}

void BetaSignalHandler (long sig, siginfo_t *info, ucontext_t *ucon)
{
  Object ** theCell;
  Object *    theObj = 0;
  long *pc;
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
  pc = (long *) ucon->uc_mcontext.gregs[REG_PC];

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
      pc = (long*) ucon->uc_mcontext.gregs[REG_O7];
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
    if (IsBetaCodeAddrOfProcess((unsigned long)pc)){
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

/******************************** BEGIN x86sol **************************/
#ifdef x86sol

static void ExitHandler(int sig)
{
  DEBUG_CODE({
    fprintf(output, "\nExitHandler: Caught signal %d", (int)sig);
    PrintSignal((int)sig);
    fprintf(output, " during signal handling.\n");
    fflush(output);
  });
  if (isMakingDump) {
#if 0
    NotifySignalDuringDump((int)sig);
#endif
  }
  BetaExit(1);
}

void BetaSignalHandler (long sig, siginfo_t *info, ucontext_t *ucon)
{
  Object *    theObj = 0;
  long *pc;
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
  pc = (long *) ucon->uc_mcontext.gregs[PC];

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
      if (IsBetaCodeAddrOfProcess((unsigned long)pc)){
	todo=DisplayBetaStack( RefNoneErr, theObj, pc, sig);
      } else {
	todo=DisplayBetaStack( SegmentationErr, theObj, pc, sig);
      }
    }
    break;
  case SIGTRAP: 
    if ( (*((char*)pc-1)) == (char)0xcc ){
      /* int3 break */
      ucon->uc_mcontext.gregs[EIP] -= 1; /* pc points just after int3 instruction */
      pc = (long *) ucon->uc_mcontext.gregs[EIP];
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


/***************************** BEGIN nti ********************************/
#ifdef nti
#ifdef PERSIST
extern int proxyTrapHandler(CONTEXT* pContextRecord);
#endif

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
  long *pc;
  long todo = 0;
  long sig;

  if (NoCatchException) return OUR_EXCEPTION_CONTINUE_SEARCH;
  
  if (pContextRecord->ContextFlags & CONTEXT_CONTROL){
    pc       = (long *)pContextRecord->Eip;
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
      pc = (long *) --pContextRecord->Eip;
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
	unsigned long *pc;
	unsigned long instruction;
	
	int opcode;
	int TO;
	int reg;
	long *proxy;
	Object *real;
	ProtoType   *proto;
	UnsignedWide *registers;
	
	
	registers = &info->registerImage->R0;
	pc = (unsigned long *) info->machineState->PC.lo;
	instruction = *pc;
	
	//fprintf(output, "0x%08X\n", instruction);
	
	/* FIXME: should verify that instruction = TWLEI Rxx 0 */
	
	opcode = (instruction >> 26);
	TO = (instruction >> 21) & (0xFF >> 3);
	reg = (instruction >> 16) & (0xFF >> 3);

	//fprintf(output, "register = %d\n", reg);
	
	//fprintf(output, "address = 0x%08X\n", info->registerImage->R28.lo);
	proxy = (long *) registers[reg].lo;
		
	if(inPIT(proxy)) {
		real = (Object *)unswizzleReference(proxy);
		//fprintf(output, "address = 0x%08X\n", real);
		//proto = GETPROTO(real);
		//fprintf(output, "proto = %s\n", ProtoTypeName(proto));
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
  long *pc;
  long todo = 0;
  ExceptionKind sig = info->theKind;
  
  
  if(entered) {
  	ExitToShell();
  }
  
  entered = 1;
  
  
  /* Set StackEnd to the stack pointer just before exception */
  StackEnd = StackEndAtSignal = (long *)info->registerImage->R1.lo;
  pc = (long *) info->machineState->PC.lo;
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

void InstallSigHandler (int sig)
{
#if !(defined(sun4s) || defined(x86sol))
#ifdef UNIX
     signal (sig, (void (*)(int))BetaSignalHandler);
#endif
#else /* sun4s || x86sol */
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
  default_exceptionhandler = InstallExceptionHandler((ExceptionHandler)BetaSignalHandler);
#else /* ppcmac */
#if !(defined(sun4s) || defined(x86sol))
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
#ifdef SIGINT
    signal( SIGINT,  (void (*)(int))BetaSignalHandler);
#endif
  }
#endif /* UNIX */
  
#else /* sun4s || x86sol */
  
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
    sigaction( SIGINT,  &sa, 0);
#ifdef x86sol
    sigaction( SIGTRAP,  &sa, 0);
#endif /* x86sol */
  }
#endif /* sun4s || x86sol */
#endif /* ppcmac */

#if defined(UNIX) && defined(PERSIST)
  /* Install Proxy Trap Handler to catch RefNone correctly
   * independently of whether Persistence is enabled or not.
   */
   initProxyTrapHandler();
#endif /* UNIX && PERSIST */

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

#ifdef RTDEBUG
void sighandler_use(void)
{
  NotifySignalDuringDump(0);
}
#endif
