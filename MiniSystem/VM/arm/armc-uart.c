#define IO_BASE 0x3f000000
#define	GP_BASE (IO_BASE + 0x200000)
#define MU_BASE (IO_BASE + 0x215000)

#define AUX_ENB (*(volatile unsigned *)(MU_BASE + 0x04))
#define MU_IO   (*(volatile unsigned *)(MU_BASE + 0x40))
#define MU_LCR  (*(volatile unsigned *)(MU_BASE + 0x4c))
#define MU_LSR  (*(volatile unsigned *)(MU_BASE + 0x54))
#define MU_CNTL (*(volatile unsigned *)(MU_BASE + 0x60))
#define MU_BAUD (*(volatile unsigned *)(MU_BASE + 0x68))

#define GPFSEL1 (*(volatile unsigned *)(GP_BASE + 0x04))
#define GPPUD   (*(volatile unsigned *)(GP_BASE + 0x94))
#define GPPUDCLK0   (*(volatile unsigned *)(GP_BASE + 0x98))

void init_uart(void)
{ int i;

  AUX_ENB |= 1;     /* Enable mini-uart */
  MU_LCR = 3;       /* 8 bit */
  MU_BAUD =270;     /* 115200 baud.*/
  GPFSEL1 &= ~((7 << 12) | (7 << 15)); /* GPIO14 & 15: alt 5 */
  GPFSEL1 |= (2 << 12) | (2 << 15);

  /* Disable pull-up/down. */
  GPPUD = 0;
  for (i = 0; i < 150; i++)
    asm volatile ("nop");
  GPPUDCLK0 = (2 << 14) | (2 << 15);
  for (i = 0; i < 150; i++)
    asm volatile ("nop");
  GPPUDCLK0 = 0;

  MU_CNTL = 3; /* Enable Tx and Rx */
}


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
void puthex(int V)
{ int X;
  char d[8];
  int i; 
  for (i = 0; i < 8; i++) d[i] = '0';
  putch('0');
  putch('x');
  if (V > 0) 
    { i = 8;
      while (V > 0)
	{ X = V % 16;
	  i = i - 1;
	  if (X < 10) { d[i] = '0' + X;}
	  else
	    { d[i] = 'A' - 10 + X;
	    };
	  V = V / 16;
	};
    };
  for (i = 0; i < 8; i++) {putch(d[i]);}
  putch('\n');
}
#include <string.h>
#include <stdlib.h>

void putstr(const char *s)
{ while (*s) putch(*s++);
}

void beta_fork()
{
  putstr("beta_fork\n");
}



