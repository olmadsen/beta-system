
#ifndef COREACCESS_SUN4S_H
#define COREACCESS_SUN4S_H

#include <sys/types.h>

/* int InitializeCoreAccess (pid_t pid)
 * ====================================
 *
 * Initializes interface to process image of process pid.
 *
 * Return values
 *      OK: a file descriptor for the process image
 *      Otherwise: -1 and errno is set
 */

int InitializeCoreAccess (pid_t pid);



/* void CloseCoreAccess (int processFD)
 * ==========================\=========
 *
 * Should be called when the processFD is not going to be used again. */

void CloseCoreAccess (int processFD);



/* int WriteImage (int processFD, int address, int bytecount, char *buffer)
 * ========================================================================
 *
 * Writes the contents of buffer at address "address" in image of process
 * identified by "processFD". If bytecount is 4 (a long), the previous value 
 * at that address is returned in buffer.
 * 
 * Returns -1 in case of error., 0 otherwise. */

int WriteImage (int processFD, int address, int bytecount, char *buffer);




/* int ReadImage (int processFD, int address, int bytecount, char* buffer)
 * =======================================================================
 *
 * Reads bytecount bytes from address in the image of process identified by 
 * processFD. Result is returned in buffer.
 *
 * Returns -1 in case of error, 0 otherwise. */

int ReadImage (int processFD, int address, int bytecount, char* buffer);


/* int BreakInstruction () 
 * =======================
 *
 * Returns the opcode used to set breakpoints. */

int BreakInstruction ();

#endif
