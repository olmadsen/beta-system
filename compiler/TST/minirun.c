#define trace true 
#define fulltrace 1

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
 *  SPinstOff     : offset in code segement (G or M-entry) of instruction
 *                  decrementing SP; the SP increment is supposed to be 
 *                  the lower 16 bits of the instruction
 *  INNERinVDB    : true if IDT is merged with VDT
 *  mainEntry     : In the case where IDT is NOT merged with VDT,
 *                  this is the entry of the main-entry point
 */

#include <sys/cachectl.h>
/* MIPS 

#define SPinstOff 3
#define INNERinVDB 0
*/

/*  PPC */
#define SPinstOff 3
#define INNERinVDB 1

#define mainEntry  -1
#define mEntryOff 3
    /* offset in prototype for offset to M-entry point 
     * when inner-dispatch is merged with virtual-dispatch
     */

#define ref(x)    struct x *

long *T1BETAENVadr;
#define heapMax 1000000
long BetaStackTop,BetaThis;

long oldHT=0;
long heap[heapMax];
long _IOA= (long) &heap[0];
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
   printf("Heap:\n");
   for (i=start; i <= end; i++)  {
       printf("%x: %x\t", &heap[i],heap[i]);
       if ((i % 4) == 0) printf("\n");
     };
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
   if ((heapTop > 1000) && (heapTop < 2000)) { _IOA= &heap[heapTop]; }
   for (i=0; i<size; i++) ((long *)start)[i]=0;
   if (heapTop > heapMax) FatalErr(1);
  /* printf("AllocHeap: 0x%x %i 0x%x\n",start,size,start+size*4);*/
   return start;
}

int AlloI(int origin, long *proto,long SP) {
  long orgOff; short size=196;
  void (*Gentry)();
  long start,statOff;  
  /*printf("proto=:%x, origin=%x\n", (long)proto,origin);*/
  if ((int)proto > 1 ) {
     /* printf("%x %x %x %x %x %x %x %x\n",proto[0],proto[1],proto[2],proto[3]
      ,proto[4]
      ,proto[5],proto[6],proto[7]);*/
    statOff = (proto[0] >> 16) & 0xffff;
    orgOff = proto[0] & 0xffff;
    size = ( (short *)proto)[6];
    Gentry = (void (*)())proto[1];
  } else if (proto == 0) printf("proto=0\n");
  oldHT = heapTop;
  if (size == 0) {printf("\n***AlloI size=0\n"); size = 196;}
  start = AllocHeap(size+4);

    /*printf("\nAlloi: start=%x, orgOff=%i, size=%i, gEntry=%x, origin=%x\n"
      ,start,orgOff,size,Gentry,origin);*/

   if ((int)proto > 1 ) {int off,pt,loc;
      ((long *)start)[0] = (long) proto;
      ((long *)start)[orgOff ] = origin;
      off = ((short *)proto)[statOff / 2] ;
      while (off != 0) {
	     pt = ((long *)proto)[(statOff + 4) / 4];
	     loc =  ((short *)proto)[(statOff + 2) / 2];
	     /* printf("PartObj: obj=0x%x, off=%i, proto=%x, loc=%i\n",
                     &((long *)start)[off],off,pt,loc); */
	     ((long *)start)[off ] =  pt;
             ((long *)start)[off  + 1] = loc;
	     statOff = statOff + 8;
             off = ((short *)proto)[statOff / 2] ;
	    }
      Gentry(SP,start);

    };
   /*  printf("After Gentry\n");*/
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
   long start;
   start = AllocHeap(4+1);
   ((long *)start)[0] = -3;
   ((long *)start)[1] = 0;
   ((long *)start)[2] = origin;
   ((long *)start)[3] = proto;
   return start;
}

int AlloSI(long dummy, long *struc,long SP) /* NO dummy in real betarun */ {
   return AlloI(struc[2],(long *)struc[3],SP);
}

long AlloDO(int size, long origin ) {
    long start;
    start = AllocHeap(size);
    ((long *)start)[0] = 0;
    ((long *)start)[2] = origin;
    return start;
}

/* not found in betarun.h */
int AlloORR(long origin, long proto, long obj, long off, long range,long SP) {
    long start,i; 
/*    printf("AlloORR: range=%i, off=%i\n",range,off);*/
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
int AlloORRC(long origin, long proto, long obj, long off, long range, long SP) {
    long start,i; 
/*    printf("AlloORRC: range=%i, off=%i\n",range,off);*/
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
   /* printf("BetaText: %s\n", (char *)&betaTextArea[start+1]); */
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

long CopyCT(char * txt){
   long newRep,range,i;
   range = strlen(txt);
  /*  printf("CopyCT: range=%i  %s\n",range,txt);*/
   newRep = AllocHeap(4 + (range / 4) + 1);
   ((long *)newRep)[0] = -6; 
   ((long *)newRep)[1] = 0;
   ((long *)newRep)[2] = 0;
   ((long *)newRep)[3]= range;
   for (i=0; i < range; i++)
       ((char *)newRep)[16+i] = txt[i];
   ((char*)newRep)[16+range]=0;
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
long CopyCPP(long *struc, long *dummy) {
  long start,entry,res;
  /*printf("\nCopyCPP: struc=0x%x, dummy=0x%x, proto=0x%x\n",struc,dummy,struc[3]);*/
   if (struc[0] != -3) {
     printf("\n***CopyCPP: using dummy! Should NOT happen!\n"); 
     struc = dummy;
   }
   if (struc[0] != -3) printf("\n*** CopyCPP: illegal struc parameter\n");
   entry= ((long *)struc[3])[5];
   start = &CallBack[cbTop];
   /* printf("\nentry=%x\n",entry); */

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

   /* printf("\nCopyCPP, funcPtr=%x\n",funcPtr);*/
   res=_flush_cache((long *)&CallBack[0],(long)&CallBack[cbTop+1],BCACHE);
   return(long)&CallBack[cbTop-5];
}

/* NOT in official betarun */
long AlloSICB(long *CallBackPtr,long SP){
   long start;
   start = AlloSI(0,CallBackPtr[0],SP);  
   return start;
 }


dumpObj(char *s, long * sObj){
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
   /*printf("CopyT; obj=%x, off=%i, txt=%s\n", (long)obj, off, txt);*/
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
  /*printf("CopyVR: sourceRep=0x%x, destObj=%x, off=%i, range=%i\n", sourceRep, destObj,off,range);*/
  repObj = AllocHeap(96); /* OBS proper size must be used */
  
  /*if (((long *)repObj)[0] = -8) printf("txt=%x\n",((char *)sourceRep)[16]);*/
  
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

/* NOT implemented !! */
void ThisS(long *this){}

void Qua(long *dstQuaProto, long *theCell, long *dstQuaOrigin, long SP) {
}

void ChkRA(long *theObjHandle, long dummy, long IOAbot, long IOAused) {
/*printf("\nChkRA  obj=0x%x, IOAbot=0x%x, IOA=%i\n",theObjHandle,IOAbot,IOAused);
*/

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
   while (proto != 0) {
      mEntry = proto[(proto[mEntryOff] / 4) & 0xffff];
      /* printf("findMentry:0x%x\n",mEntry); */
      PCdist = PC - mEntry;
      if ((PCdist > 0) && (PCdist < minPC)) {
         minPC = PCdist;
         theMentry = mEntry;
      };
      proto = super(proto);
   };
   /* printf("findMentry min:0x%x\n",theMentry);*/
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
   codeStart = (long *) findMentry(proto,LSC);
   SPoff = (codeStart[SPinstOff] & 0xffff) | 0xffff0000; 
   SPoff = - SPoff;
   SPx = SP + SPoff;
   LSCglobal= ((long *)SPx)[-1];
   caller =  (long *)((long *)SPx)[-2];
   /*  printf("Dyn: SPoff=%i, caller=0x%x\n\n",SPoff,caller);  */
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

  /*printf("\nExO: jumpAdr=0x%x, exitObj=0x%x, PC=0x%x, this=0x%x\n",
        jumpAdr,exitObj,PC,this);*/
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

void Terminated(){   
  FatalErr(4);
}



/* NO RA and SPx in official betarun */
void Att(ref(Object) this, struct Component * comp, long RA, long SPx)
{ long first;
  long * compObj;
  long * compProto;
  void (* compAdr)(long a0,long * a1);
  long SPy,SPz,SPsize;
  int isFirst,i;
  long * sObj;
  long * topObj;

  SPy = GetSP();
  if (ActiveComponent != 0) {
    ActiveComponent->CallerLSC = RA;
    /* ActiveComponent->SPx = SPx;*/
    /* ActiveComponent->SPy = SPy;*/
    SPtop = SPtop + 1;
    SPxStack[SPtop] = SPx;
    SPyStack[SPtop] = SPy;
  } else { printf("ActiveComponet == 0 \n");};
  /* printf("\nAtt: comp=0x%x, this=0x%x, SPx=0x%x, SPy=0x%x\n"
	 ,(long)comp,(long)this,SPx,SPy); */
  /* dumpObj("Attach comp",comp); */
   
  topObj = comp->CallerObj; 
  compAdr = (void (*)(long,long *)) comp->CallerLSC;
  /* printf("\ncompAdr=0x%x\n",compAdr);*/
  if ((long)compAdr == -1) Terminated(); 

  isFirst = compAdr == 0;

  compObj = comp->Body;
  /*printf("\nBody=0x%x\n",compObj);*/

  compProto =  (long *) compObj[0];
  /* printf("\nCompProto=0x%x\n",compProto);*/

  if (isFirst) { 
    /* printf("***First\n");*/
    compAdr = (void (*)(long,long *)) compProto[-1];
    topObj = compObj;
   } else {
     /* pack current component to stack object */
     sObj = comp->StackObj;
     dumpObj("Attach stackObj",sObj);
     SPsize = ((long *)sObj)[2];

     SPz = SPy - SPsize; 
     for (i=0; i < SPsize / 4; i++)
         ((long *)SPz)[i] = sObj[3 + i];
   }
  
  /* if (ActiveComponent != 0) ActiveComponent->StackObj =  -1; */

  comp->CallerComp = ActiveComponent;
  comp->CallerObj = this;
  comp->CallerLSC = -1; 
  /* printf("\ndo attach\n");*/
  ActiveComponent = comp;

   /* Execute comp.
    * 1st call starts at M111FOO; a0=dummy, a1=ca; i.e a0 is not used
    * in this situation, since M111FOO adjusts SP as usual.
    * Subsequent calls after Attach; a0=SPz, a1=ca;
    */
  compAdr(SPz,topObj);

  /* we get here when the component terminates; we must return a proper
   * a0 and a1, since th and SP are set after Att
   */
  comp->CallerLSC = -1; /* (long) &Terminated;*/
  compAdr = (void (*)(long,long *))RA;
  compAdr(SPx,(long *)this);
}

/* No RA and SPz in official betarun.h */
void Susp(long * this, long oldSP, long RA, long SPz){
   long first;
   struct Component * returnComp;
   long * returnObj;
   void (* callingRA)(long SP , long * this);
   long SPx, SPy;
   int i;
   long * sObj; 
   /* printf("\n*** Suspend: 0x%x\n",ActiveComponent);*/

   returnComp = (struct Component*) ActiveComponent->CallerComp;
   returnObj = ActiveComponent->CallerObj;

   callingRA = returnComp->CallerLSC;
   /* SPx = returnComp->SPx;   */
   /* SPy = returnComp->SPy;   */
   SPx = SPxStack[SPtop];
   SPy = SPyStack[SPtop];
   SPtop = SPtop - 1;

   ActiveComponent->CallerObj = this;
   ActiveComponent->CallerLSC =  RA;

   
   /* pack stack SPz - SPy to  activeCompSP*/
   sObj = AlloSO(SPy - SPz);

   /* copy SPz[0],  SPz[1], ... , SPz[(SPy - SPz - 4) / 4] = SPy[-1] */
   for (i=0;  i < (SPy - SPz) / 4; i++)
       sObj[3+i] = ((long *)SPz)[0 + i];

   dumpObj("Suspend stackObj",sObj);
   ActiveComponent->StackObj = sObj;
   dumpObj("Suspend active", (long *)ActiveComponent);
   /* return to returnComp at RA */
   /* thisObj must be set - perhaps it is already set, since
      R30 is saved over a call? No - is smashed by BETA code, of course!*/

   ActiveComponent = ActiveComponent->CallerComp;
   /* ActiveComponent->CallerComp = 0;*/
   callingRA(SPx,returnObj);
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
   printf("T1BETAENV = 0x%x\n",T1BETAENVadr);

}

void main() {
  long a0;
   char ch;
   void (* M1BETAENV)(long a0,long * a1);
   printf("Starting simple betarun!\n");
   betaTextArea = (char *)malloc(1000);
   /*   heapTop = (long *) malloc(100000);*/
	     printf("SetProtos: %x\n",SetProtos);
   BETA_main();
   ActiveComponent = (struct Component *)AlloC(0,T1BETAENVadr,GetSP());
   topObj = ActiveComponent->Body;

   /*G1BETAENV(0,topObj);*/
   M1BETAENV =  (void (*)(long,long *)) T1BETAENVadr[mainEntry];
   M1BETAENV(0,topObj);
   printf("End simple betarun\n");
 }

void AttBC(){}

void BetaExit(){}
void FailureExit(){}
void Argc(){}
void Argv(){}
void DoGC(){}

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

      a = dyn(a,SPglobal,LSCglobal);

    }
}

void doGC() {printf("\n**** doGC ******\n"); }

double i2f(long n) { return (double)n; }
