#ifndef _PSFILE_H_
#define _PSFILE_H_
#include "beta.h"

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>

void readLong(int fd, u_long *n);
void readSome(int fd, void *buffer, u_long size); 
void Rewind(int fd);
void writeLong(int fd, u_long *n);
void windTo(int fd, u_long pos); 
void writeSome(int fd, void *buffer, u_long size);
long isDir(char *name); 
u_long preferredBufferSize(char *path);
int ScanDir(char *dir, int *longestP, int *numP, void (*CallbackFnc)(char*));

#endif /* _PSFILE_H_ */
