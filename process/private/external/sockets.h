#include <OpenTransport.h>
#include <OpenTptInternet.h>



typedef struct Socket {
	EndpointRef endpoint;
	Boolean 	readReady;
	Boolean		writeReady;
	Boolean		error;
	OTEventCode	eventcode;
} Socket;


typedef Socket *SocketRef;
