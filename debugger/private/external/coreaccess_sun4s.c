#include <stdio.h>
#include <sys/signal.h>
#include <sys/fault.h>
#include <sys/syscall.h>
#include <sys/procfs.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
 
#include <siginfo.h>
#include <sys/regset.h>
#include <sys/ucontext.h>

#include "coreaccess_sun4s.h"

int breakinstruction = 0; /* Break instruction. */

void onBreakpointHit (long sig, siginfo_t *info, ucontext_t *ucon)
{
  fprintf (stderr, "onBreakpointHit\n");

  /* Send info to debugger ..... */

  /* Unblock SIGILL signal: */
  { sigset_t sigs;
    sigemptyset (&sigs);
    sigaddset (&sigs,SIGILL);
    sigprocmask (SIG_UNBLOCK,&sigs,0);
  };
  
  fprintf (stderr,"Returning to breakaddress\n");
}

/* void Initialize ()
 * ==================
 *
 * Initializes interface to process image.
 *
 * Return values
 *      OK: a file descriptor for the process image
 *      Otherwise: -1 and errno is set
 */

int InitializeCoreAccess (pid_t pid)
{ char filename[20];
  sprintf (filename, "/proc/%d", pid);
  return open (filename,O_RDWR);
}

void CloseCoreAccess (int processFD)
{
  close (processFD);
}

int WriteImage (int processFD, int address, int bytecount, char *buffer)
{ int oldvalue;

  if (bytecount == 4) {
    lseek (processFD,address,SEEK_SET);
    if (read (processFD,&oldvalue,4) < 4) return -1;
  }

  if (pwrite (processFD,buffer,bytecount,address) < bytecount) return -1;

  if (bytecount == 4) (int)(*buffer) = oldvalue;
  
  return 0;
}

int ReadImage (int processFD, int address, int bytecount, char* buffer)
{
  lseek (processFD,address,SEEK_SET);
  if (read (processFD,buffer,bytecount) <= 0) return -1;
  return 0;
}

void prepareProcessForDebug ()
{ struct sigaction sa;

  /* SETUP SIGNALHANDLER:
   * ==================== */

  /* Specify that we want full info about the signal, and that
   * the handled signal should not be blocked while being handled: */
  sa.sa_flags = SA_SIGINFO | SA_NODEFER;

  /* No further signals should be blocked while handling the specified
   * signals. */
  sigemptyset(&sa.sa_mask); 

  /* Specify handler: */
  sa.sa_handler = onBreakpointHit;
    
  sigaction (SIGILL,&sa,0);
}
