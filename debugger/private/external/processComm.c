#include <stdio.h>

static char **envp;
static char **argv;
static int envc,argc;  

void initParamsAndEnv (int numParam, int numEnv)
{
  envp = (char **) malloc ((numEnv+2)*sizeof(char*));
  argv = (char **) malloc ((numParam+2)*sizeof(char*));
  envc=0;
  argc=1;
}

void addEnv (char *name, char* value)
{ char tmp[100];
  
  sprintf (tmp,"%s=%s",name,value);
  envp[envc++] = (char *) strdup (tmp);
}

void addParam (char *name)
{
  argv[argc++] = (char *) strdup (name);
}

int executeProcess (char *execName)
{ int pid;
  int i;
  
  if (pid = vfork ()) {

    /* Free argument and environment strings */
    for (i=0;i<argc;i++) free (argv[i]);
    for (i=0;i<envc;i++) free (envp[i]);
    free (argv); free (envp);

  } else {
    
    argv[0] = execName; argv[argc] = 0; envp[envc] = 0;
    execve (execName,argv,envp);
    fprintf (stderr, "Could not exec %s\n", execName);
    
  }
  
  return pid;
}

char* valhallaMachineName ()
{
  /* Sun variants */
#ifdef sun
#ifdef sparc
#ifdef sun4s
  return "sun4s";
#else
  return "sun4";
#endif
#else
  return "sun3";
#endif
#endif
  
  /* HP variants */
#ifdef hpux
#ifdef hppa
  return "snake";
#else
  return "hpux8";
#endif
#endif
  
  /* Macintosh */
#ifdef macintosh
  return "mac";
#endif

  /* Linux */
#ifdef linux
  return "linux";
#endif
  
  /* NTI */
#ifdef nti
  return "nti";
#endif
  
  /* default */
  return ""; 
}
