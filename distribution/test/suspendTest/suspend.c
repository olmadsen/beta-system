#include <stdio.h>

typedef void (*callback) (int,int,int);     
callback gcb;

void recursive (int level)
{ 
  fprintf (stderr, "recursive %d\n", level);
  if (level) 
    recursive (level-1);
  else
    gcb (1,2,3);
  fprintf (stderr, "recursive %d\n", level);
}

void installCallback (callback cb)
{
  gcb = cb;
  recursive (5);
}


