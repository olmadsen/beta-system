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
SetArgValues(int argc, char *argv[])
{
  ArgCount = argc;
  ArgVector = argv;
}
#endif


/* GC/PerformGC.c: Not declared in function.h, doGC should only be 
 * called from IOA(c)lloc or DoGC.
 */
extern void doGC();


#ifndef RTDEBUG
/* inline */
#endif
char *
  IOAalloc(unsigned size)
{
  register char *p;
  
  GCable_Entry();
  
  /*fprintf(output, "IOAalloc: IOATop=0x%x, size=0x%x\n", IOATop, size);*/
  
  DEBUG_CODE(Claim(size>0, "IOAalloc: size>0"));
#if (defined(sparc) || defined(hppa) || defined(crts))
  DEBUG_CODE(Claim( ((long)size&7)==0 , "IOAalloc: (size&7)==0"));
  DEBUG_CODE(Claim( ((long)IOATop&7)==0 , "IOAalloc: (IOATop&7)==0"));
#endif
  
  while ((char *)IOATop+size > (char *)IOALimit) {
    ReqObjectSize = size / 4;
    doGC();
  }
  
  p = (char *)IOATop;
#ifdef hppa
  /*
    setIOATopoffReg(getIOATopoffReg() + size);
    */
  IOATop = (long*)((long)IOATop+size);
#endif
#ifdef sparc
  IOATopoff += size;
#endif
#ifdef crts
  IOATop = (long*)((long)IOATop+size);
#endif
  
  return p;
  
}

#ifndef RTDEBUG
/* inline */
#endif
char *
  IOAcalloc(unsigned size)
{
  
  register char *p;
  
  GCable_Entry();
  
  /*fprintf(output, "IOACalloc: IOATop=0x%x, size=0x%x\n", IOATop, size);*/
  
  DEBUG_CODE(Claim(size>0, "IOACalloc: size>0"));
#if (defined(sparc) || defined(hppa) || defined(crts))
  DEBUG_CODE(Claim( ((long)size&7)==0 , "IOAcalloc: (size&7)==0"));
  DEBUG_CODE(Claim( ((long)IOATop&7)==0 , "IOAcalloc: (IOATop&7)==0"));
#endif
  
  while ((char *) IOATop+size > (char *)IOALimit) {
    ReqObjectSize = size / 4;
    doGC();
  }
  
  p = (char *)IOATop;
#ifdef hppa
  /*setIOATopoffReg(getIOATopoffReg() + size);*/
  IOATop = (long*)((long)IOATop+size);
#endif
#ifdef sparc
  IOATopoff += size;
#endif
#ifdef crts
  IOATop = (long*)((long)IOATop+size);
#endif
  
  long_clear(p, size);
  
  return p;
}

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

#ifdef crts

/* Global address registers */
long a0, a1, a2, a3, a4, a7; 
long leave;

void FailureExit()
{
  BetaError(StopCalledErr, (struct Object *) a0);
}

/* New RT routines for crts */

void pushAdr(a)
     long *a;
{
  *RefSP++ = (long)a;
}

long *popAdr()
{
  return (long *) *(--RefSP);
}  

/* oldStackPtr is provited to the callback function by HandleCB which read the
   value of the old stack pointer when called. It is then necessary that the
   called BETA object is called with the parameters theObj, oldStackPtr, arg1,..
*/
int CallBackPar(long oldStackPtr, long parNo)
{
  register long retValue;

  switch (parNo){
  case 1:
    asm("mov %%o0, %0": "=r" (retValue));
  case 2:
    asm("mov %%o1, %0": "=r" (retValue));
  case 3:
    asm("mov %%o2, %0": "=r" (retValue));
  case 4:
    asm("mov %%o3, %0": "=r" (retValue));
  otherwise:
    /* Ok, this is a hard one: oldStackPtr points to the previosly stack frame.
       This frame contains the parameters of the C-function calling back to BETA.
       On SPARC 23 words are used before the the parameters past the sixth (if any)
       are pushed on the stack. The first parameter on the stack is then the
       seventh parameter and so one.
       */
    retValue=*(long *)(oldStackPtr+23+(parNo-5));
  }
  return retValue;
}

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

/* Implementation of a pool of jmpbuffers. */

#define maxNoInPool 10

/* Basis type in pool of jump buffers */
typedef struct jmpInfoElem {
  jmp_buf *jumpBuffer;
  long * refTop;
  struct jmpInfoElem * nextElem;
} jmpInfoElem;

jmp_buf *CRTSjbp;
jmpInfoElem *jumpList;
jmpInfoElem *jumpListHead;

void initJmpPool()
{
  jmpInfoElem *tmp;
  jmp_buf *jumpBufPool;
  int i;
  
  jumpList = (jmpInfoElem *)malloc(sizeof(jmpInfoElem)*maxNoInPool);
  jumpListHead = jumpList;
  jumpBufPool = (jmp_buf *)malloc(sizeof(jmp_buf)*maxNoInPool);
  tmp = jumpList;
  for (i=0; i<(maxNoInPool-1); i++){ 
    tmp->jumpBuffer = jumpBufPool+i;
    tmp->nextElem = tmp+1; /* next points to next element in list */
    tmp = tmp->nextElem;
  }
  /* Last element needs special care */
  tmp->jumpBuffer = jumpBufPool+i;
  tmp->nextElem = NULL; /* Last element in list points to zero */
}

void reallocJmpList()     
{
  int i=0;
  jmpInfoElem *p=jumpListHead;
  jmp_buf * jmpBufPool;
  while (p != NULL){
    /* Calculate number in current chain. This may be larger than maxNoInPool. */
    p = p->nextElem;
    i++;
  }
  jumpListHead = (jmpInfoElem *) realloc(jumpListHead,
					 (i+maxNoInPool)*sizeof(jmpInfoElem));
  jumpList = jumpListHead+i-1; /* Point to previously last element in chain */
  jumpList->nextElem = jumpList+1;
  jmpBufPool = (jmp_buf *)malloc(maxNoInPool*sizeof(jmp_buf));
  p = jumpList->nextElem;
  /* Initialize new chain section to point to malloc'ed pool area */
  for (i=0; i<maxNoInPool-1; i++){
    p->jumpBuffer = jmpBufPool+i;
    p->nextElem = p+1;
    p = p->nextElem;
  }
  p->jumpBuffer = jmpBufPool+i;
  p->nextElem = NULL; /* Last element in chain has to be NULL */
}


/* 1. allocate a jmp_buf to be used by longjmp;   */
/*    this is done below                          */
/* 2. save stacktop of ref. stack;                */
/*    this is currently NOT done                  */
/* 3. save ref. for above info in a0[off]         */
/*    currently only 1 is saved                   */
/* 4. return jmp_buf                              */

jmp_buf *GetJmpBuf(int addr, int off)
{
  jmp_buf *tmp;
  
  if (jumpList->nextElem==NULL)
    reallocJmpList();
  tmp = jumpList->jumpBuffer;
  jumpList->refTop = RefSP; 
  *(jmpInfoElem **)(addr+off) = jumpList;
  jumpList=jumpList->nextElem;
  return tmp;
}

void FreeJmpBuf(int addr, int off)
{
  jmpInfoElem *p;
  
  p = *(jmpInfoElem **)(addr+off);
  jumpList = jumpList-1; /* Previous element in list */
  jumpList->jumpBuffer = p->jumpBuffer;
  jumpList->nextElem = jumpList+1; /* Next element in list */
}

/* 1. get ref. to stateinfo from a1[off]  */
/* 2. restore ref stack top               */
/*    NOT done                            */
/* 3. restore a0 using a1                 */
/* 4. return saved jmp_buf                */
/* 5. jmp_buf should really be deallocaed */

jmp_buf *UseJmpBuf(int addr, int off)
{
  jmpInfoElem *p;
  jmp_buf *jbuf;
  
  a0 = (long)addr;                                
  p = *(jmpInfoElem **)(addr+off); 
  RefSP = p->refTop;                               
  CRTSjbp = p->jumpBuffer;
  jbuf = p->jumpBuffer;
  FreeJmpBuf(addr, off);
  return jbuf;
}
#endif /* crts */
