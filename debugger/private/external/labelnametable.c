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

/* On sun4s, nm returns labels in decimal, not in hex as on
 * other architechtures. */

void findNextLabel ()
{
  char type;
  
  for (;;)
#ifdef sun4s
    if (fscanf (thePipe, "%d %c %s", &NextAddress, &type, NextLabel) == EOF){
#else
    if (fscanf (thePipe, "%x %c %s", &NextAddress, &type, NextLabel) == EOF){
#endif
      NextAddress = 0;
      pclose (thePipe);
      break;
    }
    else if ((type == 'N') || (type == 'T'))
      break;
    else
      while (fgetc (thePipe) != '\n') continue;
};

void initReadNameTable (char* execFileName)
{
  char command[100];

  (void) strcpy (command, "nm -p ");
  (void) strcat (command, execFileName);

  thePipe = popen (command, "r");
};

int nextAddress () { findNextLabel (); return NextAddress; };
char* nextLabel () { return NextLabel; };
