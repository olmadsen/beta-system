/*
 * BETA C RUNTIME SYSTEM, Copyright (C) 1992-94 Mjolner Informatics Aps.
 * by Ole Lehrmann Madsen, and Peter Andersen
 */

#include "beta.h"
#include "crun.h"

void SetProtos(ProtoType *basic, ProtoType *text) {
   BasicProto = basic; 
   TextProto = text; 
}

int main(int argc, char *argv[])
{
  SetArgValues(argc,argv); /* Initializes ArgC and ArgV */
  Initialize(); /* Initializes heaps etc */
  BETA_main(); /* Calls SetProtos from betaenv */

  ActiveComponent = AlloC(0, BasicProto, 0); /* Assumption: NO GC here! */
  BasicItem = (Item *)&ActiveComponent->Body;

  push(0); /* NULL terminate internal ReferenceStack */

  StackStart = GetSP();
  DEBUG_STACK(fprintf(output, "StackStart=0x%x\n", (int)StackStart));

  /* M1BETAENV(0,BasicItem) */
  CallB( GENMARK /*dyn*/, 
	 (Object *)BasicItem, /* object */
	 (long)(GETPROTO(BasicItem)->TopMpart), /* entrypoint */
	 0); /* SP */

  /* TerminateBasicComponent: */
  BetaExit(0);

  return 0; /* Keep compiler happy */

 }

void AttBC(void)
{
}
