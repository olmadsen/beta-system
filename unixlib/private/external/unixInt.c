#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <netdb.h>
#include <signal.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/param.h>
#include <sys/file.h>
#include <sys/time.h>
#ifndef sgi
#include <sys/timeb.h>
#endif
#include <sys/wait.h>
#include <sys/resource.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <sys/fcntl.h>

#define MAX_NO_OF_ARGS 100

#define SEPARATOR      1 
 
#define MAX_PATH       1024

#ifndef MAXHOSTNAMELEN
#define MAXHOSTNAMELEN 512
#endif

#define PATIENCE 5 /* times to retry syscalls when memory is tight */
#define PATIENT_SLEEP(x) (1 << (PATIENCE - (x)))

char *errstr(int err)
{
  return strerror(err);
}
 
static char dirBuffer[MAXPATHLEN];

char *getCurDir(void)
{ 
  if(getcwd(dirBuffer,MAXPATHLEN)==NULL)
    return "";
  return dirBuffer;
}

/************************ Pipes and such.. ************************/

struct unixPipe
{
  int readIndex;
  int writeIndex;
};

int openPipe(struct unixPipe *aUnixPipe)
{
  int ref[2];
  
  if(pipe(ref)<0) 
    return -1;
  aUnixPipe->readIndex=ref[0];
  aUnixPipe->writeIndex=ref[1];
  fflush(stdout);
  return 1;
}

extern char **environ;

int startUnixProcess(char *name, char *args, int in, int out, int err)
{
  /* This function creates a new process from the executable file with
     name as absolute path. Args is a text that contains the arguments
     for the new process. The args are decoded into a text for matters
     of convenience when passing the args from Beta to this function.
     Individual args are separated by the SEPARATOR char that is defined
     in ./ensemble.h. In and out are filedescriptors denoting open files
     that should be used as stdin and stdout for the new process respectively.
     Several error codes may be returned:
     
     -2 : Wrong arguments to be supplied to the new process
     -1 : Error in some system call, vfork, execve, .....
     default : The process id of the new process
     */

  int patience = PATIENCE;

  int i=0; 
  int pid;
  char *argRep[MAX_NO_OF_ARGS + 1];
  
  /* encode the arguments from the "args" text. Each argument is
   * separated with a SEPARATOR.
   */
  argRep[0]=name;      /* first argument must be the file name */
  if(*args=='\0'){     /* empty args means no arguments */ 
    argRep[1]=NULL;
  } else {
    argRep[1]=args; 
    for(i=2;*args != '\0';args++){
      if (*args==SEPARATOR){
	argRep[i++]=args+1;
	if(i>=MAX_NO_OF_ARGS)
	  return -2;
	*args='\0';
      }
    }
    argRep[--i]=NULL;
  }

#ifdef DEBUG
  while(i--)
    printf("argrep %d : %s",i,argRep[i]);
#endif
  
#ifdef sgi
#define FORK fork
#else
#define FORK vfork
#endif

more_patience: 

  switch(pid=FORK()){
  case 0 : 
    /* Child: */
    {
      int t;
      /* ************* IN *************** */
      /* If out is 0 (stdin) then move out to a neutral fd number */
      if (out == 0)
        {
	  t = dup(out);
	  close(out);
	  out = t;
        }
      /* If err is 0 (stdin) then move out to a neutral fd number */
      if (err == 0)
        {
	  t = dup(err);
	  close(err);
	  err = t;
        }
      /* Make fd 0 the in fd ... */
      if (in != 0) 
        {
          dup2(in,0);
	  if (in != out && in != err)
	      close(in);
	  in = 0;
	}
      else
        {
	  /*
	   * dup clears the FD_CLOEXEC flag, if we don't need to dup we clear
	   * it manually
	   */
	  clearFdCloExec(in);
	}

      /* ************* OUT *************** */
      /* If err is 1 (stdout) then move out to a neutral fd number */
      if (err == 1)
        {
	  t = dup(err);
	  close(err);
	  err = t;
        }
      /* ... and make fd 1 the out fd ... and make fd 2 the stderr */
      if (out != 1) 
        {
          dup2(out,1);
	  if (out != err)
	      close(out);
	  out = 1;
	}
      else
        {
	  /*
	   * dup clears the FD_CLOEXEC flag, if we don't need to dup we clear
	   * it manually
	   */
	  clearFdCloExec(out);
	}

      /* ************* ERR *************** */
      if (err != 2)
        {
	  dup2(err, 2);
	  close(err);
	  err = 2;
	}
      else
        {
	  /*
	   * dup clears the FD_CLOEXEC flag, if we don't need to dup we clear
	   * it manually
	   */
	  clearFdCloExec(err);
	}
      /*
       * Child process may not be BETA and may not expect non-blocking fds
       */
      clearFdNonBlock(in);
      clearFdNonBlock(out);
      clearFdNonBlock(err);
      execve(name,argRep,environ); 
      _exit(1);
    }
  case -1 : 
    /* Error: */
    {
      patience--;
      if (patience > 0 && errno == EAGAIN) {
        fprintf(stderr, "Memory is tight ... trying again to fork\n");
        sleep(PATIENT_SLEEP(patience));
        goto more_patience;
      }
      if (errno == ENOMEM) {
        fprintf(stderr, "Not enough memory to fork...\n");
      }
      return -1;
    }
  default : 
    /* Parent: */
    {
      /* close(out); */
      return pid;
    }
  }
}


int stopUnixProcess(pid)
int pid;

{
 if(kill(pid,SIGKILL)<0)
   if(errno == EPERM) 
     return -1;
 return 1;
}

int awaitNotExecuting(pid)
int pid;

/* Waits for the process denoted by process identity, pid to die or 
   receive a signal. The call does NOT return until the process has
   either died or been signalled. A return of 1 means that the process
   died, and a return of 2 implies that the process was somehow signaled.
   Error codes to be returned:

   -1 : Error in system call
    0 : The indicated process was not a child of the calling process
    
*/
{
#ifdef linux
  union wait status;
#else
  int status;
#endif

 for(;;)
   {int result;
    if((result=(int)wait(&status))<0)
      {if(errno==ECHILD)
          return 0;
       else return -1;
      }
    if(result != pid) 
      continue;
    if(WIFEXITED(status)) 
      return 1;
    if(WIFSIGNALED(status)) 
      return 2;
    return -1;
   }
}

int stillExecuting(int pid)
{
#ifdef hpux
 return 1;
#else /* !hpux */
 int res;
 int flags;
#if defined(linux) || defined(macosx)
 flags = WNOHANG;
#else /* !linux */
 flags = WNOHANG | WNOWAIT;
#endif /* linux */
 while ((res = waitpid(pid, NULL, flags)) == -1) {
   if (errno != EINTR)
     break;
 }
 if (res == 0) {
   return 1;
 }
 return 0;
#endif /* hpux */
}


/* Return UNIX variable errno */
int getErrno()
{
  return errno;
}

