/*
 * BETA RUNTIME SYSTEM, Copyright (C) 1990-2002 Mjolner Informatics A/S
 * property.c
 * by Lars Bak, Peter Andersen, Peter Orbaek, Tommy Thorn, Jacob Seligmann and S|ren Brandt
 */

/* EXPORTING:
 *
 *  SetupProperties(char *betart)
 *    
 *  Ex: SetupProperties("InfoIOA:IOA#2333");
 */
#include "beta.h"

#ifdef ppcmac
#include <Files.h>
#endif

#define MAX_NAME 100
#define MAX_VALUE 100

static long intScan(char*,char*);
static void ValueProperty(char *name, char *value);
static void BooleanProperty(char *name);

#undef HELP_PROPERTY
#ifdef HELP_PROPERTY
/* FIXME: Does not work - only reports the used entries */
static int   PropertiesSize=0;
static char *Properties=0;
static int   ReportProperties;
#endif /* HELP_PROPERTY */


/* Compare two null terminated strings non case sensitively */
int EqualNCS(char *s1, char *s2)
{
  /*fprintf(output, "EqualNCS:%s:%s:", s1, s2);*/
  while (tolower(*s1) == tolower(*s2)) {
    if (*s1 == '\0') {
      /*fprintf(output, "1\n");*/
      return 1;
    }
    s1++; s2++;
  }
  /*fprintf(output, "0\n");*/
  return 0;
}

/* 
 * If you want to add properties, change BooleanProperty or ValueProperty. 
 */

#ifdef HELP_PROPERTY
#define ENTRY(string, code)                                      \
  if (EqualNCS(name, string)){                                   \
    if (!Properties){                                            \
      PropertiesSize = MAX_NAME;                                 \
      Properties = (char*)MALLOC(PropertiesSize*sizeof(char));   \
      Properties[0]=0;                                           \
    } else {                                                     \
      if (strlen(Properties)+strlen(name)+5>PropertiesSize){     \
        PropertiesSize += 5+MAX_NAME;                            \
        Properties = (char*)                                     \
          REALLOC(Properties, PropertiesSize*sizeof(char));      \
      }                                                          \
    }                                                            \
    strcat(Properties, "  ");                                    \
    strcat(Properties, name);                                    \
    strcat(Properties, "\n");                                    \
    code;                                                        \
    return;                                                      \
  }
#else /* !HELP_PROPERTY */
#define ENTRY(string, code)                                      \
  if (EqualNCS(name, string)){                                   \
    code;                                                        \
    return;                                                      \
  }
#endif /* HELP_PROPERTY */

static void BooleanProperty(char *name)
{
  ENTRY("SkipDumpStack",     SkipDumpStack = TRUE); 
#ifdef HELP_PROPERTY
  ENTRY("Help",     ReportProperties = TRUE); 
#endif /* HELP_PROPERTY */
  ENTRY("Info",     Info0 = TRUE); 
  ENTRY("InfoIOA",  InfoIOA = TRUE);
  ENTRY("InfoAOA",  InfoAOA = TRUE);
  ENTRY("InfoAOAUse",  InfoAOAUse = TRUE);
  ENTRY("InfoVars",  InfoVars = TRUE);
  ENTRY("StatAOA",  StatAOA = TRUE);
  ENTRY("InfoCBFA", InfoCBFA = TRUE);
  ENTRY("InfoDOT", InfoDOT = TRUE);
  ENTRY("InfoLabels", InfoLabels = TRUE);
  ENTRY("InfoAll", 
	Info0 = TRUE; InfoIOA = TRUE; InfoAOA = TRUE; 
	InfoCBFA = TRUE; 
	InfoHeapUsage = TRUE; InfoVars = TRUE;
	);
  ENTRY("InfoHeapUsage", InfoHeapUsage = TRUE);
  ENTRY("InfoHeap", InfoHeapUsage = TRUE);
  ENTRY("QuaCont",  QuaCont = TRUE);
  ENTRY("NoAOAGc",  noAOAGC = TRUE);
  ENTRY("SimpleDump",  SimpleDump = TRUE);
  ENTRY("NoDumpDialog",  NoDumpDialog = TRUE);
#ifdef sparc
  ENTRY("SuspCont", SuspCont = TRUE);
#endif
  ENTRY("TraceFindActivation", TraceFindActivation = TRUE); 
  ENTRY("TFA", TraceFindActivation = TRUE); 
#ifdef PROTO_STATISTICS
  ENTRY("NoProtoStatistics", ProtoStatistics = FALSE); 
#endif /* PROTO_STATISTICS */

#ifdef RTDEBUG
  ENTRY("DebugIOA",   DebugIOA = TRUE);
  ENTRY("CheckHeap",   CheckHeap = TRUE);
  ENTRY("PrintStackAtIllegal",   PrintStackAtIllegal = TRUE);
  ENTRY("PSAI",   PrintStackAtIllegal = TRUE);
  ENTRY("StopAtIllegal",   StopAtIllegal = TRUE);
  ENTRY("SAI",   StopAtIllegal = TRUE);
  ENTRY("DebugAlloI",   DebugAlloI = TRUE);
  ENTRY("DebugCBFA",  DebugCBFA = TRUE);
  ENTRY("DumpAOA",   DumpAOA = TRUE);
  ENTRY("DebugAOA",   DebugAOA = TRUE);
  ENTRY("DebugAOAToIOA",   DebugAOAtoIOA = TRUE);
  ENTRY("DebugLIN",  DebugLIN = TRUE);
  ENTRY("DebugStack", DebugStack = TRUE);
  ENTRY("DebugStackObj", DebugStackObj = TRUE);
  ENTRY("DebugSockets", DebugSockets = TRUE);
  ENTRY("DebugStrongIsObject", DebugStrongIsObject = TRUE);
  ENTRY("FastIsObject", FastIsObject = TRUE);
  ENTRY("NoHeapClear", NoHeapClear = TRUE);
  ENTRY("IgnoreUGC", 
	DoUGC = 0; 
	fprintf(output, 
		"Unconditional GC deactivated via IgnoreUGC property in BETART\n");
	);
  ENTRY("DebugLabels", DebugLabels = TRUE);
  /* Trace GroupName() */
  ENTRY("TraceGroup", TraceGroup = TRUE); 
  /* Trace DisplayBetaStack() */
  ENTRY("TraceDump", TraceDump = TRUE);
  /* Trace find_activation() */
  /* Trace search for prefix in ObjectDescription */
  ENTRY("TraceCodeEntry", TraceCodeentry = TRUE); 
#ifdef MT
  ENTRY("DebugMT", DebugMT = TRUE);
#endif
#ifdef RTVALHALLA
  ENTRY("DebugValhalla", DebugValhalla = TRUE);
  ENTRY("TraceValhallaComm", TraceValhallaComm = TRUE);
#endif
#ifdef MT
  ENTRY("DebugAll", 
	DebugMT = TRUE;
	DebugIOA = TRUE; 
	DebugAOA = TRUE;
	DebugAOAtoIOA = TRUE;
	DebugStack=TRUE;
	DebugStackObj=TRUE;
	DebugCBFA=TRUE);
#else
  ENTRY("DebugAll",   
	DebugIOA = TRUE; 
	DebugAOA = TRUE;
	DebugAOAtoIOA = TRUE;
        DebugLIN = TRUE; 
	DebugStack=TRUE; 
	DebugCBFA=TRUE);
#endif
#endif

#ifdef PERSIST
#ifdef RTINFO
  ENTRY("InfoPersistence", InfoPersistence = TRUE);
#endif /* RTINFO */
#endif /* PERSIST */
  ENTRY("timeIOA", timeIOA = TRUE);
  ENTRY("timeAOA", timeAOA = TRUE);
  ENTRY("InfoS", isStatRecordOn = TRUE);
  ENTRY("NoCatch", NoCatchException = TRUE);
  ENTRY("NoCatchException", NoCatchException = TRUE);

  /* IF NO ENTRY IS SELECTED REPORT UNKNOWN PROPERTY */
  { char buf[512];
    sprintf( buf, "Property '%s' not known.", name);
    Notify(buf);
  }
}

#if defined(MAC)

static char *strdup(char *str)
{
	char *newstr;
	int i;
	
	newstr = malloc(strlen(str)+1);
	i = 0;
	while(newstr[i]=str[i])
		i++;
	return newstr;
}


#endif

static void ValueProperty(char *name, char *value)
{
  char buf[512];
  
  

#ifdef RTVALHALLA
  ENTRY("valhallaid", valhallaID = strdup (value));
#endif /* RTVALHALLA */

#ifdef RTDEBUG
  ENTRY("debugstackatgcnum", DebugStackAtGcNum = intScan(name, value));
#endif

  ENTRY("ioa", 
	IOASize = 1024 * intScan(name, value);
        if(IOASize < 1024){
	  sprintf(buf, "IOA size (%dKb) is too low, adjusted to 1Kb.",
		  (int)IOASize/1024);
	  Notify(buf);
	  IOASize = 1024;
	}
	);
#ifdef RTDEBUG
  ENTRY("ioabytes", 
	IOASize = intScan(name, value);
	);
#endif
#ifdef MT
  ENTRY("ioaslicesize",
	IOASliceSize = 1024 * intScan(name, value); 
	NumIOASlices = 0;
	);
  ENTRY("numioaslices",
	NumIOASlices = intScan(name, value); 
	IOASliceSize = 0;
	);
#endif

  ENTRY("cbfa", 
	CBFABlockSize = 1024 * intScan(name, value);
	if(CBFABlockSize < 1024){
	  sprintf(buf, "CBFA block size (%dKb) is too low, adjusted to 1Kb.",
		  (int)CBFABlockSize/1024);
	  Notify(buf);
	  CBFABlockSize = 1024;
	}
	);

  ENTRY("ioapercentage",
        IOAPercentage = intScan(name, value);
	if( IOAPercentage > 100 ){
	  sprintf( buf, "IOAPercentage (%d) is too high, adjusted to 100.",
		   (int)IOAPercentage);
	  Notify(buf);
	  IOAPercentage = 100;
	});

  ENTRY("aoaminfree",
	AOAMinFree = 1024 * intScan(name, value); );
  ENTRY("aoapercentage",
	AOAPercentage = intScan(name, value);
	if( AOAPercentage > 50 ){
	  sprintf(buf, "AOAPercentage (%d) is too high, adjusted to 50.",
		  (int)AOAPercentage);
	  Notify(buf);
	  AOAPercentage = 50;
	});


#ifdef MAC
#define MacCode(code) code
#else
#define MacCode(code)
#endif /* MAC */

  ENTRY("infofile",
	if( (output = fopen(value, "w")) ){
	  MacCode(MakeMPWFile(value));
	} else {
	  output = stderr;
	  sprintf(buf, "InfoFile '%s' couldn't be opened, stderr is used", value);
	  Notify(buf);
	});
  
  
  /* IF NO ENTRY IS SELECTED REPORT UNKNOWN PROPERTY */
  { 
    sprintf(buf, "Property '%s=%s' not known.", name, value);
    Notify(buf);
  }
}

/**********************************************************/
/* PRIVATE PART ---- don't change below ---- PRIVATE PART */
/**********************************************************/

static long intScan( name, value)
  char *name, *value;
{
  long result = 0; char *pointer = value;

  while( *pointer != '\0' ){
    result *= 10;
    if( (*pointer >= '0') && ( *pointer <= '9') )
      result = result + (long) *pointer++ - (long) '0';
    else{
      char buf[512];
      sprintf(buf,"Property '%s': '%s' is not an integer, 0 is assumed.", name, value);
      Notify(buf);
      return 0;
    }
  }
  return result;
}


void SetupProperties(char *betart)
{ long pos; long start = 0; long finish; long i, sep;
  char name[MAX_NAME];
  char value[MAX_VALUE];

#ifdef HELP_PROPERTY
  ReportProperties = 0;
#endif /* HELP_PROPERTY */
  
  while( (betart[start] == ' ')
	|| (betart[start] == '\t')
	|| (betart[start] == '\n' ) ) start++;
  pos = start;
  while( (betart[pos] != '\0') && (betart[pos] != ':') ) pos++;
  finish = (betart[0] == '\0');
  while( !finish ){
    if( start < pos ){
      /* The item is betart[start..pos-1]. 
       * Items can have two forms  "Info0" or "IOA#1400" or "IOA=1400".
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

#ifdef HELP_PROPERTY
  if (ReportProperties){
    fprintf(output, "The supported entries in \"%s\" are:\n", betart);
    fprintf(output, "%s", Properties);
    fflush(output);
    ReportProperties=0;
  }
#endif /* HELP_PROPERTY */

#if defined(MAC)
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
       sprintf((char*)fname, "%c%s", strlen(infoname), infoname);
       FREE(infoname);
       if (GetFInfo(fname, 0, &fn) != noErr) return;
       fn.fdType = 'TEXT';
       fn.fdCreator = 'MPS ';
       SetFInfo(fname, 0, &fn);
     }
  }
#endif
}  
