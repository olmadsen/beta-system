#include "coreaccess.h"

#if defined(sun4s) || defined(sgi) || defined(x86sol) || defined(linux)

#include <errno.h>
#include <stdio.h>
#include <signal.h>
#include <unistd.h>

#define TRACE_COREACCESS 0

#if defined(sun4s) || defined(sgi) || defined(x86sol)

/* Implementation using the /proc file system. */
#include <fcntl.h>

#ifdef old_sgi_hack
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
#if TRACE_COREACCESS
  fprintf (stderr,"getfd failed (pid=%d, lastpid=%d). Returning -1.\n", pid, lastpid);
#endif
  return -1;
}

int newfd (pid_t pid)
{ char filename[30];
  
  lastpid++;
  if (lastpid==MAX_PID_COUNT) {
#if TRACE_COREACCESS
    fprintf (stderr,"coreaccess.c: PID overflow in newfd\n");
#endif
    lastpid--;
    return -1;
  }
  
  pids[lastpid] = pid;
  
  sprintf (filename, "/proc/%d", (int)pid);
  fds[lastpid] = open (filename,O_RDWR | O_SYNC);
  if (fds[lastpid] == -1) {
#if TRACE_COREACCESS
    fprintf (stderr,
	     "coreaccess.c: failed to open /proc/%d, errno=%d (%s)\n",
	     pid,
	     errno,
	     strerror(errno)
	     );
#endif
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
  return newfd (pid);
}

void coreaccess_close (pid_t pid)
{
  closefd (pid);
}

int WriteImage (int pid, int address, int value)
{ int res,fd;
  errno = 0;
  
#if TRACE_COREACCESS
  fprintf (stderr,"WriteImage(pid=0x%x, address=0x%x)\n", (int)pid, (int)address);
#endif
  fd=getfd (pid);
  
  if (fd==-1) return -1;
  
  res = pwrite (fd,&value,sizeof(int),address);
  if (res==-1) {
#if TRACE_COREACCESS
    fprintf (stderr,"WriteImage(pid=0x%x, fd=%d, address=0x%x) failed (1). Returning errno=%d.\n", (int)pid, (int)fd, (int)address, errno);
#endif
    return errno;
  }
  else 
    if (res<sizeof(int)) {
#if TRACE_COREACCESS
      fprintf (stderr,"WriteImage(pid=0x%x, fd=%d, address=0x%x) failed (2). Returning -1.\n", (int)pid, (int)fd, (int)address);
#endif
      return -1;
    };
  
  return 0;
}

int ReadImage (pid_t pid, int address, int* value)
{ int res,fd;
  errno = 0;

#if TRACE_COREACCESS
  fprintf (stderr,"ReadImage(pid=0x%x, address=0x%x)\n", (int)pid, (int)address);
#endif

  fd=getfd (pid); if (pid==-1) return -1;
  
  lseek (fd,address,SEEK_SET);
  res = read (fd,value,sizeof(int));
  
  if (res==-1) {
#if TRACE_COREACCESS
    fprintf (stderr,"ReadImage(pid=0x%x, fd=%d, address=0x%x) failed (1). Returning errno=%d.\n", (int)pid, (int)fd, (int)address, errno);
#endif
    return errno;
  } else {
    if (res<sizeof(int)) {
#if TRACE_COREACCESS
      fprintf (stderr,"ReadImage(pid=0x%x, fd=%d, address=0x%x) failed (2). Returning -1.\n", (int)pid, (int)fd, (int)address);
#endif
      return -1;
    }
  }
  
  return 0;
}

int SetBreak (pid_t pid, int address, int* oldInstruction) 
{ int res;
  
  if (res=ReadImage (pid, address, oldInstruction)) {
#if TRACE_COREACCESS
    fprintf (stderr,"SetBreak: ReadImage(pid=0x%x, address=0x%x) failed. SetBreak returning %d.\n", (int)pid, (int)address, res);
#endif
    return res;
  };
  return WriteImage (pid,address,BREAK_INST);
}

int UnsetBreak (pid_t pid, int address, int oldInstruction)
{
  return WriteImage (pid, address, oldInstruction);
}

#endif /* not sun4s, x86sol nor sgi */

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

#if TRACE_COREACCESS
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

#if TRACE_COREACCESS
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

#endif /* not x86sol or sun4s or linux or sgi */

#if defined(ppcmac)

#include <Memory.h>
#include <TextUtils.h>
#include <stdio.h>
#include <OSUtils.h>
#include <ConditionalMacros.h>
#include <Traps.h>
#include <Gestalt.h>



const ProcInfoType uppMemoryDispatchProcInfo = 
          						kRegisterBased 
                              | RESULT_SIZE (SIZE_CODE (sizeof(OSErr)))
							  | REGISTER_RESULT_LOCATION (kRegisterD0)
                              | REGISTER_ROUTINE_PARAMETER(1, kRegisterD0, kOneByteCode)
                              | REGISTER_ROUTINE_PARAMETER(2, kRegisterD1, kTwoByteCode)
                              | REGISTER_ROUTINE_PARAMETER(3, kRegisterA0, SIZE_CODE(sizeof(void*)))
                              | REGISTER_ROUTINE_PARAMETER(4, kRegisterA1, SIZE_CODE(sizeof(long)));

pascal OSErr  VMWriteProtectMemory(void *address, unsigned long count) 
{

	UniversalProcPtr  MemoryDispatch;
	
	MemoryDispatch = GetOSTrapAddress(_MemoryDispatch);
	
#if TRACE_COREACCESS
	printf("MemoryDispatch = %X\n", (int) MemoryDispatch);
#endif	
	return CallOSTrapUniversalProc(MemoryDispatch, kRegisterBased 
                              | RESULT_SIZE (SIZE_CODE (sizeof(OSErr)))
							  | REGISTER_RESULT_LOCATION (kRegisterD0)
                              | REGISTER_ROUTINE_PARAMETER(1, kRegisterD0, kOneByteCode)
                              | REGISTER_ROUTINE_PARAMETER(2, kRegisterD1, kTwoByteCode)
                              | REGISTER_ROUTINE_PARAMETER(3, kRegisterA0, SIZE_CODE(sizeof(void*)))
                              | REGISTER_ROUTINE_PARAMETER(4, kRegisterA1, SIZE_CODE(sizeof(long))), 6, _MemoryDispatch, address, count);
}

pascal OSErr  VMUnWriteProtectMemory(void *address, unsigned long count) {

	UniversalProcPtr  MemoryDispatch;
	
	MemoryDispatch = GetOSTrapAddress(_MemoryDispatch);
	
#if TRACE_COREACCESS
	printf("MemoryDispatch = %X\n", (int) MemoryDispatch);
#endif	
	return CallOSTrapUniversalProc(MemoryDispatch, kRegisterBased 
                              | RESULT_SIZE (SIZE_CODE (sizeof(OSErr)))
							  | REGISTER_RESULT_LOCATION (kRegisterD0)
                              | REGISTER_ROUTINE_PARAMETER(1, kRegisterD0, kOneByteCode)
                              | REGISTER_ROUTINE_PARAMETER(2, kRegisterD1, kTwoByteCode)
                              | REGISTER_ROUTINE_PARAMETER(3, kRegisterA0, SIZE_CODE(sizeof(void*)))
                              | REGISTER_ROUTINE_PARAMETER(4, kRegisterA1, SIZE_CODE(sizeof(long))), 7, _MemoryDispatch, address, count);
}



int SendSIGINT(int pid) {
	return 0;
}

int UnsetBreak(int pid, int address, int oldInstruction) { 
	
	//long logicalPageSize;
	//long logicalPageSizeMask;
	OSErr err;
	
	
#if TRACE_COREACCESS
	printf("UnsetBreak %d\n", address);
#endif	
	
	//Gestalt(gestaltLogicalPageSize, &logicalPageSize);
	//logicalPageSizeMask = (~(logicalPageSize-1));
	
		
	//err = VMUnWriteProtectMemory((void *) (address & logicalPageSizeMask), logicalPageSize);
	//printf("VMUnWriteProtectMemory = %d\n", err);
	
	
	* (UInt32 *) address = oldInstruction;
	
	MakeDataExecutable((UInt32 *) address, 4L);
	
	//err = VMWriteProtectMemory((void *) (address & logicalPageSizeMask), logicalPageSize);
	//printf("VMUnWriteProtectMemory = %d\n", err);
	
	//err = DebuggerLockMemory((void *) (address & logicalPageSizeMask), logicalPageSize);
	
	return 0;
}

int SetBreak(int pid, int address, int* oldInstruction) { 
	
	long logicalPageSize;
	long logicalPageSizeMask;
	OSErr err;
	
#if TRACE_COREACCESS
	printf("setbreak %d\n", address);
#endif	
	
	Gestalt(gestaltLogicalPageSize, &logicalPageSize);
	logicalPageSizeMask = (~(logicalPageSize-1));
	
	err = DebuggerLockMemory((void *) (address & logicalPageSizeMask), logicalPageSize);
#if TRACE_COREACCESS
	printf("DebuggerLockMemory = %d\n", err);
#endif
	
	err = VMUnWriteProtectMemory((void *) (address & logicalPageSizeMask), logicalPageSize);
#if TRACE_COREACCESS
	printf("VMUnWriteProtectMemory = %d\n", err);
#endif	
	
	*oldInstruction = * (UInt32 *) address;
	* (UInt32 *) address = BREAK_INST;
	
	
	MakeDataExecutable((UInt32 *) address, 4L);
	
	//err = VMWriteProtectMemory((void *) (address & logicalPageSizeMask), logicalPageSize);
	//printf("VMUnWriteProtectMemory = %d\n", err);
	
	return 0;
}



#endif /* ppcmac */

#if defined(nti)

#include <errno.h>
#include <stdio.h>
#include <stdlib.h>

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

int ReadImage(HANDLE pid, int address, int *value) {
  HANDLE hProcess;	        /* handle of the process */
  LPCVOID lpBaseAddress;	/* address to start reading */
  LPVOID lpBuffer;	        /* address of buffer to place read data */
  DWORD nSize;     	        /* number of bytes to read */
  DWORD lpNumberOfBytesRead;    /* address of number of bytes read */
  errno = 0; 

  hProcess = pid;
  lpBaseAddress = (LPCVOID)address;
  lpBuffer = (LPVOID)value;
  nSize = 4;

  if (ReadProcessMemory(hProcess,
			lpBaseAddress,
			lpBuffer,
			nSize,
			&lpNumberOfBytesRead)) {
    errno = 0; 
  } else {
    char msg[512];
    sprintf(msg,"valhalla: ReadImage failed\n",(int)pid,address);
    process_comm_exception(msg);
  }
  return errno;
}

int WriteImage(HANDLE pid, int address, int value) {
  HANDLE hProcess;	        /* handle of the process */
  LPVOID lpBaseAddress;	        /* address to start writeing */
  LPVOID lpBuffer;	        /* address of buffer to place write data */
  DWORD nSize;     	        /* number of bytes to write */
  DWORD lpNumberOfBytesWritten; /* address of number of bytes write */

  hProcess = pid;
  lpBaseAddress = (LPVOID)address;
  lpBuffer = (LPVOID)&value;
  nSize = 4;

  if (WriteProcessMemory(hProcess,
			lpBaseAddress,
			lpBuffer,
			nSize,
			&lpNumberOfBytesWritten)) {
    errno = 0; 
  } else {
    char msg[512];
    sprintf(msg,"valhalla: Writeimage(%d,%X) failed\n",(int)pid,address);
    process_comm_exception(msg);
  }
  return errno;
}

int SetBreak(HANDLE pid, int address, int* oldInstruction) { 
  int res;
  
  if (res=ReadImage (pid, address, oldInstruction)) {
#if TRACE_COREACCESS
    fprintf (stderr,"ReadImage failed. SetBreak returning %d.\n",res);
#endif
    return res;
  };
  return WriteImage (pid,address,BREAK_INST);
}

int UnsetBreak(HANDLE pid, int address, int oldInstruction) {
  return WriteImage (pid, address, oldInstruction);
}

#endif /* not nti */


#ifdef hpux9pa
#include "stdio.h"
int SetBreak (pid_t pid, int address, int *oldInstruction) 
{
  fprintf(stderr,"SetBreak Called, not impl. on hpux9pa\n");
}

int UnsetBreak (pid_t pid, int address, int oldInstruction)
{
  fprintf(stderr,"UnsetBreak Called, not impl. on hpux9pa\n");
}

int SendSIGINT (pid_t pid)
{
 fprintf(stderr,"SendSIGINT Called, not impl. on hpux9pa\n");
}

#endif /* hpux9pa */











