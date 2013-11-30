#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <windows.h>
#include <string.h>

//#define TRACE
//#define EVENT

#define MAX_THREADS 5

/* Format of ObjDescs
   0: -xBeta--
   8: image size
   12: textDescNo
   16: strucRefDescNo
   20: indexOfStringtable
   24: no of Object descriptors
   26: ObjDesc1
   ...: ...
   
   Format of ObjDesc:
   0: index of name in stringtable
   2: descNo
   6: topDescNo
   10: vSize - size of value fields
   14: rSize - size of reference fields
   18: originOff
   20: procE
   22: alloE
   24: enterE
   26: doE
   28: exitE
   30: labStart = 30 + 12 + vdtTable.range * 4
   34: literalStart
   38: BCstart
   42: vdtTable
   labStart: ...
   : ...
   literalStart: ...
   : ...
   BCstart: size of BC
   : bytecodes ...
*/
enum{
  imageSize_index = 8,
    textDescNo_index = 12,
    strucRefDescNo_index = 16,
    stringTable_index = 20,
    noOfObjDesc_index = 24,
    };

enum {
  name_index = 0,
  descNo_index = 2,
  topDescNo_index = 6,
  vSize_index = 10,
  rSize_index = 14,
  originOff_index = 18,
  procE_index = 20,
  alloE_index = 22,
  enterE_index = 24,
  doE_index = 26,
  exitE_index = 28,
  labIndex = 30,
  literal_index = 34,
  BC_index = 38,
  vdtTable_index = 42,
};


enum {
  start_event = 1,
  alloc_event = 2,
  do_event = 3,
  doExit_event = 4,
  rtn_event = 5,
  resume_event = 6,
  suspend_event = 7,
  break_event = 8,
  vPush_event = 9,
  rPushEvent = 10,
  store_event = 11,
  rStore_event = 12,
  binOp_event =13,
  unOp_event = 14,
  jmpGT_event= 15,
  pop_event = 16,
  error_event = 17,
  stop_event = 18
};

// opcodes
enum {
  pushthis  = 1,
  pushC = 2,
  push = 3,
  rpush = 4,
  pushg = 5,
  rpushg = 6,
  xpush = 7,
  xpushg = 8,     
  store = 9,
  rstore = 10,
  storeg = 11,
  rstoreg =12,    
  xstore = 13,
  xstoreg = 14,     
  _double = 15,          
  rdouble = 16,
  rtn = 17,
  mvStack = 18,
  stop = 19,
  susp = 20,
  call = 21,
  alloc = 22,
  doExit = 24,
  rtnExit = 25,
  prim = 26,     
  jmp = 27,
  jmpFalse = 28,
  jmpGT = 30,     
  pushNone = 31,
  doSuper = 34 ,
  innerx = 35 ,
  rtnInner = 36 ,
  innerExit = 37 ,
  sendv = 38, 
  send = 39 ,     
  newVrep = 40 ,
  jmpTrue = 41 ,
  pushText = 42 ,
  exeAlloc = 43 ,
  rtnc = 44 ,
  rpop = 45 ,
  vpop= 46,
  eq = 50,
  lt = 51,
  le = 52,
  gt = 53,
  ge = 54,
  ne = 55,
  req = 56,
  rne = 57,
  seq = 58,
  sne = 59,

  plus = 61,
  minus = 62,
  
  orr = 63,
  xorr = 64 ,
  nott = 65 ,
  
  mult = 66 ,
  rdiv = 67 ,
  idiv = 68 ,
  modd = 69,
  andd =  70,
  
  uminus = 71,
  pushc2 = 72,
  allocIndexed = 73 ,
  saveBETAworld = 74 ,
  mkStrucRef = 75 ,
  mkVirtualStrucRef = 76 ,
  _allocFromStrucRefObj = 77 ,
  rtnEvent = 78 ,
  _break = 79,
  mkObjStrucRef = 80,
};

void runTimeError(char *msg){
  printf("\n\n*** Run-time error: %s\n\n",msg);
  exit(-1);
}

unsigned char heap[10]; int heapTop; // not in use

HANDLE allocMutex;

void *heapAlloc(int size) {
  void *obj; char S[50];
  if (true) { 
    switch(WaitForSingleObject(allocMutex,INFINITE)) {
    case WAIT_OBJECT_0:
      break;
    default:
      runTimeError("Wait failure: allocMutex");
    } ;
    obj = malloc(size);
    if (!ReleaseSemaphore(allocMutex,1,NULL)) runTimeError("ReleaseSemaphoreError: allocMutex");
    if (obj == 0) {
      sprintf(S,"malloc failed; size: %i",size);
      runTimeError(S);
    }
  }else {
    void *obj = (void *)&heap[heapTop];
    heapTop = heapTop + size;
    if (heapTop > 10000000) {
      printf("\n\n*** Heapoverflow");
      stop;
    };
  };
  return obj;
}

void releaseHeap(void *S){
  free(S);
}

typedef unsigned char * ObjDesc;

ObjDesc descs;

unsigned char * stringTable;

// NB! The byte order is inconsistent - sometimes big somtimes little endian
int getInt2(int inx) {
  return descs[inx] * 256 + descs[inx + 1];
};

int getInt4(int inx){
  return descs[inx+3] * 256 * 256 * 256 + descs[inx + 2] * 256 * 256 
    + descs[inx + 1] * 256 + descs[inx];
}; 

int desc_getInt2(ObjDesc desc,int inx) {
  return desc[inx] * 256 + desc[inx + 1];
};

int desc_getInt4(ObjDesc desc,int inx){
  return desc[inx+3] * 256 * 256 * 256 + desc[inx + 2] * 256 * 256 
    + desc[inx + 1] * 256 + desc[inx];
}; 

int getImageSize(){
  return getInt4(imageSize_index);
}

int getTextDescNo(){
  return getInt4(textDescNo_index);
};

int getStrucRefDescNo(){
  return getInt4(strucRefDescNo_index);
};

int getStringTableIndex(){
  return getInt4(stringTable_index);
};

char *getString(int inx){
  //fprintf(trace,"inx: %i %c %s",inx, stringTable[inx], (char *)stringTable+inx);
  return (char *) stringTable + inx + 3;
}

ObjDesc getDesc(int descNo) {
  // returns start address of desctiptor descNo
  int inx = getInt2(noOfObjDesc_index + 4 + (descNo - 1) * 2);
  //fprintf(trace,"descs: %i descNo %i descIndex: %i\n", descs, descNo, inx);
  if (inx > 0) {
    return descs + inx; }
  else 
    return 0;
}

int getBCtop(ObjDesc desc){
  int BCstart = desc_getInt4(desc,BC_index);
  // fprintf(trace,"getBCtop %i %i\n",BCstart,desc_getInt2(desc,BCstart));
  return desc_getInt2(desc,BCstart);
}
ObjDesc getByteCode(ObjDesc desc) {
  //return (ObjDesc) ((int) desc + getBcStart(desc) + BC_index + 2);
  int BCstart = desc_getInt4(desc,BC_index);
  // fprintf(trace,"getByteCode %i %i %i %i %i %i\n", BCstart
  //  ,desc[BCstart],desc[BCstart+1],desc[BCstart+2],desc[BCstart+3],desc[BCstart+4]);
  return (ObjDesc) desc + BCstart + 2;
}

typedef struct template {
  ObjDesc desc;
  int id;
  bool isObj;
  int vstack[16];  
  struct template *rstack[16];
  int vtop; int rtop;
  int lscStack[16];
  int lscTop;
  int lsc;
  struct template *rfields[32];
  int vfields[];
} template;

typedef struct Block {
  ObjDesc bc;  
  int glsc;
  int currentDescNo;
  template *thisModule,*thisObj,*thisStack,*top;
  int threadId;
  char *traceFile;
} Block;


int alloE(ObjDesc desc){ 
  //fprintf(trace,"alloE=%i",desc_getInt2(desc,alloE_index));
  return desc_getInt2(desc,alloE_index); 
}

int getAllocE(ObjDesc obj){
  //fprintf(trace,"\n*** AllocE %i\n",desc_getInt2(obj,alloE_index) -1);
  return desc_getInt2(obj,alloE_index) - 1;
}
int getEnterE(ObjDesc obj){
  return desc_getInt2(obj,enterE_index) - 1;
}
int getDoE(ObjDesc obj){
  //fprintf(trace,"\n***getDoE %i %i\n", obj, desc_getInt2(obj,doE_index));
  return desc_getInt2(obj,doE_index) - 1;
}
int getExitE(ObjDesc obj){
  return desc_getInt2(obj,exitE_index) - 1;
}
void dumpStringTable(FILE *trace) {
  int inx, StringsSize,i;
  inx = getStringTableIndex();
  StringsSize = getInt4(inx);
  i = 4;  
  i = inx + 4;
  fprintf(trace,"first; %s  :: ",stringTable + 4);
  for (i=4; i< StringsSize; i++) {
    int ch = descs[inx + i];
    if (ch == 0) { fprintf(trace," ");} else {fprintf(trace,"%c",ch);}
  }
  fprintf(trace,"\n");
};

void dumpString(FILE *trace, int inx) { //fprintf(trace,"dumpString %i\n",inx);
  int i,length = stringTable[4 + inx] + stringTable[4 + inx + 1];
  //fprintf(trace," %i:",length);
  for (i=0; i<length; i++) fprintf(trace,"%c",stringTable[4 + inx + 2 + i]);
}

void dumpCode(FILE *trace, ObjDesc desc){
  ObjDesc bc;
  int opCode,arg1,arg2,bcTop,glsc;
  int op1(){
    int V = bc[glsc]; 
    glsc = glsc + 1;
    return V;
  };
  int op2(){ 
    int V = bc[glsc] * 256 + bc[glsc + 1];
    glsc = glsc + 2;
    return V;
  };

  bc = getByteCode(desc);
  bcTop = getBCtop(desc);
  glsc = 0;

  while(glsc < bcTop) {
    if ((glsc + 1) == desc_getInt2(desc,procE_index)) fprintf(trace,"procE:\n");
    if ((glsc + 1) == alloE(desc)) fprintf(trace,"alloE:\n");
    if ((glsc + 1) == desc_getInt2(desc,enterE_index)) fprintf(trace,"enterE:\n");
    if ((glsc + 1) == desc_getInt2(desc,doE_index)) fprintf(trace,"doE:\n");
    if ((glsc + 1) == desc_getInt2(desc,exitE_index))fprintf(trace,"exitE:\n");

    fprintf(trace,"%i:\t",glsc);
    opCode = bc[glsc]; glsc = glsc + 1; 
    switch (opCode)
      {
      case pushthis:
	fprintf(trace,"pushthis ");
	break;
      case pushC: 
	arg1 = op1();
	fprintf(trace,"pushC %i", arg1);
	break;
      case push:
	fprintf(trace,"push %i",op1());
	break;
      case rpush:
	fprintf(trace,"rpush %i",op1());
	break;
      case pushg:
	fprintf(trace,"pushg %i",op1());
	break;
      case rpushg:
	fprintf(trace,"rpushg %i ", op1());
	break;
      case xpush:
	fprintf(trace,"xpush %i",op1());
	break;
      case xpushg:
	fprintf(trace,"xpushg %i",op1());
	break;
      case store:
	fprintf(trace,"store %i",op1());
     	break;
      case rstore:
	fprintf(trace,"rstore %i ",op1());
	break;
      case storeg:
	fprintf(trace,"storeg %i ",op1());
	break;
      case rstoreg:   
	fprintf(trace,"rstoreg %i ",op1());
	break; 
      case xstore:
	fprintf(trace,"xstore %i ",op1());
	break;
      case xstoreg:
	fprintf(trace,"xstoreg %i ",op1());
	break;
      case _double:
	fprintf(trace,"double");
	break;
      case rdouble:
	fprintf(trace,"rdouble");
	break;
      case rtn:
	fprintf(trace,"rtn %c ",op1());
	break;
      case mvStack:
	fprintf(trace,"mvStack");
	break;
      case call:
	arg1 = (char) op1();
	fprintf(trace,"call %c ",arg1);
	break;
      case susp:
	fprintf(trace,"susp");
	break;
      case alloc:
	arg1 = op2();
	arg2 = op1();
	fprintf(trace,"alloc %i %i",arg1,arg2);
	break;
      case doExit:
	fprintf(trace,"doExit");
	break;
      case rtnExit:
	fprintf(trace,"rtnExit");
	break;
      case prim:
	arg1 = op1();
	fprintf(trace,"prim %i ",arg1);
	switch (arg1){
	case 10: // attach 
	  fprintf(trace,"%c",op1());
	}
	break;
      case jmp:	
	fprintf(trace,"jmp %i",op2());
	break;
      case jmpFalse:
	fprintf(trace,"jmpFalse %i",op2());
	break;
      case jmpGT:
	fprintf(trace,"jmpGT %i",op2());
	break;
      case pushNone:
	fprintf(trace,"pushNone");
	break;
      case rtnEvent:
	fprintf(trace,"rtnEvent %i ",op1());
	break;
      case saveBETAworld:
	fprintf(trace,"saveBETAworld ");
	break;
      case doSuper:
	fprintf(trace,"doSuper %i",op2());
	break;
      case innerx:
	fprintf(trace,"innerx %i",op1());
	break;
      case rtnInner:
	fprintf(trace,"returnInner");
	break;
      case innerExit:
	fprintf(trace,"innerExit %i",op1());
	break;
      case sendv: 
	fprintf(trace,"sendv %i",op1());
	break;
      case send: 
	fprintf(trace,"send %i",op1());
	break;
      case newVrep:
	fprintf(trace,"newVrep");
	break;
      case jmpTrue:
	fprintf(trace,"jmpTrue %i",op2());
	break;
      case pushText:
	fprintf(trace,"pushText %i",op1());
	break;
      case exeAlloc:
	fprintf(trace,"exeAlloc %i",op2());
	break;
      case rtnc:
	fprintf(trace,"rtnC");
	break;
      case rpop:
	fprintf(trace,"rpop");
	break;
      case vpop:
	fprintf(trace,"vpop");
	break;
      case eq:
	fprintf(trace,"eq");
	break;
      case lt:
	fprintf(trace,"lt");
	break;
      case le:
	fprintf(trace,"le");
	break;
      case gt:
	fprintf(trace,"gt");
	break;
      case ge:
	fprintf(trace,"ge");
	break;
      case ne:
	fprintf(trace,"ne");
	break;
      case req:
	fprintf(trace,"req");
	break;
      case rne:
	fprintf(trace,"rne");
	break;
      case seq:
	fprintf(trace,"seq");
	break;
      case sne:
	fprintf(trace,"sne");
	break;
      case plus: 
	fprintf(trace,"plus");
	break;
      case minus:
	fprintf(trace,"minus");
	break;
      case orr: 
	fprintf(trace,"orr");
	break;
      case xorr:
	fprintf(trace,"xorr");
	break;
      case nott:
	fprintf(trace,"nott");
	break;
      case mult:
	fprintf(trace,"mult");
	break;
      case rdiv:
	fprintf(trace,"rdiv");
	break;
      case idiv:
	fprintf(trace,"idiv");	
	break;
      case modd:
	fprintf(trace,"modd");
	break;
      case andd:
	fprintf(trace,"andd");
	break;
      case uminus:
	fprintf(trace,"ne");
	break;
      case pushc2:
	fprintf(trace,"pushc2 %i",op2());
	break;
      case allocIndexed:
	arg1 = op2();
	arg2 = op1();
	fprintf(trace,"allocIndexed %i %i",arg1,arg2);
	break;
      case mkStrucRef: 
	fprintf(trace,"mkStrucRef");
	break;
      case mkObjStrucRef: 
	fprintf(trace,"mkObjStrucRef");
	break;
      case mkVirtualStrucRef:
	fprintf(trace,"mkVirtualStrucRef");
	break;
      case _allocFromStrucRefObj:
	fprintf(trace,"allocFromStrucRefObj");
	break;
      case _break:
	fprintf(trace,"break %i %i",op1(),op2());
	break;
      case stop: 
	fprintf(trace,"stop ");
	break;
      default:
	fprintf(trace,"Op: %i ",bc[glsc - 1]);
	break;
      }
    fprintf(trace,"\n");
  };
  fprintf(trace,"\n");
}

int descNo(ObjDesc desc){
  return desc_getInt4(desc,descNo_index);
}

int vSize(ObjDesc desc){
  return desc_getInt4(desc,vSize_index);
}

int rSize(ObjDesc desc){
  return desc_getInt4(desc,rSize_index);
}

void dumpDesc(FILE *trace, int xdescNo) {
  ObjDesc desc;  
  if ((desc = getDesc(xdescNo)) > 0 ) {
    fprintf(trace,"\nClass ");
    //int i;
    //for (i=0; i <10; i++) fprintf(trace,"%i ",desc[i]);
    //fprintf(trace,"\n");
    //dumpString(getInt2(desc + 0 ));
    //    dumpString(desc[0] * 256 + desc[1]);
    //dumpString(desc_getInt2(desc,0));
    int VS = vSize(desc);
    int RS = rSize(desc);
    fprintf(trace,"%s",getString(desc_getInt2(desc,0)));
    fprintf(trace," descNo:%i vSize:%i rSize:%i originOff:%i\n"
	    ,descNo(desc),VS,RS,desc_getInt2(desc,originOff_index));
    if (VS >= 16) runTimeError("vSize too big");
    if (RS >= 32) runTimeError("rSize too big");
    dumpCode(trace,desc);
  }
}

void dumpDescriptors(FILE *trace) {
  int descNo,noOfDescs = getInt4(noOfObjDesc_index);
  fprintf(trace,"Descriptors %i \n",noOfDescs);
  for (descNo=1; descNo <= noOfDescs; descNo++) dumpDesc(trace,descNo);
}

void dump_image(FILE * trace) {
  fprintf(trace,"%c%c%c%c%c%c%c%c\n"
	  ,descs[0],descs[1],descs[2],descs[3],descs[4],descs[5],descs[6],descs[7]);
  fprintf(trace,"StringTableIndex: %i\n",getStringTableIndex());
  dumpStringTable(trace);
  dumpDescriptors(trace);
}

typedef struct Event {
  int type;
  template *caller,*thisObj,*org;
  int isObj;
  int descNo;
  int bcPos;
} Event;

int hSize = 0;

template *allocTemplate(int ID,int descNo,bool isObj, int vInxSize, int rInxSize){
  int i = sizeof(template) + (16 + vInxSize) * sizeof(int);// + 1000;
  hSize = hSize + i;
  //fprintf(trace,"allocTemplate(%i,%i) ",i, hSize);
  template *obj = (template*)heapAlloc(i);
  //fprintf(trace,"template allocated: %i\n",vInxSize);
  obj->desc = getDesc(descNo);
  obj->id = ID;
  obj->isObj = isObj;
  obj->vtop = 0;
  obj->rtop = 0;
  obj->lscTop = -1;
  obj->lsc = 0;
  for (i = 0; i < 16; i++) obj->vfields[i] = 0; 
  for (i = 0; i < 24; i++) obj->rfields[i] = 0;
  // bc 
  return obj;
}

char * nameOf(template *obj){
  if (obj == 0) return "none";
  ObjDesc desc = obj->desc;
  int i,inx = desc_getInt2(desc,0);
  return getString(inx);
}

int threadStubDescNo; // perhaps a hack?
void dumpStackX(template *obj);

void runTimeErrorX(char *msg, template *thisObj, int glsc){
 
  printf("\n\n*** Run-time error: %s\n\nObject: %s(%i) at: %i\n",msg,nameOf(thisObj),descNo(thisObj->desc),glsc);

  dumpStackX(thisObj);

  exit(-1);
}


void dumpStackX(template *obj){
  template *X, *Y;
  if (X != NULL) {
    X = obj->rstack[1];
    Y = obj->rstack[2];
    printf("Caller: %s(%i) at: %i %s thisStack: %s\n"
	   ,nameOf(X),topOfLsc(X,-1),topOfLsc(X,0),nameOf(Y));
    if (descNo(X->desc) != threadStubDescNo) dumpStackX(X);
  }
}

int topDescNo(template *obj){ return desc_getInt4(obj->desc,topDescNo_index); }

template *myCorigin(template *obj){ 
  int inx;
  inx = desc_getInt2(obj->desc,originOff_index);
  template * origin = 0;
  if (inx > 0) origin = obj->rfields[inx];
  return origin;
}


ObjDesc myCode(template *obj){
  return getByteCode(obj->desc);
}

ObjDesc mySuperCode(template *obj){
  return(myCode(obj));
}

ObjDesc codeFromDescNo(int descNo){
  ObjDesc D = getByteCode(getDesc(descNo));
  return D;
}

int xlabs(int descNo,int labNo){
  ObjDesc desc = getDesc(descNo);
  int labStart = desc_getInt4(desc,labIndex);
  //int i;
  //for (i = 0; i < 50; i++) fprintf(trace," %i: %i\n",i,desc[labStart + i] );
  int lab = desc_getInt2(desc,labStart + (labNo - 1) * 2);
  //fprintf(trace,"xlabs descNo: %i labNo: %i lab: %i\n",descNo,labNo,lab);
  return lab;
}

int vdtTable(FILE *trace,template *obj,int inx){
#ifdef TRACE
  fprintf(trace," vdtTable[%i] = %i "
	  ,inx,desc_getInt4(obj->desc,vdtTable_index + (inx -1 ) * 4));
#endif
  return desc_getInt4(obj->desc,vdtTable_index + (inx -1 ) * 4);
}

int getLiteralStart(template *obj){
  return desc_getInt4(obj->desc,literal_index);
};

int getLiteral(template *obj,int inx){
  int lit = desc_getInt2(obj->desc,getLiteralStart(obj) + (inx-1) *2);
  //fprintf(trace,"getLiteral %i %i \n",inx,lit);
  return lit;
}

bool getIsObj(template *obj) {return obj->isObj; };

int getV(template *obj,int inx){ return obj->vfields[inx];};

template *getR(template *obj,int inx){ return obj->rfields[inx];};

void vPush(template *thisStack,int V){
  if ((thisStack->vtop = thisStack->vtop + 1) > 16 ) 
    runTimeErrorX("vstack overflow",thisStack,-1);
  thisStack->vstack[thisStack->vtop] = V;
}

void rPush(template *stack,template *R){
  //fprintf(trace,"\n*** rPush obj %i at %i \n",R->id,stack->rtop);
  if ((stack->rtop = stack->rtop + 1) > 16 ) runTimeErrorX("stack overflow",stack,-1);
  stack->rstack[stack->rtop] = R;
}

int vPop(template *thisStack){
  if ((thisStack->vtop = thisStack->vtop - 1) < -1) 
    runTimeErrorX("vstack underflow",thisStack,-1);
  return thisStack->vstack[thisStack->vtop + 1];
}

template *rPop(template *stack){
  //template *R = stack->rstack[stack->rtop];
  // fprintf(trace,"\n*** rPop obj %i from %i \n",R->id,stack->rtop);
  if ((stack->rtop = stack->rtop - 1) < -1) runTimeErrorX("rStack underflow",stack,-1);
  return stack->rstack[stack->rtop + 1];
}

void cSaveReturn(template *obj,int descNo, int lsc){
  //fprintf(trace,"\n***cSaveReturn in %s lscTop=%i:",nameOf(obj),obj->lscTop);
  //int i;
  //for (i=0; i < obj->lscTop; i++) fprintf(trace,"%i ",obj->lscStack[i]);
  //fprintf(trace,"\n");
  if ((obj->lscTop = obj->lscTop + 2) > 16) 
    runTimeErrorX("lsc stack overflow",obj,-1);
  obj->lscStack[obj->lscTop-1] = descNo;
  obj->lscStack[obj->lscTop] = lsc;
}

int cMyLscTop(template *obj) { return obj->lscTop; };

int topOfLsc(template *obj,int inx ){ return obj->lscStack[obj->lscTop + inx];};

int cRestoreReturn(template * obj){
  //fprintf(trace,"\n***cRestoreReturn: %i %s\n",obj->lscTop,nameOf(obj));
  if (obj->lscTop < 0) runTimeErrorX("\n**** ERROR:  lscStack underflow\n",obj,-1);
  int V = obj->lscStack[obj->lscTop];
  obj->lscTop = obj->lscTop - 1;
  return V;
}

HANDLE eventReady,eventTaken,eventProcessed;
Event *theEvent = NULL;

void *mkEvent(int type,template *caller,template *thisObj,template *org
	       ,bool isObj,int currentDescNo,int bcPos){ 
  //printf("\nmkEvent: %i %i %i\n",type,hSize,sizeof(Event));
  hSize = hSize + sizeof(Event);
  Event *E = (Event *)heapAlloc(sizeof(Event));
  E->type = type;
  E->caller = caller;
  E->thisObj = thisObj;
  E->org = org;
  E->isObj = (int) isObj;
  E->descNo = currentDescNo;
  E->bcPos = bcPos;
  //printf("\nmkEvent: %i",E->type);

  //if (type == stop_event) 
  {
    int res = WaitForSingleObject(eventTaken,INFINITE);
    switch (res) {
    case WAIT_OBJECT_0: 
      theEvent = E; 
      break;      
    default: 
      runTimeError("Wait failiure for eventTaken");
    };
    if (!ReleaseSemaphore(eventReady,1,NULL)) runTimeError("ReleaseSemaphoreError: eventReady");
    switch(WaitForSingleObject(eventProcessed,INFINITE)) {
    case WAIT_OBJECT_0:
      break;
    default:
      runTimeError("Wait failure: eventProcessed");
    } 
  };
  return E;  
};

void *mkAllocEvent(int type,template *caller,template *thisObj,template *org
		    ,bool isObj,int currentDescNo,int bcPos,bool isIndexed){
  mkEvent(type,caller,thisObj,org,isObj,currentDescNo,bcPos);
};

int descNoOf(template * obj){
  return desc_getInt4(obj->desc,descNo_index);
}

void dumpStack(FILE *trace,template *Z){
  int i;
  fprintf(trace,"\[");
  for (i=0; i < Z->rtop; i++)
    fprintf(trace,"%s ",nameOf(Z->rstack[i + 1]));
  fprintf(trace,"]\n");
}
void dumpSwapped(FILE *trace,template *X, template *Y,template *Z){
  fprintf(trace,"\nswapped: %s R[1]=%s, R[2]=%s  %s %s["
	  ,nameOf(X),nameOf(X->rstack[1]),nameOf(X->rstack[2])
	  ,nameOf(Y),nameOf(Z));
  int i;
  for (i=0; i < Z->rtop; i++)
    fprintf(trace,"%s ",nameOf(Z->rstack[i + 1]));
  fprintf(trace,"]\n");
}

void rswap(template *obj, template **R, template **S){
  //fprintf(trace,"***rswap %s %s %i\n",nameOf(*R),nameOf(*S),obj->rtop);
  template *Rx = obj->rstack[1];
  template *Sx = obj->rstack[2];
  obj->rstack[1] = *R;
  obj->rstack[2] = *S;
  *R = Rx;
  *S = Sx;
  if (obj->rtop == 0) obj->rtop = 2; // first call - we push 2 values
  if (*R == 0) { printf("*R == 0\n"); obj->rtop = 0;} // 
}



DWORD WINAPI interpreter(LPVOID B);

Event *init_interpreter(ObjDesc descs_a, int mainDescNo) {
  FILE *trace;
  Block *thisBlock;

  void allocMain(int descNo){ 
    thisBlock->thisModule = allocTemplate(1000,descNo,true,0,0);
    thisBlock->thisObj = thisBlock->thisModule;
    thisBlock->thisStack = thisBlock->thisModule;
  };

  threadStubDescNo = mainDescNo + 2;

  trace = fopen("code.s","w");
  setbuf(trace, NULL);
  descs = descs_a; // this is necessary for getImageSize() below
  // we must copy from Beta memory to avoid GC problems
  allocMutex = CreateSemaphore(NULL,1,1,NULL);

  int imageSize = getImageSize();
  thisBlock = (Block *)heapAlloc(sizeof(Block));
  descs = heapAlloc(imageSize);
  memcpy(descs,descs_a,imageSize); 
  thisBlock->bc = descs;

  fprintf(trace,"C interpreter: mainDescNo: %i imageSize: %i\n",mainDescNo,imageSize);
  //int i;
  //  for (i=0; i < mainDescNo; i++) fprintf(trace,"%i: %i\n",i,descs[i]);
  fprintf(trace,"Main desc index: %i\n", (int)getDesc(mainDescNo));

  allocMain(mainDescNo);
  thisBlock->bc = getByteCode(getDesc(mainDescNo));
  thisBlock->currentDescNo = mainDescNo;
  stringTable = descs + getStringTableIndex();
  dump_image(trace);
  thisBlock->glsc = 0; 
  thisBlock->threadId = 0;
  thisBlock->traceFile = "trace.s";
  fprintf(trace,"**** Execute:\n\n");

  eventReady = CreateSemaphore(NULL,0,1,NULL);
  eventTaken = CreateSemaphore(NULL,1,1,NULL);
  eventProcessed = CreateSemaphore(NULL,0,1,NULL);

  CreateThread(NULL,0,interpreter,(LPVOID)thisBlock,0,0);
}

Event *getEvent(bool first){
  Event *E;
  DWORD dwWaitResult; 
  //printf("\n***run_interpreter");
  if (!first) {
    if (!ReleaseSemaphore(eventProcessed,1,NULL)){ 
      printf("Errorcode: %i",GetLastError());
      runTimeError("ReleaseSemaphoreError: eventProcessed");
    };
  }
  dwWaitResult = WaitForSingleObject(eventReady,INFINITE);
  //printf("\nGot mutex\n");
  switch (dwWaitResult) 
    {
    case WAIT_OBJECT_0:         
      E = theEvent;  
      theEvent = NULL;
      break;    
    default: 
      runTimeError("Wait failiure for waitEvent");
    };
  if (!ReleaseSemaphore(eventTaken,1,NULL))
    runTimeError("ReleaseSemaphoreError: eventTaken");
  return E;
}

DWORD WINAPI interpreter(LPVOID B){;
  Block *thisBlock = (Block *)B;
  int threadId = thisBlock->threadId;
  int ID = 1000;
  int newId() { 
    ID = ID + 4; 
    // printf("\nID:%i %i",threadId,ID + threadId); 
    return ID + threadId;
  }
  HANDLE  hThreadArray[MAX_THREADS];
  int threadNo = 0;
  bool hasThreads = false;

  printf("\n***C interpreter\n");
  FILE * trace;
  trace = fopen(thisBlock->traceFile,"w");
  setbuf(trace, NULL);
  template *enablee = 0;
  int suspendEnabled = 0;
  int timeToSuspend = 0;
  ObjDesc bc = thisBlock->bc;
  int glsc = thisBlock->glsc;
  int currentDescNo = thisBlock->currentDescNo;
  template *thisModule,*thisObj,*thisStack, *callee;

  int op1(){
    int V = bc[glsc]; 
    glsc = glsc + 1;
    return V;
  };
  int op2(){ 
    int V = bc[glsc] * 256 + bc[glsc + 1];
    glsc = glsc + 2;
    return V;
  };

  Event *allocObj(template *origin,int descNo,bool isObj,int vInxSize,int rInxSize){
#ifdef TRACE
    fprintf(trace,"FROM %s(%i,%i,%i) ",nameOf(thisObj),currentDescNo,glsc,bc);
#endif
    callee = allocTemplate(newId(),descNo,isObj,vInxSize,rInxSize);
#ifdef TRACE
    fprintf(trace,"callee: %s %i ",nameOf(callee),callee);
#endif
    template *Y;
    Y = thisObj;
    rPush(callee,thisObj);
    rPush(callee,thisStack);
    rPush(callee,origin);
    cSaveReturn(thisObj,currentDescNo,glsc);
    currentDescNo = descNo;
    thisStack = callee;
    thisObj = thisStack;
    bc = (ObjDesc) myCode(thisObj);
    glsc = getAllocE(thisObj->desc);
#ifdef TRACE
    fprintf(trace,"ALLOC %s(%i,%i,%i,%i)\n"
	    ,nameOf(thisObj),descNo,glsc,(int)thisObj,bc);
#endif
    mkAllocEvent(alloc_event,Y,thisObj,origin,isObj,currentDescNo,glsc,false);
  };

  void allocIndexedObj(template * origin, int descNo,bool isObj, int dinx, int rangee){ 
#ifdef TRACE
    fprintf(trace,"allocIndexedObj(%i,%i) ",dinx,rangee);
#endif
    allocObj(origin,descNo,isObj,rangee,0);
    thisObj->vfields[dinx] = rangee; 
  };

  void allocStrucRefObj(template *origin,int inx, bool isVirtual){
#ifdef TRACE
    fprintf(trace,"***allocStrucRefObj origin: %s inx:%i \n",nameOf(origin),inx);
#endif
    template * X = allocTemplate(newId(),getStrucRefDescNo(),0,0,0);
    if (isVirtual) inx = vdtTable(trace,origin,inx);
    X->vfields[1] = inx;
    X->rfields[2] = origin;
    rPush(thisStack,X);
  };
  
  void allocFromStrucRefObj(template *obj){
#ifdef TRACE
    fprintf(trace,"***allocFromStrucRefObj %s : ", nameOf(obj));
#endif
    allocObj(obj->rfields[2],obj->vfields[1],0,0,0);
  };
  
  void allocTextObj(int litInx){
    // literals[litInx] = length
    template *origin = 0; // FIX - in beta impl., the text object is used as its own origin
    int dinx,rangee,i;
    dinx = 2; // start of repetition
    rangee = getLiteral(thisObj,litInx);
    template *X = thisObj;
    
    allocIndexedObj(origin,getTextDescNo(),1,dinx,rangee);
    thisObj->vfields[1] = rangee; // pos = rangee
    for (i = 0; i < rangee; i++) {
      char ch = getLiteral(X, litInx + i + 1);
      thisObj->vfields[3 + i] = ch;
      // fprintf(trace, "Lit %c",ch);
    }
    // fprintf(trace," %i %i %i %i \n"
    //,thisObj->vfields[0],thisObj->vfields[1],thisObj->vfields[2],thisObj->vfields[3]);
  }

  Event *doCall(bool withEnablingSuspend){
    int arg1;
    template *Y;
    arg1 = (char) op1();
#ifdef TRACE
    fprintf(trace,"call %c ",arg1);
#endif
    callee = rPop(thisStack);
#ifdef TRACE
    fprintf(trace,"FROM %s(%i,%i,%i) ",nameOf(thisObj),currentDescNo,glsc,bc);
#endif
    if (withEnablingSuspend) enablee = callee;
    cSaveReturn(thisObj,currentDescNo,glsc);
    if (callee->rtop == 0) { 
      Y = thisObj;
      rPush(callee,thisObj); 
      rPush(callee,thisStack);
      thisObj = callee;
#ifdef TRACE
      fprintf(trace,"TO %s",nameOf(callee));
#endif
      switch (arg1)
	{
	case 'N':
	  currentDescNo = descNoOf(thisObj);
	  bc = myCode(thisObj);
	  glsc = getEnterE(thisObj->desc);
#ifdef TRACE
	  fprintf(trace,"(%i,%i,%i) N\n",currentDescNo,glsc,bc);
#endif
	  break;
	case 'D':
	  arg1 = topDescNo(thisObj);
	  currentDescNo = arg1;
	  bc = codeFromDescNo(arg1);
	  glsc = getDoE(getDesc(arg1));
#ifdef TRACE
	  fprintf(trace,"D(%i,%i,%s) ",currentDescNo,glsc,nameOf(thisStack));
	  dumpStack(trace,thisStack);
#endif
#ifdef EVENT
	  mkEvent(do_event,Y,thisObj,myCorigin(thisObj),false,currentDescNo,glsc); // withEnablingSuspend
#endif
	  break;
	case 'X':
	  arg1 = topDescNo(thisObj);
	  currentDescNo = arg1;
	  //dumpDesc(arg1);
	  bc = codeFromDescNo(arg1);
	  glsc = getExitE(getDesc(arg1));
#ifdef TRACE
	  fprintf(trace,"(%i,%i,%i) X\n",arg1,glsc,bc);
#endif
	  break;
	}}
    else {
      switch (arg1)
	{
	case 'N': // same as for callN
	  rPush(callee,thisObj);
	  rPush(callee,thisStack);
	  thisObj = callee;
	  currentDescNo = descNoOf(thisObj);
	  bc = codeFromDescNo(currentDescNo);
	  glsc = getEnterE(getDesc(currentDescNo));
#ifdef TRACE
	  fprintf(trace, "resumeN %s(%i,%i)\n",nameOf(callee),currentDescNo,glsc);
#endif
	  break;
	case 'D':
#ifdef TRACE
	  fprintf(trace, "resumeD %s ",nameOf(callee));
	  dumpSwapped(trace,callee,thisObj,thisStack);
#endif
	  rswap(callee,&thisObj,&thisStack);
#ifdef TRACE
	  dumpSwapped(trace,callee,thisObj,thisStack);
	  if (thisStack != thisObj) { // external suspend?
	    fprintf(trace,"thisObj != thisStack %s %s ",nameOf(thisObj),nameOf(thisStack));
	  };
#endif
	  glsc = cRestoreReturn(thisObj);
	  currentDescNo = cRestoreReturn(thisObj);
	  bc = codeFromDescNo(currentDescNo);
#ifdef TRACE
	  fprintf(trace,"AT %s(%i,%i,%s) \n"
		  ,nameOf(thisObj),currentDescNo,glsc,nameOf(thisStack));
#endif
	  break;
	case 'X': // same as for callX
	  rPush(callee,thisObj);
	  rPush(callee,thisStack);
	  thisObj = callee;
	  currentDescNo = topDescNo(thisObj);
	  bc = codeFromDescNo(currentDescNo);
	  glsc = getExitE(getDesc(currentDescNo));
#ifdef TRACE
	  fprintf(trace, "resumeX %s(%i,%i)\n",nameOf(callee),currentDescNo,glsc);
#endif
	  break;
	}
    }
  }

  void doSuspend(template *callee, bool preemptive){
#ifdef TRACE
    fprintf(trace," AT %s FROM %s(%i,%i,%s) "
	    ,nameOf(callee),nameOf(thisObj),currentDescNo,glsc,nameOf(thisStack));
    if (preemptive) fprintf(trace,"preemptive ");
#endif
    
    thisObj->lsc = glsc; // is this necessary?
#ifdef TRACE
    if (thisObj != thisStack) // external suspend ??
      { fprintf(trace,"thisObj != thisStack %s %s ",nameOf(thisObj),nameOf(thisStack));
      }
#endif
    cSaveReturn(thisObj,currentDescNo,glsc);
#ifdef TRACE
    dumpSwapped(trace,callee,thisObj,thisStack);
#endif
    rswap(callee,&thisObj,&thisStack); // notice &
#ifdef TRACE
    dumpSwapped(trace,callee,thisObj,thisStack);
#endif
    glsc = cRestoreReturn(thisObj);
    currentDescNo = cRestoreReturn(thisObj);
#ifdef TRACE
    fprintf(trace,"TO %s(%i,%i,%s)\n",nameOf(thisObj),currentDescNo,glsc,nameOf(thisStack));
#endif
    bc = codeFromDescNo(currentDescNo);
    rPush(thisStack,callee);
  };

  int opCode,arg1,arg2,arg3,dscNo,V;
  int dinx,rangee,i;
  bool running = true;
  template *X, *Y;

  thisObj = thisBlock->thisObj;
  thisStack = thisObj;
 
#ifdef EVENT
  mkEvent(start_event,0,thisObj,0,true,thisBlock->currentDescNo,thisBlock->glsc);
#endif
  while (running)
    { 
      //fprintf(trace,"\n*** Opcode: %i, glsc: %i\n",opCode,glsc);
      //printf("\n*** Opcode: %i, glsc: %i\n",opCode,glsc);
      if (suspendEnabled == 1) {
	timeToSuspend = timeToSuspend - 1;
	if (timeToSuspend <= 0) {
	  if (enablee != 0) {
	    suspendEnabled = suspendEnabled - 1;
	    if (suspendEnabled > 0) printf("\npSuspend: %i\n",suspendEnabled);
	    doSuspend(enablee,true);
	    enablee = 0;
	  }
	}
      }
#ifdef TRACE
      fprintf(trace,"%i:\t",glsc);
#endif
      opCode = bc[glsc]; glsc = glsc + 1; 
      switch (opCode) {
      case pushthis:
#ifdef TRACE
	fprintf(trace,"pushthis\n");
#endif
	rPush(thisStack,thisObj);
	break;
      case pushC: 
	arg1 = op1();
	vPush(thisStack,arg1);
#ifdef TRACE
	fprintf(trace,"pushc %i\n", arg1);
#endif
	break;
      case push:
	arg1 = op1();
#ifdef TRACE
	fprintf(trace,"push ");
#endif
	arg2 = thisObj->vfields[arg1];
	vPush(thisStack,arg2);
#ifdef TRACE
	fprintf(trace,"%s[%i] = %i\n",nameOf(thisObj),arg1,arg2);
#endif
	break;
      case rpush:
	arg1 = op1();
	X = thisObj->rfields[arg1];
#ifdef TRACE
	fprintf(trace,"rpush %s[%i] = %s \n",nameOf(thisObj),arg1,nameOf(X));
#endif
	rPush(thisStack,X);
	break;
      case pushg:
	arg1 = op1();
	X = rPop(thisStack);
	if (X == NULL) runTimeErrorX("Reference is NONE",thisObj,glsc);
	arg2 = X->vfields[arg1];
#ifdef TRACE
	fprintf(trace,"pushg %s[%i] = %i\n",nameOf(X),arg1,arg2);
#endif
	vPush(thisStack,arg2);
	break;
      case rpushg:
	arg1 = op1();
	X = rPop(thisStack);
	if (X == NULL) runTimeErrorX("Reference is NONE",thisObj,glsc);
	Y = X->rfields[arg1];
	rPush(thisStack,Y);
#ifdef TRACE
	fprintf(trace,"rpushg %s[%i] = %s\n",nameOf(X),arg1,nameOf(Y));
#endif
	break;
      case xpush:
	arg1 = op1(); // off
	arg2 = vPop(thisStack); // inx
	arg3 = thisObj->vfields[arg1 + arg2];
	vPush(thisStack,arg3);
#ifdef TRACE
	fprintf(trace,"xpush %s[%i+%i] = %i\n",nameOf(thisObj),arg1,arg2,arg3);
#endif
	break;
      case xpushg:
	arg1 = op1();
	X = rPop(thisStack);
	if (X == NULL) runTimeErrorX("Reference is NONE",thisObj,glsc);
	arg2 = vPop(thisStack);
	arg3 = X->vfields[arg1 + arg2]; // need range check - and do we adjust for range?
#ifdef TRACE
	fprintf(trace,"xpushg %s[%i+%i] = %i\n",nameOf(X),arg1,arg2,arg3);
#endif
	vPush(thisStack,arg3); 
	break;
      case store:
	arg1 = op1();
	arg2 = vPop(thisStack);
#ifdef TRACE
	fprintf(trace,"store %s[%i] = %i\n",nameOf(thisObj),arg1,arg2);
#endif
	thisObj->vfields[arg1] = arg2; 
     	break;
      case rstore:
	arg1 = op1();
#ifdef TRACE
	fprintf(trace,"rstore ");
#endif
	X = rPop(thisStack);
	thisObj->rfields[arg1] = X;
#ifdef TRACE
	//printf("rstore: %s %i %s\n",nameOf(X),arg1,nameOf(thisObj));
	fprintf(trace,"%s[%i] = %s\n",nameOf(thisObj),arg1,nameOf(X));
#endif
	break;
      case storeg:
	arg1 = op1(); // off/inx
	X = rPop(thisStack);
	arg2 = vPop(thisStack); // value
#ifdef TRACE
	fprintf(trace,"storeg %s[%i] = %i \n",nameOf(X),arg1,arg2);
#endif
	X->vfields[arg1] = arg2;
	break;
      case rstoreg:   
	arg1 = op1();
	X = rPop(thisStack);
	if ( X == 0) {
	  runTimeErrorX("Reference is none",thisObj,glsc);
	};
	Y = rPop(thisStack);
	X->rfields[arg1] = Y;
#ifdef TRACE
	fprintf(trace,"rstoreg %s[%i] = %s \n",nameOf(X),arg1,nameOf(Y));
#endif
	break; 
      case xstore:
	arg1 = op1();
	arg2 = vPop(thisStack); // inx
	arg3 = vPop(thisStack); // value;
#ifdef TRACE
	fprintf(trace,"xstore %s[%i+%i] = %i\n",nameOf(thisObj),arg1,arg2,arg3);
#endif
	thisObj->vfields[arg1 + arg2] = arg3;
	break;
      case xstoreg:
	arg1 = op1();
	X = rPop(thisStack);
	arg2 = vPop(thisStack);
	arg3 = vPop(thisStack);
#ifdef TRACE
	fprintf(trace,"xstoreg %s[%i+%i] = %i\n",nameOf(X),arg1,arg2,arg3);
#endif
	X->vfields[arg1 + arg2] = arg3;
	break;
      case _double:
	arg1 = vPop(thisStack);
#ifdef TRACE
	fprintf(trace,"double %i\n",arg1);
#endif
	vPush(thisStack,arg1);
	vPush(thisStack,arg1);
	break;
      case rdouble:
	X = rPop(thisStack);
#ifdef TRACE
	fprintf(trace,"rdouble %s\n",nameOf(X));
#endif
	rPush(thisStack,X);
	rPush(thisStack,X);
	break;
      case rtn:
	arg1 = op1();
#ifdef TRACE
	fprintf(trace,"rtn %c ",arg1);
#endif
	if ((suspendEnabled == 1) && (thisObj == enablee)) 
	  suspendEnabled = suspendEnabled - 1;
#ifdef TRACE
	fprintf(trace,"FROM %s(%i,%i,%s) ",nameOf(thisObj),currentDescNo,glsc,nameOf(thisStack));
#endif
	X = thisObj;
	thisStack = rPop(thisObj);
	thisObj = rPop(thisObj);
	glsc = cRestoreReturn(thisObj);
	currentDescNo = cRestoreReturn(thisObj);
	bc = codeFromDescNo(currentDescNo);
	rPush(thisStack,X);
#ifdef TRACE
	fprintf(trace,"TO %s(%i,%i,%s)",nameOf(thisObj),currentDescNo,glsc,nameOf(thisStack));
	dumpStack(trace,thisStack);
#endif
#ifdef EVENT
	if (((char)arg1 == 'A') && (thisObj != X)){
	  mkEvent(rtn_event,thisObj,X,myCorigin(X),false,currentDescNo,glsc);
	}
#endif
	break;
      case mvStack:
#ifdef TRACE
	fprintf(trace,"mvStack %s -> %s [",nameOf(thisObj),nameOf(thisStack));
#endif
	thisStack = thisObj;
#ifdef TRACE
	int i;
	for (i = 0; i < thisStack->rtop; i++) fprintf(trace,"%s ",nameOf(thisStack->rstack[i+1]));
	fprintf(trace,"]\n");
#endif
	break;
      case call:
	/*return*/ doCall(false);
	break;
      case susp:
#ifdef TRACE
	fprintf(trace,"susp ");
#endif
	callee = rPop(thisStack);
	if ((suspendEnabled == 1) && (callee == enablee)) suspendEnabled = suspendEnabled - 1;
	doSuspend(callee,false);
	break;
      case alloc:
	arg1 = op2();
	arg2 = op1();
#ifdef TRACE
	fprintf(trace,"alloc %i %i ",arg1,arg2);
#endif
	/*return*/ allocObj(rPop(thisStack),arg1,arg2,0,0);
	break;
      case doExit:
#ifdef TRACE
	fprintf(trace,"doExit\n");
#endif
	thisStack = thisObj->rstack[thisObj->rtop];
#ifdef EVENT
	mkEvent(doExit_event,thisObj,thisStack,myCorigin(thisStack),false,currentDescNo,glsc);
#endif
	break;
      case rtnExit:
#ifdef TRACE
	fprintf(trace,"rtnExit");
#endif
	runTimeError("rtnExit not implemented");
	break;
      case prim:
	arg1 = op1();
#ifdef TRACE
	fprintf(trace,"prim %i ",arg1);
#endif
	switch (arg1)
	  {
	  case 2: // put
	    arg2 = vPop(thisStack);
#ifdef TRACE
	    fprintf(trace,"put \'%c\'\n",(char)arg2);
#endif
	    printf("%c",(char)arg2);
	    break;
	  case 10: // attach
	    arg2 = vPop(thisStack);
#ifdef TRACE
	    fprintf(trace,"attach %i\n",arg2);
#endif
	    suspendEnabled = suspendEnabled + 1;
	    timeToSuspend = arg2;
	    //glsc = glsc - 1;
	    doCall(true);
	    break;
	  case 11: // disable
#ifdef TRACE
	    fprintf(trace,"disable\n");
#endif
	    suspendEnabled = suspendEnabled - 1;
	    break;
	  case 12: // enable
#ifdef TRACE
	    fprintf(trace,"enable\n");
#endif
	    suspendEnabled = suspendEnabled + 1;
	    break;
	  case 13: // fork
#ifdef TRACE
	    fprintf(trace,"fork ");
#endif
	    Y = rPop(thisStack);
	    Block *B = (Block *)heapAlloc(sizeof(Block));	    
	    X = allocTemplate(newId(),threadStubDescNo,true,0,0);
	    rPush(X,Y);
#ifdef TRACE
	    fprintf(trace,"%s\n",nameOf(X));
#endif
	    B->thisModule = X;
	    B->thisObj = X;
	    B->thisStack = X;
	    B->bc = myCode(X);
	    B->currentDescNo = threadStubDescNo;
	    B->top = Y;
#ifdef TRACE
	    printf("currentDescNo: %i %i %i threadNo: %i\n"
		   ,B->currentDescNo,B->glsc,B->bc,threadNo);
#endif
	    B->glsc = 0;
	    char *fileName = heapAlloc(12);
	    int n = sprintf (fileName,"traceF%i.s",threadNo);
	    //printf("\n%s\n",fileName);
	    B->traceFile = fileName;
	    B->threadId = threadNo + 1; 
	    hThreadArray[threadNo] = CreateThread(NULL,0,interpreter,(LPVOID)B,0,0);
	    threadNo = threadNo + 1;
	    hasThreads = true;
	    break;
	  case 14: // cmpAndSwap
	    arg1 = vPop(thisStack); // offset 
	    arg2 = vPop(thisStack); // new value
	    X = rPop(thisStack);
	    arg3 = X->vfields[arg1];
	    // V = cmpxchlg(&X->vfields[arg1],arg3,arg2);
	    // V = cmpxchlg(&X->vfields[arg1],0,arg2);
	    V = __sync_bool_compare_and_swap(&X->vfields[arg1],0,arg2);
#ifdef TRACE
	    fprintf(trace,"cmpAndSwap new: %i old: %i %s adr: %i %i"
		    ,arg2,arg3,nameOf(X),&X->vfields[arg1,V]);
#endif
	    if (V) {V = 0;} else {V = 1;}; 
#ifdef TRACE
	    fprintf(trace,"%i\n",V);
#endif
	    vPush(thisStack,V);
	    break;
	  case 15: // sleep
	    arg1 = vPop(thisStack);
#ifdef TRACE
	    fprintf(trace,"sleep %i\n",arg1);
#endif
	    Sleep(arg1);
	    break;
	  case 17: 
#ifdef TRACE
	   fprintf(trace,"thisCore %s %s\n",nameOf(thisBlock->thisObj),nameOf(thisBlock->top));
#endif
	    rPush(thisStack,thisBlock->top);
	    break;
	  default:
	    printf("\n\n*** prim: missing case %i\n",arg1);
	    runTimeError("prim: missing case");
	  }
	break;
      case jmp:
	glsc = op2() - 1;
#ifdef TRACE
	fprintf(trace,"jmp %i\n",glsc);
#endif
	break;
      case jmpFalse:
	arg1 = op2();
	arg2 = vPop(thisStack);
#ifdef TRACE
	fprintf(trace,"jmpFalse %i %i \n",arg1, arg2);
#endif
	if (arg2 == 0) glsc = arg1 - 1;
	break;
      case jmpGT:
	arg1 = vPop(thisStack);
	arg2 = vPop(thisStack);
	arg3 = op2();
#ifdef TRACE
	fprintf(trace,"jmpGT %i > %i -> %i \n",arg2,arg1,arg3 - 1);
#endif
	if (arg2 > arg1) glsc = arg3 - 1;
	break;
      case pushNone:
#ifdef TRACE
	fprintf(trace,"pushNone\n");
#endif
	rPush(thisStack,0);
	break;
      case rtnEvent:
	arg1 = op1();
	X = rPop(thisObj);
#ifdef TRACE
	fprintf(trace,"rtnEvent %i %s\n",arg1,nameOf(X));
#endif
#ifdef EVENT
	mkEvent(rtn_event,thisObj,X,myCorigin(X),false,currentDescNo,glsc);
#endif
	break;
      case saveBETAworld:
#ifdef TRACE
	fprintf(trace,"saveBETAworld\n");
#endif
	X = rPop(thisStack); // should be assigned to eventprocessor.rfields[1][]
	break;
      case doSuper:
	arg1 = op2();
#ifdef TRACE
	fprintf(trace,"doSuper %i\n",arg1);
#endif
	//cSaveReturn(thisObj,descNoOf(thisObj),glsc);
	//rPush(thisObj,thisObj);
	//rPush(thisObj,thisStack);
	//cSaveReturn(thisObj,currentDescNo,glsc);
	currentDescNo = arg1;
	bc = codeFromDescNo(arg1);
	glsc = getEnterE(getDesc(arg1));
	break;
      case innerx:
	arg1 = op1();
#ifdef TRACE
	fprintf(trace,"innerx %i",arg1);
#endif
	arg2 = vdtTable(trace,thisObj,arg1); // descNo
#ifdef TRACE
	fprintf(trace,"\n");
#endif
	if (arg2 > 0) {
	  cSaveReturn(thisObj,currentDescNo,glsc);
	  currentDescNo = arg2;
	  bc = codeFromDescNo(arg2);
	  glsc = getDoE(getDesc(arg2));
	}
	break;
      case rtnInner:
#ifdef TRACE
	fprintf(trace,"returnInner\n");
#endif
	glsc = cRestoreReturn(thisObj);
	dscNo = cRestoreReturn(thisObj);
	currentDescNo = dscNo;
	bc = codeFromDescNo(dscNo);
	break;
      case innerExit:
	arg1 = op1();
#ifdef TRACE
	fprintf(trace,"innerExit %i ",arg1);
#endif
	arg2 = vdtTable(trace,thisObj,arg1);
	if (arg2 > 0) {
	  cSaveReturn(thisObj,currentDescNo,glsc);
	  bc = codeFromDescNo(arg2);
	  currentDescNo = arg2;
	  glsc = getExitE(getDesc(arg2));
#ifdef TRACE
	  fprintf(trace,"TO %i %i",currentDescNo,glsc);
#endif
	};
#ifdef TRACE
	fprintf(trace,"\n");
#endif
	break;
      case sendv: 
	arg1 = op1();
	X = rPop(thisStack);
#ifdef TRACE
	fprintf(trace,"sendv %i",arg1);
#endif
	arg2 = vdtTable(trace,X,arg1); // descNo
	allocObj(X,arg2,false,0,0);
	break;
      case send: 
#ifdef TRACE
	fprintf(trace,"send %i",op1());
#endif
	runTimeError("send is not implemented");
	break;
      case newVrep:
#ifdef TRACE
	fprintf(trace,"newVrep");
#endif
	runTimeError("newVrep is not implemented");
	break;
      case jmpTrue:
	arg1 = op2();
	arg2 = vPop(thisStack);
#ifdef TRACE
	fprintf(trace,"jmpTrue %i\n",arg1);
#endif
	if (arg2 == 1) glsc = arg1 - 1;
	break;
      case pushText:
	arg1 = op1();
#ifdef TRACE
	fprintf(trace,"pushText %i ",arg1);
#endif
	allocTextObj(arg1);
	break;
      case exeAlloc:
	arg1 = op2();
#ifdef TRACE
	fprintf(trace,"exeAlloc %i ",arg1);
	fprintf(trace,"FROM %s(%i,%i) ", nameOf(thisObj),currentDescNo,glsc);
#endif
	X = rPop(thisStack);
	cSaveReturn(thisObj,currentDescNo,glsc);
	rPush(thisObj,thisObj);
	rPush(thisObj,thisStack);
	thisStack = thisObj;
	rPush(thisObj,X);
	currentDescNo = arg1;
	bc = codeFromDescNo(arg1);
	glsc = getAllocE(getDesc(arg1));
#ifdef TRACE
	fprintf(trace,"TO %s(%i,%i)\n",nameOf(thisObj),currentDescNo,glsc);
#endif
	break;
      case rtnc:
#ifdef TRACE
	fprintf(trace,"rtnC");
#endif
	break;
      case rpop:
#ifdef TRACE
	fprintf(trace,"rpop\n");
#endif
	rPop(thisStack);
	break;
      case vpop:
#ifdef TRACE
	fprintf(trace,"vpop\n");
#endif
	vPop(thisStack);
	break;
      case eq:
	arg1 = vPop(thisStack);
	arg2 = vPop(thisStack);
#ifdef TRACE
	fprintf(trace,"eq %i %i\n",arg1,arg2);
#endif
	if (arg1 == arg2) { vPush(thisStack,1);} else vPush(thisStack,0);
	break;
      case lt:
	arg1 = vPop(thisStack);
	arg2 = vPop(thisStack);
#ifdef TRACE
	fprintf(trace,"lt %i < %i\n",arg2,arg1);
#endif
	if (arg1 > arg2) { vPush(thisStack,1);} else vPush(thisStack,0);
	break;
      case le:
	arg1 = vPop(thisStack);
	arg2 = vPop(thisStack);
#ifdef TRACE
	fprintf(trace,"le %i <= %i\n",arg2,arg1);
#endif
	if (arg1 >= arg2) { vPush(thisStack,1);} else vPush(thisStack,0);
	break;
      case gt:
	arg1 = vPop(thisStack);
	arg2 = vPop(thisStack);
#ifdef TRACE
	fprintf(trace,"gt %i > %i\n",arg2,arg1);
#endif
	if (arg1 < arg2) { vPush(thisStack,1);} else vPush(thisStack,0);
	break;
      case ge:
	arg1 = vPop(thisStack);
	arg2 = vPop(thisStack);
#ifdef TRACE
	fprintf(trace,"ge %i >= %i\n",arg2,arg1);
#endif
	if (arg1 <= arg2) { vPush(thisStack,1);} else vPush(thisStack,0);
	break;
      case ne:
	arg1 = vPop(thisStack);
	arg2 = vPop(thisStack);
#ifdef TRACE
	fprintf(trace,"ne %i != %i\n",arg1,arg2);
#endif
	if (arg1 != arg2) { vPush(thisStack,1);} else vPush(thisStack,0);
	break;
      case req:
	X = rPop(thisStack);
	Y = rPop(thisStack);
#ifdef TRACE
	fprintf(trace,"req %i == %i\n",(int)X,(int)Y);
#endif
	vPush(thisStack, X == Y);
	break;
      case rne:
	X = rPop(thisStack);
	Y = rPop(thisStack);
#ifdef TRACE
	fprintf(trace,"rne %i != %i\n",(int)X,(int)Y);
#endif
	vPush(thisStack,X != Y);
	break;    
      case seq:
	X = rPop(thisStack);
	Y = rPop(thisStack);
	//printf("\nseq:struc: %s %s\n",nameOf(X),nameOf(Y));
	arg1 = X->vfields[1];
	arg2 = Y->vfields[1];
	X = X->rfields[2];
	Y = Y->rfields[2];
#ifdef TRACE
	fprintf(trace,"seq %s %i %s %i\n",nameOf(X),arg1,nameOf(Y),arg2);
#endif
	vPush(thisStack,(arg1 == arg2) && (X->rfields[2] == Y->rfields[2]));
	//printf("vTop: %i\n",thisStack->vstack[thisStack->vtop]);
	break;
      case sne:
	X = rPop(thisStack);
	Y = rPop(thisStack);
#ifdef TRACE
	fprintf(trace,"sne %i != %i\n",(int)X,(int)Y);
#endif
	vPush(thisStack,(X->vfields[1] != Y->vfields[1]) || (X->rfields[2] != Y->rfields[2]));
	break;
      case plus:
	arg1 = vPop(thisStack);
	arg2 = vPop(thisStack);
#ifdef TRACE
	fprintf(trace,"plus %i + %i\n",arg1,arg2);
#endif
	vPush(thisStack,arg1 + arg2);
	break;
      case minus:
	arg1 = vPop(thisStack);
	arg2 = vPop(thisStack);
#ifdef TRACE
	fprintf(trace,"minus %i - %i\n",arg2,arg1);
#endif
	vPush(thisStack,arg2 - arg1);
	break;
      case orr: 
	arg1 = vPop(thisStack);
	arg2 = vPop(thisStack);
#ifdef TRACE
	fprintf(trace,"orr %i || %i\n",arg1,arg2);
#endif
	if ((arg1 == 1) || (arg2 ==1)) {vPush(thisStack,1);} else vPush(thisStack,0);
	break;
      case xorr:
	arg1 = vPop(thisStack);
	arg2 = vPop(thisStack);
#ifdef TRACE
	fprintf(trace,"Not mplemented xorr %i %i\n",arg1,arg2);
#endif
	if ((arg1 == 1) || (arg2 ==1)) {vPush(thisStack,1);} else vPush(thisStack,0);
	break;
      case nott:
	arg1 = vPop(thisStack);
#ifdef TRACE
	fprintf(trace,"nott %i\n",arg1);
#endif
	if (arg1 == 0) {vPush(thisStack,1);} else vPush(thisStack,0);
	break;
      case mult:
	arg1 = vPop(thisStack);
	arg2 = vPop(thisStack);
#ifdef TRACE
	fprintf(trace,"mult %i * %i\n",arg1,arg2);
#endif
	vPush(thisStack,arg1 * arg2);
	break;
      case rdiv:
	arg1 = vPop(thisStack);
	arg2 = vPop(thisStack);
#ifdef TRACE
	fprintf(trace,"\n**** rdiv is not implemented!\n\n");
#endif
	runTimeError(" rdiv is not implemented");
	break;
      case idiv:
	arg1 = vPop(thisStack);
	arg2 = vPop(thisStack);
#ifdef TRACE
	fprintf(trace,"idiv %i div %i\n",arg2,arg1);
#endif
	vPush(thisStack,arg2 / arg1);
	break;
      case modd:
	arg1 = vPop(thisStack);
	arg2 = vPop(thisStack);
#ifdef TRACE
	fprintf(trace,"modd %i %i\n", arg2,arg1);
#endif
	vPush(thisStack,arg2 % arg1);
	break;
      case andd:
	arg1 = vPop(thisStack);
	arg2 = vPop(thisStack);
#ifdef TRACE
	fprintf(trace,"andd %i %i\n",arg1,arg2);
#endif
	vPush(thisStack,arg1 && arg2);
	break;
      case uminus:
	arg1 = vPop(thisStack);
#ifdef TRACE
	fprintf(trace,"uminus %i\n",arg1);
#endif
	vPush(thisStack,-arg1);
	break;
      case pushc2:
	arg1 = op2();
#ifdef TRACE
	fprintf(trace,"pushc2 %i\n",arg1);
#endif
	vPush(thisStack,arg1);
	break;
      case allocIndexed:	
	arg1 = op2();
	arg2 = op1();
#ifdef TRACE
	fprintf(trace,"allocIndexed %i %i\n",arg1,arg2);
#endif
	X = rPop(thisStack);
	dinx = vPop(thisStack);
	rangee = vPop(thisStack);
	allocIndexedObj(X,arg1,arg2,dinx,rangee);
	break;
      case mkStrucRef: 
	arg1 = vPop(thisStack);
	X = rPop(thisStack);
#ifdef TRACE
	fprintf(trace,"mkStrucRef %i %s\n",arg1,nameOf(X));
#endif
	allocStrucRefObj(X,arg1,false);
	//X = thisStack->rstack[thisStack->rtop];
	//printf("mkStrucRef:Result: %s\n",nameOf(X));
	break;
      case mkObjStrucRef: 
	X = rPop(thisStack);
	//Y = thisStack->rstack[thisStack->rtop];
	//printf("Result-top: %s\n",nameOf(Y));
#ifdef TRACE
	fprintf(trace,"\nmkObjStrucRef X: %s  X.origin: %s X.descNo: %i \n"
	      ,nameOf(X)
	      ,nameOf(myCorigin(X)),descNo(X->desc));
#endif
	allocStrucRefObj(myCorigin(X),descNo(X->desc),false);
	//X = thisStack->rstack[thisStack->rtop];
	//printf("Result-top: %s\n",nameOf(X));
	//X = thisStack->rstack[thisStack->rtop - 1];
	//printf("Result-top-1: %s\n",nameOf(X));
	break;
      case mkVirtualStrucRef:
	arg1 = op1();
	X = rPop(thisObj);
#ifdef TRACE
	fprintf(trace,"mkVirtualStrucRef %i %s\n",arg1,nameOf(X));
#endif
	allocStrucRefObj(X,arg1,true);
	break;
      case _allocFromStrucRefObj:
	X = rPop(thisStack);
#ifdef TRACE
	fprintf(trace,"allocFromStrucRefObj %s\n",nameOf(X));
#endif
	allocFromStrucRefObj(X);
	break;
      case _break:
	arg1 = op1();
	arg2 = op2();
#ifdef TRACE
	fprintf(trace,"break %i %i\n",arg1,arg2);
#endif
	X = thisObj;
	for (i = 0; i < arg1; i++) { 
	  //fprintf(trace,"popCallStackA: %s \n",nameOf(X));
	  X = myCorigin(X);
	}
	//fprintf(trace,"popCallStackB: %s \n",nameOf(X));
      popCallStack:
	if (thisObj != X) {
	  //fprintf(trace,"popCallStackC %s \n",nameOf(thisObj));
	  thisStack = rPop(thisObj);
	  thisObj = rPop(thisObj);
	  goto popCallStack;
	};
	//fprintf(trace,"popCallStackD %s\n",nameOf(Y));
	glsc = cRestoreReturn(thisObj);
	currentDescNo = cRestoreReturn(thisObj);
	bc = codeFromDescNo(currentDescNo);
	glsc = xlabs(currentDescNo,arg2) - 1;
	//fprintf(trace,"popCallStackE %i %i\n",currentDescNo,glsc);
	break;
      case stop: 
#ifdef TRACE
	fprintf(trace,"stop: %i\n",threadNo);
#endif
	running = false;
	//threadNo = threadNo - 1;
	break;
      default:
	fprintf(trace,"Op: %i ",bc[glsc]);
	runTimeError("Illegal byte code");
	break;
      }
    };
  fclose(trace);
  printf("\nStop: %i ",threadNo); if (hasThreads) printf("TRUE");
  if (threadNo > 0) {
    WaitForMultipleObjects(threadNo, hThreadArray, TRUE, INFINITE);
    int j;
    for( j=0; j < threadNo; j++)
      { printf("Close\n");
      CloseHandle(hThreadArray[j]);
      };
    printf("After Wait\n");
    //mkEvent(stop_event,0,0,0,0,0,0); 
  };
  if (threadId == 0) mkEvent(stop_event,0,0,0,0,0,0); 
  return 0;
}

void close_interpreter(){ 
}


