#include <betapng.h>
#include <QDOffscreen.h>

int readPNG(char *name, GWorldPtr *gworld)
{
	int result;
	BetaImage image;
	
	Rect box;
	
	result = BetaReadPNG(name, &image, 1);
	
	if(result != 0) {
		return result;
	}
	
	box.left = 0;
	box.top = 0;
	box.right = image.width;
	bot.bottom = image.height;
	
	result = NewGWorld(gworld, 24, &box, nil, nil, 0);
	
	
	return 0;
}
