#include "beta.h"


/* Hej Peter!  
 *
 * Jeg bliver nød til at have denne funktion nedenunder
 * med, ellers kan jeg ikke compilere denne fil uden optimering. Jeg
 * har brug for at kompilere denne fil uden optimering.
 */
void heapview_dummy() {
#ifdef sparc
  USE();
#endif /* sparc */
}

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
  
  aoablocks = 0;aoasize = 0;
  if (AOABaseBlock){
    aoa = AOABaseBlock;
    aoablocks = 0; 
    aoasize = 0;
    while (aoa){    
      aoablocks++;
      aoasize += (long)aoa->limit - (long)BlockStart(aoa);
      aoa = aoa->next;
    }
  }
  fprintf(output, 
          "  AOA:            %8d Kb (%d blocks)\n", 
          (int)aoasize/1024, 
          (int)aoablocks);
  fprintf(output, 
          "  AOAtoIOA table: %8d Kb\n", 
          (int)(AOAtoIOAtableSize*sizeof(long)/1024));
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
          "  CBFA:           %8d Kb (%d blocks, %d entries in use)\n", 
          (int)cbfasize/1024,
          (int)cbfablocks,
          (int)NumCBFAEntries());


  fprintf(output, "\n"); 
  fflush(output);
}

#ifndef MT

typedef int *intptr;
/* constants for diff. heap informations */

#define HeapInfoIOA            0
#define HeapInfoIOALimit       1
#define HeapInfoIOATop         2
#define HeapInfoIOASize        3
#define HeapInfoIOAActive      4
#define HeapInfoIOAspace       5
#define HeapInfoCBFA          10
#define HeapInfoCBFALimit     11
#define HeapInfoCBFATop       12
#define HeapInfoCBFABlockSize 13
#define HeapInfoCBFAsize      15
#define HeapInfoAOABaseBlock  30
#define HeapInfoAOATopBlock   31
#define HeapInfoAOABlockSize  33
#define HeapInfoAOATotalSize  35
#define HeapInfoAOATotalFree  36

int getHeapInfo(int infoId)
{
  switch (infoId) {
    case HeapInfoIOA :  return (int)IOA;
    case HeapInfoIOALimit :  return (int)IOALimit;
    case HeapInfoIOATop :  return (int)IOATop;
    case HeapInfoIOASize :  return (int)IOASize;
    case HeapInfoIOAActive :  return (int)IOAActive;
    case HeapInfoIOAspace :  return (IOATop - IOA);
    case HeapInfoCBFA : return (int)CBFA;
    case HeapInfoCBFALimit : return (int)CBFALimit;
    case HeapInfoCBFATop : return (int)CBFATop;
    case HeapInfoCBFABlockSize : return (int)CBFABlockSize;
    case HeapInfoCBFAsize : return (int)NumCBFAEntries;
    case HeapInfoAOABaseBlock : return (int)AOABaseBlock;
    case HeapInfoAOATopBlock : return  0; /* (int)AOATopBlock; */
    case HeapInfoAOABlockSize : return (int)SECTOR_SIZE;
    case HeapInfoAOATotalSize : return (int)totalAOASize;
    case HeapInfoAOATotalFree : return (int)AOAFreeListTotalFree();
  default:
    fprintf(output, "getHeapInfo: illegal opcode:%d\n",infoId);
    return 0;
  };
}
#endif /* !MT */
