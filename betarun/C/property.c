/*
 * BETA RUNTIME SYSTEM, Copyright (C) 1990-94 Mjolner Informatics Aps.
 * property.c
 * by Lars Bak, Peter Andersen, Peter Orbaek, Tommy Thorn, and Jacob Seligmann
 */

/* EXPORTING:
 *
 *  SetupProperties( betart)
 *    char *betart;
 *  Ex: SetupProperties("InfoIOA:IOA#2333");
 */
#include <stdio.h>
#include "beta.h"
#include <ctype.h>

#if defined(macintosh) || defined(MAC)
#include <String.h>
#include <Files.h>
#endif

#ifndef DEMO
static long intScan();
#endif /* !DEMO */

static long CmpStr();

/* 
 * If you want to add properties, change BooleanProperty or ValueProperty. 
 */

#define ENTRY( string, code) if( CmpStr(name, string) ){ code; return; }

static void BooleanProperty(name)
  char *name;
{
   ENTRY("info",     Info0 = TRUE); 
   ENTRY("infoioa",  InfoIOA = TRUE);
   ENTRY("infoaoa",  InfoAOA = TRUE);
   ENTRY("infolvra", InfoLVRA = TRUE);
   ENTRY("infocbfa", InfoCBFA = TRUE);
   ENTRY("infolvraalloc", InfoLVRAAlloc = TRUE);
   ENTRY("infodot", InfoDOT = TRUE);
   ENTRY("infoall", 
	 Info0 = TRUE; InfoIOA = TRUE; InfoAOA = TRUE; 
	 InfoLVRA = TRUE; InfoCBFA = TRUE; InfoLVRAAlloc = TRUE);
   ENTRY("quacont",  QuaCont = TRUE);

#ifdef valhallaRT
   ENTRY("valhallatest", valhallaTest = TRUE);
#endif /* valhallaRT */

#ifdef sparc
  ENTRY("suspcont", SuspCont = TRUE);
#endif

#ifdef RTDEBUG
  ENTRY("debugioa",   DebugIOA = TRUE);
  ENTRY("debugcbfa",  DebugCBFA = TRUE);
  ENTRY("debugaoa",   DebugAOA = TRUE);
  ENTRY("debuglvra",  DebugLVRA = TRUE);
  ENTRY("debugstack", DebugStack = TRUE);
  ENTRY("debugall",   DebugIOA = TRUE; DebugAOA = TRUE;
	DebugLVRA = TRUE; DebugStack=TRUE; DebugCBFA=TRUE);
#endif

  ENTRY("infos", isStatRecordOn = TRUE);

  /* IF NO ENTRY IS SELECTED REPORT UNKNOWN PROPERTY */
  { char buf[100];
    sprintf( buf, "Property '%s' not known.", name);
    Notify(buf);
  }
}

#ifndef DEMO
static void ValueProperty( name, value)
  char *name, *value;
{
#ifdef valhallaRT
  ENTRY("valhallaid", valhallaID = strdup (value));
#endif /* valhallaRT */

  ENTRY("ioa", IOASize = 1024 * intScan(name, value));
  ENTRY("aoa",  
	AOABlockSize  = 1024 * intScan(name, value);
	if (AOAMinFree>AOABlockSize) AOAMinFree=AOABlockSize;
	);
  ENTRY("lvra", 
	LVRABlockSize = 1024 * intScan(name, value);
	if (LVRAMinFree>LVRABlockSize) LVRAMinFree=LVRABlockSize;
	);
  ENTRY("cbfa", CBFABlockSize = 1024 * intScan(name, value));

  ENTRY("ioapercentage",
        IOAPercentage = intScan(name, value);
        if( IOAPercentage < 3 ){
	  char buf[100];
	  sprintf(buf, "IOAPercentage (%d) is too low, adjusted to 3.",
		  (int)IOAPercentage);
	  Notify(buf);
	  IOAPercentage = 3;
	}
	if( IOAPercentage > 40 ){
	  char buf[100];
	  sprintf( buf, "IOAPercentage (%d) is too high, adjusted to 40.",
		   (int)IOAPercentage);
	  Notify(buf);
	  IOAPercentage = 40;
	});

  ENTRY("aoaminfree",
	AOAMinFree = 1024 * intScan(name, value); AOAPercentage = 0;);
  ENTRY("aoapercentage",
	AOAPercentage = intScan(name, value);
	AOAMinFree = 0;
        if( AOAPercentage < 3 ){
	  char buf[100];
	  sprintf(buf, "AOAPercentage (%d) is too low, adjusted to 3.",
		  (int)AOAPercentage);
	  Notify(buf);
	  AOAPercentage = 3;
	}
	if( AOAPercentage > 97 ){
	  char buf[100];
	  sprintf(buf, "AOAPercentage (%d) is too high, adjusted to 97.",
		  (int)AOAPercentage);
	  Notify(buf);
	  AOAPercentage = 97;
	});

  ENTRY("lvraminfree",
	LVRAMinFree = 1024 * intScan(name, value); LVRAPercentage = 0;);
  ENTRY("lvrapercentage",
	LVRAPercentage = intScan(name, value);
	LVRAMinFree = 0;
        if( LVRAPercentage < 3 ){
	  char buf[100];
	  sprintf(buf, "LVRAPercentage (%d) is too low, adjusted to 3.",
		  (int)LVRAPercentage);
	  Notify(buf);
	  LVRAPercentage = 3;
	}
	if( LVRAPercentage > 97 ){
	  char buf[100];
	  sprintf(buf, "LVRAPercentage (%d) is too high, adjusted to 97.",
		  (int)LVRAPercentage);
	  Notify(buf);
	  LVRAPercentage = 97;
	});

  ENTRY("infofile",
    if( !(output = fopen(value, "w")) ){
      char buf[100];
      output = stderr;
      sprintf(buf, "InfoFile '%s' couldn't be opened, stderr is used", value);
      Notify(buf);
    });

   
  /* IF NO ENTRY IS SELECTED REPORT UNKNOWN PROPERTY */
  { char buf[100];
    sprintf(buf, "Property '%s#%s' not known.", name, value);
    Notify(buf);
  }
}
#endif /* DEMO */

/**********************************************************/
/* PRIVATE PART ---- don't change below ---- PRIVATE PART */
/**********************************************************/

#ifndef DEMO
static long intScan( name, value)
  char *name, *value;
{
  long result = 0; char *pointer = value;

  while( *pointer != '\0' ){
    result *= 10;
    if( (*pointer >= '0') && ( *pointer <= '9') )
      result = result + (long) *pointer++ - (long) '0';
    else{
      char buf[100];
      sprintf(buf,"Property '%s': '%s' is not an integer, 0 is assumed.", name, value);
      Notify(buf);
      return 0;
    }
  }
  return result;
}
#endif /* !DEMO */

/* Compare two null terminated strings. s2 points to constant in lower case */
static long CmpStr( s1, s2)
   char *s1, *s2;
{
  while( tolower(*s1) == *s2 ){
    if( *s1 == '\0' )  return 1;
    s1++; s2++;
  }
  return 0;
}

void SetupProperties( betart)
  char *betart;
{ long pos; long start = 0; long finish; long i, sep;
  char name[100];
  char value[100];
  
  while( (betart[start] == ' ')
	|| (betart[start] == '\t')
	|| (betart[start] == '\n' ) ) start++;
  pos = start;
  while( (betart[pos] != '\0') && (betart[pos] != ':') ) pos++;
  finish = (betart[0] == '\0');
  while( !finish ){
    if( start < pos ){
      /* The item is betart[start..pos-1]. 
       * Items can have two forms  "Info0" or "LVRA#1400" or "LVRA=1400".
       */
      i = start;
      while( (betart[i] != '#') && (betart[i] != '=') && (i < pos) ) i++;
      if( (betart[i] == '#') || (betart[i] == '=') ) sep = i; else sep = -1;
      if( sep >= 0 ){
        /* the item has the form  "<name>#<value>" or "<name>=<value>", where
         * <name>  = betart[start..sep-1] and
         * <value> = betart[sep+1..pos-1].
         */
        if( start < sep ){
          for(i=start; i<sep; i++)  name[i-start]  = betart[i]; name[sep-start]  = '\0';
          for(i=sep+1; i<pos; i++)  value[i-sep-1] = betart[i]; value[pos-sep-1] = '\0';
#ifndef DEMO
          ValueProperty( name, value);
#endif
        }
      }else{
        /* the item has the form  "<name>", where <name>  = betart[start..pos-1]. */
        for(i=start; i<pos; i++)  name[i-start] = betart[i]; name[pos-start] = '\0';
	if( start < pos)
	  BooleanProperty( name);
      }
    }
    finish = (betart[pos] == '\0');
    if( !finish ){
      pos++; start = pos;
      while( (betart[start] == ' ')
	    || (betart[start] == '\t')
	    || (betart[start] == '\n') ) start++;
      pos = start;
      while( (betart[pos] != '\0') && (betart[pos] != ':') ) pos++;
    }
  }
#if defined(macintosh) || defined(MAC)
  if ((output == stderr) && StandAlone) {
     char *infoname; 
     char *execname;
     execname = ArgVector[0]; /* Always right ??? */
     infoname = (char *)MALLOC(strlen(execname)+9)
       /* Allow for ".info", possibly 3 digits, and NULL */;
     strcpy(infoname, execname);
     strcat(infoname, ".info");
     if ((output = fopen(infoname,"w")) == NULL){
       /* failed to open default info file */
       int i=2;
       do { sprintf(infoname, "%s.info%d", execname, i++);
          } while ((output = fopen(infoname,"w")) == NULL);
     }
     /* Set file type and creator to make xxx.info an MPW file */
     { FInfo fn;
       Str255 fname;
       sprintf(fname, "%c%s", strlen(infoname), infoname);
       FREE(infoname);
       if (GetFInfo(fname, 0, &fn) != noErr) return;
       fn.fdType = 'TEXT';
       fn.fdCreator = 'MPS ';
       SetFInfo(fname, 0, &fn);
     }
  }
#endif
}  
