#include "beta.h"
#ifdef RTVALHALLA /* Only relevant in valhalla specific runtime system. */


void valhalla_initSockets(void) {
  initSockets();
}

unsigned long valhalla_inetAddrOfThisHost(void)
{
  unsigned long ip;
  ip = inetAddrOfThisHost();
#ifndef hpux /* fuck hpux9pa: the following makes compiler crash */
  DEBUG_VALHALLA(char * name = (char *)(&ip);
		 fprintf(output,"valhalla_inetAddrOfThisHost: %d.%d.%d.%d\n",
			 (unsigned)name[0],
			 (unsigned)name[1],
			 (unsigned)name[2],
			 (unsigned)name[3]
			 );
		 fflush(output));
#endif
  return  ip;
}

int valhalla_openActiveSocket(unsigned long inetAddr, long port)
{
  return createActiveSocket(inetAddr, port, 0);
}

int valhalla_createPassiveSocket(long *port)
{
  return createPassiveSocket(port, 0);
}


int valhalla_acceptConn(int sock, int *pBlocked, unsigned long *pInetAddr)
{
  return acceptConn(sock, pBlocked, pInetAddr);
}

int valhalla_readDataMax(int fd, char *destbuffer, int buflen)
{
  return readDataMax(fd, destbuffer, buflen);
}

int valhalla_writeDataMax(int fd, char *srcbuffer, int length)
{
  return writeDataMax(fd, srcbuffer, length);
}

/* ------------------------- END sockets.c ------------------------- */
#endif /* RTVALHALLA */
