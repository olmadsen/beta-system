/*
 * crst.h: interface from BETA compiler generated C-files 
 * to BETA Runtime system.
 *
 * Copyright (C) 1992-94 Mjolner Informatics Aps.
 * Written by Ole Lehrmann Madsen, Jacob Seligmann, and Peter Andersen.
 *
 * $Id: crts.h,v 1.1 1994-04-11 14:27:53 beta Exp $
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

struct structure {
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

extern long *a0,*a1,*a2,*a3,*a4,*a7;
extern long leave;

extern void pushAdr();
extern long *popAdr();
extern long CallBackPar(long off);
extern void Trap();
extern long GetByte(long a,long byteNo);
extern long GetShort(long a,long shortNo);
extern long PutBits(long a,long b,long c,long d);
extern long GetBits(long a,long b,long c);
extern long GetSignedBits(long a,long b,long c);

extern struct Component *	AlloC(struct Object *origin, struct ProtoType *proto);
extern struct DopartObject * 	AlloDO(unsigned size, struct Object *origin);
extern struct Item *		AlloI(struct Object *origin, struct ProtoType *proto);
extern struct Item *		AlloH(struct Object *origin, struct ProtoType *proto);
extern struct RefRep *		AlloRR(struct Object* theObj, unsigned offset, unsigned range);
extern struct RefRep *		AlloVR1(struct Object* theObj, unsigned offset, unsigned range);
extern struct RefRep *		AlloVR2(struct Object* theObj, unsigned offset, unsigned range);
extern struct RefRep *		AlloVR4(struct Object* theObj, unsigned offset, unsigned range);
extern struct RefRep *		AlloVR8(struct Object* theObj, unsigned offset, unsigned range);
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
extern void 			Qua(struct ProtoType *dstQuaProto, struct Object **theCell, struct Object *dstQuaOrigin, struct Object *this)
extern struct Structure *	AlloS(struct Object *origin, struct ProtoType *proto);
extern struct Structure * 	ThisS(struct Object *this);
extern struct Structure * 	ObjS(struct Object *theObj);
extern struct Item *		AlloSI(struct Structure *struc);
extern struct Component *	AlloSC(struct Structure *struc);
extern long 			EqS(struct Structure *arg1, struct Structure *arg2);
extern long 			NeS(struct Structure *arg1, struct Structure *arg2);
extern long 			LeS(struct Structure *arg1, struct Structure *arg2);
extern long 			GeS(struct Structure *arg1, struct Structure *arg2);
extern long 			GtS(struct Structure *arg1, struct Structure *arg2);
extern long 			LtS(struct Structure *arg1, struct Structure *arg2);
extern struct Component * 	Susp(struct Object *this);

#endif
