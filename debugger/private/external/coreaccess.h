#ifndef COREACCESS_H
#define COREACCESS_H

#ifdef sparc
#define BREAK_INST 0x00000000
#endif

#ifdef hppa
#define BREAK_INST 0x00000000
#endif

#ifdef sgi
/* BREAK 80 */
#define BREAK_INST 0x00000a0d /* big-endian */
#endif

#ifdef hpux9mc
/* Illegal */
#define BREAK_INST ((0x4afc0000) | ((*oldInstruction) & 0x0000ffff))
#endif

#if defined(linux) || defined(nti)
/* int 3 - hex 0xcc */ 
#define BREAK_INST ((0x000000cc) | ((*oldInstruction) & 0xffffff00))
#endif


#ifndef BREAK_INST
#error BREAK_INST must be defined
#endif

#if defined(sun4s) || defined(sgi) || defined(sun4) || defined(linux)

#include <sys/types.h>

/* int SetBreak (pid_t pid, int address, int *oldInstruction)
 * =========================================================
 *
 * Set breakpoint at address. The previous instruction at that address
 * is returned in oldInstruction to be used by UnsetBreak.
 * Return 0 if success. errno otherwise. */

int SetBreak (pid_t pid, int address, int *oldInstruction);


/* int UnsetBreak (pid_t pid, int address, int oldInstruction)
 * ===========================================================
 *
 * Remove breakpoint previously set by SetBreak. 
 * Return 0 if success. errno otherwise. */

int UnsetBreak (pid_t pid, int address, int oldInstruction);


/* int SendSIGINT (pid_t pid);
 * ============================
 *
 * Send SIGINT to process pid.
 * Returns the return value from the "kill" system call. */

int SendSIGINT (pid_t pid);

#if defined(sun4s) || defined(sgi)

/* int coreaccess_init (pid_t pid);
 * ================================
 *
 * On sun4s and sgi, the /proc filesystem is used. 
 * coreaccess_init must be called  * to open a /proc file descriptor 
 *used by SetBreak and UnsetBreak.
 *
 * Returns 0 if ok, errno otherwise. */

/* void  coreaccess_close(pid_t pid);
 * =========================
 *
 * This call closes the /proc filedescriptor for pid opened by 
 * coreaccess_init. */

void coreaccess_close(pid_t pid);
#endif /* sun4s or sgi */

#endif /* not sun4 or sun4s or linux or sgi */

#if defined(nti)
#include <windows.h>

int SetBreak (HANDLE pid, int address, int* oldInstruction); 
  
int UnsetBreak (HANDLE pid, int address, int oldInstruction);

int SendSIGINT (int pid);

#endif /* not nti */
#endif /* COREACCESS_H allready included */
