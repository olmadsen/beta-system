
#ifndef COREACCESS_HPUX8_H
#define COREACCESS_HPUX8_H

#include <sys/types.h>

/* int Attach (pid_t pid)
 * ======================
 *
 * Attach to process pid, i.e. stop it and prepare for reading or writing
 * its address space. 
 * Return 0 if success. errno otherwise. */

int Attach (pid_t pid);

/* int Detach (pid_t pid)
 * ======================
 *
 * Detach process pid, i.e. allow it to continue. 
 * Return 0 if success. errno otherwise. */

int Detach (pid_t pid);

/* int ReadImage (pid_t pid, int address, int *value)
 * ==================================================
 *
 * Read memory long at address and return value in *value.
 * Return 0 if success. errno otherwise. */

int ReadImage (pid_t pid, int address, int *value);

/* int WriteImage (pid_t pid, int address, int value)
 * ==================================================
 * 
 * Write value at address.
 * Return 0 if success. errno otherwise. */

int WriteImage (pid_t pid, int address, int value);

/* int SetBreak (pid_t pid, int address, int oldInstruction)
 * =========================================================
 *
 * Set breakpoint at address. The breakpoint instruction is built as
 * a combination of the dedicated ILLEGAL instruction and the 
 * oldinstruction.
 * Return 0 if success. errno otherwise. */

int SetBreak (pid_t pid, int address, int oldInstruction);

#endif
