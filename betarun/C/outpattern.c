/*
 * BETA RUNTIME SYSTEM, Copyright (C) 1990-94 Mjolner Informatics Aps.
 * outpattern.c
 * by Lars Bak, Peter Andersen, Peter Orbaek, Tommy Thorn, and Jacob Seligmann
 */

#include "beta.h"

#ifdef RTVALHALLA
#include "valhallaComm.h"
#endif /* RTVALHALLA */

static char NotifyMessage[500] = { 0 /* rest is uninitialized */};

GLOBAL(static int basic_dumped)=0;
GLOBAL(static int isMakingDump)=0;

long M_Part(ProtoType * proto)
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
#ifdef nti_gnu
#define MACHINE_TYPE "nti_gnu"
#endif
  
#ifndef MACHINE_TYPE
#error MACHINE_TYPE should be defined
#endif

return MACHINE_TYPE;

#undef MACHINE_TYPE

}

/************************* ProtoTypeName **********************/

char *ProtoTypeName(ProtoType *theProto)
{
  GCEntry * stat;
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
  
  stat = (GCEntry *) ((long) theProto + theProto->GCTabOff);
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

  return (char *) dyn;
}

/* c_on_top is used by beta.dump (only) to determine if things on top
 * of the stack are outside beta-code, i.e. a program has failed in 
 * external code.
 * Error-pc is used to remember original PC when the error happened.
 */
GLOBAL(static signed   long c_on_top=0);
GLOBAL(static unsigned long error_pc);

/*************************** ObjectDescription: **********************/

static void ObjectDescription(Object *obj, 
			      long PC, 
			      char *type, 
			      int print_origin)
{
  signed long  gDist=MAXINT, mDist, activeDist=0;
  ProtoType   *proto=obj->Proto;
  ProtoType   *activeProto=proto;
  char        *groupname;
  long         mPart = M_Part(proto);
  long         gPart = G_Part(proto);

  if (isMakingDump && (obj==(Object *)BasicItem)){
    /* BasicItem will be shown as component */
    TRACE_DUMP(fprintf(output, "(BasicItem ignored - will be shown as comp)\n"));
    return;
  }

  TRACE_CODEENTRY(fprintf(output, "ObjectDescription: initial: proto=0x%x (%s), addr=0x%x\n", (int)proto, ProtoTypeName(proto), (int)PC)); 

  if (PC) {
    /* Find the active prefix level based on the PC.
     * Here we use both the G-entry and the M-entry. 
     * The prefix we are in is the one, where the distance from the 
     * G-entry or M-entry of the corresponding prefix-level
     * to PC is smallest (and positive).
     */
    
    gDist  = PC - gPart; 
    TRACE_CODEENTRY(fprintf(output, "initial gPart: 0x%x, gDist: 0x%x\n", (int)gPart, (int)gDist));
    mDist  = PC - mPart;
    TRACE_CODEENTRY(fprintf(output, "initial mPart: 0x%x, mDist: 0x%x\n", (int)mPart, (int)mDist));
    if (gDist < 0) gDist = MAXINT;
    if (mDist < 0) mDist = MAXINT;
    activeDist = (gDist<mDist) ? gDist : mDist;
    
    while(proto && (proto->Prefix != proto)/* stop at Object# */){
      proto = proto->Prefix;
      mPart = M_Part(proto);
      gPart = G_Part(proto);
      TRACE_CODEENTRY(fprintf(output, "ObjectDescription: proto=0x%x (%s), mPart=0x%x, gPart=0x%x\n", (int)proto, ProtoTypeName(proto), (int)mPart, (int)gPart)); 
      if((PC - gPart > 0) &&
	 (PC - gPart <= activeDist)){ 
	/* Use <= to get the LAST level, that has the entry point */ 
	activeProto = proto;
	activeDist  = gDist = PC - gPart; 
	TRACE_CODEENTRY(fprintf(output, "gDist: 0x%x\n", (int)gDist));
      }
      if((PC - mPart > 0) &&
	 (PC - mPart <= (long) activeDist)){ 
	/* Use <= to get the LAST level, that has the entry point */ 
	activeProto = proto;
	activeDist  = mDist = PC - mPart; 
	TRACE_CODEENTRY(fprintf(output, "mDist: 0x%x\n", (int)mDist));
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
    groupname = GroupName(PC,1);
#endif
  } else {
#ifdef MAC
    /* PC not known. can't determine if an address is in a given
     * object file on MAC, so we use the prototype instead. 
     */
    TRACE_GROUP(fprintf(output, "Calling GroupName with default activeProto\n"));
    groupname = GroupName((long)activeProto,0);
#else
   /* PC not known. Use the groupname of obj's mPart */
    TRACE_GROUP(fprintf(output, "Calling GroupName with default mPart\n"));
    groupname = GroupName(mPart,1);
#endif
  }

  proto = obj->Proto;

  if (c_on_top>0){
    /* c_on_top identifies that there is one or more C-frame(s)*/
    if (c_on_top == 1){
      c_on_top++; /* Print only the first time */
      TRACE_DUMP(fprintf(output, "  top: "));
      fprintf(output, 
	      "  [ EXTERNAL ACTIVATION PART (address 0x%x",
	      (int)error_pc
	      );
      DEBUG_CODE(PrintCodeAddress((long)error_pc));
      fprintf(output, ") ]\n");
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
    TRACE_DUMP(fprintf(output, ">>>TraceDump: GroupName failed for object 0x%x, addr 0x%x\n", (int)obj, (int)PC));
    return;
  }  

  DEBUG_CODE({
    fprintf(output, "  [PC  0x%x", (int)PC);
    PrintCodeAddress(PC);
    fprintf(output, ", object 0x%x, proto 0x%x ", (int)obj, (int)proto);
    PrintProto(proto);
    fprintf(output, "]\n");
  });

  if (activeDist == gDist)
    fprintf(output,"  allocating %s ", type);
  else
    fprintf(output,"  %s ", type);
  
  if(proto==activeProto || /* active prefix */
     (!activeProto && 
      proto->Prefix &&
      proto->Prefix->Prefix==proto->Prefix)) /* no prefix */
    fprintf(output,"<%s>", ProtoTypeName(proto));
  else
    fprintf(output,"%s", ProtoTypeName(proto));
  
  /* Print chain of prefixes */
  while(proto->Prefix &&
	proto->Prefix->Prefix != proto->Prefix){
    proto = proto->Prefix;
    if( proto == activeProto )
      fprintf(output,"<%s>", ProtoTypeName(proto));
    else
      fprintf(output,"%s", ProtoTypeName(proto));
  }
  fprintf(output," in %s\n", groupname);
  if (print_origin){
    long addr;
    Object *    staticObj;
    
    /** Print Static Environment Object. **/

    proto = obj->Proto;
    if (!activeProto) activeProto = proto;
    if (!activeProto) return;
    addr=(long)obj + (4*(long)activeProto->OriginOff);
    if (addr) 
      staticObj = *(Object **)addr;
    else
      staticObj = 0;
    TRACE_DUMP(fprintf(output, ">>>TraceDump: staticObj=0x%x\n", (int)staticObj));
    if( isSpecialProtoType(staticObj->Proto) ){
      switch (SwitchProto(staticObj->Proto)){
      case SwitchProto(ComponentPTValue):
	staticObj = (Object *) ComponentItem(obj);
	break;
      case SwitchProto(DopartObjectPTValue):
	staticObj = ((DopartObject *)staticObj)->Origin;
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
		"    -- Illegal surrounding object (0x%x) %s!\n",
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
      proto = staticObj->Proto;

      DEBUG_CODE({
	fprintf(output, "    [surrounding object 0x%x, proto 0x%x ", 
		(int)staticObj, 
		(int)proto);
	PrintProto(proto);
	fprintf(output, "]\n");
      });

      fprintf(output,"    -- ");
      fprintf(output,"%s", ProtoTypeName(proto));
      while(proto->Prefix &&
	    proto->Prefix->Prefix != proto->Prefix){
	proto = proto->Prefix;
	fprintf(output,"%s", ProtoTypeName(proto));
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

GLOBAL(static Object *lastDisplayedObject)=0;

void DisplayObject(FILE   *output, /* Where to dump object */
		   Object *obj, /* Object to display */
		   long    PC      /* Address obj was left from (jsr), 
				    * i.e. when it was current object.
				    */
		   )
{ 
  Object * theItem;

  if (isMakingDump){
    /* Make an empty line after the last line of a component 
     * in dump file.
     */
    if (lastDisplayedObject &&
	((lastDisplayedObject->Proto)==(ComponentPTValue)) 
	&& (lastDisplayedObject != obj)){
      fprintf(output, "\n"); fflush(output);
    }
  }

  if( isSpecialProtoType(obj->Proto) ){
    switch (SwitchProto(obj->Proto)){
    case SwitchProto(ComponentPTValue):
      theItem = (Object *) ComponentItem(obj);
      if (theItem == (Object *) BasicItem) {
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
	ObjectDescription(theItem, PC, "comp", 1);
      }
      break;
    case SwitchProto(DopartObjectPTValue):
      theItem = ((DopartObject *)obj)->Origin;
      /* Check whether theItem is actually an item or is the
       * body part of a component.
       */
      if (IsComponentItem(theItem)) {
	DisplayObject(output, 
		      (Object *)EnclosingComponent(theItem),
		      PC);
	return;
      } else {
	ObjectDescription(theItem, PC, "item", 1);
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
    ObjectDescription(obj, PC, "item", 1);
  }

  if (isMakingDump) lastDisplayedObject=obj;
}


#ifdef NEWRUN

static void DumpCell(Object **theCell,Object *theObj)
{ 
  register long PC=-1;
  long *SP;

  /* theObj is dyn in a frame. This is the current object in the 
   * previous frame. 
   */

  TRACE_DUMP(fprintf(output, ">>>TraceDump: theCell=0x%x, theObj=0x%x",
		     (int)theCell, (int)theObj));
  

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
    SP = (long *)theCell+DYN_OFF; /* Frame starts DYN_OFF longs above dyn */
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
    PC = ((Component *)theObj)->CallerComp->CallerLSC;
    theObj = ((Component *)theObj)->CallerObj;
  } 
    
  /* Check if theObj is inlined in a component */
  if (IsComponentItem(theObj)) {
    TRACE_DUMP(fprintf(output, " dump as comp"));
    theObj = (Object *)EnclosingComponent(theObj);
  } 
    
  if (PC==-1){
    SP = (long *)theCell+DYN_OFF; /* Frame starts DYN_OFF longs above dyn */
    PC = *((long *)SP+PC_OFF);
  }

  TRACE_DUMP(fprintf(output, ", PC=0x%x *\n", (int)PC));
  DisplayObject(output, theObj, PC);
}

#endif /* NEWRUN */

#ifndef sparc
#ifndef hppa
#ifndef NEWRUN

/********** Support routines for motorola-like stacks *************/

#define NotInHeap(address) \
  (!(inIOA(address) || inAOA(address)))

/* Traverse the StackArea [low..high] and Process all references within it. 
 * Stop when theComp is reached.
 */
static void DisplayStackPart(FILE *output, 
			     long *low, 
			     long *high,
			     Component *theComp)
{
  long * current = low;
  Object * theObj;
  Object ** theCell;
  long retAddr=0;

  TRACE_DUMP(fprintf(output, ">>>TraceDump: StackPart [0x%x..0x%x]\n", (int)low, (int)high));
  while( current <= high ){
    retAddr=0;
    if( inBetaHeap( (Object *)(*current))){
      theCell = (Object **) current;
      theObj  = *theCell;
      if( inIOA(theObj) || inAOA(theObj) ){
	if( isObject( theObj) && NotInHeap(*(current+1))){
	  if (theComp && (Object *)theComp->Body==theObj){
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
    DisplayObject( output, (Object *) theComp, retAddr);
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
void DisplayAR(FILE *output, RegWin *theAR, long PC)
{
  Object *theObj /* used for attempts to find objects */; 
  Object *lastObj /* used for last successfully identified object */;
  long* this, *end;

  /* First handle current object in this frame */
  lastObj  = (Object *) theAR->i0;
  if (inBetaHeap(lastObj) && isObject(lastObj)){
    if (IsComponentItem(lastObj)){
      lastObj = (Object*)EnclosingComponent(lastObj);
    } 
    DisplayObject(output, lastObj, PC);
  }

  /* Then handle possible pushed PCs (%o7s) in the
   * stackpart (INNER call chains).
   * In case of INNER P, the previous current object has been
   * pushed before the code address.
   */
  this = (long *) (((long) theAR)+sizeof(RegWin));
  end = (long *) (((long) theAR->fp)-4);
  while (this<=end) {
    PC = this[0];
    if (isCode(PC)) {
      /* isCode is a real macro on sparc. So now we know that
       * a code address has been pushes in the stack part.
       * Add 8 to get the real SPARC return address.
       */
      PC+=8;
      /* See if the next on the stack is an object (in case of INNER P) */
      theObj = (Object *) this[2];
      if (inBetaHeap(theObj) && isObject(theObj)) {
	/* It was an object - it was an INNER P */
	if (IsComponentItem(theObj)){
	  lastObj = (Object*)EnclosingComponent(theObj);
	} 
	DisplayObject(output, lastObj, PC);
	this+=2; /* Skip the object */
      } else {
	/* No Object below the code. Display with the previous
	 * found object.
	 */
	DisplayObject(output, lastObj, PC);
      }
    }
    this+=2;
  }
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
     * FIXME: this means that foo.bar.exe run as "foo.bar" yields
     * a dump file named foo.dump.
     * Use function EqualNCS as in initLabels in misc.c instead.
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

int DisplayBetaStack(BetaErr errorNumber, 
		     Object *theObj, 
		     long *thePC, 
		     long theSignal /* theSignal is zero if not applicable. */
		     )
{
  FILE *old_output=0;
#ifndef sparc
#ifndef hppa
  Component *      currentComponent;
#endif
#endif

  DEBUG_CODE({
    fprintf(output, "\n");
    fprintf(output, "DisplayBetaStack(errorNumber=%d", errorNumber);
    PrintBetaError(errorNumber); fprintf(output, ",\n");
    fprintf(output, "                 theObj=0x%x ", (int)theObj);
    DescribeObject(theObj);
    fprintf(output, ",\n");
    fprintf(output, "                 thePC=0x%x", (int)thePC);
    PrintCodeAddress((int)thePC); fprintf(output, ",\n");
    fprintf(output, "                 theSignal=%d", (int)theSignal);
    PrintSignal((int)theSignal);
    fprintf(output, ")\n");
    fflush(output);
  });
#ifndef MT
  TRACE_DUMP(fprintf(output, "StackEnd=0x%x, StackStart=0x%x\n", 
		     (int)StackEnd, 
		     (int)StackStart
		     ));
#endif

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
    /*DEBUG_CODE(fprintf(output, "DisplayBetaStack: valhallaID is 0\n"));*/
  }
#else
  if (theSignal) theSignal = 0; 
  /* Just to avoid a compiler warning if RTVALHALLA is not defined. */ 
#endif /* RTVALHALLA */
#endif /* MT */

#if BETAENV_RUNTIME_HANDLER
  /* FIXME: does not work with MT */

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
      skip_dump = ((int (*)(BetaErr, Object *, long *, long *))
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

  if (thePC && !IsBetaCodeAddrOfProcess((long)thePC)){
    c_on_top = 1;
  }

  error_pc = (unsigned long)thePC;
#if defined(sparc) || defined(hppa) || defined(sgi)
  /* Correct PC in case of unalignment */
  thePC = (long *)((long)thePC & ~3);
#endif

  NotifyMessage[0]=0;

  old_output = output;
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
  TRACE_DUMP(fprintf(output, ">>>TraceDump: Current object 0x%x\n", (int)theObj));
  if( theObj != 0 ){
    if( isObject(theObj)){
      if (theObj==(Object *)ActiveComponent->Body){
	DisplayObject(output, (Object *)ActiveComponent, (long)thePC);
      } else {
	DisplayObject(output, theObj, (long)thePC);
      }
    } else {
      fprintf(output,
	      "  Current object (0x%x) is damaged",
	      (int)theObj
	      );
      DEBUG_CODE(PrintWhichHeap(theObj));
      fprintf(output, "\n");
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
 
/************************* Begin HPPA ****************************/
 
#if defined(UseRefStack) && !defined(SGI)
  /*
   * The ReferenceStack way of tracing the Beta stack.
   */
  {
    Object **theCell = /*getRefSP()*/ (Object **)(RefSP-1);
    Object *theObj;
    long   *PC=thePC;

    while((void **)theCell > &ReferenceStack[0]) {
      if ((*theCell)==(Object *)ExternalMarker){
	TRACE_DUMP(fprintf(output, "  cb: "));
	fprintf(output, "  [ EXTERNAL ACTIVATION PART ]\n");
      } else if (!isLazyRef(*theCell) && (unsigned)*theCell & 1) {
	/* The reference is tagged: Should appear in beta.dump */
	theObj = (Object *)((unsigned)*theCell & ~1);
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
			  (Object *)EnclosingComponent(theObj), 
			  (long)PC);
	    if (theObj==(Object *)BasicItem) break;
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
/************************* End HPPA ****************************/

/************************* Begin NEWRUN ****************************/

#ifdef NEWRUN
  /*
   * This is the NEWRUN specifics of DisplayBetaStack
   */
  { 
    ProcessStackFrames((long)StackEnd, (long)StackStart, FALSE, TRUE, DumpCell);
  }
#endif
/*************************** End NEWRUN ***************************/

/*************************** Begin SPARC ******************************/

#ifdef sparc
  /*
   * This is the SPARC specifics of DisplayBetaStack
   */
  {
    RegWin *theAR;
    RegWin *nextCBF = (RegWin *) ActiveCallBackFrame;
    RegWin *nextCompBlock = (RegWin *) lastCompBlock;
    long   *PC=thePC;
    
    /* Flush register windows to stack */
    __asm__("ta 3");
    
    for (theAR =  (RegWin *) StackEnd;
	 theAR != (RegWin *) 0;
	 PC = (long*)theAR->i7, theAR =  (RegWin *) theAR->fp) {
      /* PC is execution point in THIS frame. The update of PC
       * in the for-loop is not done until it is restarted.
       */
      if (theAR->fp == (long)nextCBF) {
	/* This is AR of the code stub (e.g. <foo>) called from HandleCB. 
	 * Don't display objects in this, but skip to betaTop and update 
	 * nextCBF 
	 */
	RegWin *cAR;

	TRACE_DUMP(fprintf(output, "  cb: "));
	fprintf( output,"  [ EXTERNAL ACTIVATION PART ]\n");
	/* Wind down the stack until betaTop is reached.
	 * This is only done to update PC in order to get the PC
	 * for the first frame before the callback.
	 */
	TRACE_DUMP(fprintf(output, 
			   "  Winding back to 0x%x", 
			   (int)((RegWin *)theAR->fp)->l6
			   ));
	for (cAR = theAR;
	     cAR != (RegWin *)((RegWin *)theAR->fp)->l6;
	     PC = (long *)cAR->i7, cAR = (RegWin *) cAR->fp){
	  DEBUG_CODE({
	    fprintf(output, "    [");
	    PrintCodeAddress((int)PC);
	    fprintf(output, " ]\n");
	  });
	};
	nextCBF = (RegWin*) ((RegWin*)(theAR->fp))->l5;
	theAR   = (RegWin*) ((RegWin*)(theAR->fp))->l6;
	TRACE_DUMP(fprintf(output, "  Winding done."));
      }
      if (theAR == nextCompBlock) {
	/* This is the AR of attach. Continue, but get
	 * new values for nextCompBlock and nextCBF. 
	 * Please read StackLayout.doc
	 */
	nextCBF = (RegWin *) theAR->l5;
	nextCompBlock = (RegWin *) theAR->l6;
	
	if (nextCompBlock == 0){ 
	  /* We reached the bottom */
	  TRACE_DUMP({
	    fprintf(output, 
		    ">>>TraceDump: reached frame of AttBC at SP=0x%x\n", 
		    (int)theAR);
	  });
	  break;
	}
	
	TRACE_DUMP({
	  fprintf(output, 
		  ">>>TraceDump: reached frame of Att at SP=0x%x\n", 
		  (int)theAR);
	});
	continue;
      } 
      /* Normal frame */
      DisplayAR(output, theAR, (long)PC);
    }
  }
#endif
/*************************** End SPARC ***************************/

/****************************** Begin INTEL ********************************/

#ifdef RUN
  { /* RUN based DisplayBetaStack() - i.e. MOTOROLA like stack */
    long                *lowAddr;
    long                *highAddr;
    
    CallBackFrame *  cbFrame;
    
    ComponentBlock * currentBlock;
    Object *         currentObject;
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
      if( isObject( (Object *)(*lowAddr)) ) {
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
      lowAddr  = (long *)((long)currentBlock+sizeof(ComponentBlock))+1
	  /* +1 because the compiler always pushes the component before calling
	   * attach.
	   */;
      highAddr = (long *) currentBlock->next;
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
	if( isObject( (Object *)(*lowAddr)) ){
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
/***************************** End INTEL **********************************/


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
P("   of the call stack is shown as")
P("      [ EXTERNAL ACTIVATION PART ]")
P("6. In case the BETA code has called some external code which has in turn called")
P("   back into the BETA code, and the callback is still active at the point of")
P("   the error, the intermediate call stack part is also shown as")
P("      [ EXTERNAL ACTIVATION PART ]")  
#undef P
 
  fflush(output);
  if (old_output) output = old_output; 

#if defined(MAC)
  MakeMPWFile(dumpname);
#endif /* MAC */

  if (NotifyMessage[0]) Notify(NotifyMessage);

  return 0;
} /* DisplayBetaStack */



#ifdef RTDEBUG

void DescribeObject(Object *theObj)
{
  ProtoType * theProto;

  if (!theObj){
    fprintf(output, "[NONE]");
    return;
  }
  theProto = theObj->Proto;
  if (isSpecialProtoType(theProto)){
    switch (SwitchProto(theProto)){
    case SwitchProto(ComponentPTValue):
      fprintf(output, "Component: ");
      DescribeObject((Object *)((Component *)theObj)->Body);
      PrintWhichHeap(theObj);
      return;
    case SwitchProto(StackObjectPTValue):
      fprintf(output, "StackObj");
      PrintWhichHeap(theObj);
      return;
    case SwitchProto(StructurePTValue):
      fprintf(output, 
	      "Struc: origin: 0x%x \"%s\", proto: 0x%x \"%s\"", 
	      (int)(((Structure *)theObj)->iOrigin),
	      ProtoTypeName((((Structure *)theObj)->iOrigin)->Proto),
	      (int)(((Structure *)theObj)->iProto),
	      ProtoTypeName(((Structure *)theObj)->iProto)
	      );
      PrintWhichHeap(theObj);
      return;
    case SwitchProto(DopartObjectPTValue):
      fprintf(output, 
	      "Dopart: origin: 0x%x, proto: 0x%x (%s)", 
	      (int)(((DopartObject *)theObj)->Origin),
	      (int)(((DopartObject *)theObj)->Origin)->Proto,
	      ProtoTypeName((((DopartObject *)theObj)->Origin)->Proto)
	      );
      PrintWhichHeap(theObj);
      return;
    case SwitchProto(DynItemRepPTValue):
    case SwitchProto(DynCompRepPTValue):
      fprintf(output, "ObjectRep"); 
      PrintWhichHeap(theObj);
      return;
    case SwitchProto(RefRepPTValue):
      fprintf(output, "RefRep"); 
      PrintWhichHeap(theObj);
      return;
    case SwitchProto(LongRepPTValue):
      fprintf(output, "IntegerRep"); 
      PrintWhichHeap(theObj);
      return;
    case SwitchProto(ByteRepPTValue):
      fprintf(output, "CharRep: '");
      if ( ((((ValRep *)theObj)->HighBorder)-(((ValRep *)theObj)->LowBorder)+1) > 10 ){
	fprintf(output, "%s", (char *)((ValRep *)theObj)->Body);
	fprintf(output, "...'");
      } else {
	fprintf(output, "%s", (char *)((ValRep *)theObj)->Body);
	fprintf(output, "'");
      }
      PrintWhichHeap(theObj);
      return;
    case SwitchProto(ShortRepPTValue):
      fprintf(output, "ShortRep");
      PrintWhichHeap(theObj);
      return;
    case SwitchProto(DoubleRepPTValue):
      fprintf(output, "RealRep");
      PrintWhichHeap(theObj);
      return;
    default:
      fprintf(output, "Unknown special prototype!");
      return;
    }
  } else {
    /* ordinary object */
    fprintf(output, "\"%s\" <%s>", 
	    ProtoTypeName(theProto), getLabel((long)theProto));
    PrintWhichHeap(theObj);
  }
}

#endif /* RT_DEBUG */
