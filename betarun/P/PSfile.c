#include "beta.h"

#ifdef PERSIST
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>

/* readLong: reads a long from fd. */
void readLong(int fd, u_long *n) 
{
  int nb;
  
  if ((nb = read(fd, n, sizeof(u_long))) < 0) {
    perror("readLong");
    DEBUG_CODE(Illegal());
    BetaExit(1);
  }
  
  if (nb != sizeof(u_long)) {
    fprintf(output, "readLong: Could not read long\n");
    DEBUG_CODE(Illegal());
    BetaExit(1);
  }
}

/* readSome: reads size bytes into buffer from fd. */
void readSome(int fd, void *buffer, u_long size) 
{
  int nb;
  
  if ((nb = read(fd, buffer, size)) < 0) {
    perror("readSome");
    DEBUG_CODE(Illegal());
    BetaExit(1);
  }
  
  if (nb != size) {
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
void writeLong(int fd, u_long *n)
{
  int nb;
  
  if ((nb = write(fd, n, sizeof(u_long))) < 0) {
    perror("writeLong");
    DEBUG_CODE(Illegal());
    BetaExit(1);
  }
  
  if (nb != sizeof(u_long)) {
    fprintf(output, "putName: Could not write long\n");
    DEBUG_CODE(Illegal());
    BetaExit(1);
  }
}

/* windTo: Goes to position pos in fd. */
void windTo(int fd, u_long pos) 
{
  if (lseek(fd, pos, SEEK_SET) < 0) {
    perror("windTo");
    DEBUG_CODE(Illegal());
    BetaExit(1);
  }
}

/* writeSome: writes size bytes from buffer onto fd. */
void writeSome(int fd, void *buffer, u_long size)
{
  int nb;
  
  if ((nb = write(fd, buffer, size)) < 0) {
    perror("writeSome");
    DEBUG_CODE(Illegal());
    BetaExit(1);
  }
}

/* isDir: Returns true if name is a directory. */
long isDir(char *name) 
{
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
  return 0;
}

u_long preferredBufferSize(char *path)
{
  struct stat st;
  
  if (stat (path, &st) == 0) {
    return st.st_blksize;
  } else {
    perror("preferredBufferSize");
    DEBUG_CODE(Illegal());
    BetaExit(1);
  }
  return 0;
}
#endif /* PERSIST */
