#include <stdio.h>
#include <sys/signal.h>
/*#include <sys/cache.h>*/

static int breakaddress;
extern short breakpoint asm("breaklabel");

void onBreakpointHit (int sig);

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

void onBreakpointHit (int sig)
{
  fprintf (stderr, "onBreakpointHit. sig = %d\n", sig);
  fprintf (stderr,"Waiting for original opcode to be restored\n");

  getchar ();

  fprintf (stderr, "Code value at breakpoint: 0x%x\n", (short) breakpoint);
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
  InstallHandler (SIGEMT);
  InstallHandler (SIGILL);
  InstallHandler (SIGSEGV);
  InstallHandler (SIGBUS);

  breakaddress = (int) &breakpoint;

  fprintf (stderr, "breakaddress = %d. pid = %d\n", breakaddress, getpid ());
  fprintf (stderr, "Code value at breakpoint: 0x%x\n", (long) breakpoint);
  fprintf (stderr, "Waiting for breakpoint to be set\n");
  getchar ();
  fprintf (stderr, "Code value at breakpoint: 0x%x\n", (long) breakpoint);
  fprintf (stderr, "Calling breakProc\n");

  breakProc ();

  fprintf (stderr, "After breakProc\n");
}
