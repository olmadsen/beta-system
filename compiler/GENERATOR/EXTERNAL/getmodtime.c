/********** GETMODTIME.C FOR THE COMPILER ************/

#include <types.h>
#include <fcntl.h>
#include <errno.h>
#include <stdio.h>
#include <stdLib.h>
#include <memory.h>
#include <Files.h>
#include <Errors.h>
#include <Packages.h>
#include <OSUtils.h>

short GetEntryInfo(unsigned char *name, CInfoPBPtr block)
{	short	vRefNum;
	const char volName[256];
	WDPBRec	myBlock;

	if (getvol(volName,&vRefNum) != noErr) return -1;
	memset(&myBlock,0,sizeof(WDPBRec));
	myBlock.ioVRefNum = vRefNum;
	PBGetWDInfo(&myBlock,false);

	c2pstr(name);
	block->dirInfo.ioNamePtr = name;
	block->dirInfo.ioDrDirID = myBlock.ioWDDirID;
	block->dirInfo.ioVRefNum = myBlock.ioWDVRefNum;
	block->dirInfo.ioFDirIndex = 0;

	return PBGetCatInfo(block,false);
}

long getmodtime(unsigned char *name)
{	short err;
	CInfoPBRec	block;
	unsigned long time;
	err = GetEntryInfo(name,&block);
	if (err == noErr) {
		if (block.dirInfo.ioFlAttrib & 16) {
			// it's a directory
			time = block.dirInfo.ioDrMdDat;
		} else {
			// it's a file
			time = block.hFileInfo.ioFlMdDat;
		}
		return time & ~(1<<31);
	} else {
		errno = err;
		return -1;
	}
}


