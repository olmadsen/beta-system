
#include <stdio.h>
#include <beta.h>

static FILE* fifoFrom, *fifoTo;
extern char* valhallaID;

char *fromName (pid_t pid)
{ char name[50];
  sprintf (name,"/tmp/betadebugFrom%d",pid);
  return strdup (name);
}

char *toName (pid_t pid)
{ char name[50];
  sprintf (name,"/tmp/betadebugTo%d",pid);
  return strdup (name);
}

void createFIFOS (pid_t pid)
{ char* name;
  name = fromName (pid); mkfifo (name,0777); free (name);
  name = toName (pid); mkfifo (name,0777); free (name);
}

void openFIFOS (pid_t pid)
{ char* name;
  name = fromName (pid); fifoFrom = fopen (name,"r+"); free (name);
  name = toName (pid); fifoTo = fopen (name,"r+"); free (name);
}

void valhallaInit ()
{ char tmp[20];
  int valhallaPID, pid;
  
  if (valhallaID) {
  } else {
    
    pid = getpid ();
    
    /* Valhalla is not running. */
    createFIFOS (pid);
    
    valhallaPID = vfork ();
    
    if (valhallaPID) {

      if (valhallaPID!=-1) {
	
	sprintf (tmp,"%d",valhallaPID); 
	valhallaID = strdup (tmp);
	openFIFOS (pid);
	
      } else
	fprintf (stderr, "Could not fork\n");

    } else {

      sprintf (tmp,"%d",pid);
      execl ("getObj", "-PID", tmp, (char *) 0);
      fprintf (stderr, "Could not start valhalla\n");
      
    }
  }
}


void valhallaCommunicate ()
{


}
