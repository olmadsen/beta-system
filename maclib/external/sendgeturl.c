#ifdef macosx
#include <Carbon/Carbon.h>
#else
#include <AppleEvents.h>
#include <Processes.h>
#endif


OSErr CreateAppleEvent(OSType suite, OSType id, AppleEvent *event, ProcessSerialNumber *targetPSN)
{   OSErr err;
    AEAddressDesc progressApp;
	
	err = AECreateDesc(typeProcessSerialNumber, targetPSN, 
							 sizeof(ProcessSerialNumber), &progressApp);
	if (err)
		return err;
		
	err = AECreateAppleEvent(suite, id,
							 &progressApp,
							 kAutoGenerateReturnID,
							 kAnyTransactionID,
							 event);
							 
	AEDisposeDesc(&progressApp);
	return err;
}


OSErr SendGetURL(char *url, long length, ProcessSerialNumber *psn)
{
	OSErr err;
	AppleEvent event;
	AppleEvent reply;
	AEDesc urlDesc;   
	
	err = CreateAppleEvent('GURL', 'GURL', &event, psn);
	
	if (err)
		return err;
	
	AECreateDesc(typeChar, url, length, &urlDesc);
	err = AEPutParamDesc(&event, keyDirectObject, &urlDesc);
	
	if (err)
		return err;
		
	err = SetFrontProcess(psn);
	
	err = AESend(&event,&reply,kAEWaitReply,kAEHighPriority,500,nil, nil);
	
	return err;
}

