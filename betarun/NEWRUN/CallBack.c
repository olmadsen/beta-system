/*
 * BETA C RUNTIME SYSTEM, Copyright (C) 1992-94 Mjolner Informatics Aps.
 * by Peter Oerbaek, Peter Andersen, Tommy Thorn and Kim Jensen Moeller.
 */

#include "beta.h"
#include "crun.h"


/* UNSOLVED PROBLEM:
 * if valhallaisstepping, we should call valhalla after callback returns to C 
 */


#ifdef RTVALHALLA
#include "valhallaComm.h"
#endif /* RTVALHALLA */


#ifdef sgi
#include <sys/cachectl.h>
#define GEN_CB_STUB()                                                         \
                                                                              \
 /*                                                                           \
  * lui t9,     entry     >> 16                                               \
  * ori t9, t9, entry     & 0xffff                                            \
  * lui r8,     strucaddr >> 16                                               \
  * ori r8, r8, strucaddr & 0xffff                                            \
  * jr  t9                                                                    \
  */                                                                          \
                                                                              \
 CBFATop->code[0]= 0x3c000000 | (25 << 16) | (entry >> 16);                   \
 CBFATop->code[1]= 0x34000000 | (25 << 21) | (25<< 16) | (entry & 0xffff);    \
 CBFATop->code[2]= 0x3c000000 | (8 << 16) | (strucaddr >> 16);               \
 CBFATop->code[3]= 0x34000000 | (8 << 21) | (8 << 16) | (strucaddr & 0xffff);\
 CBFATop->code[4]= 0x8 | (25 << 21);                                          \
                                                                              \
 cacheflush(&CBFATop->theStruct, sizeof(CallBackEntry), BCACHE)               \

#endif


/* CopyCPP:
 * Called from BETA to generate callback code, i.e. the code
 * called from C before re-entering BETA world.
 */
void *CopyCPP(struct Structure *theStruct, struct Structure *dummy) 
{
  unsigned long entry;     /* Beta code stub, e.g. _foo */
  unsigned long strucaddr; /* Address of struc */

  DEBUG_CODE(NumCopyCPP++);

  if (!theStruct) return (void *)0 /* NULL function pointer given to C */;
 
  if (theStruct->Proto != StructurePTValue){
    printf("\n*** CopyCPP: dummy used\n");
    theStruct = dummy;
  }
  if (theStruct->Proto != StructurePTValue){
    printf("\n*** CopyCPP: dummy ILLEGAL\n");
  }
  
  /* Take the next free entry in the Call Back Functions Area.	*/
  /* This area is defined by 
   * [ lastCBFABlock->entries <= CBFATop < CBFALimit ].
   */

  if (CBFATop+1 > CBFALimit){
    CBFArelloc();
  }

  Ck(theStruct);Ck(theStruct->iOrigin);

  CBFATop->theStruct = theStruct;

  entry     = (unsigned long)theStruct->iProto->CallBackRoutine;
  strucaddr = (unsigned long)&CBFATop->theStruct;

  GEN_CB_STUB();

  DEBUG_CBFA(fprintf(output, "CopyCPP: allocated callback stub 0x%x\n", CBFATop));

  ++CBFATop;
  return (void *)&(CBFATop-1)->code[0];
}


/* AlloSICB:
 * Called from BETA callback stub to allocate item and setup
 * stack to make GC handle callback frames on stack.
 */
struct Item *AlloSICB(struct Structure **struchandle, long *SP)
{
  /* Put ActiveCallBackFrame on stack */

  /* inlined AlloSI */
  struct Item *ss;
  struct Structure *struc = *struchandle;
  DEBUG_CODE(NumAlloSICB++);
  Ck(struc);
  Ck(struc->iOrigin);
  ss = AlloI((struct Object *)struc->iOrigin, struc->iProto, SP);
  Ck(ss);
  return ss;
}
