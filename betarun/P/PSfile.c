#include "beta.h"

#ifdef PERSIST

#ifndef MAC
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#endif

#ifdef MAC
#include <fcntl.h>
#include <IOCtl.h>
#include <Files.h>
#endif

#ifdef UNIX
#include <unistd.h>
#endif
#ifdef nti
#include <io.h>
#include <windows.h> /* to get CreateDirectory */
#endif /* nti */
#include <errno.h>

#ifdef PSENDIAN
/* Get definition of ntohl */
#ifdef linux
# include <sys/types.h>
# include <netinet/in.h>
#else
# include "winsock.h"
#endif 
#endif 

/* createDirectory,
 */
int createDirectory(char *path, u_long attr)
{
#ifdef nti
  struct _SECURITY_ATTRIBUTES lpSA;
  
  lpSA.nLength = sizeof(struct _SECURITY_ATTRIBUTES);
  lpSA.lpSecurityDescriptor = NULL;
  lpSA.bInheritHandle = TRUE;
  return CreateDirectory((LPCSTR)path, &lpSA);
#else
#ifndef MAC
  return mkdir(path, attr);
#else
  return 0;
#endif
#endif
}
/* readLong: reads a long from fd. */
void readLong(int fd, unsigned long *n) 
{
  int nb;
  
  if ((nb = read(fd, n, sizeof(unsigned long))) < 0) {
    perror("readLong");
    DEBUG_CODE(ILLEGAL);
    BetaExit(1);
  }
  
  if (nb != sizeof(unsigned long)) {
    fprintf(output, "readLong: Could not read long\n");
    DEBUG_CODE(ILLEGAL);
    BetaExit(1);
  }

#ifdef PSENDIAN
  *n = ntohl(*n);
#endif
}

/* readSome: reads size bytes into buffer from fd. */
void readSome(int fd, char *buffer, unsigned long size) 
{
  int nb, toread = size;
  char *ptr = (char*)buffer;
  /* Claim(!lseek(fd, 0, SEEK_CUR), "Grr"); */

  while (toread>0) {
    if ((nb = read(fd, ptr, toread)) < 0) {
      perror("readSome");
      DEBUG_CODE(ILLEGAL);
      BetaExit(1);
    } else if (nb == 0) {
      return;
    } else {
      ptr += nb;
      toread -= nb;
    }
  }
  
  if ((unsigned long)(ptr - (char*)buffer) != size) {
    fprintf(output, "readSome: Could not read\n");
    DEBUG_CODE(ILLEGAL);
    BetaExit(1);
  }
}

/* Rewind: winds the cursor to the beginning of the file. */
void Rewind(int fd)
{
  if (lseek(fd, 0, SEEK_SET) < 0) {
    perror("Rewind");
    DEBUG_CODE(ILLEGAL);
    BetaExit(1);
  }
}

/* writeLong: writes a long to fd. */
void writeLong(int fd, unsigned long *n)
{
   int nb;
   u_long nendian;
   
#ifdef PSENDIAN
   nendian = ntohl(*n);
#else
   nendian = *n;
#endif   
   if ((nb = write(fd, &nendian, sizeof(unsigned long))) < 0) {
      perror("writeLong");
      DEBUG_CODE(ILLEGAL);
      BetaExit(1);
   }
   /*fprintf(output, "writeLong: nendian: 0x%X\n", (int)nendian);*/
  
   if (nb != sizeof(unsigned long)) {
      fprintf(output, "putName: Could not write long\n");
      DEBUG_CODE(ILLEGAL);
      BetaExit(1);
   }
}

/* windTo: Goes to position pos in fd. */
void windTo(int fd, unsigned long pos) 
{
#ifdef MAC	
   if(lseek(fd, 0, SEEK_END) < pos) {
      ioctl(fd, FIOSETEOF, (long *) pos);
   }
#endif
   
   if (lseek(fd, pos, SEEK_SET) < 0) {
      perror("windTo");
      DEBUG_CODE(ILLEGAL);
      BetaExit(1);
   }
}

/* writeSome: writes size bytes from buffer onto fd. */
void writeSome(int fd, void *buffer, unsigned long size)
{
  int nb;
  
  if ((nb = write(fd, buffer, size)) < 0) {
    perror("writeSome");
    DEBUG_CODE(ILLEGAL);
    BetaExit(1);
  }
}

long fileExists(char *name)
{
#ifndef MAC
   struct stat st;
   if (stat(name, &st) < 0) {
      return 0;
   } else {
      return 1;
   }
#else
   OSErr result;
   FSSpec fs;
   Str255 path;
   int i = 0;
      
   while(name[i] != '\0') {
      path[i+1] = (unsigned char) name[i];
      i++;
   }
   path[0] = (unsigned char) i; 
   
   result = FSMakeFSSpec(0, 0, path, &fs);
   if(result < 0) {
      return 0;
   } 
   else {
      return 1;	
   }
#endif
}

/* isDir: Returns true if name is a directory. */
long isDir(char *name) 
{
#ifdef UNIX
  int fd;
  
  if ((fd = open(name,O_RDWR))<0) {
    switch(errno) {
    case EISDIR:
      return 1;
      break;
    default:
      return 0;
      break;
    }
  } else {
    close(fd);
    return 0;
  }
#endif

#ifdef nti
  struct _stat buf;
  int result = _stat(name, &buf);
  if (result != 0)
    return 0;
  if (buf.st_mode & _S_IFDIR) 
    return 1;
#endif
  return 0;
}

unsigned long preferredBufferSize(int fd)
{
  unsigned long res;
#if 0   /* Prevents cross platform stores */
#ifdef MAC
  res = 8192;
#else
#ifdef nti
  res = 8192;
#else /* nti */
  
  struct stat st;
  if (fstat (fd, &st) == 0) {
     res = st.st_blksize;
  } else {
     res = 8192;
  }
  if (res<8192) {
     res = 8192;
  }
#endif /* nti */
#endif /* MAC */
#else
  res = 8192;
#endif /* 0 */
  return res;
}

#endif /* PERSIST */
