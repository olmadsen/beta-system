#include "beta.h"

#ifdef PERSIST
#ifndef MAC
#include <sys/types.h>
#endif


#include "storageblock.h"
#include "trie.h"

Trie *toblocks = NULL, *fromblocks = NULL;

void SMinit(void)
{
   fromblocks = TInit();
}

void SMopen(CAStorage *csb)
{
    TInsert((u_long)csb, (u_long)csb, &fromblocks, (u_long)csb);
}

static void freeFunc(u_long current)
{
    CAStorage *csb;
    
    csb = (CAStorage *)current;
    
    if (!SBstat(csb)) {
        /* block is closed */
        
        /* Flush cache */
        CAflush(csb);
        
        /* flush header */
        DESflush(csb -> des);
        
        /* free memory */
        CAdestroy(csb);
    } else {
        TInsert((u_long)csb, (u_long)csb, &toblocks, (u_long)csb);
    }
}

void SMGC()
{
    toblocks = TInit();
    if (fromblocks) {
        TIFree(fromblocks, freeFunc);
    }
    fromblocks = toblocks;
    toblocks = NULL;
}

#endif /* PERSIST */
