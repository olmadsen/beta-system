#include <QuickDraw.h>
#include <Memory.h>
#include <QuickdrawText.h>
#include <QDOffscreen.h>
#include <StdIO.h>

#include <agl.h>

extern GLboolean mglUseFont(GLint fontID, GLint face, GLint size, GLint first, GLint count, GLint base)
{
	GrafPtr 	port;
	GrafPtr		savedPort;
	FontInfo	info;
	
	short		width, height;
	short		x, y;
	
	long 		datasize;
	int			from, i;
	
	char		*source;
	char		*dest;
	
	Rect 		gworldBounds;
	
	Rect		bounds;
	PixMap		**pix;
	
	GLint 		inx;
	short		ch;
	short 		xmove;
	OSErr		err;
	BitMap		bitmap;
	
	GLubyte		*glbitmap;
	
	GWorldPtr 	gworld;
	CGrafPtr		savedport;
	GDHandle	gdh;
	
	Boolean 	good;
		
	gworldBounds.top = 0;
	gworldBounds.left = 0;
	gworldBounds.right = 100;
	gworldBounds.bottom = 100;
	
	err = NewGWorld(&gworld, 0, &gworldBounds, nil,  nil, 0);
		
	pix = GetGWorldPixMap(gworld);
	good = LockPixels(pix);
	
	GetGWorld(&savedport, &gdh);
	SetGWorld(gworld, nil);
	
	
	TextFont(fontID);
	TextFace(face);
	TextSize(size);
	
	GetFontInfo(&info);
	
	SetGWorld(savedport, gdh);
	
	width = info.widMax + 10;
	height = info.ascent + info.descent;
	
	x = 0;
	y = info.descent;
	
	
	
	SetRect(&bitmap.bounds, 0, 0, width, height);
	bitmap.rowBytes = ((((width + 7) >> 3) + 3) >> 2) << 2;
	datasize = height * bitmap.rowBytes;
	bitmap.baseAddr = NewPtr(datasize);
	
	
	SetRect(&bounds, 0, 0, width, height);
	HLock((Handle) pix);
	
	
	for (inx = 0; inx < count; inx++) {
		GetGWorld(&savedport, &gdh);
		SetGWorld(gworld, nil);
		EraseRect(&bounds);
		ch = first + inx;
		
		MoveTo(x, info.ascent);
		DrawChar(ch);
		xmove = CharWidth(ch);
		SetGWorld(savedport, gdh);
		
		glbitmap = (GLubyte *) NewPtr(datasize);
				
		CopyBits((BitMap *) (*pix), &bitmap, &bounds, &bounds, 0, 0);		
		
		source = (char *) bitmap.baseAddr;
		dest = (char *) glbitmap;
		
		
		for (from = 0; from < height; from++) {
			int to = height - 1 - from;
			
			printf("from = %d to = %d\n", from, to);
			
			BlockMove((Ptr) (bitmap.baseAddr + from * bitmap.rowBytes),
					  (Ptr) (glbitmap + to*bitmap.rowBytes),
					  bitmap.rowBytes);
		}
		
		glNewList(base + inx, GL_COMPILE);
			glBitmap(width, height, 0, y, xmove, 0, glbitmap);
		glEndList();
	}
	
	return GL_TRUE;
}

