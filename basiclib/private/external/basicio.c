#include <stdio.h>
#include <errno.h>
#include <sys/time.h>

void PutToScreen(char ch)
  {
   putchar(ch);
   fflush(stdout);
  }
void PutTextToScreen(char *str)
  {
   fputs(str,stdout);
   fflush(stdout);
  }

static int my_getchar(void)
{
    int ch;
    ch=getchar();
    if (ch == EOF && errno==EAGAIN) {
        fd_set fdset;
        int fd = fileno(stdin);
        FD_ZERO(&fdset);
        FD_SET(fd, &fdset);
        select(1, &fdset,NULL,NULL,NULL);
        ch=getchar();
    }
    return ch;
}

    
char GetFromKeyboard(void)
  {
   return(my_getchar());
  }
int KeyboardEOS(void)
{
    int ch;
    ch=my_getchar();
    ungetc(ch, stdin);
    return(ch==EOF); 
}
int KeyboardPeek(void)
{
  int ch;
  ch=my_getchar();
 
  if (ch != EOF) {
      ungetc(ch, stdin);
  }
  
  return (ch);
}

void PutToStdErr(char ch)
  {
   putc(ch, stderr);
   fflush(stderr); 
  }
void PutTextToStdErr(char *str)
  {
   fputs(str,stderr);
   fflush(stderr); 
  }

double infReal(void)
{
  double x;
#if defined(nti) || defined(linux)
  ((unsigned long *)(&x))[0] = 0x00000000;
  ((unsigned long *)(&x))[1] = 0x7FF00000;
#else
  ((unsigned long *)(&x))[0] = 0x7FF00000;
  ((unsigned long *)(&x))[1] = 0x00000000;
#endif
  return x;
}
