/*
 * BETA C RUNTIME SYSTEM, Copyright (C) 1992-94 Mjolner Informatics Aps.
 * by Peter Andersen, Tommy Thorn, and Jacob Seligmann
 */

#define GCable_Module

#include "beta.h"
#include "crun.h"

#if (defined(sparc) && (!defined(RTDEBUG)))
/* An extra nop is needed before retl in case Return is called directly
 * from a runtime routine. This is the case for e.g. an empty program.
 * If you try to do this with an asm("nop") in a C function, the C function
 * will NOT become a leaf routine. Thus we do it manually her.
 */
#ifdef sun4s
asmlabel(Return, "nop; retl; nop");
#else
asmlabel(_Return, "nop; retl; nop");
#endif /* sun4s */
#else
void Return() 
{
  DEBUG_CODE(NumReturn++);
  return;
}
#endif

#ifdef sparc
/* Functions used to call RT routines directly from C.
 * Needed because %i1 in calling regwin is destroyed by (C)AlloSI
 * Must be here away from the corresponding CAlloXXX functions
 * to prevent gcc from inlining it.
 */

struct Item *SPARC_AlloSI(struct Structure *s, int i1, int i2, int i3, int i4)
{
  struct Item *CAlloSI(struct Structure *s, int i1, int i2, int i3, int i4);
  GCable_Entry();
  return CAlloSI(s, i1, i2 ,i3, i4);
  GCable_Exit(1);
}

struct Component *SPARC_AlloC(struct Object *origin, int i1, struct ProtoType *proto, int i3, int i4)
{
  struct Component *CAlloC(struct Object *origin, 
			   int i1, 
			   struct ProtoType *proto, 
			   int i3, 
			   int i4);
  GCable_Entry();
  return CAlloC(origin, i1, proto, i3, i4);
  GCable_Exit(1);
}

struct Item *SPARC_AlloI(struct Object *origin, int i1, struct ProtoType *proto, int i3, int i4)
{ struct Item *CAlloI(struct Object *origin, int i1, struct ProtoType *proto, int i3, int i4);
  GCable_Entry();
  return CAlloI(origin, i1, proto, i3, i4);
  GCable_Exit(1);
}

#endif /* sparc */

void RefNone(ref(Object) theObj)
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
    CallBetaEntry(LazyItem->Proto->TopMpart, LazyItem);
    
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
#ifdef crts
  BetaError(RefNoneErr,theObj);
#else
  BetaError(RefNoneErr, theObj);
#endif
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
#ifdef __powerc
  if (StandAlone) {
    ArgCount = 0;
    ArgVector = 0;
  } else {
    ArgCount = argc;
    ArgVector = argv;
  }
#else
  ArgCount = argc;
  ArgVector = argv;
#endif
}
#endif

#ifndef __GNUC__
#include "IOAalloc.h"
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
  BetaExit(1);
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

#if 0
long memcnt=0;
  memcnt+=size; \
  DEBUG_IOA(fprintf(output, "jmp-alloc: 0x%x total 0x%x\n",size, memcnt)); }
#define INFO_FREE(size) {\
  memcnt-=size; \
  DEBUG_IOA(fprintf(output, "jmp-free: 0x%x total 0x%x\n",size, memcnt)); }
#else
#define INFO_FREE(size)
#endif
#endif

/* Basis type in pool of jump buffers */
typedef struct jmpInfoElem {
  jmp_buf jumpBuffer; /* inline buffer */
  long * refTop;
} jmpInfoElem;

#ifdef JUMPSTACK

/* Implementation of a stack of jmpInfoElem. */
#define JmpStackSize 200

jmpInfoElem * jmp_buf_stack;
jmpInfoElem * jmp_buf_stack_top;

void initJmpPool()
{  
  jmp_buf_stack = (jmpInfoElem *)MALLOC(sizeof(jmpInfoElem)*JmpStackSize);
  jmp_buf_stack_top = jmp_buf_stack;
}

void reallocJmpList()     
{
  fprintf(output,"***ERROR: Jump Stack Overflow...\n"); fflush(output); BetaExit(1);
}

long GetJumpStackSize(void)
{ 
  return (((long)jmp_buf_stack_top-(long)jmp_buf_stack)/4)+1; /* longs on stack */
}
void PackAndFreeJmpBuf(long dest)
{ long long_size = ((long)jmp_buf_stack_top-(long)jmp_buf_stack)/4; /* longs on stack */
  if (!(long_size)) {
    jmp_buf_stack_top=jmp_buf_stack; /* reset */
	*(long*)dest=0; /* empty stack */
    return;
  }
  *(long*)dest=long_size; /* save long_size */
  dest+=4;
  memcpy((void*)dest, (void*)jmp_buf_stack, long_size*4);
  jmp_buf_stack_top=jmp_buf_stack; /* reset */
}
void UnPackAndAllocateJmpBuf(long src, long long_size)
{
  if (!long_size) {
    jmp_buf_stack_top=jmp_buf_stack; /* reset */
    return;
  }
  memcpy(jmp_buf_stack, (void*)src, long_size*4);
  jmp_buf_stack_top = (jmpInfoElem *) ((long)jmp_buf_stack+(long_size*4));
}

#endif

/* 1. allocate a jmp_buf to be used by longjmp;   */
/*    this is done below                          */
/* 2. save stacktop of ref. stack;                */
/* 3. save ref. for above info in a0[off]         */
/* 4. return jmp_buf                              */

void FreeJmpBuf(unsigned long addr, unsigned long off);

jmp_buf *GetJmpBuf(int addr, int off)
{
  jmpInfoElem *info;
  if (*(jmpInfoElem **)(addr+off)) /* is a buffer already allocated? */
     FreeJmpBuf(addr, off);        /* then free it */
  if ((long)jmp_buf_stack_top>=(long)jmp_buf_stack+(long)sizeof(jmpInfoElem)*JmpStackSize)
     reallocJmpList();
  info=jmp_buf_stack_top; /* info points into first free on Stack (this is a static address) */
  jmp_buf_stack_top++;
  info->refTop = RefSP;
  *(jmpInfoElem **)(addr+off) = info;
  return &(info->jumpBuffer);
}


void FreeJmpBuf(unsigned long addr, unsigned long off)
{
  jmpInfoElem *info = *(jmpInfoElem **)(addr+off);

  if (!info) return; /* no jump buffer here */
  
  /* free jmpInfoElem until info */
  while((jmp_buf_stack_top-1)!=info) {
    jmp_buf_stack_top--;
	if ((jmp_buf_stack_top==jmp_buf_stack) || !(jmp_buf_stack_top->jumpBuffer)) {
	   fprintf(output,"*** ERROR in FreeJmpBuf: jmp_buf_stack reached or jmp_buf_stack_top->jumpBuffer==0 (0x%x,0x%x,0x%x)\n",(unsigned)jmp_buf_stack,(unsigned)jmp_buf_stack_top,(unsigned)jmp_buf_stack_top->jumpBuffer);
	   BetaExit(1);
	}
  }
  if (info) {
    *(jmpInfoElem **)(addr+off) = 0;
	jmp_buf_stack_top--; /* info itself */
  } else {
    fprintf(output,"WARNING: attempt to clear jmp_buf 0 in 0x%x, off: %d\n",(unsigned)addr,(int)off);
  }
}

/* 1. get ref. to stateinfo from a1[off]  */
/* 2. restore ref stack top               */
/*    NOT done                            */
/* 3. restore a0 using a1                 */
/* 4. return saved jmp_buf                */
/* 5. jmp_buf should really be deallocaed */


jmp_buf *UseJmpBuf(int addr, int off)
{
  jmpInfoElem *info;
  
  a0 = (long)addr;                                
  info = *(jmpInfoElem **)(addr+off); 
  RefSP = info->refTop;                               
  FreeJmpBuf(addr, off);
  return &(info->jumpBuffer);
}
#endif /* crts */
