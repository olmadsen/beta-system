
#ifndef VALHALLAFIFOS_H
#define VALHALLAFIFOS_H

#include <sys/types.h>
#include <stdio.h>

/* FIFO NAMES
 * ==========
 * 
 * fromName and toName generates and returns names of FIFOS used for
 * communication between valhalla and debugged process. */

char *fromName (pid_t pid);
char *toName (pid_t pid);

/* FIFO CREATION, OPENING and DELETION
 * ===================================
 *
 * createFIFOS creates two fifos with the names returned from fromName and
 * toName.
 *
 * openFIFOS opens these fifos for reading and writing. */

void createFIFOS (pid_t pid);
void openFIFOS (pid_t pid, FILE **fifoFrom, FILE **fifoTo);
void deleteFIFOS (pid_t pid);

#endif
