#ifdef RTVALHALLA /* Only relevant in valhalla specific runtime system. */
#ifndef VALHALLASOCKETS_H
#define VALHALLASOCKETS_H

/* Declarations below are implemented in valhallaSOCKETS.c, which is a cut-down
 * version of ~beta/process/v1.4/private/external/sockets.c */

int valhalla_openActiveSocket(unsigned long inetAddr, long port);
int valhalla_writeDataMax(int fd, char *srcbuffer, int length);
int valhalla_readDataMax(int fd, char *destbuffer, int buflen);
unsigned long valhalla_inetAddrOfThisHost(void);
int valhalla_acceptConn(int sock, int *pBlocked, unsigned long *pInetAddr);
int valhalla_createPassiveSocket(long *port, unsigned long *pInetAddr);

#endif /* VALHALLASOCKETS_H */
#endif /* RTVALHALLA */
