#if defined(sun4s) || defined(hpux9pa) || defined(linux) || defined(sgi) || defined(x86sol)
#define UNIX
#endif

#include <stdio.h>
#ifdef UNIX
#include <errno.h>
# include <sys/time.h>
# include <fcntl.h>
#endif

void PutToScreen(char ch)
{
  putchar(ch);
  fflush(stdout);
}
void PutTextToScreen(char *str)
{
  fputs(str,stdout);
  fflush(stdout);
}

static int my_getchar(void)
{
  int ch;
  ch=getchar();
#ifdef UNIX
  if (ch == EOF && errno==EAGAIN) {
    fd_set fdset;
    int fd = fileno(stdin);
    FD_ZERO(&fdset);
    FD_SET(fd, &fdset);
    select(1, &fdset,NULL,NULL,NULL);
    ch=getchar();
  }
#endif
  return ch;
}


char GetFromKeyboard(void)
{
  return(my_getchar());
}
int KeyboardEOS(void)
{
  int ch;
  ch=my_getchar();
  ungetc(ch, stdin);
  return(ch==EOF); 
}
int KeyboardPeek(void)
{
  int ch;
  ch=my_getchar();
  
  if (ch != EOF) {
    ungetc(ch, stdin);
  }
  
  return (ch);
}

void PutToStdErr(char ch)
{
  putc(ch, stderr);
  fflush(stderr); 
}
void PutTextToStdErr(char *str)
{
  fputs(str,stderr);
  fflush(stderr); 
}

double infReal(void)
{
  double x;
#if defined(nti) || defined(linux) || defined(x86sol)
  ((unsigned long *)(&x))[0] = 0x00000000;
  ((unsigned long *)(&x))[1] = 0x7FF00000;
#else
  ((unsigned long *)(&x))[0] = 0x7FF00000;
  ((unsigned long *)(&x))[1] = 0x00000000;
#endif
  return x;
}

#ifdef UNIX

int getStandardInNonBlock()
{
  int fd = fileno(stdin);

  if (0 > fcntl(fd, F_SETFL, O_NONBLOCK)) {
    return -1;
  }

  return fd;
}

/*
 * All fds that BETA reads from should be non-blocking.  Returns fd or -1 for
 * error.
 */

int setFdNonBlock(int fd)
{
  if (0>fcntl(fd,F_SETFL, O_NONBLOCK)) {
    return -1;
  }
  return fd;
}

/*
 * Nonblocking needs to be reset on fds that are passed to new process.
 * Returns fd or -1 for error.
 */

int clearFdNonBlock(int fd)
{
  char buf[1000];
  int result;
  result = fcntl(fd, F_SETFL, 0);
  if (0 > result) {
    perror("clearFdNonBlock");
    return -1;
  }
  return fd;
}

/*
 * Set the close-on-exec flag on a file descriptor.  This flag is cleared
 * when dup'ing or dup2'ing.  Useful to make sure the write end of pipes
 * is not kept open by child processes, thus messing up EOS/EOF detection.
 *
 * Returns 0 for success or -1 for failure (check errno)
 */

int setFdCloExec(int fd)
{
  return fcntl(fd, F_SETFD, FD_CLOEXEC);
}

/*
 * Not normally necessary as dup does this for us.
 *
 * Returns 0 for success or -1 for failure (check errno)
 */

int clearFdCloExec(int fd)
{
  return fcntl(fd, F_SETFD, 0);
}

#endif /* UNIX */
