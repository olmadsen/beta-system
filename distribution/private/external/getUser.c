#include <unistd.h>
#include <stdio.h>

char user[10];

char* getUser ()
{ FILE *f;

  f = popen ("whoami","r");
  fscanf (f, "%s", user);
  pclose (f);
  
  return user; 
}

