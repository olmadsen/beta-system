#include <stdio.h>
#include <beta.h>
#include <sys/types.h>

char *fromName (pid_t pid)
{ char name[50];
  sprintf (name,"/tmp/betadebugFrom%d",pid);
  return strdup (name);
}

char *toName (pid_t pid)
{ char name[50];
  sprintf (name,"/tmp/betadebugTo%d",pid);
  return strdup (name);
}

void createFIFOS (pid_t pid)
{ char* name;
  name = fromName (pid); mkfifo (name,0777); free (name);
  name = toName (pid); mkfifo (name,0777); free (name);
}

void openFIFOS (pid_t pid, FILE **fifoFrom, FILE **fifoTo)
{ char* name;
  name = fromName (pid); *fifoFrom = fopen (name,"r+"); free (name);
  name = toName (pid); *fifoTo = fopen (name,"r+"); free (name);
}

void deleteFIFOS (pid_t pid)
{ char* name;
  name = fromName (pid); unlink (name); 
  fprintf (stderr, "deleteFIFOS: %s\n", name);
  free (name);
  name = toName (pid); unlink (name);
  fprintf (stderr, "deleteFIFOS: %s\n", name);
  free (name);
}
