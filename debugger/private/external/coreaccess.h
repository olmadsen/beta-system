#ifndef COREACCESS_H
#define COREACCESS_H

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

#endif
