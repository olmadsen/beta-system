#ifdef nti
# include <sys/types.h>
# include <stdio.h>
# include <fcntl.h>
# include <errno.h>
# include <time.h>
# include <winsock.h>
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
  void sleep(long period)
  {
    Sleep(1000*period);
  }
# define ioctl ioctlsocket
#endif

#if (defined(sun4s) || defined(nti))
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
    switch(errno){
    case EINVAL:
      fprintf(stderr, 
	      "selectSockets: warning: select returned EINVAL\n", 
	      res);
      /* deliberately no break here: fall through */
    case EINTR:
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
    case EBADF:
      fprintf(stderr, 
	      "selectSockets: error: select returned EBADF\n", 
	      res);
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


