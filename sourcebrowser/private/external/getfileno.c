#include <stdio.h>
#include <unistd.h>

int getfileno (FILE* f)
{
  return fileno(f);
}  
