/***************************
 *                         *
 * Architecture dependance *
 *                         *
 ***************************/


/* Create well-defined symbols for architecture */

#include <arch.h>

#if defined(A_SUN4)
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>

#else
#  if defined(A_SUN4S) || defined(A_LINUX) || defined(A_SGI)
#  include <sys/types.h>
#  include <sys/socket.h>
#  include <netdb.h>
#  include <netinet/in.h>

#  else
#    if defined(A_HPUX8)
#    include <sys/socket.h>
#    include <netinet/in.h>
#    include <netdb.h>

#    else
#      if defined(A_SNAKE)
#      include <sys/types.h>
#      include <sys/socket.h>
#      include <netdb.h>


#      else
#        if defined(A_NT)
#        error "Not yet implemented on this platform"

#        else
#          error ARCH_UNKNOWN
#        endif
#      endif
#    endif
#  endif
#endif


int getName (int adr)
{ return adr; }


struct hostent* thisHost ()
{ char host[100];

  if (gethostname (host, 100) == 0)
    return gethostbyname (host);
  else
    return (struct hostent *)0; 
}
