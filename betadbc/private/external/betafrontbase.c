#include <stdio.h>
#include <stdlib.h>

int Frontbase_getInteger(void *r[],int inx)
{
  return (*(int*)(r[inx-1]));
}

char* Frontbase_getText(void *r[],int inx)
{
  return ((char*) r[inx-1]);
}

double Frontbase_getReal(void *r[],int inx)
{
  return (*(double*) r[inx-1]);
}

unsigned char Frontbase_getBoolean(void *r[], int inx)
{
  return (*(unsigned char*) r[inx-1]);
}

