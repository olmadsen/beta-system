#include <stdio.h>
#include <string.h>


FILE* rshBegin (char* command)
{ FILE *thePipe;

  /* printf ("Command: %s\n", command); */

  thePipe = popen (command, "r");
  return thePipe;
}

int getPipeDesc (FILE* thePipe)
{ int fd;
  fd = fileno(thePipe);
  return fd;
}

int rshGetNext (FILE* thePipe)
{ char output[400];

  if (fscanf (thePipe,"%s\n",output) == EOF) return 2;

  if (strcmp (output, "##betadistr##ok") == 0) return 0;
  else if (strcmp (output, "##betadistr##notfound") == 0) return 1;
  else if (strcmp (output, "##betadistr##error") == 0) return 2;
  else return 3;
}

void rshClose (FILE* thePipe)
{ 
  pclose (thePipe);
  /* printf ("After pclose\n"); */
  /* commenting out pclose is necessary if the remotely started 
   * process does not disconnect itself from session context. */
}
