#include <sys/types.h>
#include <sys/time.h>
#include <stdio.h>
#include <sys/ioctl.h> 
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
#include <time.h>

#ifdef sun4s
#include <stropts.h>
#endif

void sleepUntil (int due)
{ int now = time (0);
  if (due > now) sleep (due-now);
}

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
{ char ch;

  ungetc(ch = getchar(),stdin);

  if (ch==EOF)
    return 1;
  else
    return 0;
}

char sysenvKeyboardPeek()
{ char ch;

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

#ifdef sun4s
#define CASTFDSET 
#else
#define CASTFDSET (int *)
#endif


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
  while (writeCandidates[i] != -1) {
    /* printf ("Setting %d in writers\n",writeCandidates[i]); */
    FD_SET (exceptCandidates[i], &exceptFDSET);
    if (exceptCandidates[i] > max)
      max = exceptCandidates[i];
    i++;
  }

  
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
  }

  return res;
}


