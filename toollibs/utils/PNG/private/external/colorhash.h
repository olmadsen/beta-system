#ifndef _COLORHASH_H
#define _COLORHASH_H

#include "betaimage.h"

typedef struct ColorHashEntry {
  Color color;
  long index;
  struct ColorHashEntry *next;
} ColorHashEntry;

typedef ColorHashEntry *ColorHashEntryPtr;

typedef struct {
  ColorHashEntryPtr *buckets;
  long nbuckets;
  long count;
  Color special;
  int special_set;
} ColorHash;


void ColorHashInit(ColorHash *hash);
void ColorHashInsert(ColorHash *hash, Color *color);
long  ColorHashLookup(ColorHash *hash, Color *color);
long ColorHashCount(ColorHash *hash);

#endif
