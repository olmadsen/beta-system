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

void putstr(const char *s)
{ while (*s) putch(*s++);
}

int main(void)
{ init_uart();

  putstr("Hello world\n");

}
