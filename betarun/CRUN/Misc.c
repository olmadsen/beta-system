/*
 * BETA C RUNTIME SYSTEM, Copyright (C) 1992-94 Mjolner Informatics Aps.
 * by Peter Andersen, Tommy Thorn, and Jacob Seligmann
 */

#define GCable_Module

#include "beta.h"
#include "crun.h"

#if 0
#ifdef hppa
unsigned savedIOATopoff;
long *   savedIOA;
long *   savedRefSP;
#endif
#endif

#ifdef hppa
void Return() 
{}
#endif
     
#ifdef crts
void Return() 
{}
#endif

#ifdef sparc
/* The first nop is needed in case Return is called directly from a 
 * runtime routine. This is the case for e.g. an empty program.
 */
#ifdef sun4s
asmlabel(Return, "nop; retl; nop");
#else
asmlabel(_Return, "nop; retl; nop");
#endif
#endif

void
  RefNone(ref(Object) theObj)
{
#if (defined(hppa) && defined(RTLAZY))
  /* Called with the possible dangling reference in %r31 */
  asm volatile ("\tCOPY\t%%r31,%0\n" : "=r" (theObj));
  if (isLazyRef(theObj)){
    /* save reference registers in case of dangling reference */
    PushGCRegs();
    CkReg("RefNone", *(RefSP-1), "%r7");
    CkReg("RefNone", *(RefSP-2), "%r6");
    CkReg("RefNone", *(RefSP-3), "%r5");
    CkReg("RefNone", *(RefSP-4), "%r4");
    CkReg("RefNone", *(RefSP-5), "%r3");
    /* Save data registers on machine stack in case of dangling reference */
    pushReg((void *)getD0Reg());
    pushReg((void *)getD1Reg());
    pushReg((void *)getR8Reg());
    
    LazyDangler = (long)theObj; /* dangling reference */
    CallBetaEntry(*((long *)LazyItem->Proto-1), LazyItem);
    
    setR8Reg((long)popReg());
    setD1Reg((long)popReg());
    setD0Reg((long)popReg());
    PopGCRegs();
  } else {
    /* Reference was NONE */
    theObj = (struct Object *)getThisReg(); /* Get current object */
    BetaError(RefNoneErr, theObj);
  }
#else
#ifdef hppa
    theObj = (struct Object *)getThisReg(); /* Get current object */
#endif
  BetaError(RefNoneErr, theObj);
#endif /* hppa && RTLAZY */
  
}

#ifdef sparc
/* Need to do this in assembler, as the arguments to
   my caller normally isn't accesseable */
asmlabel(SetArgValues, "
	set "USCORE"ArgCount, %g1
	st %i0, [%g1]
	set "USCORE"ArgVector, %g1
	retl
	st %i1, [%g1]
");
#else
void SetArgValues(int argc, char *argv[])
{
  ArgCount = argc;
  ArgVector = argv;
}
#endif

#ifdef sparc
#ifdef sun4s
asmlabel(FailureExit, "
	mov	%i0, %o1
	call	BetaError
	mov	-8, %o0
");
#else
asmlabel(_FailureExit, "
	mov	%i0, %o1
	call	_BetaError
	mov	-8, %o0
");
#endif
#endif

#ifdef hppa
void FailureExit()
{
  BetaError(StopCalledErr, cast(Object)(getThisReg()));
}
#endif


#ifdef RTDEBUG
#ifndef hppa
void CCk(ref(Object) r)
{
  if(r) 
    Claim(inIOA(r) || inAOA(r) || inLVRA(r) || isLazyRef(r),
	  "Reference none or inside IOA, AOA, or LVRA");
}
#endif hppa
#endif

#ifdef RTDEBUG
void Misc_UseCk()
{
  Ck(0);
}
#endif

#ifdef crts

/* Global address registers */
long a0, a1, a2, a3, a4, a7; 
long leave;

void FailureExit()
{
  BetaError(StopCalledErr, (struct Object *) a0);
}

/* New RT routines for crts */


void Trap()
{
  fprintf(output, "Trap called... Exiting\n");
  exit(0);
}

char GetByte(unsigned long a, int byteNo /* 0-3 */)
{ return (a >> (8*(3-byteNo))) & 0xff; /* big endian */ }

unsigned short GetShort(unsigned long a,int shortNo /* 0-1 */)
{ return (a >> (16*(1-shortNo))) & 0xffff; /* big endian */ }

void PutBits(unsigned long a, unsigned long *b, int pos, int len)
{
  *b= ((a & ((1<<len)-1)) << (32-len-pos)) 
    | (*b & ~(((1<<len)-1) << (32-len-pos)) );
}

unsigned long GetBits(unsigned long a, int pos, int len)
{
  if (len==0) return 0;
  return (a<<pos) >> (32-len);
}

signed long GetSignedBits(unsigned long a, int pos, int len)
{
  if (len==0) return 0;
  return ((signed long)(a<<pos)) >> (32-len);
}

signed long SignExtByte(signed char a)
{
  return (a<<24)>>24;
}

signed long SignExtWord(signed short a)
{
  return (a<<16)>>16;
}



#include <setjmp.h>

#ifdef RTDEBUG

long memcnt=0;
#define INFO_ALLOC(size) {\
  memcnt+=size; \
  /*fprintf(output, "jmp-alloc: 0x%x total 0x%x\n",size, memcnt); */}
#define INFO_FREE(size) {\
  memcnt-=size; \
  /*fprintf(output, "jmp-free: 0x%x total 0x%x\n",size, memcnt);*/ }
#else
#define INFO_FREE(size)
#endif


/* Basis type in pool of jump buffers */
typedef struct jmpInfoElem {
  jmp_buf *jumpBuffer;
  long * refTop;
} jmpInfoElem;

#ifdef SIMPLEJMP
jmp_buf glb_jmp_buf;
#else
/* Implementation of a pool of jmpbuffers. */
#define maxNoInPool 1000

jmp_buf *CRTSjbp;
jmpInfoElem *jumpList;
jmpInfoElem *jumpListHead;
long numInJumpBuf=maxNoInPool;

void initJmpPool()
{
  jmpInfoElem *tmp;
  jmp_buf *jumpBufPool;
  int i;
  
  jumpList = (jmpInfoElem *)MALLOC(sizeof(jmpInfoElem)*numInJumpBuf);
  INFO_ALLOC(sizeof(jmpInfoElem)*numInJumpBuf);
  jumpListHead = jumpList;
  jumpBufPool = (jmp_buf *)MALLOC(sizeof(jmp_buf)*numInJumpBuf);
  INFO_ALLOC(sizeof(jmp_buf)*numInJumpBuf);
  tmp = jumpList;
  for (i=0; i<numInJumpBuf; i++){ 
    tmp->jumpBuffer = jumpBufPool+i;
    tmp++;
  }
}

void reallocJmpList()     
{
  int i=0;
  jmpInfoElem *p;
  jmp_buf * jmpBufPool;
  fprintf(output,"WARNING: JmpPool overflow...\n"); fflush(output);
  jumpListHead = (jmpInfoElem *) REALLOC(jumpListHead,
					 2*numInJumpBuf*sizeof(jmpInfoElem));
  jumpList = jumpListHead+numInJumpBuf; /* Points to element after last element */
  p = jumpList;
  jmpBufPool = (jmp_buf *)MALLOC(numInJumpBuf*sizeof(jmp_buf));
  INFO_ALLOC(numInJumpBuf*sizeof(jmp_buf));
  /* Initialize new chain section to point to malloc'ed pool area */
  for (i=0; i<numInJumpBuf; i++){
    p->jumpBuffer = jmpBufPool+i;
    p++;
  }
  numInJumpBuf*=2;
}

#endif SIMPLEJMP


/* 1. allocate a jmp_buf to be used by longjmp;   */
/*    this is done below                          */
/* 2. save stacktop of ref. stack;                */
/*    this is currently NOT done                  */
/* 3. save ref. for above info in a0[off]         */
/*    currently only 1 is saved                   */
/* 4. return jmp_buf                              */

jmp_buf *GetJmpBuf(int addr, int off)
{
#ifdef SIMPLEJMP

  jmpInfoElem *info;
  if (*(jmpInfoElem **)(addr+off) != 0 ) {
    info=*(jmpInfoElem **)(addr+off);
    info->refTop = RefSP;
    /*    FreeJmpBuf(addr,off);*/
  } else {
    info = (jmpInfoElem *)MALLOC(sizeof(jmpInfoElem));
    INFO_ALLOC(sizeof(jmpInfoElem));
    info->refTop = RefSP;
    info->jumpBuffer = (jmp_buf *)MALLOC(sizeof(jmp_buf));
    INFO_ALLOC(sizeof(jmp_buf));
    *(jmpInfoElem **)(addr+off) = info;
  }
  return info->jumpBuffer;

#else SIMPLEJMP

  jmp_buf *tmp;
  
  if (jumpList >= jumpListHead+numInJumpBuf){
    reallocJmpList();
  }
  tmp = jumpList->jumpBuffer;
  jumpList->refTop = RefSP; 
  *(jmpInfoElem **)(addr+off) = jumpList;
  jumpList=jumpList+1;
  return tmp;
#endif SIMPLEJMP
}

void FreeJmpBuf(int addr, int off)
{
#ifdef SIMPLEJMP
  jmpInfoElem *info = *(jmpInfoElem **)(addr+off);
  if (info) {
    FREE(info->jumpBuffer); /* NO! Look at how it is used in UseJmpBuf! */
    INFO_FREE(sizeof(jmpInfoElem));
    FREE(info);
    INFO_FREE(sizeof(jmp_buf));
    *(jmpInfoElem **)(addr+off) = 0;
  } else {
    fprintf(output,"WARNING: attempt to clear jmp_buf 0 in 0x%x, off: %d\n",addr,off);
  }
#endif SIMPLEJMP
#if 0
  jmpInfoElem *p;
  p = *(jmpInfoElem **)(addr+off);
  jumpList = jumpList-1; /* Previous element in list */
  jumpList->jumpBuffer = p->jumpBuffer;
  jumpList->nextElem = jumpList+1; /* Next element in list */
#endif
}

/* 1. get ref. to stateinfo from a1[off]  */
/* 2. restore ref stack top               */
/*    NOT done                            */
/* 3. restore a0 using a1                 */
/* 4. return saved jmp_buf                */
/* 5. jmp_buf should really be deallocaed */

jmp_buf *UseJmpBuf(int addr, int off)
{
#ifdef SIMPLEJMP  
  jmpInfoElem *info;
  jmp_buf *jbuf;
  
  a0 = (long)addr;                                
  info = *(jmpInfoElem **)(addr+off); 
  RefSP = info->refTop;                               
  memcpy(&glb_jmp_buf, info->jumpBuffer, sizeof(jmp_buf));
  FreeJmpBuf(addr, off);
  return &glb_jmp_buf;
#else SIMPLEJMP
  jmpInfoElem *p;
  jmp_buf *jbuf;
  
  a0 = (long)addr;                                
  p = *(jmpInfoElem **)(addr+off); 
  RefSP = p->refTop;                               
  CRTSjbp = p->jumpBuffer;
  jbuf = p->jumpBuffer;
  FreeJmpBuf(addr, off);
  return jbuf;
#endif SIMPLEJMP
}
#endif /* crts */
