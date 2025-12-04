#include <stdlib.h>
#include <stdio.h>

void main()
{ 
  int base = 0x10200000;
  int adr = 0;
  int i;
  printf("Map: %d %08x base = %d\n",0x00100000,1048576,base);
  for (i = 0; i < 4097; i++)
    { printf("0x%08x: 0x%08x\n",base,adr);
      base = base + 4;
      adr = adr + 0x0100000;
    };
  printf("End of table: %d 0x%08x\n",base,1073741824);
}
