#include <Quickdraw.h>
#include <QDOffscreen.h>
#include <Files.h>
#include <stdio.h>

GWorldPtr CreateGWorld (short width, short height);

void ClearGWorld (GWorldPtr gworld, short red, short green, short blue);

void CopyWindowToGWorld (WindowPtr src, GWorldPtr dst,
						 Rect *srcRect, Rect *dstRect,
						 short mode, RgnHandle maskRgn);
						 
void CopyGWorldToWindow (GWorldPtr src, WindowPtr dst,
						 Rect *srcRect, Rect *dstRect,
						 short mode, RgnHandle maskRgn);

PicHandle ReadPictureFile (FSSpec *spec);


void DrawPictureInGWorld (PicHandle picture, GWorldPtr gworld, Rect *dstRect);

GWorldPtr GWorldFromPictureFile (FSSpec *spec);

void GetGWorldSize (GWorldPtr gworld, long *width, long *height);


GWorldPtr CreateGWorld (short width, short height)
{
	GWorldPtr gworld;
	QDErr err;
	Rect bounds;
	
	bounds.top = 0;
	bounds.left = 0;
	bounds.right = width;
	bounds.bottom = height;
	
	err = NewGWorld(&gworld, 0, &bounds, nil,  nil, 0);
	if (err == noErr) {
		return gworld;
	}
	else {
		return nil;
	}
}

void ClearGWorld (GWorldPtr gworld, short red, short green, short blue)
{
	RGBColor 		color;
	CGrafPtr 		origPort;
	GDHandle 		origGD;
	Boolean 		good;
	PixMapHandle 	pix;
	
	if (gworld != nil) {
		GetGWorld(&origPort, &origGD);
		SetGWorld(gworld, nil);
		
		pix = GetGWorldPixMap(gworld);
		good = LockPixels(pix);
		if (good) {
			PenNormal();
			color.red = red;
			color.blue = blue;
			color.green = green;
			RGBBackColor(&color);
			EraseRect(&gworld->portRect);
		}
		UnlockPixels(pix);
		SetGWorld(origPort, origGD);
	}
	return;
}


void CopyWindowToGWorld (WindowPtr src, GWorldPtr dst,
						 Rect *srcRect, Rect *dstRect,
						 short mode, RgnHandle maskRgn)
{
	GrafPtr 		asGrafPtr;
	PixMapHandle 	pix;
	Boolean			good;
	
	if (dst != nil && src != nil) {
		pix = GetGWorldPixMap(dst);
		good = LockPixels(pix);
		if (good) {
			asGrafPtr = (GrafPtr) dst;
			CopyBits(&src->portBits, &asGrafPtr->portBits,
					 srcRect, dstRect, mode, maskRgn);
		}
		UnlockPixels(pix);
	}
	return;
}


void CopyGWorldToWindow (GWorldPtr src, WindowPtr dst,
						 Rect *srcRect, Rect *dstRect,
						 short mode, RgnHandle maskRgn)
{
	GrafPtr 		asGrafPtr;
	PixMapHandle 	pix;
	Boolean			good;
	
	if (dst != nil && src != nil) {
		printf("pix = GetGWorldPixMap(src);\n");
		pix = GetGWorldPixMap(src);
		good = LockPixels(pix);
		if (good) {
			asGrafPtr = (GrafPtr) src;
			printf("CopyBits srcRect.top = %d dstRect.top = %d srcRect.bottom = %d dstRect.bottom = %d, dstRect.right = %d\n", 
					srcRect->top, dstRect->top, srcRect->bottom, dstRect->bottom,dstRect->right );
			CopyBits(&asGrafPtr->portBits, &dst->portBits,
					 srcRect, dstRect, mode, maskRgn);
		}
		UnlockPixels(pix);
	}
	return;
}


PicHandle ReadPictureFile (FSSpec *spec)
{
	OSErr 		err;
	OSErr		ignore;
	short 		refNum;
	long 		length;
	long 		size;
	PicHandle  	picture;
	
	err = FSpOpenDF(spec, fsCurPerm, &refNum);
	printf("FSpOpenDF err = %d\n", err);
	if (err == noErr) {
		
		err = GetEOF(refNum, &length);
		printf("GetEOF err = %d\n length = %d\n", err, length);

		if (err == noErr && length > 512) {
			err = SetFPos(refNum, fsFromStart, 512);
			printf("SetFPos err = %d\n", err);
			if (err == noErr) {
				size = length - 512;
				picture = (PicHandle) NewHandle(size);
				if (picture != nil) {
					err = FSRead(refNum, &size, *picture);
					printf("FSRead err = %d\n", err);
					if (err == noErr) {
						ignore = FSClose(refNum);
						return picture;
					}
					else {
						DisposeHandle((Handle) picture);
					}
				}
			}
		}
	}
	else {
		return nil;
	}
	ignore = FSClose(refNum);
	return nil;
}

void DrawPictureInGWorld (PicHandle picture, GWorldPtr gworld, Rect *dstRect)
{
	CGrafPtr 		origPort;
	GDHandle 		origGD;
	Boolean 		good;
	PixMapHandle 	pix;
	
	if (picture != nil && gworld != nil) {
		printf("Drawing on GWorld\n");
		GetGWorld(&origPort, &origGD);
		SetGWorld(gworld, nil);
		
		pix = GetGWorldPixMap(gworld);
		good = LockPixels(pix);
		if (good) {
			printf("Draw picturing\n");
			DrawPicture(picture, dstRect);
		}
		UnlockPixels(pix);
		SetGWorld(origPort, origGD);
	}
}

GWorldPtr GWorldFromPictureFile (FSSpec *spec)
{
	PicHandle picture;
	Rect bounds;
	GWorldPtr gworld;
	
	picture = ReadPictureFile(spec);
	if (picture != nil) {
		bounds = (*picture)->picFrame;
		OffsetRect(&bounds, -bounds.left, -bounds.top);
		gworld = CreateGWorld(bounds.right, bounds.bottom);
		if (gworld != nil) {
			ClearGWorld(gworld, 0xFFFF, 0xFFFF, 0xFFFF);
			DrawPictureInGWorld(picture, gworld, &bounds);
		}
		KillPicture(picture);
	}
	return gworld;
}

void GetGWorldSize (GWorldPtr gworld, long *width, long *height)
{
	if (gworld != nil) {
		(*width) = (gworld->portRect.right - gworld->portRect.left);
		(*height) = (gworld->portRect.bottom - gworld->portRect.top);
	}
	return;
}
