#define INVSOCK(sock) ((sock)<0)

#include <stdio.h>
#include <io.h>
#include <string.h>
#include <errno.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/timeb.h>
#include <dos.h>
#ifdef nti_bor
# include <dir.h>
#else
# define MAXPATH 512
#endif
#include <stdlib.h>
#include <windows.h>
#include <winsock.h>

#undef INVSOCK
#define INVSOCK(sock) ((sock)==INVALID_SOCKET)

#include <malloc.h>

#define MAX_NO_OF_ARGS 100

#define SEPARATOR      1 
 
#define MAXPATHLEN MAXPATH

#ifndef MAXHOSTNAMELEN
# define MAXHOSTNAMELEN 512
#endif


int EOFvalue(){return EOF;}


int EOFfunction(F)
FILE *F;
{return feof(F);}



/* ----------------- Functions supporting Stream.GetText -------------------- */

static char *OutOfMemError="Out of memory during StreamGetText\n";

#define INITBUFFERSIZE  500   /* Initial size of Buffer. */

static char *Buffer;          /* Nuffer space allocate here. */
static int  BufferSize=0;     /* Current size of Buffer. */


void InitBuffer()
  {
   BufferSize=INITBUFFERSIZE;
   Buffer=(char *)malloc(BufferSize);
   if(!Buffer)
     {
      fputs(OutOfMemError,stderr);
      exit(147);
     }
  }


void EnlargeBuffer()
  /* Double the size of Buffer or allocate an initial Buffer. */
  {
   BufferSize*=2;
   Buffer=realloc(Buffer,BufferSize);
   if(!Buffer)
     {
      fputs(OutOfMemError,stderr);
      exit(147);
     }
  }

static char streamStatus;

int StreamError()
  /* Return whether or not last call to GetTExtFromStream succeeded. */
  {
   return(streamStatus==EOF);
  }
 

char *GetTextFromStream(F,toEOL)
  /* Read a string from the file. If toEOL is true then read to end of line,
     else read to first space. Skip the character (eol or space) that causes
     reading to stop.
     Call StreamError afterwards to see if operation succeeded.
  */
  FILE *F;
  int  toEOL;
  {
   register FILE *F1;        /* We use a lot of registers for efficiency. */
   register char *Buffer1;
   register int  i,ch;
   int           oldSize;

   if(!BufferSize)            /* The first time, initialize Buffer. */
     InitBuffer();
   F1=F;
   oldSize=0;                 /* This much of Buffer currently used. */
   if(!toEOL)                 /* Skip to first non-blank. */
     {
      while((ch=getc(F1))<=' ' && ch!=EOF) 
        /* SKIP */ ;
      if(ch==EOF || ungetc(ch,F1)==EOF)
        {
         streamStatus=ch;
         return("");
        }
     }
   while(1)
     {
      Buffer1=Buffer+oldSize; /* Insert from this place in Buffer. */
      i=BufferSize-oldSize;
      if(toEOL)               /* We have two almost identical copies of the
                                 inner loop, one reading to eol the other to
                                 a blank.
                              */
        {
         while(i--)           /* While more room in Buffer. */
           {
            if((*Buffer1++=ch=getc(F1))=='\n' || ch==EOF)
              {
               streamStatus=ch;
               Buffer1[-1]=0; /* Skip the stop char. */
               return(Buffer);
              }
           }
        }
      else
        {
         while(i--)           /* While more room in Buffer. */
           {
            if((*Buffer1++=ch=getc(F1))<=' ' || ch==EOF)
              {
               streamStatus=ch;
               Buffer1[-1]=0; /* Skip the stop char. */
               return(Buffer);
              }
           }
        }
      oldSize=BufferSize;
      EnlargeBuffer();
     }
  }

char *errstr(err)
int err;
{
  /* FIXME: should use FormatError() */
  return strerror(err);
}
 
static char dirBuffer[MAXPATHLEN];

char *getCurDir()

{ 
  if(!GetCurrentDirectory(MAXPATHLEN,dirBuffer))
    return "";
  return dirBuffer;
}



/************************ Pipes and such.. ************************/

struct ntPipe 
{
  int readIndex;
  int writeIndex;
};

openPipe(struct ntPipe *aNtPipe)
{
  SECURITY_ATTRIBUTES secAtt;

  secAtt.nLength = sizeof(SECURITY_ATTRIBUTES);
  secAtt.bInheritHandle = TRUE;
  secAtt.lpSecurityDescriptor = NULL;
  
  if (CreatePipe((PHANDLE)(&aNtPipe->readIndex),
		 (PHANDLE)(&aNtPipe->writeIndex),
		 &secAtt,0)) 
    return 1;
  return -1;
}

duplicate(old,new)
int old,new;

{
 if(dup2(old,new)<0) 
   return -1;
 return 1;
}

void onSigPipe()

{/* No action taken for now */}

void catchSIGPIPE()

/* This signal is received if a broken pipe is written */

{/*signal(SIGPIPE,onSigPipe);*/}


/******************** Networking : sockets and select ***************/




/* #define ECHO_ERROR */


static int WSAIsStarted = 0;

static void StopWSA(void)
{
#ifdef ECHO_ERROR
  printf("atexit closing socket communication\n");
#endif
  WSAIsStarted = 0;
/*  Sleep(500);*/
  WSACleanup();
}

#define StartWSA() if (!WSAIsStarted) _StartWSA()

static void _StartWSA(void)
{
  if (!WSAIsStarted) {
    WSADATA wsadata;
#ifdef ECHO_ERROR
    printf("Sockets need to be started\n");
#endif
    if (WSAStartup(MAKEWORD(1,1), &wsadata) == 0) {
#ifdef ECHO_ERROR
      printf("Sockets started :-)\n");
#endif
      WSAIsStarted = 1;
      atexit(StopWSA);
    } else {
#ifdef ECHO_ERROR
      printf("Sockets could not be started :-(\n");
#endif
    }
  }
}



openActive(host,port)
char *host;
int port;
{struct sockaddr_in addr;
 struct hostent *hostInfo;
 int sock;
 
/* signal(SIGPIPE,onSigPipe);*/

 StartWSA();

 /* Create a socket */
 if(INVSOCK(sock=socket(AF_INET,SOCK_STREAM,0)))
   return -1;

 if((hostInfo=gethostbyname(host)) == NULL) {
   return -1;
 }

 /* And connect to the server */
 memset((char *)&addr,0,sizeof(addr)); /* instead of bzero */
 addr.sin_family=AF_INET;
 addr.sin_port=port;
 addr.sin_addr= *(struct in_addr *)(hostInfo->h_addr);
 
 if(INVSOCK(connect(sock,(struct sockaddr *)&addr,sizeof(addr))))
   return -1;

 /* Connection is now established and the descriptor is in sock */
 return sock;
};



 
char hostBuffer[MAXHOSTNAMELEN];

char *getHostName()

{
 if(gethostname(hostBuffer,MAXHOSTNAMELEN)<0)
   return NULL;
 return hostBuffer;
}



bindPort(port)
int port;

{struct sockaddr_in sockaddr;
 int listenSock;

 /* Create a socket */
 if(INVSOCK(listenSock=socket(AF_INET,SOCK_STREAM,0)))
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



acceptConnection(sock)
int sock;

{int newSock;
 struct sockaddr_in from;
 int fromaddrlen=sizeof( struct sockaddr_in );

 while(INVSOCK(newSock=accept(sock,(struct sockaddr *)&from,&(fromaddrlen))))
   {if(errno!=EINTR) 
      return -1;
    Sleep(1);
   }
 return newSock;
}


selectIndex(candidates,active,timeout)
int *candidates; /* IN  - the filedescriptors to be checked */
int *active;     /* OUT - the "active" filedescriptors  */
int timeout;     /* IN  - 0 : polling  -1 : blocking 
                        else timeout specifies a max. time to wait for
                        activity.
                 */

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

{register i;
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

int startNtProcess(aname,args,in,out)
char *args;
char *aname;
int in,out;

/* This function creates a new process from the executable file with
   name as absolute path. Args is a text that contains the arguments
   for the new process. The args are decoded into a text for matters
   of convenience when passing the args from Beta to this function.
   Individual args are separated by the SEPARATOR char that is defined
   in ./ensemble.h. In and out are filedescriptors denoting open files
   that should be used as stdin and stdout for the new process respectively, 
   set to zero, if they are not used.
   Several error codes may be returned:
   
   -2 : Wrong arguments to be supplied to the new process
   -1 : Error in some system call, vfork, execve, .....
   default : The process id of the new process
*/

{
  STARTUPINFO si;
  PROCESS_INFORMATION pi;
  BOOL res;
  char *name;
  char *s,*d;

  si.cb = sizeof(STARTUPINFO);
  si.lpReserved = NULL;
  si.lpDesktop = NULL;
  si.lpTitle = "Program forked by BETA";
  si.dwFlags = STARTF_USESHOWWINDOW | STARTF_USESTDHANDLES;
  si.wShowWindow = SW_SHOWDEFAULT;
  si.cbReserved2 = 0;
  si.lpReserved2 = NULL;
#if 1
  si.hStdInput  = in  ? (HANDLE)in  : GetStdHandle(STD_INPUT_HANDLE);
  si.hStdOutput = out ? (HANDLE)out : GetStdHandle(STD_OUTPUT_HANDLE);
  si.hStdError = GetStdHandle(STD_ERROR_HANDLE);
#endif

/* Set to get arguments quoted in "". It seems that CreateProcess 
   parses the text, and removes the quotes, effectively creating argv.*/
#define QOUTEARGS 0

  name = malloc(strlen(aname) + strlen(args) + 8 + 2 * MAX_NO_OF_ARGS);
  
#if QOUTEARGS
  sprintf(name, "\"%s\" ", aname); /* Copy cmd name into quotes.*/
#else
  sprintf(name, "%s ", aname); /* Copy cmd name.*/
#endif
  
  if (args)    /* Copy arguments, possibly quoting them with "". */
  {
    int sepflag = 1;
    d = name + strlen(name);
#if QOUTEARGS
    *d++ = '"';                  /* start-quote for first argument.*/
#endif
    for (s = args; *s; s++, d++)
    {
      if (*s == SEPARATOR)
      {
	sepflag = 1;
#if QOUTEARGS
	*d = '"';
	*++d = ' ';
	*++d = '"';
#else
	*d = ' ';
#endif
      }
      else
      {
	sepflag = 0;
	*d = *s;
      }
    }
  
    if (sepflag) /* Did it end with en extra separator? (Empty args does) */
    {
#if QOUTEARGS
      d -= 2;
#else
      d -= 1;
#endif 
    }   
    *d = 0;
  }
  res = CreateProcess(NULL, name, NULL, NULL, TRUE, 0,
		      NULL, NULL, &si, &pi);

  free(name);

  if (res)     /* Process create OK */
    return (int)pi.hProcess;

  return -1;
}



int stopNtProcess(pid)
int pid;

{
 if(!TerminateProcess((HANDLE)pid,0))
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
  DWORD retval = WaitForSingleObject((HANDLE)pid, INFINITE);
  if (retval != WAIT_FAILED)
    return (int) retval;
  return -1;
}

int stillExecuting(pid)
int pid;

{
  if (WaitForSingleObject((HANDLE)pid, 1) != WAIT_FAILED)
    return 1;
  return 0;
}

char* CCorrectFilenameCase(char* filename)
{
#ifdef nti_bor
# define FINDDATA struct ffblk
# define FINDFIRST(name,info) findfirst(name,info,0)
# define FINDDATA_NAME fileinfo.ff_name
# define FINDCLOSE(file)
#else
# define FINDDATA struct _finddata_t
# define FINDFIRST(name,info) _findfirst(name,info)
# define FINDDATA_NAME fileinfo.name
# define FINDCLOSE(file) _findclose(file)
#endif
  FINDDATA fileinfo;
  char *s, *t;
  long hFile;
  int res = 0;
  static char buffer[128];
  
  buffer[0]=0;
  if ((hFile = FINDFIRST(filename, &fileinfo)) != -1L) 
  {
    /* As the filename does not contain any wildcards, the casecorrect 
     * copy returned by find should not be longer than filename...
     * It may be shorter, if filename contains a path
     */
    strcpy(buffer, FINDDATA_NAME);
  }

  FINDCLOSE(hFile);
  return buffer;
}
  
