/*
 * BETA C RUNTIME SYSTEM, Copyright (C) 1992-94 Mjolner Informatics Aps.
 * by Peter Andersen, Tommy Thorn, and Jacob Seligmann
 */

#define GCable_Module

#include "beta.h"
#include "crun.h"

#ifdef hppa
unsigned savedIOATopoff;
long *   savedIOA;
long *   savedRefSP;
#endif

#ifdef hppa
void Return() {}
#endif

#ifdef crts
void Return() 
{
}
#endif

#ifdef sparc
     /* The first nop is needed in case Return is called directly from a 
      * runtime ruotine. This is the case for e.g. an empty program.
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
  BetaError(RefNoneErr, theObj);
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
  setIOATopoffReg(getIOATopoffReg() + size);
#endif
#ifdef sparc
  IOATopoff += size;
#endif
#ifdef crts
  IOATop += size;
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
  setIOATopoffReg(getIOATopoffReg() + size);
#endif
#ifdef sparc
  IOATopoff += size;
#endif
#ifdef crts
  IOATop += size;
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
  BetaError(StopCalledErr, cast(Object)(getD0Reg()));
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
#endif
#endif

#ifdef crts

/* Global address registers */
char *a0,*a1,*a2,*a3,*a4,*a7;
long leave;

/* New RT routines for crts */
static long *refstack[1000];
static long reftop=0;

void pushAdr(a)
     long *a;
{
  refstack[reftop] = a;
  reftop=reftop+1;
}

long *popAdr()
{
  reftop=reftop-1;
  return (long *)refstack[reftop];
}  

int CallBackPar(off)
     int off;
{
}

void Trap()
{
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

/* This is a new jumpbuf implementation (pool of jmpbuffers). 
 *  PRJ
 */

#define maxNoInPool 10

/* Basis type in pool of jump buffers */
typedef struct jmpInfoElem {
  jmp_buf *jumpBuffer;
  long refTop;
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


jmp_buf *GetJmpBuf(int addr, int off)
{
  jmp_buf *tmp;

  if (jumpList->nextElem==NULL)
    reallocJmpList();
  tmp = jumpList->jumpBuffer;
  jumpList->refTop = reftop; 
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


jmp_buf *UseJmpBuf(int addr, int off)
{
  jmpInfoElem *p;
  jmp_buf *jbuf;

  a0 = (char *)addr;                                
  p = *(jmpInfoElem **)(addr+off); 
  reftop = p->refTop;                               
  CRTSjbp = p->jumpBuffer;
  jbuf = p->jumpBuffer;
  FreeJmpBuf(addr, off);
  return jbuf;
}



#if 0
/* Old jump buffer implementation. PRJ */
typedef struct jmpInfo {
  jmp_buf *jumpBuffer;
  long refTop;
} jmpInfo;

jmp_buf *CRTSjbp;

/* 1. allocate a jmp_buf to be used by longjmp;   */
/*    this is done below                          */
/* 2. save stacktop of ref. stack;                */
/*    this is currently NOT done                  */
/* 3. save ref. for above info in a0[off]         */
/*    currently only 1 is saved                   */
/* 4. return jmp_buf                              */
jmp_buf *GetJmpBuf(int addr, int off) 
{
  jmpInfo *p;

  p = (struct jmpInfo *)malloc(sizeof(jmpInfo));
  p->jumpBuffer = (jmp_buf *)malloc(sizeof(jmp_buf)); /* 1 */
  p->refTop = reftop;                                 /* 2 */
  *(jmpInfo **)(addr+off) = p;                        /* 3 */
  return p->jumpBuffer;                               /* 4 */
}
 
/* 1. get ref. to stateinfo from a1[off]  */
/* 2. restore ref stack top               */
/*    NOT done                            */
/* 3. restore a0 using a1                 */
/* 4. return saved jmp_buf                */
/* 5. jmp_buf should really be deallocaed */
jmp_buf *UseJmpBuf(int addr, int off)
{
  struct jmpInfo *p;
  jmp_buf *tmp;

  a0 = (char *)addr;                                 /* 3 */
  p = *(jmpInfo **)(addr+off);                       /* 1 */
  reftop = p->refTop;                                /* 2 */
  tmp = p->jumpBuffer;
  free(p);                                           /* 5 */
  CRTSjbp = tmp;           /* To be free'd later! */ /* 5 */
  return tmp;                                        /* 4 */
}


void FreeJmpBuf(int a, int b)
{
  printf("FreeJumpBuf NYI\n");
}

#endif
#endif /* crts */
