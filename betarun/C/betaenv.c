/*
 * BETA RUNTIME SYSTEM, Copyright (C) 1990-94 Mjolner Informatics Aps.
 * by Lars Bak.
 */

#include "beta.h"

#include <stdio.h>

#ifndef DEFAULT_PROPERTY_NAME
#define DEFAULT_PROPERTY_NAME "BETART"
#endif

#ifdef MAC
#include <Memory.h>
#include <Resources.h>

void *ReAlloc(void *p, Size size)
{
	Ptr newp;
	Size oldsize;
	
	
	SetPtrSize(p, size);
	
	if (MemError) {
		oldsize = GetPtrSize(p);
		newp = NewPtr(size);
		if (newp) {
			if (size < oldsize) {
				BlockMove(p, newp, size);
			}
			else {
				BlockMove(p, newp, oldsize);
			}
			DisposePtr(p);
		}
		return newp;
	}
	else {
		return p;
	}
	
	return 0;
}

#endif


#ifdef hppa
void *memalign(size_t align, size_t size) { 
  return ((void*)(((long)malloc(size+align-1)+(align-1))&~(align-1)));
}
#endif

#ifdef macosx
void *memalign(size_t align, size_t size) { 
  return (void *) malloc(size);
}
#endif

void GetBetaEnv()
{
  char *betart;
  
#if defined(MAC)
  char **theHandle;
  long length;
  
  if(betart = getenv(DEFAULT_PROPERTY_NAME)){
    SetupProperties(betart);
  } else {
    if( theHandle = GetNamedResource('STR ',(const unsigned char*)"\pBETART") ){
      betart = *theHandle; length = betart[0];
      betart = strncpy( (Ptr) NewPtr(length+1), &betart[1], length);
      betart[length] = 0; SetupProperties( betart);
    }
    if( theHandle = GetNamedResource('STR ',(const unsigned char*)"\pVALHALLART") ){
      char* valhallaEnv;
	  
      valhallaEnv = *theHandle; length = valhallaEnv[0];
      valhallaEnv = strncpy( (Ptr) NewPtr(length+1), &valhallaEnv[1], length);
      valhallaEnv[length] = 0; SetupProperties( valhallaEnv);
	  RemoveResource(theHandle);
    }
  }
#else /* !MAC */
  if((betart = getenv(DEFAULT_PROPERTY_NAME))){
    DEBUG_CODE({
      fprintf(output, "%s is \"%s\"\n", DEFAULT_PROPERTY_NAME, betart);
    });
    SetupProperties(betart);
  }
#ifdef RTVALHALLA
  { 
    char* valhallart;
    if ((valhallart = getenv ("VALHALLART")))
      SetupProperties(valhallart);
  }
#endif /* RTVALHALLA*/
#endif /* MAC */
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
