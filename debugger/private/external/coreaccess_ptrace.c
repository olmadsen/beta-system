#include <errno.h>
#include <sys/ptrace.h>
#include <signal.h>

#if defined(sun4) || defined(sun4s)
#include <sys/wait.h>
#define PT_ATTACH PTRACE_ATTACH
#define PT_DETACH PTRACE_DETACH
#define PT_WIUSER PTRACE_POKETEXT
#define PT_RIUSER PTRACE_PEEKTEXT   
#endif

#include "coreaccess_ptrace.h"

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
  
  if (Attach (pid)) return errno;
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
    
#ifdef sun4
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

int SendSIGINT (pid_t pid)
{
  return kill (pid, SIGINT);
}
