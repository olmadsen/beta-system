#include <stdio.h>
#include <beta.h>
#include "valhallaFIFOS.h"
#include "valhallaComm.h"

static FILE *fifoFrom, *fifoTo;

void valhallaInit ()
{ char tmp[20];
  int valhallaPID, pid;
  
  if (valhallaID) {

    /* Valhalla is already running. */
    valhallaPID = atoi (valhallaID);
    openFIFOS (valhallaPID,&fifoFrom,&fifoTo);

  } else {
    
    /* Valhalla is not running. */
    
    pid = getpid (); 
    createFIFOS (pid); 
    valhallaPID = vfork ();
    
    if (valhallaPID) {

      if (valhallaPID!=-1) {
	sprintf (tmp,"%d",valhallaPID); valhallaID = strdup (tmp);
	openFIFOS (pid,&fifoFrom,&fifoTo);
      } else
	fprintf (stderr, "Could not fork\n");

    } else {

      sprintf (tmp,"%d",pid);
      execl ("getObj","getObj","-PID",tmp,"-EXECNAME","putObj",(char *) 0);
      fprintf (stderr, "Could not exec\n");
      exit (0);
      
    }
  }
}

int fifoBinGetInt (FILE *f)
{ int val;
  if (fifoBinGetBytes (f, (char *)&val, sizeof(val)) != sizeof(val))
    fprintf (stderr, "WARNING -- fifoBinGetInt failed\n");
  return val;
}

void fifoBinPutInt (FILE *f, int val)
{ 
  if (fifoBinPutBytes (f, (char *)&val, sizeof(val)) != sizeof(val))
    fprintf (stderr, "WARNING -- fifoBinPutInt failed\n");
}

int fifoBinGetBytes (FILE *f, char* buf, int bytes)
{
  return fread (buf,1,bytes,f);
}

int fifoBinPutBytes (FILE *f, char* buf, int bytes)
{
  return fwrite(buf,1,bytes,f);
}

typedef struct group_header
{
  struct group_header *self;
  long                *protoTable;
  struct group_header *next;
  long                code_start;
  long                code_end;
} group_header;

extern struct group_header* NextGroup (struct group_header* current);
extern char* NameOfGroup (struct group_header *group);

void valhallaCommunicate ()
{ int opcode;
  group_header *current;

  while (TRUE) {
    opcode = fifoBinGetInt (fifoTo);
    
    switch (opcode) {

    case VOP_SCANGROUPS:

      fprintf (stderr, "VOP_SCANGROUPS\n");
      
      { group_header *current = 0;

	while (current = NextGroup (current)) {
	  fprintf (fifoFrom,"%s\n",NameOfGroup(current));      /* groupName */
	  fifoBinPutInt (fifoFrom, (int) current->self);       /* dataStart */ 
	  fifoBinPutInt (fifoFrom, (int) current->next);       /* dataEnd   */
	  fifoBinPutInt (fifoFrom, (int) current->code_start); /* codeStart */
	  fifoBinPutInt (fifoFrom, (int) current->code_end);   /* codeEnd   */
	}
	fprintf (fifoFrom,"\n");
	fflush (fifoFrom);
      }
      break;

    case VOP_KILL:

      fprintf (stderr, "Killed\n");
      fclose (fifoFrom); fclose (fifoTo);
      return;

    default:

      fprintf (stderr, "Got %d\n", opcode);
      break;

    }
  }
}
