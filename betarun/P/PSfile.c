#include "beta.h"

void psf_dummy() {
#ifdef sparc
  USE();
#endif /* sparc */
}

#ifdef PERSIST
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#ifdef UNIX
#include <unistd.h>
#endif
#ifdef nti
#include <io.h>
#endif
#include <errno.h>

/* readLong: reads a long from fd. */
void readLong(int fd, unsigned long *n) 
{
  int nb;
  
  if ((nb = read(fd, n, sizeof(unsigned long))) < 0) {
    perror("readLong");
    DEBUG_CODE(Illegal());
    BetaExit(1);
  }
  
  if (nb != sizeof(unsigned long)) {
    fprintf(output, "readLong: Could not read long\n");
    DEBUG_CODE(Illegal());
    BetaExit(1);
  }
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
      DEBUG_CODE(Illegal());
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
    DEBUG_CODE(Illegal());
    BetaExit(1);
  }
}

/* Rewind: winds the cursor to the beginning of the file. */
void Rewind(int fd)
{
  if (lseek(fd, 0, SEEK_SET) < 0) {
    perror("Rewind");
    DEBUG_CODE(Illegal());
    BetaExit(1);
  }
}

/* writeLong: writes a long to fd. */
void writeLong(int fd, unsigned long *n)
{
  int nb;
  
  if ((nb = write(fd, n, sizeof(unsigned long))) < 0) {
    perror("writeLong");
    DEBUG_CODE(Illegal());
    BetaExit(1);
  }
  
  if (nb != sizeof(unsigned long)) {
    fprintf(output, "putName: Could not write long\n");
    DEBUG_CODE(Illegal());
    BetaExit(1);
  }
}

/* windTo: Goes to position pos in fd. */
void windTo(int fd, unsigned long pos) 
{
  if (lseek(fd, pos, SEEK_SET) < 0) {
    perror("windTo");
    DEBUG_CODE(Illegal());
    BetaExit(1);
  }
}

/* writeSome: writes size bytes from buffer onto fd. */
void writeSome(int fd, void *buffer, unsigned long size)
{
  int nb;
  
  if ((nb = write(fd, buffer, size)) < 0) {
    perror("writeSome");
    DEBUG_CODE(Illegal());
    BetaExit(1);
  }
}

long fileExists(char *name)
{
  struct stat st;
  if (stat(name, &st) < 0) {
    return 0;
  } else {
    return 1;
  }
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
#ifdef nti
  return 32*1024;
#else /* nti */
  struct stat st;
  
  if (fstat (fd, &st) == 0) {
    return st.st_blksize;
  } else {
    perror("preferredBufferSize");
    DEBUG_CODE(Illegal());
    BetaExit(1);
  }
  return 0;
#endif /* nti */
}

#endif /* PERSIST */
