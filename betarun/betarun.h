/*
 * betarun.h: interface from BETA compiler generated C-files 
 * to BETA Runtime system.
 *
 * Copyright (C) 1992-94 Mjolner Informatics Aps.
 * Written by Ole Lehrmann Madsen, Jacob Seligmann, and Peter Andersen.
 *
 * $Id: betarun.h,v 1.6 1994-10-21 10:28:14 beta Exp $
 *
 */


#ifndef _CRTS_H_
#define _CRTS_H_

struct ProtoType {
  short           	GCTabOff; 
  short           	OriginOff;
  long *       		GenPart;
  struct ProtoType *	Prefix;
  short           	Size;
  short           	FormOff;
  short          	FormInx;
  short           	AstRef;
  long            	(*CallBackRoutine)();
};

struct Object { 
  struct ProtoType *  	Proto;
  long            	GCAttr;
};

struct Item { 
  struct ProtoType *  	Proto;
  long            	GCAttr;
};

struct DopartObject { 
  struct ProtoType *  	Proto;
  long            	GCAttr;
  struct Object *     	Origin;
  long            	Size;
};

struct Component {
  struct ProtoType *  	Proto;
  long            	GCAttr;
  struct StackObject *	StackObj;
  struct Object *     	CallerObj;
  struct Component *  	CallerComp;
  long            	CallerLSC;
};

struct ValRep {
  struct ProtoType *  	Proto;
  long            	GCAttr;
  long            	LowBorder;
  long            	HighBorder;
};

struct RefRep {
  struct ProtoType *  	Proto;
  long            	GCAttr; 
  long            	LowBorder;
  long            	HighBorder;
};

struct Structure {
  struct ProtoType *  	Proto;
  long            	GCAttr;
  struct Object *     	iOrigin;
  struct ProtoType *  	iProto;
};

struct GCEntry {
  unsigned short 	StaticOff;
  short 		OrigOff;
  struct ProtoType * 	Proto;
};

struct PartObject {
  struct ProtoType * 	Proto;
  long 			OrigOff;
};

extern long *IOA;
extern long *IOATop;

extern long a0, a1, a2, a3, a4, a7; 
extern long leave;
extern void *CRTSjbp;

extern long * cIntStackPtr;
extern double * cFloatStackPtr;
extern long * RefSP;
extern long * oldSP;

extern void Trap(void);

#if defined(sun4) || defined(sun4s)
/* oldStackPtr is provided to the callback function by HandleCB which read the
   value of the old stack pointer when called. It is then necessary that the
   called BETA object is called with the parameters theObj, oldStackPtr, arg1,..
*/
#define CallBackPar1(dReg) (dReg = arg1)
#define CallBackPar2(dReg) (dReg = arg2)
#define CallBackPar3(dReg) (dReg = arg3)
#define CallBackPar4(dReg) (dReg = arg4)
#define CallBackPar5(dReg) (dReg = arg5)
#define CallBackPar6(dReg) (dReg = arg6)

#define CallBackParN(oldStackPtr, dReg, parNo)						\
  /* Ok, this is a hard one: oldStackPtr points to the previosly stack frame.		\
     This frame contains the parameters of the C-function calling back to BETA.		\
     On SPARC 23 words are used before the the parameters past the sixth (if any)	\
     are pushed on the stack. The first parameter on the stack is then the		\
     seventh parameter and so one.							\
   */											\
  dReg = *(long *)(oldStackPtr+(23+parNo-7)*4);

#define SaveCompState()

#define RestoreCompState()

#define SaveCurrSP()

#endif /* SUN4 & SUN4S */

#ifdef sgi

#define SaveCurrSP() \
  { register long * SP asm("$29"); \
    asm("":"=r" (SP)); /* fool gcc */ \
    oldSP = SP; \
   }

#define SaveCompState()				\
  asm(" addiu $29, $29, -108 ");		\
  asm(" sw $2, 4($29) ");			\
  asm(" sw $3, 8($29) ");			\
  asm(" sw $4, 12($29) ");			\
  asm(" sw $5, 16($29) ");			\
  asm(" sw $6, 20($29) ");			\
  asm(" sw $7, 24($29) ");			\
  asm(" sw $8, 28($29) ");			\
  asm(" sw $9, 32($29) ");			\
  asm(" sw $10, 36($29) ");			\
  asm(" sw $11, 40($29) ");			\
  asm(" sw $12, 44($29) ");			\
  asm(" sw $13, 48($29) ");			\
  asm(" sw $14, 52($29) ");			\
  asm(" sw $15, 56($29) ");			\
  asm(" sw $24, 60($29) ");			\
  asm(" sw $25, 64($29) ");			\
  asm(" sw $16, 68($29) ");			\
  asm(" sw $17, 72($29) ");			\
  asm(" sw $18, 76($29) ");			\
  asm(" sw $19, 80($29) ");			\
  asm(" sw $20, 84($29) ");			\
  asm(" sw $21, 88($29) ");			\
  asm(" sw $22, 92($29) ");			\
  asm(" sw $23, 96($29) ");			\
  asm(" sw $28, 100($29) ");			\
  asm(" sw $30, 104($29) ");			\
  asm(" sw $31, 108($29) ");                    \
  SaveCurrSP();

#define RestoreCompState()			\
  asm(" lw $2, 4($29) ");			\
  asm(" lw $3, 8($29) ");			\
  asm(" lw $4, 12($29) ");			\
  asm(" lw $5, 16($29) ");			\
  asm(" lw $6, 20($29) ");			\
  asm(" lw $7, 24($29) ");			\
  asm(" lw $8, 28($29) ");			\
  asm(" lw $9, 32($29) ");			\
  asm(" lw $10, 36($29) ");			\
  asm(" lw $11, 40($29) ");			\
  asm(" lw $12, 44($29) ");			\
  asm(" lw $13, 48($29) ");			\
  asm(" lw $14, 52($29) ");			\
  asm(" lw $15, 56($29) ");			\
  asm(" lw $24, 60($29) ");			\
  asm(" lw $25, 64($29) ");			\
  asm(" lw $16, 68($29) ");			\
  asm(" lw $17, 72($29) ");			\
  asm(" lw $18, 76($29) ");			\
  asm(" lw $19, 80($29) ");			\
  asm(" lw $20, 84($29) ");			\
  asm(" lw $21, 88($29) ");			\
  asm(" lw $22, 92($29) ");			\
  asm(" lw $23, 96($29) ");			\
  asm(" lw $28, 100($29) ");			\
  asm(" lw $30, 104($29) ");			\
  asm(" lw $31, 108($29) ");			\
  asm(" addiu $29, $29, 108 ");

#define CallBackPar1(dReg) (dReg = arg1)
#define CallBackPar2(dReg) (dReg = arg2)
#define CallBackPar3(dReg) (dReg = arg3)
#define CallBackPar4(dReg) (dReg = arg4)
#define CallBackPar5(dReg) (dReg = arg5)
#define CallBackPar6(dReg) (dReg = arg6)

#define CallBackParN(oldStackPtr, dReg, parNo)	\
    dReg = *(long *)(oldStackPtr+(parNo-1)*4);

#endif /* sgi */

#include <setjmp.h>
jmp_buf *UseJmpBuf(int,int);
jmp_buf *GetJmpBuf(int,int);
void FreeJmpBuf(int, int);

extern char 		GetByte(unsigned long a, int byteNo /* 0-3 */);
extern unsigned short 	GetShort(unsigned long a,int shortNo /* 0-1 */);
extern void 		PutBits(unsigned long a, unsigned long *b, int pos, int len);
extern unsigned long 	GetBits(unsigned long a, int pos, int len);
extern signed long 	GetSignedBits(unsigned long a, int pos, int len);
extern signed long 	SignExtByte(signed char a);
extern signed long 	SignExtWord(signed short a);

extern struct Component *	AlloC(struct Object *origin, struct ProtoType *proto);
extern struct DopartObject * 	AlloDO(unsigned size, struct Object *origin);
extern struct Item *		AlloI(struct Object *origin, struct ProtoType *proto);
extern struct Item *		AlloH(struct Object *origin, struct ProtoType *proto);
extern struct RefRep *		AlloRR(struct Object* theObj, unsigned offset, int range);
extern struct ValRep *		AlloVR1(struct Object* theObj, unsigned offset, int range);
extern struct ValRep *		AlloVR2(struct Object* theObj, unsigned offset, int range);
extern struct ValRep *		AlloVR4(struct Object* theObj, unsigned offset, int range);
extern struct ValRep *		AlloVR8(struct Object* theObj, unsigned offset, int range);
extern struct Component *	Att(struct Item *this, struct Component *comp);
extern void			AttBC(struct Item *this, struct Component *comp);
extern void 			CinitT(void);
extern char *			CpkVT(struct Object *currentObj, struct ValRep *theRep);
extern char *			CpkSVT(struct Object *currentObj, struct ValRep *theRep, unsigned low, long high);
extern void *			CopyCPP(struct Structure *theStruct, struct Object *theObj);
extern void 			ChkRA(struct Object **theObjHandle);
extern struct ValRep *		CopyCT(unsigned char *textPtr);
extern void 			CopyRR(struct ValRep *theRep, struct Object* theObj, unsigned offset);
extern void 			CopySRR(struct RefRep *theRep, struct Item *theItem, unsigned offset, unsigned low, unsigned high);
extern void 			CopySVR(struct RefRep *theRep, struct Item *theItem, unsigned offset, unsigned low, unsigned high);
extern void 			CopyT(char *asciz, struct Item *theItem, unsigned offset);
extern void 			CopyVR(struct ValRep *theRep, struct Object *theObj, unsigned offset);
extern void			ExtRR(struct Object *theObj, unsigned offset, long add);
extern void			ExtVR(struct Object *theObj, unsigned offset, long add);
extern void			HandleIndexErr(struct Item *this, struct Component *comp);
extern void 			MkTO(char *cText, struct Item *theItem, unsigned offset);
extern void			Return(void);
extern void			RefNone(struct Object *theObj);
extern void			SetArgValues(long argc, char *argv[]);
extern void			FailureExit(void);
extern void			NewRR(struct Object *theObj, long offset, long range);
extern void			NewVR(struct Object *theObj, long offset, long range);
extern void 			DoGC(void);
extern void 			Qua(struct ProtoType *dstQuaProto, struct Object **theCell, struct Object *dstQuaOrigin, struct Object *this);
extern struct Structure *	AlloS(struct Object *origin, struct ProtoType *proto);
extern struct Structure * 	ThisS(struct Object *this);
extern struct Structure * 	ObjS(struct Object *theObj);
extern struct Item *		AlloSI(struct Structure *struc);
extern struct Component *	AlloSC(struct Structure *struc);
extern long 			eqS(struct Structure *arg1, struct Structure *arg2);
extern long 			neS(struct Structure *arg1, struct Structure *arg2);
extern long 			leS(struct Structure *arg1, struct Structure *arg2);
extern long 			geS(struct Structure *arg1, struct Structure *arg2);
extern long 			gtS(struct Structure *arg1, struct Structure *arg2);
extern long 			ltS(struct Structure *arg1, struct Structure *arg2);
extern struct Component * 	Susp(struct Object *this);

#endif
