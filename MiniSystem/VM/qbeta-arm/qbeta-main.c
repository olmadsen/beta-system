#include "header.h"
extern unsigned char BC[];

#include "../interpreter_c.c"

void putint(int V)
{ int X;
  char d[8];
  int i; 
  for (i = 0; i < 8; i++) d[i] = '0';
  for (i = 0; i < 8; i++) {
    d[7 - i] = '0' + V % 10;
    V = V / 10;
  }
  for (i = 0; i < 8; i++) {putch(d[i]);}
}

int cmpAndSwap(int adr, int old, int new){
}

void Bfork(void * interpreter, void * B, int coreNo)
{ putstr("Bfork: ");
  putint(coreNo);
  putch('\n');
  if ((0 < coreNo) && (coreNo < 4)){
      if (start_core(interpreter, B, coreNo)) {
         putstr("Failed startcore ");
         putch('0'+ coreNo );
         putch('\n');
      }
  }else{
    putstr("coreNo not in 1,2,3\n");
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
