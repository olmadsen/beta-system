/*
 * File extShellSockets.c
 * ======================
 */

#ifndef linux
#define FD_SETSIZE 32
#endif

#include "extShellSockets.h"

#include <sys/types.h>
#include <sys/socket.h>
#include <sys/file.h>
#include <sys/time.h>
#include <netinet/in.h>
#include <errno.h>
#include <stdio.h>
/*#include <sys/filio.h>*/
#include <fcntl.h>
#include <signal.h>
#include <errno.h>

#ifndef FALSE
#define FALSE 0
#define TRUE 1
#endif

/*
#ifdef sun4
static int one = 1;
#endif
*/

void 
onSIGPIPE ()
{
  /* Right now no action is taken. An appropriate way of handling the
   * SIGPIPE signal would probably be to find the offending SocketStream
   * and perform a callback resulting in a Beta exception being raised.
   * This is not trivial however, as the BetaStackTop variable must be
   * set before a callback to Beta. 
   * (See '~sbrandt/beta/objectserver/lazyfetch/trapHandler.c')
   */
  /* printf ("SIGPIPE caught\n"); */
  signal(SIGPIPE,onSIGPIPE);
};




void 
initSignals ()
{
  /* SIGPIPE is raised if someone tries to write on a broken stream. */
  signal(SIGPIPE,onSIGPIPE);
}




int 
newPassiveSocket (int *portNumber)
{ 
  struct sockaddr_in si; /* from <netinet/in.h> */
  int siSize;

  /* Create new Internet domain stream socket. (Connection oriented) */
  int newSock = socket (AF_INET, SOCK_STREAM, 0);
  if (newSock == -1) return -1;

  memset((char *)&si, 0, sizeof(si)); /* clear si */
  si.sin_family = AF_INET;
  si.sin_port = *portNumber; 
  /* If portNumber == 0, the system decides on a port number to use. */
  si.sin_addr.s_addr = INADDR_ANY;

  if (bind (newSock, (struct sockaddr *) &si, sizeof (si)) == -1) return -2;

  /* Get the port number assigned to newSock. */
  siSize = sizeof (si);
  if (getsockname (newSock, (struct sockaddr *) &si, &siSize) == -1) return -2;
  (*portNumber) = si.sin_port;
  
  /* Start listening on the socket: */
  if (listen (newSock, 5) == -1) return -3;
  
  return newSock;
}




 
int
newActiveSocket (int hostAdr, int port, int *newSock, int block)
{ struct sockaddr_in si; /* from <netinet/in.h> */

  /* Create new Internet domain stream socket. (Connection oriented) */
  *newSock = socket (AF_INET, SOCK_STREAM, 0);
  if (*newSock == -1) return -1;

  if (!block)
#ifdef sun4
    /* ioctl (*newSock, FIONBIO, &one); */
    if (fcntl (*newSock, F_SETFL, O_NDELAY) == -1) return -2;
#else
    /* Mark newSock as non-blocking. */
    if (fcntl (*newSock, F_SETFL, O_NONBLOCK) == -1) return -2;
#endif

  memset((char *)&si, 0, sizeof(si)); /* clear si */
  si.sin_family = AF_INET;
  si.sin_port = port; 
  si.sin_addr.s_addr = hostAdr;
    
  /* Now connect to server. */
  while (TRUE) {
    if (connect (*newSock, (struct sockaddr *) &si, sizeof(si)) == -1) {
      /* printf ("newActiveSocket errno: %d\n", errno); */
      if (block)
	if (errno == EINTR); /* Try again */ else return -4; /* Error */
      else
	if ((errno == EINPROGRESS) || (errno == EINTR))
	  return -3; /* The connection is in progress. */
	else 
	  return -4; /* Error */
    }
    else
      return 0;
  }
}

#if defined(sun4s) || defined(linux)
#define CASTFDSET 
#else
#define CASTFDSET (int *)
#endif

int 
tryAccept (int sock, int blocking, int acceptBlock)
{ struct sockaddr_in from; /* from <netinet/in.h> */
  int fromSize, acceptSock;

  fd_set sockFDSET;
  struct timeval time;
  int ready;

  if (!blocking) {
    /* Use select to check whether an accept would block. */
    time.tv_sec = 0;
    time.tv_usec = 0;
    FD_ZERO (&sockFDSET);
    FD_SET (sock, &sockFDSET);
    ready = (select (sock + 1, CASTFDSET &sockFDSET, 0, 0, &time) == 1);
  }
  
  if (ready || blocking) {
    for (;;) {
      fromSize = sizeof (from);
      acceptSock = accept (sock, (struct sockaddr *) &from, &fromSize);
      if (acceptSock == -1) {
	if (errno != EINTR) return -3; 
	/* Interrupted system call. Try again. */
      } else {
	/* Connection pending. Mark acceptSock as non-blocking. */

        if (!acceptBlock)
#ifdef sun4
	  if (fcntl (acceptSock, F_SETFL, O_NDELAY) == -1) return -2;
	/* ioctl (acceptSock, FIONBIO, &one); */
#else
	  if (fcntl (acceptSock, F_SETFL, O_NONBLOCK) == -1) return -2;
#endif
	return acceptSock;
      }
    }
  }
  return -1; /* No connection pending */
}


int nbReadn (int sock, char* ptr, int nbytes)
{
  int nread;

  while (TRUE) {
    nread = recv (sock, ptr, nbytes, 0);
    if (nread < 0) {
      /* printf ("nbReadn errno: %d\n",errno); */
      switch (errno) {
#if !(defined(sun4s) || defined(linux) || defined(sgi))
      case EWOULDBLOCK: /* EWOULDBLOCK = EAGAIN on sun4s, linux, sgi */
#endif
      case ENOTCONN:
      case EAGAIN:
	return 0;
      case EINTR:
	break; /* Try again */
      default:
	return -1;
      }
    } else if (nread == 0)
      return -2; /* End of file => broken connection. */ 
    else
      return nread;
  }
}

int nbWriten (int sock, char* ptr, int nbytes)
{
  int nwritten;
  while (TRUE) {
    nwritten = send (sock, ptr, nbytes, 0);
    if (nwritten < 0) {
      /* printf ("nbWriten errno: %d\n",errno); */
      switch (errno) {
#if !(defined(sun4s) || defined(linux) || defined(sgi))
      case EWOULDBLOCK:
#endif
      case ENOTCONN:
      case ENOBUFS:
      case EAGAIN:
	return 0;
      case EINTR:
	break;
      default:
	return -1;
      }
    } else
      return nwritten;
  }
}



int bReadn (int sock, char* ptr, int nbytes)
{
  int nleft, nread;

  nleft = nbytes;
  while (nleft > 0) {
    nread = recv (sock, ptr, nleft, 0);
    if (nread < 0) 
      return nread;
    else if (nread == 0) 
      return -1;
    
    nleft -= nread;
    ptr += nread;
  }
  return 0;
}


int bWriten (int sock, char* ptr, int nbytes)
/* Write n bytes to blocking socket. */
{
  int nleft, nwritten;

  nleft = nbytes;
  while (nleft > 0) {
    nwritten = send (sock, ptr, nleft, 0);
    if (nwritten > 0) {
      nleft -= nwritten;
      ptr += nwritten;
    } else
      return -1; /* error */
  }
  return 0;
}


int getName (int adr)
{ return adr; };


struct hostent* thisHost ()
{ char host[100];

  if (gethostname (host, 100) == 0)
    return gethostbyname (host);
  else
    return NULL;
}
