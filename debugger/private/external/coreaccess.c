#include "coreaccess.h"

#if defined(sun4s) || defined(sgi) || defined(sun4) || defined(linux)

#include <errno.h>
#include <stdio.h>
#include <signal.h>
#include <unistd.h>

#if defined(sun4s) || defined(sgi)

/* Implementation using the /proc file system. */
#include <fcntl.h>

#ifdef sgi
/* The (undocumented) pwrite in IRIX 5.3 does not seem to
 * work. This can probably be dropped when IRIX 5.3 is not needed
 * anymore.
 */
static ssize_t myPwrite(int fildes,
		       const void  *buf, 
		       size_t  nbyte, 
		       off_t offset)
{
  lseek(fildes, offset, SEEK_SET);
  return write(fildes, buf, nbyte);
}
#define pwrite myPwrite
#endif /* sgi */

#define MAX_PID_COUNT 10

static pid_t pids[MAX_PID_COUNT];
static int fds[MAX_PID_COUNT];
static int lastpid = -1;

int getfd (pid_t pid)
{ int i;
  for (i=0;i<=lastpid;i++) 
    if (pid==pids[i]) return fds[i];
  fprintf (stderr,"getfd failed (pid=%d, lastpid=%d). Returning -1.\n", pid, lastpid);
  return -1;
}

int newfd (pid_t pid)
{ char filename[30];
  
  lastpid++;
  if (lastpid==MAX_PID_COUNT) {
    fprintf (stderr,"coreaccess.c: PID overflow in newfd\n");
    lastpid--;
    return -1;
  }
  
  pids[lastpid] = pid;
  
  sprintf (filename, "/proc/%d", (int)pid);
  fds[lastpid] = open (filename,O_RDWR | O_SYNC);
  if (fds[lastpid] == -1) {
    fprintf (stderr,
	     "coreaccess.c: failed to open /proc/%d, errno=%d (%s)\n",
	     pid,
	     errno,
	     strerror(errno)
	     );
    lastpid--;
    return errno;
  }

  return 0;
}

void closefd (pid_t pid)
{ int i;
  for (i=0;i<=lastpid;i++) {
    if (pid==pids[i]) {
      close (fds[i]);
      pids[i] = pids[lastpid];
      fds[i] = fds[lastpid];
      lastpid--;
      return;
    }
  }
}

int coreaccess_init (pid_t pid)
{ 
  /*fprintf(stderr, "coreaccess_init(0x%x)\n", pid); fflush(stderr);*/
  return newfd (pid);
}

void coreaccess_close (pid_t pid)
{
  closefd (pid);
}

int WriteImage (int pid, int address, int value)
{ int res,fd;
  errno = 0;
  
  fd=getfd (pid);
  
  if (fd==-1) return -1;
  
  res = pwrite (fd,&value,sizeof(int),address);
  if (res==-1) {
    fprintf (stderr,"WriteImage failed (1). Returning %d.\n",errno);
    return errno;
  }
  else 
    if (res<sizeof(int)) {
      fprintf (stderr,"WriteImage failed (2). Returning -1.\n");
      return -1;
    };
  
  return 0;
}

int ReadImage (pid_t pid, int address, int* value)
{ int res,fd;
  errno = 0;

  fd=getfd (pid); if (pid==-1) return -1;
  
  lseek (fd,address,SEEK_SET);
  res = read (fd,value,sizeof(int));
  
  if (res==-1) 
    return errno;
  else 
    if (res<sizeof(int)) 
      return -1;
  
  return 0;
}

int SetBreak (pid_t pid, int address, int* oldInstruction) 
{ int res;
  
  if (res=ReadImage (pid, address, oldInstruction)) {
    fprintf (stderr,"ReadImage failed. SetBreak returning %d.\n",res);
    return res;
  };
  return WriteImage (pid,address,BREAK_INST);
}

int UnsetBreak (pid_t pid, int address, int oldInstruction)
{
  return WriteImage (pid, address, oldInstruction);
}

#endif /* not sun4s nor sgi */

#if defined(sun4) || defined(linux)

/* Implementation of coreaccess.h using ptrace. */
#include <sys/ptrace.h>

#ifdef sun4
#include <sys/wait.h>
#define PT_ATTACH PTRACE_ATTACH
#define PT_DETACH PTRACE_DETACH
#define PT_WIUSER PTRACE_POKETEXT
#define PT_RIUSER PTRACE_PEEKTEXT   
#endif

#ifdef linux
#define PT_ATTACH PTRACE_ATTACH
#define PT_DETACH PTRACE_DETACH
#define PT_WIUSER PTRACE_POKETEXT
#define PT_RIUSER PTRACE_PEEKTEXT   
#endif

#ifdef linux
#define PTRACE(req, pid, addr, data, addr2) ptrace(req, pid, addr, data)
#else
#define PTRACE(req, pid, addr, data, addr2) ptrace(req, pid, addr, data, addr2)
#endif

int Attach (pid_t pid)
{ errno = 0; 
  PTRACE (PT_ATTACH, pid, 0, 0, 0);
  if (errno) return errno;
  waitpid (pid,0,0); 
  return errno;
}

int Detach (pid_t pid)
{ errno = 0; 
  PTRACE (PT_DETACH, pid, 1, 0, 0); 
  return errno;
}

int ReadImage (pid_t pid, int address, int *value)
{ errno = 0; 
  *value = PTRACE (PT_RIUSER, pid, address, 0, 0); 
  return errno;
}

int WriteImage (pid_t pid, int address, int value)
{ errno = 0;
  PTRACE (PT_WIUSER, pid, address, value, 0);  
  return errno;
}

int SetBreak (pid_t pid, int address, int* oldInstruction) 
{ int res;
  
  if (Attach (pid)) {
    return errno;
  }
  if (res = ReadImage (pid, address, oldInstruction)) {
    Detach (pid); return res;
  }

#if 0
  fprintf(stderr, 
	  "SetBreak: WriteImage(pid=0x%x, address=0x%x, value=0x%x\n",
	  pid, address, BREAK_INST);
#endif

  WriteImage (pid,address,BREAK_INST);
  
  Detach (pid);
  return errno;
}

int UnsetBreak (pid_t pid, int address, int oldInstruction)
{
  if (Attach (pid)) return errno;

#if 0
  fprintf(stderr, 
	  "UnsetBreak: WriteImage(pid=0x%x, address=0x%x, value=0x%x\n",
	  pid, address, oldInstruction);
#endif

  WriteImage (pid, address, oldInstruction);
  Detach (pid);
  return errno;
}

#endif /* not sun4 or linux */

int SendSIGINT (pid_t pid)
{
  return kill (pid, SIGINT);
}

#endif /* not sun4 or sun4s or linux or sgi */

#if defined(nti)

#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

int coreaccess_init(HANDLE pid) { 
  /* no initialization requiered */
  return 0;
}

void coreaccess_close(HANDLE pid) {
  /* no cleanup requiered */
  return;
}

extern void process_comm_exception(char *message);

int SendSIGINT(int pid) {
  UINT exit_code;
  HANDLE hProcess=(HANDLE)pid;

  exit_code= 0; /* which is the prober exit-code ? */

  if (TerminateProcess(hProcess, exit_code)) {
    /* call succeeded */
    return 0;
  } else {
    /* call failed */
    LPVOID lpMsgBuf;
    FormatMessage
      (FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM,
       NULL,
       GetLastError(),
       MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), // Default language
       (LPTSTR) &lpMsgBuf,
       0,
       NULL);
    process_comm_exception((char *)lpMsgBuf);
  }
}

int ReadImage(int pid, int address, int *value) {
  errno = 0; 
  printf("ReadImage not implemented\n");
  exit(1);
  return errno;
}

int WriteImage(int pid, int address, int value) { 
  errno = 0;
  printf("WriteImage not implemented\n");
  exit(1);
  return errno;
}

int SetBreak(int pid, int address, int* oldInstruction) { 
  int res;
  errno = 0;
  printf("SetBreak not implemented\n");
  exit(1);
  return errno;
}

int UnsetBreak(int pid, int address, int oldInstruction) {
  errno = 0;
  printf("UnsetBreak not implemented\n");
  exit(1);
  return errno;
}

#endif /* not nti */













