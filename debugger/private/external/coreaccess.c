#include <errno.h>
#include <stdio.h>
#include <signal.h>

#include "coreaccess.h"

#ifdef sun4s

/* Implementation using the /proc file system. */
#include <fcntl.h>

#define MAX_PID_COUNT 10

static pid_t pids[MAX_PID_COUNT];
static int fds[MAX_PID_COUNT];
static int lastpid = -1;

int getfd (pid_t pid)
{ int i;
  for (i=0;i<=lastpid;i++) 
    if (pid==pids[i]) return fds[i];
  fprintf (stderr,"getfd failed. Returning -1.\n");
  return -1;
}

int newfd (pid_t pid)
{ char filename[30];
  int i;
  
  lastpid++;
  if (lastpid==MAX_PID_COUNT) {
    fprintf (stderr,"coreaccess.c: PID overflow in newfd\n");
    lastpid--;
    return -1;
  }
  
  pids[lastpid] = pid;
  
  sprintf (filename, "/proc/%d", pid);
  fds[lastpid] = open (filename,O_RDWR | O_SYNC);
  if (fds[lastpid] == -1) {
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
  
  if (res==ReadImage (pid, address, oldInstruction)) {
    fprintf (stderr,"ReadImage failed. SetBreak returning %d.\n",res);
    return res;
  };
  
  return WriteImage (pid,address,0);
}

int UnsetBreak (pid_t pid, int address, int oldInstruction)
{
  return WriteImage (pid, address, oldInstruction);
}


#else /* Not Solaris */

/* Implementation of coreaccess.h using ptrace. */
#include <sys/ptrace.h>

#ifdef sun4
#include <sys/wait.h>
#define PT_ATTACH PTRACE_ATTACH
#define PT_DETACH PTRACE_DETACH
#define PT_WIUSER PTRACE_POKETEXT
#define PT_RIUSER PTRACE_PEEKTEXT   
#endif

int Attach (pid_t pid)
{ errno = 0; 
  ptrace (PT_ATTACH, pid, 0, 0, 0);
  if (errno) return errno;
  waitpid (pid,0,0); 
  return errno;
}

int Detach (pid_t pid)
{ errno = 0; 
  ptrace (PT_DETACH, pid, 1, 0, 0); 
  return errno;
}

int ReadImage (pid_t pid, int address, int *value)
{ errno = 0; 
  *value = ptrace (PT_RIUSER, pid, address, 0, 0); 
  return errno;
}

int WriteImage (pid_t pid, int address, int value)
{ errno = 0;
  ptrace (PT_WIUSER, pid, address, value, 0);  
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

#if defined(hpux) && !defined(hppa)
  /* MC 680x0 instruction generating illegal instruction trap:
   *   Asm syntax: ILLEGAL
   *   Instruction format: 0100 1010 1111 1100 = 0x4afc */
  WriteImage (pid, address, ((0x4afc0000) | ((*oldInstruction) & 0x0000ffff)));
#endif
  
#ifdef hppa
  WHICH ILLEGAL INSTRUCTION FOR HP-PA ?
#endif

#ifdef sparc
  WriteImage (pid,address,0);
#endif
  
  Detach (pid);
  return errno;
}

int UnsetBreak (pid_t pid, int address, int oldInstruction)
{
  if (Attach (pid)) return errno;
  WriteImage (pid, address, oldInstruction);
  Detach (pid);
  return errno;
}

#endif /* not sun4s */

int SendSIGINT (pid_t pid)
{
  return kill (pid, SIGINT);
}
