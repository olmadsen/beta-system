#include "beta.h"

extern long   LVRANumOfBlocks;
extern struct LVRABlock *LVRABaseBlock;

void PrintHeapUsage(char *prompt)
{
  long aoasize, aoablocks, lvrasize, lvrablocks, cbfasize, cbfablocks;
  struct CallBackArea *cbfa;
  struct LVRABlock    *lvra;
  struct Block        *aoa;

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
  aoasize=AOABlockSize*aoablocks;
  fprintf(output, 
	  "  AOA:            %8d Kb (%d blocks)\n", 
	  (int)aoasize/1024, 
	  (int)aoablocks);
  fprintf(output, 
	  "  AOAtoIOA table: %8d Kb\n", 
	  (int)AOAtoIOAtableSize*sizeof(long)/1024);
  fflush(output);

  lvrablocks = 0; 
  lvrasize = 0;
  if (LVRABaseBlock){
    lvra = LVRABaseBlock;
    lvrablocks = 1; 
    lvrasize = (long)lvra->limit - (long)LVRABlockStart(lvra);
    while (lvra->next){    
       lvrablocks++;
       lvrasize += (long)lvra->limit - (long)LVRABlockStart(lvra);
       lvra = lvra->next;
    }
  }
  fprintf(output, 
	  "  LVRA:           %8d Kb (%d blocks)\n", 
	  (int)lvrasize/1024,
	  (int)lvrablocks);
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
    case 20 : return (int)LVRANumOfBlocks;
    case 23 : return (int)LVRABlockSize;
    case 25 : {
               int p = (int)LVRABaseBlock;
               int count = 0;

               while (p!=0)
                {
                  count +=  (* ((intptr) (p + 8))) - (p+16);
                  p = * (intptr)p;
                };
                return count;
              };
               
    case 30 : return (int)AOABaseBlock;
    case 31 : return (int)AOATopBlock;
    case 33 : return (int)AOABlockSize;
    case 35 : {
               int p = (int)AOABaseBlock;
               int count = 0;

               while (p!=0)
                {
                  count +=  (* ((intptr) (p + 8))) - (p+16);
                  p = * (intptr)p;
                };
                return count;
              };
  default:
    fprintf(output, "getHeapInfo: illegal opcode\n");
    return 0;
  };
}
#endif /* !MT */
