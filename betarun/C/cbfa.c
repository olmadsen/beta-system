/*
 * BETA RUNTIME SYSTEM, Copyright (C) 1990-94 Mjolner Informatics Aps.
 * cbfa.c
 * by Lars Bak, Peter Andersen, Peter Orbaek, Tommy Thorn, and Jacob Seligmann
 */
#include "beta.h"

void CBFAAlloc()
{
  /* Allocate the Call Back Functions Area. */
  if ( CBFABlockSize < 0 ) {
    char buf[100];
    sprintf(buf, "Too small CBFA specified: %dKb", (int)CBFABlockSize/Kb);
    Notify2(buf, "Check your BETART environment variable");
    exit(1);
  }
  if ( CBFABlockSize == 0 ) {
    INFO_CBFA( Notify2("Warning, CBFA size of 0Kb specified.",
		       "CBFA: Check your BETART environment variable"));
  } else {
#ifdef hppa
    (void) MALLOC(16); /* to avoid spurious bug, with overwriten CBFA */
#endif
    if ( ! (CBFA = cast(CallBackArea) MALLOC(sizeof(struct CallBackArea))) ) {
      Notify("Couldn't allocate CBFA");
      exit(1);
    }
    lastCBFA = CBFA;
    if ( ! (lastCBFA->entries = cast(CallBackEntry) MALLOC(CBFABlockSize)) ) {
      char buf[100];
      sprintf(buf,"Couldn't allocate CBFA (%dKb)\n", (int)CBFABlockSize/Kb);
      Notify(buf);
      exit(1);
    }
    lastCBFA->next = 0;
    CBFATop = lastCBFA->entries;
    CBFALimit = cast(CallBackEntry) ((long) lastCBFA->entries + CBFABlockSize);
  }
  INFO_CBFA( fprintf(output, "#(CBFA: new block allocated %dKb.)\n", 
		     (int)CBFABlockSize/Kb) );
}

void CBFArelloc()
{
  /* BetaError(CBFAfullErr, 0); */
  
  if ( CBFABlockSize == 0 ) {
    Notify2("Using callbacks and CBFA size of 0Kb specified",
	    "Check your BETART environment variable");
    exit(1);
  }
  
  /* Allocate new CBFA block */
  if ( ! (lastCBFA->next = cast(CallBackArea) MALLOC(sizeof(struct CallBackArea))) ) {
    Notify("Couldn't allocate CBFA");
    exit(1);
  }
  lastCBFA = lastCBFA->next;
  if ( ! (lastCBFA->entries = cast(CallBackEntry) MALLOC(CBFABlockSize)) ) {
    char buf[100];
    sprintf(buf,"Couldn't allocate CBFA (%dKb)", (int)CBFABlockSize/Kb);
    Notify(buf);
    exit(1);
  }
  lastCBFA->next = 0;
  CBFATop = lastCBFA->entries;
  CBFALimit = cast(CallBackEntry) ((long) lastCBFA->entries + CBFABlockSize);
  
  INFO_CBFA( fprintf(output, "#(CBFA: new block allocated %dKb.)\n", 
		     (int)CBFABlockSize/Kb) );
}

void freeCBF(external_entry)
     unsigned long external_entry; /* Address of cell just after the ref(Structure) */
{
  /* For now we just clear the struct of the entry  */
  struct CallBackEntry *theCBE 
    = (struct CallBackEntry *)(external_entry - sizeof(struct Structure *));
  
#ifdef RTDEBUG
  Claim(inBetaHeap((ref(Object))(theCBE->theStruct)), 
	"inBetaHeap(theCBE->theStruct)");
#ifdef sparc
  Claim(theCBE->mov_o7_g1 == MOV_O7_G1, 
	"theCBE->mov_o7_g1 is \"mov o7,i7\"");
  Claim((theCBE->call_HandleCallBack & 0xc0000000) == 0x40000000, 
	"theCBE->call_HandleCallBack is \"call\"");
  Claim(theCBE->nop == NOP,
	"theCBE->nop is \"nop\"");
#endif /* sparc */
  Claim(CBFABlockSize != 0, "CBFABlockSize != 0");
  Claim(CBFATop != CBFA->entries, "CBFATop != CBFA->entries");
  
  { ref(CallBackArea) cbfa = CBFA;
    ref(CallBackEntry) current = cbfa->entries;
    long limit = (long) cbfa->entries + CBFABlockSize;
    int found = 0;
    
    for (; current != CBFATop;
	 current=(ref(CallBackEntry))((long)current+CallBackEntrySize)){
      if ( (long) current >= limit){
	/* Go to next block */
	cbfa = cbfa->next;        
	/* guarentied to be non-nil since current != CBFATop */
	
	current = cbfa->entries; 
	/* guarentied to be different from CBFATop. 
	 * If not the block would not have been allocated 
	 */
	limit = (long)cbfa->entries + CBFABlockSize;
      }
      if (theCBE->theStruct == current->theStruct ){
	found = 1;
	break;
      }
    }
    Claim(found, "CallbackEntry is in CBFA");
  }
#endif /* RTDEBUG */
  
  theCBE->theStruct = 0;
  /* theStruct will no longer constitute a root for GC */
  
}

void freeCallbackCalled()
{
  Notify2("Call of Callback function, that has been explicitly freed.",
	  "Ignored.");
}

/* makeCBF: 
 * If the following external is declared in BETA:
 *   makeCBF: External
 *     (# pat: ##external;
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

#ifdef RTDEBUG
void CBFACheck()
{
  if (CBFABlockSize){
    if( CBFATop != CBFA->entries ){
      ref(CallBackArea) cbfa = CBFA;
      ref(CallBackEntry) current = cbfa->entries;
      long limit = (long) cbfa->entries + CBFABlockSize;
      
      for (; current != CBFATop;
	   current = (ref(CallBackEntry))((long)current+CallBackEntrySize)){
	if ( (long) current >= limit){
	  /* Go to next block */
	  cbfa = cbfa->next;        
	  /* guarentied to be non-nil since current != CBFATop */
	  
	  current = cbfa->entries; 
	  
	  /* guarentied to be different from CBFATop. 
	   * If not the block would not have been allocated 
	   */
	  limit = (long)cbfa->entries + CBFABlockSize;
	}
	if (current->theStruct) {
	  Claim(inBetaHeap((ref(Object))(current->theStruct)), 
		"inBetaHeap(current->theStruct)");
	  Claim(inBetaHeap(current->theStruct->iOrigin), 
		"inBetaHeap(current->theStruct->iOrigin)");
	}
      }
    }
  }
}
#endif
