/*=========================RCS info==================================*/
/* $Author: beta $ */
/* $Revision: 1.1.1.1 $ */
/* $Source: /a/home/alhambra02/beta/.CVSHOME/beta_project/basiclib/private/external/cbreak/mystrings.c,v $ */
/* $Date: 1995-09-26 10:31:47 $ */
/* $State: Exp $ */
/* $Locker:  $ */
/*===================================================================*/
/* -------------------------------------------- */
/*  file:  mystrings.c                          */
/*  purpose: some small, many needed strings    */
/*           handling routines                  */
/*  author:  R. Vankemmel                       */
/* -------------------------------------------- */

#include <string.h>
#include <stdlib.h>
#include <ctype.h>

/* trim: remove trailing blanks, tabs, newlines */
/* ref: K&R Ansi C p. 65 */
int trim(char s[])
{
    int n;

    for (n=strlen(s)-1; n>=0; n--)
	if (s[n] != ' ' && s[n] != '\t' && s[n] != '\n')
	    break;
    s[n+1] = '\0';
    return n;
}

/* skip: remove leading blanks, tabs */
/* author: R. Vankemmel              */
int skip(char s[])
{
    int n;

    for (n=0; n < strlen(s); n++)
	if (s[n] != ' ' && s[n] != '\t') break;

    return n;
}

/* nextword: skip a text string up to the next word */
/* author: R. Vankemmel                             */
int nextword(char s[])
{
    int n;

    /* first skip non blank remaining chars */
    for (n=0; n<strlen(s); n++)
	if (isspace((int) s[n])) break;
     
    /* are we at end ? */
    if (n != (strlen(s)-1))
    {
       /* now skip extra blanks up to new word */
       n += skip(s+n);
    }

    return n;
}

/* reverse: reverse string s in place */
/* ref: K&R p 62 (ANSI C sec. ed.     */
void reverse(char s[])
{
   int c,j,i;

   for (i=0, j=strlen(s)-1; i<j; i++, j--) 
       c=s[i], s[i]=s[j], s[j]=c;
}


/*  itoa:  convert n to characters in s */
/* ref:  K&R p 64 (ANSI C, second ed.)  */
void itoa(int n, char s[])
{
   int i,sign;

   if ((sign = n) < 0)   /* record sign */
       n = -n;           /* make n positive */
   i = 0;
   do {     /* generate digits in reverse order */
       s[i++] = n % 10 + '0'; /* get next digit */
   } while ((n /= 10) > 0);   /* delete it      */
   if (sign < 0)
      s[i++] = '-';
   s[i] = '\0';
   reverse(s);
}

/* matof: my atof() function ; same as atof() BUT 
 * it converts also Fortran like numbers using D format as in
 * x.xxxxxD+yy or x.xxxxxd+yy which is not understood by scanf() or atof. 
 * Also the E specifier can be 
 * in lower or upper case.
 */
double matof(char *c)
/* this routine converst a real number in string format into a double.
 * If the real numbers in the string are written as 0.xxxe+xx the you
 * can use simply atof(). However in PRISM the output format may be
 * 0.xxxd+xx which is not recognized in C. So, we must detect a d or
 * D and replace it by e or E. Note that the input string is NOT changed.
 *
 * author: R. Vankemmel 27/5/91 / based on a routine of Jan Ureel from the 
 *				  PRISM postprocessor..
 * revision: RVK 23/8/1994: rewrote it.
 */
{    
     int j,index=0;
     char temp[128];

     for(j=skip(c); j < nextword(c) && j< strlen(c); j++) {
	 if (isspace(c[j])) continue;
	 else
	  if ( isdigit(c[j]) || (c[j]=='.') || (c[j]=='-') ||
	         (c[j]=='+') ) temp[index++]=c[j];
	  else 
	  if ( (c[j]=='E') || (c[j]=='e') ||
	       (c[j]=='D') || (c[j]=='d')  )
	     temp[index++]='e';
     }
     temp[index++] = '\0';
     return(atof(temp));
}
       
