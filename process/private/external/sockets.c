/* ------------------------- FILE sockets.c ------------------------- */

/*
 * COPYRIGHT
 *       Copyright Mjolner Informatics, 1994
 *       All rights reserved.
 */


/*******************
 *                 *
 * Common includes *
 *                 *
 *******************/


#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <netdb.h>		/* to see struct hostent */
#include <netinet/in.h>
#include <stdio.h>		/* to see FILE */
#include <values.h>		/* to see MAXINT */
#include <sys/types.h>
#include <sys/socket.h>         /* to see SOL_SOCKET, SO_TYPE */
#include <sys/param.h>		/* to see NOFILE */
#include <sys/time.h>		/* to see struct timeval */
#include "sockSignals.h"

#define SUPPORT_TIMESTAMPING

#ifdef linux
#define TYPE_FD_SET fd_set
#else
#define TYPE_FD_SET struct fd_set
#endif

/***************************
 *                         *
 * Architecture dependance *
 *                         *
 ***************************/


/* Create well-defined symbols for architecture */

#include "arch.h"


/* Architecture dependant includes */

#if defined(A_SUN)
#  include <sys/filio.h>	/* to see FIONREAD */
#  include <sys/sockio.h>	/* to see SIOCSPGRP */
#  if defined(A_SUN4S)
#    include <sys/stropts.h>	/* to see S_INPUT,S_ERROR */
#  endif
#else
#  if (defined(A_HP) || defined(A_SGI))
#    include <sys/ioctl.h>	/* to see FIONREAD & SIOCSPGRP */
#  else
#    if defined(A_LINUX)
#      include <linux/termios.h>
#    else
#      error ARCH_UNKNOWN
#    endif
#  endif
#endif


/* Architecture dependant types/values */

#if (defined(A_SUN) || defined(A_SGI))
#  define HPFD_cast
#else
#  if defined(A_HP)
#    define HPFD_cast (int*)
#  else
#    if defined(A_LINUX)
#      define HPFD_cast
#    else
#      error ARCH_UNKNOWN
#    endif
#  endif
#endif

#if defined(A_SUN34)
#  define SIGNALPARM void
#else
#  if defined(A_HP) || defined(A_SUN4S) || defined(A_SGI)
#    define SIGNALPARM int ignore
#  else
#    if defined(A_LINUX)
#      define SIGNALPARM int ignore
#    else
#      error ARCH_UNKNOWN
#    endif
#  endif
#endif

#if defined(A_SUN34) || defined(A_HP)
#  define SOCKADDR_type sockaddr_in
#else
#  if defined(A_SUN4S) || defined(A_SGI)
#    define SOCKADDR_type sockaddr
#  else
#    if defined (A_LINUX)
#      define SOCKADDR_type sockaddr
#    else
#      error ARCH_UNKNOWN
#    endif
#  endif
#endif

#if defined(A_SUN4S)
#  define ERR_WOULDBLOCK EWOULDBLOCK
#else
#  define ERR_WOULDBLOCK EAGAIN
#endif


/********************************************************************
 *                                                                  *
 * DEBUGGING #defines:                                              *
 * Define any of these to invoke behaviour suitable for debugging   *
 * certain aspects of communication/signal handling.                *
 *                                                                  *
 ********************************************************************/


/* A readable and not too long filespec, for debug(gish) output */
#define FILE_ID "process/v1.4/.../sockets.c"

#define DO_ECHO_ERROR
#define DO_ECHO_ACTION
#define DO_ECHO_TRANSFER
#define DO_SHOW_SELECT

/* BEFORE include "echoError.h": redirect error output to stdout */
#define STDERR stdout
#include "echoError.h"

#ifdef DO_ECHO_TRANSFER

   /* This ought to go into its own file, echoError.c */

#  include <stdio.h>
#  include <ctype.h>
#  define MAXLISTLEN 200
#  define BLOCKS_PER_LINE 6
#  define PER_BLOCK 4
#  define min(a,b) ((a)<(b)? (a):(b))

   char *hexList(char *data, int len)
   {
     static char buffer[1024];
     int i,listLen=min(len,MAXLISTLEN);
     char *p;

     buffer[0]=0;
     p=buffer;

     for (i=0; i<listLen; i++) {
       if (!(i % (BLOCKS_PER_LINE*PER_BLOCK))) {
	 sprintf(p,"\n>>");
	 p += strlen("\n>>");
       }
       else if (!(i % 4)) {
	 sprintf(p,"  ");
	 p += strlen("  ");
       }
       sprintf(p," %02x",(int)(unsigned char)data[i]);
       p += strlen(" ##");
     }

     for (i=0; i<listLen; i++) {
       if (!(i % (BLOCKS_PER_LINE*PER_BLOCK))) {
	 sprintf(p,"\n>>");
	 p += strlen("\n>>");
       }
       else if (!(i % PER_BLOCK)) {
	 sprintf(p,"  ");
	 p += strlen("  ");
       }
       if isprint(data[i])
	 sprintf(p,"  %c",data[i]);
       else
	 sprintf(p,"  .");
       p += strlen("  .");
     }

     return buffer;
   }

#endif


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


#ifdef SUPPORT_TIMESTAMPING

/* A timestamp of zero means unknown/uninitialized */

#define MORE_THAN_MAXFD 512

#if defined(A_SUN4S)
#define MAXFD sysconf(_SC_OPEN_MAX)
#else
#define MAXFD NOFILE
#endif /* defined(A_SUN4S) */

static unsigned long current_timestamp;
static unsigned long timestamps[MORE_THAN_MAXFD];
static size_t max_fd;


#define CHECK_FD(fd,th,el) (0<=fd && fd<max_fd)? (th):(el)

#define INIT_TIMESTAMP() (max_fd=MAXFD)
#define GET_TIMESTAMP(fd) CHECK_FD(fd,(timestamps[(fd)]),0)
#define SET_TIMESTAMP(fd) CHECK_FD(fd,(timestamps[(fd)]=++current_timestamp),0)
#define RESET_TIMESTAMP(fd) CHECK_FD(fd,(timestamps[(fd)]=0),0)

#else

#define INIT_TIMESTAMP()
#define GET_TIMESTAMP(fd) 0
#define SET_TIMESTAMP(fd)
#define RESET_TIMESTAMP(fd)

#endif /* SUPPORT_TIMESTAMPING */

unsigned long getTimeStamp(long fd)
{
  return GET_TIMESTAMP(fd);
}


/********************************************************************
 *                                                                  *
 * Initialization of this module                                    *
 *                                                                  *
 ********************************************************************/


/* function 'initSockets' initializes signal handlers etc.
 * It is idempotent.
 *
 * args
 *   none
 *
 * return value
 *   none
 */
void initSockets(void)
{
  static initialized=0;

  if (!initialized) {
    initialized = 1;
    INIT_TIMESTAMP();
    initSockSignals();

    /* This will print out the message iff it is true */
    ECHO_USER_ERROR("C-layer is compiled to echo communication errors");
  }
}


/********************************************************************
 *                                                                  *
 * Local support for this file                                      *
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
  long dummy;
  int dummy_len=sizeof(dummy);
  int res=getsockopt(fd,SOL_SOCKET,SO_TYPE,(char*)&dummy,&dummy_len);

  if (0>res) {
    RESET_TIMESTAMP(fd);
    errno=ENOTSOCK;		/* ANY error means 'Not a socket' */
    return 0;
  }
  else {
    SET_TIMESTAMP(fd);
    return 1;
  }
}


/* function 'selectReadable' tests whether the 'select' system call
 * views the socket with file descriptor 'fd' as readable.
 *
 * args
 *   fd: file descriptor to test
 *
 * return value
 *   0, if not readable
 *   1, if readable
 *   -1, in case of error
 */
long selectReadable(int fd)
{
  static TYPE_FD_SET read_mask,write_mask,error_mask;
  static struct timeval timeout = {0,0};
  long result;
  int err,err_size=sizeof(err);

  SET_TIMESTAMP(fd);

  /* Ask select whether socket is readable */
  do {
    FD_ZERO(&read_mask);
    FD_ZERO(&error_mask);
    FD_SET(fd,&read_mask);
    FD_SET(fd,&error_mask);

    SHOW_SELECT("selectReadable",&read_mask,&write_mask,&error_mask);
    if (0 > (result=select(fd+1,
			   HPFD_cast &read_mask,
			   HPFD_cast &write_mask,
			   HPFD_cast &error_mask,
			   &timeout))) {
      SHOW_SELECT("       (error)",&read_mask,&write_mask,&error_mask);
      if (EINTR == errno)
	continue;		/* interrupted ssytem call: restart */
      else
	return -1;		/* probably bad file descriptor */
    }
    SHOW_SELECT("          (ok)",&read_mask,&write_mask,&error_mask);
  } while (0);

  if (FD_ISSET(fd,&error_mask))	/* socket in error condition */
    return -1;
  if (FD_ISSET(fd,&read_mask))	/* socket ok and readable */
    return 1;
  return 0;			/* socket ok but not readable */
}


/* finction 'doBlock' waits for a possibility to read/write, and 
 * returns after at most 'timeoutValue' seconds, returning
 * non-zero iff the desired read/write is possible or an error
 * has occurred (this also has to be attended to).
 *
 * args
 *   fd: file descriptor to test
 *   rd: non-zero means "I want to read"
 *   wr: non-zero means "I want to write"
 *   timeoutValue: upper bound on number of seconds to wait
 *
 * return value
 *   if timed out: 1
 *   if error occurred on fd: 0
 *   if desired read/write is possible: 0
 */
long doBlock(long fd, long rd, long wr, long timeoutValue)
{
  static TYPE_FD_SET read_mask,write_mask,error_mask;
  static struct timeval timeout = {0,0};
  struct timeval *ptm;
  long result;
  int err,err_size=sizeof(err);

  SET_TIMESTAMP(fd);

  if (-1==timeoutValue)		/* unlimited timeout */
    ptm=0;
  else {
    ptm=&timeout;
    ptm->tv_sec=timeoutValue;
  }

  /* Ask select whether socket is readable */
  do {
    FD_ZERO(&read_mask);
    FD_ZERO(&write_mask);
    FD_ZERO(&error_mask);
    if (rd) FD_SET(fd,&read_mask);
    if (wr) FD_SET(fd,&write_mask);
    FD_SET(fd,&error_mask);

    SHOW_SELECT("       doBlock",&read_mask,&write_mask,&error_mask);
    if (0 > (result=select(fd+1,
			   HPFD_cast &read_mask,
			   HPFD_cast &write_mask,
			   HPFD_cast &error_mask,
			   ptm))) {
      SHOW_SELECT("       (error)",&read_mask,&write_mask,&error_mask);
      if (EINTR == errno)
	continue;		/* interrupted ssytem call: restart */
      else
	return -1;		/* probably bad file descriptor */
    }
    SHOW_SELECT("          (ok)",&read_mask,&write_mask,&error_mask);
  } while (0);

  if (!result)
    return 1;			/* timed out */
  if (FD_ISSET(fd,&error_mask))
    return 0;			/* error occurred, get going! */  
  if (rd && !FD_ISSET(fd,&read_mask))
    return 1;			/* would read, but can't */
  if (wr && !FD_ISSET(fd,&write_mask))
    return 1;			/* would write, but can't */
  return 0;			/* ready */
}


/********************************************************************
 *                                                                  *
 * Retrieving error number                                          *
 *                                                                  *
 ********************************************************************/


/* function 'Errno' simply returns the value of the variable 'errno'
 * used by C-stdlib to report the most recent error.
 *
 * args
 *   none
 *
 * return value
 *   errno, promoted to a long, to please BETA
 */
long Errno(void)
{
  return errno;
}


/********************************************************************
 *                                                                  *
 * Utility functions for IP addresses etc.                          *
 *                                                                  *
 ********************************************************************/

unsigned long
host2inetAddr(char *host)
{
  struct hostent *pHostInfo=gethostbyname(host);

  if (!pHostInfo) {
    ECHO_ERROR("host2inetAddr");
    return -1;
  }
  return ntohl(*(unsigned long *)(*pHostInfo->h_addr_list));
}


char const *
nameOfThisHost(long *pErrorCode)
{
  static int nameOfThisHostCached=0;
  static char nameOfThisHostCache[MAXHOSTNAMELEN+1];

  if (!nameOfThisHostCached) {
    struct hostent *pHostInfo;

    if (0 > gethostname(nameOfThisHostCache,MAXHOSTNAMELEN)) {
      ECHO_ERROR("nameOfThisHost");
      *pErrorCode=-1;
      return "";
    }
    nameOfThisHostCached=1;
  }
  *pErrorCode=0;
  return nameOfThisHostCache;
}


unsigned long
inetAddrOfThisHost(void)
{
  static int inetAddrOfThisHostCached=0;
  static unsigned long inetAddrOfThisHostCache;
  long errorCode;

  if (!inetAddrOfThisHostCached) {
    struct hostent *pHostInfo=gethostbyname(nameOfThisHost(&errorCode));

    if (!pHostInfo) {
      ECHO_ERROR("inetAddrOfThisHost");
      return -1;
    }
    if (0 > errorCode) {
      /* no ECHO_ERROR here: has already been reported */
      return -1;
    }
    inetAddrOfThisHostCache = ntohl(*(unsigned long *)(*pHostInfo->h_addr_list));
    inetAddrOfThisHostCached=1;
  }
  return inetAddrOfThisHostCache;
}


/********************************************************************
 *                                                                  *
 * Support for active socket                                        *
 *                                                                  *
 ********************************************************************/

/* inetAddr & port is in HOST byteorder. */
int openActiveSocket(unsigned long inetAddr, long port)
{
  struct sockaddr_in addr;
  int sock;

  /* Create a socket */
  if((sock=socket(AF_INET,SOCK_STREAM,0))<0) {
    ECHO_ERROR("openActiveSocket,1");
    return -1;
  }

  /* And connect to the server */
  memset((char *)&addr,0,sizeof(addr)); /* instead of bzero */
  addr.sin_family=AF_INET;
  addr.sin_port=htons((unsigned short)port);
  addr.sin_addr.s_addr=htonl(inetAddr);

  if(connect(sock,(struct SOCKADDR_type*)&addr,sizeof(addr))<0) {
    ECHO_ERROR("openActiveSocket,2");
    return -1;
  }

  SET_TIMESTAMP(sock);

  /* Connection is now established and the descriptor is in sock */
  ECHO_ACTION("opened active socket",sock,port);
  return sock;
}


/********************************************************************
 *                                                                  *
 * Support for passive socket                                       *
 *                                                                  *
 ********************************************************************/


/* function 'createPassiveSocket' creates a passive socket
 * and binds it to a port. In case the port is 0, a random,
 * free port is chosen, and the port number is returned in
 * (*port). The internet address (225.130.16.214 style value
 * as an unsigned long integer) for this passiveSocket (i.e.
 * this host) is returned in (*pInetAddr), iff the operation
 * succeeds.
 *
 * args
 *   port: pointer to port number to bind socket to
 *   pInetAddr: pointer to place to put internet address
 *
 * return value
 *   normally: file descriptor for the new passive socket
 *   in case of error: -1
 */
int createPassiveSocket(long *port, unsigned long *pInetAddr)
{
  struct sockaddr_in sockaddr;
  int listenSock;
  int size;

  /* Create a socket */
  if (0>(listenSock=socket(AF_INET,SOCK_STREAM,0))) {
    ECHO_ERROR("createPassiveSocket,1");
    return -1;
  }

  /* Bind the socket */
  memset((char *)&sockaddr,0,sizeof(sockaddr)); /* instead of bzero */
  sockaddr.sin_family=AF_INET;
  sockaddr.sin_port=htons((unsigned short)*port);
  sockaddr.sin_addr.s_addr=INADDR_ANY;
  if(0>bind(listenSock,(struct SOCKADDR_type*)&sockaddr,sizeof(sockaddr))) {
    ECHO_ERROR("createPassiveSocket,2");
    return -1;
  }

  /* If the port number was 0, we must lookup the randomly chosen no. */
  if (!*port) {
    size = sizeof(sockaddr);
    if (0>getsockname(listenSock,(struct SOCKADDR_type*)&sockaddr,&size)) {
      ECHO_ERROR("createPassiveSocket,3");
      return -1;
    }
    (*port) = ntohs(sockaddr.sin_port);
  }

  /* Ask OS to create client request queue */
  if (listen(listenSock,5)<0) {
    ECHO_ERROR("createPassiveSocket,4");
    return -1;
  }

  /* Report internet address of this host */
  {
    unsigned long inetAddr=inetAddrOfThisHost();
    if (0 > inetAddr) {
      ECHO_ERROR("createPassiveSocket,5");
      errno=0; /* Make this situation detectable */
      return -1;
    }
    *pInetAddr=inetAddr;
  }

  SET_TIMESTAMP(listenSock);

  ECHO_ACTION("created passive socket",listenSock,*port);
  return listenSock;
}


/* function 'acceptConn' substitutes 'acceptConnection' from
 * 'unixinterface.bet', because that function doesn't handle a non-blocking
 * passive socket correctly. On return (*pBlocked) will be 1 iff the
 * operation was terminated because it would have blocked, and 0
 * otherwise.
 *
 * args
 *   sock: file descriptor for passive socket to accept on
 *   pBlocked: pointer to integer, used to tell caller whether op. blocked
 *   pInetAddr: pointer to place to put internet address of peer.
 *
 * return value
 *   normally: file descriptor of new, connected socket
 *   in case of error: -1
 */
int acceptConn(int sock, int *pBlocked, unsigned long *pInetAddr)
{
  int newSock;
  struct SOCKADDR_type from;
  int fromaddrlen=sizeof( struct SOCKADDR_type );

  SET_TIMESTAMP(sock);

  *pBlocked=0;
  do {
    if ((newSock=accept(sock,&(from),&(fromaddrlen)))<0) {
      switch (errno) {
      case EINTR:		/* Interrupt during system call .. */
	continue;		/* .. simply restart it */
      case EWOULDBLOCK:		/* not ready */
	*pBlocked=1;
	return 0;
      default:
	ECHO_ERROR("acceptConn");
	return -1;
      }
    }
  } while (0);

  /* Report internet address of peer */
  {
    struct sockaddr_in peer;
    int size = sizeof(peer);

    if (0>getpeername(newSock,(struct SOCKADDR_type*)&peer,&size)) {
      ECHO_ERROR("acceptConn,2");
      return -1;
    }
    *pInetAddr=ntohl(peer.sin_addr.s_addr);
  }

  SET_TIMESTAMP(newSock);

  ECHO_ACTION("accepted new connection",newSock,*pInetAddr);
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

  SET_TIMESTAMP(fd);

  if (0>ioctl(fd,FIONREAD,(caddr_t)&result)) {
    ECHO_ERROR("sockToRead");
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
 * the question can-we-read-now-from-this-FILE-which-is-a-socket.
 *
 * args
 *   fd: file descriptor for the socket acted on
 *   fp: FILE pointer for the FILE wrapper for the socket
 *
 * return value
 *   when no data in FILE buffer and in socket buffer: 1
 *   when some data in at least one of the buffers: 0
 *   in case of error: -1
 */
int sockStreamEos(int fd, FILE* fp)
{
  long result;

  SET_TIMESTAMP(fd);

  if (feof(fp)) {		/* eof detected, see if still true */
    if (0>ioctl(fd,FIONREAD,(caddr_t)&result)) {
      return -1;
    }
    if (result>0) {
      clearerr(fp);		/* tell the stupid stream, eof is over */
      return 0;
    }
    else
      return 1;
  }
  else {			/* eof not detected */
    if (0>ioctl(fd,FIONREAD,(caddr_t)&result)) {
      return -1;
    }
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
#      if defined(A_SUN) || defined(A_SGI)
         return (0 >= fp->_cnt);
#      else
#        if defined(A_HP)
	   return (0 >= fp->__cnt);
#        else
#          if defined(A_LINUX)
	     /* !!! This has NOT been tested! */
             return (0 >= fp->_IO_read_end - fp->_IO_read_ptr);
#          else
#	     error ARCH_UNKNOWN
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
 *   when successful: 0
 *   in case of error: -1
 */
int makeNonblocking(int fd)
{
  int on=1;

  if (!validateSocket(fd)) {
    ECHO_ERROR("makeNonblocking");
    return -1;
  }

  if (0>fcntl(fd,F_SETFL,O_NONBLOCK)) {
    ECHO_ERROR("makeNonblocking,2");
    return -1;
  }

  if (0>setsockopt(fd,SOL_SOCKET,SO_KEEPALIVE,(char*)&on,sizeof(on))) {
    ECHO_ERROR("makeNonblocking,3");
    return -1;
  }

  SET_TIMESTAMP(fd);

  ECHO_ACTION("made socket nonblocking",fd,0);
  return 0;
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
 *   when successful: 0
 *   in case of error: -1
 */
int makePassiveNonblocking(int fd)
{
  if (!validateSocket(fd)) {
    ECHO_ERROR("makePassiveNonblocking");
    return -1;
  }

  if (0>fcntl(fd,F_SETFL,O_NDELAY)) {
    ECHO_ERROR("makePassiveNonblocking,2");
    return -1;
  }

  SET_TIMESTAMP(fd);

  ECHO_ACTION("made passive socket nonblocking",fd,0);
  return 0;
}


/********************************************************************
 *                                                                  *
 * Data transfer                                                    *
 *                                                                  *
 ********************************************************************/


/* function 'readDataMax' attempts to receive at most the number of
 * bytes specified in 'buflen' at the memory location 'destbuffer'.
 * If no data is ready at first attempt, there are two possible
 * outcomes: In the case where 'fd' refers to a blocking socket,
 * the operation blocks until some data is available. If
 * 'fd' refers to a non-blocking socket, the operation ends
 * immediately. If data is available, min{available,buflen}
 * bytes are received, and the operation ends.
 *
 * args
 *   fd: file descriptor of socket acted on
 *   destbuffer: received data are written to this location
 *   buflen: maximum number of bytes to receive
 *
 * return value
 *   normally: number of bytes received - possibly 0
 *   in case of error: -1 (NB: "no-data-received" is not an error)
 */
int readDataMax(int fd, char *destbuffer, int buflen)
{
  int received;

  SET_TIMESTAMP(fd);

  do {
    switch (received=read(fd,destbuffer,buflen)) {
    case -1:			/* ERROR */
      switch (errno) {
      case ERR_WOULDBLOCK:	/* No data available */
	return 0;
      case EINTR:		/* Interrupted, just restart */
	continue;
      default:
	ECHO_ERROR("readDataMax,1");
	return -1;
      }
      break;

    case 0:
      /* No data available and not WOULDBLOCK: comm.partner closed down */
      ECHO_USER_ERROR("other party closed down; readDataMax,2");
      errno=ENOTCONN;
      return -1;

    default:
      ECHO_TRANSFER("read",fd,destbuffer,received,buflen);
    }
  } while (0);
  return received;
}


/* function 'writeDataMax' attempts to send at most the number of
 * bytes specified in 'length' from the memory location 'srcbuffer'.
 * If no data can be written at first attempt, there are two
 * possible outcomes: In the case where 'fd' refers to a blocking
 * socket, the operation blocks until some data have have been
 * sent. If 'fd' refers to a non-blocking socket, the operation
 * ends immediately. In any case, the number of bytes sent is
 * what the OS accepts in one go, and this may be less than
 * 'buflen'.
 *
 * args
 *   fd: file descriptor of socket acted on
 *   srcbuffer: points to data to send
 *   length: maximum number of bytes to send
 *
 * return value
 *   normally: number of bytes sent - possibly 0
 *   in case of error: -1
 */
int writeDataMax(int fd, char *srcbuffer, int length)
{
  int sent;

  SET_TIMESTAMP(fd);

  do {
    if (0 > (sent=write(fd,srcbuffer,length)))
      switch (errno) {
      case ERR_WOULDBLOCK:	/* Buffer full */
	return 0;
      case EINTR:		/* Interrupt, just restart */
	continue;
      default:
	ECHO_ERROR("writeDataMax");
	return -1;
      }
    else {
      ECHO_TRANSFER("wrote",fd,srcbuffer,sent,length);
    }
  } while (0);

  return sent;
}

/* ------------------------- END sockets.c ------------------------- */
