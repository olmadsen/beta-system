#include <string.h>
#include <stdlib.h>
#include <stdio.h>

void *memmove(void *t, const void *s, size_t n);
void *memmove(void *t, const void *s, size_t n)
{
 static int size = 0;
 static void *tmp = NULL;
 if (size < n) {
    if (tmp != NULL)
       free(tmp);
    if ((tmp = malloc(size = n)) == NULL) {
       fprintf(stderr,
	       "Sorry, out of memory in memmove() clone, aborting...\n");
       exit(1);
    }
  }
 memcpy(tmp, s, n);
 memcpy(t, tmp, n);
}
