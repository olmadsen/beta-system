/*
 * BETA RUNTIME SYSTEM, Copyright (C) 1990 Mjolner Informatics Aps.
 * Mod: $RCSfile: cbfa.c,v $, rel: %R%, date: $Date: 1992-08-27 15:12:23 $, SID: $Revision: 1.4 $
 * by Lars Bak.
 */
#include "beta.h"

void CBFAAlloc()
{
    /* Allocate the Call Back Functions Area. */
    if ( CBFABlockSize < 0 ) {
	fprintf(output,"#Beta: Too small CBFA specified %dKb\n", CBFABlockSize/Kb);
	fprintf(output,"#Beta: Check your BETART environment variable\n");
	exit(1);
    }
    if ( CBFABlockSize == 0 ) {
	INFO_CBFA( fprintf(output,"#CBFA: Warning, CBFA size of 0Kb specified\n"));
	INFO_CBFA( fprintf(output,"#CBFA: Check your BETART environment variable\n"));
    } else {
	if ( ! (CBFA = cast(CallBackArea) MALLOC(sizeof(struct CallBackArea))) ) {
	    fprintf(output,"#Beta: Couldn't allocate CBFA\n");
	    exit(1);
	}
	lastCBFA = CBFA;
	if ( ! (lastCBFA->entries = cast(CallBackEntry) MALLOC(CBFABlockSize)) ) {
	    fprintf(output,"#Beta: Couldn't allocate CBFA (%dKb)\n", CBFABlockSize/Kb);
	    exit(1);
	}
	lastCBFA->next = 0;
	CBFATop = lastCBFA->entries;
	CBFALimit = cast(CallBackEntry) ((long) lastCBFA->entries + CBFABlockSize);
    }
}

void CBFArelloc ()
{
    /* BetaError(-11, 0); */
    
    if ( CBFABlockSize == 0 ) {
	fprintf(output,"#CBFA: Using callbacks and CBFA size of 0Kb specified\n");
	fprintf(output,"#Beta: Check your BETART environment variable\n");
	exit(1);
    }
	
    /* Allocate new CBFA block */
    if ( ! (CBFA->next = cast(CallBackArea) MALLOC(sizeof(struct CallBackArea))) ) {
	fprintf(output,"#Beta: Couldn't allocate CBFA\n");
	exit(1);
    }
    lastCBFA = CBFA->next;
    if ( ! (lastCBFA->entries = cast(CallBackEntry) MALLOC(CBFABlockSize)) ) {
	fprintf(output,"#Beta: Couldn't allocate CBFA (%dKb)\n", CBFABlockSize/Kb);
	exit(1);
    }
    lastCBFA->next = 0;
    CBFATop = lastCBFA->entries;
    CBFALimit = cast(CallBackEntry) ((long) lastCBFA->entries + CBFABlockSize);
    
    INFO_CBFA( fprintf(output, "#(CBFA: new block allocated %dKb.)\n", CBFABlockSize/Kb); );
    
}
