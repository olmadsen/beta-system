#ifndef _PSFILE_H_
#define _PSFILE_H_
#include "beta.h"

#ifndef MAC
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#endif

#ifndef nti
#ifndef MAC
#include <unistd.h>
#endif /* MAC */
#endif /* nti */
#include <errno.h>

void readLong(int fd, unsigned long *n);
void readSome(int fd, void *buffer, unsigned long size); 
void Rewind(int fd);
void writeLong(int fd, unsigned long *n);
void windTo(int fd, unsigned long pos); 
void writeSome(int fd, void *buffer, unsigned long size);
long fileExists(char *name);
long isDir(char *name); 
unsigned long preferredBufferSize(int fd);
int ScanDir(char *dir, int *longestP, int *numP, void (*CallbackFnc)(char*));

#endif /* _PSFILE_H_ */
