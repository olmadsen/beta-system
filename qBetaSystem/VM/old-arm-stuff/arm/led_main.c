#include <string.h>
#include <stdlib.h>

/** GPIO Register set */
//volatile unsigned int* gpio = (unsigned int*)GPIO_BASE;
int set_led(){
  asm(
      "  mailbox .req r0 @; Alias mailbox to r0\n\t"
      "  ldr mailbox, =0x3f00b880 @; Load the mailbox's base address into r0\n\t"
      
      "wait1$:\n\t"
      "  status .req r1 @; Alias status to r1\n\t"
      "  ldr status, [mailbox, #0x18] @; Load the Mailbox 0 status address\n\t"
      "  tst status, #0x80000000 @; Check the status against the FULL bit\n\t"
      "  .unreq status @; Unset the alias\n\t"
      "  bne wait1$ @; Keep checking the mailbox until it isn't full\n\t"
      
      
      "  message .req r1 @; Alias message to r1\n\t"
      "  ldr message, =PropertyInfo @; Load r1 with address of our message buffer\n\t"
      "  add message, #8 @; Put the channel in the last 4 bits\n\t"
      "  str message, [mailbox, #0x20] @; Put the message in the mailbox\n\t"
      "  .unreq message @; Unset the alias\n\t"     
      "b L\n\t"
      ".align 4 @; This ensures lowest 4 bits are 0 for the following label\n\t"
      "PropertyInfo:\n\t"
      "  @; = Message Header =\n\t"
      "  .int PropertyInfoEnd - PropertyInfo @; Calculate buffer size\n\t"
      "  .int 0 @; Request code: Process Request\n\t"
      "  @; = Tag Header =\n\t"
      "  .int 0x00038041 @; Tag ID (SET_GPIO_STATE)\n\t"
      "  .int 8 @; Value buffer size\n\t"
      "  .int 0 @; Request/response size\n\t"
      "#  @; = Tag Value Buffer =\n\t"
      "  .int 130 @; ACT_LED pin number\n\t"
      "  .int 1 @; Turn it on\n\t"
      "  .int 0 @; End tag\n\t"
      "PropertyInfoEnd:\n\t"
      ".ltorg\n\t"
      "L:\n\t"
      );
};

void kernel_main( unsigned int r0, unsigned int r1, unsigned int atags )
{
    int loop;
    unsigned int* counters, cnt;

    /* Allocate a block of memory for counters */
    // counters = malloc( 1024 * sizeof( unsigned int ) );

    /* Failed to allocate memory! 
    if( counters == NULL )
        while(1) {set_led();/ * Trap here * / }

    for( loop=0; loop<1024; loop++ )
        counters[loop] = 0;
    */
    /* Never exit as there is no OS to exit to! */
    while(1)
    {
        /* Light the LED */
        set_led();

	for (loop = 0; loop < 500000; loop++) cnt = cnt + 1;

        /* Set the GPIO16 output low ( Turn OK LED on )*/
        //clr_led();

	for (loop = 0; loop < 500000; loop++) cnt = cnt + 1;
        //for(counters[1] = 0; counters[1] < 500000; counters[1]++)
    }
}
