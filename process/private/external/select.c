#include "sockets.h"
#include <Events.h>
#include <Windows.h>
#include <stdlib.h>
#include <stdio.h>
#include <Memory.h>

#define kEndMarker						((SocketRef)-1)


int selectSockets (int *readCandidates, 
                   int *writeCandidates, 
				   int *exceptCandidates, 
				   int sec, 
				   int usec);


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
			printf("excepters[%d]->eventcode = %d\n", excepters[i]->endpoint, excepters[i]->eventcode);
			readyCount++;
		}
		else {
			excepters[i] = kEndMarker;
		}
	}
	return readyCount;
}

