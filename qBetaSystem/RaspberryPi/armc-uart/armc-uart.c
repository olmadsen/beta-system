#include "uart_init.c"

void raw_putc(char c)
{ while (!(MU_LSR & 0x20))
    ;
  MU_IO = c;
}

void putch(char c)
{ if ( c == '\n')
    raw_putc('\r');
  raw_putc(c);
}
#include <string.h>
#include <stdlib.h>

void putstr(const char *s)
{ while (*s) putch(*s++);
}

#define GPIO_BASE       0x3F200000UL

volatile unsigned int* gpio = (unsigned int*)GPIO_BASE;

int pinMode(int pin, int val){
  if (pin == 4){
    gpio[0] |= ( val << 12 );
  };

}

int digitalWrite(int pin, int val){
  if (pin == 4){
    if (val == 1) {
      gpio[10] = ( 1 << 4 ); //LED_ON();
    }else{
      gpio[7] = ( 1 << 4); // LED_OFF();
    }
  }
}

void blink()
{
  int loop,cnt;
  unsigned int* counters;

    /* Set the LED GPIO pin to an output to drive the LED */
    //gpio[LED_GPFSEL] |= ( 1 << LED_GPFBIT );
    //gpio[0] |= ( 1 << 12 );
    pinMode(4,1);
    /* Allocate a block of memory for counters */
    counters = malloc( 1024 * sizeof( unsigned int ) );

    /* Failed to allocate memory! */
    if( counters == NULL )
      while(1) { gpio[10] = ( 1 << 4 );}; // LED_ON();/* Trap here */ }

    for( loop=0; loop<1024; loop++ )
      counters[loop] = 0;
    
    /* Never exit as there is no OS to exit to! */
    for (loop = 0; loop < 10; loop++)
      {
	/* Light the LED */
	// gpio[10] = ( 1 << 4 ); //LED_ON();
	digitalWrite(4,1);

	for(counters[0] = 0; counters[0] < 500000; counters[0]++)
	  ;
	//for (loop =0; loop < 200000; loop++) cnt = cnt + 1;
	/* Set the GPIO16 output low ( Turn OK LED on )*/
	//gpio[7] = ( 1 << 4); // LED_OFF();
	
	digitalWrite(4,0);

        for(counters[1] = 0; counters[1] < 500000; counters[1]++)
	  ;
	//for (loop =0; loop < 200000; loop++) cnt = cnt + 1;
      }
}


int kernel_main( unsigned int r0, unsigned int r1, unsigned int atags )
{ 
  init_uart();

  blink();

  putstr("Hello world\n");
}
