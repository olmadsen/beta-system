#include "header.h"

#define PL011_UART
// *******
//
//    UART AND GPIO UTILITY FUNCTIONS
// 
// *******       

#define IO_BASE 0x3f000000

#ifdef PL011_UART
#define UART0_BASE (IO_BASE + 0x201000)

#define UART0_DR     (*(volatile unsigned *)(UART0_BASE + 0x00))
#define UART0_FR     (*(volatile unsigned *)(UART0_BASE + 0x18))
#define UART0_IBRD   (*(volatile unsigned *)(UART0_BASE + 0x24))
#define UART0_FBRD   (*(volatile unsigned *)(UART0_BASE + 0x28))
#define UART0_LCRH   (*(volatile unsigned *)(UART0_BASE + 0x2C))
#define UART0_CR     (*(volatile unsigned *)(UART0_BASE + 0x30))
#define UART0_IMSC   (*(volatile unsigned *)(UART0_BASE + 0x38))
#define UART0_ICR    (*(volatile unsigned *)(UART0_BASE + 0x44))

#endif

#define GP_BASE (IO_BASE + 0x200000)
#define MU_BASE (IO_BASE + 0x215000)

#define AUX_ENB (*(volatile unsigned *)(MU_BASE + 0x04))
#define MU_IO   (*(volatile unsigned *)(MU_BASE + 0x40))
#define MU_IER  (*(volatile unsigned *)(MU_BASE + 0x44)) // AI-robot
#define MU_IIR  (*(volatile unsigned *)(MU_BASE + 0x48)) // AI-robot
#define MU_LCR  (*(volatile unsigned *)(MU_BASE + 0x4c))
#define MU_LSR  (*(volatile unsigned *)(MU_BASE + 0x54))
#define MU_CNTL (*(volatile unsigned *)(MU_BASE + 0x60))
#define MU_BAUD (*(volatile unsigned *)(MU_BASE + 0x68))

#define GPFSEL0 (*(volatile unsigned *)(GP_BASE + 0x00))
#define GPFSEL1 (*(volatile unsigned *)(GP_BASE + 0x04))
#define GPSET0  (*(volatile unsigned *)(GP_BASE + 0x1C))
#define GPCLR0  (*(volatile unsigned *)(GP_BASE + 0x28))
#define GPLEV0  (*(volatile unsigned *)(GP_BASE + 0x34))
#define GPPUD   (*(volatile unsigned *)(GP_BASE + 0x94))
#define GPPUDCLK0   (*(volatile unsigned *)(GP_BASE + 0x98))


#ifdef PL011_UART
void init_uart(void) {
  int i;

  // Disable UART
  UART0_CR = 0;

  // GPIO14/15 → ALT0 (PL011)
  GPFSEL1 &= ~((7 << 12) | (7 << 15));
  GPFSEL1 |=  (4 << 12) | (4 << 15);  // ALT0

  // Disable pull-up/down
  GPPUD = 0;
  for (i = 0; i < 150; i++) asm volatile ("nop");

  GPPUDCLK0 = (1 << 14) | (1 << 15);
  for (i = 0; i < 150; i++) asm volatile ("nop");

  GPPUDCLK0 = 0;

  // Clear interrupts
  UART0_ICR = 0x7FF;

  // Baud rate = 115200
  // For 48 MHz UART clock:
  // IBRD = 26, FBRD = 3
  UART0_IBRD = 26;
  UART0_FBRD = 3;

  // 8-bit, FIFO enabled
  UART0_LCRH = (1 << 4) | (3 << 5);

  // Enable UART, TX, RX
  UART0_CR = (1 << 0) | (1 << 8) | (1 << 9);
}

#else
void init_uart(void) {
  int i;

  AUX_ENB |= 1;	  /* Enable mini-uart */ 
  MU_CNTL = 0;   // AI-robot MUST disable first
  MU_IER  = 0;   // AI-robot disable interrupts
  MU_LCR = 3;		/* 8 bit.  */
  MU_BAUD = 270;	/* 115200 baud.  */
  MU_IIR  = 0xC6;  // AI-robot clear FIFOs BEFORE enabling

  // GPIO config
  GPFSEL1 &= ~((7 << 12) | (7 << 15));	/* GPIO14 & 15: alt5  */
  GPFSEL1 |= (2 << 12) | (2 << 15);

  /* Disable pull-up/down.  */
  GPPUD = 0;

  for (i = 0; i < 150; i++)
    asm volatile ("nop");

  GPPUDCLK0 = (1 << 14) | (1 << 15); //AI-robot used to be (2 << 14) | (2 << 15); AI-robot

  for (i = 0; i < 150; i++)
    asm volatile ("nop");

  GPPUDCLK0 = 0;

  for (i = 0; i < 150; i++)   // AI-robot
    asm volatile ("nop");

  MU_CNTL = 3;		/* Enable Tx and Rx.  */
}
#endif

static uint8_t put_mutex = 0;

static inline void put_lock() {
  lock_mutex(&put_mutex);
}

static void put_unlock() {
  unlock_mutex(&put_mutex);
}

#ifdef PL011_UART
static void raw_putc(char c) {
  while (UART0_FR & (1 << 5)); // TXFF = FIFO full
  UART0_DR = c;
}

int UART_isReady(){
  return ! (UART0_FR & (1 << 5));
}

char uart_getc() {
  while (UART0_FR & (1 << 4)); // RXFE = empty
  return UART0_DR & 0xFF;
}

#else
static void raw_putc(char c) {
  while (!(MU_LSR & 0x20))
    ;
  MU_IO = c;
}

int UART_isReady(){
  return (MU_LSR & 0x20);
}
#endif

static void raw_putcX(char c) {
  MU_IO = c;
}
static inline void dmb(void)
{
    asm volatile ("dmb ish" ::: "memory");
}

static void _putch(char c) {
  if (c == '\n')
    raw_putc ('\r');
  raw_putc (c);
}
void putch(char c) {
  put_lock();
  _putch(c);
  put_unlock();
  /* new:
  dmb();
  put_lock();
  _putch(c);
  dmb();
  put_unlock();*/
}

#ifdef PL011_UART
char getch(){
  char c;
  put_lock();
  c = uart_getc();
  put_unlock();
  return c;
}
#endif

static void _putstr(const char *s) {
  while (*s)
    _putch (*s++);
}

void putstr(const char *s) {
  //dmb(); // new
  put_lock();
  _putstr(s);
  //dmb(); // new
  put_unlock();
}

static void _puthex(int i) {
  int b;
  for (b=28; b>=0; b-=4) {
    int a = (i>>b) & 0x0f;
    if (a>9) _putch('A'-10+a);
    else _putch('0'+a);
  }
}

void puthex(int i) {
  put_lock();
  _puthex(i);
  put_unlock();
}

void pinMode(int pin, int mode) {
  if (mode) { // output
    (&GPFSEL0)[pin/10] |= (1<<((pin%10)*3));
  } else { // input
    (&GPFSEL0)[pin/10] &= ~(1<<((pin%10)*3));
  }
}

int digitalWrite(int pin, int value) {
  if (value) {
    (&GPSET0)[pin/32] |= (1<<(pin%32));
  } else {
    (&GPCLR0)[pin/32] |= (1<<(pin%32));
  }
  return ((&GPCLR0)[pin/32] & (1<<(pin%32))) ? 1 : 0;
}

void sleep(int C){
  //putstr("sleep:\n");
  while (C > 0) C = C - 1;
  //putstr("end:sleep");
}



// *******
//
//    C RUNTIME STARTUP
// 
// *******       

extern int __bss_start__;
extern int __bss_end__;

// Initialize the C runtime. This is only done once by the first
// core - before the other cores are started.
void _cstartup(void *ftbBlob, unsigned int machType) {
    /*__bss_start__ and __bss_end__ are defined in the linker script */
    int* bss = &__bss_start__;
    int* bss_end = &__bss_end__;

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

    putstr("\n_cstartUp:");
    putstr("\n  bss      : ");
    puthex((int)bss);
    putstr("\n  bss_end  : ");
    puthex((int)bss_end);
    putstr("\n  ftbBlob  : ");
    puthex((int)ftbBlob);
    putstr("\n  machType : ");
    puthex((int)machType);
    putstr("\n\n");
    
    /* We should never return from main - and if we do, the
       core will be put to infinite sleep... */
    main(ftbBlob, machType);
}

