#define INVSOCK(sock) ((sock)<0)

#include <stdio.h>
#include <io.h>
#include <string.h>
#include <errno.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/timeb.h>
#ifndef nti_gnu
# include <dos.h>
#endif
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

#ifdef nti_gnu
  #ifdef fdopen /* fdopen is macro-defined in older version of GNU-SDK */
  #undef fdopen /* we need a "real" fdopen function */
  FILE* fdopen (int nHandle, char* szMode)
  {
  return _fdopen(nHandle,szMode);
  }
  #endif
#endif

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


/* awaitNotExecuting: 
 * Return codes:
 *  
 *  -1 : Error in system call
 *   0 : The indicated process terminated.
 */
int awaitNotExecuting(int pid)
{
  DWORD state = WaitForSingleObject((HANDLE)pid, INFINITE);
  if (state == WAIT_OBJECT_0)
    return 0;
  if (state == WAIT_FAILED)
    return -1;
  return -1;
}

int stillExecuting(int pid)
{
  DWORD state = WaitForSingleObject((HANDLE)pid, 0);
  if (state == WAIT_TIMEOUT)
    return 1;
  if (state == WAIT_OBJECT_0)
    return 0;
  if (state == WAIT_FAILED)
    return -1;
  return -1;
}

#ifdef nti_bor
# define FINDDATA struct ffblk
# define FINDFIRST(name,info) findfirst(name,info,0)
# define FINDNEXT(handle,info) _findnext(handle,info)
# define FINDDATA_NAME fileinfo.ff_name
# define FINDCLOSE(file)
#else
# define FINDDATA struct _finddata_t
# define FINDFIRST(name,info) _findfirst(name,info)
# define FINDNEXT(handle,info) _findnext(handle,info)
# define FINDDATA_NAME fileinfo.name
# define FINDCLOSE(file) _findclose(file)
#endif

char* CCorrectFilenameCase(char* filename)
{
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


static FINDDATA fileinfo;
static char *NTFfilenames = NULL;
static int NTFcurlen = 0;
static char *NTFcur = NULL;

int OpenNTFindFiles(char* match)
{
  long hFile;
  int count = 0, len = 0;
  NTFcurlen = 0;
  if ((hFile = FINDFIRST(match, &fileinfo)) != -1L) {
    count++;
    len = strlen(FINDDATA_NAME);
    NTFfilenames = malloc(len+1);
    strncpy(NTFfilenames, FINDDATA_NAME, len);
    NTFcurlen += len+1;
    NTFfilenames[NTFcurlen-1]=0;
    while(!FINDNEXT(hFile, &fileinfo)) {
      count++;
      len = strlen(FINDDATA_NAME);
      NTFfilenames = realloc(NTFfilenames, NTFcurlen + len + 1);
      strncpy(NTFfilenames+NTFcurlen, FINDDATA_NAME, len);
      NTFcurlen += len+1;
      NTFfilenames[NTFcurlen-1]=0;
    }
  }
  FINDCLOSE(hFile);
  NTFcur = NTFfilenames;
  return count;
}

char *GetNTFindFiles(void)
{
  char *old = NTFcur;

  if (NTFcur-NTFfilenames >= NTFcurlen-1)
    return NULL;

  while (*NTFcur)
    NTFcur++;
  NTFcur++;

  return old;
}

void CloseNTFindFiles(void)
{
  NTFcur = NULL;
  free(NTFfilenames);
  NTFfilenames = NULL;
}

