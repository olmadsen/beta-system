/*
 * BETA RUNTIME SYSTEM, Copyright (C) 1992-94 Mjolner Informatics Aps.
 * sparcdep.h
 * by Tommy Thorn
 */

/* SPARC Specifics, requires the use of GCC */

#ifndef _SPARC_H_
#define _SPARC_H_ 1

typedef struct _RegWin {
  long l0, l1, l2, l3, l4, l5, l6, l7;
  long i0, i1, i2, i3, i4, i5, fp, i7;
  long scratch[12];
} RegWin;

#ifdef sun4s
#define CPREF "C"
#define USCORE ""
#else
#define CPREF "_C"
#define USCORE "_"
#endif

/*
 * Stack manipulation - special for the SPARC
 *
 * Stack Layout:
 * 	sp	-> <space for l0 .. l7 registers>
 * 	sp+32	-> <space for i0 .. i7 registers>
 *	sp+64	-> <top of stack value>
 *
 * sp must be 8 byte aligned
 *
 * Instead of pushing a component block to the stack, it resides
 * in registers %l5 - %l7 of the coresponding reg.window
 */

#define setret(newret) (retAddress = (newret))
#define getret(saved) (saved = retAddress)

/* Various machine instructions */
#define RETL 0x81c3e008
#define MOV_O7_G1 0x8210000f
#define MK_CALL(p,f) \
  (*(long *)p = 0x40000000| (((unsigned) ((char*)f-(char*)p)) >> 2))
#define NOP 0x1000000

#define DeclReference1(type, name) type name
#define DeclReference2(type, name) type name

#define asmlabel(label, code) \
  __asm__(".text; .align 4; .global " #label "; " #label ": " code)

#define RETURN(v) return v

#define return_in_i1(value)                             \
    __asm__ volatile("":: "r" (value));                 \
    __asm__("ret; restore %0, 0, %%i1"::"r" (value));   

#define return_in_i0(value)                             \
    __asm__ volatile("":: "r" (value));                 \
    __asm__("ret; restore %0, 0, %%i0"::"r" (value));   

#define return_i1_in_o0()                               \
    __asm__("ret; restore %i1, 0, %o0");                

#define FetchOriginProto()
#define FetchObjOriginProtoOffRange()
#define FetchObjOffRange()
#define FetchThis()
#define FetchThisOffRange()
#define FetchThisComp()
#define FetchRepObjOff()
#define FetchRepObjOffLowHigh()
#define FetchORepObjOff()
#define FetchORepObjOffLowHigh()
#define FetchStruc()
#define FetchOriginSize()
#define FetchAsciz()
#define FetchItemAscii()
#define FetchParamProtoCellOriginThis()  

#define SaveVar(var) push(var)
#define RestoreVar(var) pop(var)

#ifdef MT
#define GetProto(s_obj) findProto((unsigned long *)((s_obj)->iProto))
#else
#define GetProto(s_obj) s_obj->iProto
#endif

#ifdef MT

static __inline__ ProtoType *findProto(unsigned long *Ventry)
     /* MUST match corresponding function in BetaRun.bet */
{ 
  /* A V-entry either has the form
   * 
   * 1. V-entry without G-part
   *    <V1FOO>:    sethi  %hi(AlloI1), %i5     # (LoadProtoAndAlloc3)
   *    <V1FOO+4>:  sethi  %hi(T1FOO), %i1      # (LoadProtoAndAlloc3)
   *    <V1FOO+8>:  jmp    %i5 + %lo(AlloI1)    # (LoadProtoAndAlloc3)
   *    <V1FOO+12>: or     %i1, %lo(T1FOO), %i1 # (LoadProtoAndAlloc3)
   *    ...
   * 
   * 2a.V-entry with G-part
   *    <V1FOO>:    or     %g0, RTOff, %l6      # (SaveReturn)
   *    <V1FOO+4>:  or     %g0, %o7, %l7        # (JsrT)
   *    <V1FOO+8>:  sethi  %hi(T1FOO), %i5      # (doCall)
   *    <V1FOO+12>: call   AlloI2               # (JsrT)
   *    <V1FOO+16>: or     %i5, %lo(T1FOO), %i5 # (doCall)
   *    ...
   * 
   * 2b.Like 2a, but with large RTOff (RTOff+4>4095):
   *    <V1FOO>:    sethi  %hi(RTOff), %l6      # (SaveReturn)
   *    <V1FOO+4>:  or     %l6, %lo(RTOff), %l6 # (SaveReturn)
   *    <V1FOO+8>:  or     %g0, %o7, %l7        # (JsrT)   
   *    <V1FOO+12>: sethi  %hi(T1FOO), %i5      # (doCall) 
   *    <V1FOO+16>: call   AlloI2               # (JsrT)   
   *    <V1FOO+20>: or     %i5, %lo(T1FOO), %i5 # (doCall) 
   *    ...
   */
  unsigned instr1, instr2;

  /* Load second instruction */
  instr1 = Ventry[1];
  
  /* Test bit 24: is 1 in SETHI and 0 in OR */
  if ((instr1>>24) & 1){
    /* case 1 */
    instr2 = Ventry[3];
  } else {
    /* Load third instruction */
    instr1 = Ventry[2];
    if ((instr1>>24) & 1){
      /* case 2a */
      instr2 = Ventry[4];
    } else {
      /* case 2b */
      instr1 = Ventry[3];
      instr2 = Ventry[5];
    }
  }
  /* Preg now contains SETHI instr. and RegTmp contains OR instr. */
  return (ProtoType *)((instr1<<10) | (instr2 & 0x3ff));
}

/* CallAndSave macros are used as wrappers for C-routines
 * called from BETA. These C routines may NOT call back
 * to BETA (e.g. via V-entry invocation) since they
 * store values in TSD.
 * For calling C-functions, which call back to BETA,
 * the CallAndPush macros must be used.
 */
#define CallAndSave_I0_I1_O0(name)                      \
           "mov %o7,%l7; "                              \
           "st %i0,[%g4+32]; " /* TSD->_CurrentObject */\
           "st %o0,[%g4+36]; " /* TSD->_Origin */       \
           "call "CPREF#name"; "                        \
           "st %i1,[%g4+40]; " /* TSD->_SavedCallO */   \
           "mov %l7,%o7; "                              \
           "ld [%g4+32],%i0; "                          \
           "ld [%g4+36],%o0; "                          \
           "ld [%g4+40],%i1; "                          \
           "st %g0,[%g4+32];  "                         \
           "st %g0,[%g4+36];  "                         \
           "retl; "                                     \
           "st %g0,[%g4+40];  "
#define CallAndSave_I1_O0(name)                         \
           "mov %o7,%l7; "                              \
           "st %o0,[%g4+36]; " /* TSD->_Origin */       \
           "call "CPREF#name"; "                        \
           "st %i1,[%g4+40]; " /* TSD->_SavedCallO */   \
           "mov %l7,%o7; "                              \
           "ld [%g4+36],%o0; "                          \
           "ld [%g4+40],%i1; "                          \
           "st %g0,[%g4+36];  "                         \
           "retl; "                                     \
           "st %g0,[%g4+40];  "
#define CallAndSave_I0_I1(name)                         \
           "mov %o7,%l7; "                              \
           "st %i0,[%g4+32]; " /* TSD->_CurrentObject */\
           "call "CPREF#name"; "                        \
           "st %i1,[%g4+40]; " /* TSD->_SavedCallO */   \
           "mov %l7,%o7; "                              \
           "ld [%g4+32],%i0; "                          \
           "ld [%g4+40],%i1; "                          \
           "st %g0,[%g4+32];  "                         \
           "retl; "                                     \
           "st %g0,[%g4+40];  "
#define CallAndPush_I0_I1(name)                         \
	   "ld [%g4+4],%l6; " /* TSD->_ActiveStack */   \
	   "add %g2,8,%l7; "  /* room for 2 refs? */    \
	   "cmp %l7,%g3; "                              \
	   "tge 16; "                                   \
           "mov %o7,%l7; "                              \
	   "add %g2,4,%g2; "                            \
           "st %i0,[%l6+%g2]; "                         \
	   "add %g2,4,%g2; "                            \
           "call "CPREF#name"; "                        \
           "st %i1,[%l6+%g2]; "                         \
           "mov %l7,%o7; "                              \
	   "ld [%g4+4],%l6; " /* TSD->_ActiveStack */   \
           "ld [%l6+%g2],%i1; "                         \
	   "sub %g2,4,%g2; "                            \
           "ld [%l6+%g2],%i0; "                         \
           "retl; "                                     \
	   "sub %g2,4,%g2; "

#endif /* MT */


#ifndef MT
/* AlloC, AlloI, AlloH, AlloS */
#define ParamOriginProto(type, name)			\
  asmlabel(name,					\
	   "clr %o1;"					\
	   "clr %o3;"					\
	   "clr %o4;"					\
	   "ba "CPREF#name";"				\
	   "mov %i1,%o2;"				\
	   );			                        \
  type C##name(Object *origin,                   \
               int i1,                                  \
               ProtoType *proto,                 \
               int i3,                                  \
               int i4)

#else /* MT */
/* AlloC, AlloI, AlloH, AlloS generated in BetaRun.bet */
#endif /* MT */


#ifndef MT

/* Att, AttBC, HandleIndexErr */
#define ParamThisComp(type, name)			\
  asmlabel(name, 					\
	   "clr %o3; "					\
	   "clr %o4; "					\
	   "mov %i0,%o0; "				\
	   "ba "CPREF#name"; "				\
	   "mov %i1,%o1");				\
 type C##name(Object *this, Component *comp,\
              int i2, int i3, int i4)

#else /* MT */

/* HandleIndexErr */
#define ParamThisComp(type, name)			\
  asmlabel(name,                                        \
	   "mov %i0,%o0; "				\
	   "mov %i1,%o1; "				\
	   CallAndSave_I0_I1_O0(name)                   \
	   );                                           \
 type C##name(Object *this, Component *comp)

#endif /* MT */


#ifndef MT

/* Susp */
#define ParamThis(type, name)	\
  asmlabel(name, 		\
	   "clr %o1; " 		\
	   "clr %o3; "		\
	   "clr %o4; "		\
	   "ba "CPREF#name"; "	\
	   "mov %i0,%o0; ");	\
 type C##name(Object *this, int i1, int i2, int i3, int i4)

#endif /* MT */

#ifndef MT

/* AlloSI, AlloSC */
#define ParamStruc(type, name)				\
  asmlabel(name,					\
	   "clr %o1;"					\
	   "clr %o3;"					\
	   "clr %o4;"					\
	   "ba "CPREF#name";"				\
	   "mov %i1,%o0;"  /* struc */			\
	   );			                        \
 type C##name(Structure *struc, int i1, int i2, int i3, int i4)

#endif /* MT */

#ifndef MT

/* AlloRR, AlloVR1, AlloVR2, AlloVR4, AlloVR8 */
#define ParamThisOffRange(name)		        	\
  asmlabel(name, 					\
           "mov %o1, %o5; " /* range */			\
           "mov %o0, %o2; " /* offset */		\
	   "mov %i0, %o0; " /* this */			\
           "clr %o1; "					\
           "clr %o3; "					\
	   "ba "CPREF#name"; "				\
	   "clr %o4; ");				\
 void C##name(Object *theObj,			\
	      int i1,					\
	      unsigned offset, /* in bytes */		\
	      int i3,					\
	      int i4,					\
	      /*unsigned*/ int range)
     
#endif /* MT */

#ifndef MT

/* ExtRR, ExtVRx, NewRR, NewVRx */
#define ParamObjOffRange(name)			        \
  asmlabel(name, 					\
           "mov %o1, %o5; " /* offset */		\
           "clr %o1; "					\
           "clr %o3; "					\
	   "ba "CPREF#name"; "				\
	   "clr %o4; ");				\
 void C##name(Object *theObj,			\
	      int i1,					\
	      /*unsigned*/ int range,                   \
	      int i3,					\
	      int i4,					\
	      unsigned offset /* in bytes */)
	      
#else /* MT */

/* ExtRR, ExtVRx, NewRR, NewVRx */
#define ParamObjOffRange(name)			        \
  asmlabel(name, 					\
	   CallAndPush_I0_I1(name)                      \
           );                                           \
 void C##name(Object *theObj,			\
	      unsigned offset, /* in bytes */           \
	      /*unsigned*/ int range)

#endif /* MT */

#ifndef MT

/* CopyRR, CopyVR1, CopyVR2, CopyVR4, CopyVR8 */
#define ParamRepObjOff(name)                            \
void name(SimpleRep *theRep,                            \
	  Object *theObj,                               \
	  unsigned offset /* in ints */)

#else /* MT */

/* CopyRR, CopyVR1, CopyVR2, CopyVR4, CopyVR8 */
#define ParamRepObjOff(name)                            \
  asmlabel(name,                                        \
	   CallAndSave_I0_I1_O0(name)                   \
	   );                                           \
void C##name(SimpleRep *theRep,                         \
	     Object *theObj,                            \
	     unsigned offset /* in ints */)
     
#endif /* MT */

#ifndef MT

/* CopySVRI, CopySVRC, CopyVRI, CopyVRC */
#define ParamORepObjOff(name)                           \
void name(ObjectRep *theRep,                     \
	   Object *theObj,                       \
	   unsigned offset /* in ints */)

#else /* MT */

/* CopySVRI, CopySVRC, CopyVRI, CopyVRC */
#define ParamORepObjOff(name)                           \
  asmlabel(name,                                        \
	   CallAndSave_I0_I1_O0(name)                   \
	   );                                           \
void C##name(ObjectRep *theRep,                  \
	     Object *theObj,                     \
	     unsigned offset /* in ints */)
     
#endif /* MT */


#ifndef MT

/* CopySRR, CopySVR1, CopySVR2, CopySVR4, CopySVR8 */
#define ParamRepObjOffLowHigh(name)                     \
void name(ValRep *theRep,                        \
	   Object *theObj,                       \
	   unsigned offset, /* in ints */               \
           unsigned low,                                \
	   long high)

#else /* MT */

/* CopySRR, CopySVR1, CopySVR2, CopySVR4, CopySVR8 */
#define ParamRepObjOffLowHigh(name)                     \
  asmlabel(name,                                        \
	   CallAndSave_I0_I1_O0(name)                   \
	   );                                           \
void C##name(ValRep *theRep,                     \
	     Object *theObj,                     \
	     unsigned offset, /* in ints */             \
	     unsigned low,                              \
	     long high)
     
#endif /* MT */

#ifndef MT

/* CopySVRI, CopySVRC CopySRR, CopySVR1, CopySVR2, CopySVR4, CopySVR8 */
#define ParamORepObjOffLowHigh(name)                    \
void name(ObjectRep *theRep,                     \
	   Object *theObj,                       \
	   unsigned offset, /* in ints */               \
           unsigned low,                                \
	   long high)

#else /* MT */

/* CopySVRI, CopySVRC CopySRR, CopySVR1, CopySVR2, CopySVR4, CopySVR8 */
#define ParamORepObjOffLowHigh(name)                    \
  asmlabel(name,                                        \
	   CallAndSave_I0_I1_O0(name)                   \
	   );                                           \
void C##name(ObjectRep *theRep,                  \
	     Object *theObj,                     \
	     unsigned offset, /* in ints */             \
	     unsigned low,                              \
	     long high)
     
#endif /* MT */

#ifdef MT
#define ParamObjOriginProtoOffRange(name)		\
  asmlabel(name, 					\
           "mov %i1, %o5; " /* proto */			\
	   "mov %i0, %o1; " /* theObj */		\
	   CallAndPush_I0_I1(name)                      \
	   );		                 		\
 void C##name(Object *origin,			\
	      Object *theObj,	                \
	      unsigned offset, /* in bytes */		\
	      int range,			        \
	      int i4,					\
	      ProtoType *proto)
#else
/* AlloVRI, AlloVRC */
#define ParamObjOriginProtoOffRange(name)		\
  asmlabel(name, 					\
           "mov %i1, %o5; " /* proto */			\
	   "mov %i0, %o1; " /* theObj */		\
	   "ba "CPREF#name"; "				\
	   "clr %o4; ");				\
 void C##name(Object *origin,			\
	      Object *theObj,	                \
	      unsigned offset, /* in bytes */		\
	      int range,			        \
	      int i4,					\
	      ProtoType *proto)
#endif /* MT */

#ifdef MT
/* AlloDO */
#define ParamOriginSize(type, name)	                \
  asmlabel(name, 					\
	   "mov  %o0,%o2;"                              \
	   "mov  %i0,%o0;"                              \
	   CallAndSave_I1_O0(name)                      \
           );                                           \
  type C##name(Object *origin,                   \
               int i1,                                  \
               unsigned size)
#else /* MT */
/* AlloDO */
#define ParamOriginSize(type, name)	                \
  asmlabel(name, 					\
	   "mov  %o0,%o2;"                              \
	   "mov  %i0,%o0;"                              \
	   "clr  %o1;"                                  \
	   "clr  %o3;"                                  \
	   "ba "CPREF#name"; "				\
	   "clr  %o4; ");				\
  type C##name(Object *origin,                   \
               int i1,                                  \
               unsigned size)

#endif /* MT */


#ifdef MT
/* CopyCT */
#define ParamAsciz(type, name)                          \
  asmlabel(name, 					\
           "mov %l0,%o2; "                              \
	   CallAndSave_I0_I1(name)                      \
           );                                           \
type C##name(int i0, int i1, unsigned char *asciz)
#else /* MT */
/* CopyCT */
#define ParamAsciz(type, name)                          \
asmlabel(name,                                          \
	 "clr %o0; "                                    \
	 "clr %o1; "                                    \
	 "clr %o3; "                                    \
	 "clr %o4; "                                    \
	 "ba "CPREF#name"; "                            \
	 "mov %l0,%o2; "                                \
         );                                             \
type C##name(int i0, int i1, unsigned char *asciz)

#endif /* MT */

#ifdef MT
/* CopyT */
#define ParamItemAscii(type, name)                      \
asmlabel(name,                                          \
	 "mov %o0,%o5;"                                 \
         CallAndSave_I0_I1(name)                        \
         );                                             \
type C##name(int i0,                                    \
	     Item *theItem,                      \
	     unsigned offset, /* i ints */              \
	     int i3,                                    \
	     int i4,                                    \
	     char *ascii)
#else /* MT */
/* CopyT */
#define ParamItemAscii(type, name)                      \
asmlabel(name,                                          \
	 "mov %o0,%o5;"                                 \
         "clr %o0;"                                     \
	 "clr %o3;"                                     \
	 "ba "CPREF#name"; "                            \
         "clr %o4;"                                     \
         );                                             \
type C##name(int i0,                                    \
	     Item *theItem,                      \
	     unsigned offset, /* i ints */              \
	     int i3,                                    \
	     int i4,                                    \
	     char *ascii)

#endif /* MT */

#ifdef MT
/* Qua */
#define ParamProtoCellOriginThis(name)                  \
asmlabel(name,                                          \
	 "mov %i1,%o2; " /* dstQuaProto */              \
	 "mov %i0,%o3; " /* This */                     \
         CallAndSave_I0_I1_O0(name)                     \
         );                                             \
void C##name(Object * dstQuaOrigin,                  \
	     Object **theCell,                   \
	     ProtoType * dstQuaProto,                \
	     Object * this)
#else /* MT */
/* Qua */
#define ParamProtoCellOriginThis(name)                  \
asmlabel(name,                                          \
	 "mov %i1,%o2; " /* dstQuaProto */              \
	 "ba "CPREF#name"; "                            \
	 "mov %i0,%o3; " /* This */                     \
         );                                             \
void C##name(Object * dstQuaOrigin,                  \
	     Object **theCell,                   \
	     ProtoType * dstQuaProto,                \
	     Object * this)

#endif /* MT */

/* On the SPARC we need to skip the first instruction.
 * And we clear the other outgoing registers %o1-%o4, since these will
 * become %i registers in the BETA frame, i.e. GC roots.
 * NOT needed: Each G entry clears %i-regs itself.
 */
#define CallBetaEntry(entry,item)			\
    (* (void (*)()) ((long*)entry+1) )(item/*,0,0,0,0*/);

#ifdef MT
    
#define BETA_CLOBBER()                                               \
  __asm__ volatile ("" :::                                           \
		    "%i0","%i1","%i2","%i3","%i4","%i5",             \
		    "%l0","%l1","%l2","%l3","%l4","%l5","%l6","%l7")

static __inline__ Object *
CallVEntry(void (*entry)(), Object *origin)
{
  register Object *newObject;
  /* Clear current object before calling V-entry.
   * FIXME: should set a correct current object
   */
  __asm__ volatile ("clr %i0");
  __asm__ volatile ("" ::: "%i0");
  /* Call V-entry with origin as parameter (%o0) */
  (*entry)(origin);
  /* Tell gcc, that a lot of registers may have been destroyed
   * by the V-entry 
   */
  BETA_CLOBBER();
  /* Move the object from %i1 (Ventry return) to newObject */
  __asm__ volatile ("mov %%i1,%0" : "=r" (newObject) );
  return newObject;
}

static __inline__ Component *
CallAlloC(void *Ventry, Object *origin)
{
  register Component *newComp;
  extern void AlloC(Object *origin);

  /* Clear current object before calling AlloC.
   * FIXME: should set a correct current object
   */
  __asm__ volatile ("clr %i0");
  __asm__ volatile ("" ::: "%i0");
  /* Move the Ventry to %i1 (AlloC argument) */
  __asm__ volatile ("mov %0,%%i1" : /* no outs */: "r" (Ventry) : "%i1");
  /* Call AlloC */
  AlloC(origin);
  /* Tell gcc, that a lot of registers may have been destroyed
   * by AlloC
   */
  BETA_CLOBBER();
  /* Move the comp from %i1 (AlloC return) to newComp */
  __asm__ volatile ("mov %%i1,%0" : "=r" (newComp) );
  return newComp;
}

#endif /* MT */

#ifdef RTVALHALLA
#define ValhallaCallBetaEntry(entry,item,event)		\
    ValhallaOnProcessStop ((long*)entry+2,0,0,0,event); \
    (* (void (*)()) ((long*)entry+1) )(item);
#endif

#ifdef MT
# define push(v) \
{\
   RefTopOffReg++;\
   if (DataTopOffReg<RefTopOffReg) __asm__("ta 16");\
   *(long*)((long)ActiveStack + (long)RefTopOffReg) = (long)v;\
}

# define pop(v) \
{\
   (v) = *((__typeof__(v)*)((long)ActiveStack+(long)RefTopOffReg));\
   RefTopOffReg--;\
}
#else
# define push(v) (StackPointer -= 2, StackPointer[28] = (long) v)
# define pop(v) ((v) = (__typeof__(v))StackPointer[28], StackPointer += 2)
#endif

#define Protect(var, code)				\
  push(var);						\
  { code; }						\
  pop(var);						\

#define Protect2(v1, v2, code)				\
  push(v1); push(v2);					\
  { code; }						\
  pop(v2); pop(v1);					\

#ifndef MT
static __inline__ void USE()
{ int x;
  x=(int)IOA;
  x=(int)IOATopOff;
  x=(int)StackPointer;
  x=(int)FramePointer;
  x=(int)retAddress;
}
#endif

/* Routines called from others */
extern void      CAlloRR (Object *, int, unsigned, int, int, int);
extern void      CAlloVR1(Object *, int, unsigned, int, int, int);
extern void      CAlloVR2(Object *, int, unsigned, int, int, int);
extern void      CAlloVR4(Object *, int, unsigned, int, int, int);
extern void      CAlloVR8(Object *, int, unsigned, int, int, int);
extern void      CAlloVRI(Object *, Object *, unsigned, int, int, ProtoType *);
extern void      CAlloVRC(Object *, Object *, unsigned, int, int, ProtoType *);

#endif /* _SPARC_H_ */
