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

extern int cmpAndSwap(int adr, int old, int new);

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
  volatile static int X,V;
  static int8_t CL = 0;
  putstr("qBeta main is here\n");
  putstr("Once again!\n");

  putstr("Try lock\n");

  lock_mutex(&CL);
  putstr("Got lock\n");
  unlock_mutex(&CL);
  
  putstr("Try cmpAndSwap\n");
  X = 0;
  V = cmpAndSwap((int)&X,0,1);
  if (V) {putstr("Got lock 1st!\n");} else {putstr("Did not get lock 1st!\n");}
  putstr("X: ");
  putint(X);
  putch(10);
  V = cmpAndSwap((int)&X,0,1);
  if (V) {putstr("Got lock 2nd!\n");} else {putstr("Did not get lock 2nd!\n");}
  V = 0; 
  V = cmpAndSwap((int)&X,0,1);
  if (V) {putstr("Got lock 3rd!\n");} else {putstr("Did not get lock 3rd!\n");}
  putstr("Hmm!?\n");
  
  set_descs(BC);  
  run_interpreter(1); // isXB = 1 
  getEvent(true); 
}

void exit(int no){
  while (1) ;
}
