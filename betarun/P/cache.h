#ifndef _CACHE_H_
#define _CACHE_H_

#ifndef ppcmac
#include <sys/types.h>
#endif

#include "trie.h"
#include "des.h"

typedef struct castorage {
   Trie *fromCache, *toCache;
   u_long bc; /* blocks in toCache */
   u_long vl; /* log2 block size */
   u_long open;
   u_long miss;
   u_long hit;
   u_long updates;
   DEStorage *des;
} CAStorage;

CAStorage *CAcreate(DEStorage *des);
void CAdestroy(CAStorage *cas);
void CAflush(CAStorage *cas);
void CAload(CAStorage *cas, u_long areaID, char *buffer, u_long offset, u_long nb);
u_long /* area offset */ CAallocate(CAStorage *cas, u_long areaID, u_long nb);
void CAsave(CAStorage *cas, u_long areaID, char *buffer, u_long offset, u_long nb);
u_long CAarea(CAStorage *cas, u_long minSize);
u_long CApresent(CAStorage *cas, u_long areaID, u_long offset);

#endif /* _CACHE_H_ */
