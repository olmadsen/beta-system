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
#include <malloc.h>

typedef struct unixPipe
{
  int readIndex;
  int writeIndex;
} unixPipe;

#define MAX_NO_OF_ARGS 100

#define SEPARATOR      1 
 
#define MAX_PATH       1024

#ifndef MAXHOSTNAMELEN
#define MAXHOSTNAMELEN 512
#endif

char *errstr(err)
int err;
{
  return strerror(err);
}
 
static char dirBuffer[MAXPATHLEN];

char *getCurDir()
{ 
  if (getcwd(dirBuffer,MAXPATHLEN)==NULL)
    return "";
  return dirBuffer;
}



/************************ Pipes and such.. ************************/

int openPipe(unixPipe *aUnixPipe)
{
  int ref[2];
  
  if(pipe(ref)<0) 
    return -1;
  aUnixPipe->readIndex=ref[0];
  aUnixPipe->writeIndex=ref[1];
  return 1;
}

int duplicate(int old, int new)
{
 if(dup2(old,new)<0) 
   return -1;
 return 1;
}

void onSigPipe(void)
{
#ifdef SYSV
  /* reinstall handler - is disabled by system when caught */
  catchSIGPIPE();
#else
  /* No action taken for now */
#endif
}

void catchSIGPIPE(void)
     /* This signal is received if a broken pipe is written */
{
  signal(SIGPIPE,onSigPipe);
}

/******************** Networking : sockets and select ***************/


int openActive(char *host, int port)
{
  struct sockaddr_in addr;
  struct hostent *hostInfo;
  int sock;
  
  signal(SIGPIPE,onSigPipe);
  
  /* Create a socket */
  if((sock=socket(AF_INET,SOCK_STREAM,0))<0)
    return -1;
  
  if((hostInfo=gethostbyname(host)) == NULL) {
    return -1;
  }
  
  /* And connect to the server */
  memset((char *)&addr,0,sizeof(addr)); /* instead of bzero */
  addr.sin_family=AF_INET;
  addr.sin_port=port;
  addr.sin_addr= *(struct in_addr *)(hostInfo->h_addr);
  
  if(connect(sock,(struct sockaddr *)&addr,sizeof(addr))<0)
    return -1;
  
  /* Connection is now established and the descriptor is in sock */
  return sock;
}

char hostBuffer[MAXHOSTNAMELEN];

char *getHostName(void)
{
  if(gethostname(hostBuffer,MAXHOSTNAMELEN)<0)
    return NULL;
  return hostBuffer;
}

int bindPort(int port)
{
  struct sockaddr_in sockaddr;
  int listenSock;
  
  /* Create a socket */
  if((listenSock=socket(AF_INET,SOCK_STREAM,0))<0)
    return -1;
  
  /* Bind the socket */ 
  memset((char *)&sockaddr,0,sizeof(sockaddr)); /* instead of bzero */
  sockaddr.sin_family=AF_INET;
  sockaddr.sin_port=port;
  sockaddr.sin_addr.s_addr=INADDR_ANY;
  if(bind(listenSock,(struct sockaddr *)&sockaddr,sizeof(sockaddr))<0)
    return -1;
  
  if(listen(listenSock,5)<0)
    return -1;
  
  return listenSock;
}

int acceptConnection(int sock)
{
  int newSock;
  struct sockaddr_in from;
  int fromaddrlen=sizeof( struct sockaddr_in );
  
  while((newSock=accept(sock,(struct sockaddr *)&from,&(fromaddrlen)))<0)
    {if(errno!=EINTR) 
      return -1;
    sleep(1);
    }
  return newSock;
}


int selectIndex(int *candidates /* IN  - the filedescriptors to be checked */,
		int *active     /* OUT - the "active" filedescriptors  */,
		int timeout     /* IN  - 0 : polling  -1 : blocking 
				 * else timeout specifies a max. time to wait 
				 * for activity.
				 */
		)
/* This function examines a set of file descriptors in order to 
   check which may currently be read without having some exception
   pending on them. If timeout is 0 (polling mode), return is 
   immediate, and if timeout is -1, this function does not return
   until at least one of the indicated file descriptors are readable.
   If neither -1 or 0, a max. time to wait for activity is specified.
   Both the "candidates" and the "active" are represented as an array of
   integers. Entry i in one of the arrays represent the i'th file
   descriptor in the systems descriptor table. To indicate either that
   a descriptor should be checked (in candidates) or that a descriptor
   is readable (in active) the corresponding entry is non-zero.
   Error codes: 
   
   -1 : Error in select call
*/
{
  register i;
  int j,mask=0,checkMask=1,res,exceptMask;
  
  /* convert rep to the corresponding bitmask */
  for(i=0;i < 32; i++)
    {if(candidates[i]) 
      mask = mask | ( 1 << i );
    active[i]=0;
    }
  
  /* check for exceptions on the same descriptors */
  exceptMask=mask;
  if(timeout>=0)
    /* polling */
    {struct timeval timer;
    
    timer.tv_sec=timeout;
    timer.tv_usec=0;
    if((res=select(32, (fd_set *)&mask, NULL, (fd_set *)&exceptMask, &timer)) < 0)
      return -1;
    }
  else
    /* blocking */
    if((res=select(32, (fd_set *)&mask, NULL, (fd_set *)&exceptMask, NULL)) < 0)
      return -1;
  /* make sure that desc. holding an exception are not */
  /* considered active */
  mask=(~exceptMask) & mask;
  /* convert the mask of active desc. to an array */
  for(i=0; i < 32 ; i++)
    {if(mask & checkMask)
      active[i]=1; /* mark the active file descriptor */
    checkMask = checkMask << 1;
    }
  return 1;
} 


extern char **environ;

int startUnixProcess(char *args, char *name, int in, int out)
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
  
  int thisIn,thisOut;
  int i; 
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
      if(*args==SEPARATOR){
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
  
  switch(pid=FORK()){
  case 0 : 
    /* Child: */
    {
      dup2(in,0);
      dup2(out,1);
      if (in != 0 && in != 1) 
	close(in);
      if (out != 0 && out != 1) 
	close(out);
      execve(name,argRep,environ); 
      _exit(1);
    }
  case -1 : 
    /* Error: */
    {
      return -1;
    }
  default : 
    /* Parent: */
    {
      return pid;
    }
  }
}


int stopUnixProcess(int pid)
{
  if(kill(pid,SIGKILL)<0)
    if(errno == EPERM) 
      return -1;
  return 1;
}

int awaitNotExecuting(int pid)
{
  /* Waits for the process denoted by process identity, pid to die or 
   * receive a signal. The call does NOT return until the process has
   * either died or been signalled. A return of 1 means that the process
   * died, and a return of 2 implies that the process was somehow signaled.
   * Error codes to be returned:
   * 
   * -1 : Error in system call
   * 0 : The indicated process was not a child of the calling process
   */
#ifdef linux
  union wait status;
#else
  int status;
#endif
  
  for(;;){
    int result;
    if((result=(int)wait(&status))<0){
      if(errno==ECHILD)
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
#else
 int stat = 0, res;
 int flags;
#ifdef linux
 flags = WNOHANG;
#else
 flags = WNOHANG | WNOWAIT;
#endif
 while ((res = waitpid(pid, NULL, flags)) == -1) {
   if (errno != EINTR)
     break;
 }
 if (res == 0) {
   return 1;
 }
 return 0;
#endif
}


/* Return UNIX variable errno */
int getErrno()
{
  return errno;
}

