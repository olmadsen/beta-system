////
////	SignatureToApp.h		Interface for SignatureToApp
////
////	By Jens Alfke			©1992 Apple Computer, Inc. All rights reserved.
////

#pragma once


#ifndef __SIGNATURETOAPP__
	#define __SIGNATURETOAPP__

#ifndef __PROCESSES__
#ifdef macosx
#include <Carbon/Carbon.h>
#else
	#include <Processes.h>
#endif
#endif


#ifdef __cplusplus
extern "C" {
#endif

typedef enum{
	Sig2App_FindProcess		=0,
	Sig2App_FindApplication,
	Sig2App_LaunchApplication
} Sig2App_Mode;

// Launch control flags: these are part of the Process Manager. The relevant ones are:
//	launchContinue		Don't quit this app after launching the new one (you want to use this!!)
//	launchUseMinimum	Use the minimum heap size as specified in the app's SIZE resource.
//	launchDontSwitch	Don't activate the launched app.
//	launchInhibitDaemon	Prevent launch of background-only apps.
// See IM-VI p.29-15 for the full poop.


OSErr
SignatureToApp(	OSType sig,						// Signature of app
				const FSSpec *document,			// Document to open with app, or NULL
				ProcessSerialNumber *psn,		// Returns PSN of app (ignored if NULL)
				FSSpec *fileSpec,				// Returns location of app (ignored if NULL)
				Boolean *launched,				// Set to TRUE if I had to launch (ignored if NULL)
				Sig2App_Mode mode,				// Mode -- find proc/find app/launch app
				LaunchFlags launchControlFlags	// Launch control flags; see Process Mgr
			  );

#ifdef __cplusplus
}
#endif

#endif
