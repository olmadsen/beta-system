/*
 * BETA RUNTIME SYSTEM, Copyright (C) 1990 Mjolner Informatics Aps.
 * Mod: $RCSfile: cbfa.c,v $, rel: %R%, date: $Date: 1992-06-15 15:23:02 $, SID: $Revision: 1.2 $
 * by Lars Bak.
 */
#include "beta.h"

void CBFAAlloc()
{
  /* Allocate the Call Back Functions Area. */
  if ( ! (CBFA = cast(CallBackArea) malloc(sizeof(struct CallBackArea))) ) {
    fprintf(output,"#Beta: Couldn't allocate CBFA\n");
    exit(1);
  }
  lastCBFA = CBFA;
  if ( ! (lastCBFA->entries = cast(CallBackEntry) malloc(CBFABlockSize)) ) {
    fprintf(output,"#Beta: Couldn't allocate CBFA (%dKb)\n", CBFABlockSize/Kb);
    exit(1);
  }
  lastCBFA->next = 0;
  CBFATop = lastCBFA->entries;
  CBFALimit = cast(CallBackEntry) ((long) lastCBFA->entries + CBFABlockSize);
}

void CBFArelloc ()
{
  /* BetaError(-11, 0); */

  /* Allocate new CBFA block */
  if ( ! (CBFA->next = cast(CallBackArea) malloc(sizeof(struct CallBackArea))) ) {
    fprintf(output,"#Beta: Couldn't allocate CBFA\n");
    exit(1);
  }
  lastCBFA = CBFA->next;
  if ( ! (lastCBFA->entries = cast(CallBackEntry) malloc(CBFABlockSize)) ) {
    fprintf(output,"#Beta: Couldn't allocate CBFA (%dKb)\n", CBFABlockSize/Kb);
    exit(1);
  }
  lastCBFA->next = 0;
  CBFATop = lastCBFA->entries;
  CBFALimit = cast(CallBackEntry) ((long) lastCBFA->entries + CBFABlockSize);

  INFO_CBFA( fprintf(output, "#(CBFA: new block allocated %dKb.)\n", CBFABlockSize/Kb); );
}
