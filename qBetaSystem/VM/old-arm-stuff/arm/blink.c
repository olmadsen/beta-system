
#include <string.h>
#include <stdlib.h>

#include "rpi-gpio.h"

/** GPIO Register set */
volatile unsigned int* gpio = (unsigned int*)GPIO_BASE;

void blink()
{
    int loop;
    unsigned int* counters;

    /* Set the LED GPIO pin to an output to drive the LED */
    gpio[LED_GPFSEL] |= ( 1 << LED_GPFBIT );

    /* Allocate a block of memory for counters */
    counters = malloc( 1024 * sizeof( unsigned int ) );

    /* Failed to allocate memory! */
    if( counters == NULL )
        while(1) {     LED_ON();/* Trap here */ }

    for( loop=0; loop<1024; loop++ )
        counters[loop] = 0;

    /* Never exit as there is no OS to exit to! */
    while(1)
    {
        /* Light the LED */
        LED_ON();

        for(counters[0] = 0; counters[0] < 500000; counters[0]++)
            ;

        /* Set the GPIO16 output low ( Turn OK LED on )*/
        LED_OFF();

        for(counters[1] = 0; counters[1] < 500000; counters[1]++)
            ;
    }
}
