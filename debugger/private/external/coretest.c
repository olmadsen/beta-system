#include "coreaccess_hpux8.h"
#include <errno.h>
#include <stdlib.h>

main (int argv, char *argc[])
{ int address = atoi (argc[1]);
  int pid = atoi (argc[2]);
  int oldinstruction;

  fprintf (stderr, "breakaddress = %d, pid = %d\n", address, pid);

  if (Attach (pid) ||
      ReadImage (pid,address,&oldinstruction) || 
      SetBreak (pid,address,oldinstruction) ||
      Detach (pid)) {
    fprintf (stderr, "Breakpoint set failed. errno = %d\n", errno);
    exit (99);
  }

  fprintf (stderr, "Old instruction = 0x%x\n", oldinstruction);
  
  fprintf (stderr, "Waiting\n");
  getchar ();

  if (Attach (pid) ||
      WriteImage (pid,address,oldinstruction) ||
      Detach (pid)) {
    fprintf (stderr, "Breakpoint remove failed\n");
    exit (99);
  }
}
