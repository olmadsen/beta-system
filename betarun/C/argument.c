/*
 * BETA RUNTIME SYSTEM, Copyright (C) 1991 Mjolner Informatics Aps.
 * Mod: $RCSfile: argument.c,v $, rel: %R%, date: $Date: 1991-01-30 10:55:32 $, SID: $Revision: 1.1 $
 * by Lars Bak
 */
#include "beta.h"

  
/* Argc is an external described in "betaenvbody.bet"
 *   Argc: External
 *   (# noOfArgs: @integer;  
 *   exit noOfArgs
 *   #)
 */

int  Argc(){ return ArgCount; }

/* Argv is an external described in "betaenvbody.bet"
 *   Argv: External
 *  (# argNo: @integer;
 *     theArg: [1]@char;
 *  enter argNo
 *  do CallC
 *  exit theArg
 *  #) 
 */

char *Argv(n) int n; { return ArgVector[n-1]; }
