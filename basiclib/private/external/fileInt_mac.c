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

/***** Return variable errno *************/

int getErrno()

{return errno;}

/* Return information about constants that are defined in the
   header files. Such constants may have different values on
   different operating systems
   */

/* Constants giving the mode in which files are opened */ 

int readMode(){return O_RDONLY;}

int readWriteCreateMode(){return O_RDWR | O_CREAT;}

int writeCreateMode(){return O_WRONLY | O_CREAT | O_TRUNC;}

int appendCreateMode(){return O_WRONLY | O_CREAT | O_APPEND;}

int readAppendCreateMode(){return O_WRONLY | O_CREAT | O_APPEND;} 


int EOFpeek(str)
     FILE *str;

{

  /* A dirty and possibly highly machine dependent way of testing for
     EOF. The problem is that the end of a Beta stream is encountered
     when the NEXT char is EOF. It is then necessary to peek into
     the FILE buffer to see if the next char to be read is the EOF
     char. One (obvious) way to do that is to just read the next char
     and then ungetc it back to the stream. The problem with that 
     approach is however that ungetc may provoke deletion of a char 
     if the next opeartion on the stream is fseek. So instead the 
     char is written back by direct manipulation of the FILE buffer.
     _cnt denotes the number of chars left in the buffer and _ptr
     is a pointer into the buffer.
     */

  if(getc(str)==EOF)
    return 1;
  else
    {
      str->_cnt++;
      str->_ptr--;
      return 0;
    }
}

int EOFvalue() { return EOF; }

int EOFfunction(FILE *F) { return feof(F); }


/* ----------------- Functions supporting Stream.GetText -------------------- */

static char *OutOfMemError="Out of memory during StreamGetText\n";

#define INITBUFFERSIZE  500   /* Initial size of Buffer. */

static char *Buffer;          /* Nuffer space allocate here. */
static int  BufferSize=0;     /* Current size of Buffer. */


void InitBuffer()
{
  BufferSize=INITBUFFERSIZE;
  Buffer=(char *)malloc(BufferSize);
  if(!Buffer)
    {
      fputs(OutOfMemError,stderr);
      exit(147);
    }
}


void EnlargeBuffer()
     /* Double the size of Buffer or allocate an initial Buffer. */
{
  BufferSize*=2;
  Buffer=realloc(Buffer,BufferSize);
  if(!Buffer)
    {
      fputs(OutOfMemError,stderr);
      exit(147);
    }
}


static char streamStatus;


int StreamError()
     /* Return whether or not last call to GetTExtFromStream succeeded. */
{
  return(streamStatus==EOF);
}


char *GetTextFromStream(F,toEOL)
     /* Read a string from the file. If toEOL is true then read to end of line,
	else read to first space. Skip the character (eol or space) that causes
	reading to stop.
	Call StreamError afterwards to see if operation succeeded.
	*/
     FILE *F;
     int  toEOL;
{
  register FILE *F1;        /* We use a lot of registers for efficiency. */
  register char *Buffer1;
  register int  i,ch;
  int           oldSize;

  if(!BufferSize)            /* The first time, initialize Buffer. */
    InitBuffer();
  F1=F;
  oldSize=0;                 /* This much of Buffer currently used. */
  if(!toEOL)                 /* Skip to first non-blank. */
    {
      while((ch=getc(F1))<=' ' && ch!=EOF) 
        /* SKIP */ ;
      if(ch==EOF || ungetc(ch,F1)==EOF)
        {
	  streamStatus=ch;
	  return("");
        }
    }
  while(1)
    {
      Buffer1=Buffer+oldSize; /* Insert from this place in Buffer. */
      i=BufferSize-oldSize;
      if(toEOL)               /* We have two almost identical copies of the
                                 inner loop, one reading to eol the other to
                                 a blank.
				 */
        {
	  while(i--)           /* While more room in Buffer. */
	    {
	      if((*Buffer1++=ch=getc(F1))=='\n' || ch==EOF)
		{
		  streamStatus=ch;
		  Buffer1[-1]=0; /* Skip the stop char. */
		  return(Buffer);
		}
	    }
        }
      else
        {
	  while(i--)           /* While more room in Buffer. */
	    {
	      if((*Buffer1++=ch=getc(F1))<=' ' || ch==EOF)
		{
		  streamStatus=ch;
		  Buffer1[-1]=0; /* Skip the stop char. */
		  return(Buffer);
		}
	    }
        }
      oldSize=BufferSize;
      EnlargeBuffer();
    }
}

#define longint long

extern char *pStrcat(unsigned char *s, unsigned char *t);
extern char *pStrcpy(unsigned char *s, unsigned char *t);

short FSpIsDir(FSSpec *fs)
{
  short err; 
  CInfoPBRec      block;
  memset(&block,0,sizeof(CInfoPBRec));
  block.hFileInfo.ioNamePtr = fs->name;
  block.hFileInfo.ioVRefNum = fs->vRefNum;
  block.hFileInfo.ioDirID   = fs->parID;
  err = PBGetCatInfo(&block,false);
  if (err == noErr) 
    if (block.dirInfo.ioFlAttrib & 16) return 1; else return 0;
  else return err;
}

long FSpGetDirID(FSSpec *fs)
{
  short err;
  CInfoPBRec      block;
  memset(&block,0,sizeof(CInfoPBRec));
  block.hFileInfo.ioNamePtr = fs->name;
  block.hFileInfo.ioVRefNum = fs->vRefNum;
  block.hFileInfo.ioDirID   = fs->parID;
  err = PBGetCatInfo(&block,false);
  if (err == noErr) {
    return block.dirInfo.ioDrDirID;
  } else {
    return err;
  }
}

short FSpIsLocked(FSSpec *fs)
{
  short err;
  CInfoPBRec      block;
  memset(&block,0,sizeof(CInfoPBRec));
  block.hFileInfo.ioNamePtr   = fs->name;
  block.hFileInfo.ioVRefNum   = fs->vRefNum;
  block.hFileInfo.ioDirID     = fs->parID;
  err = PBGetCatInfo(&block,false);
  if (err == noErr) {
    if (block.hFileInfo.ioFlAttrib & 1) return 0; else return 1;
  } else {
    return err;
  }
}

long FSpEntryExists(FSSpec *fs)
{
  short err;
  CInfoPBRec      block;
  memset(&block,0,sizeof(CInfoPBRec));
  block.hFileInfo.ioNamePtr   = fs->name;
  block.hFileInfo.ioVRefNum   = fs->vRefNum;
  block.hFileInfo.ioDirID     = fs->parID;
  /* printf("name: %s, vol: %d, parID: %d\n",p2cstr(fs->name), fs->vRefNum, fs->parID); */
  err = PBGetCatInfo(&block,false);
  switch (err) {
  case noErr:    return 1;
  case fnfErr:   return 0;
  case dirNFErr: return 0;
  default:       return err;
  }
}

long FSpGetModTime(FSSpec *fs)
{
  short err;
  unsigned long time;
  CInfoPBRec      block;
  memset(&block,0,sizeof(CInfoPBRec));
  block.hFileInfo.ioNamePtr   = fs->name;
  block.hFileInfo.ioVRefNum   = fs->vRefNum;
  block.hFileInfo.ioDirID     = fs->parID;
  err = PBGetCatInfo(&block,false);
  if (err==noErr) {
    if (block.dirInfo.ioFlAttrib & 16) {
      /* it's a directory */
      time = block.dirInfo.ioDrMdDat;
    } else {
      /* it's a file */
      time = block.hFileInfo.ioFlMdDat;
    }
    return time & ~(1<<31);
  } else {
    errno = err;
    return -1;
  }
}

OSErr FSpEntryTouch(FSSpec *fs)
{
  short           err;
  CInfoPBRec      block;
  unsigned        long secs;

  memset(&block,0,sizeof(CInfoPBRec));
  block.hFileInfo.ioNamePtr = fs->name;
  block.hFileInfo.ioVRefNum = fs->vRefNum;
  block.hFileInfo.ioDirID   = fs->parID;

  err = PBGetCatInfo(&block,false);
  if (err == noErr) {
    GetDateTime(&secs);
    if (block.dirInfo.ioFlAttrib & 16) {
      block.dirInfo.ioDrMdDat = secs;
    } else {
      block.hFileInfo.ioFlMdDat = secs;
    }
    err = PBSetCatInfo(&block,false);
  };
  return err;
}

OSErr FSpEntryRename(FSSpec *fs,char *newname)
{
  OSErr             err;
  CInfoPBRec block;

  memset(&block,0,sizeof(CInfoPBRec));
  c2pstr(newname);
  err = HRename(fs->vRefNum,fs->parID,fs->name,newname);
  if (err == noErr) {
    memset(&fs->name,0,64);
    block.dirInfo.ioVRefNum   = fs->vRefNum;
    block.dirInfo.ioDrDirID   = fs->parID;
    block.dirInfo.ioFDirIndex = -1;
    err = PBGetCatInfo(&block,false);
    if (err == noErr){
      block.dirInfo.ioNamePtr = newname;
      block.dirInfo.ioFDirIndex = 0;
      err = PBGetCatInfo(&block,false);       
      if (err == noErr){
	if (block.dirInfo.ioFlAttrib & 16) {
	  block.dirInfo.ioFDirIndex = -1;
	  err = PBGetCatInfo(&block,false);
	  if (err == noErr){
	    strncpy(&fs->name,block.dirInfo.
		    ioNamePtr,64);
	  }                                       
	  
	} else {
	  Str255 filename;
	  short    i = 0;
	  short    last = 0;

	  while (i <= newname[0]) {
	    i++;
	    if (newname[i] == ':') {
	      last = i;
	    }
	  }
	  i = 1;
	  while (last+i <= newname[0]) {
	    filename[i] = newname[last+i];
	    i++;
	  }
	  memset(&filename,0,256);
	  filename[0] = newname[0]-last;
	  block.hFileInfo.ioVRefNum   = fs->vRefNu
	    m;
	  block.hFileInfo.ioDirID     = fs->parID;
	  block.hFileInfo.ioNamePtr   = newname;
	  block.hFileInfo.ioFDirIndex = 0;
	  err = PBGetCatInfo(&block,false);
	  if (err == noErr){
	    strncpy(&fs->name,block.hFileInfo.ioNamePtr,64);
	  }                                       
	  
	}
      }
    }
  }
  return err;     
}

long CountEntries (long dirID,short vRefNum)
{
  OSErr err;
  short index  = 1;
  long    result = 0;
  CInfoPBRec      block;

  do 
    {
      memset(&block,0,sizeof(CInfoPBRec));
      block.hFileInfo.ioFDirIndex = index;
      block.hFileInfo.ioDirID     = dirID;     
      block.hFileInfo.ioVRefNum   = vRefNum;     
      err = PBGetCatInfo(&block,false);
      if (err == noErr) {
	result++;
	index++;
      }
    } while (err == noErr);
  return result;
} 

StringPtr GetIndEntryName (long Target,short vRefNum,long inx)
{
  OSErr           err;
  CInfoPBRec      block;
  Str255          name;
  long result = 0;

  memset(&block,0,sizeof(CInfoPBRec));
  memset(&name,0,256);
  block.hFileInfo.ioFDirIndex = inx;
  block.hFileInfo.ioDirID     = Target;     
  block.hFileInfo.ioVRefNum   = vRefNum; 
  block.hFileInfo.ioNamePtr   = name;
  err = PBGetCatInfo(&block,false);
  if (err == noErr) {
    return block.hFileInfo.ioNamePtr;
  }
} 

OSErr HMakeFSSpec(short vRefNum,long dirID,char *name,FSSpec *fs)
{ 
  OSErr           err;
  CInfoPBRec      block;
  short                   nofound = 1;
  short                   i = 1;

  memset(&block,0,sizeof(CInfoPBRec));
  c2pstr(name);

  while (i <= name[0] && nofound) {
    if (name[i] == ':' && nofound) {
      nofound = 0;
    }
    i++;    
  }

  if (!nofound && i>2) {          
    /* it's a full path */
    HParamBlockRec  vInfo;
    Str255                  namecopy;       /* changed by PBHGetVInf
					       o */
    memset(&vInfo,0,sizeof(HParamBlockRec));
    strncpy(&namecopy,name,256);
    vInfo.volumeParam.ioNamePtr  = namecopy;
    vInfo.volumeParam.ioVolIndex = -1;
    err = PBHGetVInfo(&vInfo,false);
    if (err == noErr) {
      block.dirInfo.ioNamePtr = name;
      block.dirInfo.ioVRefNum = vInfo.volumeParam.ioVRefNum;
    } else {
      return err;
    }                       
    err = PBGetCatInfo(&block,false);
    if (err == noErr){ 
      block.dirInfo.ioFDirIndex = -1;
      err = PBGetCatInfo(&block,false);
      if (err == noErr){ 
	fs->vRefNum = block.dirInfo.ioVRefNum;
	fs->parID   = block.dirInfo.ioDrParID;
	strncpy(&fs->name,block.dirInfo.ioNamePtr,64);
      } else {
	Str255  filename;
	short           i = 1;
	short           last = 0;
	while (i <= name[0]) {
	  if (name[i] == ':') {
	    last = i;
	  }
	  i++;
	}
	memset(&filename,0,256);
	i = 1;
	while (last+i <= name[0]) {
	  filename[i] = name[last+i];
	  i++;
	}
	filename[0] = name[0]-last;
	block.hFileInfo.ioVRefNum   = block.dirInfo.ioVR
	  efNum;
	block.hFileInfo.ioNamePtr   = name;
	block.hFileInfo.ioFDirIndex = 0;
	err = PBGetCatInfo(&block,false);
	if (err == noErr){
	  fs->vRefNum = block.hFileInfo.ioVRefNum;
	  fs->parID   = block.hFileInfo.ioFlParID;
	  strncpy(&fs->name,&filename,64);
	} else {
	  return err;
	}
      }
    } else {
      OSErr           localerr;
      Str255  parname,entryname;
      short           i = 1;
      short           last = name[0];
      
      while (i <= name[0]) {
	if (name[i] == ':') {
	  last = i;
	}
	i++;
      }
      memset(&parname,0,256);
      memset(&entryname,0,256);
      if (last<name[0]) {
	strncpy(&parname,name,last+1);
	parname[0] = last;
	BlockMove(name+last+1,&entryname,name[0]-last);
      } else {
	BlockMove(name+1,&entryname,name[0]);
      }
      c2pstr(&entryname);
      block.dirInfo.ioNamePtr = &parname;
      localerr = PBGetCatInfo(&block,false);
      if (localerr == noErr){
	fs->vRefNum = block.dirInfo.ioVRefNum;
	fs->parID   = block.dirInfo.ioDrDirID;
	strncpy(&fs->name,&entryname,64);
      } else {
	return localerr;
      }               
    }
  } else {                
    /* it's a partial path */
    if (vRefNum && dirID) {
      block.dirInfo.ioVRefNum = vRefNum;
      block.dirInfo.ioDrDirID = dirID;
    } else {
      WDPBRec wdInfo;
      memset(&wdInfo,0,sizeof(WDPBRec));
      err = PBHGetVol(&wdInfo,false);
      if (err == noErr){
	wdInfo.ioVRefNum = wdInfo.ioWDVRefNum;
	dirID = wdInfo.ioWDDirID;
	err = PBGetWDInfo(&wdInfo,false);
	if (err == noErr){
	  block.dirInfo.ioVRefNum   = wdInfo.ioVRe
	    fNum;
	  block.dirInfo.ioDrDirID   = dirID;
	} else {
	  return err;
	}
      } else {
	return err;
      }
    }
    block.dirInfo.ioFDirIndex = -1;
    err = PBGetCatInfo(&block,false);
    if (err == noErr){
      block.dirInfo.ioNamePtr = name;
      block.dirInfo.ioFDirIndex = 0;
      err = PBGetCatInfo(&block,false);
      if (err == noErr){
	if (block.dirInfo.ioFlAttrib & 16) {
	  block.dirInfo.ioFDirIndex = -1;
	  err = PBGetCatInfo(&block,false);
	  if (err == noErr){
	    fs->vRefNum = block.dirInfo.ioVR
	      efNum;
	    fs->parID   = block.dirInfo.ioDr
	      ParID;
	    strncpy(&fs->name,block.dirInfo.
		    ioNamePtr,64);
	  }                                       
	  
	} else {
	  Str255  filename;
	  short           i = 1;
	  short           last = 0;
	  while (i <= name[0]) {
	    i++;
	    if (name[i] == ':') {
	      last = i;
	    }
	  }
	  memset(&filename,0,256);
	  i = 1;
	  while (last+i <= name[0]) {
	    filename[i] = name[last+i];
	    i++;
	  }
	  filename[0] = name[0]-last;
	  block.hFileInfo.ioVRefNum   = block.dirI
	    nfo.ioVRefNum;
	  block.hFileInfo.ioDirID     = dirID;
	  block.hFileInfo.ioNamePtr   = name;
	  block.hFileInfo.ioFDirIndex = 0;
	  err = PBGetCatInfo(&block,false);
	  if (err == noErr){
	    fs->vRefNum = block.hFileInfo.io
	      VRefNum;
	    fs->parID   = block.hFileInfo.io
	      FlParID;
	    strncpy(&fs->name,&filename,64);
	  }                                       
	  
	}
      } else {
	OSErr           localerr;
	Str255  parname,entryname;
	short           i = 1;
	short           last = name[0];
	
	while (i <= name[0]) {
	  if (name[i] == ':') {
	    last = i;
	  }
	  i++;
	}
	memset(&parname,0,256);
	memset(&entryname,0,256);
	if (last<name[0]) {
	  strncpy(&parname,name,last+1);
	  parname[0] = last;
	  BlockMove(name+last+1,&entryname,name[0]
		    -last);
	} else {
	  BlockMove(name+1,&entryname,name[0]);
	}
	c2pstr(&entryname);
	block.dirInfo.ioNamePtr = &parname;
	localerr = PBGetCatInfo(&block,false);
	if (localerr == noErr){
	  fs->vRefNum = block.dirInfo.ioVRefNum;
	  fs->parID   = block.dirInfo.ioDrDirID;
	  strncpy(&fs->name,&entryname,64);
	} else {
	  block.dirInfo.ioFDirIndex = -1;
	  localerr = PBGetCatInfo(&block,false);
	  if (localerr == noErr){
	    fs->vRefNum = block.dirInfo.ioVR
	      efNum;
	    fs->parID   = block.dirInfo.ioDr
	      DirID;
	    strncpy(&fs->name,&entryname,64)
	      ;
	  };
	}               
      }
    }
  }
  return err;
}
