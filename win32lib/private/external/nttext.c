#include <string.h>
#include <malloc.h>
#ifdef nti
#include <stdlib.h>
#else
#include <pwd.h>
char *getenv();
#endif

char tmp[1024];

char *getPassWdHome(name)
     /* Only to be called on arguments of the form "~/" or "~name/" */ 
     char *name;
{
  char *val;
  if (strcmp("~\\", name) == 0) {
    /* Special case */
    val = getenv("HOME");
    if (!val) {
      char *hd = getenv("HOMEDRIVE");
      char *hp = getenv("HOMEPATH");
      if (!hd || !hp)
	return "";
      strcat(strcpy(tmp,hd),hp);
      return tmp;
    }
    return val;
  } else if (stricmp("~beta\\",name) == 0) {
    /* Special case */
    val = getenv("BETALIB");
    if (val)
      return val;
    else
      return "c:\\beta";
  }

  if ((name[0] != '~') || (strlen(name) == 0)) { 
    return (""); /* Not good but ... */
  } else {
    strcpy(tmp,name+1);
    strcpy(tmp+strlen(tmp)-1, "HOME");
    strupr(tmp);
    val = getenv(tmp);
    return val?val:"";
  }
}
