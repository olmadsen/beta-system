#ifdef nti
# include <windows.h>
# include <winbase.h>
#else
# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
#endif

#define MAXLENGTH 128

static char username[MAXLENGTH];

char* getUser ()
{
#ifdef nti

  int len = MAXLENGTH;
  int r = GetUserName(username, &len);
  if (!r)
    return NULL;

#else
  char *name = getlogin();
  if (name)
    strcpy (username, name);
  else
    return NULL;
#endif
  return username; 
}

