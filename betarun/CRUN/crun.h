/*
 * BETA C RUNTIME SYSTEM, Copyright (C) 1992-94 Mjolner Informatics Aps.
 * by Peter Andersen, Tommy Thorn, and Jacob Seligmann
 */


#ifndef _CRUN_H_
#define _CRUN_H_

#ifdef crts
#define ParamOriginProto(t,name)			 \
  t name(struct Object *origin, struct ProtoType *proto)
#define ParamThisComp(t,name)                            \
  t name(struct Object *this, struct Component *comp)
#define ParamObjOffRange(t, name)			 \
  t name(struct Object *theObj,			         \
	 unsigned offset, /* in bytes */		 \
	 unsigned range				         \
	 )
#define ParamStruc(t, name)                              \
  t name(struct Structure *struc)
#define ParamThis(t,name)                                \
  t name(struct Object *this)

#define setret(newret)
#define getret(saved)

#define RETURN(v) return v
#define GCable_Entry()
#define GCable_Exit(v)

#define CallBetaEntry(entry,item)	                \
    (* (void (*)()) ((long*)entry) )(item)

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


#define DeclReference1(type, name) type name
#define DeclReference2(type, name) type name

#define FetchOriginProto
#define FetchStruc
#define FetchThis
#define FetchThisComp

#endif

#ifndef hppa
extern struct Component* CAlloC();
extern struct Item    * CAlloI();
#endif
extern ref(ValRep) 	AlloVR();
extern ref(ValRep)      LVRACAlloc();
extern ref(ValRep)      LVRAAlloc();
extern ref(RefRep)	AlloRR();
extern ref(StackObject) AlloSO() asm("AlloSO");
extern void		CopyT() asm("CopyT");
extern void		CopySRR() asm("CopySRR");
extern void		CopySVR() asm("CopySVR");
extern ref(Structure)	AlloS() asm("AlloS");
extern ref(Structure)	ThisS() asm("ThisS");
extern ref(Structure)	ObjS() asm("ObjS");
extern void		DoGC() asm("DoGC");
extern ref(Item)	AlloSI() asm("AlloSI");
extern ref(Component)	AlloSC() asm("AlloSC");
extern void             Return();
extern void             RefNone() asm("RefNone");
extern void             AttBC() asm("AttBC");
extern void             CopyRR() asm("CopyRR");
extern void             CopyVR() asm("CopyVR");
extern void             BetaError();
extern void             ChkRA() asm("ChkRA");
extern ref(Component)   Susp() asm("Susp");
extern char	      * IOAalloc();
extern char	      * IOAcalloc();

static inline void
AssignReference(long *theCell, ref(Item) newObject)
{
  *(struct Item **)theCell = newObject;
  if (! inIOA(theCell) && inIOA(newObject))
    AOAtoIOAInsert(casthandle(Object)theCell);
}

static inline
long_clear(char *p, unsigned bytesize)
{
  register long i;
#ifdef RTDEBUG
  if (bytesize&3)
    fprintf(stderr, "What! bytesize&3 != 0\n");
#endif
  for (i = bytesize-4; i >= 0; i -= 4)
    *(long *)(p+i) = 0;	/* Ugly Hacks Work Fast */
}

static inline void
setup_item(ref(Item) theItem,
	   ref(ProtoType) prototype,
	   ref(Object) origin
	   )
{
    register ref(GCEntry) initTab;
  
    theItem->Proto = prototype;
    theItem->GCAttr = 1; /* Set item age to 1 */

    /* Initialize the body part of the item, according to the genTable. */

    initTab = cast(GCEntry) ((char *)prototype + prototype->GCTabOff);

    /* initTab is now pointing to the static GCTable.
     * This table has zero or more elements terminated with a zero word.
     * Each element looks like:
     *   WORD  Offset in the generated object, where this static object begins.
     *   WORD  Signed distance to inclosing object.
     *   LONG  ProtoType of this static object.
     */

    for (; initTab->StaticOff; ++initTab) {
	register ref(PartObject) po;
	
	po = cast(PartObject) ((long *)theItem + initTab->StaticOff);
	po->Proto = initTab->Proto;
	po->OrigOff = initTab->OrigOff;

	/*
	if ( (long)po->Proto == -1)
	  printf("\nsetup_item: component: 0x%08x\n", po);
        */
    }

  ((long *)theItem)[prototype->OriginOff] = (long) origin;
}

#ifdef RTDEBUG
  /* Consistency checks - Checks for valid references */
# ifdef hppa
  static char __CkString[80];
#  define Ck(r) \
   { sprintf(__CkString, "%s: %d: Ck failed: %s (0x%x)", __FILE__, __LINE__, #r, r); \
     if(r) Claim(inIOA(r) || inAOA(r) || inLVRA(cast(Object)(r)) || isLazyRef(r), __CkString); }
# else
/*#  define Ck(r) \
 *  if(r) Claim(inIOA(r) || inAOA(r) || inLVRA(r), __FILE__":" #r ": none or inside IOA, AOA, or LVRA")
 */
extern void CCk(ref(Object) r); /* Easier to debug a function call - PA */
#define Ck(r) CCk(cast(Object)r)
# endif
#else
#define Ck(r)
#endif

#endif
