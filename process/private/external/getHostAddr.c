#include <stdio.h>
#ifndef nti
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <sys/param.h>
#else
#include <winsock.h>
#include <malloc.h>
#define MAXHOSTNAMELEN 256
#endif

char *getHostAddr()
{ char buffer[MAXHOSTNAMELEN];
  struct hostent *hostInfo;
  char *ip;
  unsigned char *cp;

  if(gethostname(buffer,MAXHOSTNAMELEN)<0)
    return NULL;
  if((hostInfo=gethostbyname(buffer)) == NULL)
    return NULL;
  cp = (unsigned char *) hostInfo->h_addr;
  ip = (char *)malloc(16);
  sprintf(ip, "%d.%d.%d.%d", cp[0], cp[1], cp[2], cp[3]);
  return ip;
}


