/*
 * Low level support for scanning BETA objects in the
 * different kinds of heaps. Used by ~beta/sysutils/v1.4/scanobjects.bet.
 *
 * COPYRIGHT
 *       Copyright Mjolner Informatics, 1994
 *       All rights reserved.
 */

#include "beta.h"
#ifndef MT 

#define GC_PANIC_MSG "\n\n\tPANIC: object scan stopped because of GC!!\n\n"
#define MSG_DEST stdout


/**********************
 *                    *
 *   Implementation   *
 *                    *
 **********************/

#if 0
static char *
stripName(char *s)
{
  char *p;

  for (p=s; *p!='\0'; p++)
    if (*p=='/')
      s = p+1;
  return s;
}
#endif

static int
isPrefix(ref(ProtoType) fst, ref(ProtoType) snd)
{
  ref(ProtoType) tmp=snd;

  if ((long)fst > 0 && (long)snd > 0) {

    /* Real object prototypes */
    while (1) {
      if (tmp==fst)
	return 1;
      if (0==tmp->Prefix || tmp->Prefix==tmp->Prefix->Prefix)
	return 0;
      tmp=tmp->Prefix;
    }
  }
  else {

    /* At least one of {fst,snd} is special or NULL */
    return 0;
  }
}


static void
printMessage(FILE *fp,
	     ref(Object) theObj,
	     int printOrigin,
	     int printSize)
{
  ref(ProtoType) proto=theObj->Proto;
  char *name;

  if ((long)proto < 0)
    switch (SwitchProto(proto)) {
    case SwitchProto(ComponentPTValue): name = "[Component]"; break;
    case SwitchProto(StackObjectPTValue): name = "[Stack_Object]"; break;
    case SwitchProto(StructurePTValue): name = "[Struc_Object]"; break;
    case SwitchProto(DynItemRepPTValue):
    case SwitchProto(DynCompRepPTValue): name = "[Object_Repetition]"; break;
    case SwitchProto(RefRepPTValue): name = "[Reference_Repetition]"; break;
    case SwitchProto(LongRepPTValue): name = "[Integer_Repetition]"; break;
    case SwitchProto(ByteRepPTValue): name = "[Char_Repetition]"; break;
    case SwitchProto(ShortRepPTValue): name = "[Shortint_Repetition]"; break;
    case SwitchProto(DoubleRepPTValue): name = "[Real_Repetition]"; break;
    default: name = "[???]"; break;
    }
  else {
    name = ProtoTypeName(proto);
  }
  fprintf(fp, "%s", name);

  if ((long)proto >= 0) {	/* Real object */
    
    while (proto->Prefix && proto->Prefix->Prefix != proto->Prefix) {
      proto = proto->Prefix;
      fprintf(fp, "%s", ProtoTypeName(proto));
    }

    if (printOrigin) {
      fprintf(fp," ");
      printMessage(fp,
		   cast(Object)(((long*)theObj)[theObj->Proto->OriginOff]),
		   0,	/* don't print origins recursively */
		   0);	/* don't print size of origin */
    }
  }

  if (printSize) {
    fprintf(fp," %ld",4*ObjectSize(theObj));
  }
}


static void
noise_cb(ref(Object) theObj, int printOrigin, int printSize)
{
  fprintf(MSG_DEST,"{scan} ");
  printMessage(MSG_DEST,theObj,printOrigin,printSize);
  fprintf(MSG_DEST,"\n");
}


static void
scanAOAliveObjects(int printVisited, int printOrigin, int printSize,
		   int docallback,
		   ref(ProtoType) rootProto,
		   void (*cb)(ref(Object)))
{
  ref(Block) theBlock;
  ref(Object) theObj;
  long objSize;
  ref(Block) savedLastBlock;
  ptr(long) savedLastTop;
  ptr(long) currentTop;
  long SavedNumAOAGc = NumAOAGc;

  /* If no AOA yet, stop */
  if (!AOABaseBlock)
    return;

  /* Ignore objects created during this scan: find limit */
  savedLastBlock = AOABaseBlock;
  while (savedLastBlock->next)
    savedLastBlock=savedLastBlock->next;
  savedLastTop=savedLastBlock->top;

  theBlock = AOABaseBlock;
  while (theBlock) {

    if (theBlock==savedLastBlock) {
      currentTop=savedLastTop;
    }
    else {
      currentTop=theBlock->top;
    }

    theObj = (ref(Object)) BlockStart(theBlock);
    while ((ptr(long)) theObj < currentTop) {

      /* Check for AOA-GC */
      if (SavedNumAOAGc != NumAOAGc) {
	fprintf(MSG_DEST,GC_PANIC_MSG);
	return;
      }

      /* Expose the object */
      if (((long) theObj->Proto) >= 0) {

	/* Real object: filter by root */
	if ((0==rootProto) || isPrefix(rootProto,theObj->Proto)) {
	  if (printVisited)
	    noise_cb(theObj,printOrigin,printSize);
	  if (docallback)
	    (*cb)(theObj);
	}
      }
      else {

	/* Non-object: suppressed if there is a root */
	if (printVisited && (0==rootProto))
	  noise_cb(theObj,printOrigin,printSize);
      }

      /* Go to next object */
      objSize = 4*ObjectSize(theObj);
      theObj = (ref(Object)) ((long) theObj + objSize);
    }

    if (theBlock==savedLastBlock) {
      break;
    }
    else {
      theBlock = theBlock->next;
    }
  }
}


static void
scanIOAliveObjects(int printVisited,
		   int printOrigin,
		   int printSize,
		   int docallback,
		   ref(ProtoType) rootProto,
		   void (*cb)(ref(Object)))
{
  ref(Object) theObj = (ref(Object))IOA;
  long objSize;
  long SavedNumIOAGc = NumIOAGc;

  /* If 'cb' creates new objects, ignore them */
  long *SavedIOATop = IOATop;

  while ((long*)theObj < SavedIOATop) {

    /* Check for IOA-GC */
    if (SavedNumIOAGc != NumIOAGc) {
      fprintf(MSG_DEST,GC_PANIC_MSG);
      return;
    }

    /* Expose the object */
    if (((long) theObj->Proto) >= 0) {

      /* Real object: filter by root */
      if ((0==rootProto) || isPrefix(rootProto,theObj->Proto)) {
	if (printVisited)
	  noise_cb(theObj,printOrigin,printSize);
	if (docallback)
	  (*cb)(theObj);
      }
    }
    else {

      /* Non-object: suppressed if there is a root */
      if (printVisited && (0==rootProto))
	noise_cb(theObj,printOrigin,printSize);
    }

    /* Go to next object */
    objSize = 4*ObjectSize(theObj);
    theObj = (ref(Object)) ((long)theObj + objSize);
  }
}



/*****************
 *               *
 *   Interface   *
 *               *
 *****************/


void
lowScanIOA(long printVisited, long printOrigin, long printSize,
	   long docallback,
	   ref(ProtoType) rootProto,
	   void (*cb)(ref(Object)))
{
  scanIOAliveObjects(printVisited,
		     printOrigin,
		     printSize,
		     docallback,
		     rootProto,
		     cb);
}


void
lowScanAOA(long printVisited, long printOrigin, long printSize,
	   long docallback,
	   ref(ProtoType) rootProto,
	   void (*cb)(ref(Object)))
{
  scanAOAliveObjects(printVisited,
		     printOrigin,
		     printSize,
		     docallback,
		     rootProto,
		     cb);
}
#endif /* !MT */
