/* Prototypes: */
double getTimeAsDouble(void);

#ifdef MAC

#include <Events.h>
#include <OSUtils.h>

int getImRead(int thefile)
{  EventRecord theEvent;

	if (EventAvail(keyDownMask,&theEvent))
		return 1;
	else
  		return 0;
}

double getTimeAsDouble(void)
{
  /* FIXME!  Implement this correctly! */
  return time(0);
}


void sleepDouble(double secs)
{	
	Boolean result;
	EventRecord event;
	/*
	 * This WaitNextEvent does not take any event out of the
	 * event queue since the mask parameter (first param) is 0.
	 */
	result = WaitNextEvent(0, &event, secs * 60, nil);
	return;
}


void ExtsleepUntil(double due)
{
	int now = time (0);
  	if (due > now) sleepDouble (due-now);
	return;
}

#else /* NOT MAC */

#ifdef nti
# include <sys/types.h>
# include <stdio.h>
# include <fcntl.h>
# include <errno.h>
# include <time.h>
# ifdef nti_gnu
#   include <windows.h>
#   include <Windows32/Sockets.h>
# else
#   include <winsock.h>
# endif
#else
# include <sys/types.h>
# include <sys/time.h>
# include <stdio.h>
# include <sys/ioctl.h> 
# include <fcntl.h>
# include <errno.h>
# include <unistd.h>
# include <time.h>
#endif




#ifdef sun4s
# include <stropts.h>
#endif

#ifdef nti
double getTimeAsDouble(void)
{
  return ((double)GetTickCount())/1000;
}

void sleepDouble(double period)
{
#ifndef FALSE
# define FALSE 0
#endif
  SleepEx((long)(1000*period),FALSE);
}
# define ioctl ioctlsocket
#else
double getTimeAsDouble(void)
{
  struct timeval tp;
  struct timezone tzp;
  gettimeofday(&tp, &tzp);
  return (double)tp.tv_sec + ((double)tp.tv_usec/1000000);
}

void sleepDouble(double period)
{
  fd_set aset;
  struct timeval tv;
  FD_ZERO(&aset);
  tv.tv_sec = period;
  tv.tv_usec = 1000000*(period-tv.tv_sec);
  select(0,&aset,&aset,&aset,&tv);
}
#endif


#if (defined(sun4s) || defined(nti) || defined(linux)) 
# define CASTFDSET 
#else 
# define CASTFDSET (int *)
#endif



/* DEBUGGING OUTPUT: comment out the following #define to remove it.
 * When present, define "SHOW_SELECT" in the environment (like
 * 'setenv SHOW_SELECT') to enable it.
 */
#define DO_SHOW_SELECT

#ifdef DO_SHOW_SELECT
# define DEBUG_DEST stdout
# define SHOW_SELECT(msg,rd,wr,er) print_select_parms(DEBUG_DEST,msg,rd,wr,er)

  static int do_show_select_initalized=0;
  static int do_show_select=0;

  static int print_fd_set(FILE *f, char const *msg, fd_set const *pmask)
  {
    int i,first=1,count=0;
    
    count += fprintf(f,"%s",msg);
    for (i=0; i<FD_SETSIZE; i++) {
      if (FD_ISSET(i,pmask)) {
	if (first) {
	  first=0;
	  count += fprintf(f,"{");
	}
	else {
	  count += fprintf(f,",");
	}
	count += fprintf(f,"%d",i);
      }
    }
    if (first)
      count += fprintf(f,"{");
    count += fprintf(f,"}");
    return count;
  }

  static int fill(FILE *f,int width)
  {
    int i;
    for (i=0; i<width; i++)
      fprintf(f," ");
    return width;
  }

  static void print_select_parms(FILE *f,
				 char const * msg, 
				 fd_set const *rd,
				 fd_set const *wr,
				 fd_set const *er)
  {
    int width;
    static int const col_width=20;

    if (!do_show_select_initalized) {
      /* do_show_select true iff SHOW_SELECT defined */
      do_show_select = (getenv("SHOW_SELECT") != 0);
      do_show_select_initalized=1;
    }

    if (do_show_select) {
      width=fprintf(f,"%s: ",msg);
      width+=fill(f,col_width-width);
      width+=print_fd_set(f," rd",rd);
      width+=fill(f,2*col_width-width);
      width+=print_fd_set(f," wr",wr);
      width+=fill(f,3*col_width-width);
      print_fd_set(f," er",er);
      printf("\n");
      fflush(f);
    }
  }

#else
# define DEBUG_DEST
# define SHOW_SELECT(msg,rd,wr,er) 
#endif


void ExtsleepUntil (double due)
{ 
  double now = getTimeAsDouble();
  if (due > now) sleepDouble (due-now);
}

#if defined(sun4s) || defined(hpux9pa) || defined(linux) || defined(sgi)
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

#endif

int getStandardIn ()
{ return fileno(stdin); } 

char sysenvGetCh ()
{ return getchar(); }

int readyBytes (int fd)
{
  long noOfBytes;
  int result;

#ifdef sun4s

  result=ioctl(fd,I_NREAD,&noOfBytes);
  if (result>0) 
    return noOfBytes;
  else 
    return 0;

#else

  result=ioctl(fd,FIONREAD,&noOfBytes);
  if (result==0) { return noOfBytes;} else { return 0;};

#endif
}

int sysenvKeyboardEOS()
{ int ch;

  ungetc(ch = getchar(),stdin);

  if (ch==EOF)
    return 1;
  else
    return 0;
}

char sysenvKeyboardPeek()
{ int ch;

  ch = getchar();
  if (ch != EOF) ungetc(ch, stdin);
  return ch;
}



/* SELECTSOCKETS
 * =============
 *
 * Checks which socket descriptors in readCandidates, writeCandidates
 * and exceptCandidates are ready for a non blocking read or write. 
 * readCandidates, writeCandidates and exceptCandidates are expected to 
 * be terminated by a file descriptor with value -1.
 * Entries in readCandidates  or writeCandidates that would block are set 
 * to -1 upon return. 
 * Ready descriptors are untouched.
 * The total number of descriptors ready for reading or writing is returned. 
 *
 * If (sec==-1) a blocking select call is used. Otherwise sec and usec
 * are used to specify the maximum amount of time to wait for some selector 
 * to get ready.
 *
 * ErrorCodes returned:
 *    -1: Error in select call.
 *
 */


int 
selectSockets (int *readCandidates, int *writeCandidates, int *exceptCandidates, int sec, int usec)
{ fd_set readFDSET, writeFDSET, exceptFDSET;
  struct timeval time;
  int i, max, res;

  max = 0;

  /* Insert readCandidates in readFDSET */
  FD_ZERO (&readFDSET);
  FD_ZERO (&writeFDSET);
  FD_ZERO (&exceptFDSET);

  i = 0;
  while (readCandidates[i] != -1) {
    FD_SET (readCandidates[i], &readFDSET);
    if (readCandidates[i] > max)
      max = readCandidates[i];
    i++;
  }

  /* Insert writeCandidates in writeFDSET*/
  i = 0;
  while (writeCandidates[i] != -1) {
    /* printf ("Setting %d in writers\n",writeCandidates[i]); */
    FD_SET (writeCandidates[i], &writeFDSET);
    if (writeCandidates[i] > max)
      max = writeCandidates[i];
    i++;
  }

  /* Insert exceptCandidates in exceptFDSET */
  i = 0;
  while (exceptCandidates[i] != -1) {
    /* printf ("Setting %d in writers\n",writeCandidates[i]); */
    FD_SET (exceptCandidates[i], &exceptFDSET);
    if (exceptCandidates[i] > max)
      max = exceptCandidates[i];
    i++;
  }

  SHOW_SELECT("systemenvExt.c: Selecting",&readFDSET,&writeFDSET,&exceptFDSET);
  
  if (sec==-1) {
    /* Use blocking select call. */
    res = select (max + 1, CASTFDSET &readFDSET, CASTFDSET &writeFDSET, 
		  CASTFDSET &exceptFDSET, NULL);

  } else {
    time.tv_sec = sec;
    time.tv_usec = usec;
    
    res = select (max + 1, CASTFDSET &readFDSET, CASTFDSET &writeFDSET, 
		  CASTFDSET &exceptFDSET, &time);
  }

  SHOW_SELECT("systemenvExt.c:  Selected",&readFDSET,&writeFDSET,&exceptFDSET);

  if (res >= 0) {
    res = 0;
    /* Check readers: */
    i = 0;
    while (readCandidates[i] != -1) {
      if (FD_ISSET (readCandidates[i], &readFDSET))
	res++;
      else
	readCandidates[i] = -1;
      i++;
    }
    
    /* Check writers: */
    i = 0;
    while (writeCandidates[i] != -1) {
      if (FD_ISSET (writeCandidates[i], &writeFDSET))
	res++;
      else
	writeCandidates[i] = -1;
      i++;
    }

    /* Check excepters: */
    i = 0;
    while (exceptCandidates[i] != -1) {
      if (FD_ISSET (exceptCandidates[i], &exceptFDSET))
	res++;
      else
	exceptCandidates[i] = -1;
      i++;
    }
  } else {
#ifdef nti
    errno = WSAGetLastError();
#endif
    switch (errno) {
#ifdef nti
    case WSAEINVAL:
#else
    case EINVAL:
#endif
      fprintf(stderr, 
	      "selectSockets: warning: select returned EINVAL\n", 
	      res);
      /* deliberately no break here: fall through */
#ifdef nti
    case WSAEINTR:
#else
    case EINTR:
#endif
      /* unset everything: */
      res = 0;
      
      /* Check readers: */
      i = 0;
      while (readCandidates[i] != -1) {
	readCandidates[i] = -1;
	i++;
      }
      
      /* Check writers: */
      i = 0;
      while (writeCandidates[i] != -1) {
	writeCandidates[i] = -1;
	i++;
      }
      
      /* Check excepters: */
      i = 0;
      while (exceptCandidates[i] != -1) {
	exceptCandidates[i] = -1;
	i++;
      }
      break;
#ifdef nti
    case WSAENOTSOCK:
#else
    case EBADF:
#endif
      fprintf(stderr, 
	      "selectSockets: error: select returned EBADF\n");
      break;
    default:
      fprintf(stderr, 
	      "selectSockets: unknown return code from select (%d)\n", 
	      res);
      break;
    }
  }

  return res;
}

#endif /* MAC */


