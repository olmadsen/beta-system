// Interpreter main program for ARM on RaspberryPi
//#include <stdbool.h>
#include "interpreter_c.c"
//#include "arm/blink.c"
//#include "qbeta_image.c"
//#include "ArmLed_bc.c"

extern void start1();
extern void Bfork(void * interpreter, void * B, int coreNo);
extern int cmpAndSwap(int adr, int old, int new); 
//extern void init_mmu();
//extern void init_mmu_s();
extern int _start;
extern int _end;
extern int __bss_start;
extern int __data_start;
extern int _edata;
extern int __bss_end__;
extern int ttb0_base;
extern int ttb1_base;
extern int level2_pagetable;
extern int pagetable_macro;
extern unsigned char BC[];

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
  unsigned int *A;
  volatile int X,V,Q;
  int i;
  X = 0;
  V = 0;
  P = (unsigned int*)0x10200408; //0x40201008;
  Q = P[0];
  //init_uart();
  //init_mmu_s();
  //putstr("\nAfter init-mmu\n");
  //puthex(Q);

  putstr("\n\n**** qbeta is here ****\n");
  putstr("\n_start      : ");
  puthex((int)&_start);
  
  putstr("\n__data_start: ");
  puthex((int)&__data_start);
  putstr("\n_edata      : ");  
  puthex((int)&_edata);  
  putstr("\n__bss_start : ");
  puthex((int)&__bss_start);
  putstr("\n__bss_end__ : ");
  puthex((int)&__bss_end__);  
  putstr("\n_end        : ");
  puthex((int)&_end);  
  putch('\n');

  putstr("\nTTL: \nttb0_base: ");
  puthex((int)&ttb0_base);
  putstr(" length: ");
  putint(4096);
  putch('\n');
  A = (unsigned int*) &ttb0_base;
  putstr("Pagetable_start:\n");
  for (i = 0; i < 8; i++) {
      puthex((int)&A[i]);
      putch(':');
      puthex(A[i]);
      putch('\n');
  }
  /*
  A = (unsigned int*) &pagetable_macro;
  putstr("\nPagetable_macro:\n");
  for (i = 0; i < 8; i++) {
      puthex((int)&A[i]);
      putch(':');
      puthex(A[i]);
      putch('\n');
  }
  A = (unsigned int*) &ttb1_base; //level2_pagetable;
  putstr("Level2_pagetable:\n");
  for (i = 0; i < 512; i++) {
    if ((i < 3) || (508 < i)) {
      puthex((int)&A[i]);
      putch(':');
      puthex(A[i]);
      putch('\n');
    }
    if (i == 4) putstr("...\n");
    }
  */
  X = 0x1234;
  putstr("&X,X, X[0]:");
  puthex((int)&X);
  putch(',');
  puthex(X);
  putch(',');
  puthex((&X)[0]);
  putch('\n');
  
  //V = __ldrex(&X);  // generates LDREX

  /* V =__sync_val_compare_and_swap(&X,0,1);
  if (V) {putstr("OBS! Got lock 1st!\n");}
  else
    {putstr("OBS! Did not get lock 1st!\n");}
  */
  
  putstr("Try cmpAndSwap\n");
  X = 0;
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
