#include "beta.h"

void PrintHeapUsage(char *prompt)
{
  long aoasize, aoablocks, cbfasize, cbfablocks;
  CallBackArea *cbfa;
  Block        *aoa;

  fprintf(output, "Heap usage %s:\n", prompt);
  fprintf(output, 
	  "  IOA:            %8d Kb\n", 
	  (GLOBAL_IOA) ? (int)IOASize/1024 : 0);
  fprintf(output, 
	  "  ToSpace:        %8d Kb\n", 
	  (ToSpace) ? (int)IOASize/1024 : 0);
  
  aoablocks = 0;
  if (AOABaseBlock){
    aoa = AOABaseBlock;
    aoablocks = 1; 
    while (aoa->next){    
      aoablocks++;
       aoa = aoa->next;
    }
  }
#ifdef USEMMAP
  aoasize=(long)AOABaseBlock->limit - (long)BlockStart(AOABaseBlock);
#else
  aoasize=totalAOASize;
#endif
  fprintf(output, 
	  "  AOA:            %8d Kb (%d blocks)\n", 
	  (int)aoasize/1024, 
	  (int)aoablocks);
  fprintf(output, 
	  "  AOAtoIOA table: %8d Kb\n", 
	  (int)AOAtoIOAtableSize*sizeof(long)/1024);
  fflush(output);

  cbfablocks = 0;
  if (CBFA){
    cbfa = CBFA;
    cbfablocks = 1;  
    while (cbfa->next){    
      cbfablocks++; cbfa = cbfa->next; 
    }
  }
  cbfasize=CBFABlockSize*cbfablocks;
  fprintf(output, 
	  "  CBFA:           %8d Kb (%d blocks)\n", 
	  (int)cbfasize/1024,
	  (int)cbfablocks);

  fprintf(output, "\n"); 
  fflush(output);
}

#ifndef MT

typedef int *intptr;

#define GetIOA 0
/* ... */
/* Replicate defines in beta file */

int getHeapInfo(int infoId)
{
  switch (infoId) {
    case 0 :  return (int)IOA;
    case 1 :  return (int)IOALimit;
    case 2 :  return (int)IOATop;
    case 3 :  return (int)IOASize;
    case 4 :  return (int)IOAActive;
    case 5 :  return (IOATop - IOA);
    case 10 : return (int)CBFA;
    case 11 : return (int)CBFALimit;
    case 12 : return (int)CBFATop;
    case 13 : return (int)CBFABlockSize;
    case 15 : return (int)((int)CBFATop - (int)CBFA);
    case 30 : return (int)AOABaseBlock;
    case 31 : return 0; /* (int)AOATopBlock; */
    case 33 : return (int)AOABlockSize;
    case 35 : return (int)totalAOASize;
    case 36 : return (int)AOAFreeListTotalFree();
  default:
    fprintf(output, "getHeapInfo: illegal opcode %d\n", (int)infoId);
    return 0;
  };
}
#endif /* !MT */
