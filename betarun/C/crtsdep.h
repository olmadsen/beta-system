/*
 * BETA RUNTIME SYSTEM, Copyright (C) 1992-94 Mjolner Informatics Aps.
 * crtsdep.h
 * by Peter Ryberg Jensen
 * $Id: crtsdep.h,v 1.2 1994-08-24 13:25:14 beta Exp $
 */

#define ParamOriginProto(retType,name)			 \
  retType name(struct Object *origin, struct ProtoType *proto)
#define ParamThisComp(retType,name)                            \
  retType name(struct Object *this, struct Component *comp)
#define ParamObjOffRange(retType, name)			 \
  retType name(struct Object *theObj,			         \
	 unsigned offset, /* in bytes */		 \
	 unsigned range				         \
	 )
#define ParamStruc(retType, name)                              \
  retType name(struct Structure *struc)
#define ParamThis(retType,name)                                \
  retType name(struct Object *this)

#define setret(newret)
#define getret(saved)

#define RETURN(v) return v
#define GCable_Entry()
#define GCable_Exit(v)

extern long a1;
#define CallBetaEntry(entry,item)	                \
    a1=(long)(item); (* (void (*)()) (entry))()

extern void pushAdr(long *a);
extern long *popAdr();
#define push(v) pushAdr((long*)v)
#define pop(v) (long*)v=popAdr()

#define Protect(var, code)				\
  push(var);						\
  { code; }						\
  pop(var);

#define Protect2(v1, v2, code)				\
  push(v1); push(v2);					\
  { code; }						\
  pop(v2); pop(v1);

#define PushGCRegs()				\
  pushAdr((long *) a0);				\
  pushAdr((long *) a1);				\
  pushAdr((long *) a2);				\
  pushAdr((long *) a3);				\
  pushAdr((long *) a4); 

#define PopGCRegs()			\
  a4 = (long) popAdr();                 \
  a3 = (long) popAdr();			\
  a2 = (long) popAdr();			\
  a1 = (long) popAdr();			\
  a0 = (long) popAdr();

#define DeclReference1(type, name) type name
#define DeclReference2(type, name) type name

#define FetchOriginProto()
#define FetchStruc()
#define FetchThis()
#define FetchThisComp()


/* Various machine instructions used for callbacks in Callback.c */
/* SPARC machine code: */
#define MOV_O7_G1 0x8210000f
#define MK_CALL(p,f) \
  (*(long *)p = 0x40000000| (((unsigned) ((char*)f-(char*)p)) >> 2))
#define NOP 0x1000000

/* Points to top of cStack. Used for nested external calls */
extern long *cIntStackPtr;
extern double *cFloatStackPtr;

