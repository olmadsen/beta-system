#include "coreaccess_ptrace.h"
#include <errno.h>
#include <stdlib.h>

main (int argv, char *argc[])
{ int address = atoi (argc[1]);
  int pid = atoi (argc[2]);
  int oldinstruction;

  fprintf (stderr, "breakaddress = %d, pid = %d\n", address, pid);

  if (SetBreak (pid,address,&oldinstruction)) {
    fprintf (stderr, "Breakpoint set failed. errno = %d\n", errno);
    exit (99);
  }

  fprintf (stderr, "Old instruction = 0x%x\n", oldinstruction);
  
  fprintf (stderr, "Waiting\n");
  getchar ();

  if (UnsetBreak (pid,address,oldinstruction)) {
    fprintf (stderr, "Breakpoint remove failed\n");
    exit (99);
  }
}
