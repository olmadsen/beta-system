/*
 * BETA RUNTIME SYSTEM, Copyright (C) 1990 Mjolner Informatics Aps.
 * by Lars Bak.
 */

#include <stdio.h>

#ifdef macintosh
#include <StdLib.h>
#include <Resources.h>
#include <String.h>
#include <memory.h>
#endif

#include "beta.h"

#ifndef DEFAULT_PROPERTY_NAME
#define DEFAULT_PROPERTY_NAME "BETART"
#endif

void GetBetaEnv()
{
  char *betaEnv, *getenv();
  
#ifdef macintosh
  char **theHandle;
  long length;
  
  if( betaEnv = getenv("BETASU") ){ SetupProperties( betaEnv); return; };
  
  if( betaEnv = getenv( DEFAULT_PROPERTY_NAME) ){
    SetupProperties( betaEnv);
  } else {
    if( theHandle = GetNamedResource('STR ',"\pBETART") ){
      betaEnv = *theHandle; length = betaEnv[0];
      betaEnv = strncpy( (Ptr) NewPtr(length+1), &betaEnv[1], length);
      betaEnv[length] = 0; SetupProperties( betaEnv);
    }
  }
#else
  if( betaEnv = getenv( DEFAULT_PROPERTY_NAME) )
    SetupProperties( betaEnv);
#endif
}
