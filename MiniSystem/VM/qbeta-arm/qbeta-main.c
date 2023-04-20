#include "header.h"
extern unsigned char BC[];
extern void put32(int adr, int val);

#define IO_BASE 0x3f000000
#define	GP_BASE (IO_BASE + 0x200000)
#define MU_BASE (IO_BASE + 0x215000)

#define AUX_ENB (*(volatile unsigned *)(MU_BASE + 0x04))
#define MU_IO   (*(volatile unsigned *)(MU_BASE + 0x40))
#define MU_LCR  (*(volatile unsigned *)(MU_BASE + 0x4c))
#define MU_LSR  (*(volatile unsigned *)(MU_BASE + 0x54))
#define MU_CNTL (*(volatile unsigned *)(MU_BASE + 0x60))
#define MU_BAUD (*(volatile unsigned *)(MU_BASE + 0x68))

#define GPFSEL1 (*(volatile unsigned *)(GP_BASE + 0x04))
#define GPPUD   (*(volatile unsigned *)(GP_BASE + 0x94))
#define GPPUDCLK0   (*(volatile unsigned *)(GP_BASE + 0x98)))

int cmpAndSwap(int adr, int old, int new){
}
void raw_putc(char c)
{ while (!(MU_LSR & 0x20))
    ;
  MU_IO = c;
}
extern int startCore(int adr);

#include "../interpreter_c.c"

void putint(int V)
{ int X;
  char d[8];
  int i; 
  for (i = 0; i < 8; i++) d[i] = '0';
  //putch('0');
  //putch('x');
  for (i = 0; i < 8; i++) {
    d[7 - i] = '0' + V % 10;
    V = V / 10;
  }
  for (i = 0; i < 8; i++) {putch(d[i]);}
}


void Bfork(void * interpreter, void * B, int coreNo)
{ put32(0x50,(int)interpreter);
  put32(0x40,(int) B);
  raw_putc(100+coreNo);
  switch (coreNo)
    {
    case 1:
      putstr("Bfork core1\n");
      put32(0x60,128000000);
      //startCore(0x9C);
      if (start_core(interpreter, B, 1)) {
         putstr("Failed startcore ");
         putch('0'+ 0 );
         putch('\n');
      }
      break;
    case 2:
      put32(0x60,256000000);
      startCore(0xAC);
      break;
    case 3:
      put32(0x60,384000000);
      startCore(0xBC);
      break;
    default:
      putstr("coreNo not in 1,2,3\n");
      break;
    }
}
void main(void *ftbBlob, unsigned int machType) {

  putstr("qBeta main is here\n");
  putstr("Once again!\n");
  set_descs(BC);  
  run_interpreter(1); // isXB = 1 
  getEvent(true); 
}

void exit(int no){
  while (1) ;
}
