#include "colorhash.h"
#include <stdlib.h>

void ColorHashInit(ColorHash *hash)
{ long i;
 
  hash->count = 0;
  hash->nbuckets = 257;
  hash->buckets = (ColorHashEntryPtr *) malloc(hash->nbuckets * sizeof(ColorHashEntryPtr));
  for(i = 0; i < hash->nbuckets; i++) {
    hash->buckets[i] = NULL;
  }
  return;
}

void ColorHashInsert(ColorHash *hash, Color *color)
{
  long index;

  ColorHashEntryPtr current;

  unsigned char r, g, b;

  r = color->red | 0x7;
  g = color->green | 0x7;
  b = color->blue | 0x7;
  

  
  index = (r << 16) | (g << 8) | (b);
  index = index % hash->nbuckets;

  current = hash->buckets[index];
  while(current) {
    if((current->color.red == r) &&
       (current->color.green == g) &&
       (current->color.blue == b))
      {
        return;
      }
    current = current->next;
  }

  current = (ColorHashEntryPtr) malloc(sizeof(ColorHashEntry));
  current->color.red = r;
  current->color.green = g;
  current->color.blue = b;
  
  current->next = hash->buckets[index];
  hash->buckets[index] = current;
  hash->count++;
  return;
}

long ColorHashCount(ColorHash *hash)
{
  return hash->count;
}


long  ColorHashLookup(ColorHash *hash, Color *color)
{
  long index;

  ColorHashEntryPtr current;

  unsigned char r, g, b;
  
  r = color->red | 0x7;
  g = color->green | 0x7;
  b = color->blue | 0x7;
  
  if(hash->special_set) {
    if(hash->special.red == color->red
       || hash->special.green == color->green
       || hash->special.blue == color->blue)
      {
        return 0;
      }
  }

  
  index = (r << 16) | (g << 8) | (b);
  index = index % hash->nbuckets;

  current = hash->buckets[index];
  while(current) {
    if((current->color.red == r) &&
       (current->color.green == g) &&
       (current->color.blue == b))
      {
        if(hash->special_set) {
          return current->index + 1;
        } else {
          return current->index;
        }
      }
    current = current->next;
  }
  return 0;
}
