#include <stdio.h>
#ifdef linux
#include <signal.h>
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
#else
#include <sys/signal.h>
#endif
/*#include <sys/cache.h>*/

static int breakaddress;
extern long breakpoint asm("breaklabel");

void onBreakpointHit ();

void InstallHandler (int sig)
{ struct sigaction act;
  
  /* SETUP SIGNALHANDLER:
   * ==================== */
  
  act.sa_handler = onBreakpointHit;
  sigemptyset (&act.sa_mask);
  act.sa_flags = SA_RESETHAND;
  
  sigaction (sig, &act, 0);
  /*cachectl (CC_IPURGE,0,0);*/
}

void onBreakpointHit (
#ifdef sun4s
long sig, siginfo_t *info, ucontext_t *ucon
#else
#ifdef linux
long sig, struct sigcontext scp
#else
long sig, long code, struct sigcontext * scp
#endif
#endif
)
{ 
  long PC=0;
#ifdef sparc
  PC = (long) ucon->uc_mcontext.gregs[REG_PC];
#endif
#if defined(hpux) || defined(sgi) /* hppa, hpux9mc, sgi */
  PC = (long) scp->sc_pc
#endif
#ifdef linux
  if (sig==SIGTRAP){
    scp.eip -= 1; /* Points just after int3 instruction */
  }
  PC = (long) scp.eip;
#endif

  fprintf (stderr, "onBreakpointHit. sig = %d, PC=0x%x\n", sig, PC);
  fprintf (stderr,"Waiting for original opcode to be restored\n");
  fprintf (stderr, "(Type <return> in coretest)\n");

  getchar ();

  fprintf (stderr, "Code value at breakpoint: 0x%08x\n", breakpoint);
  fprintf (stderr,"Returning to breakaddress\n");

  InstallHandler (sig);
}

void onTrace ()
{
  fprintf (stderr, "onTrace\n");
  fprintf (stderr,"Waiting for original opcode to be restored\n");
  
  getchar ();
  
  fprintf (stderr,"Returning to breakaddress\n");
}


void breakProc ()
{
  fprintf (stderr, "Before break\n");
  asm volatile (".global breaklabel");
  asm volatile ("breaklabel:");
  fprintf (stderr, "After break\n");
}

main ()
{ 
#ifdef SIGEMT
  InstallHandler (SIGEMT);
#endif
#ifdef linux
  InstallHandler (SIGTRAP);
#endif
  InstallHandler (SIGILL);
  InstallHandler (SIGSEGV);
  InstallHandler (SIGBUS);

  breakaddress = (int) &breakpoint;

  fprintf (stderr, "Code value at breakpoint: 0x%08x\n", breakpoint);
  fprintf (stderr, "Waiting for breakpoint to be set\n");
  fprintf (stderr, "(Run: coretest %d %d)\n", breakaddress, getpid ());
  getchar ();
  fprintf (stderr, "Code value at breakpoint: 0x%08x\n", breakpoint);
  fprintf (stderr, "Calling breakProc\n");

  breakProc ();

  fprintf (stderr, "After breakProc\n");
}
