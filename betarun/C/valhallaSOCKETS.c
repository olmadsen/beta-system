#ifdef RTVALHALLA /* Only relevant in valhalla specific runtime system. */
/* ------------------------- FILE valhallaSOCKETS.c ------------------------- */

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
#include <sys/time.h>		

/********************************************************************
 *                                                                  *
 * Utility functions for IP addresses etc.                          *
 *                                                                  *
 ********************************************************************/


unsigned long
valhalla_inetAddrOfThisHost(void)
{
  static int inetAddrOfThisHostCached=0;
  static unsigned long inetAddrOfThisHostCache;

  if (!inetAddrOfThisHostCached) {
    struct hostent *pHostInfo=gethostbyname("localhost");

    if (!pHostInfo) {
      return -1;
    }
    inetAddrOfThisHostCache = *(unsigned long *)(*pHostInfo->h_addr_list);
    inetAddrOfThisHostCached=1;
  }
  return inetAddrOfThisHostCache;
}


/********************************************************************
 *                                                                  *
 * Support for active socket                                        *
 *                                                                  *
 ********************************************************************/


int valhalla_openActiveSocket(unsigned long inetAddr, long port)
{
  struct sockaddr_in addr;
  int sock;

  /* Create a socket */
  if((sock=socket(AF_INET,SOCK_STREAM,0))<0) {
    return -1;
  }

  /* And connect to the server */
  memset((char *)&addr,0,sizeof(addr)); /* instead of bzero */
  addr.sin_family=AF_INET;
  addr.sin_port=(int)port;
  addr.sin_addr.s_addr=inetAddr;

  if(connect(sock,(struct sockaddr*)&addr,sizeof(addr))<0) {
    return -1;
  }

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
 * (*port). The internet address (225.130.16.214 style value
 * as an unsigned long integer) for this passiveSocket (i.e.
 * this host) is returned in (*pInetAddr), iff the operation
 * succeeds.
 *
 * args
 *   port: pointer to port number to bind socket to
 *
 * return value
 *   normally: file descriptor for the new passive socket
 *   in case of error: -1
 */
int valhalla_createPassiveSocket(long *port)
{
  struct sockaddr_in sockaddr;
  int listenSock;
  int size;

  /* Create a socket */
  if (0>(listenSock=socket(AF_INET,SOCK_STREAM,0))) {
    return -1;
  }

  /* Bind the socket */
  memset((char *)&sockaddr,0,sizeof(sockaddr)); /* instead of bzero */
  sockaddr.sin_family=AF_INET;
  sockaddr.sin_port=(int)*port;
  sockaddr.sin_addr.s_addr=INADDR_ANY;
  if(0>bind(listenSock,(struct sockaddr*)&sockaddr,sizeof(sockaddr))) {
    return -1;
  }

  /* If the port number was 0, we must lookup the randomly chosen no. */
  if (!*port) {
    size = sizeof(sockaddr);
    if (0>getsockname(listenSock,(struct sockaddr*)&sockaddr,&size)) {
      return -1;
    }
    (*port) = sockaddr.sin_port;
  }

  /* Ask OS to create client request queue */
  if (listen(listenSock,5)<0) {
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
int valhalla_acceptConn(int sock, int *pBlocked, unsigned long *pInetAddr)
{
  int newSock;
  struct sockaddr from;
  int fromaddrlen=sizeof( struct sockaddr );

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
	return -1;
      }
    }
  } while (0);

  /* Report internet address of peer */
  {
    struct sockaddr_in peer;
    int size = sizeof(peer);

    if (0>getpeername(newSock,(struct sockaddr*)&peer,&size)) {
      return -1;
    }
    *pInetAddr=peer.sin_addr.s_addr;
  }

  return newSock;
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
int valhalla_readDataMax(int fd, char *destbuffer, int buflen)
{
  int received;

  do {
    switch (received=read(fd,destbuffer,buflen)) {
    case -1:			/* ERROR */
      switch (errno) {
      case EINTR:		/* Interrupted, just restart */
	continue;
      default:
	return -1;
      }
      break;

    case 0:
      /* No data available and not WOULDBLOCK: comm.partner closed down */
      errno=ENOTCONN;
      return -1;

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
int valhalla_writeDataMax(int fd, char *srcbuffer, int length)
{
  int sent;

  do {
    if (0 > (sent=write(fd,srcbuffer,length)))
      switch (errno) {
      case EINTR:		/* Interrupt, just restart */
	continue;
      default:
	return -1;
      }
  } while (0);

  return sent;
}

/* ------------------------- END sockets.c ------------------------- */
#endif /* RTVALHALLA */
