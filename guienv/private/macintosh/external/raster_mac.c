#include <files.h>
#include <Memory.h>
#include <Quickdraw.h>
#include <Windows.h>
#include <StdIO.h>

#define Check(error) if(error) goto clean;

void CreateBitmapFromPictureFile (char *name,BitMapHandle *bitmap,Handle *data)
{
	OSErr error = 0;
	short refNum = 0;
	long file_length = 0;
	long pict_size = 0;
	
	PicHandle pict = nil;
	short width = 0;
	short height = 0;
	Rect bounds;
	BitMapHandle bits = nil;
	Handle theData;
	GrafPort port;
	GrafPtr savedport;
	
	error = fsopen(name,0,&refNum);
	Check(error);
	
	error = GetEOF(refNum,&file_length);
	Check(error);
	
	error = SetFPos(refNum,fsFromStart,512);
	Check(error);
	
	pict_size = file_length - 512;
	pict = (PicHandle) NewHandle(pict_size);
	error = MemError();
	Check(error);
	
	error = FSRead(refNum,&pict_size,*pict);
	Check(error);
	
	error = FSClose(refNum);
	Check(error);
	refNum = 0;
	
	width = (**pict).picFrame.right - (**pict).picFrame.left;
	height = (**pict).picFrame.bottom - (**pict).picFrame.top;
	
	bits = (BitMapHandle) NewHandle(sizeof(BitMap));
	error = MemError();
	Check(error);
	
	MoveHHi((Handle) bits);
	HLock((Handle) bits);
	SetRect(&bounds,0,0,width,height);
	(**bits).bounds = bounds;
	(**bits).rowBytes =  ((width + 15) >> 4) << 1;
	theData = NewHandle((**bits).rowBytes * (long) height);
	error = MemError();
	Check(error);
	
	GetPort(&savedport);
	OpenPort(&port);
	port.portRect = bounds;
	RectRgn(port.clipRgn, &bounds);
  	RectRgn(port.visRgn, &bounds);
	MoveHHi(theData);
	HLock(theData);
	(**bits).baseAddr = (*theData);
	SetPortBits((*bits));
	
	DrawPicture(pict,&bounds);
	HUnlock((Handle) bits);
	(**bits).baseAddr = nil;
	HUnlock(theData);
	
	SetPort(savedport);
	ClosePort(&port);
	KillPicture(pict);
	pict = nil;
	
	(*bitmap) = bits;
	(*data) = theData;
	return;
clean:
	(*bitmap) = nil;
	(*data) = nil;
}

void BitMapGetSize (BitMapHandle bits,long *width,long *height)
{
	(*width) = (long) (**bits).bounds.right - (**bits).bounds.left;
	(*height) = (long) (**bits).bounds.bottom - (**bits).bounds.top;
}

long BitMapGetWidth (BitMapHandle bits)
{
	return (**bits).bounds.right - (**bits).bounds.left;
}

long BitMapGetHeight (BitMapHandle bits)
{
	return (**bits).bounds.bottom - (**bits).bounds.top;
}

void LockPix (BitMapHandle bits,Handle data)
{
	MoveHHi(data);
	HLock(data);
	(**bits).baseAddr = (*data);
}

void UnlockPix (BitMapHandle bits,Handle data)
{
	HUnlock(data);
	(**bits).baseAddr = nil;
}

void CreatePixmapFromPictureFile (char *name,PixMapHandle *pixmap,Handle *data)
{
	OSErr error = 0;
	short refNum = 0;
	long file_length = 0;
	long pict_size = 0;
	
	PicHandle pict = nil;
	short width = 0;
	short height = 0;
	Rect bounds;
	PixMapHandle pixels = nil;
	long theDepth, i, offRowBytes;
	GDHandle theMaxDevice, oldDevice;
	CTabHandle    ourCMHandle;
	CGrafPort port;
	PixMapHandle savedPortPix;
	GrafPtr savedport;
	Handle theData;
	
	error = fsopen(name,0,&refNum);
	Check(error);
	
	error = GetEOF(refNum,&file_length);
	Check(error);
	
	error = SetFPos(refNum,fsFromStart,512);
	Check(error);
	
	pict_size = file_length - 512;
	pict = (PicHandle) NewHandle(pict_size);
	error = MemError();
	Check(error);
	
	error = FSRead(refNum,&pict_size,*pict);
	Check(error);
	
	error = FSClose(refNum);
	Check(error);
	refNum = 0;
	
	width = (**pict).picFrame.right - (**pict).picFrame.left;
	height = (**pict).picFrame.bottom - (**pict).picFrame.top;
	
	
	
	oldDevice = GetGDevice();
	theMaxDevice = GetMaxDevice(&(*(GetGrayRgn()))->rgnBBox);
	SetGDevice(theMaxDevice);
	
	pixels =  NewPixMap();
	error = MemError();
	Check(error);
	
	theDepth = (*pixels)->pixelSize;
	SetRect(&bounds,0,0,width,height);
	offRowBytes = (((theDepth * width) + 15) >> 4) << 1;
	(**pixels).bounds = bounds;
	(**pixels).rowBytes =  offRowBytes + 0x8000;
	theData = NewHandle(offRowBytes * (long) height);
	error = MemError();
	Check(error);
	
	ourCMHandle = (**(**theMaxDevice).gdPMap).pmTable;
   error = HandToHand(&((Handle) ourCMHandle));
	Check(error);
	
	for (i = 0; i <= (**ourCMHandle ).ctSize; ++i)
        (**ourCMHandle ).ctTable[i].value = i;
    (**ourCMHandle ).ctFlags &= 0x7fff;
    (**ourCMHandle ).ctSeed = GetCTSeed();
    /* This code is necessary for converting GDevice cluts to Pixmap cluts */

    (**pixels).pmTable = ourCMHandle;
	
	GetPort(&savedport);
	OpenCPort(&port);
	port.portRect = bounds;
	RectRgn(port.clipRgn, &bounds);
  	RectRgn(port.visRgn, &bounds);
	savedPortPix = port.portPixMap;
	LockPix((BitMapHandle) pixels,theData);
	SetPortPix(pixels);
	
	DrawPicture(pict,&bounds);
	SetPortPix(savedPortPix);
	UnlockPix((BitMapHandle) pixels,theData);
	SetPort(savedport);
	CloseCPort(&port);
	KillPicture(pict);
	pict = nil;

	(*pixmap) = pixels;
	(*data) = theData;
	return;
clean:
	(*pixmap) = nil;
	(*data) = nil;
}

void PixMapGetSize (PixMapHandle pixels,long *width,long *height)
{
	(*width) = (long) (**pixels).bounds.right - (**pixels).bounds.left;
	(*height) = (long) (**pixels).bounds.bottom - (**pixels).bounds.top;
}

long PixMapGetWidth (PixMapHandle pixels)
{
	return (**pixels).bounds.right - (**pixels).bounds.left;
}

long PixMapGetHeight (PixMapHandle pixels)
{
	return (**pixels).bounds.bottom - (**pixels).bounds.top;
}