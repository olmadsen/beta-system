/*
 *  file:  vms_getkey.c
 * purpose: unbuffered single character input on VAX VMS systems.
 * routines: 
 *       getkey() returns the next keystroke without echo or a carriage
 *	 return.
 *
 *       putchar(char) works like the UNIX putchar, buffering the
 *       characters until the buffer fills up (512 chars) or
 *	 a newline character is putchared.
 *
 * author: Anthony C. McCracken
 * date  : 10-APR-92 Version 1.6
 *
 * modification:  R. Vankemmel 28/10/1994
 *                I had a routine which was handling single char input
 *                on UNIX SYSV/BSD systems using the native ioctl calls,
 *                curses or POSIX call's. Also Think C on MAC was supported.
 *                Some users asked for a VMS version. However,  Anthony C.
 *                McCracken posted such a routine on the net which I
 *                rearranged in order to include it transparantly in my
 *                code i.e. the user can call the same routine my_getch()
 *                on all platforms. For this purpose, Mr. McCracken's code
 *                was split into a header file and a source file. This 
 *                allowed much easier inclusion.
 */

#include <string.h>       /* for the strlen() call */
/* original source moved into header file up to here -----------------*/
#include "vms_getkey.h"

/* add system function prototyping: see help pages on system services */
extern int sys$assign(descr *, short int *, int, char *, ...);
extern int sys$qiow( int, int, int, iosb *, void (* fun)(), int,  ... );

/* continue with original source -------------------------------------*/
short int __tty_chan = 0;

void build_descr(descr *p,char *s)    /* Builds a fixed length string */
                                      /* descriptor                   */
{

   p->length = strlen(s);
   p->dtype = 14;
   p->class = 1;
   p->ptr = s;
}

char getkey()
{
   descr __tty_name;
   char __tty_buff;
   iosb __tty_iosb;
   int __i;

   if (__tty_chan == 0) {
      build_descr(&__tty_name,"TT:");
      if (sys$assign(&__tty_name,&__tty_chan,0,0) != SS$_NORMAL) return(0);
   }
   __i = sys$qiow(0,__tty_chan,IO$_READVBLK+IO$M_NOECHO,&__tty_iosb,0,0,
                &__tty_buff,1,0,0,0,0);
   if (__i != SS$_NORMAL) return(0);
   else return(__tty_buff);
}

#define __putcharbufsize 512
char __putcbuff[__putcharbufsize];
int __pcp = 0;

#define putchar(c) {if(c=='\n') __barfout(__putcbuff,&__pcp); \
                   else __putcbuff[__pcp++]=c; \
                   if (__pcp>__putcharbufsize-2) __barfout(__putcbuff,&__pcp);}

void __barfout(char *s, int *__i)
{
   s[(*__i)++] = '\n';
   s[*__i] = 0;
   fputs(s,stdout);
   *__i = 0;
}



#ifdef _VMS_TEST_
#include <stdio.h>
#include "vms_getkey.h"
main()
{
   char c;

   printf("Press ANY key to continue\n");
   c = getkey();
   printf("You pressed the %c key\n",c);
}
#endif


