#include <betapng.h>
#include <QuickDraw.h>
#include <QDOffscreen.h>

static void BetaSwapBig(BetaImage *image)
{
  unsigned char *row;
  unsigned char *pixel;

  int i, j;

  unsigned char r, g, b, a;

  row = image->data;

  for(j = 0; j < image->height; j++) {
    pixel = row;
    for(i = 0; i < image->width; i++) {
      r = pixel[0];
      g = pixel[1];
      b = pixel[2];
      a = pixel[3];

      
      pixel[0] = a;
      pixel[1] = r;
      pixel[2] = g; 
      pixel[3] = b;

      pixel += 4;
    }
    row += image->rowbytes;
  }
}



RgnHandle BuildMask(BetaImage *image)
{
	BitMap mask;
	unsigned char a;
	
	int i, j;
	RgnHandle rgn;
	unsigned char *row;
	unsigned char *pixel;
			
	mask.bounds.left = 0;
	mask.bounds.top = 0;
	mask.bounds.right = image->width;
	mask.bounds.bottom = image->height;
	allocate_bitmap(&mask);
		
	row = image->data;
	for (j = 0; j < image->height; j++) {
		pixel = row;
		for (i = 0; i < image->width; i++) {
			a = pixel[3];
			if (a < 200) {
				BitClr(mask.baseAddr, j * (mask.rowBytes) * 8 + i);
			}
			else {
					BitSet(mask.baseAddr, j * (mask.rowBytes) * 8 + i);
			}
			pixel+=4;
		}
		row += image->rowbytes;
	}
	rgn = NewRgn();
	BitMapToRegion(rgn, &mask);
	DisposePtr(mask.baseAddr);
	return rgn;
}

int readPNG(char *name, GWorldPtr *gworld, RgnHandle *maskrgn)
{
	int 			result;
	BetaImage 		image;
	PixMapHandle	dstPixMap;
	
	
	long	dstRowBytes;
	char	*dst;
	
	long	srcRowBytes;
	char	*src;
	int		j;
	
	
	
	Rect box;
	
	result = BetaReadPNG(name, &image, 1);
	
	if(result != 0) {
		return result;
	}
	
	*maskrgn = BuildMask(&image);
	
	
	box.left = 0;
	box.top = 0;
	box.right = image.width;
	box.bottom = image.height;
	
	result = NewGWorld(gworld, 24, &box, NULL, NULL, 0);
	
	dstPixMap = GetGWorldPixMap(*gworld);
	dst = GetPixBaseAddr(dstPixMap);
	dstRowBytes = (long) (**dstPixMap).rowBytes & 0x7fff;
	
	
	
	BetaSwapBig(&image);
	
	src = image.data;
	srcRowBytes = image.rowbytes;
	
	for(j = 0; j < image.height; j++) {
		BlockMove(src, dst, srcRowBytes);
		src += srcRowBytes;
		dst += dstRowBytes;
	}
	
	return 0;
}
