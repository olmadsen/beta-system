#include <stdio.h>
#include <stdlib.h>

int Frontbase_getInteger(void *r[],int inx) {
  if (r[inx-1])
    return (*(int*)(r[inx-1]));
  return 0;
}

char* Frontbase_getText(void *r[],int inx) {
  if (r[inx-1])
    return ((char*) r[inx-1]);
  return "";
}

double Frontbase_getReal(void *r[],int inx) {
  if (r[inx-1])
    return (*(double*) r[inx-1]);
  return 0.0;
}

unsigned char Frontbase_getBoolean(void *r[], int inx) {
  if (r[inx-1])
    return (*(unsigned char*) r[inx-1]);
  return '\0';
}

