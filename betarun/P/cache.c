#include "beta.h"

#ifdef PERSIST
#ifndef MAC
#include <sys/types.h>
#endif
#include <string.h>

#include "trie.h"
#include "des.h"
#include "cache.h"
#include "PSfile.h"

#define MAXBLOCKSALLOWED 128
#define CASCLEAN 0
#define CASDIRTY 1

/* Local function definitions 
 */
static void visitFunc(contentsBox *current);
static void flushFromCache(CAStorage *csb);
static void flushToCache(CAStorage *csb);
static void freeFunc(unsigned long block);
static u_long log2(u_long x);
static void load(char *buffer, char *cb, u_long offset, u_long nb);
static void save(char *buffer, char *cb, u_long offset, u_long nb);
static void loadsave(CAStorage *cas, 
		     u_long areaID, 
		     char *buffer, 
		     u_long offset, 
		     u_long nb,
		     void (*func)(char *, char *, u_long, u_long));

/* local variables */

/* Public operations on storage caches
 */

CAStorage *CAcreate(DEStorage *des)
{
    CAStorage *cas=(CAStorage *)malloc(sizeof(struct castorage));
  
    cas -> toCache = TInit();
    cas -> fromCache = TInit();
    cas -> bc = 0;
    cas -> des = des;
    cas -> vl = log2(preferredBufferSize(des -> fd));
    cas -> hit = 0;
    cas -> miss = 0;
    cas -> updates = 0; /* are not saved in on disk */
    
    if (DEFAULTTABLESIZE > ((1 << cas -> vl) - 1)) {
        perror("CAcreate: Cannot create unique block keys in 32 bits");
    }
  
    return cas;
}

void CAdestroy(CAStorage *cas)
{
  if (cas) {
    if (cas -> toCache) {
      TIFree(cas -> toCache, freeFunc);
    } else {
      fprintf(stderr, "CAdestroy toCache failed: NULL cas->toCache\n");
    }
    if (cas -> fromCache) {
      TIFree(cas -> fromCache, freeFunc);
    } else {
      fprintf(stderr, "CAdestroy fromCache failed: NULL cas->fromCache\n");
    }
    if (cas -> des) {
      DESdestroy(cas -> des);
    } else {
      fprintf(stderr, "CAdestroy des failed: NULL cas->des\n");
    }
    /*fprintf(stderr, "cas miss: %8d\n", (int)(cas -> miss));
      fprintf(stderr, "cas hit : %8d\n", (int)(cas -> hit));*/
    free(cas);
  } else {
    fprintf(stderr, "CAdestroy failed: NULL cas\n");
  }
}

void CAflush(CAStorage *cas)
{
  if (cas) {
    flushFromCache(cas);
    flushToCache(cas);
  } else {
    fprintf(stderr, "CAflush failed: NULL cas\n");
  }
}

u_long CAarea(CAStorage *cas,
              u_long minSize)
{
  /* Make sure that the size of the area is a multiple of the
   * preferred buffer size.
   */
  /*fprintf(output, "CAarea: minsize before: 0x%08x\n", (int)minSize);*/
  /*fprintf(output, "CAarea: cas -> vl: 0x%08x\n", (int)cas -> vl);*/
  minSize = (minSize >> (cas -> vl)) << (cas -> vl);
  minSize += 1 << (cas -> vl);
  /*fprintf(output, "CAarea: minsize after: 0x%08x\n", (int)minSize);*/
  
  return DESarea(cas -> des, minSize);
}

u_long /* area offset */ CAallocate(CAStorage *cas,
                                    u_long areaID,
                                    u_long nb)
{
    /* When allocating space we do not want this space to cross block
     * boundaries. If there is not enough space in the current block
     * of the area, then the top pointer is forwarded to the start of
     * the next block. Still, if what is requested for allocation is
     * larger than a block size the allocation cannot but cross block
     * boundaries. In such a case we have still achieved that the area
     * starts at the beginning of a block.
     */
    return DESallocate(cas -> des, areaID, nb, cas -> vl);
}

void CAload(CAStorage *cas, u_long areaID, char *buffer, u_long offset, u_long nb)
{
   loadsave(cas, areaID, buffer, offset, nb, load);
}

void CAsave(CAStorage *cas, u_long areaID, char *buffer, u_long offset, u_long nb)
{
#ifdef DEBUGPERSISTENCE
   {
      u_long current;

      fprintf(output, "CAsave: 0x%8X, ", (int)offset);
      
      for (current = 0; current < nb; current++) {
         fprintf(output, "0x%X ", (int)buffer[current]);
      }
      fprintf(output, "\n");
   }
#endif /* DEBUGPERSISTENCE */

   loadsave(cas, areaID, buffer, offset, nb, save);
   cas -> updates += 1;
}

/* Private utility operations */

static void load(char *buffer, char *cb, u_long offset, u_long nb)
{
    memcpy(buffer, cb + offset, nb);
}

static void save(char *buffer, char *cb, u_long offset, u_long nb)
{
    *(u_long *)((u_long)cb - sizeof(u_long)) = CASDIRTY;
    memcpy(cb + offset, buffer, nb);
}

static void loadsave(CAStorage *cas, 
		     u_long areaID, 
		     char *buffer, 
		     u_long offset, 
		     u_long nb,
		     void (*func)(char *, char *, u_long, u_long))
{
    u_long key, mask;
    char *cb;
    
    mask = (1 << cas -> vl) - 1;
    key = (offset & ~mask) | areaID;
    
    
    /* Use key to lookup cache */
    if ((cb = (char *)TILookup(key, cas -> fromCache)) ||
        (cb = (char *)TILookup(key, cas -> toCache))) {
        u_long offsetInBlock;

        /* Cache hit */
        cas -> hit += 1;
        
        offsetInBlock = offset & mask;
        
        if (offsetInBlock + nb <= ((u_long)1 << cas -> vl)) {
            func(buffer, cb, offsetInBlock, nb);
        } else {
            /* Request for read/write across block boundaries. */
            perror("loadsave: Cross block boundry load not implemented");
        }
    } else {
        /* Cache miss */
        cas -> miss += 1;
        if (cas -> bc < MAXBLOCKSALLOWED) {
            cb = (char *)calloc((1 << (cas -> vl)) + sizeof(u_long), sizeof(char));
            
            *cb = CASCLEAN;
            cb += sizeof(u_long);
            
            DESload(cas -> des, areaID, cb, offset & ~mask, (1 << (cas -> vl)));
      
            /* insert loaded block in toCache */
            TInsert(key, (u_long)cb, &(cas -> toCache), key);
            cas -> bc += 1;
        } else {
            flushFromCache(cas);
            TIFree(cas -> fromCache, freeFunc);
            cas -> fromCache = cas -> toCache;
            cas -> toCache = TInit();
            cas -> bc = 0;
        }
        loadsave(cas, areaID, buffer, offset, nb, func);
    }
}

u_long CApresent(CAStorage *cas, u_long areaID, u_long offset)
{
    u_long key, mask;
    char *cb;
    
    mask = (1 << cas -> vl) - 1;
    key = (offset & ~mask) | areaID;
    
    
    /* Use key to lookup cache */
    if ((cb = (char *)TILookup(key, cas -> fromCache)) ||
        (cb = (char *)TILookup(key, cas -> toCache))) {
        return 1;
    } else {
        return 0;
    }
}
    
/* Local function declarations */
static CAStorage *currentcsb;

static void visitFunc(contentsBox *current) 
{
    u_long offset, areaID, mask;

#if 1
    char *cb;
    
    cb = (char *)(current -> contents);
    if (*((u_long *)((u_long)cb - sizeof(u_long))) == CASDIRTY) {
#endif
        mask = (1 << currentcsb -> vl) - 1;
        
        offset = current -> key & ~mask;
        areaID = current -> key & mask;
        
        DESsave(currentcsb -> des,
                areaID,
                (char *)(current -> contents),
                offset,
                1 << (currentcsb -> vl));
#if 1
    }
#endif
}
    
static void flushFromCache(CAStorage *csb)
{
    currentcsb = csb;
    if (currentcsb -> fromCache) {
      TIVisit(currentcsb -> fromCache, visitFunc);
    } else {
      fprintf(stderr, "flushFromCache failed: NULL currentcsb->fromCache\n");
    }
}

static void flushToCache(CAStorage *csb)
{
    currentcsb = csb;
    if (currentcsb -> toCache) {
      TIVisit(currentcsb -> toCache, visitFunc);
    } else {
      fprintf(stderr, "flushToCache failed: NULL currentcsb->toCache\n");
    }
}


static void freeFunc(unsigned long block)
{
    free((char *)((u_long)block - sizeof(u_long)));
}

static u_long log2(u_long x)
{
    u_long k;
  
    /* calculates the highest number k, where 1 << k <= x */
    k = 0;
  
    while (x) {
        x = x >> 1;
        k = k + 1;
    }
  
    return k - 1;
}

#endif /* PERSIST */  
