/* © 1990 Mj¿lner Informatik Aps. by: Kim Jensen M¿ller */

#include <types.h>
#include <quickdraw.h>
#include <controls.h>
#include <dialogs.h>
#include <toolutils.h>
#include <osutils.h>
#include <events.h>
#include <packages.h>
#include <resources.h>
#include <StandardFile.h>
#include <Strings.h>
#include <stdio.h>
#include <TextUtils.h>
#include <string.h>
#include <Controls.h>

#define	GetFileDialogID	-601

#define SFSaveDisk		0x214		/* Negative of current volume refnum [WORD]	*/
#define CurDirStore		0x398		/* DirID of current directory [LONG]		*/
#define ResLoad			0xA5E		/* Boolean ResLoad setting [WORD]			*/
#define TopMapHndl		0xA50		/* 1st map in resource list [Handle]		*/


#define kSelectItem		10

#define reDrawList		101 /* returning 101 as item number will cause the FILE list
								to be recalculated */

Str255 gSelectString = "\pSelect";
Str255 gLastSelected = "\p";
Boolean gValid;


Boolean gChanged;

char *pStrcat(unsigned char *s,unsigned char *t);
char *pStrcpy(unsigned char *s, unsigned char *t);

char *GetPathName(char *s);

unsigned char *GetBetaFolder(unsigned char *s);

pascal short GetBetaFolderHook (short item, DialogPtr dialog, StandardFileReply *reply);

pascal Boolean FoldersOnly (CInfoPBPtr pb, StandardFileReply *reply);
pascal	OSErr	FSpGetFullPath(const FSSpec *spec,
							   short *fullPathLength,
							   Handle *fullPath);
void SetSelectButtonName(StringPtr selName,Boolean hilited,DialogPtr theDlg);

void MakeCannonFSSpec(FSSpec *spec);



long		MyCurDir;
Boolean		CurDirValid;
SFReply		reply;          /* reply record */
OSErr		err;			/* used in all OS calls */

/******** FSpGetFullPath is taken from "morefiles" by apple. */

pascal	OSErr	FSpGetFullPath(const FSSpec *spec,
							   short *fullPathLength,
							   Handle *fullPath)
{
	OSErr		result;
	FSSpec		tempSpec;
	CInfoPBRec	pb;
	
	*fullPathLength = 0;
	*fullPath = NULL;
	
	/* Make a copy of the input FSSpec that can be modified */
	BlockMoveData(spec, &tempSpec, sizeof(FSSpec));
	
	if ( tempSpec.parID == fsRtParID )
	{
		/* The object is a volume */
		
		/* Add a colon to make it a full pathname */
		++tempSpec.name[0];
		tempSpec.name[tempSpec.name[0]] = ':';
		
		/* We're done */
		result = PtrToHand(&tempSpec.name[1], fullPath, tempSpec.name[0]);
	}
	else
	{
		/* The object isn't a volume */
		
		/* Is the object a file or a directory? */
		pb.dirInfo.ioNamePtr = tempSpec.name;
		pb.dirInfo.ioVRefNum = tempSpec.vRefNum;
		pb.dirInfo.ioDrDirID = tempSpec.parID;
		pb.dirInfo.ioFDirIndex = 0;
		result = PBGetCatInfoSync(&pb);
		if ( result == noErr )
		{
			/* if the object is a directory, append a colon so full pathname ends with colon */
			if ( (pb.hFileInfo.ioFlAttrib & ioDirMask) != 0 )
			{
				++tempSpec.name[0];
				tempSpec.name[tempSpec.name[0]] = ':';
			}
			
			/* Put the object name in first */
			result = PtrToHand(&tempSpec.name[1], fullPath, tempSpec.name[0]);
			if ( result == noErr )
			{
				/* Get the ancestor directory names */
				pb.dirInfo.ioNamePtr = tempSpec.name;
				pb.dirInfo.ioVRefNum = tempSpec.vRefNum;
				pb.dirInfo.ioDrParID = tempSpec.parID;
				do	/* loop until we have an error or find the root directory */
				{
					pb.dirInfo.ioFDirIndex = -1;
					pb.dirInfo.ioDrDirID = pb.dirInfo.ioDrParID;
					result = PBGetCatInfoSync(&pb);
					if ( result == noErr )
					{
						/* Append colon to directory name */
						++tempSpec.name[0];
						tempSpec.name[tempSpec.name[0]] = ':';
						
						/* Add directory name to beginning of fullPath */
						(void) Munger(*fullPath, 0, NULL, 0, &tempSpec.name[1], tempSpec.name[0]);
						result = MemError();
					}
				} while ( (result == noErr) && (pb.dirInfo.ioDrDirID != fsRtDirID) );
			}
		}
	}
	if ( result == noErr )
	{
		/* Return the length */
		*fullPathLength = InlineGetHandleSize(*fullPath);
	}
	else
	{
		/* Dispose of the handle and return NULL and zero length */
		if ( *fullPath != NULL )
		{
			DisposeHandle(*fullPath);
		}
		*fullPath = NULL;
		*fullPathLength = 0;
	}
	
	return ( result );
}




/** PathNameFromDirID *********************************************************/

#define CPromptID 7130

static unsigned char *PathNameFromDirID(long DirID,short vRefNum,unsigned char *s)
{
	CInfoPBRec	block;
	Str255		directoryName;

	*s = 0;
	block.dirInfo.ioNamePtr = directoryName;
	block.dirInfo.ioDrParID = DirID;

	do {
		block.dirInfo.ioVRefNum = vRefNum;
		block.dirInfo.ioFDirIndex = -1;
		block.dirInfo.ioDrDirID = block.dirInfo.ioDrParID;

		err = PBGetCatInfo(&block,false);
		/* Append a Macintosh style colon (':') */
		pStrcat(directoryName,"\p:");
		pStrcat(directoryName,s);
		pStrcpy(s,directoryName);
	} while (block.dirInfo.ioDrDirID != 2);
	return(s);
}

unsigned char *GetBetaFolder (unsigned char *s)
{
	SFTypeList 			typeList;
	StandardFileReply 	reply;
	Point				where;
	Handle				fullpath;
	short				length;
	OSErr 				err;
	static	Str255 		result;
	Str255				store;
	
	where.h = -1;
	where.v = -1;
	
	gValid = false;
	
	CustomGetFile (NewFileFilterYDProc(FoldersOnly),
				   -1,
				   typeList,
				   &reply,
				   GetFileDialogID,
				   where,
				   NewDlgHookYDProc(GetBetaFolderHook),
				   nil,
				   nil,
				   nil,
				   &reply);
				   
				   
	if (gValid) {
		MakeCannonFSSpec(&(reply.sfFile));
		err = FSpGetFullPath(&(reply.sfFile), &length, &fullpath);
		if (err == 0) {
			BlockMove(*fullpath, result + 1, length);
			result[0] = length;
			p2cstr(result);
			DisposeHandle(fullpath);
			return result;
		}
	}
	
	return (unsigned char *) "";
}



pascal Boolean FoldersOnly (CInfoPBPtr pb, StandardFileReply *reply)
{
	if (pb->hFileInfo.ioFlAttrib & (1<<4)) {
		return false;
	}
	else {
		return true;
	}
}

pascal short GetBetaFolderHook (short item, DialogPtr dialog, StandardFileReply *reply)
{	FSSpec spec;
	Str255 store;
	CInfoPBRec 	pb;
	
	switch (item) {
		case sfHookFirstCall:
			pb.hFileInfo.ioCompletion = nil;
			pb.hFileInfo.ioNamePtr = gLastSelected;
			pb.hFileInfo.ioVRefNum = LMGetSFSaveDisk();
			pb.hFileInfo.ioFDirIndex = -1;
			pb.hFileInfo.ioDirID = LMGetCurDirStore();
			err = PBGetCatInfo(&pb, false);
			SetSelectButtonName(gLastSelected, true, dialog);

			return item;
		case sfHookLastCall:
			return item;
		case kSelectItem:
			gValid = true;
			return sfItemCancelButton;
		default:
			MakeCannonFSSpec(&(reply->sfFile));
			if (!EqualString(reply->sfFile.name, gLastSelected, true, true)) {
				BlockMove(reply->sfFile.name, gLastSelected, reply->sfFile.name[0] + 1);
				SetSelectButtonName(reply->sfFile.name, true, dialog);
			}
			return item;
	}
}


/* pascal short GetBetaFolderHook (short item, DialogPtr dialog, StandardFileReply *reply)
{	
	CInfoPBRec 	pb;
	OSErr		err;
	Str255		name;
	
	if (GetWRefCon((WindowPtr) dialog) != sfMainDialogRefCon) {
		return item;
	}
	
	switch (item) {
		case sfHookFirstCall:
			pb.dirInfo.ioCompletion = nil;
			pb.dirInfo.ioNamePtr = name;
			pb.dirInfo.ioVRefNum = LMGetSFSaveDisk();
			pb.dirInfo.ioFDirIndex = -1;
			pb.dirInfo.ioDirID = LMGetCurDirStore();
			err = PBGetCatInfo(&pb, false);
			SetSelectButtonName(name, true, dialog);
			gChanged = true;
			return item;
		case sfHookNullEvent:
			if (gChanged) {
				if (reply->sfIsFolder || reply->sfIsVolume) {
					SetSelectButtonName(reply->sfFile.name, true, dialog);
				}
				else {
					pb.hFileInfo.ioCompletion = nil;
					pb.hFileInfo.ioNamePtr = name;
					pb.hFileInfo.ioVRefNum = reply->sfFile.vRefNum;
					pb.hFileInfo.ioFDirIndex = -1;
					pb.hFileInfo.ioDirID = reply->sfFile.parID;
					err = PBGetCatInfo(&pb, false);
					SetSelectButtonName(name, true, dialog);
				}
				gChanged = false;

			}
			return item;
		case kSelectItem:
			return sfItemOpenButton;
		default:
			gChanged = true;
			return item;
	}
}
*/

void SetSelectButtonName(StringPtr selName,Boolean hilited,DialogPtr theDlg)
{
	short iType;
	Handle iHndl;
	Rect iRect;
	Str255 storeName,tempLenStr,tempSelName;
	short btnWidth;
	
	BlockMove(selName,tempSelName,selName[0]+1);
	GetDialogItem(theDlg,kSelectItem,&iType,&iHndl,&iRect);
	
	/* truncate select name to fit in button */
	
	btnWidth = iRect.right - iRect.left;
	BlockMove(gSelectString,tempLenStr,gSelectString[0]+1);
	p2cstr(tempLenStr);
	strcat((char *)tempLenStr," ÒÓ  ");
	c2pstr((char *)tempLenStr);
	btnWidth -= StringWidth(tempLenStr);
	TruncString(btnWidth,tempSelName,smTruncMiddle);
	
	BlockMove(gSelectString,storeName,gSelectString[0]+1);
	p2cstr(storeName);
	p2cstr(tempSelName);
	strcat((char *)storeName," Ò");
	strcat((char *)storeName,(char *)tempSelName);
	strcat((char *)storeName,"Ó");
	
	c2pstr((char *)storeName);
	c2pstr((char *)tempSelName);
	SetControlTitle((ControlHandle) iHndl,storeName);
	
	SetDialogItem(theDlg,kSelectItem,iType,iHndl,&iRect);

	if (hilited)
		HiliteControl((ControlHandle) iHndl,0);
	else
		HiliteControl((ControlHandle) iHndl,255);		
}


void MakeCannonFSSpec(FSSpec *spec)
{	OSErr err;

	err = FSMakeFSSpec(spec->vRefNum, 
					   spec->parID,
					   spec->name,
					   spec);
	return;
}


