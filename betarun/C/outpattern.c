/*
 * BETA RUNTIME SYSTEM, Copyright (C) 1990-94 Mjolner Informatics Aps.
 * outpattern.c
 * by Lars Bak, Peter Andersen, Peter Orbaek, Tommy Thorn, and Jacob Seligmann
 */

#include "beta.h"

#if defined(MAC)
#include <String.h>
#include <Files.h>
#endif

#if 0
#define TRACE_GROUP(code) code; fflush(output) /* Trace GroupName() */
#else
#define TRACE_GROUP(code)
#endif
#if 0
/* Trace DisplayBetaStack() */
#define TRACE_DUMP(code) code; fflush(output)
#else
#define TRACE_DUMP(code)
#endif
#if 0
/* Trace search for prefix in ObjectDescription */
#define TRACE_CODEENTRY(code) code; fflush(output)
#else
#define TRACE_CODEENTRY(code)
#endif

#ifdef RTVALHALLA
#include "valhallaComm.h"
#endif /* RTVALHALLA */

static char NotifyMessage[500] = { 0 /* rest is uninitialized */};

GLOBAL(static int basic_dumped)=0;
GLOBAL(static int isMakingDump)=0;

long M_Part(ref(ProtoType) proto)
     /* Return the address og of the M-entry for the prototype proto.
      *
      * If the pattern has NO do-part and NO explicit prefix,
      * the routine returns MAXINT.
      * 
      * If the pattern has NO do-part but has a prefix, the routine will 
      * return the entry part of the last prefix.
      */
{
  if (!proto) return MAXINT;
  while ((!proto->MpartOff) && (proto!=proto->Prefix)){
    proto=proto->Prefix;
  }
  
  if (proto->MpartOff){
#ifdef macppc
    return **(long **)((long)proto+proto->MpartOff);
#else
    return *(long *)((long)proto+proto->MpartOff);
#endif
  } else {
    return MAXINT;
  }

}

char *machine_type(void)
{
#undef MACHINE_TYPE

  /* Sun variants */
#ifdef sun4s
#define MACHINE_TYPE "sun4s"
#endif
 
  /* HP variants */
#ifdef hpux9pa
#define MACHINE_TYPE "hpux9pa"
#endif
  
  /* SGI */
#ifdef sgi
#define MACHINE_TYPE "sgi"
#endif

  /* Macintosh */
#ifdef macppc
#define MACHINE_TYPE "ppcmac"
#endif

  /* Linux */
#ifdef linux
#define MACHINE_TYPE "linux"
#endif
  
  /* NTI */
#ifdef nti_bor
#define MACHINE_TYPE "nti_bor"
#endif
#ifdef nti_ms
#define MACHINE_TYPE "nti_ms"
#endif
  
#ifndef MACHINE_TYPE
#error MACHINE_TYPE should be defined
#endif

return MACHINE_TYPE;

#undef MACHINE_TYPE

}

/************************* ProtoTypeName **********************/

char *ProtoTypeName(struct ProtoType *theProto)
{
  ref(GCEntry) stat;
  short *dyn;

#ifdef RTDEBUG
  if (isSpecialProtoType(theProto)){
    /* ProtoTypeName is used for some debug output, where
     * the prototype may be a special one
     */
    switch (SwitchProto(theProto)){
    case SwitchProto(ComponentPTValue):    return "[Component]";
    case SwitchProto(StackObjectPTValue):  return "[StackObj]";
    case SwitchProto(StructurePTValue):    return "[StrucObject]";
    case SwitchProto(DopartObjectPTValue): return "[DopartObject]";
    case SwitchProto(DynItemRepPTValue):
    case SwitchProto(DynCompRepPTValue):   return "[ObjectRep]";
    case SwitchProto(RefRepPTValue):       return "[RefRep]";
    case SwitchProto(LongRepPTValue):       return "[IntegerRep]";
    case SwitchProto(ByteRepPTValue):      return "[CharRep]";
    case SwitchProto(ShortRepPTValue):      return "[ShortRep]";
    case SwitchProto(DoubleRepPTValue):    return "[RealRep]";
    }
  }
#endif /* RTDEBUG */
  
  stat = cast(GCEntry) ((long) theProto + theProto->GCTabOff);
  while (*(short *) stat) stat++;	/* Step over static gc entries */ 
  dyn = ((short *) stat) + 1;		/* Step over the zero */
  while (*dyn++)
     ;			/* Step over dynamic gc entries */

#if defined(linux) || defined(nti)
  /* Step over little endian long/short/real position information */
  { 
    int skiplists=0; /* number of entries for shortints and reals */

    if((*(char*)dyn) & 0x80) skiplists++;
    if((*(char*)dyn) & 0x40) skiplists++;
    
    /* step over 'integer' bit vector (short-aligned) */
    dyn += (theProto->Size+15)>>4; 
 
    while (skiplists--){
      while (*dyn++);                /* step over shortint/real info */
    }
  }
#endif

  return (ptr(char)) dyn;
}

/* c_on_top is used by beta.dump (only) to determine if things on top
 * of the stack are outside beta-code, i.e. a program has failed in 
 * external code.
 * Error-pc is used to remember original PC when the error happened.
 */
GLOBAL(static signed   long c_on_top=0);
GLOBAL(static unsigned long error_pc);

/*************************** ObjectDescription: **********************/

static void ObjectDescription(ref(Object) theObj, long retAddress, char *type, int print_origin)
{
  signed long    gDist=MAXINT, mDist, activeDist=0;
  ref(ProtoType) theProto=theObj->Proto;
  ref(ProtoType) activeProto=theProto;
  char *groupname;
  long mPart = M_Part(theProto);
  long gPart = G_Part(theProto);

  if (isMakingDump && (theObj==(struct Object *)BasicItem)){
    /* BasicItem will be shown as component */
    TRACE_DUMP(fprintf(output, "(BasicItem ignored - will be shown as comp)\n"));
    return;
  }

  TRACE_CODEENTRY(fprintf(output, "ObjectDescription: initial: theProto=0x%x (%s), addr=0x%x\n", theProto, ProtoTypeName(theProto), retAddress)); 

  if (retAddress) {
    /* Find the active prefix level based on the retAddress.
     * Here we use both the G-entry and the M-entry. 
     * The prefix we are in is the one, where the distance from the 
     * G-entry or M-entry of the corresponding prefix-level
     * to retAddress is smallest (and positive).
     */
    
    gDist  = retAddress - gPart; 
    TRACE_CODEENTRY(fprintf(output, "initial gPart: 0x%x, gDist: 0x%x\n", gPart, gDist));
    mDist  = retAddress - mPart;
    TRACE_CODEENTRY(fprintf(output, "initial mPart: 0x%x, mDist: 0x%x\n", mPart, mDist));
    if (gDist < 0) gDist = MAXINT;
    if (mDist < 0) mDist = MAXINT;
    activeDist = (gDist<mDist) ? gDist : mDist;
    
    while(theProto && (theProto->Prefix != theProto)/* stop at Object# */){
      theProto = theProto->Prefix;
      mPart = M_Part(theProto);
      gPart = G_Part(theProto);
      TRACE_CODEENTRY(fprintf(output, "ObjectDescription: theProto=0x%x (%s), mPart=0x%x, gPart=0x%x\n", theProto, ProtoTypeName(theProto), mPart, gPart)); 
      if((retAddress - gPart > 0) &&
	 (retAddress - gPart <= activeDist)){ 
	/* Use <= to get the LAST level, that has the entry point */ 
	activeProto = theProto;
	activeDist  = gDist = retAddress - gPart; 
	TRACE_CODEENTRY(fprintf(output, "gDist: 0x%x\n", gDist));
      }
      if((retAddress - mPart > 0) &&
	 (retAddress - mPart <= (long) activeDist)){ 
	/* Use <= to get the LAST level, that has the entry point */ 
	activeProto = theProto;
	activeDist  = mDist = retAddress - mPart; 
	TRACE_CODEENTRY(fprintf(output, "mDist: 0x%x\n", mDist));
      }
    }
    if (activeDist == MAXINT) return;
#ifdef MAC
    /* can't determine if an address is in a given
     * object file on MAC, so we use the prototype instead. 
     */
    TRACE_GROUP(fprintf(output, "Calling GroupName with activeProto\n"));
    groupname = GroupName((long)activeProto,0);
#else
    TRACE_GROUP(fprintf(output, "Calling GroupName with return address\n"));
    groupname = GroupName(retAddress,1);
#endif
  } else {
#ifdef MAC
    /* retAddress not known. can't determine if an address is in a given
     * object file on MAC, so we use the prototype instead. 
     */
    TRACE_GROUP(fprintf(output, "Calling GroupName with default activeProto\n"));
    groupname = GroupName((long)activeProto,0);
#else
   /* retAddress not known. Use the groupname of theObj's mPart */
    TRACE_GROUP(fprintf(output, "Calling GroupName with default mPart\n"));
    groupname = GroupName(mPart,1);
#endif
  }

  theProto = theObj->Proto;

  if (c_on_top>0){
    /* c_on_top identifies that there is one or more C-frame(s)*/
    if (c_on_top == 1){
      c_on_top++; /* Print only the first time */
      TRACE_DUMP(fprintf(output, "  top: "));
      fprintf(output, 
	      "  [ EXTERNAL ACTIVATION PART (address 0x%x) ]\n",
	      (int)error_pc
	      );
#ifdef sgi
      fprintf(output, "\n");
      fprintf(output, "  (Unable to find start of BETA stack - sorry)\n");
      BetaExit(1);
#endif
    } 
    return;
  }

  if (groupname==NULL){
    /* GroupName failed */
    TRACE_DUMP(fprintf(output, ">>>TraceDump: GroupName failed for object 0x%x, addr 0x%x\n", (int)theObj, (int)retAddress));
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
    ref(Object)    staticObj;
    
    /** Print Static Environment Object. **/

    theProto = theObj->Proto;
    if (!activeProto) activeProto = theProto;
    if (!activeProto) return;
    addr=(long)theObj + (4*(long)activeProto->OriginOff);
    if (addr) 
      staticObj = *(handle(Object))addr;
    else
      staticObj = 0;
    TRACE_DUMP(fprintf(output, ">>>TraceDump: staticObj=0x%x\n", staticObj));
    if( isSpecialProtoType(staticObj->Proto) ){
      switch (SwitchProto(staticObj->Proto)){
      case SwitchProto(ComponentPTValue):
	staticObj = cast(Object) ComponentItem(theObj);
	break;
      case SwitchProto(DopartObjectPTValue):
	staticObj = (cast(DopartObject)theObj)->Origin;
	break;

      case SwitchProto(DynItemRepPTValue):
      case SwitchProto(DynCompRepPTValue):
      case SwitchProto(StackObjectPTValue):
      case SwitchProto(ByteRepPTValue):
      case SwitchProto(ShortRepPTValue):
      case SwitchProto(DoubleRepPTValue):
      case SwitchProto(LongRepPTValue):
      case SwitchProto(RefRepPTValue):
	/* This is an error */
	fprintf(output,
		"    -- Surrounding object (0x%x) damaged %s!\n",
		(int)staticObj,
		ProtoTypeName(staticObj->Proto));
	return;
      } 
    }
    if( staticObj && isObject( staticObj ) ){
      groupname = GroupName((long)staticObj->Proto,0);
      if (groupname==NULL){
	fprintf(output,
		"    -- Surrounding object (0x%x) damaged!\n",
		(int)staticObj
		);
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
	fprintf(output,
		"    -- Surrounding object (0x%x) damaged!\n",
		(int)staticObj
		);
      } else {
	fprintf(output,
		"    -- Surrounding object is zero!\n"
		);
      }
    }
  }
}

/********************** DisplayObject: ********************
 * Called by DisplayBetaStack and BetaError (in case of QuaCont)
 */

GLOBAL(static struct Object *lastDisplayedObject)=0;

void DisplayObject(output,theObj,retAddress)
     ptr(FILE)   output;       /* Where to dump object */
     ref(Object) theObj;       /* Object to display */
     long        retAddress;   /* Address theObj was left from (jsr), i.e. when 
				* it was current object.
				*/
{ 
  ref(Object) theItem;

  if (isMakingDump){
    /* Make an empty line after the last line of a component 
     * in dump file.
     */
    if (lastDisplayedObject &&
	((lastDisplayedObject->Proto)==(ComponentPTValue)) 
	&& (lastDisplayedObject != theObj)){
      fprintf(output, "\n"); fflush(output);
    }
  }

  if( isSpecialProtoType(theObj->Proto) ){
    switch (SwitchProto(theObj->Proto)){
    case SwitchProto(ComponentPTValue):
      theItem = cast(Object) ComponentItem(theObj);
      if (theItem == cast(Object) BasicItem) {
	if (!basic_dumped){
	  fprintf(output,
		  "  basic component in %s\n", 
		  GroupName((long)theItem->Proto,0) );
	  if (isMakingDump) {
	    /* only dump basicitem once in dump file */
	    basic_dumped=1;
	  }
	}
      } else {
	ObjectDescription(theItem, retAddress, "comp", 1);
      }
      break;
    case SwitchProto(DopartObjectPTValue):
      theItem = (cast(DopartObject)theObj)->Origin;
      /* Check whether theItem is actually an item or is the
       * body part of a component.
       */
      if (IsComponentItem(theItem)) {
	DisplayObject(output, 
		      (struct Object *)EnclosingComponent(theItem),
		      retAddress);
	return;
      } else {
	ObjectDescription(theItem, retAddress, "item", 1);
      }
      break;
    case SwitchProto(StructurePTValue):
      fprintf(output, "  strucobject\n");
    case SwitchProto(StackObjectPTValue):
      fprintf(output,"  stackobject\n");
      break;
    case SwitchProto(ByteRepPTValue):
      fprintf(output,"  ByteRep\n");
      break;
    case SwitchProto(ShortRepPTValue):
      fprintf(output,"  ShortRep\n");
      break;
    case SwitchProto(DoubleRepPTValue):
      fprintf(output,"  DoubleRep\n");
      break;
    case SwitchProto(LongRepPTValue):
      fprintf(output,"  ValRep\n");
      break;
    case SwitchProto(DynItemRepPTValue):
    case SwitchProto(DynCompRepPTValue):
      fprintf(output, "  ObjectRep\n"); 
      break;
    case SwitchProto(RefRepPTValue):
      fprintf(output,"  RefRep\n");
      break;
    } 
  }else{    
    ObjectDescription(theObj, retAddress, "item", 1);
  }

  if (isMakingDump) lastDisplayedObject=theObj;
}

/******************** ErrorMessage ******************/

static const struct errorEntry 
{
  enum BetaErr errorNumber;
  char *       errorMessage;
} 
errorTable[] = 
{
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
  { LeaveBasicCompErr, "Illegal leave/restart" },
  { QuaErr,            "Qualification error in reference assignment" },
  { QuaOrigErr,        "Qualification error in reference assignment; origins differ" },
  { RecursiveAttErr,   "Attach of component that is already attached" },
  { IOAFullErr,        "IOA heap is full" },
  { FpZeroDivErr,      "Floating Point division by zero" },
  { FpExceptErr,       "Floating Point exception" },
#ifdef intel
  { FpStackUflowErr,   "Floating Point stack underflow" },
  { FpStackOflowErr,   "Floating Point stack overflow" },
#endif
#ifdef RTDEBUG
  { InterruptErr,      "User Interrupt" },
#endif
  { EmulatorTrapErr,   "Emulator trap" },
  { IllegalInstErr,    "Illegal instruction" },
  { BusErr,            "Bus error" },
#ifdef UNIX
  { SegmentationErr,   "Segmentation fault" },
#else
  { SegmentationErr,   "Access violation" },
#endif /* UNIX */
  { AOAtoIOAfullErr,   "AOAtoIOAtable is full" },
  { AOAtoLVRAfullErr,  "AOAtoLVRAtable is full" },
  { CTextPoolErr,      "Text parameter to C routine too big (max. 1000 bytes)" },
  { AOAtoIOAallocErr,  "Failed to allocate AOAtoIOAtable" },
  { UnorderedFval,     "Unordered Floating Point value in comparison" },
#ifdef MT
  { StackErr,          "Component Stack Overflow" },
#else
  { StackErr,          "Stack Overflow" },
#endif
#ifdef UNIX
  { UnknownSigErr,     "Unknown signal" },
#else
  { UnknownSigErr,     "Unknown exception" },
#endif
  { 0, 0 }
  };

GLOBAL(static char UnknownError[25]);

char *ErrorMessage(enum BetaErr errorNumber)
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

#ifdef NEWRUN

static void DumpCell(struct Object **theCell,struct Object *theObj)
{ 
  register long PC=-1;
  long *SP;

  /* theObj is dyn in a frame. This is the current object in the 
   * previous frame. 
   */

  TRACE_DUMP(fprintf(output, ">>>TraceDump: theCell=0x%x, theObj=0x%x",
		     theCell, theObj));
  

  /* First check if theObj is CALLBACKMARK */
  if ((theObj==CALLBACKMARK)||(theObj==GENMARK)){
    if (theObj==CALLBACKMARK){
      TRACE_DUMP(fprintf(output, "  cb: "));
      fprintf(output, "  [ EXTERNAL ACTIVATION PART ]\n");
    } else {
      TRACE_DUMP(fprintf(output, "  allo: "));
    }
    /* Since ProcessStackFrames now skips to previous frame before
     * BETA called C, we will not see the current object in the
     * frame before C as a dyn-pointer in any frame (it is hidden
     * by this CALLBACKMARK).
     * So we have to go to this previous frame ourselves and
     * find the current object for that frame and dump it.
     * See figure in stack.c.
     */
    SP = (long *)theCell+DYNOFF; /* Frame starts DYNOFF longs above dyn */
    SP = (long*)GetSPbeta(SP);	 /* SP-beta */
    if (SP==0){
      /* We passed the main+CallB frames */
      return;
    }
    theObj = GetThis(SP);
    PC = 0;			 /* not known - is somewhere in the C frames */
  }
    
  /* Check if theObj IS a component */
  if (theObj && (theObj->Proto==ComponentPTValue)){
    TRACE_DUMP(fprintf(output, " is comp - getting real dyn"));
    /* Passing a component frame. The real dyn is found 
     * as theComp->CallerObj - see stack.c for details.
     */
    PC = ((struct Component *)theObj)->CallerComp->CallerLSC;
    theObj = ((struct Component *)theObj)->CallerObj;
  } 
    
  /* Check if theObj is inlined in a component */
  if (IsComponentItem(theObj)) {
    TRACE_DUMP(fprintf(output, " dump as comp"));
    theObj = (struct Object *)EnclosingComponent(theObj);
  } 
    
  if (PC==-1){
    SP = (long *)theCell+DYNOFF; /* Frame starts DYNOFF longs above dyn */
    PC = *((long *)SP+PC_OFF);
  }

  TRACE_DUMP(fprintf(output, ", PC=0x%x *\n", PC));
  DisplayObject(output, theObj, PC);
}

#endif /* NEWRUN */

#ifndef sparc
#ifndef hppa
#ifndef NEWRUN

/********** Support routines for motorola-like stacks *************/

#define NotInHeap(address) \
  (!(inIOA(address) || inAOA(address) || inLVRA((ref(Object))address)))

/* Traverse the StackArea [low..high] and Process all references within it. 
 * Stop when theComp is reached.
 */
static void DisplayStackPart(FILE *output, 
			     long *low, 
			     long *high,
			     struct Component *theComp)
{
  ptr(long) current = low;
  ref(Object) theObj;
  handle(Object) theCell;
  long retAddr=0;

  TRACE_DUMP(fprintf(output, ">>>TraceDump: StackPart [0x%x..0x%x]\n", (int)low, (int)high));
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

#endif /* NEWRUN */
#endif /* hppa */
#endif /* sparc */

/************* support routines for SPARC ***************/

#ifdef sparc
void
  DisplayAR(FILE *output, struct RegWin *theAR, long *PC)
{
  struct Object *theObj = (struct Object *) theAR->i0;
  
  if ((inIOA(theObj) || inAOA(theObj)) && isObject(theObj))
    DisplayObject(output, theObj, (long)PC);
}
#endif /* sparc */

/********************** OpenDumpFile ********************/

#ifdef UNIX
static int OpenDumpFile(long errorNumber)
{
  char dumpname[500];
  char dirCh;
  char *execname, *localname;

  dirCh = '/';
  execname = ArgVector[0];
  if ( (localname=strrchr(execname, dirCh)) ) 
    localname = &localname[1];
  else
    localname = execname;
  strcpy(dumpname, localname);
  strcat(dumpname, ".dump");
  if( (output = fopen(dumpname,"w")) == NULL){
    /* beta.dump cannot be opened - use stderr */
    output = stderr;
    fprintf(output, "\n# Beta execution aborted: ");
    fprintf(output, ErrorMessage(errorNumber));
    fprintf(output, ".\n");
    fflush(output);
  } else {
    /* beta.dump opened successfully */
    fprintf(stderr, "\n# Beta execution aborted: ");
    fprintf(stderr, ErrorMessage(errorNumber));
    fprintf(stderr, ".\n# Look at '%s'\n", dumpname);
    fflush(stderr);
    /* Write diagnostics to dump file too */
    fprintf(output, "Beta execution aborted: ");
    fprintf(output, ErrorMessage(errorNumber));
    fprintf(output, ".\n");
    fflush(output);
  }
  return 1;
}
#endif /* UNIX */

#if defined(MAC)
GLOBAL(static char dumpname[33]); /* max filename length is 32 */
static int OpenDumpFile(long errorNumber)
{
  char dirCh;
  char *execname, *localname;
  char lookat[100];
  int locallen;

  dirCh = ':';
  execname = ArgVector[0]; /* Always right ??? */
  if ( (localname=strrchr(execname, dirCh)) ) 
    localname = &localname[1];
  else
    localname = execname;

  locallen = strlen(localname);
  if (locallen>27){
    strncpy(dumpname, localname, 27); /* allow for ".dump" */
    dumpname[27] = 0;
  } else {
    strcpy(dumpname, localname);
  }
  strcat(dumpname, ".dump");
  
  if( (output = fopen(dumpname,"w")) == NULL){
    /* beta.dump cannot be opened */
    if (StandAlone){
      /* macintosh, failed to open dump file: running as standalone appl */
      int i=2;
      char extension[10];
      do {
	/* Construct xxxxx.dumpNNN name taking max filename 
	 * length into account.
	 */
	if (i<10){
	  if (locallen>26){
	    strncpy(dumpname, localname, 26); /* allow for ".dumpN" */
	    dumpname[26] = 0;
	  } else {
	    strcpy(dumpname, localname);
	  }
	} else if (i<100) {
	  if (locallen>25){
	    strncpy(dumpname, localname, 25); /* allow for ".dumpNN" */
	    dumpname[25]=0;
	  } else {
	    strcpy(dumpname, localname);
	  }
	} else {
	  if (locallen>24){
	    strncpy(dumpname, localname, 24); /* allow for ".dumpNNN" */
	    dumpname[24]=0;
	  } else {
	    strcpy(dumpname, localname);
	  }
	}
	sprintf(extension, "dump%d", i++);
	strcat(dumpname, extension);
      } while (((output = fopen(dumpname,"w")) == NULL) && (i<1000));
      if (i==1000){
	/* Failed to open dump1, dump2, ... dump999 */
	strncpy(dumpname, localname, 27); /* allow for ".dump" */
	strcat(dumpname, ".dump");
	sprintf(lookat, "\n\nFailed to open '%s'", dumpname);
	CPrompt("Beta execution aborted:\n\n", 
		ErrorMessage(errorNumber), 
		lookat, 
		"");
	return 0;
      } else {
	sprintf(lookat, "\n\nLook at '%s'", dumpname);
	CPrompt("Beta execution aborted:\n\n", 
		ErrorMessage(errorNumber), 
		lookat, 
		"");
      }
    } else {
      /* macintosh, failed to open dump file: running as tool under MPW */
      output = stderr;
      fprintf(output, "\n# Beta execution aborted: ");
      fprintf(output, ErrorMessage(errorNumber));
      fprintf(output, ".\n");
    }
  } else {
    /* beta.dump opened successfully */
    if (StandAlone){
      /* macintosh, dump file opened OK: running as stand alone application */
      char *lookat;
      lookat = MALLOC(strlen(dumpname)+12);
      sprintf(lookat, "\n\nLook at '%s'", dumpname);
      CPrompt("Beta execution aborted:\n\n", 
	      ErrorMessage(errorNumber), 
	      lookat, 
	      "");
    } else {
      /* macintosh, dump file opened OK: running as tool under MPW */
      fprintf(stderr, "\n# Beta execution aborted: ");
      fprintf(stderr, ErrorMessage(errorNumber));
      fprintf(stderr, ".\nFile \"%s\"; Line 1\n", dumpname);
    }
    /* Dump file opened OK: Write diagnostics to dump file too */
    fprintf(output, "Beta execution aborted: ");
    fprintf(output, ErrorMessage(errorNumber));
    fprintf(output, ".\n");
  }
  return 1;
}
#endif /* mac */

#ifdef nti
static char *OpenDumpFile(long errorNumber)
{
  GLOBAL(static char dumpname[500]);
  char dirCh;
  char *execname, *localname;

  dirCh = '\\';
  execname = ArgVector[0];
  if ( (localname=strrchr(execname, dirCh)) ) 
    localname = &localname[1];
  else
    localname = execname;
  strcpy(dumpname, localname);
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
  if( (output = fopen(dumpname,"w")) == NULL){
    /* beta.dump cannot be opened */
    { sprintf(NotifyMessage,
	      "\nBeta execution aborted: %s.\nFailed to open '%s'",
              ErrorMessage(errorNumber),
	      dumpname);
      return 0;
    }
  } else {
    /* beta.dump opened successfully */
    { sprintf(NotifyMessage,
	      "\nBeta execution aborted: %s.\nLook at '%s'",
              ErrorMessage(errorNumber), dumpname);
    }
    /* Dump file opened OK: Write diagnostics to dump file too */
    fprintf(output, "Beta execution aborted: ");
    fprintf(output, ErrorMessage(errorNumber));
    fprintf(output, ".\n");
  }
  return dumpname;
}
#endif /* nti */


/**************** DisplayBetaStack: *******************/

/* If DisplayBetaStack returns non-zero, the debugger was invoked, and
 * the process should continue execution. */

int DisplayBetaStack(enum BetaErr errorNumber, 
		     struct Object *theObj, 
		     long *thePC, 
		     long theSignal /* theSignal is zero if not applicable. */
		     )
{
#ifndef sparc
#ifndef hppa
  ref(Component)      currentComponent;
#endif
#endif

  TRACE_DUMP(fprintf(stdout, 
		     "DisplayBetaStack(errorNumber=%d, theObj=0x%x, thePC=0x%x, theSignal=%d\n",
		     errorNumber, 
		     theObj, 
		     thePC, 
		     theSignal));
#ifndef MT
  TRACE_DUMP(fprintf(stdout, "StackEnd=0x%x, StackStart=0x%x\n", 
		     (long)StackEnd, 
		     (long)StackStart
		     ));
#endif
  TRACE_DUMP(fflush(stdout));

#ifndef MT
#if (defined(RTVALHALLA) && !defined(nti_bor))
  if (valhallaID){
#ifdef UseRefStack
    printf("DisplayBetaStack: calling Valhalla\n");
    switch (ValhallaOnProcessStop (thePC,RefSP,theObj,theSignal,errorNumber))
#else
    DEBUG_VALHALLA(fprintf(output, "DisplayBetaStack: calling ValhallaOnProcessStop\n"));
    switch (ValhallaOnProcessStop (thePC,StackEnd,theObj,theSignal,errorNumber))
#endif
      {
      case CONTINUE: 
	DEBUG_VALHALLA(fprintf(output, "DisplayBetaStack: continuing after ValhallaOnProcessStop\n"));
	return 1;
      case TERMINATE: 
	DEBUG_VALHALLA(fprintf(output, "DisplayBetaStack: breaking after ValhallaOnProcessStop\n"));
	break;
      }
  } else {
#ifdef RTDEBUG
    fprintf(output, "DisplayBetaStack: valhallaID is 0\n");
#endif
  }
#else
  if (theSignal) theSignal = 0; 
  /* Just to avoid a compiler warning if RTVALHALLA is not defined. */ 
#endif /* RTVALHALLA */
#endif /* MT */



#define BETAENV_RUNTIME_HANDLER 0
  /* FIXME: does not work with MT */
#if BETAENV_RUNTIME_HANDLER

  /* see TST/tstprogram.bet */
  
  if (errorNumber==StopCalledErr){
      DEBUG_CODE(fprintf(output, "RTS: ignoring handler for StopCalled\n"));
  } else {
    DEBUG_CODE(fprintf(output, "RTS: setting BetaStackTop to value before trap\n"));
    BetaStackTop = StackEnd;
    if (CBFA && CBFA->entries){
      int skip_dump;
      DEBUG_CODE(fprintf(output, 
			 "RTS: calling errorhandler (first callback)\n"));
      skip_dump = ((int (*)(enum BetaErr, struct Object *, long *, long *))
		   ((&CBFA->entries[0].theStruct)+1))(errorNumber, 
						      theObj, 
						      thePC, 
						      StackEnd);
      if (skip_dump) return 0;
    }
  }
#endif /* BETAENV_RUNTIME_HANDLER */



  if (isMakingDump){
    /* Something went wrong during the dump. Stop here! */
    fprintf(output, "\n# Error during dump: ");
    fprintf(output, ErrorMessage(errorNumber));
    fprintf(output, ". Aborting.\n\n");
    fflush(output);
    fflush(stdout);
    isMakingDump=0; /* allow other threads to make dump */
    if (NotifyMessage[0]) Notify(NotifyMessage);
    BetaExit(1);
  } else {
    isMakingDump=1;
  }

  if (thePC && !IsBetaCodeAddr((long)thePC)){
    c_on_top = 1;
  }

  error_pc = (unsigned long)thePC;
#if defined(sparc) || defined(hppa) || defined(sgi)
  /* Correct PC in case of unalignment */
  thePC = (long *)((long)thePC & ~3);
#endif

  NotifyMessage[0]=0;

  if (!OpenDumpFile(errorNumber))
    return 0;
  
  DEBUG_CODE(fprintf(output,
		     "\nIOA: 0x%x, IOATop: 0x%x, IOALimit: 0x%x\n",
		     (int)GLOBAL_IOA, 
		     (int)GLOBAL_IOATop, 
		     (int)GLOBAL_IOALimit));
  DEBUG_CODE(fprintf(output,
		     "ToSpace: 0x%x, ToSpaceTop: 0x%x, ToSpaceLimit: 0x%x\n", 
		     (int)ToSpace, 
		     (int)ToSpaceTop, 
		     (int)ToSpaceLimit));

  fprintf(output,"\nCall chain: (%s)\n\n", machine_type());
  fflush(output);
  
#ifndef sparc
  /* If we are able to retrieve information about the current object
   * dump it.
   */
  TRACE_DUMP(fprintf(output, ">>>TraceDump: Current object 0x%x\n", (int)theObj); fflush(output));
  if( theObj != 0 ){
    if( isObject(theObj)){
      if (theObj==(struct Object *)ActiveComponent->Body){
	DisplayObject(output, (struct Object *)ActiveComponent, (long)thePC);
      } else {
	DisplayObject(output, theObj, (long)thePC);
      }
    } else {
      fprintf(output,
	      "  Current object (0x%x) is damaged",
	      (int)theObj
	      );
      if (inIOA(theObj))
	fprintf(output, " (is in IOA)");
      if (inAOA(theObj)) 
	fprintf(output, " (is in AOA)");
      if (inLVRA(theObj)) 
	fprintf(output, " (is in LVRA)");
      if (ToSpace<=(long*)theObj && (long*)theObj<ToSpaceLimit)
	fprintf(output, " (is in ToSpace!)");
      fprintf(output, ".\n");
      fflush(output);
#if 1
      DEBUG_CODE({
	extern int isObjectState;
	if (inBetaHeap(theObj)){
	  fprintf(output, "    proto: 0x%x\n", (int)theObj->Proto);
	  fflush(output);
	  fprintf(output, "    gc:    0x%x\n", (int)theObj->GCAttr);
	  fflush(output);
	}
	fprintf(output, "  isObjectState: %d\n", isObjectState);
	fflush(output);
      });
#endif
      
    }
  } else {
    fprintf(output,"Current object is zero!\n");
  }
#endif
  

#ifdef MT
  fprintf(output, "DisplayBetaStack: NYI for MT\n"); fflush(output);
#endif

#ifndef MT
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
#if 0 /* not yet */
#ifdef RTVALHALLA
	theCell--;
	PC = (long *)*theCell
#endif
#endif
	if(theObj && isObject(theObj)) {
	  /* Check if theObj is inlined in a component */
	  if (IsComponentItem(theObj)) {
	    DisplayObject(output, 
			  (struct Object *)EnclosingComponent(theObj), 
			  (long)PC);
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

#ifdef NEWRUN
  /*
   * This is the NEWRUN specifics of DisplayBetaStack
   */
  { 
    ProcessStackFrames((long)StackEnd, (long)StackStart, FALSE, TRUE, DumpCell);
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
    __asm__("ta 3");
    
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

#ifdef RUN
  { /* RUN based DisplayBetaStack() - i.e. MOTOROLA like stack */
    long                *lowAddr;
    long                *highAddr;
    
    ref(CallBackFrame)  cbFrame;
    
    ref(ComponentBlock) currentBlock;
    ref(Object)         currentObject;
    long                retAddr;
    
    /*
     * First handle the topmost component block, designated by 
     * StackEnd, ActiveCallbackFrame and lastCompBlock.
     */
    currentComponent = ActiveComponent;
    lowAddr  = (long *) StackEnd;
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
	  TRACE_DUMP(fprintf(output, ">>>TraceDump: current: 0x%x\n", (int)currentObject));
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
	    TRACE_DUMP(fprintf(output, ">>>TraceDump: lowAddr: 0x%x\n", (int)lowAddr));
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
#endif /* RUN */


#endif /* MT */

#undef P
#define P(text) fprintf(output, "%s\n", text);
P("")
P("Legend:")
P("")
P("The above dump shows the dynamic call stack of invoked objects.")
P("The dump starts at the object that was the current object when")
P("the error occurred and continues down towards the basic component.")
P("The descriptions have the following meaning:")
P("1. Items are shown in two lines, like this:")
P("      item <name#>pname1#pname2#pname3 in ifile")
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
P("      comp <name#>pname1#pname2#pname3 in cfile")
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

#if defined(MAC)
  MakeMPWFile(dumpname);
#endif /* MAC */

  return 0;
} /* DisplayBetaStack */



#ifdef RTDEBUG

void DescribeObject(theObject)
     struct Object *theObject;
{
  ref(ProtoType) theProto = theObject->Proto;
  if (isSpecialProtoType(theProto)){
    switch (SwitchProto(theProto)){
    case SwitchProto(ComponentPTValue):
      fprintf(output, "Component: ");
      DescribeObject((struct Object *)(cast(Component)theObject)->Body);
      return;
    case SwitchProto(StackObjectPTValue):
      fprintf(output, "StackObj");
      return;
    case SwitchProto(StructurePTValue):
      fprintf(output, 
	      "Struc: origin: 0x%x, proto: 0x%x", 
	      (int)((cast(Structure)theObject)->iOrigin),
	      (int)((cast(Structure)theObject)->iProto));
      return;
    case SwitchProto(DopartObjectPTValue):
      fprintf(output, 
	      "Dopart: origin: 0x%x, proto: 0x%x (%s)", 
	      (int)((cast(DopartObject)theObject)->Origin),
	      (int)((cast(DopartObject)theObject)->Origin)->Proto,
	      ProtoTypeName(((cast(DopartObject)theObject)->Origin)->Proto)
	      );
      return;
    case SwitchProto(DynItemRepPTValue):
    case SwitchProto(DynCompRepPTValue):
      fprintf(output, "ObjectRep\n"); return;
    case SwitchProto(RefRepPTValue):
      fprintf(output, "RefRep"); return;
    case SwitchProto(LongRepPTValue):
      fprintf(output, "IntegerRep"); return;
    case SwitchProto(ByteRepPTValue):
      fprintf(output, "CharRep: '");
      if ( (((cast(ValRep)theObject)->HighBorder)-((cast(ValRep)theObject)->LowBorder)+1) > 10 ){
	fprintf(output, "%s", (char *)(cast(ValRep)theObject)->Body);
	fprintf(output, "...'");
      } else {
	fprintf(output, "%s", (char *)(cast(ValRep)theObject)->Body);
	fprintf(output, "'");
      }
      return;
    case SwitchProto(ShortRepPTValue):
      fprintf(output, "ShortRep");
      return;
    case SwitchProto(DoubleRepPTValue):
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
    while (*dyn++){};			/* Step over dynamic gc entries */
    
#ifdef sparc
    if (DebugStack){
#ifdef MT
      fprintf(output, "%s", (char *)dyn);
#else
      extern char *getLabel (long addr);
      fprintf(output, "%s: \"%s\"", getLabel((long)theProto), (char *)dyn);
#endif
    } else {
      fprintf(output, "%s", (char *)dyn);
    }
#else
    fprintf(output, "%s", (char *)dyn);
#endif
  }
}

#endif /* RT_DEBUG */
