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

#define	GetFileDialogID	-601

#define SFSaveDisk		0x214		/* Negative of current volume refnum [WORD]	*/
#define CurDirStore		0x398		/* DirID of current directory [LONG]		*/
#define ResLoad			0xA5E		/* Boolean ResLoad setting [WORD]			*/
#define TopMapHndl		0xA50		/* 1st map in resource list [Handle]		*/


#define firstTime		-1  /* the first time our hook is called, it is passed a -1 */

#define reDrawList		101 /* returning 101 as item number will cause the FILE list
								to be recalculated */

char *pStrcat(unsigned char *s,unsigned char *t);
char *pStrcpy(unsigned char *s, unsigned char *t);

char *GetPathName(char *s);

long		MyCurDir;
Boolean		CurDirValid;
SFReply		reply;          /* reply record */
OSErr		err;			/* used in all OS calls */



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

unsigned char *GetBetaFolder(unsigned char *s)
{
	/* pascal short MyGetDirHook(); */  
	pascal Boolean FoldersOnly();
                
	Point        wher;                /* where to display dialog */
	SFTypeList   myFileTypes;          /* we won't actually use this */
	short int    NumFileTypes = -1;
	Str255       VolName, dirName;
	CInfoPBRec   block;
	
	wher.h=80; wher.v=90;
	CurDirValid = false;

	SFPGetFile(wher,	/* location */
		"\pBETA Folder",	/* vestigial string */
		/* FoldersOnly */ nil,		/* fileFilter */
		-1,					/* numtypes; -1 means all */
		myFileTypes,			/* array to types to show */
		/* MyGetDirHook */ nil,		/* dlgHook */
		&reply,				/* record for returned values */
		GetFileDialogID,
		nil);
	   
	if (CurDirValid){
	   /* Use MyCurDir as vRefNum */
	   	block.dirInfo.ioNamePtr = dirName;
	    block.dirInfo.ioDrParID = MyCurDir;
		block.dirInfo.ioVRefNum = -*(short *)SFSaveDisk;
		block.dirInfo.ioFDirIndex = -1;
		block.dirInfo.ioDrDirID = block.dirInfo.ioDrParID;
		
		PBGetCatInfo(&block,false);
		PathNameFromDirID(MyCurDir, -*(short *)SFSaveDisk, s);
		return s;

	}
	return "\p";
}

pascal short MyGetDirHook(short	item, DialogPtr dPtr)
{
	switch (item) {
		case firstTime:
			/* Read in the prompt string from the resource fork, and initialize */
			/* CurDirValid to FALSE. */
			CurDirValid = false;
			break;
		case 11:
			if (reply.fType != 0) {
				MyCurDir = reply.fType;
				CurDirValid = true;
				return(getCancel);
			};
			break;
		case 12:
			MyCurDir = *(long *)CurDirStore;
			CurDirValid = true;
			return(getCancel);
			break;
	};
	return(item);	/* By default, return the item passed to us. */
};


pascal Boolean FoldersOnly(p)
	ParmBlkPtr p;
{
	/* Normally, folders are ALWAYS shown, and aren't even passed to		*/
	/* this file filter for judgement. Under such circumstances, it is		*/
	/* only necessary to blindly return TRUE (allow no files whatsoever).	*/
	/* However, Standard File is not documented in such a manner, and		*/
	/* this feature may not be TRUE in the future. Therefore, we DO check	*/
	/* to see if the entry passed to us describes a file or a directory.	*/

	if ((p->fileParam.ioFlAttrib & 0x10) != 0)
		return(false);
	return(true);
};

