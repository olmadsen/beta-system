#include <unistd.h>
#include <stdio.h> 
#include <stdlib.h>
#include <errno.h>

/* #define SADDEBUG 1 */

#ifdef SADDEBUG
#define SADOUT "/users/beta/r4.1/distribution/v1.6/test/sadout"
#endif

char tmp[100];

int getNum (char* str, int* next)
{ int first = *next;
  
  while (str[*next] != '.') (*next)++;

  memcpy (tmp,&str[first],(*next) - first);
  tmp[(*next) - first] = 0;
  
  (*next)++;

  return atoi (tmp);
}

char* getStr (char* str, int* next)
{ char* res;
  int len;

  len = getNum (str,next);
  res = (char *) malloc (len+1);
  memcpy (res,&str[*next],len);
  res[len] = 0;
  *next += len;
  
  return res;
}

main (int argc, char** argv, char** envp)
{ 
  char *machinetype;
  char *apppath;
  char *environment;
  char *parameters;
  char *tmp;

  char *unexpanded;
  char executable[200] = "";

  char** newEnv;
  char** newParams;

#ifdef SADDEBUG
  FILE *f;
#endif

  int cur;
  int newCount;
  int oldCount;
  int i;
  int sp; /* Space position */

  machinetype = argv[1];
  apppath = argv[2];
  environment = argv[3];
  parameters = argv[4];

  /* Replace '$' in the original apppath string with "machinetype". */

  cur = 0;
  unexpanded = getStr (apppath, &cur);
  while (i = getNum (apppath, &cur)) {
    tmp = unexpanded + i - 1;
    tmp[0] = 0;
    strcat (executable, unexpanded);
    strcat (executable, machinetype);
    unexpanded = tmp+1;
  }
  strcat (executable, unexpanded);

#ifdef SADDEBUG
  f = fopen (SADOUT, "a");
  fprintf (f, "Executable name: '%s'\n", executable); fflush (f);
  fprintf (f, "Machine type: '%s'\n", machinetype); fflush (f);
#endif

  cur = 1;
  newCount = getNum (environment,&cur);
  
  for (oldCount = 0; envp[oldCount]; oldCount++) ;

  newEnv = (char **) malloc ((newCount+oldCount+1)*sizeof(char *));
  
  for (i = 0; i < newCount; i++) 
    newEnv[i] = getStr (environment,&cur);
  
  for (i = 0; i < oldCount; i++) 
    newEnv[i+newCount] = envp[i];
  
  newEnv[oldCount+newCount] = 0;
  
  cur = 1;
  
  newCount = getNum (parameters,&cur) + 1;
  
  newParams = (char **) malloc ((newCount+1)*sizeof(char *));

  newParams[0] = executable;
  for (i = 1; i < newCount; i++)
    newParams[i] = getStr (parameters,&cur);

  newParams[newCount] = 0;

#ifdef SADDEBUG
  for (i = 0; newEnv[i]; i++)
    fprintf (f, "Environment value %d: '%s'\n", i, newEnv[i]); fflush (f);

  for (i = 0; newParams[i]; i++)
    fprintf (f, "Parameter value %d: '%s'\n", i, newParams[i]); fflush (f);
  
  fclose (f);
#endif

  execve (executable, newParams, newEnv);

#ifdef SADDEBUG
  f = fopen (SADOUT, "a");
  fprintf (f, "execve errno = %d\n", errno); fflush (f);
  fclose (f);
#endif

  if (errno == ENOENT)
    exit (1);  /* The executable did not exist */
  else
    exit (99); /* Some other error occurred. */
}

