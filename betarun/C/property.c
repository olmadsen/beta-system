/*
 * BETA RUNTIME SYSTEM, Copyright (C) 1990 Mjolner Informatics Aps.
 * Mod: $Id: property.c,v 1.13 1992-09-03 12:54:26 beta Exp $
 * by Lars Bak, Peter Andersen, Peter Orbaek and Tommy Thorn
 */

/* EXPORTING:
 *
 *  SetupProperties( betart)
 *    char *betart;
 *  Ex: SetupProperties("InfoIOA:IOA#2333");
 */
#include <stdio.h>
#include "beta.h"

static int intScan(), CmpStr();

/* 
 * If you want to add properties, change BooleanProperty or ValueProperty. 
 */

#define ENTRY( string, code) if( CmpStr(name, string)   ){ code; return; }

static BooleanProperty( name)
  char *name;
{
  ENTRY("Info",     Info0 = TRUE);

  ENTRY("InfoIOA",  InfoIOA = TRUE);
  ENTRY("InfoAOA",  InfoAOA = TRUE);
  ENTRY("InfoLVRA", InfoLVRA = TRUE);
  ENTRY("InfoCBFA", InfoCBFA = TRUE);
  ENTRY("InfoLVRAAlloc", InfoLVRAAlloc = TRUE);

#ifdef RTDEBUG
  ENTRY("DebugIOA",  DebugIOA = TRUE);
  ENTRY("DebugAOA",  DebugAOA = TRUE);
  ENTRY("DebugLVRA", DebugLVRA = TRUE);
#endif

  ENTRY("InfoS", isStatRecordOn = TRUE);

  /* IF NO ENTRY IS SELECTED PLEASE REPORT UNKNOWN PROPERTY */
  fprintf( output, "#Property '%s' not known!\n", name);
}

static ValueProperty( name, value)
  char *name, *value;
{
  ENTRY("IOA",  IOASize       = 1024 * intScan(name, value));
  ENTRY("AOA",  AOABlockSize  = 1024 * intScan(name, value));
  ENTRY("LVRA", LVRABlockSize = 1024 * intScan(name, value));
  ENTRY("CBFA", CBFABlockSize = 1024 * intScan(name, value));
#ifdef DOT
  ENTRY("DOT",  DOTSize       =    4 * intScan(name, value));
#endif

  ENTRY("IOAPercentage",
        IOAPercentage = intScan(name, value);
        if( IOAPercentage < 3 ){
	  fprintf( output, "#IOAPercentage (%d) is to low, adjusted to 3\n",
		   IOAPercentage);
	  LVRAPercentage = 3;
	}
	if( IOAPercentage > 40 ){
	  fprintf( output, "#IOAPercentage (%d) is to high, adjusted to 40\n",
		   IOAPercentage);
	  IOAPercentage = 40;
	});

  ENTRY("AOAMinFree",
	AOAMinFree = 1024 * intScan(name, value); AOAPercentage = 0;);
  ENTRY("AOAPercentage",
	AOAPercentage = intScan(name, value);
	AOAMinFree = 0;
        if( AOAPercentage < 3 ){
	  fprintf( output, "#AOAPercentage (%d) is to low, adjusted to 3\n",
		  AOAPercentage);
	  AOAPercentage = 3;
	}
	if( AOAPercentage > 97 ){
	  fprintf( output, "#AOAPercentage (%d) is to high, adjusted to 3\n",
		  AOAPercentage);
	  AOAPercentage = 97;
	});

  ENTRY("LVRAMinFree",
	LVRAMinFree = 1024 * intScan(name, value); LVRAPercentage = 0;);
  ENTRY("LVRAPercentage",
	LVRAPercentage = intScan(name, value);
	LVRAMinFree = 0;
        if( LVRAPercentage < 3 ){
	  fprintf( output, "#LVRAPercentage (%d) is to low, adjusted to 3\n",
		   LVRAPercentage);
	  LVRAPercentage = 3;
	}
	if( LVRAPercentage > 97 ){
	  fprintf( output, "#LVRAPercentage (%d) is to high, adjusted to 3\n",
		   LVRAPercentage);
	  LVRAPercentage = 97;
	});

  ENTRY("InfoFile",
    if( !(output = fopen(value, "w")) ){
      fprintf( stderr, "#InfoFile '%s' couldn't be opened, stderr is used\n", value);
      output = stderr;
    });
   
  /* IF NO ENTRY IS SELECTED PLEASE REPORT UNKNOWN PROPERTY */
  fprintf( output, "#Property '%s#%s' not known!\n", name, value);
}

/**********************************************************/
/* PRIVATE PART ---- do'nt change below ---- PRIVATE PART */
/**********************************************************/

static int intScan( name, value)
  char *name, *value;
{
  int result = 0; char *pointer = value;

  while( *pointer != '\0' ){
    result *= 10;
    if( (*pointer >= '0') && ( *pointer <= '9') )
      result = result + (int) *pointer++ - (int) '0';
    else{
      fprintf( output,"#Property '%s': '%s' is not an integer, 0 is assumed!\n", name, value);
      return 0;
    }
  }
  return result;
}

/* Compare two null terminated strings. */
static int CmpStr( s1, s2)
   char *s1, *s2;
{
  while( *s1 == *s2 ){
    if( *s1 == '\0' ) return 1;
    s1++; s2++;
  }
  return 0;
}

SetupProperties( betart)
  char *betart;
{ int pos; int start = 0; int finish; int i, sep;
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
       * Items can have two forms  "Info0" or "LVRA#1400".
       */
      i = start;
      while( (betart[i] != '#') && (i < pos) ) i++;
      if( betart[i] == '#' )  sep = i; else sep = -1;
      if( sep >= 0 ){
        /* the item has the form  "<name>#<value>", where
         * <name>  = betart[start..sep-1] and
         * <value> = betart[sep+1..pos-1].
         */
        if( start < sep ){
          for(i=start; i<sep; i++)  name[i-start]  = betart[i]; name[sep-start]  = '\0';
          for(i=sep+1; i<pos; i++)  value[i-sep-1] = betart[i]; value[pos-sep-1] = '\0';
          ValueProperty( name, value);
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
}  
