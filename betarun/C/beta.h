#ifndef _BETA_H_
#define _BETA_H_
/*
 * BETA RUNTIME SYSTEM, Copyright (C) 1991-94 Mjolner Informatics Aps.
 * beta.h
 * by Lars Bak, Peter Andersen, Peter Orbaek, Tommy Thorn, and Jacob Seligmann
 */

#include "define.h"

#include <stdio.h>
#include <ctype.h>

#if defined (MAC)
# include <Resources.h>
# include <Memory.h>
# include <StdLib.h>
# include <String.h>
# include <Files.h>
# ifdef RTDEBUG
#  include <Types.h>
# endif
#else
# include <string.h>
# include <malloc.h>
# include <memory.h>
# include <stdlib.h>
#endif

#ifdef UNIX
#include <dlfcn.h>
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


#ifdef sparc
#include "sparcdep.h"
#endif

#ifdef hppa
#include "snakedep.h"
#endif

#include "function.h"
#include "data.h"

#endif /* _BETA_H_ */
