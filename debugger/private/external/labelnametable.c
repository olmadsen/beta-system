/* labelnametable.c
 *
 * Provides support for reading code labels from the nametable of an 
 * executable file.
 *
 * Sets up a pipe to nm and reads the nametable from this pipe.
 *
 */

#include <stdio.h>
#include <string.h>

FILE *thePipe; /* The pipe from which the nameTable is read */
int NextAddress;    
char NextLabel[100]; /* The last address and label read from the pipe. */

#ifdef sun4s
#define nmcommand "nm -hvp"
#else
#define nmcommand "nm -hvp"
#endif

void findNextLabel ()
{ char type;
  char ch;
  int inx;

  while (1) {
    NextAddress=0;
    while ((ch=fgetc (thePipe))!=' ') {
      if (ch==EOF) {
	NextAddress = 0;
	pclose (thePipe);
	return;
      }
      NextAddress = (NextAddress*10)+(ch-'0');
    }

    type = fgetc (thePipe);
    
    if ((type != 'N') && (type != 'T')) {
      while (fgetc (thePipe) != '\n') continue;
      continue;
    }

    fgetc (thePipe);

    inx=0;
    while ((NextLabel[inx++]=fgetc(thePipe))!='\n')
      ;
    NextLabel[inx-1] = 0;

    return;
  }
};

void initReadNameTable (char* execFileName)
{ char command[100];
  
  sprintf (command,"%s %s",nmcommand,execFileName);
  thePipe = popen (command, "r");
};

int nextAddress () { findNextLabel (); return NextAddress; };
char* nextLabel () { return NextLabel; };
