#include <stdio.h>
#include <string.h>

/* REDIRECTOUTPUT
 * ==============
 *
 * Used in initialization of shells started by ensemble.createShell.
 * Output from these are redirected to an unbuffered log file. */

void redirectOutput (char *fname)
{ 
  if (strlen (fname)) {

    if (freopen (fname, "a", stdout)){
      setbuf (stdout, 0); /* disable buffering on stdout */
    } else {
      freopen ("/dev/null", "w", stdout);
    }
      
    if (freopen (fname, "a", stderr)){
      setbuf (stderr, 0); /* disable buffering on stderr */
    } else {
      freopen ("/dev/null", "w", stderr);
    }
  } else {
    freopen ("/dev/null", "w", stdout);
    freopen ("/dev/null", "w", stderr);
  }
}
