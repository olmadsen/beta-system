#include <Files.h>
#include <Memory.h>
#include <Quickdraw.h>
#include <Windows.h>
#include <StdIO.h>
#include <QDOffscreen.h>


#define Check(error) if(error) goto clean;

int CreateBitmapFromPictureFile (unsigned char *name,BitMapHandle *bitmap,Handle *data);

void BitMapGetSize (BitMapHandle bits,long *width,long *height);

long BitMapGetWidth (BitMapHandle bits);

long BitMapGetHeight (BitMapHandle bits);

void LockPix (BitMapHandle bits,Handle data);

void UnlockPix (BitMapHandle bits,Handle data);

void CreatePixmapFromPictureFile (unsigned char *name,PixMapHandle *pixmap,Handle *data);

void PixMapGetSize (PixMapHandle pixels,long *width,long *height);

long PixMapGetWidth (PixMapHandle pixels);

long PixMapGetHeight (PixMapHandle pixels);

PixPatHandle CreatePixPatFromPixMap (PixMapHandle pixels, Handle data);

void copy_mask_to_window (GWorldPtr src, WindowPtr dst,
						 		  Rect *srcRect, Rect *maskRect, Rect *dstRect,
						 		  BitMap *mask);
								  

void allocate_bitmap(BitMap *bitmap);

RgnHandle CalculateMask (GWorldPtr gworld,int red, int green, int blue);

								  

int CreateBitmapFromPictureFile (unsigned char *name,BitMapHandle *bitmap,Handle *data)
{
	OSErr error = 0;
	short theRefnum = 0;
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
	
	c2pstr(name);
	error = FSOpen(name, (short) 0, &theRefnum);

	Check(error);
	
	error = GetEOF(theRefnum,&file_length);
	Check(error);
	
	
	error = SetFPos(theRefnum,fsFromStart,512);
	Check(error);
	
	pict_size = file_length - 512;
	pict = (PicHandle) NewHandle(pict_size);
	error = MemError();
	Check(error);
	
	error = FSRead(theRefnum,&pict_size,*pict);
	Check(error);
	
	error = FSClose(theRefnum);
	Check(error);
	theRefnum = 0;
	
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
	return 0;
clean:
	(*bitmap) = nil;
	(*data) = nil;
	return error;
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

void CreatePixmapFromPictureFile (unsigned char *name,PixMapHandle *pixmap,Handle *data)
{
	OSErr error = 0;
	short theRefnum = 0;
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
	
	c2pstr(name);
	error = FSOpen(name,0,&theRefnum);
	Check(error);
	
	error = GetEOF(theRefnum,&file_length);
	Check(error);
	
	error = SetFPos(theRefnum,fsFromStart,512);
	Check(error);
	
	pict_size = file_length - 512;
	pict = (PicHandle) NewHandle(pict_size);
	error = MemError();
	Check(error);
	
	error = FSRead(theRefnum,&pict_size,*pict);
	Check(error);
	
	error = FSClose(theRefnum);
	Check(error);
	theRefnum = 0;
	
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

PixPatHandle CreatePixPatFromPixMap (PixMapHandle pixels, Handle data)
{
	PixPatHandle pixPat;
	PixMapHandle patMap;
	Handle patData;
	OSErr error = 0;
	
	pixPat = NewPixPat();
	patMap = (*pixPat)->patMap;
	(*patMap)->rowBytes = (*pixels)->rowBytes;
	(*patMap)->pixelSize = (*pixels)->pixelSize;
	
	patData = (*pixPat)->patData;
	error = PtrToXHand((*data), patData, GetHandleSize(data));
	if (error) {
		SysBeep(1);
	}
	PixPatChanged(pixPat);
	
	return pixPat;
}


void allocate_bitmap(BitMap *bitmap)
{
	short width;
	short height;
	long size;
	
	width = bitmap->bounds.right - bitmap->bounds.left;
	height = bitmap->bounds.bottom - bitmap->bounds.top;
	bitmap->rowBytes = ((((width + 7) >> 3) + 3) >> 2) << 2;
	
	size = height * bitmap->rowBytes;

	bitmap->baseAddr = NewPtr(size);
	return;
}


Boolean EqualRGB (RGBColor *left, RGBColor *right)
{
	if ((left->red >> 11) == (right->red >> 11)) 
		if ((left->green >> 11) == (right->green >> 11)) 
			if ((left->blue >> 11) == (right->blue >> 11))
				return true;
	return false;
}

RgnHandle CalculateMask (GWorldPtr gworld,int red, int green, int blue)
{
	PixMap **pixmap;
	BitMap mask;
	Boolean good;
	Byte *data;
	RGBColor rgb;
	RGBColor seedRGB;

	short right, bottom;
	short left, top;
	long i;
	short h, v;
	RgnHandle rgn;
	
		
	seedRGB.red = red;
	seedRGB.green = green;
	seedRGB.blue = blue;
	
	mask.bounds.left = 0;
	mask.bounds.top = 0;
	mask.bounds.right = (gworld->portRect.right - gworld->portRect.left);
	mask.bounds.bottom = (gworld->portRect.bottom - gworld->portRect.top);
	allocate_bitmap(&mask);
	
	pixmap = GetGWorldPixMap(gworld);
	good = LockPixels(pixmap);
	
	SetPort((GrafPtr) gworld);
	SetOrigin(0, 0);
	
	
	
	if (good) {		
		left = (*pixmap)->bounds.left;
		top = (*pixmap)->bounds.top;
		right = (*pixmap)->bounds.right;
		bottom = (*pixmap)->bounds.bottom;
		
		for (h = 0; h < (right - left); h++) {
			for (v = 0; v < (bottom - top); v++) {
				GetCPixel(h, v, &rgb);
				if (EqualRGB(&rgb, &seedRGB)) {
					BitClr(mask.baseAddr, v * (mask.rowBytes) * 8 + h);
				}
				else {
					BitSet(mask.baseAddr, v * (mask.rowBytes) * 8 + h);
				}
			}
		}

	}
	UnlockPixels(pixmap);
	
	rgn = NewRgn();
	BitMapToRegion(rgn, &mask);
	return rgn;
}


void copy_mask_to_window (GWorldPtr src, WindowPtr dst,
						 		  Rect *srcRect, Rect *maskRect, Rect *dstRect,
						 		  BitMap *mask)
{
	GrafPtr 			asGrafPtr;
	PixMapHandle 	pix;
	Boolean			good;
	
	if (dst != nil && src != nil) {
		pix = GetGWorldPixMap(src);
		good = LockPixels(pix);
		if (good) {
			asGrafPtr = (GrafPtr) src;
			CopyMask((BitMap *) (*pix), mask, &dst->portBits,
					   srcRect, maskRect, dstRect);
		}
		UnlockPixels(pix);
	}
	return;
}

