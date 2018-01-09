// Interpreter main program for ARm on RaspberryPi
//#include <stdbool.h>
#include "interpreter_c.c"
//#include "arm/blink.c"
#include "qbeta_image.c"

extern void start1();
extern void Bfork(void * interpreter, void * B, int coreNo);
extern int cmpAndSwap(int adr, int old, int new); 
extern void init_mmu();
extern void init_mmu_s();
extern int __bss_start;
extern int __data_start;

void hello(char *S)
{ putstr("Here we are!\n");
  putstr(S);
}
void yes(char *S)
{
  putstr(S);
}
void bingo(char *S)
{
  putstr(S);
}

void kernel_main( unsigned int r0, unsigned int r1, unsigned int atags )
{ int loop,cnt;
  unsigned int* counters;
//blink();
  /*pinMode(4,1);
  while(1){
    counters = malloc( 1024 * sizeof( unsigned int ) );
    for( loop=0; loop<1024; loop++ )
      counters[loop] = 0;
    //digitalWrite(4,1);
    for(counters[0] = 0; counters[0] < 500000; counters[0]++)
      ;
    digitalWrite(4,0);
    for(counters[1] = 0; counters[1] < 500000; counters[1]++)
      ;
      }
      while(1);
  */
  unsigned int *P;
  volatile int X,V,Q;
  X = 0;
  V = 0;
  P = (unsigned int*)0x10200408; //0x40201008;
  Q = P[0];
  //init_uart();
  //init_mmu_s();
  putstr("\nmmu initiated\n");
  puthex(Q);

  putstr("qbeta is here\n");
  puthex(0); 
  puthex(100);
  puthex(0x01AF);

  puthex((int)&__bss_start);
  puthex((int)&__data_start);
  puthex(64 * 1024 * 1024);

  P = (unsigned int*)0x10200000;
  puthex((int)&P[0]);
  puthex(P[0]);

  P = (unsigned int*)0x102000fc;
  puthex((int)&P[0]);
  puthex(P[0]);

  P = (unsigned int*)0x10200408; //0x40201008;
  puthex((int)&P[0]);
  puthex(P[0]);
  
  X = 0x1234;
  puthex((int)&X);
  puthex(X);
  puthex((&X)[0]);
  //V = __ldrex(&X);  // generates LDREX
  putstr("Try cmpAndSwap\n");
  X = 0;
  //V =__sync_val_compare_and_swap(&X,0,1);
  
  if (V) {putstr("OBS! Got lock 1st!\n");} else {putstr("OBS! Did not get lock 1st!\n");}

  V = cmpAndSwap((int)&X,0,1);
  if (V) {putstr("Got lock 1st!\n");} else {putstr("Did not get lock 1st!\n");}
  V = cmpAndSwap((int)&X,0,1);
  if (V) {putstr("Got lock 2nd!\n");} else {putstr("Did not get lock 2nd!\n");}
  V = 0; 
  V = cmpAndSwap((int)&X,0,1);
  if (V) {putstr("Got lock 3rd!\n");} else {putstr("Did not get lock 3rd!\n");}
  putstr("Hmm!?\n");
  
  //beta_fork(l);
  //start1();
  /*
  int i;
  Bfork(hello,"Hello world\n",1);
  for (i=0; i<100000;i++);
  Bfork(yes,"Yes we can!\n",2);
  for (i=0; i<100000;i++);
  Bfork(bingo,"Bingo!\n",3);
  */
  putstr("Start interpreter\n");
  set_descs(BC);
  run_interpreter(1); // isXB = 1 
  getEvent(true); 
  while (1) ;
}

void exit(int no){
  while (1) ;
}
