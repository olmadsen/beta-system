/*
 * BETA RUNTIME SYSTEM, Copyright (C) 1990-93 Mjolner Informatics Aps.
 * cbfa.c
 * by Lars Bak, Peter Andersen, Peter Orbaek and Tommy Thorn.
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
#ifdef hppa
	(void) MALLOC(16); /* to avoid spurious bug, with overwriten CBFA */
#endif
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
    INFO_CBFA( fprintf(output, "#(CBFA: new block allocated %dKb.)\n", CBFABlockSize/Kb); );
}

void CBFArelloc()
{
    /* BetaError(CBFAfullErr, 0); */
    
    if ( CBFABlockSize == 0 ) {
	fprintf(output,"#CBFA: Using callbacks and CBFA size of 0Kb specified\n");
	fprintf(output,"#Beta: Check your BETART environment variable\n");
	exit(1);
    }
	
    /* Allocate new CBFA block */
    if ( ! (lastCBFA->next = cast(CallBackArea) MALLOC(sizeof(struct CallBackArea))) ) {
	fprintf(output,"#Beta: Couldn't allocate CBFA\n");
	exit(1);
    }
    lastCBFA = lastCBFA->next;
    if ( ! (lastCBFA->entries = cast(CallBackEntry) MALLOC(CBFABlockSize)) ) {
	fprintf(output,"#Beta: Couldn't allocate CBFA (%dKb)\n", CBFABlockSize/Kb);
	exit(1);
    }
    lastCBFA->next = 0;
    CBFATop = lastCBFA->entries;
    CBFALimit = cast(CallBackEntry) ((long) lastCBFA->entries + CBFABlockSize);
    
    INFO_CBFA( fprintf(output, "#(CBFA: new block allocated %dKb.)\n", CBFABlockSize/Kb); );
}

void freeCBF(cb)
     ref(CallBackEntry) cb;
{
  /* For now we just clear the entry */
  cb->theStruct = 0; /* theStruct will no longer constitute a root for GC */
}

/* makeCBF: 
 * If the following external is declared in BETA:
 *   makeCBF: External
 *     (# pat: ##Object;
 *        cb: @integer;
 *     enter pat##
 *     exit cb
 *     #);
 *   P: (# ... CExternalEntry; ... #);
 *   ptr: @integer;
 * then the call 
 *   P## -> makeCBF -> ptr;
 * will install a callback to P through ptr.
 * ptr may then be handled to an external, that may call back.
 * Later ptr may be freed using freeCBF.
 */
ref(CallBackEntry) makeCBF(pat)
     ref(CallBackEntry) pat;
{
  return pat
    /* All casts are done by the BETA compiler, which calls CopyCPP */;
}
