#include "beta.h"
#ifdef RTVALHALLA /* Only relevant in valhalla specific runtime system. */

void valhalla_initSockets(void) {
  initSockets();
}

unsigned long valhalla_inetAddrOfThisHost(void)
{
  unsigned long ip;
  ip = 0x7f000001; /* inetAddrOfThisHost() makes win95 do dialup */
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
#ifdef MAC
  int recieved = 0;
  int count = 0;
  	
  	DEBUG_VALHALLA(fprintf(output, "Read data %d\n", buflen));

  while(count < buflen) {
  	recieved = readDataMax(fd, destbuffer + count, buflen - count);
  	DEBUG_VALHALLA(fprintf(output, "recieved %d\n", recieved));
  	if (recieved == -1) {
  		return -1;
  	}
  	else {
  		count += recieved;
  	}
  	GiveTime();
  }
  return count;
#else
   return readDataMax(fd, destbuffer, buflen);
#endif /* MAC */
}

int valhalla_writeDataMax(int fd, char *srcbuffer, int length)
{
  int res;
  DEBUG_VALHALLA(fprintf(output, "valhalla_writeDataMax: fd=%d\n", (int)fd));
  res = writeDataMax(fd, srcbuffer, length);
  DEBUG_VALHALLA(fprintf(output, "valhalla_writeDataMax: res=%d\n", res));
  return res;
}

#endif /* RTVALHALLA */
