#ifndef _BETAPNG_H
#define _BETAPNG_H
#include "betaimage.h"

#define NoSuchFileError  1
#define WrongFormatError 2
#define MemoryError      3

#define TOP_DOWN 1
#define BOTTOM_UP 2

int BetaReadPNG(char *name, BetaImage *image, int row_order);

#endif
