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
/* $Source: /a/home/alhambra02/beta/.CVSHOME/beta_project/basiclib/private/external/cbreak/my_gets.c,v $ */
/* $Date: 1995-09-26 10:31:47 $ */
/* $State: Exp $ */
/* $Locker:  $ */
/*===================================================================*/
/* 
    file: my_gets.c

    purpose: my_gets() has the same functionality as gets()
	     but it checks when gets() returns a NULL pointer.
	     This is mainly because an EOF was read. In case
	     gets() is used in a loop, this may cause endless 
	     loops because stdin is closed when a ^D at input 
	     was given. my_gets() then reopens stdin so that
	     input reading may continue.

	     my_gets() skips also leading blanks and tabs.
	     It returns the position in the buffer of the 
	     first relevant char.
	
    syntax:  char *my_gets(char *buffer, int *begin)
    input:   *buffer : any character string
    output:  *begin  : index in buffer[] where first relevant character
		       is or on EOF:   -1
	     *my_gets: on succes: pointer to first relevant char in 
				  buffer[]
		       on CR/LF:  NULL pointer;
		       on EOF (^D): NULL pointer;


     author: R. Vankemmel
     date:   7/7/93
*/
/*--------------------------------------------------------------*/
#include <stdio.h>
#include <errno.h>
extern int skip();

char *my_gets(char *buffer,int *begin)
{
    char *bufptr;

    bufptr = gets(buffer);       /* read stdin   */
    if (bufptr != (char *) NULL) /* check on EOF */
    {
       *begin = skip(buffer);     /* where is first relevant char */
       if (buffer[*begin] == '\0') /* newline replaced by \0 in gets() */
           return(NULL);
       else 
	   return(buffer + *begin); /* return pointer to relevant string */
    }
    else
    {
       /* probably an EOF (^D) pressed : reopen stdin !!! */
       printf("\nmy_gets: Caught error at input\n");
       /* check if we need to reopen stdin */
       if (feof(stdin))
       {
          freopen("/dev/tty", "r", stdin);
       }
       else if (ferror(stdin)) 
       {
	  clearerr(stdin);
       }
       *begin = -1;
       buffer[0] = '\0';
       return(NULL);
    }
}
