/*
 * BETA RUNTIME SYSTEM, Copyright (C) 1990-94 Mjolner Informatics Aps.
 * by Lars Bak.
 */

#include <stdio.h>
#ifdef nti
#include <stdlib.h>
#endif

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
  char *betaEnv;
#ifndef nti
  char *getenv();
#endif
  
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
  if( (betaEnv = getenv(DEFAULT_PROPERTY_NAME)) )
    SetupProperties( betaEnv);
#endif
}

#ifdef nti
int beta_instance;
int beta_previnstance;
char *beta_cmdline;
int beta_show;

/* Create ArgVector and ArgCount from a command line string */
void SetupArgValues(int ret, int inst, int prev, char *cmd, int show)
{
  char *p;

  beta_instance = inst;
  beta_previnstance = prev;
  beta_cmdline = cmd;
  beta_show = show;

  /* Get copy of command line */
  p = MALLOC(strlen(beta_cmdline));
  strcpy(p, beta_cmdline);

  ArgVector = NULL;
  ArgCount = 0;
  /* Cut command line into arguments */
  while (*p) {
    while (*p == ' ' || *p == '\t')
      p++;
    /* At start of argument or EOT */
    if (*p) {
      /* Make room for argument */
      ArgVector = (char**)REALLOC(ArgVector, (ArgCount+1)*sizeof(char*));
      ArgVector[ArgCount++] = p;
      /* Skip argument */
      while (*p && *p != ' ' && *p != '\t')
        p++;
      /* Terminate argument string */
      if (*p)
        *p++ = '\0';
    }
  }
}
#endif
