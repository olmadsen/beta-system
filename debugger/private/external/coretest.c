#include "coreaccess.h"
#include <errno.h>
#include <stdlib.h>
#include <stdio.h>

main (int argv, char *argc[])
{ int address = atoi (argc[1]);
  int pid = atoi (argc[2]);
  int oldinstruction;

  fprintf (stderr, "breakaddress = %d, pid = %d\n", address, pid);

#ifdef sun4s
  coreaccess_init (pid);
#endif

  if (SetBreak (pid,address,&oldinstruction)) {
    fprintf (stderr, "Breakpoint set failed. errno = %d\n", errno);
    exit (99);
  }

  fprintf (stderr, "Old instruction = 0x%08x\n", oldinstruction);
  
  fprintf (stderr, "Waiting\n");
  fprintf (stderr, "(Type <return> in breaktest)\n");
  getchar ();

  if (UnsetBreak (pid,address,oldinstruction)) {
    fprintf (stderr, "Breakpoint remove failed\n");
    exit (99);
  }

  fprintf (stderr, "(Type <return> in breaktest)\n");
  
#ifdef sun4s
  coreaccess_close (pid);
#endif
  
}
