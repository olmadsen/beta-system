#ifdef RTVALHALLA /* Only relevant in valhalla specific runtime system. */
#ifndef VALHALLASOCKETS_H
#define VALHALLASOCKETS_H

/* FIXME: Should be eliminated altogether, as they are just
 * wrappers for functions in sockets.c
 */

int valhalla_openActiveSocket(unsigned long inetAddr, long port);
int valhalla_writeDataMax(int fd, char *srcbuffer, int length);
int valhalla_readDataMax(int fd, char *destbuffer, int buflen);
unsigned long valhalla_inetAddrOfThisHost(void);
int valhalla_acceptConn(int sock, int *pBlocked, unsigned long *pInetAddr);
int valhalla_createPassiveSocket(long *port, unsigned long *pInetAddr);
void valhalla_initSockets(void);

#endif /* VALHALLASOCKETS_H */
#endif /* RTVALHALLA */
