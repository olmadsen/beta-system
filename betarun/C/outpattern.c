/*
 * BETA RUNTIME SYSTEM, Copyright (C) 1990-93 Mjolner Informatics Aps.
 * outpattern.c
 * by Lars Bak, Peter Andersen, Peter Orbaek and Tommy Thorn
 */

#include "beta.h"

#define MAXINT 2147483647

static long M_Part(ref(ProtoType) proto)
     /* Return the address og of the M-entry for the prototype proto.
      * Use the fact, that if the corresponding object has a do part, 
      * then above the prototype, the INNER table can be used to find
      * the M-entry:
      *
      *        long: Return
      *        long: M-entry
      *        long: M-entry of prefix
      *        long: M-entry of prefix-prefix
      *        ...
      * proto: ...
      *
      * Should ONLY be called for a prototype which is known to correspond to 
      * object with do-part.
      * NOTICE. The Return entry point has no underscore (_) prepended to its
      * name on any platform.
      */
{
#ifdef macintosh
#error Address of label Return not yet calculated for Macintosh. / datpete
  
  /* Maybe 
   *   extern void Return();
   * and
   *   &Return 
   * i.e. a function pointer, can be used on mac instead of asm("Return"),
   * since the mac C-compiler does not put a underscore in front of 
   * function names.
   */
  
#else /* Not macintosh */
#ifdef hppa
  extern void Return() asm("Return");
#else
  extern long *Return asm("Return");
#endif
#endif
  long *m;
  long *r;
  
  m = (long *)proto - 1;
  r = m - 1;
  while ( (*r != (long)&Return) && (r != 0) ){
    /* r != 0 just to avoid segmentation fault if something is wrong */
    m = r;
    r = m - 1;
  }
  /* fprintf(output, "*m: 0x%x\n", *m); fflush(output); */
  return *m;
}

static char *machine_name()
{
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
  return "(snake)";
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
  
  /* default */
  return ""; 
}

static ptr(char) ProtoTypeName(theProto)
     ref(ProtoType) theProto;
{
  ref(GCEntry) stat = cast(GCEntry) ((long) theProto + theProto->GCTabOff);
  ptr(short) dyn;
  
  while (*(short *) stat) stat++;	/* Step over static gc entries */ 
  dyn = ((short *) stat) + 1;		/* Step over the zero */
  while (*dyn++);			/* Step over dynamic gc entries */
  
  return (ptr(char)) dyn;
}

/* c_on_top are used by beta.dump (only) to determine if things on top
 * of the stack is outside beta-code, i.e. a program has failed in 
 * external code.
 */
static int c_on_top;

#ifdef macintosh
#error Functions NextGroup and GroupName are not yet implemented for macintosh. \
The are used by beta.dump, objinterface, and persistent store / datpete
#else
  
  typedef struct group_header
{
  struct group_header *self;
  char                *ascii;
  struct group_header *next;
  long                code_start;
  long                code_end;
} group_header;

/* NextGroup is used by objectserver/persistent store to scan through the
 * data-segments, in order to implement InitFragment.
 * It must be non-static.
 */
struct group_header* NextGroup (struct group_header* current)
     /* Return group in executable following current. 
      * If current is NULL, first group is returned. */
{ 
  extern long *data1 asm("BETA_data1");
  extern long *BETA_end; /* C-variable */
  long *limit;

  DEBUG_CODE(fprintf (output, "NextGroup. current = 0x%x\n", current));
  
  if (current) {
    /* Get next data segment if any. Padding by linker 
     * may have moved it some longs down */
    current=current->next;

    limit = (long *) current + 10;
    if (limit > (long *) &BETA_end) limit = (long *) &BETA_end;

    for (; (long*) current < limit; ((long*)current)++) {
      if (current->self == current) {
	DEBUG_CODE(fprintf (output, "NextGroup = %s\n", current->ascii));
	return current;
      }
      DEBUG_CODE(fprintf (output, "NextGroup pad\n"));
    }
    /* No next group. */
    return 0;
  } else {
    DEBUG_CODE(fprintf (output, "NextGroup = %s\n", ((struct group_header *)&data1)->ascii));
    return (struct group_header *)&data1;
  }
}

/* GroupName is used by DisplayBetaStack (beta.dump) and objinterface.bet.
 * It must be non-static.
 */
char *GroupName(long address, int isCode)
{
  struct group_header *group;
  struct group_header *current;
  struct group_header *last;
  long dist, distance;
  
  DEBUG_CODE(fprintf (output, "GroupName\n"));

  current = last = group = NextGroup (0);  /* first (betaenv) data segment */
  if ((isCode && (address<current->code_start)) || 
      (!isCode && (address<(long)current))){  
    c_on_top++;
    return ""; 
  }
  
  distance = MAXINT;
  
  while (current){
    
    /* Check if the address is closer to the start 
     * of current segment than previous segments */
    
    if (isCode)
      dist = address - current->code_start;
    else
      dist = address - (long) current;
    if (dist >= 0 && dist < distance) {
      distance = dist;
      group = current;
    }
    
    last = current;
    current = NextGroup (current);
  }
  
  if ((isCode && (address>last->code_end)) 
      || (!isCode && (address>(long)last->next)) ){ 
    c_on_top++; 
    return ""; 
  } else {
    /* GroupName succeeded. From now on we are in the beta-stack */
    c_on_top=0;
  }
  
  DEBUG_CODE(fprintf (stderr, "GroupName returning (adr) 0x%x\n",(long) group->ascii));
  DEBUG_CODE(fprintf (stderr, "GroupName returning (string) %s\n", group->ascii));

  return group->ascii;
}

#endif /* not macintosh */

static void ObjectDescription(ref(Object) theObj, long retAddress, char *type, int print_origin)
{
  long           gDist=MAXINT, mDist=MAXINT, activeDist=0;
  ref(ProtoType) theProto=theObj->Proto;
  ref(ProtoType) activeProto=theProto;
  char *groupname;
  long mPart = M_Part(theProto);
  long gPart = (long) theProto->GenPart;
  
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
    groupname = GroupName(retAddress,1);
  } else {
    /* retAddress == 0 */
    groupname = (activeDist == gDist) ? GroupName(gPart,1) : GroupName(mPart,1);
  }
  
  theProto = theObj->Proto;
  
  if (c_on_top){
    /* c_on_top may have been set by GroupName if there is one or more C-frame(s)
     * on top of the stack
     */
    if (c_on_top == 1){
      c_on_top++;
      fprintf(output, "  [ EXTERNAL ACTIVATION PART ]\n");
    } 
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
    if( staticObj )
      if( isObject( staticObj ) ){
	fprintf(output,"    -- ");
	theProto = staticObj->Proto;
	fprintf(output,"%s", ProtoTypeName(theProto));
	while(theProto->Prefix &&
	      theProto->Prefix->Prefix != theProto->Prefix){
	  theProto = theProto->Prefix;
	  fprintf(output,"%s", ProtoTypeName(theProto));
	}
	fprintf(output, " in %s\n", GroupName((long)theObj->Proto,0) );
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
  RefNoneErr,        "Reference is none",
  CompTerminatedErr, "Executing terminated component",
  RepRangeErr,       "Repetition index out of range",
  ArithExceptErr,    "Arithmetic exception",
  RepSubRangeErr,    "Repetition subrange out of range",
  RepLowRangeErr,    "Repetition subrange out of range (low)",
  RepHighRangeErr,   "Repetition subrange out of range (high)",
  StopCalledErr,     "Stop is called",
  LVRAfullErr,       "LVRA is full",
  ZeroDivErr,        "Integer division by zero",
  CBFAfullErr,       "Call back function area (CBFA) is full",
  PascalCallBackErr, "Call back Pascal function has wrong return size",
  CompCallBackErr,   "Suspending component involving call backs",
  LeaveBasicCompErr, "Attempt to leave basic component",
  QuaErr,            "Qualification error in reference assignment",
  QuaOrigErr,        "Qualification error in reference assignment; origins differ",
  RecursiveAttErr,   "Attach of component that is already attached",
  EmulatorTrapErr,   "Emulator trap",
  IllegalInstErr,    "Illegal instruction",
  BusErr,            "Bus error",
  SegmentationErr,   "Segmentation fault",
  AOAtoIOAfullErr,   "AOAtoIOAtable is full",
  AOAtoLVRAfullErr,  "AOAtoLVRAtable is full",
  CTextPoolErr,      "Text parameter to C routine too big (max. 1000 bytes)",
  AOAtoIOAallocErr,  "Failed to allocate AOAtoIOAtable",
  UnknownSigErr,     "Unknown signal",
  0, 0
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
  sprintf(UnknownError, "Unknown error (%d)", errorNumber);
  BetaErrorString = UnknownError;
  return UnknownError;
}

#ifndef sparc

static NotInHeap( address)
     long address;
{
  if( inIOA(address) || inAOA(address) || inLVRA(address) ) return FALSE;
  else return TRUE;
}

/* Traverse the StackArea [low..high] and Process all references within it. 
 * Stop when theComp is reached.
 */
static DisplayStackPart( output, low, high, theComp)
     ptr(long) low;
     ptr(long) high;
     FILE *output;
     ref(Component) theComp;
{
  ptr(long) current = low;
  ref(Object) theObj;
  handle(Object) theCell;
  long retAddr=0;
  
  while( current <= high ){
    retAddr=0;
    if( inBetaHeap( *current)){
      theCell = (handle(Object)) current;
      theObj  = *theCell;
      if( inIOA(theObj) || inAOA(theObj) ){
	if( isObject( theObj) && NotInHeap(*(current+1)))
	  if (theComp && cast(Object)theComp->Body==theObj){
	    retAddr=*(current+1); /* pc of theComp, when it was left */
	    break;
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
}
#endif

#ifdef sparc
void
  DisplayAR(FILE *output, struct RegWin *theAR, long *PC)
{
  struct Object *theObj = (struct Object *) theAR->i0;
  
  if ((inIOA(theObj) || inAOA(theObj)) && isObject(theObj))
    DisplayObject(output, theObj, PC);
}
#endif

void DisplayBetaStack( errorNumber, theObj, thePC)
     long errorNumber;
     ref(Object) theObj;
     long *thePC;
{
  
#ifndef sparc
  ref(Component)      currentComponent;
#endif
  
  c_on_top = 0;
  
  if( (output = fopen("beta.dump","w")) == NULL){
    /* beta.dump cannot be opened */
#ifdef macintosh
    if (StandAlone){
      int i=2;
      char dumpname[20];
      char lookat[30];
      do {
	sprintf(dumpname, "beta.dump%d", i++);
      } while ((output = fopen(dumpname,"w")) == NULL);
      sprintf(lookat, "\n\nLook at '%s'", dumpname);
      CPrompt("Beta execution aborted:\n\n", ErrorMessage(errorNumber), lookat, "");
    } else {
      output = stderr;
      fprintf(output, "\n# Beta execution aborted: ");
      fprintf(output, ErrorMessage(errorNumber));
      fprintf(output, ".\n");
    }
#else
    output = stderr;
    fprintf(output, "\n# Beta execution aborted: ");
    fprintf(output, ErrorMessage(errorNumber));
    fprintf(output, ".\n");
#endif
  }else{
    /* beta.dump opened successfully */
#ifdef macintosh
    if (StandAlone){
      CPrompt("Beta execution aborted:\n\n", ErrorMessage(errorNumber), "\n\nLook at 'beta.dump'", "");
    } else {
      fprintf(stderr, "\n# Beta execution aborted: ");
      fprintf(stderr, ErrorMessage(errorNumber));
      fprintf(stderr, ", look at 'beta.dump'.\n");
    }
#else
    fprintf(stderr, "\n# Beta execution aborted: ");
    fprintf(stderr, ErrorMessage(errorNumber));
    fprintf(stderr, ", look at 'beta.dump'.\n");
#endif
    fprintf(output, "Beta execution aborted: ");
    fprintf(output, ErrorMessage(errorNumber));
    fprintf(output, ".\n");
  }
  
  fprintf(output,"\nCall chain: %s\n\n", machine_name());
  
#ifndef sparc
  /* If we are able to retrieve information about the current object
   * dump it.
   */
  if( theObj != 0 ){
    if( isObject(theObj)){
      if (theObj!=cast(Object)ActiveComponent->Body)
	/* retAddress is 0 because we have no way of knowing
	 * current address in current object (yet)
	 */
	DisplayObject(output, theObj, thePC);
    }else{
      fprintf(output,"Current object is damaged!\n");
    }
  }else
    fprintf(output,"Current object is damaged!\n");
#endif
  
  if (StackStart == 0){
    fprintf(output,"\n  [initialization of basic component]\n");
    return;
  }
  
#ifdef hppa
  /*
   * The HP-PA (Snake) specific parts of tracing the Beta stack.
   */
  {
    struct Object **theCell = getRefSP();
    struct Object *theObj;
    long   *PC=thePC;

    while((void **)theCell > &ReferenceStack[0]) {
      if((unsigned)*theCell & 1) {
	theObj = (struct Object *)((unsigned)*theCell & ~1);
	/* PC = ?????? */
	if(theObj && isObject(theObj)) {
	  DisplayObject(output, theObj, PC);
	} else {
	  fprintf(output, "[Damaged object!: %x]\n", (long)theObj);
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
  
  { 
    ptr(long)           theTop;
    ptr(long)           theBottom;
    
    ref(CallBackFrame)  theFrame;
    
    ref(ComponentBlock) currentBlock;
    ref(Object)         currentObject;
    long                retAddr=0;
    
    /*
     * First handle the topmost component block
     */
    currentComponent = ActiveComponent;
    theTop    = StackEnd;
    theBottom = (ptr(long)) lastCompBlock;
    theFrame  = ActiveCallBackFrame; 
    /* Follow the stack */
    while( theFrame){
      DisplayStackPart( output, theTop+1, (long *)theFrame-1, 0);
      fprintf( output,"  [ EXTERNAL ACTIVATION PART ]\n");
      theTop   = theFrame->betaTop;
      theFrame = theFrame->next;
      if( isObject( *theTop) ) DisplayObject( output, *theTop, 0);
      theTop += 2;
    }
    
    DisplayStackPart(output, theTop, theBottom-1 -2, currentComponent);  
    /* -2 because:
     *  There will always be at least 2 longs, not needed above the
     *  ComponentBlock: the exitAddress (TerminateComponent) and
     *  the Saved previous object when the component starts executing.
     */
    
    fflush( output);
    
    /*
     * Then handle the remaining component blocks.
     */
    currentBlock     = lastCompBlock;
    currentObject    = currentComponent->CallerObj;
    retAddr          = currentComponent->CallerLSC;
    currentComponent = currentComponent->CallerComp;
    
    while( currentBlock->next ){
      theTop    = (long *) ((long) currentBlock + sizeof(struct ComponentBlock) );
      theBottom = (ptr(long)) currentBlock->next;
      theFrame  = currentBlock->callBackFrame;
      
      DisplayObject(output, currentObject, retAddr);
      while( theFrame){
	DisplayStackPart( output, theTop+1, (long *)theFrame-1, 0);
	fprintf( output,"  [ EXTERNAL ACTIVATION PART ]\n");
	theTop   = theFrame->betaTop;
	theFrame = theFrame->next;
	if( isObject( *theTop) ) DisplayObject( output, *theTop, 0);
	theTop += 2;
      }
      
      DisplayStackPart( output, theTop +1, theBottom-1 -2, currentComponent); 
      /* theTop +1 because the component to be attached is always
       * pushed before attach is called. We don't want to show
       * it here, since we have just shown it as separate component
       * block.
       */
      
      currentBlock = currentBlock->next;
      currentObject    = currentComponent->CallerObj;
      retAddr          = currentComponent->CallerLSC;
      currentComponent = currentComponent->CallerComp;
    }
  }
#endif
#endif
  
#undef P
#define P(text) fprintf(output, "%s\n", text);
  
  P("Legend:");
  P("");
  P("The above dump shows the dynamic call stack of invoked objects. The dump starts ");
  P("at the object that were the current object when the error occurred, and continues");
  P("downwards towards the basic component.");
  P("");
  P("The description of the objects have the following meaning:");
  P("");
  P("1. Items are shown with two lines, like this:");
  P("  ");
  P("   item <name>#pname1#pname2#pname3 in ifile");
  P("     -- sname#spname1#spname2 in sfile");
  P(" ");
  P("   meaning that the item is an instance of the descriptor called \"name\" which");
  P("   has prefix \"pname1\" which has prefix \"pname2\" etc.");
  P("   This item is defined in the file \"ifile\".");
  P("   The part of the prefix chain enclosed in \"<\" and \">\" indicates where");
  P("   in the action sequence the error occurred.");
  P("   The line beginning with \"--\" shows the textually surrounding descriptor in");
  P("   the same notation.");
  P("");
  P("2. The descriptor names used in the above description will normally have one or");
  P("   more \"meta characters\" appended. The meaning of these are:");
  P("   ");
  P("   #  The descriptor belongs to a pattern, e.g. P: (# ... #)");
  P("");
  P("   ~  Singular named descriptor, e.g. X: @ (# ... #)");
  P("");
  P("   *  Singular unnamed descriptor, e.g. ; ...; (# ... #); ...");
  P("");
  P("   -  Descriptor SLOT.");
  P("");
  P("3. Components are shown like this:");
  P("");
  P("   comp <name>#pname1#pname2#pname3 in cfile");
  P("");
  P("   corresponding to the notation for items.");
  P("");
  P("4. The bottommost component corresponding to the basic environent is shown");
  P("   like an ordinary component, but indicated with \"basic component\".");
  P("");
  P("5. In case that the error occurred in some external code called from BETA,");
  P("   the top of the call stack will be shown like this:");
  P("");
  P("   [ EXTERNAL ACTIVATION PART ]");
  P("");
  P("6. In case the BETA code has called some external code, which in turn has");
  P("   called back into the BETA code, and this callback is still active when");
  P("   the error occurred, the intermediate call stack part is shown like");
  P("");
  P("   [ EXTERNAL ACTIVATION PART ]");
  P("");
  
#undef P
  
  fclose(output);
}



#ifdef RTDEBUG

char *DescribeObject(theObject)
     struct Object *theObject;
{
  ref(ProtoType) theProto = theObject->Proto;
  if (isSpecialProtoType(theProto)){
    char buffer[100];
    switch ((long) theProto){
    case (long) ComponentPTValue:
      strcpy(buffer, "Component: ");
      strncat(buffer, DescribeObject((cast(Component)theObject)->Body), 88);
      return buffer;
    case (long) StackObjectPTValue:
      return "StackObj";
    case (long) StructurePTValue:
      sprintf(buffer, 
	      "Struc: origin: 0x%x, proto: 0x%x", 
	      (cast(Structure)theObject)->iOrigin,
	      (cast(Structure)theObject)->iProto);
      return buffer;
    case (long) DopartObjectPTValue:
      sprintf(buffer, 
	      "Dopart: origin: 0x%x", 
	      (cast(DopartObject)theObject)->Origin);
      return buffer;
    case (long) RefRepPTValue:
      return "RefRep";	
    case (long) ValRepPTValue:
      return "IntegerRep";
    case (long) ByteRepPTValue:
      strcpy(buffer, "CharRep: '");
      if ( (((cast(ValRep)theObject)->HighBorder)-((cast(ValRep)theObject)->LowBorder)+1) > 10 ){
	strncat(buffer, (char *)(cast(ValRep)theObject)->Body, 10);
	strcat(buffer, "...'");
      } else {
	strcat(buffer, (char *)(cast(ValRep)theObject)->Body);
	strcat(buffer, "'");
      }
      return buffer;
    case (long) WordRepPTValue:
      return "ShortRep";
    case (long) DoubleRepPTValue:
      return "RealRep";
    }
  } else {
    ref(GCEntry) stat = cast(GCEntry) ((long) theProto + theProto->GCTabOff);
    ptr(short) dyn;
    
    while (*(short *) stat) stat++;	/* Step over static gc entries */ 
    dyn = ((short *) stat) + 1;		/* Step over the zero */
    while (*dyn++);			/* Step over dynamic gc entries */
    
    return (ptr(char)) dyn;
  }
}

#endif
