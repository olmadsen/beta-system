
#include <stdio.h>
#include <signal.h>

void sighandler ()
{
  fprintf (stderr, "sighandler called\n");
}

main ()
{
  signal (SIGINT,sighandler);

  while (1);
}
