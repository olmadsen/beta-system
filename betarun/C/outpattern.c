/*
 * BETA RUNTIME SYSTEM, Copyright (C) 1990-94 Mjolner Informatics Aps.
 * outpattern.c
 * by Lars Bak, Peter Andersen, Peter Orbaek, Tommy Thorn, and Jacob Seligmann
 */

#include "beta.h"

#if defined(macintosh) ||defined(MAC)
#include <String.h>
#include <Files.h>
#endif

#define MAXINT (signed long)0x7fffffff
#define MININT (signed long)0x80000000

#ifdef RTDEBUG
/* #define DO_TRACE_DUMP  */ /* Trace DisplayBetaStack() */
/* #define DO_TRACE_GROUP */ /* Trace GroupName() */
#endif

#ifdef DO_TRACE_DUMP
#define TRACE_DUMP(code) code
#else
#define TRACE_DUMP(code)
#endif
#ifdef DO_TRACE_GROUP
#define TRACE_GROUP(code) code
#else
#define TRACE_GROUP(code)
#endif

#ifdef RTVALHALLA
#include "valhallaComm.h"
#endif RTVALHALLA

#ifdef macintosh
#define JUMP_TABLE(addr) (*(long *)(((long)(addr))+2))
#define G_Part(proto) (long) JUMP_TABLE(proto->GenPart)
#else
#ifdef __powerc
#define G_Part(proto) ((long) *(long*)proto->GenPart)
#else
#define G_Part(proto) (long) proto->GenPart
#endif
#endif

static long M_Part(ref(ProtoType) proto)
     /* Return the address og of the M-entry for the prototype proto.
      * Use the fact, that if the corresponding object has a do part, 
      * then above the prototype, the INNER table can be used to find
      * the M-entry:
      *
      *        long: _Return
      *        long: M-entry
      *        long: M-entry of prefix
      *        long: M-entry of prefix-prefix
      *        ...
      * proto: ...
      *
      * Should ONLY be called for a prototype which is known to correspond to 
      * object with do-part.
	  * 
	  * CRTS: prototype is, e.g.
	  * long T18TSTVIRT[]={
	        (48<<16)|(0xffff&2),
			(long)&G18TSTVIRT,
			(long)T15TSTVIRT,
			(4<<16)|(0xffff&0),
			(1<<16)|(0xffff&1090),
			0,
			0,
			(long)&M15TSTVIRT, M-entry of prefix
			0,
			(long)&M18TSTVIRT, M-entry
			0,
			(long)&Return,
			(0<<16)|(0xffff&10),
			0,
			(long)&V20
		}; / *innerTableSize=3 * /
      */
{
  extern void Return();
  long *m;
  long *r;
  register long ret= (long)Return;
  
#ifdef hppa
  asm volatile ("
	LDIL L'Return, %0
	LDO  R'Return(%0),%0
	": "=r" (ret));
#endif

#ifndef crts
  m = (long *)proto - 1;
  r = m - 1;
  while ( (*r != ret) && (r != 0) ){
    /* r != 0 just to avoid segmentation fault if something is wrong */
    m = r;
    r = m - 1;
  }
#else /* crts */
  m = (long *)proto + 7; /* first M-Part */
  r = m + 2; /* next M-Part (possible Return) */
  while ((r != 0) && (*r != ret)){
    /* r != 0 just to avoid segmentation fault if something is wrong */
    m = r;
    r = m + 2;
  }
#endif /* !crts */
  
  /* fprintf(output, "*m: 0x%x\n", *m); fflush(output); */
#ifdef macintosh
  return JUMP_TABLE(*m);
#else
#ifdef __powerc
  return *(long*)(*m);
#else
  return *m;
#endif
#endif
}

static char *machine_name()
{
#ifdef crts
#ifdef SGI
return "(sgi)";
#endif
#ifdef SUN4S
return "(sun4s)";
#endif
#ifdef __powerc
return "(ppc)";
#endif
#endif /* crts */

  /* Sun variants */
#ifdef sun
#ifdef sparc
#ifdef sun4s
  return "(sun4s)";
#else
  return "(sun4)";
#endif
#else
  return "(sun3)";
#endif
#endif
  
  /* HP variants */
#ifdef hpux
#ifdef hppa
  /*return "(snake)";*/
  return "(hpux9pa)";
#else
  return "(hpux8)";
#endif
#endif
  
  /* Macintosh */
#ifdef macintosh
  return "(mac)";
#endif

  /* Linux */
#ifdef linux
  return "(linux)";
#endif
  
  /* NTI */
#ifdef nti
  return "(nti)";
#endif
  
  /* default */
  return ""; 
}

#ifdef valhallaRT
extern int valhallaOnError (long,ref(Object),long*,long*,long);
/*    long errorNumber;
 *    ref(Object) theObj;
 *    long* thePC;
 *    long* theSP;
 *    long theSignal; */
#endif

static ptr(char) ProtoTypeName(theProto)
     ref(ProtoType) theProto;
{
  ref(GCEntry) stat = cast(GCEntry) ((long) theProto + theProto->GCTabOff);
  ptr(short) dyn;
  
  while (*(short *) stat) stat++;	/* Step over static gc entries */ 
  dyn = ((short *) stat) + 1;		/* Step over the zero */
  while (*dyn++);			/* Step over dynamic gc entries */

#if defined(linux) || defined(nti)
  /* Step over little endian long/short/real position information */
  {
    dyn += (theProto->Size+15)>>4; /* step over 'long' bit vector */
    while (*dyn++);                /* step over 'short' list */
    while (*dyn++);                /* step over 'real' list */
  }
#endif

#ifdef crts
/* skip 0's: at this point dyn points to prototype:
  dyn      -> .half 0
	      .half 0
	      .half 0 
	      .long ptr to ptr to text
  * or
  dyn      -> .half 0
	      .half 0
	      .long ptr to ptr to text
  */
  while ((*dyn)==0) dyn++;
  return (char*) (**(long**)dyn);
#else
  return (ptr(char)) dyn;
#endif
}

/* c_on_top is used by beta.dump (only) to determine if things on top
 * of the stack are outside beta-code, i.e. a program has failed in 
 * external code.
 */
static signed long c_on_top;

/* NextGroup is used by objectserver/persistent store to scan through the
 * data-segments, in order to implement InitFragment.
 * It must be non-static.
 */

#ifdef crts

extern void BETA_code_end(void);

/* NameOfGroup return the groupName corresponding to the group_header
 * given as parameter. */
char* NameOfGroup (group_header *group)
{
   return (char*) (*group->form_id);
}

static long* CURRENT_BETA_DATA;
group_header* NextGroup (group_header* current)
{ 
  if (current) {
    CURRENT_BETA_DATA++;
    /*DEBUG_CODE(fprintf (output, "NextGroup. current = 0x%x\n", (long)CURRENT_BETA_DATA));*/
    return (group_header *)*CURRENT_BETA_DATA;
  } else {
    CURRENT_BETA_DATA= (long*) &BETA_data1;
    /*DEBUG_CODE(fprintf (output, "NextGroup. current = 0x%x\n", (long)CURRENT_BETA_DATA));*/
    return (group_header *)*CURRENT_BETA_DATA;
  }
}

int IsBetaPrototype(group_header *gh, long data_addr) 
{ long* proto=gh->protoTable;
  int i;
  for (i=0; i<gh->NoOfPrototypes; i++)
    if ((*proto)==data_addr) 
       return 1;
     else
       proto++;
  return 0;
}

/* GroupName is used by DisplayBetaStack (beta.dump) and objinterface.bet.
 * It must be non-static.
 */
char *GroupName(long address, int isCode)
{
  group_header *group;
  group_header *current;
  group_header *last;
  signed long dist, distance;
  
  TRACE_GROUP(fprintf (output, 
		       "GroupName(addr: 0x%x, %s)\n",
		       (int)address,
		       isCode ? "code" : "data"));

  current = last = group = NextGroup (0);  /* first (betaenv) data segment */
#ifdef __powerc
  if (isCode && (address<(*(long*)current->code_start))) { /* code addr < betaenv code start */
#else
  if (isCode && ((long*)address<current->code_start)) { /* code addr < betaenv code start */
#endif
     c_on_top++;
     TRACE_GROUP(fprintf (output, "c_on_top\n"));
     return ""; 
  }
  distance = MAXINT;
  
  while (current){
    
    if (!isCode) { /* data address; try find a Prototype... */
       if (IsBetaPrototype(current,address))
	  return NameOfGroup (current);
    } else {
#ifdef __powerc
      dist = address - (*(long*)current->code_start);
#else
      dist = address - (long)current->code_start;
#endif
      if (dist >= 0 && dist < distance) {
        distance = dist;
        group = current;
      }
    }
    TRACE_GROUP(if (isCode){
      fprintf(output, 
	      " cur->code: 0x%x-0x%x, dist: %d: %s\n", 
	      (int)current->code_start,
	      (int)current->code_end,
	      (int)distance, 
	      NameOfGroup(current));
    } else {
      fprintf(output, 
	      " cur: 0x%x, dist: %d: %s\n", 
	      (int)current,
	      (int)distance, 
	      NameOfGroup(current));
    });
    last = current;
    current = NextGroup (current);
  }
  if (isCode && (address>(long)BETA_code_end)) { /* code addr > code end */
    c_on_top++; 
    return ""; 
  } else {
    /* GroupName succeeded. From now on we are in the beta-stack */
    c_on_top=MININT;
  }

  return NameOfGroup (group);
}

#else /* !crts */

/* NameOfGroup return the groupName corresponding to the group_header
 * given as parameter. */
char* NameOfGroup (struct group_header *group)
{
   return (char *) &(group->protoTable[(group->protoTable[0]) + 1]);
}

group_header* NextGroup (group_header* current)
     /* Return group in executable following current. 
      * If current is NULL, first group is returned. */
{ 
  long *limit;

  /*DEBUG_CODE(fprintf (output, "NextGroup. current = 0x%x\n", current));*/
  
  if (current) {
    /* Get next data segment if any. Padding by linker 
     * may have moved it some longs down */
    current=current->next;

    limit = (long *) current + 10;
    if (limit > (long *) &BETA_end) limit = (long *) &BETA_end;

    for (; (long*) current < limit; ((long*)current)++) {
      if (current->self == current) {
	return current;
      }
      /*DEBUG_CODE(fprintf (output, "NextGroup pad\n"));*/
    }
    /* No next group. */
    return 0;
  } else {
    return (struct group_header *)&BETA_data1;
  }
}

/* GroupName is used by DisplayBetaStack (beta.dump) and objinterface.bet.
 * It must be non-static.
 */
char *GroupName(long address, int isCode)
{
  group_header *group;
  group_header *current;
  group_header *last;
  signed long dist, distance;
  
  TRACE_GROUP(fprintf (output, 
		       "GroupName(addr: 0x%x, %s)\n",
		       (int)address,
		       isCode ? "code" : "data"));

  current = last = group = NextGroup (0);  /* first (betaenv) data segment */
  if (
#ifndef macintosh
      (isCode && (address<current->code_start)) /* code addr < betaenv code start */
      ||
#endif
      (!isCode && (address<(long)current))){    /* data addr < betaenv data start */
    c_on_top++;
    TRACE_GROUP(fprintf (output, "c_on_top\n"));
    return ""; 
  }
  distance = MAXINT;
  
  while (current){
    
    /* Check if the address is closer to the start 
     * of current segment than previous segments 
     */
    if (isCode)
      dist = address - (long)current->code_start;
    else
      dist = address - (long) current;
    if (dist >= 0 && dist < distance) {
      distance = dist;
      group = current;
    }
    TRACE_GROUP(if (isCode){
      fprintf(output, 
	      " cur->code: 0x%x-0x%x, dist: %d: %s\n", 
	      (int)current->code_start,
	      (int)current->code_end,
	      (int)distance, 
	      NameOfGroup(current));
    } else {
      fprintf(output, 
	      " cur: 0x%x, dist: %d: %s\n", 
	      (int)current,
	      (int)distance, 
	      NameOfGroup(current));
    });
    last = current;
    current = NextGroup (current);
  }
  if (
#ifndef macintosh
      (isCode && (address>last->code_end))       /* code addr > code end */
      || 
#endif
         (!isCode && (address>(long)last->next)) ){ /* data addr > data end */
    c_on_top++; 
    return NULL; 
  } else {
    /* GroupName succeeded. From now on we are in the beta-stack */
    c_on_top=MININT;
  }

  return NameOfGroup (group);
}

#endif

static void ObjectDescription(ref(Object) theObj, long retAddress, char *type, int print_origin)
{
  signed long    gDist=MAXINT, mDist=MAXINT, activeDist=0;
  ref(ProtoType) theProto=theObj->Proto;
  ref(ProtoType) activeProto=theProto;
  char *groupname;
  long mPart = M_Part(theProto);
  long gPart = G_Part(theProto);

  if (theObj==(struct Object *)BasicItem){
    /* BasicItem will be shown as component */
    return;
  }
  
  if (retAddress) {
    /* Find the active prefix level based on the retAddress.
     * Here we use both the G-entry and the M-entry. 
     * The prefix we are in is the one, where the distance from the 
     * G-entry or M-entry of the corresponding prefix-level
     * to retAddress is smallest.
     */
    
    gDist  = retAddress - gPart; 
    /* fprintf(output, "gDist: 0x%x\n", gDist); fflush(output); */
    mDist  = retAddress - mPart;
    /* fprintf(output, "mDist: 0x%x\n", mDist); fflush(output); */
    if (gDist < 0) gDist = MAXINT;
    if (mDist < 0) mDist = MAXINT;
    activeDist = (gDist<mDist) ? gDist : mDist;
    
    while(theProto->Prefix && 
	  theProto->Prefix->Prefix != theProto->Prefix){
      theProto = theProto->Prefix;
      mPart = M_Part(theProto);
      gPart = G_Part(theProto);
      if((retAddress - gPart > 0) &&
	 (retAddress - gPart < activeDist)){ 
	activeProto = theProto;
	activeDist  = gDist = retAddress - gPart; 
	/* fprintf(output, "gDist: 0x%x\n", gDist); fflush(output); */
      }
      if((retAddress - mPart > 0) &&
	 (retAddress - mPart < (long) activeDist)){ 
	activeProto = theProto;
	activeDist  = mDist = retAddress - mPart; 
	/* fprintf(output, "mDist: 0x%x\n", mDist); fflush(output); */
      }
    }
    if (activeDist == MAXINT) return;
    TRACE_GROUP(fprintf(output, "Calling GroupName with return address\n"));
    groupname = GroupName(retAddress,1);
  } else {
    /* retAddress == 0 */
    TRACE_GROUP(fprintf(output, "Calling GroupName with %s\n",
			(activeDist == gDist) ? "gPart" : "mPart"
			));
    groupname = (activeDist == gDist) ? GroupName(gPart,1) : GroupName(mPart,1);
  }
  
  theProto = theObj->Proto;

  if (c_on_top>0){
    /* c_on_top may have been set by GroupName if there is one or more C-frame(s)
     * on top of the stack
     */
    if (c_on_top == 1){
      c_on_top++; /* Print only the first time */
      TRACE_DUMP(fprintf(output, "  top: "));
      fprintf(output, "  [ EXTERNAL ACTIVATION PART ]\n");
    } 
    return;
  }

  if (groupname==NULL){
    /* GroupName failed, and since we reached this point, it was not
     * due to external part on top of stack.
     */
    TRACE_DUMP(fprintf(output, ">>> GroupName failed for object 0x%x\n", (int)theObj));
    return;
  }  
  
  if (activeDist == gDist)
    fprintf(output,"  allocating %s ", type);
  else
    fprintf(output,"  %s ", type);
  
  if(theProto==activeProto || /* active prefix */
     (!activeProto && 
      theProto->Prefix &&
      theProto->Prefix->Prefix==theProto->Prefix)) /* no prefix */
    fprintf(output,"<%s>", ProtoTypeName(theProto));
  else
    fprintf(output,"%s", ProtoTypeName(theProto));
  
  /* Print chain of prefixes */
  while(theProto->Prefix &&
	theProto->Prefix->Prefix != theProto->Prefix){
    theProto = theProto->Prefix;
    if( theProto == activeProto )
      fprintf(output,"<%s>", ProtoTypeName(theProto));
    else
      fprintf(output,"%s", ProtoTypeName(theProto));
  }
  fprintf(output," in %s\n", groupname);
  if (print_origin){
    long addr;
    ref(Object)    staticObj=0;
    
    /* Print Static Environment Object. */

    theProto = theObj->Proto;
    if (!activeProto) activeProto = theProto;
    if (!activeProto) return;
    addr=(long)theObj + (4*(long)activeProto->OriginOff);
    if (addr) 
      staticObj = *(handle(Object))addr;
    else
      staticObj = 0;
    if( isSpecialProtoType(staticObj->Proto) ){
      switch ((long) staticObj->Proto){
      case (long) ComponentPTValue:
	staticObj = cast(Object) ComponentItem(theObj);
	break;
      case (long) DopartObjectPTValue:
	staticObj = (cast(DopartObject)theObj)->Origin;
	break;
      case (long) StackObjectPTValue:
      case (long) ByteRepPTValue:
      case (long) WordRepPTValue:
      case (long) DoubleRepPTValue:
      case (long) ValRepPTValue:
      case (long) RefRepPTValue:
	/* This is an error */
	fprintf(output,"    -- Surrounding object damaged!\n");
	return;
	break;
      } 
    }
    if( staticObj && isObject( staticObj ) ){
      groupname = GroupName((long)staticObj->Proto,0);
      if (groupname==NULL){
	fprintf(output,"    -- Surrounding object damaged!\n");
	return;
      }
      fprintf(output,"    -- ");
      theProto = staticObj->Proto;
      fprintf(output,"%s", ProtoTypeName(theProto));
      while(theProto->Prefix &&
	    theProto->Prefix->Prefix != theProto->Prefix){
	theProto = theProto->Prefix;
	fprintf(output,"%s", ProtoTypeName(theProto));
      }
      fprintf(output, " in %s\n", groupname);
    } else {
      if (staticObj){
	fprintf(output,"    -- Surrounding object damaged!\n");
      } else {
	fprintf(output,"    -- Surrounding object is zero!\n");
      }
    }
  }
}


void DisplayObject(output,theObj,retAddress)
     ptr(FILE)   output;       /* Where to dump object */
     ref(Object) theObj;         /* Object to display */
     long        retAddress;   /* Address theObj was left from (jsr), i.e. when 
				* it was current object.
				*/
{ 
  ref(Object) theItem=0;

  if( isSpecialProtoType(theObj->Proto) ){
    switch ((long) theObj->Proto){
    case (long) ComponentPTValue:
      theItem = cast(Object) ComponentItem(theObj);
      if (theItem== cast(Object) BasicItem) {
	fprintf(output,"  basic component in %s\n", 
		GroupName((long)theItem->Proto,0) );
      } else {
	ObjectDescription(theItem, retAddress, "comp", 0);
      }
      break;
    case (long) DopartObjectPTValue:
      theItem = (cast(DopartObject)theObj)->Origin;
      ObjectDescription(theItem, retAddress, "item", 1);
      break;
    case (long) StackObjectPTValue:
      fprintf(output,"  stackobject\n");
      break;
    case (long) ByteRepPTValue:
      fprintf(output,"  ByteRep\n");
      break;
    case (long) WordRepPTValue:
      fprintf(output,"  WordRep\n");
      break;
    case (long) DoubleRepPTValue:
      fprintf(output,"  DoubleRep\n");
      break;
    case (long) ValRepPTValue:
      fprintf(output,"  ValRep\n");
      break;
    case (long) RefRepPTValue:
      fprintf(output,"  RefRep\n");
      break;
    } 
  }else{    
    ObjectDescription(theObj, retAddress, "item", 1);
  }
}

static struct errorEntry {
  long  errorNumber;
  char *errorMessage;
} errorTable[] = {
  { RefNoneErr,        "Reference is none" },
  { CompTerminatedErr, "Executing terminated component" },
  { RepRangeErr,       "Repetition index out of range" },
  { ArithExceptErr,    "Arithmetic exception" },
  { RepSubRangeErr,    "Repetition subrange out of range" },
  { RepLowRangeErr,    "Repetition subrange out of range (low)" },
  { RepHighRangeErr,   "Repetition subrange out of range (high)" },
  { StopCalledErr,     "Stop is called" },
  { LVRAfullErr,       "LVRA is full" },
  { ZeroDivErr,        "Integer division by zero" },
  { CBFAfullErr,       "Call back function area (CBFA) is full" },
  { PascalCallBackErr, "Call back Pascal function has wrong return size" },
  { CompCallBackErr,   "Suspending component involving call backs" },
  { LeaveBasicCompErr, "Attempt to leave basic component" },
  { QuaErr,            "Qualification error in reference assignment" },
  { QuaOrigErr,        "Qualification error in reference assignment; origins differ" },
  { RecursiveAttErr,   "Attach of component that is already attached" },
#ifdef RTDEBUG
  { InterruptErr,      "User Interrupt" },
#endif
  { EmulatorTrapErr,   "Emulator trap" },
  { IllegalInstErr,    "Illegal instruction" },
  { BusErr,            "Bus error" },
  { SegmentationErr,   "Segmentation fault" },
  { AOAtoIOAfullErr,   "AOAtoIOAtable is full" },
  { AOAtoLVRAfullErr,  "AOAtoLVRAtable is full" },
  { CTextPoolErr,      "Text parameter to C routine too big (max. 1000 bytes)" },
  { AOAtoIOAallocErr,  "Failed to allocate AOAtoIOAtable" },
  { UnorderedFval,     "Unordered Floating Point Value" },
  { UnknownSigErr,     "Unknown signal" },
  { 0, 0 }
  };

static char UnknownError[25];

char *ErrorMessage(errorNumber)
     long errorNumber;
{
  long  index = 0;
  
  while( errorTable[index].errorNumber != 0){
    if( errorNumber == errorTable[index].errorNumber){
      BetaErrorString = errorTable[index].errorMessage; /* For Valhalla */
      return errorTable[index].errorMessage;
    }
    index++;
  }
  sprintf(UnknownError, "Unknown error (%d)", (int)errorNumber);
  BetaErrorString = UnknownError;
  return UnknownError;
}

#ifndef sparc
#ifndef hppa
#ifndef crts

/* Support routines for motorola-like stacks */

static int NotInHeap( address)
     long address;
{
  if( inIOA(address) || inAOA(address) || inLVRA((ref(Object))address) ) 
    return FALSE;
  else return TRUE;
}

/* Traverse the StackArea [low..high] and Process all references within it. 
 * Stop when theComp is reached.
 */
static void DisplayStackPart( output, low, high, theComp)
     ptr(long) low;
     ptr(long) high;
     FILE *output;
     ref(Component) theComp;
{
  ptr(long) current = low;
  ref(Object) theObj;
  handle(Object) theCell;
  long retAddr=0;

  TRACE_DUMP(fprintf(output, ">>> StackPart [0x%x..0x%x]\n", (int)low, (int)high));
  while( current <= high ){
    retAddr=0;
    if( inBetaHeap( (ref(Object))(*current))){
      theCell = (handle(Object)) current;
      theObj  = *theCell;
      if( inIOA(theObj) || inAOA(theObj) ){
	if( isObject( theObj) && NotInHeap(*(current+1))){
	  if (theComp && cast(Object)theComp->Body==theObj){
	    retAddr=*(current+1); /* pc of theComp, when it was left */
	    break;
	  }
	}
	DisplayObject(output, theObj, (long) *(current+1));
      }
    }else{
      switch( *current){
      case -8: current++;
      case -7: current++;
      case -6: current++;
      case -5: current++;
	break;
      }
    }
    current++;
  }
  if (theComp){
    DisplayObject( output, (ref(Object)) theComp, retAddr);
    /* Make an empty line after the component */
    fprintf( output, "\n");
  }
  fflush(output);
}

#endif /* crts */
#endif /* hppa */
#endif /* sparc */

#ifdef sparc

/* SPARC support routines */
void
  DisplayAR(FILE *output, struct RegWin *theAR, long *PC)
{
  struct Object *theObj = (struct Object *) theAR->i0;
  
  if ((inIOA(theObj) || inAOA(theObj)) && isObject(theObj))
    DisplayObject(output, theObj, (long)PC);
}
#endif

static int isMakingDump=0;

/***** DisplayBetaStack: the main routine for producing the dump file *********/

/* If DisplayBetaStack returns non-zero, the debugger was invoked, and
 * the process should continue execution. */

int DisplayBetaStack( errorNumber, theObj, thePC, theSignal)
     long errorNumber;
     ref(Object) theObj;
     long *thePC;
     long theSignal; /* theSignal is zero if not applicable. */
{

#ifndef sparc
#ifndef hppa
#ifndef crts
  ref(Component)      currentComponent;
#endif
#endif
#endif
  char *dumpname;
  char dirCh;
  char *execname, *localname;
  
#ifdef RTVALHALLA
  if (valhallaID)
    switch (ValhallaOnProcessStop (thePC,StackEnd,theObj,theSignal,errorNumber)){
    case CONTINUE: return 1;
    case TERMINATE: break;
    }
#else
  theSignal = 0; 
  /* Just to avoid a compiler warning if RTVALHALLA is not defined. */ 
#endif 

  if (isMakingDump){
    /* Something went wrong during the dump. Stop here! */
#ifdef UNIX
    fprintf(stderr, "\n# Error during dump: ");
    fprintf(stderr, ErrorMessage(errorNumber));
    fprintf(stderr, ". Aborting.\n\n");
#endif
    fflush(output);
    fflush(stdout);
    exit(1);
  }
  isMakingDump=1;

#ifdef valhallaRT
  if (valhallaTest)
    if (valhallaOnError (errorNumber,theObj,thePC,stackEnd,theSignal))
      return 1;
#else
  theSignal = 0; 
  /* Just to avoid a compiler warning if valhallaRT is not defined. */ 
#endif  

 c_on_top = 0;

#if defined(macintosh) ||defined(MAC)
  dirCh = ':';
  execname = ArgVector[0]; /* Always right ??? */
#else
#ifdef nti
  dirCh = '\\';
  execname = ArgVector[0];
#else
  dirCh = '/';
  execname = ArgVector[0];
#endif
#endif
  if ( (localname=strrchr(execname, dirCh)) ) 
    localname = &localname[1];
  else
    localname = execname;
  dumpname = (char *)MALLOC(strlen(localname)+9); /* Allow for ".dump", possibly 3 digits, and NULL */
  strcpy(dumpname, localname);
#ifdef nti
  { /* If a '.' is present overwrite it and what follows */
    char *exetype = strrchr(dumpname, '.');
    char *pathsep = strrchr(dumpname, dirCh);
    /* If local name is 1 or 2 overwrite extension. Case 3 appends extension.
     * 1. D:\USERS\BETA\TEST.EXE   => D:\USERS\BETA\TEST.DUMP
     * 2. BETA.EXE                 => BETA.DUMP
     * 3. D:\USERS\BETA\V1.0\TEST  => not D:\USERS\BETA\V1.DUMP
     *                             => but D:\USERS\BETA\V1.0\TEST.DUMP
     */
    if (exetype && (!pathsep || pathsep < exetype))
      strcpy(exetype, ".dump");
    else
      strcat(dumpname, ".dump");
  }
#else
  strcat(dumpname, ".dump");
#endif
  
  if( (output = fopen(dumpname,"w")) == NULL){
    /* beta.dump cannot be opened */
#if defined(macintosh) ||defined(MAC)
    if (StandAlone){
      /* macintosh, failed to open dump file: running as standalone application */
      int i=2;
      char *lookat;
      do {
	sprintf(dumpname, "%s.dump%d", localname, i++);
      } while ((output = fopen(dumpname,"w")) == NULL);
      lookat = MALLOC(strlen(dumpname)+12);
      sprintf(lookat, "\n\nLook at '%s'", dumpname);
      CPrompt("Beta execution aborted:\n\n", ErrorMessage(errorNumber), lookat, "");
    } else {
      /* macintosh, failed to open dump file: running as tool under MPW */
      output = stderr;
      fprintf(output, "\n# Beta execution aborted: ");
      fprintf(output, ErrorMessage(errorNumber));
      fprintf(output, ".\n");
    }
#else
    /* UNIX: failed to open dump file */
    output = stderr;
    fprintf(output, "\n# Beta execution aborted: ");
    fprintf(output, ErrorMessage(errorNumber));
    fprintf(output, ".\n");
#endif
  }else{
    /* beta.dump opened successfully */
#if defined(macintosh) ||defined(MAC)
    if (StandAlone){
      /* macintosh, dump file opened OK: running as stand alone application */
      char *lookat;
      lookat = MALLOC(strlen(dumpname)+12);
      sprintf(lookat, "\n\nLook at '%s'", dumpname);
      CPrompt("Beta execution aborted:\n\n", ErrorMessage(errorNumber), lookat, "");
    } else {
      /* macintosh, dump file opened OK: running as tool under MPW */
      fprintf(stderr, "\n# Beta execution aborted: ");
      fprintf(stderr, ErrorMessage(errorNumber));
      fprintf(stderr, ".\n# Look at '%s'\n", dumpname);
    }
#else
    /* UNIX, dump file opened OK */
    fprintf(stderr, "\n# Beta execution aborted: ");
    fprintf(stderr, ErrorMessage(errorNumber));
    fprintf(stderr, ".\n# Look at '%s'\n", dumpname);
#endif
    /* Dump file opened OK: Write diagnostics to dump file too */
    fprintf(output, "Beta execution aborted: ");
    fprintf(output, ErrorMessage(errorNumber));
    fprintf(output, ".\n");
  }
  
  fprintf(output,"\nCall chain: %s\n\n", machine_name());
  
#ifndef sparc
  /* If we are able to retrieve information about the current object
   * dump it.
   */
  TRACE_DUMP(fprintf(output, ">>> Current object 0x%x\n", (int)theObj));
  if( theObj != 0 ){
    if( isObject(theObj)){
      if (theObj==cast(Object)ActiveComponent->Body){
	TRACE_DUMP(fprintf(output, "(is ActiveComponent->Body)\n"));
      } else {
	/* retAddress is 0 because we have no way of knowing
	 * current address in current object (yet)
	 */
	DisplayObject(output, theObj, (long)thePC);
      }
    }else{
      fprintf(output,"  Current object is damaged!\n");
    }
  } else {
    fprintf(output,"Current object is zero!\n");
  }
#endif
  
  if (StackStart == 0){
    fprintf(output,"\n  [initialization of basic component]\n");
    return 0;
  }
  
#if defined(UseRefStack) && !defined(SGI)
  /*
   * The ReferenceStack way of tracing the Beta stack.
   */
  {
    struct Object **theCell = /*getRefSP()*/ (struct Object **)(RefSP-1);
    struct Object *theObj;
    long   *PC=thePC;

    while((void **)theCell > &ReferenceStack[0]) {
      if ((*theCell)==(struct Object *)ExternalMarker){
	TRACE_DUMP(fprintf(output, "  cb: "));
	fprintf(output, "  [ EXTERNAL ACTIVATION PART ]\n");
      } else if (!isLazyRef(*theCell) && (unsigned)*theCell & 1) {
	/* The reference is tagged: Should appear in beta.dump */
	theObj = (struct Object *)((unsigned)*theCell & ~1);
	PC = 0; /* No way to tell the PC ?? */
	if(theObj && isObject(theObj)) {
	  /* Hack: Check if theObj is inlined in a component */
	  register struct Object *theComp;
	  theComp = (struct Object *)((long)theObj-headsize(Component));
	  if ((theObj->GCAttr == -(headsize(Component)/sizeof(long))) && 
	      (theComp->Proto==ComponentPTValue)) {
	    DisplayObject(output, theComp, (long)PC);
	    /* Make an empty line after the component */
	    fprintf(output, "\n");
	    if (theObj==(struct Object *)BasicItem) break;
	  } else {
	    DisplayObject(output, theObj, (long)PC);
	  }
	} else {
	  if (theObj) fprintf(output, "  [Damaged object!: %x]\n", (int)theObj);
	}
      }
      theCell--;
    }
    
    fflush(output);
  }
#endif
  
#ifdef sparc
  /*
   * This is the SPARC specifics of DisplayBetaStack
   */
  {
    struct RegWin *theAR;
    struct RegWin *nextCBF = (struct RegWin *) ActiveCallBackFrame;
    struct RegWin *nextCompBlock = (struct RegWin *) lastCompBlock;
    long   *PC=thePC;
    
    /* Flush register windows to stack */
    asm("ta 3");
    
    for (theAR =  (struct RegWin *) StackEnd;
	 theAR != (struct RegWin *) 0;
	 PC = (long*)theAR->i7, theAR =  (struct RegWin *) theAR->fp) {
      if (theAR == nextCompBlock) {
	/* This is the AR of attach. Continue, but get
	 * new values for nextCompBlock and nextCBF. 
	 * Please read StackLayout.doc
	 */
	
	nextCBF = (struct RegWin *) theAR->l5;
	nextCompBlock = (struct RegWin *) theAR->l6;
	
	if (nextCompBlock == 0)
	  { /* We reached the bottom */
	    DisplayObject(output, (struct Object *)theAR->i1, 0); /* AttBC */
	    fprintf(output, "\n"); fflush(output);
	    break;
	  }
	
	DisplayObject(output, (struct Object *) theAR->i0, 0); /* Att */
	/* Make an empty line after the component */
	fprintf(output, "\n"); fflush(output);
	
	continue;
      }
      else if (theAR == nextCBF) {
	/* This is AR of HandleCB. Don't display objects in this, but
	 * skip to betaTop and update nextCBF */
	struct RegWin *cAR;

	TRACE_DUMP(fprintf(output, "  cb: "));
	fprintf( output,"  [ EXTERNAL ACTIVATION PART ]\n");
	
	/* Wind down the stack until betaTop is reached.
	 * This is only done to update PC.
	 */
	for (cAR = theAR;
	     cAR != (struct RegWin *) theAR->l6;
	     PC = (long *)cAR->i7, cAR = (struct RegWin *) cAR->fp);
	nextCBF = (struct RegWin *) theAR->l5;
	theAR = (struct RegWin *) theAR->l6;
      }
      if (theAR->fp != (long) nextCompBlock)
	DisplayAR(output, theAR, PC);
    }
  }
#endif

#ifndef hppa
#ifndef sparc
#ifndef crts  
  { /* RUN based DisplayBetaStack() - i.e. MOTOROLA like stack */
    long                *lowAddr;
    long                *highAddr;
    
    ref(CallBackFrame)  cbFrame;
    
    ref(ComponentBlock) currentBlock;
    ref(Object)         currentObject;
    long                retAddr=0;
    
    /*
     * First handle the topmost component block, designated by 
     * StackEnd, ActiveCallbackFrame and lastCompBlock.
     */
    currentComponent = ActiveComponent;
    lowAddr  = StackEnd;
    highAddr = (long *) lastCompBlock;
    cbFrame  = ActiveCallBackFrame; 

    /* Follow the stack */
    while (cbFrame) {
	DisplayStackPart(output, lowAddr, (long *)cbFrame-2, 0);
	/* -2 because 2 longs are not shown:
	 *    1. The last of the three pushed words in the callback frame
	 *    2. The address of the call back stub.
	 */
      TRACE_DUMP(fprintf(output, "  cb: "));
      fprintf( output,"  [ EXTERNAL ACTIVATION PART ]\n"); 
      lowAddr = cbFrame->betaTop;
#ifdef intel
      lowAddr += 4;
      /* lowAddr+4 because the compiler saves 4 intel registers
       * before setting BetaStackTop.
       */
#endif
      cbFrame = cbFrame->next;
      if( isObject( (ref(Object))(*lowAddr)) ) {
	  TRACE_DUMP(fprintf(output, ">>> lowAddr: 0x%x\n", (int)lowAddr));
	  DisplayObject( output, (void *)(*lowAddr), 0);
      }
      lowAddr += 2;
    }
    
    /* Displays the objects from the last callback was initiated
     * (if any) and onwards to the ComponentBlock.
     */
    DisplayStackPart(output, lowAddr, highAddr-3, currentComponent);  
    /* -3 because 3 longs are not shown: 
     *    1. The last of the three pushed words in the comp block
     *    2. The address of the M-part for the component.
     *    3. The current object saved by the M-part.
     */
    
    fflush( output);
    
    /*
     * Then handle the remaining component blocks designated by the linked
     * list of ComponentBlocks from lastCompBlock and onwards.
     */
    currentBlock     = lastCompBlock;
    currentObject    = currentComponent->CallerObj;
    retAddr          = currentComponent->CallerLSC;
    currentComponent = currentComponent->CallerComp;
    
    while (currentBlock->next){
      lowAddr  = (long *)((long)currentBlock+sizeof(struct ComponentBlock))+1
	  /* +1 because the compiler always pushes the component before calling
	   * attach.
	   */;
      highAddr = (ptr(long)) currentBlock->next;
      cbFrame  = currentBlock->callBackFrame;
      
      /* Display current object in ComponentBlock */
      if (cbFrame){
	  TRACE_DUMP(fprintf(output, ">>> current: 0x%x\n", (int)currentObject));
	  /* Current object will be shown along with the first CB frame */
      } else {
	  DisplayObject(output, currentObject, retAddr);
      }

      /* Display callbackframes in the component */
      while (cbFrame) {
	DisplayStackPart(output, lowAddr, (long *)cbFrame-2, 0);
	/* -2 because 2 longs are not shown:
	 *    1. The last of the three pushed words in the callback frame
	 *    2. The address of the call back stub.
	 */
	TRACE_DUMP(fprintf(output, "  cb: "));
	fprintf( output,"  [ EXTERNAL ACTIVATION PART ]\n");
	lowAddr = cbFrame->betaTop;
#ifdef intel
	lowAddr += 4;
	/* lowAddr+4 because the compiler saves 4 intel registers
	 * before setting BetaStackTop.
	 */
#endif
	cbFrame = cbFrame->next;
	if( isObject( (ref(Object))(*lowAddr)) ){
	    TRACE_DUMP(fprintf(output, ">>> lowAddr: 0x%x\n", (int)lowAddr));
	    DisplayObject( output, (void *)(*lowAddr), 0);
	}
	lowAddr += 2;
      }
      
      /* Displays the objects from the last callback was initiated
       * (if any) and onwards to the ComponentBlock.
       */
      DisplayStackPart(output, lowAddr, highAddr-3, currentComponent); 
      /* -3 because:
       *  3 longs are not shown: 
       *    1. The last of the three pushed words in the comp block
       *    2. The address of the M-part for the component.
       *    3. The current object saved by the M-part.
       */
      currentBlock = currentBlock->next;
      currentObject    = currentComponent->CallerObj;
      retAddr          = currentComponent->CallerLSC;
      currentComponent = currentComponent->CallerComp;
    }
  }
#endif
#endif
#endif
  
#undef P
#define P(text) fprintf(output, "%s\n", text);
P("Legend:")
P("The above dump shows the dynamic call stack of invoked objects. The dump starts")
P("at the object that was the current object when the error occurred and continues")
P("down towards the basic component. The descriptions have the following meaning:")
P("1. Items are shown in two lines, like this:")
P("      item <name>#pname1#pname2#pname3 in ifile")
P("        -- sname#spname1#spname2 in sfile")
P("   meaning that the item is an instance of the descriptor \"name\" which has")
P("   prefix \"pname1\" which has prefix \"pname2\", etc. This item is defined in the")
P("   file \"ifile\". The part of the prefix chain enclosed in \"<\" and \">\" indicates")
P("   where in the action sequence the error occurred. The line beginning with")
P("   \"--\" shows the textually surrounding descriptor using the same notation.")
P("2. The descriptor names used in the above description will normally have one or")
P("   more \"meta characters\" appended. The meaning of these is:")
P("      #  The descriptor belongs to a pattern, e.g. P: (# ... #)")
P("      ~  Singular named descriptor, e.g. X: @(# ... #)")
P("      *  Singular unnamed descriptor, e.g. ... ; (# ... #) ; ...")
P("      -  Descriptor SLOT.")
P("3. Components are shown using a notation similar to that of items, like this:")
P("      comp <name>#pname1#pname2#pname3 in cfile")
P("4. The bottommost component corresponding to the basic environment is shown")
P("   like an ordinary component, but indicated with \"basic component\".")
P("5. In case the error occurred in some external code called from BETA, the top")
P("   of the call stack is shown like")
P("      [ EXTERNAL ACTIVATION PART ]")
P("6. In case the BETA code has called some external code which has in turn called")
P("   back into the BETA code, and the callback is still active at the point of")
P("   the error, the intermediate call stack part is also shown like")
P("      [ EXTERNAL ACTIVATION PART ]")  
#undef P
  
  fclose(output);

#if defined(macintosh) ||defined(MAC)
  /* Set file type and creator to make xxx.dump an MPW file */
  {  FInfo fn;
     Str255 fname;
     sprintf(fname, "%c%s", strlen(dumpname), dumpname);
     if (GetFInfo(fname, 0, &fn) != noErr) return 0;
     fn.fdType = 'TEXT';
     fn.fdCreator = 'MPS ';
     if (SetFInfo(fname, 0, &fn) != noErr) return 0;
   }
#endif

  return 0;
}



#ifdef RTDEBUG

void DescribeObject(theObject)
     struct Object *theObject;
{
  ref(ProtoType) theProto = theObject->Proto;
  if (isSpecialProtoType(theProto)){
    switch ((long) theProto){
    case (long) ComponentPTValue:
      fprintf(output, "Component: ");
      DescribeObject((struct Object *)(cast(Component)theObject)->Body);
      return;
    case (long) StackObjectPTValue:
      fprintf(output, "StackObj");
      return;
    case (long) StructurePTValue:
      fprintf(output, 
	      "Struc: origin: 0x%x, proto: 0x%x", 
	      (int)((cast(Structure)theObject)->iOrigin),
	      (int)((cast(Structure)theObject)->iProto));
      return;
    case (long) DopartObjectPTValue:
      fprintf(output, 
	      "Dopart: origin: 0x%x", 
	      (int)((cast(DopartObject)theObject)->Origin));
      return;
    case (long) RefRepPTValue:
      fprintf(output, "RefRep");	
    case (long) ValRepPTValue:
      fprintf(output, "IntegerRep");
    case (long) ByteRepPTValue:
      fprintf(output, "CharRep: '");
      if ( (((cast(ValRep)theObject)->HighBorder)-((cast(ValRep)theObject)->LowBorder)+1) > 10 ){
	fprintf(output, "%s", (char *)(cast(ValRep)theObject)->Body);
	fprintf(output, "...'");
      } else {
	fprintf(output, "%s", (char *)(cast(ValRep)theObject)->Body);
	fprintf(output, "'");
      }
      return;
    case (long) WordRepPTValue:
      fprintf(output, "ShortRep");
      return;
    case (long) DoubleRepPTValue:
      fprintf(output, "RealRep");
      return;
    default:
      fprintf(output, "Unknown object type!");
      return;
    }
  } else {
    ref(GCEntry) stat = cast(GCEntry) ((long) theProto + theProto->GCTabOff);
    ptr(short) dyn;
    
    while (*(short *) stat) stat++;	/* Step over static gc entries */ 
    dyn = ((short *) stat) + 1;		/* Step over the zero */
    while (*dyn++);			/* Step over dynamic gc entries */
    
    fprintf(output, "%s", (char *)dyn);
  }
}

#endif
