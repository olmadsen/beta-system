/*
 * BETA RUNTIME SYSTEM, Copyright (C) 1990-94 Mjolner Informatics Aps.
 * by Lars Bak.
 */

#include "beta.h"

#include <stdio.h>

#ifndef DEFAULT_PROPERTY_NAME
#define DEFAULT_PROPERTY_NAME "BETART"
#endif

void GetBetaEnv()
{
  char *betaEnv;
  
#if defined(MAC)
  char **theHandle;
  long length;
  
  if( betaEnv = getenv("BETASU") ){ SetupProperties( betaEnv); return; };
  
  if( betaEnv = getenv( DEFAULT_PROPERTY_NAME) ){
    SetupProperties( betaEnv);
  } else {
    if( theHandle = GetNamedResource('STR ',(const unsigned char*)"\pBETART") ){
      betaEnv = *theHandle; length = betaEnv[0];
      betaEnv = strncpy( (Ptr) NewPtr(length+1), &betaEnv[1], length);
      betaEnv[length] = 0; SetupProperties( betaEnv);
    }
  }
#else
  if( (betaEnv = getenv(DEFAULT_PROPERTY_NAME)) )
    SetupProperties( betaEnv);
#ifdef RTVALHALLA
  { char* valhallaEnv;
    if ((valhallaEnv = getenv ("VALHALLART")))
      SetupProperties(valhallaEnv);
  }
#endif
#endif
}

#ifdef nti
#include <winbase.h>

/* Create ArgVector and ArgCount from a command line string */
/* Is called from _WinMain@16, when linked as subsystem windows */
void SetupArgValues(int ret, int inst, int prev, char *cmd, int show)
{
  char *p = ""; /* Init so that !*p */

  beta_instance = inst;
  beta_previnstance = prev;
  beta_cmdline = GetCommandLine();
  beta_show = show;

  if (beta_cmdline) {
    /* Get copy of command line */
    p = MALLOC(strlen(beta_cmdline)+1);
    strcpy(p, beta_cmdline);
  }

  ArgVector = NULL;
  ArgCount = 0;
  /* Cut command line into arguments */
  while (*p) {
    while (*p == ' ' || *p == '\t')
      p++;
    /* At start of argument or EOT */
    if (*p) {
      if (*p == '"') { /* Quoted argument, ignore spaces */
	p++;
	/* Make room for argument */
	ArgVector = (char**)REALLOC(ArgVector, (ArgCount+1)*sizeof(char*));
	ArgVector[ArgCount++] = p;
	/* Skip argument */
	while (*p && *p != '"')
	  p++;
	/* Terminate argument string */
	if (*p)
	  *p++ = '\0';
      } else {
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
}

static int GetWindowsVersion(){
  /* Return values:
     0 for win32s, 1 for win95 and 2 for winnt.
     #define VER_PLATFORM_WIN32s	(0)
     #define VER_PLATFORM_WIN32_WINDOWS (1)
     #define VER_PLATFORM_WIN32_NT	(2)
     */
  
  OSVERSIONINFO osvi;
  memset(&osvi, 0, sizeof(OSVERSIONINFO));
  osvi.dwOSVersionInfoSize = sizeof (OSVERSIONINFO);
  GetVersionEx (&osvi);
  return osvi.dwPlatformId;
}

int isWinNT() {
  return GetWindowsVersion()==VER_PLATFORM_WIN32_NT;
}

int isWin95() {
  return GetWindowsVersion()==VER_PLATFORM_WIN32_WINDOWS;
}

int isWin32s() {
  return GetWindowsVersion()==VER_PLATFORM_WIN32s;
}

#endif /* nti */
