/*
 * BETA RUNTIME SYSTEM, Copyright (C) 1992-94 Mjolner Informatics Aps.
 * crtsdep.h
 * by Ole Lehrmann Madsen, Peter Andersen, Kim Jensen M¿ller, and Peter Ryberg Jensen
 * $Id: crtsdep.h,v 1.17 1996-10-01 12:14:30 beta Exp $
 */

#define JUMPSTACK 1

#define ParamOriginProto(retType,name)			 \
  retType name(struct Object *origin, struct ProtoType *proto)
#define ParamThisComp(retType,name)                            \
  retType name(struct Object *this, struct Component *comp)
#define ParamThisOffRange(retType, name)			 \
  retType name(struct Object *theObj,			         \
	 unsigned offset, /* in bytes */		 \
	 int range				         \
	 )
#define ParamObjOriginProtoOffRange(name)			\
 void name(struct Object *origin,			\
	      struct Object *theObj,	                \
	      unsigned offset, /* in bytes */		\
	      struct ProtoType *proto,			\
	      int range)

#define ParamStruc(retType, name)                              \
  retType name(struct Structure *struc)
#define ParamThis(retType,name)                                \
  retType name(struct Object *this)

#define RETURN(v) return v
#define GCable_Entry()
#define GCable_Exit(v)

extern long a1;
#define CallBetaEntry(entry,item)	                \
    a1=(long)(item); (* (void (*)()) (entry))()

/* extern void pushAdr(long *a);
   extern long *popAdr();*/

#define pushAdr(a) \
  *RefSP++ = (long)a

#define popAdr() \
  (long *) *(--RefSP)

#define push(v) *RefSP++ = (long) v
#define pop(v) v = (void *) *(--RefSP)

#define SaveVar(var) push(var)
#define RestoreVar(var) pop(var)

#define Protect(var, code)				\
  push(var);						\
  { code; }						\
  pop(var);

#define Protect2(v1, v2, code)				\
  push(v1); push(v2);					\
  { code; }						\
  pop(v2); pop(v1);

#define PushGCRegs()				\
  *RefSP++=a0;					\
  *RefSP++=a1;					\
  *RefSP++=a2;					\
  *RefSP++=a3;					\
  *RefSP++=a4;

#define PopGCRegs()			        \
  a4 = *(--RefSP);				\
  a3 = *(--RefSP);				\
  a2 = *(--RefSP);				\
  a1 = *(--RefSP);				\
  a0 = *(--RefSP);

#define DeclReference1(type, name) type name
#define DeclReference2(type, name) type name

#define FetchOriginProto()
#define FetchStruc()
#define FetchThis()
#define FetchThisComp()

/* Points to top of cStack. Used for nested external calls */
extern long *cIntStackPtr;
extern double *cFloatStackPtr;

extern struct RefRep *		AlloRR(struct Object* theObj, 
				       unsigned offset, 
				       int range);
extern struct ValRep *		AlloVR1(struct Object* theObj, 
					unsigned offset, 
					int range);
extern struct ValRep *		AlloVR2(struct Object* theObj, 
					unsigned offset, 
					int range);
extern struct ValRep *		AlloVR4(struct Object* theObj, 
					unsigned offset,
					int range);
extern struct ValRep *		AlloVR8(struct Object* theObj, 
					unsigned offset, 
					int range);
extern void AlloVRI(struct Object *iOrigin,
		    struct Object *theObj,
		    unsigned offset, /* in bytes */
		    struct ProtoType *proto,
		    int range);
extern void AlloVRC(struct Object *iOrigin,
		     struct Object *theObj,
		     unsigned offset, /* in bytes */
		     struct ProtoType *proto,
		     int range);
extern void CopyT(char *asciz, 
		  struct Item *theItem,
		  unsigned offset);

extern struct StackObject *     AlloSO(unsigned size);

#ifdef JUMPSTACK
extern void initJmpPool(void);
#endif

/************************************************************************************/
/*                           Machine dependent makros                               */
/************************************************************************************/

#if defined(SUN4) || defined(SUN4S)

extern long * oldSP;

/* For callbacks in Callback.c */

#define MK_CALL(f) \
  CBFATop->code[0] = 0x9de3bf90; /* save %sp, -112, %sp */ \
  CBFATop->code[1] = 0x11000000 | (((unsigned) &oldSP) & 0xfffffc00)>>10; /* sethi %hi(oldSP), %o0 */ \
  CBFATop->code[2] = 0xfc222000 | (((unsigned) &oldSP) & 0x3ff); /* st %fp, [%o0+lo(oldSP) */\
  CBFATop->code[3] = 0x90100018; /* mov %i0, %o0 */ \
  CBFATop->code[4] = 0x92100019; /* mov %i1, %o1 */ \
  CBFATop->code[5] = 0x9410001a; /* mov %i2, %2 */ \
  CBFATop->code[6] = 0x9610001b; /* mov %i3, %o3 */ \
  CBFATop->code[7] = 0x9810001c; /* mov %i4, %o4 */ \
  CBFATop->code[8] = 0x40000000 | (((unsigned) ((char*)f-(char*)&(CBFATop->code[8]))) >> 2); /* call HandleCB */\
  CBFATop->code[9] = 0x9a10001d; /* mov %i5, %o5 */ \
  CBFATop->code[10] = 0x81c7e008; /* ret */ \
  CBFATop->code[11] = 0x91e80008; /* restore %go, %o0, %o0 */


#define NUMBER_TO_STRUCT (9*4)

#define FlushCache	 					\
  __asm__("iflush %0"::"r" (&CBFATop->code[0]));		\
  __asm__("iflush %0"::"r" (&CBFATop->code[1]));		\
  __asm__("iflush %0"::"r" (&CBFATop->code[2]));		\
  __asm__("iflush %0"::"r" (&CBFATop->code[3]));		\
  __asm__("iflush %0"::"r" (&CBFATop->code[4]));		\
  __asm__("iflush %0"::"r" (&CBFATop->code[5]));		\
  __asm__("iflush %0"::"r" (&CBFATop->code[6]));		\
  __asm__("iflush %0"::"r" (&CBFATop->code[7]));		\
  __asm__("iflush %0"::"r" (&CBFATop->code[8]));		\
  __asm__("iflush %0"::"r" (&CBFATop->code[9]));		\
  __asm__("iflush %0"::"r" (&CBFATop->code[10]));		\
  __asm__("iflush %0"::"r" (&CBFATop->code[11]));		\

/* Used for components in Attach.c and Suspend.c */
register long * StackPointer asm("%sp");
register long * FramePointer asm("%fp");
register long   retAddress   asm("%i7");

#define setret(newret) (retAddress = (long) (newret))
#define setret_Susp(saved) (retAddress = (long) (saved))
#define setret_Att(newret) (retAddress = (long) (newret))
#define getret(saved) (saved = retAddress)
#define getret_Susp(saved) (saved = retAddress)
#define getret_CB(saved) (saved = retAddress)
 
#define SetStackPointer(newSP) (StackPointer = newSP)
#define SetFramePointer(newFP) (FramePointer = newFP)

#define GetStackPointer(SP) (SP=StackPointer)
#define GetFramePointer(FP) (FP=FramePointer)
#define GetFramePointer_Att(FP) (FP=FramePointer)

#define SaveCompState_sparc()\
  asm("ta 3");

#endif /* SUN4 */


#ifdef SGI

#include <sys/cachectl.h>

extern long * oldSP;

/* For callbacks in Callback.c */

#define MK_CALL(f)\
  CBFATop->code[0] = 0x27bdffc8; /* addiu $sp,$sp,-56 */ \
  CBFATop->code[1] = 0xafbc0018; /* sw $gp,24($sp) */ \
  CBFATop->code[2] = 0xafbf0030; /* sw $ra,48($sp) */ \
  CBFATop->code[3] = 0xafb7002c; /* sw $s7,44($sp) */ \
  CBFATop->code[4] = 0xafbc0028; /* sw $gp,40($sp) */ \
  CBFATop->code[5] = 0xafa40038; /* sw $ao,56($sp) */ \
  CBFATop->code[6] = 0xafa5003c; /* sw $a1,60($sp) */ \
  CBFATop->code[7] = 0xafa60040; /* sw $a2,64($sp) */ \
  CBFATop->code[8] = 0xafa70044; /* sw $a3,72($sp) */ \
  CBFATop->code[9] = 0x3c170000 | (((unsigned) &oldSP & 0xffff0000)>>16); /* lui $s7,hi(oldSP)*/\
  CBFATop->code[10] = 0x36f70000 | ((unsigned) &oldSP & 0xffff); /* ori $s7,$s7,lo(oldSP) */ \
  CBFATop->code[11] = 0x03a02021; /* move $a0,$sp */ \
  CBFATop->code[12] = 0x24840038; /* addiu $a0,$a0,56 */ \
  CBFATop->code[13] = 0xaee40000; /* sw $a0,0($s7) */ \
  CBFATop->code[14] = 0x8fa20048; /* lw $v0,72($sp) */ \
  CBFATop->code[15] = 0x00000000; /* nop */ \
  CBFATop->code[16] = 0xafa20010; /* sw $v0,16($sp) */ \
  CBFATop->code[17] = 0x8fa2004c; /* lw $v0,76($sp) */ \
  CBFATop->code[18] = 0x00000000; /* nop */ \
  CBFATop->code[19] = 0xafa20014; /* sw $v0,20($sp) */ \
  CBFATop->code[20] = 0x03a0b821; /* move $s7,$sp */ \
  CBFATop->code[21] = 0x3c190000 | (((unsigned)f & 0xffff0000)>>16); /* lui $t9,hi(HandleCB) */ \
  CBFATop->code[22] = 0x37390000 | ((unsigned)f & 0xffff); /* ori $t9,$t9,lo(HnadleCB) */ \
  CBFATop->code[23] = 0x8fa40038; /* lw a0, 56($sp) */ \
  CBFATop->code[24] = 0x00000000; /* nop */ \
  CBFATop->code[25] = 0x0320f809; /* jarl $t9 */ \
  CBFATop->code[26] = 0x00000000; /* nop */ \
  CBFATop->code[27] = 0x8efc0018; /* lw $gp,24($s7) */ \
  CBFATop->code[28] = 0x00000000; /* nop */ \
  CBFATop->code[29] = 0x02e0e821; /* move $sp,$s7 */ \
  CBFATop->code[30] = 0x8fbf0030; /* lw $ra,48($sp) */ \
  CBFATop->code[31] = 0x00000000; /* nop */ \
  CBFATop->code[32] = 0x8fb7002c; /* lw $s7,44($sp) */ \
  CBFATop->code[33] = 0x00000000; /* nop */ \
  CBFATop->code[34] = 0x27bd0038; /* addiu $sp,$sp,56 */ \
  CBFATop->code[35] = 0x03e00008; /* jr $ra */ \
  CBFATop->code[36] = 0x00000000; /* nop */

#define NUMBER_TO_STRUCT (28*4)

/* _flush_cache(addr, number_of_bytes_to_flush,cache)
   where cache is either DCACHE, ICACHE or BCACHE (both caches)
*/
#define FlushCache \
  _flush_cache((char *)(&CBFATop->code[0]), 36*4, DCACHE)

/* Used for components in Attach.c and Suspend.c */

#define setret(newret) (*(oldSP-2) = newret)
#define setret_Susp(newret) (*(oldSP-1) = newret)
#if 0
#define setret_Att(newret) \
  asm("sw %0, 64($29)"::"r" (newret));
#endif

#define getret(saved) (saved = *(oldSP-2))
#define getret_Susp(saved) (saved = *(oldSP-1))
#if 0
#define getret_Att(saved) \
  asm("lw %0, 64($29)":"=r" (saved));
#endif

#define getret_CB(saved) \
  asm("move %0, $31":"=r" (saved));

#define SetStackPointer(newSP) \
  asm("move $sp, %0"::"r" (newSP)); \
  asm("lw $gp,16($sp)");

#define GetStackPointer(SP) \
  asm("move %0, $sp":"=r" (SP));

#define SetFramePointer(newFP) (oldSP = newFP)
#define GetFramePointer(FP) (FP = oldSP)

#define GetFramePointer_Att(FP) \
  GetStackPointer(FP); \
  FP=FP+72/4;

#define SaveCompState_sparc()

#endif /* SGI */

#ifdef MAC

// this must be hacked to PowerPC code!!!!!!!!
 
extern long * oldSP;

/* For callbacks in Callback.c */

/* PowerPC mess: */

#define MK_CALL(f)                              \
{ unsigned long * code;                         \
  unsigned long * func = (unsigned long *) f;   \
  code = (unsigned long *) NewPtr(4*18);        \
*(code++) = (unsigned long) CBFATop->theStruct; \
CBFATop->code[0] = (unsigned long*) code;        \
CBFATop->code[1] = (unsigned long*) *(func+1); /* TOC */    \
*(code++) = 0x7C0802A6;                                          /* mflr      r0;  		*/ \
*(code++) = 0xBF41FFE8;                                          /* stmw      r26,-0x0018(SP) 	*/ \
*(code++) = 0x90010008;                                          /* stw       r0,0x0008(SP) 	*/ \
*(code++) = 0x9421FFB0;                                          /* stwu      SP,-0x0050(SP) 	*/ \
*(code++) = 0x3F400000 | (((unsigned) &oldSP & 0xffff0000)>>16); /* lis       r26,1 		*/ \
*(code++) = 0x635A0000 | ((unsigned) &oldSP & 0xffff);           /* ori       r26,r26,0xFFFF 	*/ \
*(code++) = 0x903A0000;                                          /* stw       SP,0x0000(r26) 	*/ \
*(code++) = 0x3F400000 | ((*func & 0xffff0000)>>16); 		 /* lis       r26,1 		*/ \
*(code++) = 0x635A0000 |  (*func & 0xffff);           		 /* ori       r26,r26,0xFFFF 	*/ \
*(code++) = 0x7F4803A6;                                          /* mtlr      r26;  		*/ \
*(code++) = 0x4E800021;                                          /* blrl 		   	*/ \
*(code++) = 0x60000000;                                          /* nop 	    		*/ \
*(code++) = 0x80010058;                                          /* lwz       r0,0x0058(SP) 	*/ \
*(code++) = 0x30210050;                                          /* addic     SP,SP,80 		*/ \
*(code++) = 0x7C0803A6;                                          /* mtlr      r0   	        */ \
*(code++) = 0xBB41FFE8;                                          /* lmw       r26,-0x0018(SP) 	*/ \
*(code++) = 0x4E800020;                                          /* blr       		     	*/ \
}

/* PowerPC UniversalProcPointer Call */

#define MK_UNIV_CALL(f,univProcInfo)          \
{ unsigned long * code;                       \
  unsigned long * func = (unsigned long *) f; \
  UniversalProcPtr myCallBack;                \
  code = NewPtr(4*18);                        \
*(code++) = CBFATop->theStruct;               \
myCallBack = NewRoutineDescriptor((ProcPtr)code, univProcInfo, GetCurrentISA()); \
CBFATop->code[0] = myCallBack;                \
CBFATop->code[1] = *(func+1); /* TOC ?? */    \
*(code++) = 0x7C0802A6;                                          /* mflr      r0;  		*/ \
*(code++) = 0xBF41FFE8;                                          /* stmw      r26,-0x0018(SP) 	*/ \
*(code++) = 0x90010008;                                          /* stw       r0,0x0008(SP) 	*/ \
*(code++) = 0x9421FFB0;                                          /* stwu      SP,-0x0050(SP) 	*/ \
*(code++) = 0x3F400000 | (((unsigned) &oldSP & 0xffff0000)>>16); /* lis       r26,1 	        */ \
*(code++) = 0x635A0000 | ((unsigned) &oldSP & 0xffff);           /* ori       r26,r26,0xFFFF 	*/ \
*(code++) = 0x903A0000;                                          /* stw       SP,0x0000(r26) 	*/ \
*(code++) = 0x3F400000 | ((*func & 0xffff0000)>>16); 		 /* lis       r26,1 		*/ \
*(code++) = 0x635A0000 |  (*func & 0xffff);           		 /* ori       r26,r26,0xFFFF 	*/ \
*(code++) = 0x7F4803A6;                                          /* mtlr      r26;  		*/ \
*(code++) = 0x4E800021;                                          /* blrl 		     	*/ \
*(code++) = 0x60000000;                                          /* nop 	      		*/ \
*(code++) = 0x80010058;                                          /* lwz       r0,0x0058(SP) 	*/ \
*(code++) = 0x30210050;                                          /* addic     SP,SP,80 		*/ \
*(code++) = 0x7C0803A6;                                          /* mtlr      r0   		*/ \
*(code++) = 0xBB41FFE8;                                          /* lmw       r26,-0x0018(SP) 	*/ \
*(code++) = 0x4E800020;                                          /* blr 		        */ \
}

#define NUMBER_TO_STRUCT (12*4)

/* flush the data cache */
#define FlushCache

/* Used for components in Attach.c and Suspend.c */

#define setret(newret) (*(oldSP+2) = newret)
#define setret_Susp(newret) (*(oldSP+2) = newret)

#define getret(saved) (saved = (long*)*(oldSP+2))
#define getret_Susp(saved) (saved = *(oldSP+2))

#define getret_CB(saved) (saved = *(oldSP+2))

extern PPC_SetStackPointer(long*);
#define SetStackPointer(newSP) PPC_SetStackPointer(newSP)

extern long * PPC_GetStackPointer();
#define GetStackPointer(SP) (SP=PPC_GetStackPointer())

#define SetFramePointer(newFP) (oldSP = newFP)
#define GetFramePointer(FP) (FP = oldSP)

#define GetFramePointer_Att(FP) (FP = (SP + 120/4))

#define SaveCompState_sparc()

#define HandlePCB_Frame_Size 72

#endif /* MAC */
