/*
Copyright 1993 by R. Vankemmel

Permission to use, copy, modify and distribute this software and the
supporting documentation without fee is hereby granted, provided that :

1 : Both the above copyright notice and this permission notice
    appear in all copies of both the software and the supporting
    documentation.
2 : You don't make a profit out of it.
3 : You properly credit the author of this software when it is 
    included in any other package.

THE AUTHORS DISCLAIM ALL WARRANTIES WITH REGARD TO THIS SOFTWARE,
INCLUDING ALL IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS. IN NO
EVENT SHALL THEY BE LIABLE FOR ANY SPECIAL, INDIRECT OR CONSEQUENTIAL
DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR
PROFITS, WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS
ACTION, ARISING OUT OF OR IN CONNECTION WITH THE USE OR PERFORMANCE OF
THIS SOFTWARE.
*/
/*=========================RCS info==================================*/
/* $Author: beta $ */
/* $Revision: 1.1.1.1 $ */
/* $Source: /a/home/alhambra02/beta/.CVSHOME/beta_project/basiclib/private/external/cbreak/test.c,v $ */
/* $Date: 1995-09-26 10:31:47 $ */
/* $State: Exp $ */
/* $Locker:  $ */
/*===================================================================*/
/*

   file:    test.c
   purpose: test program for the my_getch() routine.

   author:  R. Vankemmel
   date:    11-5-93

   revisions:
    1) 


*/
/* ============================================================== */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <errno.h>

extern int   my_getch();

#ifndef TRUE
#   define TRUE (1)
#endif
#ifndef FALSE
#   define FALSE (0)
#endif

/* ---------------------------------------------------------------*/
main(int argc, char **argv)
{
 int input;     /* entered character */
 int answer=FALSE,leave_loop;   

 printf("\n           Testing the my_getch() routine\n ");
 printf("                Author:   R. Vankemmel\n");
 printf("                Date:     2/7/93\n");
 printf("\n");

 do 
   {
      printf("     Please enter something <y,n>: ");
      putchar('n');           /* show the default option */
      fflush(stdout);
      input = my_getch();
      printf("\b%c\n",input); /* flush entered character */
      putchar('\n');
      switch(input)           /* check the entered character */
      {                       /* and perform something       */
	case 'y':             /* depending on the answer     */
	case 'Y':
	     answer = TRUE;
             leave_loop  = TRUE; 
	     break;
	case 'n':
	case 'N':
	case '\r':
	case '\n':
	     answer = FALSE;
             leave_loop  = TRUE; 
	     break;
	default:
	     leave_loop  = FALSE;
	     break;
      }
   }
   while (! leave_loop);

   if (answer)
      printf("     You said yes \n");
   else
      printf("     You said no \n");

}

/* ---------------------------------------------------------------------- */
