#include <memory.h>
#include <Files.h>
#define longint long


extern char *pStrcat(unsigned char *s, unsigned char *t);
extern char *pStrcpy(unsigned char *s, unsigned char *t);

unsigned char *s, *t;
/** PathNameFromDirID *********************************************************/

char *PathNameFromDirID(DirID, vRefNum, s)
     long	DirID;
     short	vRefNum;
     char	*s;
{
  CInfoPBRec	block;
  Str255		directoryName;
  short err;

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
  } while (block.dirInfo.ioDrDirID != fsRtDirID);

  return(s);
}


/** PathNameFromWD ************************************************************/

char *PathNameFromWD(vRefNum,s)
     long	vRefNum;
     char	*s;
{

  WDPBRec	myBlock;

  myBlock.ioNamePtr = nil;
  myBlock.ioVRefNum = vRefNum;
  myBlock.ioWDIndex = 0;
  myBlock.ioWDProcID = 0;

  /* Change the Working Directory number in vRefnum into a real vRefnum */
  /* and DirID. The real vRefnum is returned in ioVRefnum, and the real */
  /* DirID is returned in ioWDDirID. */

  PBGetWDInfo(&myBlock,false);

  return(PathNameFromDirID(myBlock.ioWDDirID,myBlock.ioWDVRefNum,s));
};

char *getwd(s)
     char	*s;
{
  short	vRefNum,err;
  Str255	volName;
	
  err = getvol(&volName , &vRefNum);
  PathNameFromWD(vRefNum,s);
  return (s);
}
