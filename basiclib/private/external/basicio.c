#include <stdio.h>

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
char GetFromKeyboard(void)
  {
   return(getchar());
  }
int KeyboardEOS(void)
  {
   int ch;
   ungetc(ch=getchar(),stdin);
   return(ch==EOF); 
  }
int KeyboardPeek(void)
{ int ch;
  if ((ch=getchar()) != EOF) ungetc(ch, stdin);
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
