/* ------------------------- FILE sockets.c ------------------------- */

/*
 * COPYRIGHT
 *       Copyright Mjolner Informatics, 1994-95
 *       All rights reserved.
 */


/*******************
 *                 *
 * Common includes *
 *                 *
 *******************/


#include <string.h>
#include <errno.h>
#include <stdio.h>		/* to see FILE */
#include "sockSignals.h"


#ifdef nti
#  include <winsock.h> 
#  include <limits.h>
#else
#  define SUPPORT_TIMESTAMPING
#  include <fcntl.h>
#  include <unistd.h>
#  include <netdb.h>		/* to see struct hostent */
#  include <netinet/in.h>
#  include <values.h>		/* to see MAXINT */
#  include <sys/socket.h>         /* to see SOL_SOCKET, SO_TYPE */
#  include <sys/param.h>		/* to see NOFILE */
#  include <sys/time.h>		/* to see struct timeval */
#  include <sys/types.h>
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
#      ifdef nti
#      else
#        error ARCH_UNKNOWN
#      endif
#    endif
#  endif
#endif


/* Architecture dependant types/values */

#if defined(A_SUN) || defined(A_SGI)
#  define HPFD_cast
#else
#  if defined(A_HP)
#    define HPFD_cast (int*)
#  else
#    if defined(A_LINUX)
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

#if defined(A_SUN34)
#  define SIGNALPARM void
#else
#  if defined(A_HP) || defined(A_SUN4S) || defined(A_SGI)
#    define SIGNALPARM int ignore
#  else
#    if defined(A_LINUX)
#      define SIGNALPARM int ignore
#    else
#      ifdef nti
#      else
#        error ARCH_UNKNOWN
#      endif
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
#      ifdef nti
#        define SOCKADDR_type sockaddr
#      else
#        error ARCH_UNKNOWN
#      endif
#    endif
#  endif
#endif

#if defined(A_SUN4S)
#  define ERR_WOULDBLOCK EWOULDBLOCK
#else
#  define ERR_WOULDBLOCK EAGAIN
#endif


#ifdef nti
#  define MAXHOSTNAMELEN 256 /* Value from fraxinus:'man gethostname' */
#  define MAXINT INT_MAX
#endif
/********************************************************************
 *                                                                  *
 * DEBUGGING #defines:                                              *
 * Define any of these to invoke behaviour suitable for debugging   *
 * certain aspects of communication/signal handling.                *
 *                                                                  *
 ********************************************************************/


/* A readable and not too long filespec, for debug(gish) output */
#define FILE_ID "process/v1.5/.../sockets.c"

#define DO_ECHO_ERROR(x) printf(x);
#define DO_ECHO_ACTION(x) printf(x);
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
#  ifndef nti
#    define min(a,b) ((a)<(b)? (a):(b))
#  endif
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
#if defined(A_NT)

static void 
StopWSA(void)
{
  ECHO_USER_ERROR("WSACleanup");
  /*  Sleep(500); */
  WSACleanup();
}

static void
StartWSA(void)
{
  WSADATA wsadata;

  ECHO_USER_ERROR("WSAStartup");
  if (WSAStartup(MAKEWORD(1,1), &wsadata) == 0) {
    atexit(StopWSA);
  } else {
    ECHO_USER_ERROR("WSAStartup failed");
    exit(1);
  }
}

# define START_WSA() StartWSA()
#else
# define START_WSA()
#endif

void initSockets(void)
{
  static initialized=0;

  if (!initialized) {
    initialized = 1;
    INIT_TIMESTAMP();
    START_WSA();
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
  int dummy_len = sizeof(dummy);

  int res = getsockopt(fd, SOL_SOCKET, SO_TYPE, (char*)&dummy, &dummy_len);

#ifdef nti
  if (res) 
  {
    RESET_TIMESTAMP(fd);
    errno = WSAENOTSOCK;
    return 0;
  }
#else
  if (0 > res) 
  {
    RESET_TIMESTAMP(fd);
    errno = ENOTSOCK;		/* ANY error means 'Not a socket' */
    return 0;
  }
#endif

  SET_TIMESTAMP(fd);
  return 1;
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
  static struct fd_set read_mask,write_mask,error_mask;
  static struct timeval timeout = {0,0};
  long result;
  int err,err_size = sizeof(err);

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
			   &timeout))) 
    {
      SHOW_SELECT("       (error)",&read_mask,&write_mask,&error_mask);
#ifdef nti
    errno = WSAGetLastError();
#endif
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
  static struct fd_set read_mask,write_mask,error_mask;
  static struct timeval timeout = {0,0};
  struct timeval *ptm;
  long result;
  int err,err_size=sizeof(err);

#ifdef nti
  printf("doBlock called! You should not block this way! (doing it anyway...\n)");
#endif

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
			   ptm))) 
    {
      SHOW_SELECT("       (error)",&read_mask,&write_mask,&error_mask);
#ifdef nti
    errno = WSAGetLastError();
#endif
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
unsigned long host2inetAddr(char *host)
{
  struct hostent *pHostInfo=gethostbyname(host);

  if (!pHostInfo) {
    ECHO_ERROR("host2inetAddr");
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
    struct hostent *pHostInfo;

    if (0 > gethostname(nameOfThisHostCache,MAXHOSTNAMELEN)) {
      ECHO_ERROR("nameOfThisHost");
#ifdef nti
      errno = WSAGetLastError();
#endif
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
unsigned long inetAddrOfThisHost(void)
{
  static int inetAddrOfThisHostCached=0;
  static unsigned long inetAddrOfThisHostCache;
  long errorCode;

  if (!inetAddrOfThisHostCached) {
    struct hostent *pHostInfo=gethostbyname(nameOfThisHost(&errorCode));

    if (!pHostInfo) {
      ECHO_ERROR("inetAddrOfThisHost");
#ifdef nti
      errno = WSAGetLastError();
#endif
      return -1;
    }
    if (0 > errorCode) {
      /* no ECHO_ERROR here: has already been reported */
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

int createActiveSocket(unsigned long inetAddr, long port)
{
  int on = 1;
  unsigned long NonBlock = 1;
  struct sockaddr_in addr;
  int sock;

  SET_TIMESTAMP(sock);

  /* Create a socket */
#ifdef nti
  if((sock = socket(AF_INET,SOCK_STREAM,0)) == SOCKET_ERROR) {
    ECHO_ERROR("createActiveSocket,1");
    errno = WSAGetLastError();
    return -1;
  }
  ECHO_ACTION_INT("opened active socket on port",sock,port);

  /* And connect to the server */
  memset((char *)&addr,0,sizeof(addr)); /* instead of bzero */
  addr.sin_family = AF_INET;
  addr.sin_port = htons((unsigned short)port);
  addr.sin_addr.s_addr = htonl(inetAddr);

  if(connect(sock,(struct SOCKADDR_type*)&addr,sizeof(addr))) {
    ECHO_ERROR("createActiveSocket,2");
    errno = WSAGetLastError();
    return -1;
  }

  if (ioctlsocket(sock, FIONBIO, &NonBlock)) {
    ECHO_ERROR("createActiveSocket,3");
    errno = WSAGetLastError();
    return -1;
  }

  if (setsockopt(sock, SOL_SOCKET, SO_KEEPALIVE, (char*)&on, sizeof(on))) {
    ECHO_ERROR("createActiveSocket,4");
    errno = WSAGetLastError();
    return -1;
  }

#else /* Not nti */

  if((sock=socket(AF_INET,SOCK_STREAM,0))<0) {
    ECHO_ERROR("createActiveSocket,1");
    return -1;
  }
  ECHO_ACTION_INT("opened active socket on port",sock,port);

  /* And connect to the server */
  memset((char *)&addr,0,sizeof(addr)); /* instead of bzero */
  addr.sin_family=AF_INET;
  addr.sin_port=htons((unsigned short)port);
  addr.sin_addr.s_addr=htonl(inetAddr);

  if(connect(sock,(struct SOCKADDR_type*)&addr,sizeof(addr))<0) {
    ECHO_ERROR("createActiveSocket,2");
    return -1;
  }

  if (0 > fcntl(sock, F_SETFL, O_NONBLOCK)) {
    ECHO_ERROR("createActiveSocket,3");
    return -1;
  }

  if (0 > setsockopt(sock, SOL_SOCKET, SO_KEEPALIVE, (char*)&on, sizeof(on))) {
    ECHO_ERROR("createActiveSocket,4");
    return -1;
  }
#endif

  /* Connection is now established and the descriptor is in sock */
  ECHO_ACTION_IP("established connection to",sock,inetAddr);
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
int createPassiveSocket(long *port)
{
  unsigned long NonBlock = 1;
  unsigned long on = 1;
  struct sockaddr_in sockaddr;
  int listenSock;
  int size;

  SET_TIMESTAMP(listenSock);

  /* Create a socket */
#ifdef nti
  if ((listenSock = socket(AF_INET,SOCK_STREAM,0)) == INVALID_SOCKET) {
    ECHO_ERROR("createPassiveSocket,1");
    errno = WSAGetLastError();
    return -1;
  }
  if (ioctlsocket(listenSock, FIONBIO, &NonBlock)) {
    ECHO_ERROR("createPassiveSocket,2");
    errno = WSAGetLastError();
    return -1;
  }
  if (setsockopt(listenSock, SOL_SOCKET, SO_REUSEADDR, 
		 (char*)&on, sizeof(on))) {
    ECHO_ERROR("createPassiveSocket,2a");
    errno = WSAGetLastError();
    return -1;
  }
#else
  if (0>(listenSock=socket(AF_INET,SOCK_STREAM,0))) {
    ECHO_ERROR("createPassiveSocket,1");
    return -1;
  }
  if (0>fcntl(listenSock, F_SETFL, O_NDELAY)) {
    ECHO_ERROR("createPassiveSocket,2");
    return -1;
  }
  if (setsockopt(listenSock, SOL_SOCKET, SO_REUSEADDR,
		 (char*)&on, sizeof(on))) {
    ECHO_ERROR("createPassiveSocket,2a");
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
    ECHO_ERROR("createPassiveSocket,3");
    errno = WSAGetLastError();
    return -1;
  }
#else
  if(0 > bind(listenSock,(struct SOCKADDR_type*)&sockaddr,sizeof(sockaddr))) {
    ECHO_ERROR("createPassiveSocket,3");
    return -1;
  }
#endif

  /* If the port number was 0, we must lookup the randomly chosen no. */
  if (!*port) {
    size = sizeof(sockaddr);
    if (0 > getsockname(listenSock,(struct SOCKADDR_type*)&sockaddr,&size)) {
      ECHO_ERROR("createPassiveSocket,4");
#ifdef nti
      errno = WSAGetLastError();
#endif
      return -1;
    }
    (*port) = ntohs(sockaddr.sin_port);
  }

  /* Ask OS to create client request queue */
  if (listen(listenSock,5)<0) {
    ECHO_ERROR("createPassiveSocket,5");
#ifdef nti
    errno = WSAGetLastError();
#endif
    return -1;
  }

  ECHO_ACTION_INT("created passive socket on port",listenSock,*port);
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
  
  ECHO_ACTION_INT("accepted new connection on fd",sock,newSock);

  /* Report internet address of peer */
  {
    struct sockaddr_in peer;
    int size = sizeof(peer);

    if (0 > getpeername(newSock,(struct SOCKADDR_type*)&peer,&size)) 
    {
      ECHO_ERROR("acceptConn,2");
#ifdef nti
      errno = WSAGetLastError();
#endif
      return -1;
    }
    *pInetAddr=ntohl(peer.sin_addr.s_addr);
  }

  SET_TIMESTAMP(newSock);

  ECHO_ACTION_IP("connected to",newSock,*pInetAddr);
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
  if (ioctlsocket(fd, FIONREAD, &result)) 
#else
  if (0 > ioctl(fd, FIONREAD, (caddr_t)&result)) 
#endif
  {
    ECHO_ERROR("sockToRead");
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

#ifdef nti
  if (closesocket(fd))
  {
    ECHO_ERROR("closeSocket");
    printf("Closesocket failed with WSAGetLastError=%d\n", WSAGetLastError());
    errno = WSAGetLastError();
    return -1;
  }
#else
  if (0 > close(fd)) 
  {
    ECHO_ERROR("closeSocket");
    return -1;
  }
#endif

  ECHO_ACTION("closed socket", fd);
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
    case -1:			/* ERROR */
      switch (WSAGetLastError()) 
      {
      case WSAEWOULDBLOCK:
	return 0;

      case EINTR:		/* Interrupted, just restart */
	continue;
      
      default:
	ECHO_USER_ERROR("readDataMax,1");
	errno = WSAGetLastError();
	return -1;
      }
      break;
    
    case 0:
      /* No data available and not WOULDBLOCK: comm.partner closed down */
      ECHO_USER_ERROR("other party closed down; readDataMax,2");
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
	ECHO_USER_ERROR("readDataMax,1");
	return -1;
      }
      break;
    
    case 0:
      /* No data available and not WOULDBLOCK: comm.partner closed down */
      ECHO_USER_ERROR("other party closed down; readDataMax,2");
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
	return 0;

      case EINTR:		/* Interrupt, just restart */
	continue;
      
      default:
	ECHO_ERROR("writeDataMax");
	errno = WSAGetLastError();   /* betacode uses this */
	return -1;
      }
    }
    else 
    {
      ECHO_TRANSFER("wrote",fd,srcbuffer,sent,length);
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
	ECHO_ERROR("writeDataMax");
	return -1;
      }
    }
    else 
    {
      ECHO_TRANSFER("wrote",fd,srcbuffer,sent,length);
    }
#endif
  } while(0);
  
  return sent;
}




/* ------------------------- END sockets.c ------------------------- */
