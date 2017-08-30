#include <string.h>
#include <stdlib.h>

#include "rpi-gpio.h"

/** GPIO Register set */
volatile unsigned int* gpio = (unsigned int*)GPIO_BASE;

/** Main function - we'll never return from here */
void kernel_main( unsigned int r0, unsigned int r1, unsigned int atags )
{
  int loop,cnt;
    unsigned int* counters;

    /* Set the LED GPIO pin to an output to drive the LED */
    //gpio[LED_GPFSEL] |= ( 1 << LED_GPFBIT );
    gpio[0] |= ( 1 << 12 );
    /* Allocate a block of memory for counters */
    counters = malloc( 1024 * sizeof( unsigned int ) );

    /* Failed to allocate memory! */
    if( counters == NULL )
      while(1) { gpio[10] = ( 1 << 4 );}; // LED_ON();/* Trap here */ }

    for( loop=0; loop<1024; loop++ )
      counters[loop] = 0;
    
    /* Never exit as there is no OS to exit to! */
    while(1)
      {
	/* Light the LED */
	gpio[10] = ( 1 << 4 ); //LED_ON();
	
	for(counters[0] = 0; counters[0] < 500000; counters[0]++)
	  ;
	//for (loop =0; loop < 200000; loop++) cnt = cnt + 1;
	/* Set the GPIO16 output low ( Turn OK LED on )*/
	gpio[7] = ( 1 << 4); // LED_OFF();
	
        for(counters[1] = 0; counters[1] < 500000; counters[1]++)
	  ;
	//for (loop =0; loop < 200000; loop++) cnt = cnt + 1;
      }
}
