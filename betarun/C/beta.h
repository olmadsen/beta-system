#ifndef _BETA_H_
#define _BETA_H_
/*
 * BETA RUNTIME SYSTEM, Copyright (C) 1991-94 Mjolner Informatics Aps.
 * beta.h
 * by Lars Bak, Peter Andersen, Peter Orbaek, Tommy Thorn, and Jacob Seligmann
 */

#include "define.h"
#include "macro.h"

#include <stdio.h>
#include <ctype.h>

#if defined (MAC)
# include <StdLib.h>
# include <String.h>
# ifdef RTDEBUG
#  include <Types.h>
# endif
#else
# include <string.h>
# include <memory.h>
# include <stdlib.h>
#endif

#ifdef __linux__
# define __USE_GNU 1  /* Make sure we get non-standard routines from dlfcn.h */
# include <malloc.h>  /* Make sure we get memalign() */
#endif
#ifdef UNIX
# if ! (defined(hppa) || defined(macosx))
#   include <dlfcn.h>
# endif /* hppa */
#endif /* UNIX */

#ifdef RTVALHALLA
#include <string.h>
#endif

#ifdef nti
  #include <windows.h>
#endif

#ifdef MT
#include <thread.h>
#endif

#include "constant.h"
#include "betaerror.h"
#include "object.h"
#include "heap.h"
#include "registers.h"
#include "macro.h"
#include "data.h"


#ifdef sparc
#include "sparcdep.h"
#endif

#ifdef hppa
#include "snakedep.h"
#endif

#ifdef ALLOC_TRACE
# include "trace-types.h"
#endif

#include "function.h"


/* vim:sw=2:
 * (set shiftwidth in VIM) */

#endif /* _BETA_H_ */
