#include <stdio.h>
#include <unistd.h>

static char **envp;
static char **argv;
static int envc,argc;  
extern char **environ;

void initParamsAndEnv (int numParam, int numEnv)
{
  envp = (char **) malloc ((numEnv+2)*sizeof(char*));
  argv = (char **) malloc ((numParam+2)*sizeof(char*));
  envc=0;
  argc=1;
}

typedef void (*forEachEnv) (char*,char*);

void extScanEnv (forEachEnv forEach) 
{ 
  char name[100], value[1000], ch;
  int i,j;
  
  i=0;
  while (environ[i]) {
    j=0;
    while ((name[j]=environ[i][j])!='=') j++;
    name[j]=0;
    strcpy (value,&(environ[i][j])+1);
    forEach (name,value);
    i++;
  }
}   

int getfileno (FILE* f)
{
  return fileno(f);
}  

void addEnv (char *name, char* value)
{ char tmp[1000];
  
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
    _exit (99); /* Call _exit instead of exit if an execve after a fork
                 * fails. See why in man(2) vfork. */
    
  }
  
  return pid;
}

char *valhallaMachineName()
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

