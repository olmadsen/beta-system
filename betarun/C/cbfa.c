/*
 * BETA RUNTIME SYSTEM, Copyright (C) 1990-94 Mjolner Informatics Aps.
 * cbfa.c
 * by Lars Bak, Peter Andersen, Peter Orbaek, Tommy Thorn, and Jacob Seligmann
 */
#include "beta.h"

/* Pointer to the last Call Back Functions Area. */
GLOBAL(static ref(CallBackArea) lastCBFA = 0);  


void CBFAalloc()
{
  /* Allocate the Call Back Functions Area. */
  if ( CBFABlockSize < 0 ) {
    char buf[100];
    sprintf(buf, "Too small CBFA specified: %dKb", (int)CBFABlockSize/Kb);
    Notify2(buf, "Check your BETART environment variable");
    BetaExit(1);
  }
  if ( CBFABlockSize == 0 ) {
    INFO_CBFA( Notify2("Warning, CBFA size of 0Kb specified.",
		       "Check your BETART environment variable"));
  } else {
#ifdef hppa
    (void) MALLOC(16); /* to avoid spurious bug, with overwriten CBFA */
#endif
    if ( ! (CBFA = cast(CallBackArea) MALLOC(sizeof(struct CallBackArea))) ) {
      char buf[300];
      sprintf(buf, "%s: Cannot allocate CBFA", ArgVector[0]);
      Notify(buf);
      BetaExit(1);
    }
    lastCBFA = CBFA;
    if ( ! (lastCBFA->entries = cast(CallBackEntry) MALLOC(CBFABlockSize)) ) {
      char buf[300];
      sprintf(buf,
	      "%s: Cannot allocate the CBFA heap (%dKb)\n", 
	      ArgVector[0],
	      (int)CBFABlockSize/Kb);
#ifdef MAC
      EnlargeMacHeap(buf);
#endif
      Notify(buf);
      BetaExit(1);
    }
    lastCBFA->next = 0;
    CBFATop = lastCBFA->entries;
    CBFALimit = cast(CallBackEntry) ((long) lastCBFA->entries + CBFABlockSize);
  }
  INFO_CBFA(fprintf(output, "#(CBFA: new block allocated %dKb.)\n", 
		    (int)CBFABlockSize/Kb) );
  INFO_HEAP_USAGE(PrintHeapUsage("after CBFA allocation"));
}

void CBFArelloc()
{
  
  if ( CBFABlockSize == 0 ) {
    Notify2("Using callbacks and CBFA size of 0Kb specified",
	    "Check your BETART environment variable");
    BetaExit(1);
  }

  /* We can claim that top must equal limit since the block size
   * is now adjusted to be an integral number of entries in
   * initialize.c.
   */
  DEBUG_CBFA(Claim((CBFATop==CBFALimit),"CBFATop==CBFALimit"));

  /* Allocate new CBFA block */
  if ( ! (lastCBFA->next = cast(CallBackArea) MALLOC(sizeof(struct CallBackArea))) ) {
    char buf[300];
    sprintf(buf, "%s: Cannot allocate CBFA", ArgVector[0]);
    Notify(buf);
    BetaExit(1);
  }
  lastCBFA = lastCBFA->next;
  if ( ! (lastCBFA->entries = cast(CallBackEntry) MALLOC(CBFABlockSize)) ) {
    char buf[100];
    sprintf(buf,
	    "%s: Cannot allocate CBFA (%dKb)", 
	    ArgVector[0],
	    (int)CBFABlockSize/Kb);
    Notify(buf);
    BetaExit(1);
  }
  lastCBFA->next = 0;
  CBFATop = lastCBFA->entries;
  CBFALimit = cast(CallBackEntry) ((long) lastCBFA->entries + CBFABlockSize);
  
  INFO_CBFA(fprintf(output, "#(CBFA: new block allocated %dKb.)\n", 
		    (int)CBFABlockSize/Kb) );
  INFO_HEAP_USAGE(PrintHeapUsage("after CBFA reallocation"));

  return;
}

void freeCBF(external_entry)
     unsigned long external_entry; /* Address of cell just after the ref(Structure) */
{
  /* For now we just clear the struct of the entry  */
  struct CallBackEntry *theCBE;

  if (!external_entry){
    DEBUG_CODE(fprintf(output, "freeCBF: external_entry is NULL\n");
	       fflush(output));
    return;
  }
  
  theCBE 
    = (struct CallBackEntry *)(external_entry - sizeof(struct Structure *));
#ifdef RTDEBUG
  Claim(inBetaHeap((ref(Object))(theCBE->theStruct)), 
	"inBetaHeap(theCBE->theStruct)");
#ifndef MT
#ifdef sparc
  Claim(theCBE->mov_o7_g1 == MOV_O7_G1, 
	"theCBE->mov_o7_g1 is \"mov o7,i7\"");
  Claim((theCBE->call_HandleCallBack & 0xc0000000) == 0x40000000, 
	"theCBE->call_HandleCallBack is \"call\"");
  Claim(theCBE->nop == NOP,
	"theCBE->nop is \"nop\"");
#endif /* sparc */
#endif /* MT */
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
	/*DEBUG_CBFA(fprintf(output, "CBFACheck: current=0x%x", current));*/
	if (current->theStruct) {
	  /*DEBUG_CBFA(fprintf(output, "\n"));*/
	  Claim(inBetaHeap((ref(Object))(current->theStruct)), 
		"inBetaHeap(current->theStruct)");
	  Claim(inBetaHeap(current->theStruct->iOrigin), 
		"inBetaHeap(current->theStruct->iOrigin)");
	} else {
	  /*DEBUG_CBFA(fprintf(output, " (free)\n"));*/
	}
      }
    }
  }
}
void PrintCBFA()
{
  int numBlock=0;
  int numEntry=0;
  
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
	  numBlock++;
	  fprintf(output, "CBFA Block %d:\n", numBlock);
	  /* guarentied to be non-nil since current != CBFATop */
	  
	  current = cbfa->entries; 
	  
	  /* guarentied to be different from CBFATop. 
	   * If not the block would not have been allocated 
	   */
	  limit = (long)cbfa->entries + CBFABlockSize;
	}
	numEntry++;
	fprintf(output, "Entry no %d: 0x%x\n", (int)numEntry, (int)current);
	fprintf(output, "  theStruct: 0x%08x: 0x%08x ", 
		(int)&current->theStruct, (int)current->theStruct);
	if ((current->theStruct) 
	    && inBetaHeap((ref(Object))(current->theStruct))
	    && inBetaHeap(current->theStruct->iOrigin)){
	  fprintf(output, "(OK)\n");
	} else {
	  fprintf(output, "(NOT OK!)\n");
	}
	fprintf(output, "  code:\n");
	{ int i;
	  for (i=1; i<CallBackEntrySize/sizeof(long); i++){
	    fprintf(output, "             0x%08x: 0x%08x\n", 
		    (int)((long*)current+i), (int)*((long*)current+i));
	  }
	}
      }
    }
  }
}
#endif
