// Interpreter main program for ARm on RaspberryPi
//#include <stdbool.h>
#include "interpreter_c.c"
//#include "arm/blink.c"
#include "qbeta_image.c"

extern void start1();
extern void Bfork(void * interpreter, void * B, int coreNo);
extern int cmpAndSwap(int adr, int old, int new); 

void hello(char *S)
{ putstr("Here we are!\n");
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
  int X,V;
  X = 0;
  V = 0;
  init_uart();

  putstr("qbeta is here\n");
  /*
  V = cmpAndSwap((int)&X,0,1);
  if (V) {putstr("Got lock 1st!\n");} else {putstr("Did not get lock 1st!\n");}
  V = cmpAndSwap((int)&X,0,1);
  if (V) {putstr("Got lock 2nd!\n");} else {putstr("Did not get lock 2nd!\n");}
  V = 0; 
  V = cmpAndSwap((int)&X,0,1);
  if (V) {putstr("Got lock 3rd!\n");} else {putstr("Did not get lock 3rd!\n");}
  putstr("Hmm!?\n");
  */
  //beta_fork();
  //start1();
  Bfork(hello,"Hello world\n",1);
  set_descs(BC);
  run_interpreter(1); // isXB = 1 
  getEvent(true); 
  while (1) ;
}

void exit(int no){
  while (1) ;
}
