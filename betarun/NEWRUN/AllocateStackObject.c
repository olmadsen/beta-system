/*
 * BETA C RUNTIME SYSTEM, Copyright (C) 1992-94 Mjolner Informatics Aps.
 * by Peter Andersen, Peter Orbaek and Tommy Thorn.
 */

#include "beta.h"
#include "crun.h"

struct StackObject *AlloSO(unsigned size, long *SP)
{
    struct StackObject *sObj=0;
    unsigned long stacksize = StackObjectSize(size);

    DEBUG_CODE(NumAlloSO++);

    if (stacksize>IOAMAXSIZE){
      DEBUG_AOA(fprintf(output, "AlloSO allocates in AOA\n"));
      sObj = (struct StackObject *)AOAalloc(stacksize);
      DEBUG_AOA(if (!sObj) fprintf(output, "AOAalloc failed\n"));
    }
    if (!sObj){
      sObj = (struct StackObject *)IOAalloc(stacksize, SP);
    }

    sObj->Proto = StackObjectPTValue;
    sObj->GCAttr = 1;
    sObj->BodySize = size;
    sObj->StackSize = 0;

    /*fprintf(output, "AlloSO: theObj: 0x%x, size=0x%x\n", sObj, size);*/

    Ck(sObj);

    return sObj;
}


