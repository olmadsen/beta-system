/* THIS FILE IS NO LONGER USED FOR VALHALLA. SHOULD BE MOVED ALONG WITH
 * ../../utils/buffered_io.bet. */

#include <stdio.h>
#include <unistd.h>

int getfileno (FILE* f)
{
  return fileno(f);
}  
