#include <string.h>
#include <pwd.h>
#include <malloc.h>
char *getenv();

char *getPassWdHome(name)
     /* Only to be called on arguments of the form "~/" or "~name/" */ 
     char *name;
{ struct passwd *buffer;
  
  if (strcmp("~/", name) == 0) {
    /* Special case */
    return(getenv("HOME"));
  }
  else {
    if ((name[0] != '~') || (strlen(name) == 0)) { 
      return (""); /* Not good but ... */
    }
    else {
      int i;
      char *tmp;
      tmp = malloc(strlen(name)+1);
      for (i=1;i<strlen(name)-1;i++) tmp[i-1] = name[i]; tmp[strlen(name) - 2] = '\0'; 
      /* Drop last character ... */ 
      if ((buffer = getpwnam(tmp)) != NULL ) { 	
	return(buffer->pw_dir);
      } else {
	return (""); /* Not good but ... */
      }
    }
  }
}
