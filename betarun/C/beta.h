#ifndef _BETA_H_
#define _BETA_H_
/*
 * BETA RUNTIME SYSTEM, Copyright (C) 1991-93 Mjolner Informatics Aps.
 * beta.h
 * by Lars Bak, Peter Andersen, Peter Orbaek and Tommy Thorn
 */

#include <stdio.h>

#ifndef macintosh
# include <string.h>
# include <malloc.h>
# include <memory.h>
#endif

#ifdef macintosh
# include <Memory.h>
# include <StdLib.h>
# ifdef RTDEBUG
#  include <Types.h>
# endif
#endif

#include "define.h"
#include "betaerror.h"
#include "object.h"
#include "heap.h"
#include "constant.h"
#include "macro.h"
#include "function.h"
#include "data.h"

#ifdef sparc
#include "sparcdep.h"
#endif

#ifdef hppa
#include "snakedep.h"
#endif

#ifdef __STDC__
#define P(A) A
#else
#define P(A) ()
#endif


#endif
