////
////	SignatureToApp.c		Implementation of the SignatureToApp function.
////
////	By Jens Alfke			©1991 Apple Computer, Inc. All rights reserved.
////

#ifdef macosx
#include <Carbon/Carbon.h>
#else
#include <Errors.h>
#include <Files.h>
#include <Processes.h>
#include <Folders.h>
#include <AppleEvents.h>
#endif

#include "signaturetoapp_ext.h"



int FindRunningAppByPSN(ProcessSerialNumber *psn)
{
	OSErr err;
	ProcessInfoRec info;
	FSSpec fileSpec;
	info.processInfoLength = sizeof(info);
	info.processName = NULL;
	info.processAppSpec = &fileSpec;
	err = GetProcessInformation(psn,&info);
	
	if(err) {
		return 0;
	}
	else {
		return 1;
	}
}


   ////////////////////////////////////////////////////////////
  //	FindRunningAppBySignature							//
 //			Search process list for app with this signature//
////////////////////////////////////////////////////////////
static OSErr
FindRunningAppBySignature( OSType sig, ProcessSerialNumber *psn, FSSpec *fileSpec )
{
	OSErr err;
	ProcessInfoRec info;
	
	psn->highLongOfPSN = 0;
	psn->lowLongOfPSN  = kNoProcess;
	do{
		err = GetNextProcess(psn);
		if( !err ) {
			info.processInfoLength = sizeof(info);
			info.processName = NULL;
			info.processAppSpec = fileSpec;
			err= GetProcessInformation(psn,&info);
		}
	} while( !err && info.processSignature != sig );

	if( err )
		fileSpec->name[0] = 0;								// Clear name if not found
	else
		*psn = info.processNumber;
	return err;
}


   ////////////////////////////////////////////////////////////
  //	GetSysVolume										//
 //			Get the vRefNum of the system (boot) volume	   //
////////////////////////////////////////////////////////////
static OSErr
GetSysVolume( short *vRefNum )
{
	long dir;
	
	return FindFolder(kOnSystemDisk,kSystemFolderType,false, vRefNum,&dir);
}


   ////////////////////////////////////////////////////////////
  //	GetIndVolume										//
 //			Get the vRefNum of an indexed on-line volume   //
////////////////////////////////////////////////////////////
static OSErr
GetIndVolume( short index, short *vRefNum )
{
	ParamBlockRec pb;
	OSErr err;
	
	pb.volumeParam.ioCompletion = NULL;
	pb.volumeParam.ioNamePtr = NULL;
	pb.volumeParam.ioVolIndex = index;
	
	err= PBGetVInfo(&pb,false);
	
	*vRefNum = pb.volumeParam.ioVRefNum;
	return err;
}


   ////////////////////////////////////////////////////////////
  //	VolHasDesktopDB										//
 //			Check if a volume supports desktop DB calls	   //
////////////////////////////////////////////////////////////
static OSErr
VolHasDesktopDB( short vRefNum, Boolean *hasDesktop )
{
	typedef struct {						// Volume Info Rec; see IM-VI 25-32
		short	vMVersion;
		long	vMAttrib;
		Handle	vMLocalHand;
		long	vMServerAddr;
		long	vMVolumeGrade;
		short	vMForeignPrivID;
	} VolInfoRec;
	const bHasNewDesk = 1L <<12;			// Flag mask for vMAttrib field
	
	HParamBlockRec pb;
	VolInfoRec info;
	OSErr err;
	
	long i, *ip;
	for( i=0, ip=(long*)&pb; i<sizeof(pb)/sizeof(long); i++ )		// Clear pb
		*ip++ = 0;
	pb.ioParam.ioCompletion = NULL;
	pb.ioParam.ioNamePtr = NULL;
	pb.ioParam.ioVRefNum = vRefNum;
	pb.ioParam.ioBuffer = (Ptr)&info;
	pb.ioParam.ioReqCount = sizeof(VolInfoRec);
	
	err= PBHGetVolParms(&pb,false);			// Get volume info

	*hasDesktop = err==noErr && (info.vMAttrib & bHasNewDesk)!=0;
	return err;
}


   ////////////////////////////////////////////////////////////
  //	FindAppOnVolume										//
 //			Ask vol's desktop db for application		   //
////////////////////////////////////////////////////////////
static OSErr
FindAppOnVolume( OSType sig, short vRefNum, FSSpec *file )
{
	DTPBRec pb;
	OSErr err;
	short refNum;
	
	long i, *ip;
	for( i=0, ip=(long*)&pb; i<sizeof(pb)/sizeof(long); i++ )		// Clear pb
		*ip++ = 0;

	pb.ioCompletion = NULL;
	pb.ioVRefNum = vRefNum;
	pb.ioNamePtr = NULL;
	err= PBDTGetPath(&pb);				// Puts DT refnum into pb.ioDTRefNum
	if( err ) return err;
	refNum = pb.ioDTRefNum;
	
	pb.ioCompletion = NULL;
	pb.ioDTRefNum = refNum;
	pb.ioIndex = 0;
	pb.ioFileCreator = sig;
	pb.ioNamePtr = (StringPtr)&file->name;
	err= PBDTGetAPPLSync(&pb);						// Find it!
	
	if( err == fnfErr )
		err = afpItemNotFound;						// Bug in PBDTGetAPPL
	if( err )
		return err;									// Returns afpItemNotFound if app wasn't found.

	file->vRefNum = vRefNum;
	file->parID = pb.ioAPPLParID;
	return noErr;
}


   ////////////////////////////////////////////////////////////
  //	BuildODoc											//
 //			Construct an 'odoc' Apple event				   //
////////////////////////////////////////////////////////////
static OSErr
BuildODoc( const FSSpec *fileSpec, OSType signature, const ProcessSerialNumber *psn,
		   AppleEvent *event )
{
	// If psn is non-NULL the event will be addressed to that process;
	// otherwise it'll be addressed to the supplied signature.
	
	AEDesc addr,ev;
	OSErr err;
	
	event->descriptorType = 0;
	event->dataHandle = NULL;
	
	if( psn )
		err= AECreateDesc(typeProcessSerialNumber,(void*)psn,sizeof(*psn), &addr);
	else
		err= AECreateDesc(typeApplSignature,(void*)&signature,sizeof(signature), &addr);
	if( err ) return err;
	
	err= AECreateAppleEvent(kCoreEventClass,kAEOpenDocuments, &addr,kAutoGenerateReturnID,0,&ev);
	AEDisposeDesc(&addr);
	if( !err )
		err= AEPutParamPtr(&ev,keyDirectObject, typeFSS,(void*)fileSpec,sizeof(FSSpec));
	
	if( err )
		AEDisposeDesc(&ev);
	else
		*event = ev;
	return err;
}


   ////////////////////////////////////////////////////////////
  //	LaunchIt											//
 //			Launch app once we have a location			   //
////////////////////////////////////////////////////////////
static OSErr
LaunchIt( const FSSpec *fileSpec, LaunchFlags launchControlFlags, const AppleEvent *odoc,
			ProcessSerialNumber *psn )
{
	LaunchParamBlockRec pb;
	AEDesc paramDesc;
	OSErr err;
	
	pb.launchBlockID = extendedBlock;
	pb.launchEPBLength = extendedBlockLen;
	pb.launchFileFlags = launchNoFileFlags;
	pb.launchControlFlags = launchControlFlags | launchNoFileFlags;
	pb.launchAppSpec = (FSSpec*)fileSpec;
	
	if( odoc ) {
		err= AECoerceDesc(odoc,typeAppParameters, &paramDesc);
		if( err ) return err;
		HLock((Handle) paramDesc.dataHandle);
		pb.launchAppParameters = (void*) *paramDesc.dataHandle;
	} else
		pb.launchAppParameters = NULL;
	
	err= LaunchApplication(&pb);
	
	if( odoc )
		AEDisposeDesc(&paramDesc);
		
	if( !err )
		*psn = pb.launchProcessSN;
	return err;
}


   ////////////////////////////////////////////////////////////
  //	SignatureToApp										//
 //			Main routine. Find app, launching if need be   //
////////////////////////////////////////////////////////////
OSErr
SignatureToApp( OSType sig, const FSSpec *document,
				ProcessSerialNumber *psn, FSSpec *fileSpec, Boolean *launched,
				Sig2App_Mode mode,
				LaunchFlags launchControlFlags )
{
	ProcessSerialNumber dummyPSN;
	OSErr err;
	short sysVRefNum, vRefNum, index;
	FSSpec file;
	Boolean hasDesktopDB;
	
	if( launched )
		*launched = false;
	if( psn == NULL )
		psn = &dummyPSN;								// Allow psn parameter to be NIL
	
	// First see if it's already running:
	
	err= FindRunningAppBySignature(sig,psn,fileSpec);
	
	if( err==noErr && mode==Sig2App_LaunchApplication ) {
		if( (launchControlFlags & launchDontSwitch) == 0 ) {
			err= SetFrontProcess(psn);				// They wanted to switch to it…
			if( err ) return err;
		}
		if( document ) {
			// They wanna open a document, so do it:
			AppleEvent aevt;
			err= BuildODoc(document,sig,psn, &aevt);
			if( !err )
				err= AESend(&aevt,NULL,kAENoReply | kAEAlwaysInteract,
							kAENormalPriority,kAEDefaultTimeout,
							NULL,NULL);
			AEDisposeDesc(&aevt);
		}
		return err;
	}

	if( err != procNotFound || mode<=Sig2App_FindProcess )
		return err;
	
	// Well, it's not running but it's okay to launch it. Let's have a look around:
	
	
	
	if( err= GetSysVolume(&sysVRefNum) ) return err;	// Find boot volume
	vRefNum = sysVRefNum;								// Start search with boot volume
	index = 0;
	
	do{
		if( index==0 || vRefNum != sysVRefNum ) {
			
			if( err= VolHasDesktopDB(vRefNum,&hasDesktopDB) ) {
				return err;
			}
				
			if( hasDesktopDB ) {
																
																
																// If volume has a desktop DB,
				err= FindAppOnVolume(sig,vRefNum, &file);		// ask it to find app
				if( err==noErr ) {
					// FOUND IT!
					if( fileSpec )
						*fileSpec = file;
					if( mode==Sig2App_LaunchApplication ) {
						AEDesc odoc;
						if( document )
							err= BuildODoc(document,sig,NULL,&odoc);
						if( err ) return err;
						err= LaunchIt(&file,launchControlFlags,		// Launch it!
										document ?&odoc :NULL,
										psn);
						if( document )
							AEDisposeDesc(&odoc);
						if( !err && launched )
							*launched = true;
					}
					return err;
					
				} else if( err != afpItemNotFound )
					return err;
			}
		}
		err= GetIndVolume(++index,&vRefNum);				// Else go to next volume
	} while( err==noErr );								// Keep going until we run out of vols
	
	if( err==nsvErr || err==afpItemNotFound )
		err= fnfErr;									// File not found on any volume
	return err;
}
