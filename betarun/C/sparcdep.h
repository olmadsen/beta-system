/*
 * BETA RUNTIME SYSTEM, Copyright (C) 1992-94 Mjolner Informatics Aps.
 * sparcdep.h
 * by Tommy Thorn
 */

/* SPARC Specifics, requires the use of GCC */

#ifndef _SPARC_H_
#define _SPARC_H_ 1

struct RegWin {
    long l0, l1, l2, l3, l4, l5, l6, l7;
    long i0, i1, i2, i3, i4, i5, fp, i7;
};

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

#define setret(newret) (retAddress = (long) (newret))
#define getret(saved) (saved = retAddress)

/* Various machine instructions */
#define RETL 0x81c3e008
#define MOV_O7_G1 0x8210000f
#define MK_CALL(p,f) \
  (*(long *)p = 0x40000000| (((unsigned) ((char*)f-(char*)p)) >> 2))
#define NOP 0x1000000

/* Defining this in the head of a module, together with a
   GCable_Entry and GCable_Exit in every routine in that module makes
   the activation record look like BETA, but *BEWARE*!:
   CHECK THAT THE ROUTINE DOESN'T USE ANY STACK, OR LOOSE!!
*/

#ifdef GCable_Module
register volatile void *GCreg0 __asm__("%o0");
register volatile void *GCreg1 __asm__("%o1");
register volatile void *GCreg2 __asm__("%o2");
register volatile void *GCreg3 __asm__("%o3");
register volatile void *GCreg4 __asm__("%o4");

#define GCable_Entry() \
  StackPointer = FramePointer-16; /* = 64 */ \
  GCreg0 = GCreg1 = GCreg2 = GCreg3 = GCreg4 = 0

#define GCable_Exit(n) /* nothing on the sparc */
#endif /* GCable_Module */

#define DeclReference1(type, name) type name
#define DeclReference2(type, name) type name

#define asmlabel(label, code) \
  __asm__(".text; .align 4; .global " #label "; " #label ": " code)

#define asmcomment(text) \
  __asm__("! " #text)


#define RETURN(v) return v

#define return_in_i1(value)                             \
    __asm__ volatile("":: "r" (value));                 \
    __asm__("ret; restore %0, 0, %%i1"::"r" (value));   \
    return value /* keep gcc happy */

#define return_in_i0(value)                             \
    __asm__ volatile("":: "r" (value));                 \
    __asm__("ret; restore %0, 0, %%i0"::"r" (value));   \
    return value /* keep gcc happy */

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
#define FetchAscii()
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

static __inline__ struct ProtoType *findProto(unsigned long *Ventry)
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
  return (struct ProtoType *)((instr1<<10) | (instr2 & 0x3ff));
}

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
  type C##name(struct Object *origin,                   \
               int i1,                                  \
               struct ProtoType *proto,                 \
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
 type C##name(struct Object *this, struct Component *comp,\
              int i2, int i3, int i4)

#else /* MT */

/* HandleIndexErr */
#define ParamThisComp(type, name)			\
  asmlabel(name,                                        \
	   "mov %i0,%o0; "				\
	   "mov %i1,%o1; "				\
	   CallAndSave_I0_I1_O0(name)                   \
	   );                                           \
 type C##name(struct Object *this, struct Component *comp)

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
 type C##name(struct Object *this, int i1, int i2, int i3, int i4)

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
 type C##name(struct Structure *struc, int i1, int i2, int i3, int i4)

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
 void C##name(struct Object *theObj,			\
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
 void C##name(struct Object *theObj,			\
	      int i1,					\
	      /*unsigned*/ int range,                   \
	      int i3,					\
	      int i4,					\
	      unsigned offset /* in bytes */)
	      
#else /* MT */

/* ExtRR, ExtVRx */
#define ParamObjOffRange(name)			        \
  asmlabel(name, 					\
	   CallAndSave_I0_I1_O0(name)                   \
           );                                           \
 void C##name(struct Object *theObj,			\
	      unsigned offset, /* in bytes */           \
	      /*unsigned*/ int range)

#endif /* MT */

#ifndef MT

/* CopyRR, CopyVR1, CopyVR2, CopyVR4, CopyVR8 */
#define ParamRepObjOff(name)                            \
void name(struct ValRep *theRep,                        \
	   struct Object *theObj,                       \
	   unsigned offset /* in ints */)

#else /* MT */

/* CopyRR, CopyVR1, CopyVR2, CopyVR4, CopyVR8 */
#define ParamRepObjOff(name)                            \
  asmlabel(name,                                        \
	   CallAndSave_I0_I1_O0(name)                   \
	   );                                           \
void C##name(struct ValRep *theRep,                     \
	     struct Object *theObj,                     \
	     unsigned offset /* in ints */)
     
#endif /* MT */

#ifndef MT

/* CopySVRI, CopySVRC, CopyVRI, CopyVRC */
#define ParamORepObjOff(name)                           \
void name(struct ObjectRep *theRep,                     \
	   struct Object *theObj,                       \
	   unsigned offset /* in ints */)

#else /* MT */

/* CopySVRI, CopySVRC, CopyVRI, CopyVRC */
#define ParamORepObjOff(name)                           \
  asmlabel(name,                                        \
	   CallAndSave_I0_I1_O0(name)                   \
	   );                                           \
void C##name(struct ObjectRep *theRep,                  \
	     struct Object *theObj,                     \
	     unsigned offset /* in ints */)
     
#endif /* MT */


#ifndef MT

/* CopySRR, CopySVR1, CopySVR2, CopySVR4, CopySVR8 */
#define ParamRepObjOffLowHigh(name)                     \
void name(struct ValRep *theRep,                        \
	   struct Object *theObj,                       \
	   unsigned offset, /* in ints */               \
           unsigned low,                                \
	   long high)

#else /* MT */

/* CopySRR, CopySVR1, CopySVR2, CopySVR4, CopySVR8 */
#define ParamRepObjOffLowHigh(name)                     \
  asmlabel(name,                                        \
	   CallAndSave_I0_I1_O0(name)                   \
	   );                                           \
void C##name(struct ValRep *theRep,                     \
	     struct Object *theObj,                     \
	     unsigned offset, /* in ints */             \
	     unsigned low,                              \
	     long high)
     
#endif /* MT */

#ifndef MT

/* CopySVRI, CopySVRC CopySRR, CopySVR1, CopySVR2, CopySVR4, CopySVR8 */
#define ParamORepObjOffLowHigh(name)                    \
void name(struct ObjectRep *theRep,                     \
	   struct Object *theObj,                       \
	   unsigned offset, /* in ints */               \
           unsigned low,                                \
	   long high)

#else /* MT */

/* CopySVRI, CopySVRC CopySRR, CopySVR1, CopySVR2, CopySVR4, CopySVR8 */
#define ParamORepObjOffLowHigh(name)                    \
  asmlabel(name,                                        \
	   CallAndSave_I0_I1_O0(name)                   \
	   );                                           \
void C##name(struct ObjectRep *theRep,                  \
	     struct Object *theObj,                     \
	     unsigned offset, /* in ints */             \
	     unsigned low,                              \
	     long high)
     
#endif /* MT */

#ifndef MT
/* AlloVRI, AlloVRC */
#define ParamObjOriginProtoOffRange(name)		\
  asmlabel(name, 					\
           "mov %i1, %o5; " /* proto */			\
	   "mov %i0, %o1; " /* theObj */		\
	   "ba "CPREF#name"; "				\
	   "clr %o4; ");				\
 void C##name(struct Object *origin,			\
	      struct Object *theObj,	                \
	      unsigned offset, /* in bytes */		\
	      int range,			        \
	      int i4,					\
	      struct ProtoType *proto)
#endif /* MT */

#ifdef MT
/* AlloDO */
#define ParamOriginSize(type, name)	                \
  asmlabel(name, 					\
	   "mov  %o0,%o2;"                              \
	   "mov  %i0,%o0;"                              \
	   CallAndSave_I1_O0(name)                      \
           );                                           \
  type C##name(struct Object *origin,                   \
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
  type C##name(struct Object *origin,                   \
               int i1,                                  \
               unsigned size)

#endif /* MT */


#ifdef MT
/* CopyCT */
#define ParamAscii(type, name)                          \
  asmlabel(name, 					\
           "mov %l0,%o2; "                              \
	   CallAndSave_I0_I1(name)                      \
           );                                           \
type C##name(int i0, int i1, unsigned char *ascii)
#else /* MT */
/* CopyCT */
#define ParamAscii(type, name)                          \
asmlabel(name,                                          \
	 "clr %o0; "                                    \
	 "clr %o1; "                                    \
	 "clr %o3; "                                    \
	 "clr %o4; "                                    \
	 "ba "CPREF#name"; "                            \
	 "mov %l0,%o2; "                                \
         );                                             \
type C##name(int i0, int i1, unsigned char *ascii)

#endif /* MT */

#ifdef MT
/* CopyT */
#define ParamItemAscii(type, name)                      \
asmlabel(name,                                          \
	 "mov %o0,%o5;"                                 \
         CallAndSave_I0_I1(name)                        \
         );                                             \
type C##name(int i0,                                    \
	     struct Item *theItem,                      \
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
	     struct Item *theItem,                      \
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
void C##name(ref(Object) dstQuaOrigin,                  \
	     struct Object **theCell,                   \
	     ref(ProtoType) dstQuaProto,                \
	     ref(Object) this)
#else /* MT */
/* Qua */
#define ParamProtoCellOriginThis(name)                  \
asmlabel(name,                                          \
	 "mov %i1,%o2; " /* dstQuaProto */              \
	 "ba "CPREF#name"; "                            \
	 "mov %i0,%o3; " /* This */                     \
         );                                             \
void C##name(ref(Object) dstQuaOrigin,                  \
	     struct Object **theCell,                   \
	     ref(ProtoType) dstQuaProto,                \
	     ref(Object) this)

#endif /* MT */

/* On the SPARC we need to skip the first instruction */
#define CallBetaEntry(entry,item)			\
    (* (void (*)()) ((long*)entry+1) )(item);

#ifdef MT
    
static __inline__ struct Object *
CallVEntry(void (*entry)(), struct Object *origin)
{
  register struct Object *newObject;
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
  __asm__ volatile ("" ::: 
		    "%i0","%i1","%i2","%i3","%i4","%i5",
		    "%l0","%l1","%l2","%l3","%l4","%l5","%l6","%l7");
  /* Move the object from %i1 (Ventry return) to newObject */
  __asm__ volatile ("mov %%i1,%0" : "=r" (newObject) );
  return newObject;
}
#endif

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
# define push(v) (StackPointer -= 2, StackPointer[16] = (long) v)
# define pop(v) ((v) = (__typeof__(v))StackPointer[16], StackPointer += 2)
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
extern void      CAlloRR (ref(Object), int, unsigned, int, int, int);
extern void      CAlloVR1(ref(Object), int, unsigned, int, int, int);
extern void      CAlloVR2(ref(Object), int, unsigned, int, int, int);
extern void      CAlloVR4(ref(Object), int, unsigned, int, int, int);
extern void      CAlloVR8(ref(Object), int, unsigned, int, int, int);
extern void      CAlloVRI(ref(Object), ref(Object), unsigned, int, int, ref(ProtoType));
extern void      CAlloVRC(ref(Object), ref(Object), unsigned, int, int, ref(ProtoType));

#endif /* _SPARC_H_ */
