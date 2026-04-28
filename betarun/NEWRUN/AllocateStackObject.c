/*
 * BETA C RUNTIME SYSTEM, Copyright (C) Aarhus University
 * by Peter Andersen, Peter Orbaek and Tommy Thorn.
 */

#include "beta.h"
#include "crun.h"

StackObject *AlloSO(unsigned size, long *SP)
{
    StackObject *sObj=0;
    unsigned long stacksize = StackObjectSize(size);

    DEBUG_CODE(NumAlloSO++);

    do {
      if (stacksize>IOAMAXSIZE){
	DEBUG_AOA(fprintf(output, "AlloSO allocates in AOA\n"));
	sObj = (StackObject *)AOAalloc(stacksize);
	DEBUG_AOA(if (!sObj) fprintf(output, "AOAalloc failed\n"));
      }
      if (sObj){
	sObj->GCAttr = 0; /* In AOA */
      } else {
	sObj = (StackObject *)IOATryAlloc(stacksize, SP);
	if (sObj && IOAMinAge!=0) sObj->GCAttr = IOAMinAge; /* In IOA */
      }
    } while (!sObj);

    SETPROTO(sObj, StackObjectPTValue);
    /* sObj->GCAttr set above if in IOA */
    sObj->BodySize = size;
    /* No need: IOA is memset(0) sObj->StackSize = 0; */

    /*fprintf(output, "AlloSO: theObj: 0x%x, size=0x%x\n", sObj, size);*/

    /* Ck(sObj); No good - the stack part is not yet initialized */

    return sObj;
}


