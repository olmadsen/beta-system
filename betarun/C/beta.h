#ifndef _BETA_H_
#define _BETA_H_
/*
 * BETA RUNTIME SYSTEM, Copyright (C) 1991, 1992 Mjolner Informatics Aps.
 * Mod: $RCSfile: beta.h,v $, rel: %R%, date: $Date: 1992-08-28 11:57:45 $, SID: $Revision: 1.5 $
 * by Lars Bak, Peter Andersen and Tommy Thorn
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
