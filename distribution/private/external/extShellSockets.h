/*
 * File shellSockets.h
 * ===================
 */


#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h> /* For hostent struct */



void initSignals ();
/* Initializes socket specific signal handling for the Shell. */



int newPassiveSocket (int *portNumber);
/* Returns a new passive socket on which to listen for remote calls using 
 * 'tryAccept'. Upon return, portNumber contains the portNumber of the newly 
 * created socket. If portNumber is initially zero, newPassiveSocket selects
 * a new portNumber. Otherwise it tries to use portNumber.
 * ErrorCodes returned:
 *    -1: Unable to create new socket.
 *    -2: Unable to bind socket.
 *    -3: Unable to listen on socket.
 */



int newActiveSocket (int hostAdr, int port, int *newSock, int block);
/* Returns a new active socket connected to the port and host specified as
 * parameters. hostAdr is the internet address of the host to contact.
 * If block is FALSE, the new socket will be marked as nonblocking.
 * ErrorCodes returned:
 *     0: Ok (ready)
 *    -1: Unable to create new socket.
 *    -2: Unable to mark socket as nonblocking.
 *    -3: Connection in progress (if not block). EINTR (if block)
 *    -4: Unable to connect to server.
 */



int tryAccept (int sock, int blocking, int acceptBlock);
/* Checks whether a connection is pending on sock, and in that case
 * returns a socket for handling the new connection. sock should 
 * have been created using 'newPassiveSocket'. Information of the
 * client wanting the connection is available, but is currently
 * not returned.
 * If blocking is TRUE, tryAccept will only return if a connection
 * was accepted. If blocking is FALSE, tryAccept checks whether a connection
 * was ready and returns immediately in any case.
 * If acceptBlock if FALSE, the accepted socket will be marked as nonblocking.
 * ErrorCodes returned:
 *    -1: No connection pending.
 *    -2: Unable to mark accepted socket as nonblocking.
 *    -2: Some other error occurred. (Check errorno)
 */  



int nbReadn (int sock, char* ptr, int nbytes);
/* Reads at most n bytes from nonblocking socket.  
 *
 * Return values:
 *  =0: Nothing to read yet.
 *  >0: Number of bytes actually read.
 *  -1: An error occurred (other than EWOULDBLOCK, EINTR)
 *  -2: Connection broken.
 */

int nbWriten (int sock, char* ptr, int nbytes);
/* Writes at most n bytes to nonblocking socket.
 *
 * Return values:
 *   >=0: Number of bytes actually written.
 *    -1: An error occurred (other than EWOULDBLOCK, EINTR)
 */



int bReadn (int sock, char* ptr, int nbytes);
/* Read n bytes from blocking socket. 
 * Returns 0 if ok and a negative number otherwise.
 */

int bWriten (int sock, char* ptr, int nbytes);
/* Write n bytes to blocking socket. 
 * Returns 0 if ok and a negative number otherwise.
 */
