#include <OpenTransport.h>
#include <OpenTptInternet.h>

#include <stdio.h>
#include <Memory.h>
#include <stdlib.h>



void CloseDown (void);

static OSStatus Initialize (void);
 /* Makes sure that OpenTransport is initialized */


static OSStatus InitializeServices (void);

OSStatus HostnameToIP (char *name, InetHost *host);
/* Converts a ascii name to a IP address. Runs sync.
 * async is possible. See "InitializeServices"
 */

OSStatus OpenEndpoint (EndpointRef *endpoint);
/* An "EndPoint" is like a unix socket.
 * OTCreateConfiguration("tcp") makes the EndPoint a "tcp ip" 
 * communication channel.
 */

void MakeIPAddress (TNetbuf *outAddress, InetHost host, InetPort port);
/* Fills the TNetbuf structure with an address (IP + port).
 * The outAddress->buf field is allocated with NewPtrClear and must
 * be disposed later by DisposePtr
 */

OSStatus Bind (EndpointRef endpoint, InetHost host, InetPort port);

OSStatus Connect (EndpointRef endpoint, InetHost host, InetPort port);

OTResult Send (EndpointRef endpoint, void *buffer, long size);


OTResult Recieve (EndpointRef endpoint, void *buffer, long size);

#define kDefaultInternetServicesPath	((OTConfiguration*)-3)

enum {
	kOpen,
	kClosed
};

static short 		gState 	 = kClosed;
static InetSvcRef 	services = nil;


void CloseDown (void)
{
	if (gState == kOpen) {
		if (services != nil) {
			OTCloseProvider(services);
			services = nil;
		}
		CloseOpenTransport();
		gState = kClosed;
	}
}


 static OSStatus Initialize (void)
 /* Makes sure that OpenTransport is initialized */
{
	OSStatus status = kOTNoError;
	
	if (gState != kOpen) {
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
	
	if (services == nil) {
		services = OTOpenInternetServices(kDefaultInternetServicesPath, 0, &status);
		if (status != kOTNoError) {
			services = nil;
		}
	}
	return status;
}



OSStatus HostnameToIP (char *name, InetHost *host)
/* Converts a ascii name to a IP address. Runs sync. */
/* async is possible. See "InitializeServices" */
{
	OSStatus 	status  = kOTNoError;
	InetHost 	address = 0;
	
	InetHostInfo hinfo;	

	status = Initialize();
	
	if (status == kOTNoError) {
		status = InitializeServices();
		if (status == kOTNoError) {
			status = OTInetStringToAddress(services, name, &hinfo);
			if (status == kOTNoError) {
				(*host) = hinfo.addrs[0]; 	/* There might be more than one
											 * Just choose the first one.
											 */
			}
		}
	}

	return status;
}




OSStatus OpenEndpoint (EndpointRef *endpoint)
/* An "EndPoint" is like a unix socket.
 * OTCreateConfiguration("tcp") makes the EndPoint a "tcp ip" 
 * communication channel.
 */
{
	TEndpointInfo info;
	OSStatus 	  status = kOTNoError;
	
	(*endpoint) = OTOpenEndpoint(OTCreateConfiguration("tcp"), 0, &info, &status);
	
	return status;
}

void MakeIPAddress (TNetbuf *outAddress, InetHost host, InetPort port)
/* Fills the TNetbuf structure with an address (IP + port).
 * The outAddress->buf field is allocated with NewPtrClear and must
 * be disposed later by DisposePtr
 */
{
	InetAddress* inAddr = nil;
	inAddr = (InetAddress*) NewPtrClear(sizeof (InetAddress));

	inAddr->fAddressType = AF_INET;
	inAddr->fPort = port;
	inAddr->fHost = host;
	
	outAddress->maxlen = outAddress->len = sizeof (InetAddress);
	outAddress->buf = (UInt8*) inAddr;
}

OSStatus Bind (EndpointRef endpoint, InetHost host, InetPort port)
{
	OSStatus  status = kOTNoError;
	TBind     req;
	
	MakeIPAddress(&req.addr, host, port);
	
	status = OTBind(endpoint, &req, nil);
	
	return status;
}

OSStatus Connect (EndpointRef endpoint, InetHost host, InetPort port)
{
	TCall     sndCall;
	OSStatus  status = kOTNoError;
	OTResult  result = kOTNoError;
	
	MakeIPAddress(&sndCall.addr, host, port);
	sndCall.udata.buf = sndCall.opt.buf = nil;
	sndCall.udata.len = sndCall.opt.len = 0;
	sndCall.udata.maxlen = sndCall.opt.maxlen = 0;
	sndCall.sequence = 0;
	
	status = OTConnect(endpoint, &sndCall, nil);
	
	return status;
}

OTResult Send (EndpointRef endpoint, void *buffer, long size)
{
	OTResult  result = kOTNoError;
	
	result = OTSnd(endpoint, buffer, size, 0);
	
	return result;
}


OTResult Recieve (EndpointRef endpoint, void *buffer, long size)
{
	OTResult  result = kOTNoError;
	OTFlags flags = 0;
	
	result = OTRcv(endpoint, buffer, size, &flags);
	
	return result;
}
