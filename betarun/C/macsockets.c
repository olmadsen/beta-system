#include "beta.h"


#include <OpenTransport.h>
#include <OpenTptInternet.h>
#include <stdio.h>
#include <Memory.h>
#include <stdlib.h>
#include <Processes.h>
#include <Events.h>
#include <Windows.h>


typedef struct Socket {
	EndpointRef endpoint;
	Boolean 	readReady;
	Boolean		writeReady;
	Boolean		error;
	OTEventCode	eventcode;
} Socket;


typedef Socket *SocketRef;


#define kDefaultInternetServicesPath	((OTConfiguration*)-3)

enum {
	kOpen,
	kClosed
};

enum {
	kNoError,
	kUnknown,
	kDisconnect,
	kExpedited,
	kMemory,
	kInputOutput,
	kInternal,
	kHostUnreachable
};


static short 				gState = kClosed;
static InetSvcRef 			gServices = nil;
static OTEventCode 			gEventCode = 0;
static ProcessSerialNumber 	gThisProcess;
static long					gLastError = kNoError;

int selectSockets (int *readCandidates, 
                   int *writeCandidates, 
				   int *exceptCandidates, 
				   int sec, 
				   int usec);

void CloseDown (void);

static OSStatus InitializeOpenTransport (void);
 /* Makes sure that OpenTransport is initialized */


static OSStatus InitializeServices (void);


void MakeIPAddress (TNetbuf *outAddress, InetHost host, InetPort port);
/* Fills the TNetbuf structure with an address (IP + port).
 * The outAddress->buf field is allocated with NewPtrClear and must
 * be disposed later by DisposePtr
 */
 

OSStatus Bind (EndpointRef endpoint, InetHost host, InetPort port, OTQLen qlen);

OSStatus Connect (EndpointRef endpoint, InetHost host, InetPort port);


pascal void BetaNotifyProc (void*			inContextPtr,
							OTEventCode		inEventCode,
							OTResult		inResult,
							void*			inCookie);






void CloseDown (void)
{
	if (gState == kOpen) {
		if (gServices != nil) {
			OTCloseProvider(gServices);
			gServices = nil;
		}
		CloseOpenTransport();
		gState = kClosed;
	}
}

SocketRef MakeSocket(EndpointRef endpoint);


 static OSStatus InitializeOpenTransport (void)
 /* Makes sure that OpenTransport is initialized */
{
	OSStatus status = kOTNoError;
	OSErr error;
	
	
	if (gState != kOpen) {
		error = GetCurrentProcess(&gThisProcess);
		status = InitOpenTransport();
		if (status == kOTNoError) {
			gState = kOpen;
			atexit(CloseDown);
		}
	}
	
	return status;
}

static OSStatus InitializeServices (void)
{
	OSStatus 	status  = kOTNoError;
	
	if (gServices == nil) {
		gServices = OTOpenInternetServices(kDefaultInternetServicesPath, 0, &status);

		if (status != kOTNoError) {
			gServices = nil;
		}
	}
	return status;
}


void MakeIPAddress (TNetbuf *outAddress, InetHost host, InetPort port)
/* Fills the TNetbuf structure with an address (IP + port).
 * The outAddress->buf field is allocated with NewPtrClear and must
 * be disposed later by DisposePtr
 */
{
	InetAddress* inAddr = nil;
	inAddr = (InetAddress*) malloc(sizeof (InetAddress));

	inAddr->fAddressType = AF_INET;
	inAddr->fPort = port;
	inAddr->fHost = host;
	
	outAddress->maxlen = outAddress->len = sizeof (InetAddress);
	outAddress->buf = (UInt8*) inAddr;
}

OSStatus Bind (EndpointRef endpoint, InetHost host, InetPort port, OTQLen qlen)
{
	OSStatus	status;
	TBind     	req;
	long		before, after;
	
	MakeIPAddress(&req.addr, host, port);
	req.qlen = qlen;
	before = TickCount();
	status = OTBind(endpoint, &req, nil);
	after = TickCount();
	free(req.addr.buf);
	return status;
}

OSStatus Connect (EndpointRef endpoint, InetHost host, InetPort port)
{
	TCall     sndCall;
	OSStatus  status;
	
	DEBUG_SOCKETS(printf("connecting to %d\n", port));
	MakeIPAddress(&sndCall.addr, host, port);
	sndCall.udata.buf = sndCall.opt.buf = nil;
	sndCall.udata.len = sndCall.opt.len = 0;
	sndCall.udata.maxlen = sndCall.opt.maxlen = 0;
	sndCall.sequence = 0;
	
	status = OTConnect(endpoint, &sndCall, nil);
	
	free(sndCall.addr.buf);
	
	return status;
}




/*
 * This is a notification callback that are called
 * whenever something happens on an endpoint (socket)
 * 
 * IMPORTANT
 *    This callback is called on interrupt. This means
 *    the callback cannot allocate memory or call
 *    any procedure that allocates memory.
 */
 
pascal void BetaNotifyProc (void*			inContextPtr,
							OTEventCode		inEventCode,
							OTResult		inResult,
							void*			inCookie)
{
	OSStatus status;
				
	SocketRef socket = (SocketRef) inContextPtr;
	
	switch (inEventCode) {
		case T_DATA:
		case T_EXDATA:
		case T_LISTEN:
			socket->readReady = true;
			break;
		case T_GODATA:
		case T_GOEXDATA:
			socket->writeReady = true;
			break;
		case T_RESET:
		case T_DISCONNECT:
		case T_ORDREL:
		case kOTProviderWillClose:
		case kOTProviderIsClosed:
			socket->error = true;
			socket->readReady = false;
			socket->writeReady = false;
			socket->eventcode = inEventCode;
			break;
		default:
			break;
	}
	
	status = WakeUpProcess(&gThisProcess); /* WakeUpProcess causes WaitNextEvent to        */
										   /* Terminate. WakeUpProcess is  interrupt safe. */	
	
	return;
}

SocketRef MakeSocket(EndpointRef endpoint)
{	
	SocketRef socket;
	
	socket = (SocketRef) malloc(sizeof(Socket));
	
	if (socket != nil) {
		socket->endpoint = endpoint;
		socket->readReady = false;
		socket->writeReady = false;
		socket->error = false;
		socket->eventcode = 0;
	}
	return socket;
}


/*
 * Here comes the functions used by the BETA implementation
 */

unsigned long getTimeStamp(long fd)
{
	DEBUG_SOCKETS(printf("printf getTimeStamp\n"));
 	return -1;
}

/* 
 *  Find host by name. Return IP-address in host-byteorder. 
 */
long host2inetAddr(char *host)
{
	OSStatus status;
	InetHostInfo hinfo;

	DEBUG_SOCKETS(printf("host2inetAddr %s\n", host));
	status = InitializeOpenTransport();
	if (status == kOTNoError) {
		
		status = InitializeServices();
		if (status == kOTNoError) {
			status = OTInetStringToAddress(gServices, host, &hinfo);
			if (status == kOTNoError) {
				DEBUG_SOCKETS(printf("%x\n", hinfo.addrs[0]));
				return hinfo.addrs[0]; 	/* There might be more than one
										 * just return the first one.
									     */
			}
			else {
				return -1;
			}
		}
		else {
			return -1;
		}
	}
	else  {
		return -1;
	}
}

/* 
 *  Get name of this host. (cached here.)
 */
char const *nameOfThisHost(long *pErrorCode)
{
	DEBUG_SOCKETS(printf("nameOfThisHost\n"));
	return "mariner";
}

/*
 *  Get IP-address of this host in host-byteorder. (Cached here)
 */
long inetAddrOfThisHost(void)
{
	DEBUG_SOCKETS(printf("inetAddrOfThisHost\n"));
  	return 0x82e11081;
}

void initSockets(void)
{	
	/* Do Nothing, since the caller does not check for errors. */
	/* bind, host2initAddr does the actual init */
	return;
}

int createActiveSocket(unsigned long inetAddr, long port, int nonblock)
{
	EndpointRef 	endpoint;
	TEndpointInfo 	info;
	OSStatus 		status;
	SocketRef 		socket;
	TDiscon 		discon;
	
	status = InitializeOpenTransport();
	if (status == kOTNoError) {
		endpoint = OTOpenEndpoint(OTCreateConfiguration("tcp"), 0, &info, &status);
		
		DEBUG_SOCKETS(printf("OTOpenEndpoint %d\n", status));
			
		if (status == kOTNoError) {
			socket = MakeSocket(endpoint);
			if (socket != nil) {			
				status = OTInstallNotifier(endpoint, (OTNotifyProcPtr) BetaNotifyProc, socket);
				DEBUG_SOCKETS(printf("OTInstallNotifier %d\n", status));
				if (status == kOTNoError) {
					status = Bind(endpoint, 0, 0, 0);
					DEBUG_SOCKETS(printf("Bind %d\n", status));
					if (status == kOTNoError) {
						status = Connect(endpoint, (InetHost) inetAddr, (InetPort) port);
						DEBUG_SOCKETS(printf("Connect %d\n", status));
						if (status == kOTNoError) {
							return (int) socket;
						} 
						else {
							if (status == kOTLookErr) {
								status = OTLook(endpoint);
								DEBUG_SOCKETS(printf("OTLook %d\n", status));

								if (status == T_DISCONNECT) {
									status = OTRcvDisconnect(endpoint, &discon);
									DEBUG_SOCKETS(printf("OTRcvDisconnect %d\n", status));
								};
								return -1;
							}
							return -1;
						}
					} 
					else {
						gLastError = kInternal;
						return -1;
					}
				} 
				else {
					gLastError = kInternal;
					return -1;
				}
			}
			else {
				gLastError = kMemory;
				return -1;
			}
		}
		else {
			switch (status) {
				case kEHOSTUNREACHErr:
					gLastError = kHostUnreachable;
					break;
				default:
					gLastError = kUnknown;
					break;
				};
			return -1;
		}
	}
	else {
		gLastError = kUnknown;
		return -1;
	}
}

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
	DEBUG_SOCKETS(printf("sockToRead\n"));
	return -1;
}

int doshutdown(int fd, int how)
{
	DEBUG_SOCKETS(printf("doshutdown\n"));
  	return -1;
}




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
{	long error;

	error = gLastError;
	gLastError = kNoError;
  	
  	return error;
}

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
	SocketRef 		socket = (SocketRef) fd;
	EndpointRef 	endpoint = socket->endpoint;
	OSStatus		status;
 	
	DEBUG_SOCKETS(printf("closeSocket tada\n"));
	
	if (socket != nil) {
		DEBUG_SOCKETS(printf("socket is non nil"));

		if (endpoint != nil) {
			DEBUG_SOCKETS(printf("endpoint is non nil"));
			status = OTCloseProvider(endpoint);
			DEBUG_SOCKETS(printf("OTCloseProvider %d\n", status));
			socket->endpoint = nil;
			free(socket);
		}
		else {
			DEBUG_SOCKETS(printf("endpoint is non nil"));
		}
	} 
	else {
		DEBUG_SOCKETS(printf("socket is nil"));
	}
	
	return 0;
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

	/* NOTE: There is a difference between bind, listen & accept
	 * on Unix and Mac:
	 * OTBind = bind + listen
	 * OTListen + OTAccept = accept
	 */
	 
	SocketRef 		socket = (SocketRef) sock;
	EndpointRef 	endpoint = socket->endpoint;
	EndpointRef 	newEndpoint;
	SocketRef		newSocket;
	OSStatus 		status;
	TCall			call;
	TEndpointInfo 	info;
			
	
	call.addr.maxlen = sizeof(struct InetAddress);
	call.addr.len = sizeof(struct InetAddress);
	call.addr.buf = (unsigned char*) malloc(call.addr.maxlen);
	call.opt.maxlen = 0;
	call.opt.buf = 0;
	call.udata.maxlen = 0;
	call.sequence = (long) socket;
	
	socket->error = false;
	*pBlocked = 0;
	status = OTListen(endpoint, &call);
	
	
	switch (status) {
		case kOTNoError:
			newEndpoint = OTOpenEndpoint(OTCreateConfiguration("tcp"), 0, &info, &status);
			if (status == kOTNoError) {
				newSocket = MakeSocket(newEndpoint);
				if (newSocket != nil) {
					status = OTInstallNotifier(newEndpoint, (OTNotifyProcPtr) BetaNotifyProc, newSocket);
					if (status == kOTNoError) {
						status = OTAccept(endpoint, newEndpoint, &call);
						if (status == kOTNoError) {
							return (int) newSocket;
						}
						else {
							return -1;
						}
					}
					else {
						return -1;
					}
				}
				else {
					return -1;
				}
			}
			else {
				return -1;
			}
		case kOTNoDataErr:
			(*pBlocked) = 1;
			return 0;
		default:
			return -1;
	}
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
	SocketRef socket = (SocketRef) fd;
	EndpointRef endpoint = socket->endpoint;
	OTResult result;

	if (socket->error) {
		switch (socket->eventcode) {
			case T_RESET:
			case T_DISCONNECT:
			case T_ORDREL:
				/*
				 * T_RESET means that the user turned off the network.
				 * T_ORDREL means that the peer closed the connection
				 * in an orderly fashion.
				 * T_DISCONNECT means that the connection is broken.
				 * Should we distinguish between these conditions?
				 */
				gLastError = kDisconnect;
				break;
			default:
				gLastError = kUnknown;
		}
		return -1;
	}
	else {
		
		socket->writeReady = false;
		result = OTSnd(endpoint, srcbuffer, length, 0);
		
		
		if (result > 0) {
			return (int) result;
		}
		else {
			switch (result) {
				case kOTFlowErr:
					/* Try again when the T_GODATA notification arrives */
					return 0;
				case kEAGAINErr:
					/* Try again as soon as possible */
					socket->writeReady = true;
					return 0;
				default:
					gLastError = kInternal;
					return -1;
				
			}
		}
	}
}

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
	SocketRef socket = (SocketRef) fd;
	EndpointRef endpoint = socket->endpoint;
	OTFlags flags = 0;
	OTResult result;
	
	if (socket->error) {
		switch (socket->eventcode) {
			case T_RESET:
			case T_DISCONNECT:
			case T_ORDREL:
				/*
				 * T_RESET means that the user turned of the network.
				 * T_ORDREL means that the peer closed the connection
				 * in an orderly fashion.
				 * T_DISCONNECT means that the connection is broken.
				 * Should we distinguish between these conditions?
				 */
				gLastError = kDisconnect;
				break;
			default:
				gLastError = kUnknown;
		}
		return -1;
	}
	else {
		socket->readReady = false;
		if (socket->error) {
		}
		result = OTRcv(endpoint, destbuffer, buflen, &flags);
		if (socket->error) {
		}
		if (result > 0) {
			if (flags & T_EXPEDITED) {
				/* Expedited is special urgent data, that should not be
				 * considered part of the normal data stream.
				 * Expedited data is only supported by the macintosh
				 * opentransport library (not unix sockets fx). 
				 * We do not expect to recieve expedited data, 
				 * therefore we raise an error.
				 */
				 gLastError = kExpedited;
				 return -1;
			}
			else {
				if (flags & T_MORE) {
					socket->readReady = true;
				}
				return (int) result;
			}
		}
		else if (result == kOTNoDataErr) {
			return 0;
		} 
		else {
			switch (result) {
				case kOTLookErr:
					/*
					 * This is handled by the notification proc.
					 */
					return 0;
				case kOTOutOfMemoryErr:
					gLastError = kMemory;
					return -1;
				default:
					gLastError = kInternal;
					return -1;
			};
			
		}
	}
}

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
	EndpointRef endpoint;
	TEndpointInfo info;
	OSStatus status;
	SocketRef socket;
	
	
	status = InitializeOpenTransport();
	if (status == kOTNoError) {
		endpoint = OTOpenEndpoint(OTCreateConfiguration("tcp"), 0, &info, &status);
			
		if (status == kOTNoError) {
			socket = MakeSocket(endpoint);
			if (socket != nil) {			
				status = OTInstallNotifier(endpoint, (OTNotifyProcPtr) BetaNotifyProc, socket);

				if (status == kOTNoError) {
					status = Bind(endpoint, 0, *port, 5);

					if (status == kOTNoError) {
						return (int) socket;
					} 
					else {
						return -1;
					}
				} 
				else {
					return -1;
				}
			}
			else {
				return -1;
			}
		}
		else {
			return -1;
		}
	}
	else {
		
		return -1;
	}
}


#define kEndMarker						((SocketRef)-1)





int selectSockets (int *readCandidates, 
                   int *writeCandidates, 
				   int *exceptCandidates, 
				   int sec, 
				   int usec)
{
	int readyCount = 0;
	
	SocketRef *readers = (SocketRef *) readCandidates;
	SocketRef *writers = (SocketRef *) writeCandidates;
	SocketRef *excepters = (SocketRef *) exceptCandidates;
	
	int i;
	
	EventRecord theEvent;
	Boolean result = false;
	long sleep; /* Measured in 1/60 secs */
	
	
	
	for (i = 0; readers[i] != kEndMarker; i++) {
		if(readers[i]->readReady) {
			readyCount++;
		}
	}
	
	for (i = 0; writers[i] != kEndMarker; i++) {
		if(writers[i]->writeReady) {
			readyCount++;
		}
	}
	
	for (i = 0; excepters[i] != kEndMarker; i++) {
		if(excepters[i]->error) {
			readyCount++;
		}
	}
	
	if (readyCount == 0) {
		if (sec == -1) {
			sleep = 60 * 60; /* Sleep for a minute 							*/
							 /* A larger number could have been chosen here */
							 /* since -1 means "for ever" 					*/
		} else {
			sleep = sec * 60;
		}
		result = WaitNextEvent(everyEvent, &theEvent, sleep, nil);
		switch (theEvent.what) {
			case updateEvt:
				BeginUpdate((WindowRef) theEvent.message);
				EndUpdate((WindowRef) theEvent.message);
				break;
			default:
				break;
		}
	}
	
	readyCount = 0;
	for (i = 0; readers[i] != kEndMarker; i++) {
		if(readers[i]->readReady) {
			readyCount++;
		}
		else {
			readers[i] = kEndMarker;
		}
	}
	
	for (i = 0; writers[i] != kEndMarker; i++) {
		if(writers[i]->writeReady) {
			readyCount++;
		}
		else {
			writers[i] = kEndMarker;
		}
	}
	
	for (i = 0; excepters[i] != kEndMarker; i++) {
		if(excepters[i]->error) {
			DEBUG_SOCKETS(printf("excepters[%d]->eventcode = %d\n", excepters[i]->endpoint, excepters[i]->eventcode));
			readyCount++;
		}
		else {
			excepters[i] = kEndMarker;
		}
	}
	return readyCount;
}

