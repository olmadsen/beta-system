#include <stdio.h>

void PutToScreen(ch)
  char ch;
  {
   putchar(ch);
   fflush(stdout);
  }
void PutTextToScreen(str)
  char *str;
  {
   fputs(str,stdout);
   fflush(stdout);
  }
char GetFromKeyboard()
  {
   return(getchar());
  }
int KeyboardEOS()
  {
   int ch;
   ungetc(ch=getchar(),stdin);
   return(ch==EOF); 
  }
int KeyboardPeek()
{ int ch;
  if ((ch=getchar()) != EOF) ungetc(ch, stdin);
  return (ch);
}

void PutToStdErr(ch)
  char ch;
  {
   putc(ch, stderr);
   fflush(stderr); 
  }
void PutTextToStdErr(str)
  char *str;
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
