#include "header.h"
void put32(int adr, int val){

}
int cmpAndSwap(int adr, int old, int new){
}
void raw_putc(char c){
}
void startCore(int adr){

}


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
      startCore(0x9C);
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
  
}

void exit(int no){
  while (1) ;
}
