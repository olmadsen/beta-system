/*
 * BETA C RUNTIME SYSTEM, Copyright (C) 1992-94 Mjolner Informatics Aps.
 * by Ole Lehrmann Madsen, and Peter Andersen
 */

#include "beta.h"
#include "crun.h"

void SetProtos(struct ProtoType *basic, struct ProtoType *text) {
   BasicProto = basic; 
   TextProto = text; 
}

void main(long argc, char *argv[])
{
  SetArgValues(argc,argv); /* Initializes ArgC and ArgV */
  Initialize(); /* Initializes heaps etc */
  BETA_main(); /* Calls SetProtos from betaenv */

  ActiveComponent = AlloC(0, BasicProto, 0); /* Assumption: NO GC here! */
  BasicItem = (struct Item *)&ActiveComponent->Body;

  push(0); /* NULL terminate internal ReferenceStack */

  StackStart = GetSP();
  DEBUG_STACK(fprintf(output, "StackStart=0x%x\n", StackStart));

  /* M1BETAENV(0,BasicItem) */
  CallB( GENMARK /*dyn*/, 
	 (struct Object *)BasicItem, /* object */
	 (long)(BasicItem->Proto->TopMpart), /* entrypoint */
	 0); /* SP */

  /* TerminateBasicComponent: */
  BetaExit(0);
 }

void AttBC(void)
{
}
