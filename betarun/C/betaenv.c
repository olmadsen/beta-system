/*
 * BETA RUNTIME SYSTEM, Copyright (C) 1990 Mjolner Informatics Aps.
 * by Lars Bak Petersen.
 */

#include <stdio.h>

#ifdef macintosh
#include <StdLib.h>
#include <Resources.h>
#include <String.h>
#endif

#ifndef DEFAULT_PROPERTY_NAME
#define DEFAULT_PROPERTY_NAME "BETART"
#endif

GetBetaEnv()
{
  char *betaEnv, *getenv();

#ifdef macintosh
  char *malloc();
  char **theHandle;
  int length;

  if( betaEnv = getenv("BETASU") ){ SetupProperties( betaEnv); return; };
  if( theHandle = GetNamedResource('STR ',"\pBETART") ){
    betaEnv = *theHandle; length = betaEnv[0];
    betaEnv = strncpy( malloc(length+1), &betaEnv[1], length);
    betaEnv[length] = 0; SetupProperties( betaEnv);
  }else{
    if( betaEnv = getenv( DEFAULT_PROPERTY_NAME) )
      SetupProperties( betaEnv);
  }
#else
  if( betaEnv = getenv( DEFAULT_PROPERTY_NAME) )
    SetupProperties( betaEnv);
#endif
}
