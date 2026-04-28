#include <sys/stat.h>
//#include "armc-uart.c"
//extern void init_uart(void);

extern int __bss_start__;
extern int __bss_end__;
extern void put32(int adr, int val);
extern void startCore(int adr);
extern void putstr(const char *S);
extern void puthex(int V);
extern void raw_putc(char c);
extern void init_uart();
extern void init_mmu();
extern void init_mmu_x();
extern void kernel_main( unsigned int r0, unsigned int r1, unsigned int atags );


/* Increase program data space. As malloc and related functions depend on this,
   it is useful to have a working implementation. The following suffices for a
   standalone system; it exploits the symbol _end automatically defined by the
   GNU linker. */
caddr_t _sbrk( int incr )
{
    extern char _end;
    static char* heap_end = 0;
    char* prev_heap_end;

    if( heap_end == 0 )
        heap_end = &_end;

     prev_heap_end = heap_end;

     heap_end += incr;
     return (caddr_t)prev_heap_end;
}


void _cstartup( unsigned int r0, unsigned int r1, unsigned int r2 )
{
    /*__bss_start__ and __bss_end__ are defined in the linker script */
    int* bss = &__bss_start__;
    int* bss_end = &__bss_end__;
    int* bss_i = bss;
    /*
        Clear the BSS section

        See http://en.wikipedia.org/wiki/.bss for further information on the
            BSS section

        See https://sourceware.org/newlib/libc.html#Stubs for further
            information on the c-library stubs
    */
    while( bss < bss_end )
        *bss++ = 0;

    init_uart();
    init_mmu();
    putstr("\nAfter init_uart and init_mmu\n");    
    putstr("\n_cstartUp:bss    : ");
    puthex((int)bss_i);
    putstr("\n_cstartUp:bss_end: ");
    puthex((int)bss_end);
    
    /* We should never return from main ... */
    kernel_main( r0, r1, r2 );

    /* ... but if we do, safely trap here */
    while(1)
    {
        /* EMPTY! */
    }
}


void Bfork(void * interpreter, void * B, int coreNo)
{ put32(0x50,(int)interpreter);
  put32(0x40,(int) B);
  raw_putc(100+coreNo);
  switch (coreNo)
    {
    case 1:
      putstr("Bfork core1\n");
      put32(0x60,128000000);
      startCore(0x9C);
      break;
    case 2:
      put32(0x60,256000000);
      startCore(0xAC);
      break;
    case 3:
      put32(0x60,384000000);
      startCore(0xBC);
      break;
    default:
      putstr("coreNo not in 1,2,3\n");
      break;
    }
  
}
