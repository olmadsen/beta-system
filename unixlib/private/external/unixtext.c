#include <string.h>
#include <pwd.h>
#include <stdlib.h>
#include <stdio.h>

char *getPassWdHome(char *name)
     /* Only to be called on arguments of the form "~/" or "~name/".
      * If not, or if something fails in expansion, the argument string
      * is returned.
      */ 
{ 
  struct passwd *buffer;
  char *tmp;
  
  if (strcmp("~/", name) == 0) {
    /* Special case */
    tmp=getenv("HOME");
    if (tmp || (strlen(tmp)>0)){
      return tmp;
    } else {
      /* HOME not set, or set to empty string. Try USER */
      tmp=getenv("USER");
      if (tmp || (strlen(tmp)>0)){
	buffer = getpwnam(tmp);
	if (buffer) { 	
	  return(buffer->pw_dir);
	} else {
	  /*fprintf(stderr, "getPassWdHome: getpwnam failed\n");*/
	  return name;
	}
      } else {
	/*fprintf(stderr, "getPassWdHome: neither HOME nor USER set in environment\n");*/
	return name;
      }
    }
  } 
  
  if ((!name) || 
      (strlen(name)<3) /* At least one char more between '~' and '/' */ ||
      (name[0] != '~') ||
      (name[strlen(name)-1]!='/') ) {
    return name; 
  } else {
    /* FIXME: the malloc below could be changed to a local (stack allocated) buffer
     * if max length of user name is known. However, it does not seem to
     * be specified in <sys/param.h>.
     */
    tmp = malloc(strlen(name)+1);
    if (tmp){
      /* Drop first and last character: */ 
      strncpy(tmp, name+1, strlen(name)-2);
      tmp[strlen(name)-2]=0;
      buffer = getpwnam(tmp);
      free(tmp);
      if (buffer) { 	
	return(buffer->pw_dir);
      } else {
	/*fprintf(stderr, "getPassWdHome: getpwnam failed\n");*/
	return name;
      }
    } else {
      fprintf(stderr, "getPassWdHome: malloc failed\n");
      return name;
    }
  }
}
