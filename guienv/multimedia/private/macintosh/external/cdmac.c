

#include    <ToolUtils.h>
#include    <Memory.h>
#include    <Errors.h>
#include    <Files.h>
#include    <Devices.h>

#define csDiscStatus    8
#define csWhoIsThere    97
#define csReadTOC       100
#define csReadQ         101
#define csATrkSearch    103
#define csAPlay         104
#define csAPause        105
#define csAStop         106
#define csAStatus       107
#define csAScan         108

#define BLOCKADDR       0
#define MSFADDR         1
#define TRACKADDR       2

#define TOCTRACKS       1
#define TOCENDOFDISK    2
#define TOCSTARTADDR    3

#define STEREO          9
#define MONO            15

#define START           0
#define STOP            1

#define PAUSE           1
#define CONTINUE        0

#define PLAYING         0
#define PAUSED          1

//typedef   unsigned char   Byte;
typedef unsigned short  Word;
typedef unsigned long   Long;


#define ParamBlockHdr \
 QElemPtr qLink;    				/*queue link in header*/\
 short qType;    					/*type byte for safety check*/\
 short ioTrap;    					/*FS: the Trap*/\
 Ptr ioCmdAddr;    					/*FS: address to dispatch to*/\
 ProcPtr ioCompletion;  			/*completion routine addr (0 for synch calls)*/\
 OSErr ioResult;    				/*result code*/\
 StringPtr ioNamePtr;  				/*ptr to Vol:FileName string*/\
 short ioVRefNum   				/*volume refnum (DrvNum for Eject and MountVol)*/
 
pascal  Byte Decimal2BCD(Byte n) {
    return ((n / 10) << 4) + (n % 10); 
}

pascal  Byte BCD2Decimal(Byte n) {
    return ((n >> 4) * 10) + (n & 0x0f);
}


typedef struct ReadTOCRec {
    ParamBlockHdr;
    short       ioRefNum;
    short       csCode;
    union {
        Word    type;
        Byte    addr[3];
        struct {
            Word    fill;
            Long    data;
            Word    length;
            Byte    track;
        } buffer;
    } csParam;
} ReadTOCRec;


typedef struct DiscStatusRec {
    ParamBlockHdr;
    short       ioRefNum;
    short       csCode;
    struct {
        Word    track;
        Byte    writeProtect;
        Byte    discInPlace;
        Byte    installed;
        Byte    side;
        Long    qLink;
        Word    qType;
        Word    dQDrive;
        Word    dQRefNum;
        Word    dQFSID;
        Byte    twoSideFormat;
        Byte    needsFlush;
        Byte    diskErrs;
    } csParam;
} DiscStatusRec;

typedef struct {
    Byte        cntlField;
    Byte        minutes;
    Byte        seconds;
    Byte        frames;
} StartAddrRec;


typedef struct AStatusRec {
    ParamBlockHdr;
    short       ioRefNum;
    short       csCode;
    struct {
        Byte    audioStatus;
        Byte    playMode;
        Byte    cntlField;
        Byte    minutes;
        Byte    seconds;
        Byte    frames;
    } csParam;
} AStatusRec;



typedef struct AScanRec {
    ParamBlockHdr;
    short       ioRefNum;
    short       csCode;
    struct {
        Word    type;
        Byte    addr[4];
        Word    direction;
    } csParam;
} AScanRec;

typedef struct ATrkSearchRec {
    ParamBlockHdr;
    short       ioRefNum;
    short       csCode;
    struct {
        Word    type;
        Byte    addr[4];
        Word    playFlag;
        Byte    fill;
        Byte    playMode;
    } csParam;
} ATrkSearchRec;


OSErr TrackCount(short ioRefNum, long *stopTrack) {

    auto    OSErr           osErr;
    auto    ReadTOCRec      *pb;

    pb = (ReadTOCRec *) NewPtrClear(sizeof (*pb));
    osErr = MemError();
    if (0 != pb && noErr == osErr) {
        (*pb).ioRefNum          = ioRefNum;
        (*pb).csCode            = csReadTOC;
        (*pb).csParam.type      = 1;
        osErr = PBControl((ParmBlkPtr)pb, false);
        if (noErr == osErr) {
            *stopTrack          = BCD2Decimal((*pb).csParam.addr[1]);
        }
        DisposePtr((Ptr) pb);
    }
    return osErr;
}

OSErr DiscLength(short ioRefNum, long *length)
{
	auto    OSErr           osErr;
    auto    ReadTOCRec      *pb;
	
	Byte minutes;
	Byte seconds;
	Byte frames;
	

    pb = (ReadTOCRec *) NewPtrClear(sizeof (*pb));
    osErr = MemError();
    if (0 != pb && noErr == osErr) {
        (*pb).ioRefNum          = ioRefNum;
        (*pb).csCode            = csReadTOC;
        (*pb).csParam.type      = 2;
        osErr = PBControl((ParmBlkPtr)pb, false);
		
        if (noErr == osErr) {
            minutes = BCD2Decimal((*pb).csParam.addr[0]);
			seconds  = BCD2Decimal((*pb).csParam.addr[1]);
			frames  = BCD2Decimal((*pb).csParam.addr[2]);
			
			*length = minutes * 60000 + seconds * 1000 + (frames * 1000) / 70;
        }
        DisposePtr((Ptr) pb);
    }
    return osErr;
}


OSErr DiscStatus(short ioRefNum, long *discInPlace) {

    auto    OSErr           osErr;
    auto    DiscStatusRec   *pb;    

    pb = (DiscStatusRec *) NewPtrClear(sizeof (*pb));
    osErr = MemError();
    if (0 != pb && noErr == osErr) {
        (*pb).ioRefNum          = ioRefNum;
        (*pb).csCode            = csDiscStatus;
        osErr = PBStatus((ParmBlkPtr)pb, false);
        if (noErr == osErr)
            *discInPlace = (1 == (*pb).csParam.discInPlace);
        DisposePtr((Ptr) pb);
    }
    return osErr;
}


OSErr TrackInfo(short ioRefNum, Byte track, Byte *cntlField, Byte *minutes, Byte *seconds, Byte *frames) {

    auto    OSErr           osErr;
    auto    ReadTOCRec      *pb;
    
    pb = (ReadTOCRec *) NewPtrClear(sizeof (*pb));
    osErr = MemError();
    if (0 != pb && noErr == osErr) {
        (*pb).ioRefNum                  = ioRefNum;
        (*pb).csCode                    = csReadTOC;
        (*pb).csParam.type              = 3;
        (*pb).csParam.buffer.data       = (Long) NewPtrClear(sizeof (StartAddrRec));
        osErr = MemError();
        if (0 != (*pb).csParam.buffer.data && noErr == osErr) {
            (*pb).csParam.buffer.length     = sizeof(StartAddrRec);
            (*pb).csParam.buffer.track      = Decimal2BCD(track);
            osErr = PBControl((ParmBlkPtr)pb, false);
            if (noErr == osErr) {
                *cntlField      = (*(StartAddrRec *)(*pb).csParam.buffer.data).cntlField;
                *minutes        = BCD2Decimal((*(StartAddrRec *)(*pb).csParam.buffer.data).minutes);
                *seconds        = BCD2Decimal((*(StartAddrRec *)(*pb).csParam.buffer.data).seconds);
                *frames         = BCD2Decimal((*(StartAddrRec *)(*pb).csParam.buffer.data).frames);
            }
            DisposePtr((Ptr) (*pb).csParam.buffer.data);
        }
        DisposePtr((Ptr) pb);
    }
    return osErr;
}


OSErr TrackStart(short ioRefNum, Byte Track, long *milliseconds)
{
	Byte cntlField;
	Byte minutes;
	Byte seconds;
	Byte frames;
	OSErr err;
	
	err = TrackInfo(ioRefNum, Track, &cntlField, &minutes, &seconds, &frames);
	if (err) {
		return err;
	}
	*milliseconds = minutes * 60000 + seconds * 1000 + (frames * 1000) / 70;
	return noErr;
}

OSErr AStatus(short ioRefNum, Byte *audioStatus, Byte *playMode, Byte *cntlField, Byte *minutes, Byte *seconds, Byte *frames) {

    auto    OSErr           osErr;
    auto    AStatusRec      *pb;

    pb = (AStatusRec *) NewPtrClear(sizeof (*pb));
    osErr = MemError();
    if (0 != pb && noErr == osErr) {
        (*pb).ioRefNum              = ioRefNum;
        (*pb).csCode                = csAStatus;
        osErr = PBControl((ParmBlkPtr)pb, false);
        if (noErr == osErr) {
            *audioStatus        = (*pb).csParam.audioStatus;
            *playMode           = (*pb).csParam.playMode;
            *cntlField          = (*pb).csParam.cntlField;
            *minutes            = BCD2Decimal((*pb).csParam.minutes);
            *seconds            = BCD2Decimal((*pb).csParam.seconds);
            *frames             = BCD2Decimal((*pb).csParam.frames);
        }
        DisposePtr((Ptr) pb);
    }
    return osErr;
}


OSErr CurrentPosition(short ioRefNum, long *milliseconds)
{
	Byte audioStatus;
	Byte playMode;
	Byte cntlField;
	Byte minutes;
	Byte seconds;
	Byte frames;
	OSErr err;
	
	err = AStatus(ioRefNum, &audioStatus, &playMode, &cntlField, &minutes, &seconds, &frames);
	
	if (err) {
		return err;
	}
	
	*milliseconds = minutes * 60000 + seconds * 1000 + (frames * 1000) / 70;
	
	return noErr;
}



OSErr CurrentTrack (short ioRefNum, Byte *track)
{

    auto    OSErr           osErr;
    auto    DiscStatusRec   *pb;    

    pb = (DiscStatusRec *) NewPtrClear(sizeof (*pb));
    osErr = MemError();
    if (0 != pb && noErr == osErr) {
        (*pb).ioRefNum          = ioRefNum;
        (*pb).csCode            = csDiscStatus;
        osErr = PBStatus((ParmBlkPtr)pb, false);
        if (noErr == osErr)
            *track = (*pb).csParam.track;
        DisposePtr((Ptr) pb);
    }
    return osErr;
}



OSErr ATrkSearch(short ioRefNum, Byte track, Byte playFlag, Byte playMode) {

    auto    OSErr           osErr;
    auto    ATrkSearchRec   *pb;    

    pb = (ATrkSearchRec *) NewPtrClear(sizeof (*pb));
    osErr = MemError();
    if (0 != pb && noErr == osErr) {
        (*pb).ioRefNum          = ioRefNum;
        (*pb).csCode            = csATrkSearch;
        (*pb).csParam.type      = TRACKADDR;
        (*pb).csParam.addr[3]   = Decimal2BCD(track);
        (*pb).csParam.playFlag  = playFlag;
        (*pb).csParam.playMode  = playMode;
        osErr = PBControl((ParmBlkPtr)pb, false);
        DisposePtr((Ptr) pb);
    }
    return osErr;
}

OSErr ATrkSearch2(short ioRefNum, Byte minutes, Byte seconds, Byte frames, Byte playFlag, Byte playMode) {

    auto    OSErr           osErr;
    auto    ATrkSearchRec   *pb;    

    pb = (ATrkSearchRec *) NewPtrClear(sizeof (*pb));
    osErr = MemError();
    if (0 != pb && noErr == osErr) {
        (*pb).ioRefNum          = ioRefNum;
        (*pb).csCode            = csATrkSearch;
        (*pb).csParam.type      = MSFADDR;
		(*pb).csParam.addr[1]   = Decimal2BCD(minutes);
        (*pb).csParam.addr[2]   = Decimal2BCD(seconds);
        (*pb).csParam.addr[3]   = Decimal2BCD(frames);       
		(*pb).csParam.playFlag  = playFlag;
        (*pb).csParam.playMode  = playMode;
        osErr = PBControl((ParmBlkPtr)pb, false);
        DisposePtr((Ptr) pb);
    }
    return osErr;
}


OSErr  AScan(short ioRefNum, Byte minutes, Byte seconds, Byte frames, Byte direction) {

    auto    OSErr           osErr;
    auto    AScanRec        *pb;    

    pb = (AScanRec *) NewPtrClear(sizeof (*pb));
    osErr = MemError();
    if (0 != pb && noErr == osErr) {
        (*pb).ioRefNum          = ioRefNum;
        (*pb).csCode            = csAScan;
        (*pb).csParam.type      = MSFADDR;
        (*pb).csParam.addr[1]   = Decimal2BCD(minutes);
        (*pb).csParam.addr[2]   = Decimal2BCD(seconds);
        (*pb).csParam.addr[3]   = Decimal2BCD(frames);
        (*pb).csParam.direction = direction;
        osErr = PBControl((ParmBlkPtr)pb, false);
        DisposePtr((Ptr) pb);
    }
    return osErr;
}

OSErr SetCurrentPosition(short ioRefNum, Byte track, long milli)
{
	Byte audioStatus;
	Byte playMode;
	Byte cntlField;
	Byte minutes;
	Byte seconds;
	Byte frames;
	Byte play;
	long current;
	long start;
	long amount;
	
	
	
	OSErr err;
	
	err = AStatus(ioRefNum, &audioStatus, &playMode, &cntlField, &minutes, &seconds, &frames);
	
	if (err) {
		return err;
	}
		
	if (audioStatus == 0) {
		play = 1;
	}
	else {
		play = 0;
	}
	
	err = TrackStart(ioRefNum, track, &start);
	
	if (err) {
		return err;
	}
	
	start += milli;
		
	minutes = start / 60000;
	seconds = (start - (minutes * 60000)) / 1000;
	frames = ((start - (minutes * 60000) - (seconds * 1000)) * 70) / 1000; 
	
		
	err = ATrkSearch2(ioRefNum, minutes, seconds, frames, play, playMode);
	
	return err;
}

