
#include "beta.h"

#define INFO_SOCKETS(string) DEBUG_SOCKETS(fprintf(output, string))

#include <string.h>
#include <errno.h>
#include <stdio.h>		/* to see FILE */


#ifdef nti
#  ifdef nti_gnu
#    include <Windows32/Sockets.h> 
#  else
#    include <winsock.h> 
#  endif
#  include <limits.h>
#else
#  define SUPPORT_TIMESTAMPING
#  include <fcntl.h>
#  include <unistd.h>
#  include <netdb.h>		/* to see struct hostent */
#  include <netinet/in.h>
/* #  include <values.h> defines maxint twice? *//* to see MAXINT */
#  include <sys/socket.h>         /* to see SOL_SOCKET, SO_TYPE */
#  include <sys/param.h>		/* to see NOFILE */
#  include <sys/time.h>		/* to see struct timeval */
#  include <sys/types.h>
#endif

/* Architecture dependant includes */

#ifdef sun4s
#  include <sys/filio.h>	/* to see FIONREAD */
#  include <sys/sockio.h>	/* to see SIOCSPGRP */
#  include <sys/stropts.h>	/* to see S_INPUT,S_ERROR */
#  include <signal.h>
#endif
#if (defined(hpux9pa) || defined(sgi) || defined(linux))
#  include <sys/ioctl.h>	/* to see FIONREAD & SIOCSPGRP */
#  include <signal.h>
#endif
#ifdef linux
#  include <linux/termios.h>
#endif

/* Architecture dependant types/values */

#if defined(sun) || defined(sgi)
#  define HPFD_cast
#else
#  ifdef hpux9pa
#    define HPFD_cast (int*)
#  else
#    ifdef linux
#      define HPFD_cast
#    else
#      ifdef nti
#        define HPFD_cast
#      else
#        error ARCH_UNKNOWN
#      endif
#    endif
#  endif
#endif

#if defined(hpux9pa) || defined(sun4s) || defined(sgi)
#  define SIGNALPARM int ignore
#else
#  ifdef linux
#    define SIGNALPARM int ignore
#  endif
#endif

#ifdef hpux9pa
#  define SOCKADDR_type sockaddr_in
#else
#  if defined(sun4s) || defined(sgi)
#    define SOCKADDR_type sockaddr
#  else
#    ifdef linux
#      define SOCKADDR_type sockaddr
#    else
#      ifdef nti
#        define SOCKADDR_type sockaddr
#      else
#        error ARCH_UNKNOWN
#      endif
#    endif
#  endif
#endif

#ifndef ERR_WOULDBLOCK
# ifdef sun4s
#  define ERR_WOULDBLOCK EWOULDBLOCK
# else
#  define ERR_WOULDBLOCK EAGAIN
# endif
#endif


#ifdef nti
#  define MAXHOSTNAMELEN 256 /* Value from fraxinus:'man gethostname' */
#ifndef MAXINT
#  define MAXINT INT_MAX
#endif
#endif

#ifdef sun4s
  extern int gethostname(char*name, int len);
#endif
#ifdef sgi
  extern void bzero(char *s, int n);
#endif

#ifdef SUPPORT_TIMESTAMPING

/* A timestamp of zero means unknown/uninitialized */

#define MORE_THAN_MAXFD 512

#if defined(A_SUN4S)
#  define MAXFD sysconf(_SC_OPEN_MAX)
#else
#  define MAXFD NOFILE
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
#define GET_TIMESTAMP(fd) (fd-fd)
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
#ifdef nti

static void StopWSA(void)
{
  WSACleanup();
}

static void StartWSA(void)
{
  WSADATA wsadata;

  INFO_SOCKETS("WSAStartup");
  if (WSAStartup(MAKEWORD(1,1), &wsadata) == 0) {
    atexit(StopWSA);
  } else {
    INFO_SOCKETS("WSAStartup failed");
    exit(1);
  }
}

# define START_WSA() StartWSA()
#else
# define START_WSA()
#endif

void initSockSignals(void)
{
#if defined(hpux9pa) || defined(sun4s)
  signal(SIGPIPE, SIG_IGN);  
#endif
}

void initSockets(void)
{
  static initialized=0;

  if (!initialized) {
    initialized = 1;
    INIT_TIMESTAMP();
    START_WSA();
#if !defined(RTVALHALLA)
    initSockSignals();
#endif
    /* This will print out the message iff it is true */
    INFO_SOCKETS("Sockets:C-layer is compiled to echo communication errors");
  }
}


/********************************************************************
 *                                                                  *
 * Local support for this file                                      *
 *                                                                  *
 ********************************************************************/




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
  static struct fd_set read_mask,write_mask,error_mask;
  static struct timeval timeout = {0,0};

  SET_TIMESTAMP(fd);

  /* Ask select whether socket is readable */
  do {
    FD_ZERO(&read_mask);
    FD_ZERO(&error_mask);
    FD_SET(fd,&read_mask);
    FD_SET(fd,&error_mask);

    if (0 > select(fd+1,
			   HPFD_cast &read_mask,
			   HPFD_cast &write_mask,
			   HPFD_cast &error_mask,
			   &timeout))
    {
#ifdef nti
    errno = WSAGetLastError();
#endif
      if (EINTR == errno)
	continue;		/* interrupted ssytem call: restart */
      else
	return -1;		/* probably bad file descriptor */
    }
  } while (0);

  if (FD_ISSET(fd,&error_mask))	/* socket in error condition */
    return -1;
  if (FD_ISSET(fd,&read_mask))	/* socket ok and readable */
    return 1;
  return 0;			/* socket ok but not readable */
}


/* function 'doBlock' waits for a possibility to read/write, and 
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
  static struct fd_set read_mask,write_mask,error_mask;
  static struct timeval timeout = {0,0};
  struct timeval *ptm;
  long result;

  INFO_SOCKETS("doBlock: This does not work with systemEnv (doing it anyway)")

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

    if (0 > (result=select(fd+1,
			   HPFD_cast &read_mask,
			   HPFD_cast &write_mask,
			   HPFD_cast &error_mask,
			   ptm))) 
    {
#ifdef nti
    errno = WSAGetLastError();
#endif
      if (EINTR == errno)
	continue;		/* interrupted ssytem call: restart */
      else
	return -1;		/* probably bad file descriptor */
    }
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
 * On NT, make sure to set errno to WSAGetLastError in the C-func that 
 * failed, if that is the kind of error, the BETAcode expects.
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

/* 
 *  Find host by name. Return IP-address in host-byteorder. 
 */
signed long host2inetAddr(char *host)
{
  struct hostent *pHostInfo=gethostbyname(host);

  if (!pHostInfo) {
    INFO_SOCKETS("host2inetAddr");
#ifdef nti
    errno = WSAGetLastError();
#endif
    return -1;
  }
  return ntohl(*(unsigned long *)(*pHostInfo->h_addr_list));
}


/* 
 *  Get name of this host. (cached here.)
 */
char const *nameOfThisHost(long *pErrorCode)
{
  static int nameOfThisHostCached=0;
  static char nameOfThisHostCache[MAXHOSTNAMELEN+1];

  if (!nameOfThisHostCached) {
#ifdef nti
    if (gethostname(nameOfThisHostCache,MAXHOSTNAMELEN)==SOCKET_ERROR) {
#else
    if (0 > gethostname(nameOfThisHostCache,MAXHOSTNAMELEN)) {
#endif
#ifdef nti
      errno = WSAGetLastError();
      switch (errno) {
      case WSAEFAULT:
	INFO_SOCKETS("gethostname (WSAEFAULT)\n");
	break;
      case WSAEINPROGRESS:
	INFO_SOCKETS("gethostname (WSAEINPROGRESS)\n");
	break;
      case WSANOTINITIALISED:
	INFO_SOCKETS("gethostname (WSANOTINITIALISED)\n");
	break;
      case WSAENETDOWN:
	INFO_SOCKETS("gethostname (WSAENETDOWN)\n");
	break;
      default:
	DEBUG_SOCKETS(fprintf(output,"gethostname (%d ?)\n",errno));
	break;
      }
#endif
      INFO_SOCKETS("nameOfThisHost");
      *pErrorCode=-1;
      return "";
    }
    nameOfThisHostCached=1;
  }
  *pErrorCode=0;
  return nameOfThisHostCache;
}


/*
 *  Get IP-address of this host in host-byteorder. (Cached here)
 */
signed long inetAddrOfThisHost(void)
{
  static int inetAddrOfThisHostCached=0;
  static unsigned long inetAddrOfThisHostCache;
  long errorCode;

  if (!inetAddrOfThisHostCached) {
    struct hostent *pHostInfo=gethostbyname(nameOfThisHost(&errorCode));

    if (!pHostInfo) {
      INFO_SOCKETS("inetAddrOfThisHost");
#ifdef nti
      errno = WSAGetLastError();
#endif
      return -1;
    }
    if (0 > errorCode) {
      /* no INFO_SOCKETS here: has already been reported */
#ifdef nti
      errno = WSAGetLastError();
#endif
      return -1;
    }
    inetAddrOfThisHostCache = ntohl(*(unsigned long *)(*pHostInfo->h_addr_list));
    inetAddrOfThisHostCached = 1;
  }
  return inetAddrOfThisHostCache;
}


/********************************************************************
 *                                                                  *
 * Support for active socket                                        *
 *                                                                  *
 ********************************************************************/

/* inetaddres & Portnumber in HOST byte-order. */

int createActiveSocket(unsigned long inetAddr, long port, int nonblock)
{
  int on = 1;
  struct sockaddr_in addr;
  int sock;
  struct linger li;
  
  li.l_onoff=0;
  li.l_linger=0;

  /* Create a socket */
  DEBUG_SOCKETS(fprintf(output, "Connecting to 0x%8x port %d on sock=", 
			(int)inetAddr, (int)port));
#ifdef nti

  if((sock = socket(AF_INET,SOCK_STREAM,0)) == SOCKET_ERROR) {
    INFO_SOCKETS("createActiveSocket,1");
    errno = WSAGetLastError();
    return -1;
  }
  DEBUG_SOCKETS(fprintf(output, "%d\n", sock));

  SET_TIMESTAMP(sock);

  /* And connect to the server */
  memset((char *)&addr,0,sizeof(addr)); /* instead of bzero */
  addr.sin_family = AF_INET;
  addr.sin_port = htons((unsigned short)port);
  addr.sin_addr.s_addr = htonl(inetAddr);

  if(connect(sock,(struct SOCKADDR_type*)&addr,sizeof(addr))) {
    INFO_SOCKETS("createActiveSocket,2");
    errno = WSAGetLastError();
    return -1;
  }

  if (nonblock) {
    if (ioctlsocket(sock, FIONBIO, (unsigned long*)&nonblock)) {
      INFO_SOCKETS("createActiveSocket,3");
      errno = WSAGetLastError();
      return -1;
    }
  }

  if (setsockopt(sock, SOL_SOCKET, SO_KEEPALIVE, (char*)&on, sizeof(on))) {
    INFO_SOCKETS("createActiveSocket,4");
    errno = WSAGetLastError();
    return -1;
  }

  if (setsockopt(sock, SOL_SOCKET, SO_LINGER,
		 (char*)&li, sizeof(struct linger))) {
    INFO_SOCKETS("createActiveSocket,4.1");
    errno = WSAGetLastError();
    return -1;
  }

#else /* Not nti */

  if((sock=socket(AF_INET,SOCK_STREAM,0))<0) {
    INFO_SOCKETS("createActiveSocket,1");
    return -1;
  }
  DEBUG_SOCKETS(fprintf(output, "%d\n", sock));

  SET_TIMESTAMP(sock);

  /* And connect to the server */
  memset((char *)&addr,0,sizeof(addr)); /* instead of bzero */
  addr.sin_family=AF_INET;
  addr.sin_port=htons((unsigned short)port);
  addr.sin_addr.s_addr=htonl(inetAddr);

  if(connect(sock,(struct SOCKADDR_type*)&addr,sizeof(addr))<0) {
    INFO_SOCKETS("createActiveSocket,2");
    return -1;
  }

  if (nonblock) {
    if (0 > fcntl(sock, F_SETFL, O_NONBLOCK)) {
      INFO_SOCKETS("createActiveSocket,3");
      return -1;
    }
  }

  if (0 > setsockopt(sock, SOL_SOCKET, SO_KEEPALIVE, (char*)&on, sizeof(on))) {
    INFO_SOCKETS("createActiveSocket,4");
    return -1;
  }

  if (setsockopt(sock, SOL_SOCKET, SO_LINGER,
		 (char*)&li, sizeof(struct linger))) {
    INFO_SOCKETS("createActiveSocket,4.1");
    return -1;
  }
#endif

  /* Connection is now established and the descriptor is in sock */
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
 * (*port).
 *
 * args
 *   port: pointer to port number to bind socket to
 *
 * return value
 *   normally: file descriptor for the new passive socket
 *   in case of error: -1
 */
int createPassiveSocket(long *port, int nonblock)
{
  unsigned long on = 1;
  struct sockaddr_in sockaddr;
  int listenSock;
  int size;
  struct linger li;
  
  li.l_onoff=0;
  li.l_linger=0;

  /* Create a socket */
#ifdef nti
  if ((listenSock = socket(AF_INET,SOCK_STREAM,0)) == INVALID_SOCKET) {
    INFO_SOCKETS("createPassiveSocket,1");
    errno = WSAGetLastError();
    return -1;
  }

  SET_TIMESTAMP(listenSock);

  if (nonblock) {
    if (ioctlsocket(listenSock, FIONBIO, (unsigned long*)&nonblock)) {
      INFO_SOCKETS("createPassiveSocket,2");
      errno = WSAGetLastError();
      return -1;
    }
  }

  if (setsockopt(listenSock, SOL_SOCKET, SO_REUSEADDR, 
		 (char*)&on, sizeof(on))) {
    INFO_SOCKETS("createPassiveSocket,2a");
    errno = WSAGetLastError();
    return -1;
  }

  if (setsockopt(listenSock, SOL_SOCKET, SO_LINGER,
		 (char*)&li, sizeof(struct linger))) {
    INFO_SOCKETS("createPassiveSocket,2b");
    errno = WSAGetLastError();
    return -1;
  }
#else
  if (0>(listenSock=socket(AF_INET,SOCK_STREAM,0))) {
    INFO_SOCKETS("createPassiveSocket,1");
    return -1;
  }

  SET_TIMESTAMP(listenSock);

  if (nonblock) {
    if (0>fcntl(listenSock, F_SETFL, O_NDELAY)) {
      INFO_SOCKETS("createPassiveSocket,2");
      return -1;
    }
  }
  if (setsockopt(listenSock, SOL_SOCKET, SO_REUSEADDR,
		 (char*)&on, sizeof(on))) {
    INFO_SOCKETS("createPassiveSocket,2a");
    return -1;
  }

  if (setsockopt(listenSock, SOL_SOCKET, SO_LINGER,
		 (char*)&li, sizeof(struct linger))) {
    INFO_SOCKETS("createPassiveSocket,2b");
    return -1;
  }
#endif

  /* Bind the socket */
  memset((char *)&sockaddr,0,sizeof(sockaddr)); /* instead of bzero */
  sockaddr.sin_family = AF_INET;
  sockaddr.sin_port = htons((unsigned short)*port);
  sockaddr.sin_addr.s_addr = INADDR_ANY;

#ifdef nti
  if(bind(listenSock,(struct SOCKADDR_type*)&sockaddr,sizeof(sockaddr))) {
    INFO_SOCKETS("createPassiveSocket,3");
    errno = WSAGetLastError();
    return -1;
  }
#else
  if(0 > bind(listenSock,(struct SOCKADDR_type*)&sockaddr,sizeof(sockaddr))) {
    INFO_SOCKETS("createPassiveSocket,3");
    return -1;
  }
#endif

  /* If the port number was 0, we must lookup the randomly chosen no. */
  if (!*port) {
    size = sizeof(sockaddr);
    if (0 > getsockname(listenSock,(struct SOCKADDR_type*)&sockaddr,&size)) {
      INFO_SOCKETS("createPassiveSocket,4");
#ifdef nti
      errno = WSAGetLastError();
#endif
      return -1;
    }
    (*port) = ntohs(sockaddr.sin_port);
    DEBUG_SOCKETS(fprintf(output, "Passive was assigned port %d\n",(int)*port));
  }

  /* Ask OS to create client request queue with max 5 entries*/
  if (listen(listenSock,5)<0) {
    INFO_SOCKETS("createPassiveSocket,5");
#ifdef nti
    errno = WSAGetLastError();
#endif
    return -1;
  }

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
  int fromaddrlen = sizeof( struct SOCKADDR_type );
  unsigned long on = 1;
  struct linger li;
  
  li.l_onoff=0;
  li.l_linger=0;


  SET_TIMESTAMP(sock);

  *pBlocked=0;

  do 
  {
    newSock = accept(sock, &from, &fromaddrlen);
    
#ifdef nti
    if (newSock == INVALID_SOCKET) 
    {
      switch (WSAGetLastError()) 
      {
      case EINTR:		/* Interrupt during system call .. */
	continue;		/* .. simply restart it */
	
      case WSAEWOULDBLOCK:	/* not ready */
	*pBlocked=1;
	return 0;
	
      default:
	printf("acceptConn failed, WSAGetLastError=%d\n", WSAGetLastError());
	errno = WSAGetLastError();
	return -1;
      }
    }
#else
    if (newSock < 0)
    {
      switch (errno) 
      {
      case EINTR:		/* Interrupt during system call .. */
	continue;		/* .. simply restart it */
	
      case EWOULDBLOCK:	        /* not ready */
	*pBlocked=1;
	return 0;
	
      default:
	printf("acceptConn failed, errno=%d\n", errno);
	return -1;
      }
    }
#endif
  } while (0);
  
  /* Report internet address of peer */
  {
    struct sockaddr_in peer;
    int size = sizeof(peer);

    if (0 > getpeername(newSock,(struct SOCKADDR_type*)&peer,&size)) 
    {
      INFO_SOCKETS("acceptConn,2");
#ifdef nti
      errno = WSAGetLastError();
#endif
      return -1;
    }
    *pInetAddr=ntohl(peer.sin_addr.s_addr);
  }

  SET_TIMESTAMP(newSock);

#ifdef nti
  if (ioctlsocket(newSock, FIONBIO, (unsigned long*)&on)) {
    INFO_SOCKETS("acceptConn,3");
    errno = WSAGetLastError();
    return -1;
  }
  
  if (setsockopt(newSock, SOL_SOCKET, SO_KEEPALIVE, (char*)&on, sizeof(on))) {
    INFO_SOCKETS("acceptConn,4");
    errno = WSAGetLastError();
    return -1;
  }

  if (setsockopt(newSock, SOL_SOCKET, SO_LINGER,
		 (char*)&li, sizeof(struct linger))) {
    INFO_SOCKETS("acceptConn,4.1");
    errno = WSAGetLastError();
    return -1;
  }
#else
  if (0 > fcntl(newSock, F_SETFL, O_NONBLOCK)) {
    INFO_SOCKETS("acceptConn,3");
    return -1;
  }

  if (0>setsockopt(newSock, SOL_SOCKET, SO_KEEPALIVE, (char*)&on, sizeof(on))){
    INFO_SOCKETS("acceptConn,4");
    return -1;
  }

  if (setsockopt(newSock, SOL_SOCKET, SO_LINGER,
		 (char*)&li, sizeof(struct linger))) {
    INFO_SOCKETS("acceptConn,4.1");
    return -1;
  }
#endif

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

#ifdef nti
  if (ioctlsocket(fd, FIONREAD, (unsigned long*)&result)) 
#else
  if (0 > ioctl(fd, FIONREAD, (caddr_t)&result)) 
#endif
  {
    INFO_SOCKETS("sockToRead");
#ifdef nti
    errno = WSAGetLastError();
#endif
    return -1;
  }
  else
    return (result > MAXINT) ? MAXINT : (int)result;
}


/********************************************************************
 *                                                                  *
 * Setting up a new socket and closing it down                      *
 *                                                                  *
 ********************************************************************/


/* function 'closeSocket' closes a socket and 
 * updates local information about it.  To enable 
 * holding this information up-to-date, please
 * call this function instead of calling close()
 * directly. 
 *
 * args
 *   fd: file descriptor for the socket
 *
 * return value
 *   when successful: 0
 *   in case of error: -1
 */
int closeSocket(int fd)
{
  SET_TIMESTAMP(fd);

  DEBUG_SOCKETS(fprintf(output, "CloseSocket(%d)\n", fd));

#ifdef nti
  if (closesocket(fd))
  {
    INFO_SOCKETS("closeSocket");
#ifdef RTDEBUG
    printf("Closesocket failed with WSAGetLastError=%d\n", WSAGetLastError());
#endif
    errno = WSAGetLastError();
    return -1;
  }
#else
  if (0 > close(fd)) 
  {
    INFO_SOCKETS("closeSocket");
    return -1;
  }
#endif

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
  
  do 
  {

    received = recv(fd, destbuffer, buflen, 0);
#ifdef nti
    switch (received)
    {
    case SOCKET_ERROR:			/* ERROR */
      switch (WSAGetLastError()) 
      {
      case WSAEWOULDBLOCK:
      INFO_SOCKETS("readDataMax: WSAEWOULDBLOCK");
	return 0;

      case EINTR:		/* Interrupted, just restart */
	continue;
      
      default:
	INFO_SOCKETS("readDataMax,1");
	errno = WSAGetLastError();
	return -1;
      }
    
    case 0:
      /* No data available and not WOULDBLOCK: comm.partner closed down */
      INFO_SOCKETS("other party closed down; readDataMax,2");
      errno = WSAENOTCONN;
      return -1;
    
    default:
      break;
    }
#else
    switch (received)
    {
    case -1:			/* ERROR */
      switch (errno)
      {
      case ERR_WOULDBLOCK: /* No data available */
	return 0;
      
      case EINTR:		/* Interrupted, just restart */
	continue;
      
      default:
	INFO_SOCKETS("readDataMax,1");
	return -1;
      }
      break;
    
    case 0:
      /* No data available and not WOULDBLOCK: comm.partner closed down */
      INFO_SOCKETS("other party closed down; readDataMax,2");
      errno = ENOTCONN;
      return -1;
    
    default:
      break;
    }
#endif
  } while(0);


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

  do
  {
    sent = send(fd, srcbuffer, length, 0);
  
#ifdef nti
    if (sent == -1)
    {
      switch (WSAGetLastError()) 
      {
      case WSAEWOULDBLOCK:
	INFO_SOCKETS("writeDataMax: WSAEWOULDBLOCK");
	return 0;

      case EINTR:		/* Interrupt, just restart */
	continue;
      
      default:
	INFO_SOCKETS("writeDataMax");
	errno = WSAGetLastError();   /* betacode uses this */
	return -1;
      }
    }
    else 
    {
    }
#else
    if (sent < 0)
    {
      switch (errno) 
      {
      case ERR_WOULDBLOCK:	/* Buffer full */
	return 0;
      
      case EINTR:		/* Interrupt, just restart */
	continue;
      
      default:
	INFO_SOCKETS("writeDataMax");
	return -1;
      }
    }
    else 
    {
    }
#endif
  } while(0);
  
  return sent;
}

int doshutdown(int fd, int how)
{
  return shutdown(fd, how);
}
