#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

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
  
  eq = 50,
  lt = 51,
  le = 52,
  gt = 53,
  ge = 54,
  ne = 55,
  req = 56,
  rne = 57,
  
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
};

void runTimeError(char *msg){
  printf("\n\n*** Run-time error: %s\n\n",msg);
  exit(-1);
}

unsigned char heap[10000000]; int heapTop;

void *heapAlloc(int size) {
  void *obj;
  if (true) { 
    obj = malloc(size);
    if (obj == 0) runTimeError("malloc failed");
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

FILE * trace;

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

//int getBcStart(ObjDesc desc) { return desc_getInt2(desc,vdtTableRange_index) * 4; }

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

ObjDesc bc;  
int glsc,currentDescNo;
  
int op1(){
  int V = bc[glsc]; 
  glsc = glsc + 1;
  return V;
};
int op2(){ 
  int V = bc[glsc] * 256 + bc[glsc + 1];
  glsc = glsc + 2;
  return V;
}


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

void dumpStringTable() {
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
  /*  i = inx + 4;
      fprintf(trace,"0: %s",descs + i);
      while (i < StringsSize) {
      //int length = getInt2(inx + i);
      int length = i;
      fprintf(trace,">>> %i: %s",length);
      fprintf(trace," %i:",length);
      i = i + 2;
      for (j=0; j<length; j++) fprintf(trace,"%c",descs[inx + i + j]);
      i = i + length;
      };*/
  fprintf(trace,"\n");
  //for (i = 0; i < StringsSize; i++) fprintf(trace,"%c",stringTable[i]);
  //fprintf(trace,"\n");
};

void dumpString(int inx) { //fprintf(trace,"dumpString %i\n",inx);
  int i,length = stringTable[4 + inx] + stringTable[4 + inx + 1];
  //fprintf(trace," %i:",length);
  for (i=0; i<length; i++) fprintf(trace,"%c",stringTable[4 + inx + 2 + i]);
}

void dumpCode(ObjDesc desc){
  int opCode,arg1,arg2,bcTop;
  ObjDesc bc;
  /*fprintf(trace,"dumpCode : \n");
  for (arg1 = 0; arg1 < 100; arg1++) {
  fprintf(trace," %i: %i\n", arg1,desc[arg1]);    
  };*/
  bc = getByteCode(desc);
  bcTop = getBCtop(desc);
  //  fprintf(trace,"dumpCode %i",bcTop);
  //  fprintf(trace," %i %i \n",bc[0],bc[1]);
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
	fprintf(trace,"pushC: %i", arg1);
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
	fprintf(trace,"rstore: %i ",op1());
	break;
      case storeg:
	fprintf(trace,"storeg: %i ",op1());
	break;
      case rstoreg:   
	fprintf(trace,"rstoreg: %i ",op1());
	break; 
      case xstore:
	fprintf(trace,"xstore: %i ",op1());
	break;
      case xstoreg:
	fprintf(trace,"xstoreg: %i ",op1());
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
	fprintf(trace,"call: %c ",arg1);
	break;
      case susp:
	fprintf(trace,"susp");
	break;
      case alloc:
	arg1 = op2();
	arg2 = op1();
	fprintf(trace,"alloc: %i %i",arg1,arg2);
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
      case mkVirtualStrucRef:
	fprintf(trace,"mkVirtualStrucRef");
	break;
      case _allocFromStrucRefObj:
	fprintf(trace,"allocFromStrucRefObj");
	break;
      case _break:
	fprintf(trace,"break: %i %i",op1(),op2());
	break;
      case stop: 
	fprintf(trace,"stop: ");
	break;
      default:
	fprintf(trace,"Op: %i ",bc[glsc]);
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

void dumpDesc(int xdescNo) {
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
    if (RS >= 24) runTimeError("rSize too big");
    dumpCode(desc);
  }
}

void dumpDescriptors() {
  int descNo,noOfDescs = getInt4(noOfObjDesc_index);
  fprintf(trace,"Descriptors %i \n",noOfDescs);
  for (descNo=1; descNo < noOfDescs; descNo++) dumpDesc(descNo);
}

void dump_image() {
  fprintf(trace,"%c%c%c%c%c%c%c%c\n"
	 ,descs[0],descs[1],descs[2],descs[3],descs[4],descs[5],descs[6],descs[7]);
  fprintf(trace,"StringTableIndex: %i\n",getStringTableIndex());
  dumpStringTable();
  dumpDescriptors();
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
  struct template *rfields[24];
  int vfields[];
} template;

template *thisModule,*thisObj,*thisStack, *callee;

typedef struct Event {
  int type;
  template *caller,*thisObj,*org;
  int isObj;
  int bcPos;
} Event;

int ID = 1000;

int newId() { ID = ID + 1; return ID;}

int hSize = 0;
template *allocTemplate(int descNo,bool isObj, int vInxSize, int rInxSize){
  int i = sizeof(template) + (16 + vInxSize) * sizeof(int) + 1000;
  hSize = hSize + i;
  fprintf(trace,"allocTemplate(%i,%i) ",i, hSize);
  template *obj = (template*)heapAlloc(i);
  //fprintf(trace,"template allocated: %i\n",vInxSize);
  obj->desc = getDesc(descNo);
  obj->id = newId();
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

int topDescNo(template *obj){ return desc_getInt4(obj->desc,topDescNo_index); }

template *myCorigin(template *obj){ 
  int inx;
  inx = desc_getInt2(obj->desc,originOff_index);
  template * origin = 0;
  if (inx > 0) origin = obj->rfields[inx];
  return origin;
}

void dumpObj(template *obj){
  fprintf(trace,"\n*** Object: id:%i\n",obj->id);
}

void dumpName(ObjDesc desc) {
  dumpString(desc_getInt2(desc,0));
}

void allocMain(int descNo){ 
  thisModule = allocTemplate(descNo,true,0,0);
  thisObj = thisModule;
  thisStack = thisModule;
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

int vdtTable(template *obj,int inx){
  fprintf(trace," vdtTable[%i] = %i "
	  ,inx,desc_getInt4(obj->desc,vdtTable_index + (inx -1 ) * 4));
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

void vpush(int V){
  if ((thisStack->vtop = thisStack->vtop + 1) > 16 ) 
    runTimeError("vstack overflow");
  thisStack->vstack[thisStack->vtop] = V;
}

void rPush(template *stack,template *R){
  //fprintf(trace,"\n*** rPush obj %i at %i \n",R->id,stack->rtop);
  if ((stack->rtop = stack->rtop + 1) > 16 ) runTimeError("stack overflow");
  stack->rstack[stack->rtop] = R;
}

int vpop(){
  if ((thisStack->vtop = thisStack->vtop - 1) < -1) 
    runTimeError("vstack underflow");
  return thisStack->vstack[thisStack->vtop + 1];
}

template *rPop(template *stack){
  //template *R = stack->rstack[stack->rtop];
  // fprintf(trace,"\n*** rPop obj %i from %i \n",R->id,stack->rtop);
  if ((stack->rtop = stack->rtop - 1) < -1) runTimeError("rStack underflow");
  return stack->rstack[stack->rtop + 1];
}

void saveReturn(template *obj,int descNo, int lsc){
  //fprintf(trace,"\n***saveReturn in %s lscTop=%i:",nameOf(obj),obj->lscTop);
  //int i;
  //for (i=0; i < obj->lscTop; i++) fprintf(trace,"%i ",obj->lscStack[i]);
  //fprintf(trace,"\n");
  if ((obj->lscTop = obj->lscTop + 2) > 16) runTimeError("lsc stack overflow");
  obj->lscStack[obj->lscTop-1] = descNo;
  obj->lscStack[obj->lscTop] = lsc;
}

int topOfLsc(template *obj,int inx ){ return obj->lscStack[obj->lscTop + inx];};

int restoreReturn(template * obj){
  //fprintf(trace,"\n***restoreReturn: %i %s\n",obj->lscTop,nameOf(obj));
  if (obj->lscTop < 0) fprintf(trace,"\n**** ERROR:  lscStack underflow\n");
  int V = obj->lscStack[obj->lscTop];
  obj->lscTop = obj->lscTop - 1;
  return V;
}

Event *last = 0;

Event *mkEvent(int type,template *caller,template *thisObj,template *org
		,bool isObj,int bcPos){ 
  fprintf(trace,"\nmkEvent: %i %i %i\n",type,hSize,sizeof(Event));
  hSize = hSize + sizeof(Event);
  Event *E = (Event *)heapAlloc(sizeof(Event));
  E->type = type;
  E->caller = caller;
  E->thisObj = thisObj;
  E->org = org;
  E->isObj = (int) isObj;
  E->bcPos = bcPos;
  //last = E;
  return E;  
}
Event *mkAllocEvent(int type,template *caller,template *thisObj,template *org
		,bool isObj,int bcPos,bool isIndexed){ 

  return mkEvent(type,caller,thisObj,org,isObj,bcPos);
};

Event *allocObj(template *origin,int descNo,bool isObj,int vInxSize,int rInxSize){
  fprintf(trace,"FROM %s(%i,%i,%i) ",nameOf(thisObj),currentDescNo,glsc,bc);
  callee = allocTemplate(descNo,isObj,vInxSize,rInxSize);
  fprintf(trace,"callee: %s %i ",nameOf(callee),callee);
  template *Y;
  Y = thisObj;
  rPush(callee,thisObj);
  rPush(callee,thisStack);
  rPush(callee,origin);
  saveReturn(thisObj,currentDescNo,glsc);
  currentDescNo = descNo;
  thisStack = callee;
  thisObj = thisStack;
  bc = (ObjDesc) myCode(thisObj);
  glsc = getAllocE(thisObj->desc);
  fprintf(trace,"ALLOC %s(%i,%i,%i,%i)\n"
	  ,nameOf(thisObj),descNo,glsc,(int)thisObj,bc);
  //dumpObj(thisObj);
  return mkAllocEvent(alloc_event,Y,thisObj,origin,isObj,glsc,false);
}

void allocIndexedObj(template * origin, int descNo,bool isObj, int dinx, int rangee){ 
  fprintf(trace,"allocIndexedObj(%i,%i) ",dinx,rangee);
  allocObj(origin,descNo,isObj,rangee,0);
  thisObj->vfields[dinx] = rangee; 
}

void allocStrucRefObj(template *origin,int inx, bool isVirtual){
  fprintf(trace,"***allocStrucRefObj origin: %s inx:%i \n",nameOf(origin),inx);
  template * X = allocTemplate(getStrucRefDescNo(),0,0,0);
  if (isVirtual) inx = vdtTable(origin,inx);
  X->vfields[1] = inx;
  X->rfields[2] = origin;
  rPush(thisStack,X);
};

void allocFromStrucRefObj(template *obj){
  fprintf(trace,"***allocFromStrucRefObj %s : ", nameOf(obj));
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

int descNoOf(template * obj){
  return desc_getInt4(obj->desc,descNo_index);
}


int suspendEnabled,timeToSuspend;

template * enablee = 0;

void dumpSwapped(template *X, template *Y,template *Z){
  fprintf(trace,"\nswapped: %s R[1]=%s, R[2]=%s ¨ %s %s \n"
	  ,nameOf(X),nameOf(X->rstack[1]),nameOf(X->rstack[2])
	  ,nameOf(Y),nameOf(Z));
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

Event *doCall(bool withEnablingSuspend){
  int arg1;
  template *Y;
  arg1 = (char) op1();
  fprintf(trace,"call %c ",arg1);
  callee = rPop(thisStack);
  fprintf(trace,"FROM %s(%i,%i,%i) ",nameOf(thisObj),currentDescNo,glsc,bc);
  if (withEnablingSuspend) enablee = callee;
  saveReturn(thisObj,currentDescNo,glsc);
  
  if (callee->rtop == 0) {
    Y = thisObj;
    rPush(callee,thisObj);
    rPush(callee,thisStack);
    thisObj = callee;
    fprintf(trace,"TO %s",nameOf(callee));
    switch (arg1)
      {
      case 'N':
	currentDescNo = descNoOf(thisObj);
	bc = myCode(thisObj);
	glsc = getEnterE(thisObj->desc);
	fprintf(trace,"(%i,%i,%i) N\n",currentDescNo,glsc,bc);
	break;
      case 'D':
	arg1 = topDescNo(thisObj);
	currentDescNo = arg1;
	bc = codeFromDescNo(arg1);
	glsc = getDoE(getDesc(arg1));
	fprintf(trace,"(%i,%i,%i) D\n",currentDescNo,glsc,bc);
	return mkEvent(do_event,Y,thisObj,myCorigin(thisObj),false,glsc); // withEnablingSuspend
	break;
      case 'X':
	arg1 = topDescNo(thisObj);
	currentDescNo = arg1;
	//dumpDesc(arg1);
	bc = codeFromDescNo(arg1);
	glsc = getExitE(getDesc(arg1));
	fprintf(trace,"(%i,%i,%i) X\n",arg1,glsc,bc);
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
	fprintf(trace, "resumeN %s(%i,%i)\n",nameOf(callee),currentDescNo,glsc);
	break;
      case 'D':
	fprintf(trace, "resumeD %s ",nameOf(callee));
	rswap(callee,&thisObj,&thisStack);
	if (thisStack != thisObj) { // external suspend?
	};
	glsc = restoreReturn(thisObj);
	currentDescNo = restoreReturn(thisObj);
	bc = codeFromDescNo(currentDescNo);
	fprintf(trace,"AT %s(%i,%i,%s) \n"
		,nameOf(thisObj),currentDescNo,glsc,nameOf(thisStack));
	break;
      case 'X': // same as for callX
	rPush(callee,thisObj);
	rPush(callee,thisStack);
	thisObj = callee;
	currentDescNo = topDescNo(thisObj);
	bc = codeFromDescNo(currentDescNo);
	glsc = getExitE(getDesc(currentDescNo));
	fprintf(trace, "resumeX %s(%i,%i)\n",nameOf(callee),currentDescNo,glsc);
	break;
      }
  }
  return mkEvent(0,0,0,0,0,0);
}

void doSuspend(template *callee, bool preemptive){
  fprintf(trace," AT %s FROM %s ",nameOf(callee),nameOf(thisObj));
  if (preemptive) fprintf(trace,"preemptive ");

  thisObj->lsc = glsc; // is this necessary?
  if (thisObj != thisStack) // external suspend ??
    {
    }
  saveReturn(thisObj,currentDescNo,glsc);
  //dumpSwapped(callee,thisObj,thisStack);
  rswap(callee,&thisObj,&thisStack); // notice &
  //dumpSwapped(callee,thisObj,thisStack);
  glsc = restoreReturn(thisObj);
  currentDescNo = restoreReturn(thisObj);
  fprintf(trace,"TO %s(%i,%i) %s\n",nameOf(thisObj),currentDescNo,glsc,nameOf(thisStack));
  bc = codeFromDescNo(currentDescNo);
  rPush(thisStack,callee);
};

Event *init_interpreter(ObjDesc descs_a, int mainDescNo) {
  trace = fopen("trace.s","w");
  setbuf(trace, NULL);
  descs = descs_a; // this is necessary for getImgaeSize() below
  // we must copy from Beta memory to avoid GC problems
  int imageSize = getImageSize();
  printf("Imagesize: %i\n",imageSize);
  //int i;
  //for (i=0; i < 100; i++) printf("i: %i\n",descs_a[i]);
  descs = heapAlloc(imageSize);
  memcpy(descs,descs_a,imageSize); 
  bc = descs;

  fprintf(trace,"C interpreter: mainDescNo: %i imageSize: %i\n",mainDescNo,imageSize);
  //int i;
  //  for (i=0; i < mainDescNo; i++) fprintf(trace,"%i: %i\n",i,descs[i]);
  fprintf(trace,"Main desc index: %i\n", (int)getDesc(mainDescNo));
  allocMain(mainDescNo);
  bc = getByteCode(getDesc(mainDescNo));
  currentDescNo = mainDescNo;
  stringTable = descs + getStringTableIndex();
  dump_image();
  glsc = 0; 
  fprintf(trace,"**** Execute:\n\n");
  return mkEvent(start_event,0,thisObj,0,true,glsc);
}

Event *run_interpreter(){
  int opCode,arg1,arg2,arg3,descNo,xglsc;
  int dinx,rangee,i;
  bool running = true;
  template *X, *Y;
  releaseHeap(last);
  while (running)
    { 
      //fprintf(trace,"\n*** Opcode: %i, glsc: %i\n",opCode,glsc);
      if (suspendEnabled == 1) {
	timeToSuspend = timeToSuspend - 1;
	if (timeToSuspend <= 0) {
	  if (enablee != 0) {
	    suspendEnabled = suspendEnabled - 1;
	    doSuspend(enablee,true);
	    enablee = 0;
	  }
	}
      }
    fprintf(trace,"%i:\t",glsc);
    opCode = bc[glsc]; glsc = glsc + 1; 
    switch (opCode) {
      case pushthis:
	fprintf(trace,"pushthis\n");
	rPush(thisStack,thisObj);
	break;
      case pushC: 
	arg1 = op1();
	vpush(arg1);
	fprintf(trace,"pushc %i\n", arg1);
	break;
      case push:
	arg1 = op1();
	fprintf(trace,"push ");
	arg2 = thisObj->vfields[arg1];
	vpush(arg2);
	fprintf(trace,"%s[%i] = %i\n",nameOf(thisObj),arg1,arg2);
	break;
      case rpush:
	arg1 = op1();
	X = thisObj->rfields[arg1];
	fprintf(trace,"rpush ");
	fprintf(trace,"%s[%i] = %s \n",nameOf(thisObj),arg1,nameOf(X));
	rPush(thisStack,X);
	break;
      case pushg:
	arg1 = op1();
	X = rPop(thisStack);
	arg2 = X->vfields[arg1];
	fprintf(trace,"pushg %s[%i] = %i\n",nameOf(X),arg1,arg2);
	vpush(arg2);
	break;
      case rpushg:
	arg1 = op1();
	X = rPop(thisStack);
	Y = X->rfields[arg1];
	rPush(thisStack,Y);
	fprintf(trace,"rpushg %s[%i] = %s\n",nameOf(X),arg1,nameOf(Y));
	break;
      case xpush:
	arg1 = op1(); // off
	arg2 = vpop(); // inx
	arg3 = thisObj->vfields[arg1 + arg2];
	vpush(arg3);
	fprintf(trace,"xpush %s[%i+%i] = %i\n",nameOf(thisObj),arg1,arg2,arg3);
	break;
      case xpushg:
	arg1 = op1();
	X = rPop(thisStack);
	arg2 = vpop();
	arg3 = X->vfields[arg1 + arg2]; // need range check - and do we adjust for range?
	fprintf(trace,"xpushg %s[%i+%i] = %i\n",nameOf(X),arg1,arg2,arg3);
	vpush(arg3); 
	break;
      case store:
	arg1 = op1();
	arg2 = vpop(thisStack);
	fprintf(trace,"store %s[%i] = %i\n",nameOf(thisObj),arg1,arg2);
	thisObj->vfields[arg1] = arg2; 
     	break;
      case rstore:
	arg1 = op1();
	fprintf(trace,"rstore ");
	X = rPop(thisStack);
	thisObj->rfields[arg1] = X;
	fprintf(trace,"%s[%i] = %s\n",nameOf(thisObj),arg1,nameOf(X));
	break;
      case storeg:
	arg1 = op1(); // off/inx
	X = rPop(thisStack);
	arg2 = vpop(); // value
	fprintf(trace,"storeg %s[%i] = %i \n",nameOf(X),arg1,arg2);
	X->vfields[arg1] = arg2;
	break;
      case rstoreg:   
	arg1 = op1();
	X = rPop(thisStack);
	if ( X == 0) {
	  runTimeError("Reference is none");
	};
	Y = rPop(thisStack);
	X->rfields[arg1] = Y;
	fprintf(trace,"rstoreg %s[%i] = %s \n",nameOf(X),arg1,nameOf(Y));
	break; 
      case xstore:
	arg1 = op1();
	arg2 = vpop(); // inx
	arg3 = vpop(); // value;
	fprintf(trace,"xstore %s[%i+%i] = %i\n",nameOf(thisObj),arg1,arg2,arg3);
	thisObj->vfields[arg1 + arg2] = arg3;
	break;
      case xstoreg:
	arg1 = op1();
	X = rPop(thisStack);
	arg2 = vpop();
	arg3 = vpop();
	fprintf(trace,"xstoreg %s[%i+%i] = %i\n",nameOf(X),arg1,arg2,arg3);
	X->vfields[arg1 + arg2] = arg3;
	break;
      case _double:
	arg1 = vpop();
	fprintf(trace,"double %i\n",arg1);
	vpush(arg1);
	vpush(arg1);
	break;
      case rdouble:
	X = rPop(thisStack);
	fprintf(trace,"rdouble %s\n",nameOf(X));
	rPush(thisStack,X);
	rPush(thisStack,X);
	break;
      case rtn:
	arg1 = op1();
	fprintf(trace,"rtn %c ",arg1);
	if ((suspendEnabled == 1) && (thisObj == enablee)) 
	  suspendEnabled = suspendEnabled - 1;
	fprintf(trace,"FROM %s(%i,%i,%i) ",nameOf(thisObj),currentDescNo,glsc,bc);
	X = thisObj;
	thisStack = rPop(thisObj);
	thisObj = rPop(thisObj);
	glsc = restoreReturn(thisObj);
	currentDescNo = restoreReturn(thisObj);
	bc = codeFromDescNo(currentDescNo);
	//xglsc = glsc;
	//fprintf(trace,"\ndumpDesc: %i\n",currentDescNo);
	//dumpDesc(currentDescNo);
	//glsc = xglsc;
	fprintf(trace,"TO %s(%i,%i,%i)\n",nameOf(thisObj),currentDescNo,glsc,bc);
	rPush(thisStack,X);
	if (((char)arg1 == 'A') && (thisObj != X)){
	  return mkEvent(rtn_event,thisObj,X,myCorigin(X),false,glsc);
	}
	break;
      case mvStack:
	fprintf(trace,"mvStack %s -> %s\n",nameOf(thisObj),nameOf(thisStack));
	thisStack = thisObj;
	break;
      case call:
	return doCall(false);
	break;
      case susp:
	fprintf(trace,"susp ");
	callee = rPop(thisStack);
	if ((suspendEnabled == 1) && (callee == enablee)) suspendEnabled = suspendEnabled - 1;
	doSuspend(callee,false);
	break;
      case alloc:
	arg1 = op2();
	arg2 = op1();
	fprintf(trace,"alloc %i %i ",arg1,arg2);
	return allocObj(rPop(thisStack),arg1,arg2,0,0);
	break;
      case doExit:
	fprintf(trace,"doExit\n");
	thisStack = thisObj->rstack[thisObj->rtop];
	//return mkEvent(doExit_event,thisObj,thisStack,myCorigin(thisStack),false,glsc);
	break;
      case rtnExit:
	fprintf(trace,"rtnExit");
	runTimeError("rtnExit not implemented");
	break;
      case prim:
	arg1 = op1();
	fprintf(trace,"prim %i ",arg1);
	switch (arg1)
	  {
	  case 2: // put
	    arg2 = vpop();
	    fprintf(trace,"put \'%c\'\n",(char)arg2);
	    printf("%c",(char)arg2);
	    break;
	  case 10: // attach
	    arg2 = vpop();
	    fprintf(trace,"attach %i\n",arg2);
	    suspendEnabled = suspendEnabled + 1;
	    timeToSuspend = arg2;
	    //glsc = glsc - 1;
	    doCall(true);
	    break;
	  case 11: // disable
	    fprintf(trace,"disable\n");
	    suspendEnabled = suspendEnabled - 1;
	    break;
	  case 12: // enable
	    fprintf(trace,"enable\n");
	    suspendEnabled = suspendEnabled + 1;
	    break;
	  default:
	    printf("\n\n*** prim: missing case %i\n",arg1);
	    runTimeError("prim: missing case");
	  }
	break;
      case jmp:
	glsc = op2() - 1;
	fprintf(trace,"jmp %i\n",glsc);
	break;
      case jmpFalse:
	arg1 = op2();
	arg2 = vpop();
	fprintf(trace,"jmpFalse %i %i \n",arg1, arg2);
	if (arg2 == 0) glsc = arg1 - 1;
	break;
      case jmpGT:
	arg1 = vpop();
	arg2 = vpop();
	arg3 = op2();
	fprintf(trace,"jmpGT %i > %i -> %i \n",arg2,arg1,arg3 - 1);
	if (arg2 > arg1) glsc = arg3 - 1;
	break;
      case pushNone:
	fprintf(trace,"pushNone\n");
	rPush(thisStack,0);
	break;
      case rtnEvent:
	arg1 = op1();
	X = rPop(thisObj);
	fprintf(trace,"rtnEvent %i %s\n",arg1,nameOf(X));
	break;
      case saveBETAworld:
	fprintf(trace,"saveBETAworld\n");
	X = rPop(thisStack); // should be assigned to eventprocessor.rfields[1][]
	break;
      case doSuper:
	arg1 = op2();
	fprintf(trace,"doSuper %i\n",arg1);
	//saveReturn(thisObj,descNoOf(thisObj),glsc);
	//rPush(thisObj,thisObj);
	//rPush(thisObj,thisStack);
	//saveReturn(thisObj,currentDescNo,glsc);
	currentDescNo = arg1;
	bc = codeFromDescNo(arg1);
	glsc = getEnterE(getDesc(arg1));
	break;
      case innerx:
	arg1 = op1();
	fprintf(trace,"innerx %i",arg1);
	arg2 = vdtTable(thisObj,arg1); // descNo
	fprintf(trace,"\n");
	if (arg2 > 0) {
	  //saveReturn(thisObj,descNoOf(thisObj),glsc);
	  saveReturn(thisObj,currentDescNo,glsc);
	  currentDescNo = arg2;
	  bc = codeFromDescNo(arg2);
	  glsc = getDoE(getDesc(arg2));
	}
	break;
      case rtnInner:
	fprintf(trace,"returnInner\n");
	glsc = restoreReturn(thisObj);
	descNo = restoreReturn(thisObj);
	currentDescNo = descNo;
	bc = codeFromDescNo(descNo);
	break;
      case innerExit:
	arg1 = op1();
	fprintf(trace,"innerExit %i ",arg1);
	arg2 = vdtTable(thisObj,arg1);
	if (arg2 > 0) {
	  saveReturn(thisObj,currentDescNo,glsc);
	  bc = codeFromDescNo(arg2);
	  currentDescNo = arg2;
	  glsc = getExitE(getDesc(arg2));
	  fprintf(trace,"TO %i %i",currentDescNo,glsc);
	};
	fprintf(trace,"\n");
	break;
      case sendv: 
	arg1 = op1();
	X = rPop(thisStack);
	fprintf(trace,"sendv %i",arg1);
	arg2 = vdtTable(X,arg1); // descNo
	allocObj(X,arg2,false,0,0);
	break;
      case send: 
	fprintf(trace,"send %i",op1());
	runTimeError("send is not implemented");
	break;
      case newVrep:
	fprintf(trace,"newVrep");
	runTimeError("newVrep is not implemented");
	break;
      case jmpTrue:
	arg1 = op2();
	arg2 = vpop();
	fprintf(trace,"jmpTrue %i\n",arg1);
	if (arg2 == 1) glsc = arg1 - 1;
	break;
      case pushText:
	arg1 = op1();
	fprintf(trace,"pushText %i ",arg1);
	allocTextObj(arg1);
	break;
      case exeAlloc:
	arg1 = op2();
	fprintf(trace,"exeAlloc %i ",arg1);
	fprintf(trace,"FROM %s(%i,%i) ", nameOf(thisObj),currentDescNo,glsc);
	X = rPop(thisStack);
	saveReturn(thisObj,currentDescNo,glsc);
	rPush(thisObj,thisObj);
	rPush(thisObj,thisStack);
	thisStack = thisObj;
	rPush(thisObj,X);
	currentDescNo = arg1;
	bc = codeFromDescNo(arg1);
	glsc = getAllocE(getDesc(arg1));
	fprintf(trace,"TO %s(%i,%i)\n",nameOf(thisObj),currentDescNo,glsc);
	break;
      case rtnc:
	fprintf(trace,"rtnC");
	break;
      case rpop:
	fprintf(trace,"rpop\n");
	rPop(thisStack);
	break;
      case eq:
	arg1 = vpop();
	arg2 = vpop();
	fprintf(trace,"eq %i %i\n",arg1,arg2);
	if (arg1 == arg2) { vpush(1);} else vpush(0);
	break;
      case lt:
	arg1 = vpop();
	arg2 = vpop();
	fprintf(trace,"lt %i < %i\n",arg2,arg1);
	if (arg1 > arg2) { vpush(1);} else vpush(0);
	break;
      case le:
	arg1 = vpop();
	arg2 = vpop();
	fprintf(trace,"le %i <= %i\n",arg2,arg1);
	if (arg1 >= arg2) { vpush(1);} else vpush(0);
	break;
      case gt:
	arg1 = vpop();
	arg2 = vpop();
	fprintf(trace,"gt %i > %i\n",arg2,arg1);
	if (arg1 < arg2) { vpush(1);} else vpush(0);
	break;
      case ge:
	arg1 = vpop();
	arg2 = vpop();
	fprintf(trace,"ge %i >= %i\n",arg2,arg1);
	if (arg1 <= arg2) { vpush(1);} else vpush(0);
	break;
      case ne:
	arg1 = vpop();
	arg2 = vpop();
	fprintf(trace,"ne %i != %i\n",arg1,arg2);
	if (arg1 != arg2) { vpush(1);} else vpush(0);
	break;
      case req:
	X = rPop(thisStack);
	Y = rPop(thisStack);
	fprintf(trace,"req %i == %i\n",(int)X,(int)Y);
	vpush(X == Y);
	break;
      case rne:
	X = rPop(thisStack);
	Y = rPop(thisStack);
	fprintf(trace,"rne %i != %i\n",(int)X,(int)Y);
	vpush(X != Y);
	break;
      case plus:
	arg1 = vpop();
	arg2 = vpop();
	fprintf(trace,"plus %i + %i\n",arg1,arg2);
	vpush(arg1 + arg2);
	break;
      case minus:
	arg1 = vpop();
	arg2 = vpop();
	fprintf(trace,"minus %i - %i\n",arg2,arg1);
	vpush(arg2 - arg1);
	break;
      case orr: 
	arg1 = vpop();
	arg2 = vpop();
	fprintf(trace,"orr %i || %i\n",arg1,arg2);
	if ((arg1 == 1) || (arg2 ==1)) {vpush(1);} else vpush(0);
	break;
      case xorr:
	arg1 = vpop();
	arg2 = vpop();
	fprintf(trace,"Not mplemented xorr %i %i\n",arg1,arg2);
	if ((arg1 == 1) || (arg2 ==1)) {vpush(1);} else vpush(0);
	break;
      case nott:
	arg1 = vpop();
	fprintf(trace,"nott %i\n",arg1);
	if (arg1 == 0) {vpush(1);} else vpush(0);
	break;
      case mult:
	arg1 = vpop();
	arg2 = vpop();
	fprintf(trace,"mult %i * %i\n",arg1,arg2);
	vpush(arg1 * arg2);
	break;
      case rdiv:
	arg1 = vpop();
	arg2 = vpop();
	fprintf(trace,"\n**** rdiv is not implemented!\n\n");
	runTimeError(" rdiv is not implemented");
	break;
      case idiv:
	arg1 = vpop();
	arg2 = vpop();
	fprintf(trace,"idiv %i div %i\n",arg2,arg1);
	vpush(arg2 / arg1);
	break;
      case modd:
	arg1 = vpop();
	arg2 = vpop();
	fprintf(trace,"modd %i %i\n", arg2,arg1);
	vpush(arg2 % arg1);
	break;
      case andd:
	arg1 = vpop();
	arg2 = vpop();
	fprintf(trace,"andd %i %i\n",arg1,arg2);
	vpush(arg1 && arg2);
	break;
      case uminus:
	arg1 = vpop();
	fprintf(trace,"uminus %i\n",arg1);
	vpush(-arg1);
	break;
      case pushc2:
	arg1 = op2();
	fprintf(trace,"pushc2 %i\n",arg1);
	vpush(arg1);
	break;
      case allocIndexed:	
	arg1 = op2();
	arg2 = op1();
	fprintf(trace,"allocIndexed %i %i\n",arg1,arg2);
	X = rPop(thisStack);
	dinx = vpop();
	rangee = vpop();
	allocIndexedObj(X,arg1,arg2,dinx,rangee);
	break;
      case mkStrucRef: 
	arg1 = vpop();
	X = rPop(thisStack);
	fprintf(trace,"mkStrucRef %i %s\n",arg1,nameOf(X));
	allocStrucRefObj(X,arg1,false);
	break;
      case mkVirtualStrucRef:
	arg1 = op1();
	X = rPop(thisObj);
	fprintf(trace,"mkVirtualStrucRef %i %s\n",arg1,nameOf(X));
	allocStrucRefObj(X,arg1,true);
	break;
      case _allocFromStrucRefObj:
	X = rPop(thisStack);
	fprintf(trace,"allocFromStrucRefObj %s\n",nameOf(X));
	allocFromStrucRefObj(X);
	break;
      case _break:
	arg1 = op1();
	arg2 = op2();
	fprintf(trace,"break %i %i\n",arg1,arg2);
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
	glsc = restoreReturn(thisObj);
	currentDescNo = restoreReturn(thisObj);
	bc = codeFromDescNo(currentDescNo);
	glsc = xlabs(currentDescNo,arg2) - 1;
	//fprintf(trace,"popCallStackE %i %i\n",currentDescNo,glsc);
	break;
      case stop: 
	fprintf(trace,"stop: \n");
	running = false;
	break;
      default:
	fprintf(trace,"Op: %i ",bc[glsc]);
	runTimeError("Illegal byte code");
	break;
      }
    };
  return mkEvent(stop_event,0,0,0,0,0);
}

void close_interpreter(){
    fclose(trace);
}

