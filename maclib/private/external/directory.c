#include <memory.h>
#include <Files.h>
#include <Errors.h>
#include <stdio.h>
#define longint long


extern char *pStrcat(unsigned char *s, unsigned char *t);
extern char *pStrcpy(unsigned char *s, unsigned char *t);

char *PathNameFromDirID(long DirID, short vRefNum, char	*s);
char *PathNameFromWD(long vRefNum,char *s);
char *getwd(char *s);


unsigned char *s, *t;
/** PathNameFromDirID *********************************************************/

char *PathNameFromDirID(long DirID, short vRefNum, char	*s)
{
  CInfoPBRec	block;
  Str255		directoryName;
  long          ParID;
  short err;
  //int i=0;

  *s = 0; /* make s be empty string to allow pStrCat below */
  block.dirInfo.ioNamePtr = directoryName;
  ParID = DirID;

  //fprintf(stdout, "PathNameFromDirID(%d, %d, 0x%x)\n", DirID, vRefNum, s); fflush(stdout);

  do {
    //fprintf(stderr, "PathNameFromDirID-%d: %d\n", i++, ParID); fflush(stderr);
	
    block.dirInfo.ioVRefNum = vRefNum;
    block.dirInfo.ioFDirIndex = -1; /* ignore ioNamePtr as input */
    block.dirInfo.ioDrDirID = ParID;

    err = PBGetCatInfo(&block,false);
	if(err==fnfErr){
	  /* File not found:
	   * If called with a volume name only, this will happen.
	   * Since we assume, that PathNameFromDirID is called only
	   * with legal DirIds, lets assume that it is because it is
	   * a volume name.
	   * And the directorypart of a path consisting of only
	   * a volumename is empty.
	   */
	  return "";
	}
	ParID = block.dirInfo.ioDrParID;
    /* Append a Macintosh style colon (':') to directoryname */
    pStrcat((unsigned char*)directoryName,"\p:");
	/* s = directoryname + s */
    pStrcat((unsigned char*)directoryName,(unsigned char*)s);
    pStrcpy((unsigned char*)s,(unsigned char*)directoryName); 
	//p2cstr(directoryName); fprintf(stderr, "PathNameFromDirID:directoryname is %s\n", directoryName); fflush(stderr);
  } while (block.dirInfo.ioDrDirID != fsRtDirID /*2*/);

  return(s);
}


/** PathNameFromWD ************************************************************/

char *PathNameFromWD(long vRefNum,char *s)
{

  WDPBRec	myBlock;
  OSErr 	err;
  myBlock.ioNamePtr = nil;
  myBlock.ioVRefNum = vRefNum;
  myBlock.ioWDIndex = 0;
  myBlock.ioWDProcID = 0;

  /* Change the Working Directory number in vRefnum into a real vRefnum */
  /* and DirID. The real vRefnum is returned in ioVRefnum, and the real */
  /* DirID is returned in ioWDDirID. */

  err = PBGetWDInfo(&myBlock,false);

  return(PathNameFromDirID(myBlock.ioWDDirID,myBlock.ioWDVRefNum,s));
};

char *getwd(char *s)
{
  short	vRefNum,err;
  Str255	volName;
	
  err = getvol((char*)&volName , &vRefNum);
  PathNameFromWD(vRefNum,s);
  return (s);
}
