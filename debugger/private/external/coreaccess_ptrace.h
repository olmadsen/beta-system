
#ifndef COREACCESS_PTRACE_H
#define COREACCESS_PTRACE_H

#include <sys/types.h>

/* int SetBreak (pid_t pid, int address, int *oldInstruction)
 * =========================================================
 *
 * Set breakpoint at address. The previous instruction at that address
 * is returned to be used by UnsetBreak.
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

#endif
