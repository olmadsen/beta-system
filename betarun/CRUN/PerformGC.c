/*
 * BETA C RUNTIME SYSTEM, Copyright (C) 1992-94 Mjolner Informatics Aps.
 * by Peter Andersen, Tommy Thorn, and Jacob Seligmann.
 */

#define GCable_Module

#include "beta.h"
#include "crun.h"

#ifdef MT

struct Object *doGC(unsigned numbytes)
{ 
  int i;
  struct Object *newObj;

  ReqObjectSize = numbytes/4;
  /* Try up to 3 IOAGcs to mature enough object to go into AOA */
  for (i=0; i<3; i++){
    IOAGc();
    if ((long)IOATop+numbytes <= (long)IOALimit) {
      /* There is now room in IOA for the new object */
      newObj = (struct Object *)IOATop;
      IOATop += numbytes;
      return newObj;
    } else {
      INFO_IOA(fprintf(output, "[%d]\n", i+1));
      if (i==2){
	/* Have now done two IOAGc's without freeing enough space.
	 * Make sure that all objects go to AOA in the next GC.
	 */
	IOAtoAOAtreshold=2;
	DEBUG_IOA(fprintf(output, "Forcing all objects in IOA to AOA\n"));
	IOAGc();
	if ((long)IOATop+numbytes <= (long)IOALimit) {
	  /* There is now room in IOA for the new object */
	  newObj = (struct Object *)IOATop;
	  IOATop += numbytes;
	  return newObj;
	} else {
	  /* Have now tried everything to get enough space in IOA */
	  /* Aber dann haben wir anderen metoden! */
	  return AOAcalloc(numbytes);
	}
      }
    }
  }
  /* Not reached */
  DEBUG_CODE(Claim(TRUE, "doGC: end not reached"));
  return 0;
}

void DoGC() /* The one called directly from betaenv */
{
  fprintf(output, "DoGC: NYI\n");
  doGC(0);
}


#else /* Not MT */

#ifdef crts
extern long a0;
extern long a1;
extern long a2;
extern long a3;
extern long a4;
#endif 

void doGC() /* The one called from IOA(c)alloc */
{
#ifdef crts
    PushGCRegs();
    CkReg("doGC", *(RefSP-1), "a4");
    CkReg("doGC", *(RefSP-2), "a3");
    CkReg("doGC", *(RefSP-3), "a2");
    CkReg("doGC", *(RefSP-4), "a1");
    CkReg("doGC", *(RefSP-5), "a0");
    IOAGc();
    PopGCRegs();
#endif
#ifdef sparc
    GCable_Entry();
    StackEnd = (long *)((struct RegWin *) StackPointer);
    IOAGc();
#endif
#ifdef hppa
#ifndef UseRefStack
    StackEnd = (long *)getSPReg();
#endif /* UseRefStack */
    PushGCRegs();
    CkReg("doGC", *(RefSP-1), "%r7");
    CkReg("doGC", *(RefSP-2), "%r6");
    CkReg("doGC", *(RefSP-3), "%r5");
    CkReg("doGC", *(RefSP-4), "%r4");
    CkReg("doGC", *(RefSP-5), "%r3");
    IOAGc();  /* saves r8 */
    PopGCRegs();
#endif
}

#ifdef sparc
/* IOA(c)alloc is now in-lined.
 * That is, ProcessStack does not skip the regwin of IOA(c)alloc,
 * and thus there is no need for the extra regwin around doGC anymore.
 */
#ifdef sun4s
asmlabel(DoGC,
	 "sethi  %hi(ReqObjectSize),%g1\n"
	 "ba     doGC\n"
         "clr    [%g1+%lo(ReqObjectSize)]\n");
#else
asmlabel(DoGC,
	 "sethi  %hi(_ReqObjectSize),%g1\n"
	 "ba     _doGC\n"
         "clr    [%g1+%lo(_ReqObjectSize)]\n");
#endif
#else
void DoGC() /* The one called directly from betaenv */
{
  ReqObjectSize = 0;
  doGC();
}
#endif

#ifdef RTDEBUG
void DoGC_UseCk()
{
  Ck(0);
}
#endif

#endif /* Not MT */
