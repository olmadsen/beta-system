#include <stdlib.h>
#include <sys/types.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <errno.h>
#include <stdio.h>
#include <time.h>
#include <io.h>
#ifdef nti_bor
#include <utime.h>
#else
#include <sys/utime.h>
#define S_IXUSR _S_IEXEC
#define S_IWUSR _S_IWRITE
#define S_IRUSR _S_IREAD
#define S_IFBLK (-1) /* ??? */
#define ENOTSAM EXDEV
#endif

#include <malloc.h>
#include <windows.h>

#define BSIZE BUFSIZ


int getEntryAccessTime(char *path)
{ 
  struct stat statBuffer; 
  int entryType;
  if (stat(path,&statBuffer)<0) return -1;
  return (int) statBuffer.st_atime;
} 

int getEntryCreationTime(char *path)
{ 
  struct stat statBuffer; 
  int entryType;
  if (stat(path,&statBuffer)<0) return -1;
  return (int) statBuffer.st_ctime;
} 
