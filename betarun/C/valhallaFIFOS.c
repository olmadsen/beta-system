#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <malloc.h>

char *fromName (pid_t pid)
{ char name[50];
  sprintf (name,"/tmp/betadebugFrom%d",(int)pid);
  return strdup (name);
}

char *toName (pid_t pid)
{ char name[50];
  sprintf (name,"/tmp/betadebugTo%d",(int)pid);
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

void openFIFOSfd (pid_t pid, int *fifoFrom, int *fifoTo)
{ char* name;
  name = fromName (pid); *fifoFrom = open (name,O_RDWR); free (name);
  name = toName (pid); *fifoTo = open (name,O_RDWR); free (name);
}

void deleteFIFOS (pid_t pid)
{ char* name;
  name = fromName (pid); unlink (name); free (name);
  name = toName (pid); unlink (name); free (name);
}
