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


  
  index = (color->red << 16) | (color->green << 8) | (color->blue);
  index = index % hash->nbuckets;

  current = hash->buckets[index];
  while(current) {
    if((current->color.red == color->red) &&
       (current->color.green == color->green) &&
       (current->color.blue == color->blue))
      {
        return;
      }
    current = current->next;
  }

  current = (ColorHashEntryPtr) malloc(sizeof(ColorHashEntry));
  current->color = *color;
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


  if(hash->special_set) {
    if(hash->special.red == color->red
       || hash->special.green == color->green
       || hash->special.blue == color->blue)
      {
        return 0;
      }
  }

  
  index = (color->red << 16) | (color->green << 8) | (color->blue);
  index = index % hash->nbuckets;

  current = hash->buckets[index];
  while(current) {
    if((current->color.red == color->red) &&
       (current->color.green == color->green) &&
       (current->color.blue == color->blue))
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
