/* Copyright Mjolner Informatics */

/* Program written by Soren Pingel Dalsgaard */

#include <string.h>
#ifdef nti_bor
#include <alloc.h>
#else
#include <malloc.h>
#endif

char *convert_to_winnt(char *src, char nl)
{
  /* Allocate room for worst case: src is all '\n' */
  char *dst = malloc(strlen(src)*2+1), *ret = dst;
  if (dst) {
    do {
      if (*src == nl) {
        *dst++ = '\r'; *dst++ = '\n';
      } else
        *dst++ = *src;
    } while (*src++);
  }
  return ret;
}

char *convert_from_winnt(char *src, char nl)
{
  /* Allocate room for worst case: no '\n' */
  char *dst = malloc(strlen(src)+1), *ret = dst;
  if (dst) {
    do {
      if (src[0] == '\r' && src[1] == '\n') {
        *dst++ = nl; src++;
      } else
        *dst++ = *src;
    } while (*src++);
  }
  return ret;
}

