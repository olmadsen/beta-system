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

extern void BETA_main(void);

void main(long argc, char *argv[])
{
  SetArgValues(argc,argv);
  Initialize();
  BETA_main();

  ActiveComponent = AlloC(0, BasicProto, 0);
  BasicItem = (struct Item *)&ActiveComponent->Body;

  push(0); /* NULL terminate internal ReferenceStack */

  StackStart = GetSP();

  /* M1BETAENV(0,BasicItem) */
  CallBetaEntry( *((long *)BasicItem->Proto-1)-8, BasicItem /*dyn*/, BasicItem);

  /* TerminateBasicComponent: */
  BetaExit(0);
 }

void AttBC(void)
{
}
