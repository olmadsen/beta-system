#include "beta.h"

typedef int *intptr;
extern long LVRANumOfBlocks;
extern long LVRABaseBlock;

int getHeapInfo(infoId)
int infoId;
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
               int p = LVRABaseBlock;
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
