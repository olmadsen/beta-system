#include <stdio.h>
#define trace true 
#define fulltrace 1

#if 0
#define TRACE_A(code) code;
#else
#define TRACE_A(code)
#endif

#if 0
#define TRACE(code) code; fflush(stdout);
#else
#define TRACE(code)
#endif

#if 0
#define TRACE2(code) code; fflush(stdout);
#else
#define TRACE2(code)
#endif

#if 0
#define TRACE3(code) code; fflush(stdout);
#else
#define TRACE3(code)
#endif

#if 0
#define TRACE_COMP(code) code; fflush(stdout);
#else
#define TRACE_COMP(code)
#endif

#if 0
#define TRACE_CB(code) code; fflush(stdout);
#else
#define TRACE_CB(code)
#endif

#if 0
#define TRACE_C(code) code; fflush(stdout);
#else
#define TRACE_C(code)
#endif

#ifdef __powerc
#define PPC
#endif

#ifdef sgi
#define SGI
#endif

/* this betarun may exists in several versions
 * (1) SGI or PPC;
 * (2) inner-dispatch (IDT) merged with virtual-dispatch (VDT).
 *
 * For PPC, IDT is always merged with VDT, i.e. there may be 3 versions:

 * V1: SGI, IDT NOT meged with VDT
 * V2: SGI, IDT merged with VDT
 * V3: PPC, IDT merged with VDT
 */

/****** platform dependent constants 
 *  SPinstOff     : offset in code segment (G or M-entry) of instruction
 *                  decrementing SP; the SP increment is supposed to be 
 *                  the lower 16 bits of the instruction
 *  INNERinVDB    : true if IDT is merged with VDT
 *  mainEntry     : In the case where IDT is NOT merged with VDT,
 *                  this is the entry of the main-entry point
 */

#define mEntryOff 3
    /* offset in prototype for offset to M-entry point 
     * when inner-dispatch is merged with virtual-dispatch
     */

#define INNERinVDB 1

/* Case V1 above  */
#ifdef SGI-with-INNERinVDB = 0
#include <sys/cachectl.h>
#define mainEntry  -1
#define SPinstOff 3
#define pcOff -1
#define callerOff -2
#endif

/* Case V2 above  */
#ifdef SGI
#include <sys/cachectl.h>
#define mainEntry  0
  /* 0 signals that the inner-dispatch table is NOT before the prototype */
#define SPinstOff 3
#define pcOff -1
#define callerOff -2
#endif  /* SGI */

/* Case V3 above */
#ifdef PPC
#define SPinstOff 2
#define mainEntry 0
  /* 0 signals that the inner-dispatch table is NOT before the prototype */
#define pcOff 2
#define callerOff -1
#endif /* PPC */

#define ref(x)    struct x *

long *T1BETAENVadr;
#define heapMax 1000000
long BetaStackTop,BetaThis;

long oldHT=0;
long heap[heapMax];

#ifdef PPC
long IOA= (long) &heap[0];
#endif
#ifdef SGI
long _IOA= (long) &heap[0];
#endif

long IOAused=0;
long IOAtop = 0; /*&heap[heapMax];*/
long heapTop=0;

long SPxStack[1000], SPyStack[1000];
long SPtop;

char * betaTextArea;
long betaTextPos =0;
/*extern void M1ENV(int a, int b);*/

extern long BetaStackTop,BetaThis;
long  TextProto;
long topObj;
typedef long ProtoType;
typedef long StackObj;
typedef long Object;

typedef struct Component{
    ref(ProtoType)  Proto;     /* Reference to the Prototype  */
    long            GCAttr;    /* The GC attribute            */
    ref(StackObject)StackObj;  /* Packed stack (suspended) 
				  or -1 (active)              */
    ref(Object)     CallerObj; /* Calling object              */
    ref(Component)  CallerComp;/* Calling component           */ 
    long            CallerLSC; /* Local sequence counter in
				  calling object              */ 
    /*long            SPx;       /* SP before Att               */
    /*long            SPy;       /* SP of last long in Att-frame*/
    /*long            level;     /* to be used for real conc    */
    /*long            dummy;     /* MUST be 8-byte aligned      */
    long            Body[1];   /* The body part               */ 
} Component;

struct Component * ActiveComponent = 0;

/******************** debugging stuff ******************/
void put(char ch){ write(1,&ch,1); }

void dumpHeap(long start, long end) {
   int i;
   TRACE(printf("Heap:\n");
         for (i=start; i <= end; i++)  {
           printf("%x: %x\t", &heap[i],heap[i]);
           if ((i % 4) == 0) printf("\n");
        };)
 }
 
long dumpObjX(long *obj, long size)
{ int i;
  for (i=0; i<size; i++)  printf("obj[%i] = &0x%x = 0x%x\n",i*4, &obj[i],obj[i]);
  fflush(stdout);
}

char *ProtoText(long *proto) {
  long statOff,off,i;
  /*  for (i=0; i<20; i++) printf("proto %i = %x\n",i,proto[i] );*/
  statOff = (proto[0] >> 16) & 0xffff;
  off = ((short *)proto)[statOff / 2] ;
  while (off != 0) {
    statOff = statOff + 8;
    off = ((short *)proto)[statOff / 2] ;
  }
  statOff = statOff + 2;
  off = ((short *)proto)[statOff / 2] ;
  while (off != 0) {
    statOff = statOff + 2;
    off = ((short *)proto)[statOff / 2] ;
  };
  statOff = statOff + 2;
  return (char *) &((char *)proto)[statOff];
}

void FatalErr(int n) {
   switch (n) {
   case 1: printf("\n***** Heap overflow\n"); break;
   case 2: printf("\n***** Index error\n"); break;
   case 3: printf("\n***** Reference is none\n"); break;
   case 4: printf("\n***** Executing terminated component\n"); break;
   case 5: printf("\n***** Component stack overflow\n"); break;
   default: printf("\n***** Fatal error: %i\n",n);
   }
   exit(-1);
 }
void BetaError(int n, long * this, long SP, long RA)
{ FatalErr(2);
}

typedef void (* EntryPoint)(long,long *);

EntryPoint theTopEntry(long * proto)
{
#ifdef INNERinVDB
  return (void (*)(long,long *)) proto[6];
#else
  return(EntryPoint) proto[-1];
#endif
}

EntryPoint theMainEntry(long * proto)
{ int i;
#ifdef INNERinVDB
  TRACE_COMP(printf("MainEntry: mentryoff=%i, mentryoff2=%i, mentry=0x%x\n"
        ,mEntryOff,(proto[mEntryOff] & 0xffff) / 4
        ,proto[(proto[mEntryOff] & 0xffff) / 4]);
        fflush(stdout);
        for (i=0; i < 10; i++) printf("Proto: i:%i, proto: 0x%x\n",i,proto[i])
   )
  
  return (void (*)(long,long *)) proto[(proto[mEntryOff] & 0xffff) / 4];
#else
  return(EntryPoint) proto[-1]; /* probably wrong??*/
#endif
}

long super(long *pt) {
   long sup;
   sup = pt[2];
   if (sup == (long)pt) return 0; else return sup;
}

long AllocHeap(int size) {
   long start,i;
   start = (long) &heap[heapTop];
   if (( start % 8) != 0) {start = start + 4; size = size + 1;}
   heapTop = heapTop + size;
   IOAused = heapTop*4;
   /* the following is to experiment with ChkRA: by redefining
    * _IOA, the oldest objects becomes logically outside _IOA
    */
#ifdef PPC
   if ((heapTop > 1000) && (heapTop < 2000)) { IOA= &heap[heapTop]; }
#endif
#ifdef SGI
   if ((heapTop > 1000) && (heapTop < 2000)) { _IOA= &heap[heapTop]; }
#endif

   for (i=0; i<size; i++) ((long *)start)[i]=0;
   if (heapTop > heapMax) FatalErr(1);
  /* printf("AllocHeap: 0x%x %i 0x%x\n",start,size,start+size*4);*/
   return start;
}

long noOfAlloI = 0, alloImin=1400, alloImark1=1457, alloImark2=1468, savedObj,savedSize;



char * BufferAdr;
char * GetTextFromStream3(long F, long toEOL) 
{  char * s;
   printf("Before:GetTextFromStream\n");
   dumpObjX((long *)savedObj,savedSize);
   printf("Buffer address = 0x%x\n",BufferAdr);
	
   /*   s = GetTextFromStream(F,toEOL);*/
   
   BufferAdr = s;
   printf("Buffer address = 0x%x\n",BufferAdr);
   
   printf("After:GetTextFromStream\n");
   dumpObjX((long *)savedObj,savedSize);
   
   return s;
}

long AlloI(int origin, long *proto,long SP) {
  long orgOff; short size=196;
  void (*Gentry)();
  long start,statOff;  
  char * s;
  noOfAlloI = noOfAlloI + 1;
  TRACE_A(if (noOfAlloI > alloImin) {
        s = ProtoText(proto);
        printf("AlloI: %i, %s proto=0x%x, origin=0x%x, origin.origin = 0x%x", 
		         noOfAlloI, s, (long)proto,origin,((long *)origin)[2]);}
  )
  if ((int)proto > 1 ) {
     TRACE(printf("%x %x %x %x %x %x %x %x\n",proto[0],proto[1],proto[2],proto[3]
      ,proto[4]
      ,proto[5],proto[6],proto[7]))
    statOff = (proto[0] >> 16) & 0xffff;
    orgOff = proto[0] & 0xffff;
    size = ( (short *)proto)[6];
    Gentry = (void (*)())proto[1];
  } else if (proto == 0) printf("proto=0\n");
  oldHT = heapTop;
  if (size == 0) {printf("\n***AlloI size=0\n"); fflush(stdout); size = 196;}
  start = AllocHeap(size+4);
 
  TRACE(printf("AlloI: start=%x, orgOff=%i, size=%i, gEntry=%x, origin=%x\n"
      ,start,orgOff,size,Gentry,origin);)

   if ((int)proto > 1 ) {int off,pt,loc;
      ((long *)start)[0] = (long) proto;
      ((long *)start)[orgOff ] = origin;
      off = ((short *)proto)[statOff / 2] ;
      while (off != 0) {
	     pt = ((long *)proto)[(statOff + 4) / 4];
	     loc =  ((short *)proto)[(statOff + 2) / 2];
	     TRACE(printf("PartObj: obj=0x%x, off=%i, proto=%x, loc=%i\n",
                     &((long *)start)[off],off,pt,loc))
	     ((long *)start)[off ] =  pt;
             ((long *)start)[off  + 1] = loc;
	     statOff = statOff + 8;
             off = ((short *)proto)[statOff / 2] ;
      }
      TRACE_A(if (noOfAlloI > alloImin) 
	         printf(", adr=0x%x, charBuf=0x%x\n",start,BufferAdr);
	         if (noOfAlloI == alloImark1) {
		     savedObj = start;
		     savedSize = size;
		     dumpObjX((long *)start,(long)size);
		  }
	          fflush(stdout);
		  if (noOfAlloI > alloImark1) {
		      dumpObjX((long *)savedObj,savedSize);
		      /*dumpObjX((long *)origin,10);*/
		   }
		   if (noOfAlloI == alloImark2) {
		      dumpObjX((long *)origin,10);
		      FatalErr(0);
                    }
	    )
	/* Gentry(SP,start); */
	if (Gentry != 0) CallB(0,start,Gentry,SP);
    };
   TRACE(printf("After Gentry\n");)
   /* dumpHeap();*/
   return start;
}

/* not in official betarun.h */
long * AlloSO(long size) {
   long * start;
   /*printf("AlloSO: %i, %i\n",size, 4 + size/4 + 1);*/
   start = (long *) AllocHeap(4 + size / 4 + 1 );
   start[0] = -2;
   start[1] = 1;
   start[2] = size;  /* body size */
   start[3] = 0;     /* stack size whats the difference between body and stack*/

   return start;
}

long AlloC(int origin, long *proto, long SP) {
   struct Component *start;
   start = (struct Component*)AllocHeap(6);
   start->Proto = -1;
   start->GCAttr = 0;
   AlloI(origin,proto,SP); /* and AlloI does allignment */
   /* the following initializations will only happen for dynamically
    * generated components. For static components, AlloC is NOT called.
    * To initialize static components, code MUST be generated.
    */
   /*start->StackObj = AlloSO(0);
   start->CallerObj = start->Body;
   start->CallerComp = 0;
   start->CallerLSC = proto[-1];
   */
   return start;
 }

int AlloS(long origin, long proto) {
   long start,i;
   TRACE_CB(printf("AlloS origin = 0x%x proto = 0x%x\n",origin,proto))
   TRACE_CB(for (i=0; i<10; i++) printf("proto[%i] = 0x%x\n",i,((long *)proto)[i]))
   start = AllocHeap(4+1);
   ((long *)start)[0] = -3;
   ((long *)start)[1] = 0;
   ((long *)start)[2] = origin;
   ((long *)start)[3] = proto;
   return start;
}

int AlloSI(long dummy, long *struc,long SP) /* NO dummy in real betarun */ {
   TRACE_CB(printf("AlloSI: dummy=0x%x struc=0x%x SP=0x%x\n",dummy,struc,SP))
   TRACE_CB(printf("AlloSI: proto = 0x%x origin =0x%x\n", struc[3],struc[2])) 
   return AlloI(struc[2],(long *)struc[3],SP);
}

long AlloDO(int size, long origin ) {
    long start;
    start = AllocHeap(size);
    ((long *)start)[0] = -9;
    ((long *)start)[2] = origin;
    return start;
}

/* not found in betarun.h */
int AlloORR(long origin, long proto, long obj, long off, long range,long SP) {
    long start,i; 
    TRACE_COMP( printf("AlloORR: proto=0x%x, obj=0x%x, range=%i, off=%i\n",proto,obj,range,off);)
    start = AllocHeap(24 + range);

   ((long *)start)[0 ] = -12;
   ((long *)start)[1 ] = 0;
   ((long *)start)[2 ] = 0;
   ((long *)start)[3 ] = range;;
   ((long *)start)[4 ] = origin; 
   ((long *)start)[5 ] = proto;
   for (i=0;  i < range; i++)
       ((long *)start)[6 + i] = AlloI(origin,(long *)proto,0);

   ((long *)obj)[off / 4 ] = start;
}  

/* not found in official betarun.h */
int AlloORRC(long origin, long proto, long obj, long off, long range, long SP)
{ long start,i; 
  TRACE_COMP( printf("AlloORR: proto=0x%x, obj=0x%x, range=%i, off=%i\n",proto,obj,range,off);)

   start = AllocHeap(24 + range);

   for (i=0;  i < range; i++)
       ((long *)start)[6 + i] = AlloC(origin,(long *)proto,0);
   ((long *)start)[0 ] = -13;
   ((long *)start)[1 ] = 0;
   ((long *)start)[2 ] = 0;
   ((long *)start)[3 ] = range;;
   ((long *)start)[4 ] = origin; 
   ((long *)start)[5 ] = proto;
   ((long *)obj)[off / 4 ] = start;
  }

int AlloVR1(long *this, int off, int range) {
    long start;
    /* printf("AlloVR1: off=%i\n",off / 4);*/
    oldHT = heapTop;
    start = AllocHeap(4 + range); /* too large */
    ((long *)start)[0] = -6; 
    ((long *)start)[3]=range;
    this[off / 4] = start;
}

int AlloVR2(long *this, int off, int range) {
    long start;
    /* printf("AlloVR1: off=%i\n",off / 4);*/
    oldHT = heapTop;
    start = AllocHeap(4 + range); /* too large */
    ((long *)start)[0] = -7; 
    ((long *)start)[3]=range;
    this[off / 4] = start;
}

int AlloVR4(long  *this, int off, int range) {
    long start;
    oldHT = heapTop;
    start = AllocHeap(4 + range);
    /* printf("AlloVR4X: %x, off= %i\n",(long)this, off);*/
    ((long *)start)[0] = -5;
    ((long *)start)[3]=range;
    this[off / 4] = start;
}
int AlloVR8(long *this, int off, int range) {
    long start;
    /* printf("AlloVR1: off=%i\n",off / 4);*/
    oldHT = heapTop;
    start = AllocHeap(4 + range*2 + 1);
    ((long *)start)[0] = -8;
    ((long *)start)[3]=range;
    this[off / 4] = start;
}

int AlloRR(long *this, int off, int range) {
    AlloVR4(this,off,range);
}

void NewVR(long * dst, int off, int range,long SP){
     long newRep,src,head, i,proto, origin,srcKind;
     /*printf("NewVR: dst=%x, off=%i, range=%i\n",(long)dst, off, range);*/

     src = dst[off];
     srcKind =((long *)src)[0];
     if (srcKind <= -12)  head = 6; else head = 4;
     newRep = AllocHeap(head + range);
     ((long *)newRep)[0] = srcKind;
     ((long *)newRep)[1] = 0;
     ((long *)newRep)[2] = 0;
     ((long *)newRep)[3] = range;
     if (srcKind <= -12) {
       origin =((long *)src)[4];
       ((long *)newRep)[4] = origin;
       proto = ((long *)src)[5];
       ((long *)newRep)[5] = proto;
       if (srcKind == -12) {
	 for (i=0;  i < range; i++)
	   ((long *)newRep)[head + i] = AlloI(origin,(long *)proto,0);
       } else {
	 for (i=0;  i < range; i++)
	   ((long *)newRep)[head + i] = AlloC(origin,(long *)proto,0);
       }
     } else
       for (i=0; i < range; i++) 
	 ((long *)newRep)[head + i] = 0;
     dst[off] = newRep;
}

void ExtVR(long * dst, int off, int rangeExt,long SP){
     long newRep, src, i, srcKind, srcRange, head, proto, origin;
     /*printf("ExtVR\n");*/

     src = dst[off];
     srcKind =((long *)src)[0];
     if (srcKind <= -12)  head = 6; else head = 4;
     srcRange =  ((long *)src)[3];
     newRep = AllocHeap(head + rangeExt + srcRange);
     ((long *)newRep)[0] = srcKind;
     ((long *)newRep)[1] = 0;
     ((long *)newRep)[2] = 0;
     ((long *)newRep)[3] = rangeExt + srcRange;
     if (srcKind <= -12) {
        origin = ((long *)src)[4];
	((long *)newRep)[4] = origin;
	proto = ((long *)src)[5];
	((long *)newRep)[5] = proto;
	if (srcKind == -12) {
	  for (i=0;  i < rangeExt; i++)
	    ((long *)newRep)[6 + srcRange + i] = AlloI(origin,(long *)proto,0);
	} else {
	  for (i=0;  i < rangeExt; i++)
	    ((long *)newRep)[6 + srcRange + i] = AlloC(origin,(long *)proto,0);
	}
      }
     for (i=0; i < srcRange; i++) 
         ((long *)newRep)[head + i] = ((long *)src)[head + i];

     dst[off] = newRep;
     
}

void ExtRR(long * dst, int off, int rangeExt,long SP){
   ExtVR(dst,off,rangeExt,SP);
}

void CinitT(){betaTextPos = 0;}

/* official betarun.h has extra currentObj parameter */
long CpkVT(long *rep){int start,range,i;
   /*   for (i=0; i < 5; i++) printf("CpkVT: %x\n",rep[i]);*/
   start = betaTextPos;
   range = rep[3];
   for (i=0; i < range; i++){
       betaTextPos = betaTextPos + 1;
       betaTextArea[betaTextPos] = ((char *)rep)[16+i];
     }
   betaTextPos = betaTextPos + 1;
   betaTextArea[betaTextPos] =0;
   TRACE_C(printf("BetaText: %s\n", (char *)&betaTextArea[start+1]); )
   return (long) &betaTextArea[start+1];    
}

/* official betarun has extra currentObj parameter */
long CpkSVT(long *rep, long first, long last) {
   long start, range, i;
   start = betaTextPos;
   range = last - first + 1;
   for (i=0; i < range; i++) {
       betaTextPos = betaTextPos + 1;
       betaTextArea[betaTextPos] = ((char *)rep)[16 + first - 1 +i];
   }
   betaTextPos = betaTextPos + 1;
   betaTextArea[betaTextPos] = 0;
#if trace 
   printf("BetaSubText: %s\n", (char *)&betaTextArea[start + 1]);
#endif
   return (long) &betaTextArea[start+1];
}
long PpkVT(long *rep){ int start,range,i;
   TRACE(for (i=0; i < 5; i++) printf("PpkVT: %x\n",rep[i]))
   start = betaTextPos;
   range = rep[3];
   betaTextPos = betaTextPos + 1;
   betaTextArea[betaTextPos] = range;
   for (i=0; i < range; i++){
       betaTextPos = betaTextPos + 1;
       betaTextArea[betaTextPos] = ((char *)rep)[16+i];
     }
   betaTextPos = betaTextPos + 1;
   betaTextArea[betaTextPos] =0;
   TRACE(printf("BetaText: size=%i %s\n", (int)betaTextArea[start+1],(char *)&betaTextArea[start+2]))
   return (long) &betaTextArea[start+1];    
}
long PpkSVT(long *rep, long first, long last) {
   printf("PpkSVT\n"); fflush(stdout); return CpkSVT(rep,first,last); 
}
long CopyCT(char * txt){
   long newRep,range,i;
   range = strlen(txt);
   TRACE_A(printf("CopyCT: range=%i  %s\n",range,txt);
           if (noOfAlloI > alloImark1) {
		       printf("txt\n");
			   dumpObjX((long *)txt,savedSize);
			   printf("openFile obj\n");
			   dumpObjX((long *)savedObj,savedSize);
		})
   newRep = AllocHeap(4 + (range / 4) + 1);
   ((long *)newRep)[0] = -6; 
   ((long *)newRep)[1] = 0;
   ((long *)newRep)[2] = 0;
   ((long *)newRep)[3]= range;
   for (i=0; i < range; i++)
       ((char *)newRep)[16+i] = txt[i];
   ((char*)newRep)[16+range]=0;
   TRACE_A(dumpObjX((long *)newRep,4 + range/4 + 1);
           if (noOfAlloI > alloImark1) { dumpObjX((long *)savedObj,savedSize);})
   return (long) newRep;
 }

long dummyCallBack(){ put('C'); return 100;}

long CallBack[5000];
long cbTop=0;

/* official betarun has 2 parameters theStruct theObj;
 * for sgi we have some parameter transfer problems; 
 * sometimes dummy is used instead of struc!
 * MUST be fixed
*/
long CopyCPP(long *struc, long *dummy) 
{ long start,entry,res,i;

  if (struc[0] != -3) printf("\n*** CopyCPP: illegal struc parameter\n");
  entry= ((long *)struc[3])[5];
  start = &CallBack[cbTop];
  TRACE_CB(printf("CopyCPP: entry=0x%x, start=0x%x\n",entry,start);)

#ifdef PPC
  /* callBack[cbTop]   = struc
   * CallBack[cbTop+1] = &CallBack[cbTop+3];
   * callBack[cbTop+2] = 0  TOC - not used 
   * callBack[cbTop+3] = lis r12,     entry >> 16
   * callBack[cbTop+4] = lis r24,     start >> 16         -- dataReg0
   * callBack[cbTop+5] = ori r12,r12, entry & 0xffff
   * callBack[cbTop+6] = ori r24,r24, start & 0xffff
   * callBack[cbTop+7] = lwz r0, 0(r12)
   * callBack[cbTop+8] = mtctr r0			
   * callBack[cbTop+9] = lwz RTOC, 4(r12)
   * callBack[cbTop+10] = bctr
   */

  CallBack[cbTop] = (long)struc;
  CallBack[cbTop+1] = &CallBack[cbTop+3];
  CallBack[cbTop+2] = 0;
  CallBack[cbTop+3] = 0x3c000000 | (12 << 21) | (entry >> 16);
  CallBack[cbTop+4] = 0x3c000000 | (24 << 21) | (start >> 16);
  CallBack[cbTop+5] = 0x60000000 | (12 << 21) | (12 << 16) | (entry & 0xffff);
  CallBack[cbTop+6] = 0x60000000 | (24 << 21) | (24 << 16) | (start & 0xffff);
  CallBack[cbTop+7] = 0x80000000 | (12 << 16);
  CallBack[cbTop+8] = 0x7c0903a6 ;
  CallBack[cbTop+9] = 0x80000000 | ( 2 << 21) | (12 << 16) | 4;
  CallBack[cbTop+10] = 0x4e800420;

  TRACE_CB(for (i=cbTop; i < cbTop+11; i++) 
           printf("CB code: i=%i, 0x%x\n",i,CallBack[i]);)
  TRACE_CB(Debugger();)	
  cbTop = cbTop + 11;
  /* FlushCodeCache;*/
  /*  needed for the 604; not needed for the 601 */
  return(long)&CallBack[cbTop-10];
#endif

#ifdef SGI
   /* callBack[cbTop]   = struc
    * callBack[cbTop+1] = lui t9,    entry>>16
    * callBack[cbTop+2] = ori t9,t9, entry & 0xffff
    * callBack[cbTop+3] = lui r8,    start>>16
    * callBack[cbTop+4] = jr  t9
    * callBack[cbTop+5] = ori r8,r8, start & 0xffff
    */

   CallBack[cbTop] = (long)struc;
   CallBack[cbTop+1] = 0x3c000000 | (25 << 16) | (entry >> 16); 
   CallBack[cbTop+2] = 0x34000000 | (25 << 21) | (25 << 16) | (entry & 0xffff);
   CallBack[cbTop+3] = 0x3c000000 | (8 << 16) | (start >> 16); 
   CallBack[cbTop+4] = 0x00000008 | (25 << 21);
   CallBack[cbTop+5] = 0x34000000 | (8 << 21) | (8 << 16) | (start & 0xffff);


   cbTop = cbTop + 6;

   TRACE_CB(printf("\nCopyCPP, funcPtr=%x\n",funcPtr))
   res=_flush_cache((long *)&CallBack[0],(long)&CallBack[cbTop+1],BCACHE);
   return(long)&CallBack[cbTop-5];
#endif
}

/* NOT in official betarun */
long AlloSICB(long *CallBackPtr,long SP){
   long start;
   start = AlloSI(0,CallBackPtr[0],SP);  
   return start;
 }

void dumpObj(char *s, long * sObj){
   int i;
/*   printf("%s = 0x%x\n",s,sObj);
   for (i=0; i<10; i++)
     printf("%s: %i, 0x%x\n", s, i, sObj[i]);*/
}

void CopySVR(long *src, long *dst, int off, int first, int last, int SP){
   long range, i, srcKind, head;
   long * newRep;
   /*printf("CopySVR: off=%i, first=%i, last=%i\n",off,first,last);*/
   range =  last - first + 1; 
   srcKind =((long *)src)[0];
   if (srcKind <= -12)  head = 6; else head = 4;
   newRep = (long *)AllocHeap(range + head+1);
                             /*someone allocates one to little?*/
   for (i=0; i < head; i++) newRep[i] = src[i];
   newRep[3] = range; 
   switch (newRep[0]) {
   case -5:  /* val rep */ case -4: /* ref rep */
     for (i=0; i < range; i++) 
         ((long *)newRep)[4 + i] = ((long *)src)[4 + i + first - 1];
     break;
   case -6:  /* byte/char */
     for (i=0; i < range; i++) 
         ((char *)newRep)[16 + i] = ((char *)src)[16 + i + first - 1];
     break;
   case -7: /* short */
     for (i=0; i < range; i++) 
         ((short *)newRep)[8 + i] = ((short *)src)[8 + i + first - 1];
     break;
   case -8: /* double */
     for (i=0; i < range; i++) 
         ((double *)newRep)[2 + i] = ((double *)src)[2 + i + first - 1];
     break;
   case -12:
   case -13:
     for (i=0; i < range; i++) 
         ((long *)newRep)[6 + i] = ((long *)src)[6 + i + first - 1];
     break;

   default:
     printf("CopySVR: rep type NOT handled: %i\n", newRep[0]);
 }
   dst[off] = (long)newRep; 
   /*for (i=0; i < (range+4); i++) printf("%x\n",newRep[i]);*/
}

void NewRR(long * dst, int off, int range,long SP){
   NewVR(dst,off,range,SP);
}

void MkTO(char *txt, long *obj, long off, long sp) {
   int i;
   int textObj,repObj;
   textObj = AlloI(0,(long *)TextProto,0);
   repObj = AllocHeap(196);
   /*printf(
     "MkTO: obj=%x, off=%i, textAdr= %x, text=%s, textProto=%x, textObj=%x, repObj=0x%x\n"
	  ,(long)obj,off,(long)txt, txt,(long)TextProto,(long)textObj,repObj);
  */

  ((long *)repObj)[0]=-6; 
  ((long *)repObj)[1]= 0;
  ((long *)repObj)[2]= 0;
  ((long *)repObj)[3] = strlen(txt);
   for (i=0; i<= strlen(txt); i++) {
       ((char *)repObj)[16+i] = txt[i];
   };

  ((long *)textObj)[2] = topObj; /* origin */
  ((long *)textObj)[3] = repObj;
  ((long *)textObj)[4] = strlen(txt);
  ((long *)textObj)[5] = 0;

  obj[off] = textObj;

/*  dumpHeap(oldHT,heapTop);*/
      
}

long * CopyT(char *txt, long *obj, long off){
   int i, repObj, range;
   TRACE_C(printf("CopyT; obj=%x, off=%i, txt=%s\n", (long)obj, off, txt))
   range = strlen(txt);
   repObj = AllocHeap(4 + (range/4) +2);

  ((long *)repObj)[0]=-6; 
  ((long *)repObj)[1]= 0;
  ((long *)repObj)[2]= 0;
  ((long *)repObj)[3] = range;
   for (i=0; i < range; i++) {
       ((char *)repObj)[16+i] = txt[i];
   };
    
   obj[off] = repObj;
   /*obj[2] = topObj; /* origin */
   return obj;
 }

void CopyVR(long sourceRep, long destObj, long off, int sp) {
  long i, repObj, range, head=4, srcKind;
  range = ((long *)sourceRep)[3];
  TRACE2(printf("CopyVR: sourceRep=0x%x, destObj=%x, off=%i, range=%i\n", sourceRep, destObj,off,range);)
  repObj = AllocHeap(96); /* OBS proper size must be used */
  
  TRACE2(if (((long *)repObj)[0] = -8) printf("txt=%x\n",((char *)sourceRep)[16]);)
  
  srcKind = ((long *)sourceRep)[0];
  ((long *)repObj)[0]= srcKind;
  ((long *)repObj)[1]= 0;
  ((long *)repObj)[2]= 0;

  ((long *)repObj)[3] = range;
  if (srcKind <= -12) {
    head = 6;
    ((long *)repObj)[4] = ((long *)sourceRep)[4];
    ((long *)repObj)[5] = ((long *)sourceRep)[5];
  };
  /* OBS a proper copy based on srcKind MUST be maded */
  for (i=0; i<= range; i++) {
    ((long *)repObj)[head + i] = ((long *)sourceRep)[head + i];
  };  
    
  ((long *)destObj)[off] = repObj;
  TRACE2( if (srcKind == -6)  printf("char rep: %s\n",&((char *)repObj)[16]);)
}

void CopyRR(long sourceRep, long destObj, long off, int sp) {
   CopyVR(sourceRep,destObj,off,sp);
}

void CopySRR(long *src, long *dst, int off, int first, int last, int sp){
   CopySVR(src,dst,off,first,last,sp);
}

void HandleIndexErr(){
 FatalErr(2);
 }

long ThisS(long *this)
{ TRACE_CB(printf("ThisS: origin = 0x%x proto =0x%x\n", this[2],this[0])) 
  return AlloS(this[2],this[0]); 
}

void Qua(long *dstQuaProto, long *theCell, long *dstQuaOrigin, long SP) {
}

void ChkRA(long *theObjHandle, long dummy, long IOAbot, long IOAused) {
/* Note: registers must be saved before calling ChkRA since any code
 * may destroyc registers
 */
/*printf("ChkRA  obj=0x%x, IOAbot=0x%x, IOA=%i\n",theObjHandle,IOAbot,IOAused);*/

}


void RefNone(){
 FatalErr(3);
}
void Return(){}

long SPglobal,LSCglobal,SPxGlobalTop;

long TopOfRefStack(long * SPx) {
   long topObj,i,next;
   next = 1;
   i = 0;
   while (next != 0) {
      topObj = next;
      i= i + 1;
      next = SPx[-i];
   };
   /*printf("TopOfStack = 0x%x\n",topObj);*/
   return topObj;   
 }

long prefixLevel(long * proto, long PC) {
  long PL,thePL,mEntry,minPC=0x3fffffff,PCdist;
  mEntry = proto[-1];
  PL = 1;
  thePL = 1;
  while (mEntry != (long)&Return) {
    PCdist = PC - mEntry;
    if ((PCdist > 0) && (PCdist < minPC)) {
      thePL = PL;
      minPC = PCdist;
    };
    PL = PL + 1;
    mEntry = proto[-PL];
  };
  /*  return,M3FOO,M2FOO,M1FOO,x1,x2,...
   *     -4   -3     -2    -1  0
   *    PL
   *           ...thePL...
   */
  /* printf("thePL=%i\n",thePL);*/
  return thePL; 
}

long *dyn(long * obj, long SP, long LSC) {
  /* obj:      an object in the call chain
   * SP:       stack pointer for frame on SP-stack for obj
   * LSC:      local sequence control (PC) in obj
   * return caller of obj and SP,LSC for caller in global variables
   *                          SPglobal, LSCglobal
   */
   long * proto, * codeStart, * caller;
   long SPoff,SPx,PL,inst,opCode,destReg,baseReg,offset;
   struct Component *callerComp;
   if ((long) obj == 4 ) {
      SPglobal= ((long *)SP)[0];
      LSCglobal= 0; /* how do we find the real one? */
      return (long *) ((long *)SP)[1];
   }
   proto = (long *)obj[0];
   if ((long)proto == -1) {
     callerComp = ((struct Component *)obj)->CallerComp;
     SPglobal = /*callerComp->SPx;*/ SPxStack[SPxGlobalTop]; /* NOT tested */
     SPxGlobalTop = SPxGlobalTop - 1;

     LSCglobal = callerComp->CallerLSC;
     return ((struct Component *)obj)->CallerObj;
   }
   if (isTop(proto)) { PL = 1; }
   else { 
     PL = prefixLevel(proto,LSC);
   };
   codeStart = (long *)proto[-PL];
   SPoff = (codeStart[3] & 0xffff) | 0xffff0000; /* codeStart[0] for non-PIC
						    codeStart[3] for PIC
						 */
   SPoff = - SPoff;
   SPx = SP + SPoff;
   LSCglobal= ((long *)SPx)[-1];
   caller =  (long *)((long *)SPx)[-2];

   /*   printf("Dyn: SPoff=%i, caller=0x%x\n\n",SPoff,caller); */
   SPglobal = SPx;

   return caller;
 }

long findMentry(long *proto, long PC)
 { long mEntry, PCdist, minPC=0x3fffffff,theMentry;
   TRACE3(printf("findMentry1: proto=0x%x, PC=0x%x, actual-mEntrOoff=%i\n"
           ,proto,PC,(proto[mEntryOff] & 0xffff) / 4))
   while (proto != 0) {
      mEntry = proto[(proto[mEntryOff] & 0xffff) / 4];
#ifdef PPC
      /* mEntry is a TOC-entry; go indirect to find the code address */
      mEntry = ((long *) mEntry)[0]; 
#endif
      TRACE3(printf("findMentry2:0x%x\n",mEntry))
      PCdist = PC - mEntry;
      if ((PCdist > 0) && (PCdist < minPC)) {
         minPC = PCdist;
         theMentry = mEntry;
      };
      proto = super(proto);
   };   
   TRACE3(printf("findMentry3 min:0x%x\n",theMentry))
   return theMentry;
 }

long *dyn2(long * obj, long SP, long LSC) {
  /* dyn2 is to be used for prototypes where the inner-dispatch
   * table is mixed with the virtual dispatch-table!
   * obj:      an object in the call chain
   * SP:       stack pointer for frame on SP-stack for obj
   * LSC:      local sequence control (PC) in obj
   * return caller of obj and SP,LSC for caller in global variables
   *                          SPglobal, LSCglobal
   */
   long * proto, * codeStart, * caller;
   long SPoff,SPx,PL,inst,opCode,destReg,baseReg,offset,i;
   struct Component *callerComp;
   TRACE3(printf("dyn2a: obj=0x%x, SP=0x%x, LSC=0x%x\n", obj,SP,LSC))
   if ((long) obj == 4 ) {
      SPglobal= ((long *)SP)[0];
      LSCglobal= 0; /* how do we find the real one? */
      return (long *) ((long *)SP)[1];
   }
   proto = (long *)obj[0];
   if ((long)proto == -1) {
     callerComp = ((struct Component *)obj)->CallerComp;
     SPglobal = /*callerComp->SPx;*/ SPxStack[SPxGlobalTop]; /* NOT tested */
     SPxGlobalTop = SPxGlobalTop - 1;

     LSCglobal = callerComp->CallerLSC;
     return ((struct Component *)obj)->CallerObj;
   }
   if (proto == (long *) -9) {
      TRACE3(printf("DoPart object\n"))
	  obj = ((long *)obj)[2]; /* get the real object via origin */
	  proto = (long *)obj[0];
   }
   codeStart = (long *) findMentry(proto,LSC);
   TRACE3(for (i=-3; i<=3; i++) {
      printf("code: %i, 0x%x, 0x%x\n", i, codeStart[i], (codeStart[i] & 0xffff) | 0xffff0000 ); fflush(stdout);
	  };
	  printf("codeStart: %i, 0x%x\n",SPinstOff,codeStart[SPinstOff]))
   SPoff = (codeStart[SPinstOff] & 0xffff) | 0xffff0000; 
   SPoff = - SPoff;
   SPx = SP + SPoff;
   LSCglobal= ((long *)SPx)[pcOff];
   caller =  (long *)((long *)SPx)[callerOff];
   TRACE3(printf("dyn2b: SPoff=%i, caller=0x%x\n\n",SPoff,caller))
   SPglobal = SPx;

   return caller;
 }
   
/* arguments jumpAdr=a0, exitObj=a1, SP-offset=dataRegA  
 * mch.saveSp MUST be  saved: see MC68machine.bet;
 * We dont use jumpAdr here;
 * and is SP-offset really needed? We compute it using dyn?
 * NOT in official betarun.h
*/
long ExO(long jumpAdr,long * exitObj, long PC, long * this, long SP) {
  long * a;
  long SPx;
  void (* compAdr)(long a0,long * a1);

  TRACE3(printf("\nExO: jumpAdr=0x%x, exitObj=0x%x, PC=0x%x, this=0x%x\n",
        jumpAdr,exitObj,PC,this))
  a = this; SPx = SP; LSCglobal = PC; SPxGlobalTop = SPtop; /* missing */
  while (a != exitObj) {
#ifdef INNERinVDB
     a = dyn2(a,SPx,LSCglobal);
#else
     a = dyn(a,SPx,LSCglobal);
#endif
     SPx = SPglobal;
  };

  return SPx;
}

void printCompStack(long * SPz, long dummy, long SPsize)
{ int i;
 TRACE_COMP(for (i=0; i < (SPsize / 4)+4; i++) {
		     printf("StackElm: %i: &SPz[i]= 0x%x, SPz[i]=0x%x\n"
		    ,i*4, &((long *)SPz)[i],((long *)SPz)[i]);} )
 
}

void terminate()
{ long SPx;
  ref(object) callerObj;
  EntryPoint callingRA;
  
  SPx = SPxStack[SPtop];
  SPtop = SPtop - 1;
  ActiveComponent->CallerLSC = -1;
  callerObj = ActiveComponent->CallerObj;
  ActiveComponent = ActiveComponent->CallerComp;
  callingRA = (EntryPoint) ActiveComponent->CallerLSC;
  
  TRACE_COMP(printf("Terminating component: activeComponent=0x%x, callerObj=0x%x, SPx=0x%x, callingRA=0x%x\n"
  ,ActiveComponent,callerObj,SPx,callingRA))
  /* we get here when the component terminates; we must return a proper
   * a0 and a1, since th and SP are set after Att
   */
  callingRA(SPx,(long *)callerObj);
}

/* NO RA and SPx in official betarun */
void Att(ref(Object) this, struct Component * comp, long RA, long SPx)
{ long first;
  long * compObj;
  long * compProto;
  void (* compAdr)(long a0,long * a1);
  long SPy,SPz,SPsize,sp,spLoc;
  int isFirst,i;
  long * sObj, * topObj;

  SPy = GetSP();
  if (ActiveComponent != 0) {
    ActiveComponent->CallerLSC = RA;
    SPtop = SPtop + 1;
    SPxStack[SPtop] = SPx;
    SPyStack[SPtop] = SPy;
  } else { printf("ActiveComponet == 0 \n");};
  TRACE_COMP(printf("\nAtt: comp=0x%x, this=0x%x, SPx=0x%x, SPy=0x%x,RA=0x%x\n"
	 ,(long)comp,(long)this,SPx,SPy,RA))
  /* dumpObj("Attach comp",comp); */
   
  topObj = comp->CallerObj; 
  compAdr = (void (*)(long,long *)) comp->CallerLSC;
  TRACE_COMP(printf("\ncompAdr=0x%x\n",compAdr))
  if ((long)compAdr == -1) FatalErr(4); 

  isFirst = compAdr == 0;

  compObj = comp->Body;
  TRACE_COMP(printf("\nBody=0x%x\n",compObj))

  compProto =  (long *) compObj[0];
  TRACE_COMP(printf("\nCompProto=0x%x\n",compProto))
  
 
  if (isFirst) { 
     compAdr = theTopEntry(compProto);
     TRACE_COMP(printf("First: compAdr=0x%x\n",compAdr))
      topObj = compObj;
   } else {
     /* pack current component to stack object */
     sObj = comp->StackObj;
     dumpObj("Attach stackObj",sObj);
     SPsize = ((long *)sObj)[2];

     SPz = SPy - SPsize; 
     TRACE_COMP(printf("UnPack: SPz=0x%x, SPy=0x%x, SPsize=%i\n",SPz,SPy,SPsize);)
     /* Unpack Stack Object. 
      * NOTE: after unpacking the stack object you CANNOT call other 
      * C-functions since this will DESTROY the stack!
      */
     for (i=0; i < (SPsize / 4); i++) {
         ((long *)SPz)[0+i] = sObj[3 + i];
   }	
#ifdef  PPC
   /* on PPC the stack contains SP pointers that links stack segments;
    * these have been made relative, since the stack may be unpacked
    * at another place in memory
    */
   spLoc = 0; sp = ((long *)SPz)[spLoc];
   ((long *) SPz)[spLoc] = SPz + sp;
	
   while (sp < SPsize) {
	 spLoc = sp;
	 sp = ((long *)SPz)[sp / 4];
	 ((long *) SPz)[spLoc / 4] = SPz + ((long *) SPz)[spLoc / 4] ;
    }
#endif
   /* DONT do this! Will DESTROY stack: printCompStack(SPz,0,SPsize);*/
  }
  
  /* if (ActiveComponent != 0) ActiveComponent->StackObj =  -1; */
  
  comp->CallerComp = ActiveComponent;
  comp->CallerObj = this;
  comp->CallerLSC = -1; 
  
  ActiveComponent = comp;

   /* Execute comp.
    * 1st call starts at M111FOO; a0=dummy, a1=ca; i.e a0 is not used
    * in this situation, since M111FOO adjusts SP as usual.
    * Subsequent calls after Attach; a0=SPz, a1=ca;
    */

  /* compAdr(SPz,topObj,SPsize);*/
  if (isFirst)
    { CallB(0,topObj,compAdr,SPz); }
  else
    compAdr(SPz,topObj);

  /* Since compAdr has executed BETA code, registers may have been destroyed.
   * On SGI this does NOT cause problmes;
   * On PPC it apparently cause problmes; we can thus NOT reply on local 
   * variables in Att being unchanged.
   * We restore SPx from SPxStack and RA from ActiveComponent.
   */
  terminate();
}

/* No RA and SPz in official betarun.h */
void Susp(long * this, long oldSP, long RA, long SPz){
   long first;
   struct Component * returnComp;
   long * callerObj;
   void (* callingRA)(long SP , long * this);
   long SPx, SPy, spLoc, sp;
   int i;
   long * sObj; 
   TRACE_COMP(printf("\nSusp:  ActiveComponent=0x%x\n",ActiveComponent))

   SPx = SPxStack[SPtop];
   SPy = SPyStack[SPtop];
   SPtop = SPtop - 1;
   
   ActiveComponent->CallerLSC =  RA;
   callerObj = ActiveComponent->CallerObj;

   returnComp = (struct Component*) ActiveComponent->CallerComp;   
   callingRA = returnComp->CallerLSC;
  
   ActiveComponent->CallerObj = this;
  
   /* pack stack SPz - SPy to  activeCompSP*/
   sObj = AlloSO(SPy - SPz);

#ifdef PPC
   /* on PPC the stack contains SP pointers that links stack segments;
    * these must be made relative, since the stack may be unpacked
    * at another place in memory
    */  
   TRACE_COMP(printCompStack(SPz,0,(SPy - SPz));)
	
   /* The next call of GetSP() is VERY TRICKY!
    * Let SP be the current strack pointer of this C-frame;
    * The code that packs the stack and converts absolute SP-links 
    * to relative SP-links assumes that  SP[0] points to the
    * previous stack-frame! This is ONLY the case if a C-function has 
    * called from this frame; the call of GetSP guarantees this!
    * Note all calls of e.g. printCompStack will also gaurantee this,
    * test prints don¿t show the problem!
    */
   sp=GetSP();
   spLoc = SPz; sp = ((long *)SPz)[0];
   while (sp <= SPy) { 
         TRACE_COMP(printf(" spLoc=0x%x, sp=0x%x\n", spLoc,sp))
	 ((long *)spLoc)[0] = sp - SPz ;
	 spLoc = sp;
	 sp = ((long *)sp)[0];
   };
#endif

   /* copy SPz[0],  SPz[1], ... , SPz[(SPy - SPz - 4) / 4] = SPy[-1] */
   for (i=0;  i < (SPy - SPz) / 4; i++) {
       sObj[3+i] = ((long *)SPz)[0 + i];
  };	


   TRACE_COMP(printCompStack(&sObj[3],0,SPy-SPz);)

   dumpObj("Suspend stackObj",sObj);
   ActiveComponent->StackObj = sObj;
   dumpObj("Suspend active", (long *)ActiveComponent);
   /* return to returnComp at RA */

   ActiveComponent = ActiveComponent->CallerComp;
   /* ActiveComponent->CallerComp = 0;*/
   callingRA(SPx,callerObj);
 }

int eqS(long * lft, long * rht) {
   int bool,l,r;
   if (lft != 0) l = lft[3];
   if (rht != 0) r = rht[3];
   if (l == r) bool = 1; else bool = 0;
   return bool;
}

int neS(long * lft, long * rht) {
   int bool,l,r;
   if (lft != 0) l = lft[3];
   if (rht != 0) r = rht[3];
   if (l != r) bool = 1; else bool = 0;
   return bool;
 }


int isTop(long * pt) {
  long sup;
  sup = super(pt);
  /* printf("IsTop: pt=0x%x, sup=%x, super(sup)=0x%x\n", pt,sup,super(pt));*/
  return (super((long *)sup) == 0);
}

int ltS(long * lft, long * rht) {
   int bool,l,r;
   if ((lft == 0) || (rht == 0)) return 0;
   l = lft[3];
   r = rht[3];
   bool = 0;
   while ((l = super((long *)l)) != 0) {/*printf("\nltS: %x, %x\n",l,r);*/
    if (l == r) return 1;
   }
   return bool;
}
int leS(long * lft, long * rht) {
   if (eqS(lft,rht)) return 1; else return ltS(lft,rht);
 }
int gtS(long * lft, long * rht) {
    return ltS(rht,lft);
  }
int geS(long * lft, long * rht) {
   if (eqS(lft,rht)) return 1; else return gtS(lft,rht);
 }
long ObjS(long *obj) { 
   long proto, orgOff,origin;
   proto = obj[0];
   orgOff = ((long *)proto)[0] & 0xffff;
   origin = obj[orgOff];
   return AlloS(origin,proto);
}
void Initialize() {
 printf("Initialize\n");
}

void SetProtos(long *adr, long *textP) {
   T1BETAENVadr = adr;
   TextProto= textP;
   TRACE(printf("T1BETAENV = 0x%x\n",T1BETAENVadr))

}

long ArgCount;
char * * ArgVector;

char *Argv(long n) 
{ if (n <= ArgCount) {return ArgVector[n-1];} else return ""; 
}
long Argc(){return ArgCount;}

void main(long argc, char *argv[]) 
{ long a0,i;
  char ch;
  void (* M1BETAENV)(long a0,long * a1);
  printf("Starting simple betarun!\n"); fflush(stdout);
  ArgCount = argc;
  ArgVector = argv;
  betaTextArea = (char *)malloc(1000);
  TRACE(printf("SetProtos: %x\n",SetProtos))
   
#ifdef PPC
  Debugger();
#endif

  BETA_main();
  ActiveComponent = (struct Component *)AlloC(0,T1BETAENVadr,GetSP());
  topObj = ActiveComponent->Body;

  M1BETAENV = theTopEntry(T1BETAENVadr);
  CallB(0,topObj,M1BETAENV,0);
  /* M1BETAENV(0,topObj); */
  printf("End simple betarun\n"); fflush(stdout);
}

void AttBC(){}

void BetaExit(){}
void FailureExit(){}
void DoGC(){}

void PrintBetaStack(long *this, long SP, long LSC) {
  long *a;
  char *kind,*pt;
  printf("\n*** Beta stack:\n");
  a = this; SPglobal = SP; LSCglobal = LSC;
   while (a != 0) {
     if ((long)a == 4) {kind = "CallBack"; pt= "";
     } else {
      if (a[0] == -1) {kind = "Component"; pt= "";} 
      else {
	kind ="Item";
        pt=ProtoText(a[0]);
      }}
      printf("%s: 0x%x %s\n",kind,a,pt);

#ifdef INNERinVDB
      a = dyn2(a,SPglobal,LSCglobal);
#else
      a = dyn(a,SPglobal,LSCglobal);
#endif
    }
}

void doGC() {printf("\n**** doGC ******\n"); }

double i2f(long n) { return (double)n; }

/* ----------------- Functions supporting Stream.GetText -------------------- */

static char *OutOfMemError="Out of memory during StreamGetText\n";

#define INITBUFFERSIZE  500   /* Initial size of Buffer. */

static char *Buffer;          /* Nuffer space allocate here. */
static int  BufferSize=0;     /* Current size of Buffer. */


void InitBuffer2()
  {
   BufferSize=INITBUFFERSIZE;
   Buffer=(char *)malloc(BufferSize);
   if(!Buffer)
     {
      fputs(OutOfMemError,stderr);
      exit(147);
     }
}


void EnlargeBuffer2()
  /* Double the size of Buffer or allocate an initial Buffer. */
{
   BufferSize*=2;
   Buffer=realloc(Buffer,BufferSize);
   if(!Buffer)
     {
      fputs(OutOfMemError,stderr);
      exit(147);
     }
}


static char streamStatus;


int StreamError2()
  /* Return whether or not last call to GetTExtFromStream succeeded. */
{
  return(streamStatus==EOF);
}
 

char *GetTextFromStream2(F,toEOL)
  /* Read a string from the file. If toEOL is true then read to end of line,
     else read to first space. Skip the character (eol or space) that causes
     reading to stop.
     Call StreamError afterwards to see if operation succeeded.
  */
  FILE *F;
  int  toEOL;
{
   register FILE *F1;        /* We use a lot of registers for efficiency. */
   register char *Buffer1;
   register int  i,ch;
   int           oldSize;

   if(!BufferSize)            /* The first time, initialize Buffer. */
     InitBuffer2();
   F1=F;
   oldSize=0;                 /* This much of Buffer currently used. */
   if(!toEOL)                 /* Skip to first non-blank. */
     {
      while((ch=getc(F1))<=' ' && ch!=EOF) 
        /* SKIP */ ;
      if(ch==EOF || ungetc(ch,F1)==EOF)
        {
         streamStatus=ch;
         return("");
        }
     }
   while(1)
     {
      Buffer1=Buffer+oldSize; /* Insert from this place in Buffer. */
      i=BufferSize-oldSize;
      if(toEOL)               /* We have two almost identical copies of the
                                 inner loop, one reading to eol the other to
                                 a blank.
                              */
        {
         while(i--)           /* While more room in Buffer. */
           {
            if((*Buffer1++=ch=getc(F1))=='\n' || ch==EOF)
              {
               streamStatus=ch;
               Buffer1[-1]=0; /* Skip the stop char. */
               return(Buffer);
              }
           }
        }
      else
        {
         while(i--)           /* While more room in Buffer. */
           {
            if((*Buffer1++=ch=getc(F1))<=' ' || ch==EOF)
              {
               streamStatus=ch;
               Buffer1[-1]=0; /* Skip the stop char. */
               return(Buffer);
              }
           }
        }
      oldSize=BufferSize;
      EnlargeBuffer2();
     }
}
  
