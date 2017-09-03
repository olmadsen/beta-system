// Interpreter main program for ARm on RaspberryPi
//#include <stdbool.h>
#include "interpreter_c.c"
//#include "arm/blink.c"
#include "qbeta_image.c"

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

  set_descs(BC);
  run_interpreter(1); // isXB = 1 
  getEvent(true); 
  while (1) ;
}

void exit(int no){
  while (1) ;
}
