#ifndef _BETA_H_
#define _BETA_H_
/*
 * BETA RUNTIME SYSTEM, Copyright (C) 1991, 1992 Mjolner Informatics Aps.
 * Mod: $Id: beta.h,v 1.6 1992-09-03 12:54:03 beta Exp $
 * by Lars Bak, Peter Andersen, Peter Orbaek and Tommy Thorn
 */

#include <stdio.h>
#include "define.h"
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
