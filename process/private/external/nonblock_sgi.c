/*
 * COPYRIGHT
 *       Copyright Mjolner Informatics, 1993
 *       All rights reserved.
 */

#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <netinet/in.h>
#include <stdio.h>		/* to see FILE */
#include <values.h>		/* to see MAXINT */
#include <sys/types.h>
#include <sys/socket.h>         /* to see SOL_SOCKET, SO_TYPE */
#include <signal.h>		/* to see signal() */
#include <sys/param.h>		/* to see NOFILE */
#include <sys/time.h>		/* to see struct timeval */

#if defined(sun3) || defined(sun4)
#  include <sys/filio.h>	/* to see FIONREAD */
#  include <sys/sockio.h>	/* to see SIOCSPGRP */
#  define HPFD_cast
#  define SIGNALPARM void
#  define SOCKADDR_type sockaddr_in
#else
#  if defined(sun4s)
#  include <sys/filio.h>	/* to see FIONREAD */
#  include <sys/sockio.h>	/* to see SIOCSPGRP */
#  include <sys/stropts.h>	/* to see S_INPUT,S_ERROR */
#    define HPFD_cast
#    define SIGNALPARM int ignore
#    define SOCKADDR_type sockaddr
     /* #define CATCH_SIGTRAP !!! Who sends this signal, anyway? */
#  else
#    if defined(hp) || defined(hpux) || defined(hpux9pa) || defined (hpux9mc) || defined(sgi)
#      include <sys/ioctl.h>	/* to see FIONREAD & SIOCSPGRP */
#      define HPFD_cast (int*)
#      define SIGNALPARM int ignore
#      define SOCKADDR_type sockaddr_in
#    else
#      if defined(linux)
#        include <linux/termios.h>
#        define HPFD_cast
#        define SOCKADDR_type sockaddr
#      else
#        error "Unknown platform"
#      endif
#    endif
#  endif
#endif

/* #include <assert.h>  This doesn't work: the linker can't find '__eprintf' */

/********************************************************************
 *                                                                  *
 * DEBUGGING #defines:                                              *
 * Define any of these to invoke behaviour suitable for debugging   *
 * certain aspects of communication/signal handling.                *
 *                                                                  *
 ********************************************************************/

/* #define MAKE_CTRL_C_A_KILLER */
/* #define ECHO_TRANSFER */
/* #define ECHO_SPOT */
/* #define ECHO_ERROR */
/* #define SHOW_SIGIO */
/* #define SHOW_SIGALRM */

/* This is needed by communication_unixbody, but could be taken out */
#define SUPPORT_ASYNCHLEVEL

/* A readable and not too long filespec, used when ECHO_ERROR */
#define FILE_ID "process/v1.4/.../nonblock.c"

/* Use asynchronous sockets, and get a signal when data is available */
/* #define USE_SIGIO_HANDLER */

/********************************************************************
 *                                                                  *
 * Local support functions                                          *
 *                                                                  *
 ********************************************************************/

/* function 'validateSocket' tests whether or not 'fd' refers to a
 * socket. This might cease to be the case, when the other party
 * breaks a connection on a formerly healthy socket.
 *
 * args
 *   fd: file descriptor to test
 *
 * return value
 *   1, if it is a socket,
 *   0, otherwise
 */
static int validateSocket(int fd)
{
  int result,optval,optlen=sizeof(int);
  struct fd_set read_mask,write_mask,error_mask;
  struct timeval timeout;
  int width;

  do {
    /* !!! This could be optimized */
    FD_ZERO(&read_mask);
    FD_ZERO(&write_mask);
    FD_ZERO(&error_mask);
    FD_SET(fd,&read_mask);
    FD_SET(fd,&write_mask);
    FD_SET(fd,&error_mask);

    timeout.tv_sec = 0;
    timeout.tv_usec = 0;
    result=select(NOFILE,
		  HPFD_cast &read_mask,
		  HPFD_cast &write_mask,
		  HPFD_cast &error_mask,
		  &timeout);
    if (0>result)
      switch (errno) {
      case EINTR:
	continue;
      default:
	return 0;
      }
  } while (0);

  /* Ok, but end-of-file means: peer closed down */
  if (!FD_ISSET(fd,&error_mask) &&
      FD_ISSET(fd,&read_mask) &&
      sockToRead(fd)<=0) {
    errno=ENOTCONN;		/* C-lib doesn't set errno here */
    return 0;
  }

  return (0>result)? 0 : (FD_ISSET(fd,&error_mask)? 0 : 1);
}


/* function 'validateSocketSet' checks all file descriptors associated
 * with bits==1 in 'mask'. For non-valid sockets (and for non-sockets),
 * the corresponding bit is reset. This makes is safe to call select
 * with 'mask' as a selection parameter afterwards.
 *
 * args
 *   mask: pointer to set of file descriptors to examine; gets updated
 *
 * return value
 *   none
 */
static void validateSocketSet(struct fd_set *mask)
{
  int fd;

  for (fd=0; fd<NFDBITS; fd++) {
    if FD_ISSET(fd,mask) {
      if (!validateSocket(fd)) {
#       ifdef ECHO_SPOT
	  perror(FILE_ID ", (this is OK) spotted bad socket");
#       endif
	FD_CLR(fd,mask);
      }
    }
  }
}

/********************************************************************
 *                                                                  *
 * Signal handling functions                                        *
 *                                                                  *
 ********************************************************************/


/* function 'initSignalHandlers' installs all chosen signal
 * handlers.
 *
 * args
 *   none
 *
 * return value
 *   none
 */
void initSignalHandlers(void);


/* function 'catchSIGUSR' installs handlers for asynchronous,
 * process-external control of the amount of printout.
 * This can be used to focus on interesting passages from
 * a long stream of communication.
 *
 * args
 *   none
 *
 * return value
 *   none
 */
#ifdef SUPPORT_ASYNCHLEVEL

static int SIGUSR_installed=0;
static int asynch_level=0;

int asynchLevel(void)
{
  return asynch_level;
}

void onSigUsr1(SIGNALPARM)
{
  signal(SIGUSR1,onSigUsr1);
  asynch_level++;
}

void onSigUsr2(SIGNALPARM)
{
  signal(SIGUSR2,onSigUsr2);
  if (asynch_level)
    asynch_level--;
}

void catchSIGUSR(void)
{
  if (!SIGUSR_installed) {
    SIGUSR_installed=1;
    signal(SIGUSR1,onSigUsr1);
    signal(SIGUSR2,onSigUsr2);
  }
}

#define CATCHSIGUSR catchSIGUSR()
#else
#define CATCHSIGUSR
#endif

/* function 'catchSIGINT' provokes a segmentation fault, when
 * user presses ^C. This may be useful, for discovering where
 * the program execution is spending its time. To use it: #define
 * 'MAKE_CTRL_C_A_KILLER'. Purely a hack, only for debugging,
 * but handy!
 *
 * args
 *   none
 *
 * return value
 *   none
 */
#ifdef MAKE_CTRL_C_A_KILLER

static int SIGINT_installed=0;

void onSigInt(SIGNALPARM)
{
  char *p=0;
  *p=87;			/* as promised - a killer */
}

void catchSIGINT(void)
{
  if (!SIGINT_installed) {
    SIGINT_installed=1;
    signal(SIGINT,onSigInt);
  }
}

#define CATCHSIGINT catchSIGINT()
#else
#define CATCHSIGINT
#endif

/* function 'catchSIGALRM' prints a message, whenever the SIGALRM signal
 * is raised. Used temporarily in May 1993 to see, why on earth an
 * OODB-client (w/hypermedia) seems to get this signal without asking for it.
 *
 * args
 *   none
 *
 * return value
 *   none
 */
#ifdef SHOW_SIGALRM

void onSigAlrm(SIGNALPARM)
{
# if defined(hp) || defined(hpux8) || defined(snake)
    signal(SIGALRM,onSigAlrm);
# endif
  puts("\t<<SIGALRM raised>>");
}

void catchSIGALRM(void)
{
  signal(SIGALRM,onSigAlrm);
}

#define CATCHSIGALRM catchSIGALRM()
#else
#define CATCHSIGALRM
#endif

/* function 'catchSIGTRAP' prints a message, whenever the SIGTRAP signal
 * is raised. Used temporarily in May 1993 to see, why on earth an
 * OODB-client (w/hypermedia) seems to get this signal without asking for it.
 *
 * args
 *   none
 *
 * return value
 *   none
 */
#ifdef CATCH_SIGTRAP

void onSigTrap(SIGNALPARM)
{
# if defined(hp) || defined(hpux8) || defined(snake)
    signal(SIGTRAP,onSigTrap);
# endif
  puts("\t<<SIGTRAP raised>>");
}

void catchSIGTRAP(void)
{
  signal(SIGTRAP,onSigTrap);
}

#define CATCHSIGTRAP catchSIGTRAP()
#else
#define CATCHSIGTRAP
#endif

/* function 'catchSIGIO' checks to see if a SIGIO handler is installed
 * (by cWaitForIO). If not, such one gets installed, and the OS is asked
 * to generate SIGIO's.
 *
 * args
 *   none
 *
 * return value
 *   none
 *
 * IMPORTANT NOTE: Using 'catchSIGIO' will uninstall any previously
 * installed SIGIO handler.
 *
 ***********
 *
 * function 'waitForIO' makes this process wait until at least one of
 * the known sockets (all_sockets) becomes active (has data available
 * for reading).
 *
 * args
 *   socks: pointer to bitarray of sockets to select from
 *   max_wait: max length in seconds of period to wait for IO activity
 *
 * return value
 *   number of active file descriptors. Zero means timeout, no activity
 *   in case of error: -1.
 */
#ifdef USE_SIGIO_HANDLER

  void onSigIO(SIGNALPARM)
  {
#   ifdef SHOW_SIGIO
      puts("<<SIGIO>>");
#   endif
#   if defined(hp) || defined(hpux) || defined(sun4s)
      signal(SIGIO,onSigIO);	/* HP's og Solaris must be told every time! */
#   endif
  }

  void catchSIGIO(void)
  {
    static int HandlerInstalled=0;

    if (!HandlerInstalled) {
      signal(SIGIO,onSigIO);
      HandlerInstalled=1;
    }
  }

  static int waitForIO(struct fd_set *socks, long max_wait)
  {
    int numfds;
    struct timeval timeout;
    struct fd_set orig_socks = *socks;

    while (1) {
      timeout.tv_sec=max_wait;
      timeout.tv_usec=0;
      numfds=select(NOFILE, HPFD_cast socks,0,0,&timeout);

      if (0>numfds) {		/* Error during select call */
	if (EINTR==errno) {	/* Just 'interrupted system call', OK */
	  *socks=orig_socks;
	  continue;
	}
	else {			/* Real error */
#         ifdef ECHO_ERROR
	    perror(FILE_ID ", waitForIO");
#         endif
	  FD_ZERO(socks);	/* We don't trust them now! */
	  return -1;
	}
      }
      else {			/* No error during select call */
	return numfds;
      }
    }
  }

#define CATCHSIGIO catchSIGIO()
#else
#define CATCHSIGIO 
#endif


/* Implementetion of initSignalHandlers */
void initSignalHandlers(void)
{
  static installed;

  if (!installed) {
    installed=1;
    CATCHSIGUSR;
    CATCHSIGINT;
    CATCHSIGALRM;
    CATCHSIGTRAP;
  }
}


/* function 'cWaitForIO': a version of 'waitForIO' returning nothing to call
 * from beta. Always monitors (selects from) all sockets known by
 * the fragment communication_unixbody, i.e. 'all_sockets'.
 *
 * args
 *   max_wait: maximun period
 *
 * return value
 *   none
 */
#ifdef USE_SIGIO_HANDLER
  static struct fd_set all_sockets; /* Used to select from all our sockets */
  static struct fd_set no_sockets; /* Used to compare: any sockets? */

  void cWaitForIO(long max_wait)
  {
    struct fd_set all_socks; /* Local copy: gets changed */

    validateSocketSet(&all_sockets);
    if (!memcmp(&no_sockets,&all_sockets,sizeof(struct fd_set))) { /* no sck */
      sleep(max_wait);
    }
    else {
      all_socks = all_sockets;
      waitForIO(&all_socks,max_wait);
    }
  }
#else
  void cWaitForIO(long max_wait)
  {
    sleep(1); /* don't know when to leave, had better get going soon.. */
  }
#endif


/********************************************************************
 *                                                                  *
 * Support for passive socket                                       *
 *                                                                  *
 ********************************************************************/

/* function 'Errno' simply returns the value of the variable 'errno'
 * used by C-stdlib to report the most recent error.
 *
 * args
 *   none
 *
 * return value
 *   errno, promoted to a long, to please Beta
 */
long Errno(void)
{
  return errno;
}


/* function 'createPassiveSocket' creates a passive socket
 * and binds it to a port. In case the port is 0, a random,
 * free port is chosen, and the port number is returned in
 * (*port).
 *
 * args
 *   port: pointer to port number to bind socket to
 *
 * return value
 *   normally: file descriptor for the new passive socket
 *   in case of error: -1
 */
int createPassiveSocket(int *port)
{
  struct sockaddr_in sockaddr;
  int listenSock;
  int size;

  /* Create a socket */
  if((listenSock=socket(AF_INET,SOCK_STREAM,0))<0)
    return -1;

  /* Bind the socket */
  memset((char *)&sockaddr,0,sizeof(sockaddr)); /* instead of bzero */
  sockaddr.sin_family=AF_INET;
  sockaddr.sin_port=*port;
  sockaddr.sin_addr.s_addr=INADDR_ANY;
  if(bind(listenSock,(struct SOCKADDR_type*)&sockaddr,sizeof(sockaddr))<0)
    return -1;

  /* If the port number was 0, we must lookup the randomly chosen no. */
  if (!*port) {
    size = sizeof(sockaddr);
    if (getsockname (listenSock,(struct SOCKADDR_type*)&sockaddr,&size) == -1) {
#     ifdef ECHO_ERROR
        perror(FILE_ID ", get port number");
#     endif
      return -1;
    }
    (*port) = sockaddr.sin_port;
  }

  if(listen(listenSock,5)<0)
    return -1;

  return listenSock;
}

/* function 'wouldBlock' tests whether the most recent operation on a socket
 * would have blocked. Use it right after 'acceptConn'.
 *
 * args
 *   none
 *
 * return value
 *   if most recent operation would have blocked: 1
 *   otherwise: 0
 */
#ifdef USE_SIGIO_HANDLER
  static int nothingToAccept = 1;
#endif

int wouldBlock(void)
{
# ifdef USE_SIGIO_HANDLER
    return nothingToAccept;
# else
    return (errno == EWOULDBLOCK)? 1 : 0;
# endif
}

/* function 'acceptConn' substitutes 'acceptConnection' from
 * 'unixinterface.bet', because that function doesn't handle a non-blocking
 * passive socket correctly.
 *
 * args
 *   sock: file descriptor for passive socket to accept on
 *
 * return value
 *   normally: file descriptor of new, connected socket
 *   in case of error: -1
 */

int acceptConn(int sock)
{
  int newSock;
  struct SOCKADDR_type from;
  int fromaddrlen=sizeof( struct SOCKADDR_type );

#ifdef USE_SIGIO_HANDLER
  struct fd_set readmask;
  FD_ZERO(&readmask);
  FD_SET(sock,&readmask);

  if (0==waitForIO(&readmask,0)) {
    nothingToAccept=1;
    return -1;
  }
  else {
    nothingToAccept=0;
  }
#endif

  if ((newSock=accept(sock,&(from),&(fromaddrlen)))<0) {
    if (EINTR == errno) {
      return 0;
    }
    else {
#     ifdef ECHO_ERROR
        perror(FILE_ID ", acceptConn,2");
#     endif
      return -1;
    }
  }
  return newSock;
}

/********************************************************************
 *                                                                  *
 * Getting status of socket                                         *
 *                                                                  *
 ********************************************************************/

/* function 'sockToRead' computes the number of bytes immediately
 * readable from the socket associated with the file descriptor 'fd'.
 *
 * args
 *   fd: the socket to check
 *
 * return value
 *   normally: the number of bytes available from socket, a value >= 0
 *   in case of error: -1, check 'errno'.
 */

int sockToRead(int fd)
{
  long result;

  if (0>ioctl(fd,FIONREAD,(caddr_t)&result)) {
# ifdef ECHO_ERROR
    perror(FILE_ID ", sockToRead");
# endif
    return -1;
  }
  else
    return (result>MAXINT)? MAXINT : (int)result;
}

/* function 'sockStreamEos' computes the end-of-stream status for
 * a socket wrapped in a FILE. This is a bit tricky, since the
 * eof for a FILE does not get updated automatically. If you ever
 * get eof on a FILE, that status will persist on the FILE until
 * you 'fclose()' it or explicitly reset it by means of 'clearerr()'.
 * That means that neither "yes" nor "no" is a reliable answer wrt
 * the question can-we-read-now-from-this-FILE/socket.
 *
 * args
 *   fd: file descriptor for the socket acted on
 *   fp: FILE pointer for the FILE wrapper for the socket
 *
 * return value
 *   when no data in FILE buffer and in socket buffer: 1
 *   when some data in at least one of the buffers: 0
 */

int sockStreamEos(int fd, FILE* fp)
{
  long result;

  if (feof(fp)) {		/* eof detected, see if still true */
    ioctl(fd,FIONREAD,(caddr_t)&result);
    if (result>0) {
      clearerr(fp);		/* tell the stupid stream, eof is over */
      return 0;
    }
    else
      return 1;
  }
  else {			/* eof not detected */
    ioctl(fd,FIONREAD,(caddr_t)&result);
    if (result>0) {		/* data on socket: not eof */
      return 0;
    }
    else {
      /* NOTE: this depends on the declaration of
       * the FILE macro in <stdio.h>. There seems
       * to be no decent way to ask for the amount of data
       * in the FILE buffer.
       *
       * Rationale: "if data in buffer: return false (not eof)"
       */
#      if defined(sun3) || defined(sun4) || defined(sun4s)
         return (0 >= fp->_cnt);
#      else
#        if defined(hp) || defined(hpux8) || defined(snake)  || defined(hpux9pa) || defined (hpux9mc)
	   return (0 >= fp->__cnt);
#        else
#          if defined(linux)
	      /* This is ugly. See /usr/include/iolib.h */
	      return (fp->_IO_read_end==fp->_IO_read_ptr); /* !!! EE/940228 */
#          else
#             if defined(sgi)
                 fprintf(stderr, "sockStreamEos: NYI for SGI\n");
	         return 0;
#             else
#	         error "Unknown platform"
#             endif
#          endif
#        endif
#      endif
    }
  }
}

/********************************************************************
 *                                                                  *
 * Setting up a new socket                                          *
 *                                                                  *
 ********************************************************************/

/* function 'makeNonblocking' makes a socket use POSIX
 * style non-blocking communication. Afterwards, it
 * is not possible to revert the socket to a blocking
 * style of operation (as far as I know). The socket
 * may be open when you do 'makeNonblocking' (i.e. the
 * filedescriptor was obtained from 'accept()' or a
 * 'connect()' was called on it), but it is not legal
 * to do it on a passive socket (after 'bind()').
 *
 * args
 *   fd: file descriptor for the socket
 *
 * return value
 *   in case of error: -1
 *   when successful: man page just says 'value other than -1'
 */

int makeNonblocking(int fd)
{
  int result;

  initSignalHandlers();
  
  if (!validateSocket(fd)) {
#   ifdef ECHO_ERROR
      perror(FILE_ID ", makeNonblocking");
#   endif
    return -1;
  }

# ifdef USE_SIGIO_HANDLER
    FD_SET(fd,&all_sockets);

#   if defined(sun3) || defined(sun4)
      result=fcntl(fd,F_SETFL,FASYNC); /* Make this socket asynchronous */
#   else
#     if defined(sun4s)
        /* Oct-29-93 (EE)
	 * Compatibility manual (from Michael Glad, on Solaris-2.2)
	 * says "use O_SYNC in place of FASYNC".
	 */
        result=fcntl(fd,F_SETFL,O_SYNC);
#     else
#       if defined(hp) || defined(hpux)
          {
	    int flag=1;
            result=ioctl(fd,FIOASYNC /*FIOSSAIOSTAT*/,&flag);
          }
#       endif
#     endif
#   endif
#   ifdef ECHO_ERROR
      if (0>result)
        perror(FILE_ID ", makeNonblocking,3");
#   endif
    {
#     if defined(sun3) || defined(sun4)
        int flag=-getpid();
        result=ioctl(fd,SIOCSPGRP,&flag); /* Give this prcs. group the signal */
#     else
#       if defined(sun4s)
            /* Give me a signal in case of input or error */
            int flag=(S_INPUT|S_ERROR);
            result=ioctl(fd,I_SETSIG,flag);
#       else
#         if defined(hp) || defined(hpux)
            /* Give this process group the signal */
            int flag=-getpid();
            result=ioctl(fd,SIOCSPGRP /*FIOSSAIOOWN*/,&flag);
#         endif
#       endif
#     endif
#     ifdef ECHO_ERROR
        if (0>result)
          perror(FILE_ID ", makeNonblocking,4");
#     endif
    }
# else /* not defined(USE_SIGIO_HANDLER) */
    result=fcntl(fd,F_SETFL,O_NONBLOCK);
#   ifdef ECHO_ERROR
      if (0>result)
        perror(FILE_ID ", makeNonblocking,2");
#   endif
# endif

  return result;
}

/* function 'makePassiveNonblocking' makes a (supposedly) passive
 * socket BSD4.2-style non-blocking, for accepting connection
 * requests in a non-blocking manner. (The POSIX-style non-
 * blocking behaviour doesn't affect 'accept()'). Do this just
 * before 'bind()', and don't do 'makeNonblocking' on the same
 * socket.
 *
 * args
 *   fd: file descriptor for the passive socket
 *
 * return value
 *   in case of error: -1
 *   when successful: man page just says 'value other than -1'
 */

int makePassiveNonblocking(int fd)
{
  int result;

  if (!validateSocket(fd)) {
#   ifdef ECHO_ERROR
      perror(FILE_ID ", makePassiveNonblocking");
#   endif
    return -1;
  }

# ifdef USE_SIGIO_HANDLER
    FD_SET(fd,&all_sockets);
    catchSIGIO();
#   if defined(sun3) || defined(sun4)
      result=fcntl(fd,F_SETFL,FASYNC); /* Make this socket asynchronous */
#   else
#     if defined(sun4s)
        /* Oct-29-93 (EE)
	 * Compatibility manual (from Michael Glad, on Solaris-2.2)
	 * says "use O_SYNC in place of FASYNC".
	 */
        result=fcntl(fd,F_SETFL,O_SYNC);
#     else
#       if defined(hp) || defined(hpux)
          {
	    int flag=1;
            result=ioctl(fd,FIOASYNC /*FIOSSAIOSTAT*/,&flag);
          }
#       endif
#     endif
#   endif
#   ifdef ECHO_ERROR
      if (0>result)
        perror(FILE_ID ", makePassiveNonblocking,2");
#   endif
    {
      int flag=-getpid();
#     if defined(sun3) || defined(sun4) || defined(sun4s)
        /* Oct-27-93 (EE)
	 * !!! This is an experiment: should probably be changed
	 * same way as above, line 626/makeNonBlocking, OR vice versa !!!
	 */
        result=ioctl(fd,SIOCSPGRP,&flag); /* Give this prcs. group the signal */
#     else
#       if defined(hp) || defined(hpux)
          /* Give this process group the signal */
          result=ioctl(fd,SIOCSPGRP /*FIOSSAIOOWN*/,&flag);
#       endif
#     endif
#     ifdef ECHO_ERROR
        if (0>result)
          perror(FILE_ID ", makePassiveNonblocking,3");
#     endif
    }
# else
    result=fcntl(fd,F_SETFL,O_NDELAY);
#   ifdef ECHO_ERROR
      if (0>result)
        perror(FILE_ID ", makePassiveNonblocking,4");
#   endif
# endif

  return result;
}

/********************************************************************
 *                                                                  *
 * Data transfer                                                    *
 *                                                                  *
 ********************************************************************/

/* function 'readData' attempts to receive the number of bytes specified
 * in 'wanted' at the memory location 'destbuffer'. It is guaranteed that
 * nothing or 'wanted' bytes is received. If no data is ready for
 * receiveing at first attempt, the operation is aborted. If any data
 * are received, the operation blocks until 'wanted' bytes have been
 * received.
 *
 * args
 *   fd: file descriptor of socket acted on
 *   destbuffer: received data are written to this location
 *   wanted: number of bytes requested
 *
 * return value
 *   normally: number of bytes received
 *   in case of no data ready for receiving (operation stopped): 0
 *   in case of error: -1
 */

int readData(int fd, char *destbuffer, int wanted)
{
  /* Buffer management:
   *
   *           |-----------------wanted-------------|
   *           |-------total-------||-----rest------|
   *           =====================-----------------...
   *           ^destbuffer          ^put new data here
   *
   * invariants: total+rest == wanted, "firstFreePos" == destbuffer+total.
   */
  int total=0,rest=wanted,received,firstTry=1;

  /* assert(wanted>0); Too bad - this doesn't compile */

# ifdef USE_SIGIO_HANDLER
    struct fd_set readmask;

    FD_ZERO(&readmask);
    FD_SET(fd,&readmask);
    switch (waitForIO(&readmask,0)) {
    case -1:
#     ifdef ECHO_ERROR
      perror(FILE_ID ", readData");
#     endif
      return -1;

    case 0:
      return 0;			/* Means 'wouldblock' */
    }
    /* waitForIO returned 1, IO active on fd */
# endif

  for (;;) {
    if (total>=wanted)	/* That's it; ">=" and not "==" to play safe */
      break;

    switch (received=read(fd,destbuffer+total,rest)) {
    case -1:			/* ERROR */
      switch (errno) {
      case EAGAIN:
	if (firstTry) {
	  return 0;
	}
	else {
	  /* At this point a timeout check could be made. A timeout
	   * here is a fatal error (Implies kill-connection)!
	   */
	  break;		/* We've started reading - don't stop now */
	}

      case EINTR:		/* OK, data arrived! */
	break;

      default:
#       ifdef ECHO_ERROR
	perror(FILE_ID ", readData,2");
#       endif
	return -1;
      }
      break;

    case 0:			/* End-of-file - comm.partner closed down */
#     ifdef ECHO_ERROR
      if (!firstTry)
	fprintf(stderr,FILE_ID ", communication partner stopped unexpectedly");
#     endif
      errno=ENOTCONN;		/* The C-lib doesn't think this is an error */
      return -1;

    default:
#     ifdef ECHO_TRANSFER
      printf("C/read(%d/%d)\n",received,wanted);
#     endif
      total+=received;
      rest-=received;
    }

#   ifdef USE_SIGIO_HANDLER
    /* Avoid making many system calls while waiting for data to arrive */
    {
      struct fd_set readmask;

      FD_ZERO(&readmask);
      FD_SET(fd,&readmask);
      switch (waitForIO(&readmask,0)) {
      case -1:
#     ifdef ECHO_ERROR
	perror(FILE_ID ", readData,3");
#     endif
	return -1;
      }
      /* waitForIO returned 0 or 1 => IO or timeout: take another round */
    }
#   endif

    firstTry=0;		/* Next time and on: wait for whole packet */
  }
  return total;
}

/* function 'writeData' attempts to send the number of bytes specified
 * in 'length' from the memory location 'srcbuffer'. It is guaranteed that
 * nothing or 'length' bytes is sent. If a buffer full condition causes
 * no bytes to be sent on first try, the operation is aborted. If any data
 * are sent, the operation blocks until 'length' bytes have been
 * sent.
 *
 * args
 *   fd: file descriptor of socket acted on
 *   srcbuffer: data sent are taken from this location
 *   length: number of bytes in data area to send
 *
 * return value
 *   normally: number of bytes sent
 *   in case of buffer full at first try: 0
 *   in case of error: -1
 */

int writeData(int fd, char *srcbuffer, int length)
{
  /* Buffer management:
   *
   *           |-----------------length-------------|
   *           |-------total-------||-----rest------|
   *           ---------------------=================
   *           ^srcbuffer           ^un-sent data from here
   *
   * invariants: total+rest == length, "sendPos" == srcbuffer+total.
   */
  int total=0,rest=length,sent,firstTry=1;

  /* assert(length>0);		returning 0 must mean "try again later" */

  for (;;) {
    if (total>=length)	/* That's it; ">=" and not "==" to play safe */
      break;

    if (0 > (sent=write(fd,srcbuffer+total,rest)))
      switch (errno) {
      case EAGAIN:
	if (firstTry) {
	  return 0;
	}
	else
	  break;

      case EINTR:		/* OK, data arrived! */
	break;

      default:
#       ifdef ECHO_ERROR
	  perror(FILE_ID ", writeData");
#       endif
	return -1;
      }
    else {
#     ifdef ECHO_TRANSFER
        printf("C/wrote(%d/%d)\n",sent,length);
#     endif
      total+=sent;
      rest-=sent;
    }
    firstTry=0;		/* Next time and on: wait for whole packet */
  }
  return total;
}
