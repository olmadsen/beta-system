#include <stdio.h>
#include <stdbool.h>

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
  allocFromStrucRefObj = 77 ,
  rtnEvent = 78 ,
  _break = 79,
};

// We need 
// descs.OD = object descriptors/templates
// descs: ^RuntimeDescriptors
// RuntimeDescriptors:
//  (# OD: [*] ^ObjDesc, top: @integer
//      ...
//  #)
// ObjDesc:
//  (# name, descInx,originOff, superObjDesc
//     basicTemplate: 
//       (# vfields:
//       #)
//     template: BasciTemplate
//       (# rfields:
//          vstack:
//          rstack:
//          lscStack: 
//       #);
//    bc: @byteCode
//  #)

unsigned char *descs;

unsigned char * stringTable;

// NB! The byte order is inconsistent - sometimes big somtimes littel endian
int getInt2(int inx) {
  return descs[inx] * 256 + descs[inx + 1];
};
int getInt4(int inx){
  return descs[inx+3] * 256 * 256 * 256 + descs[inx + 2] * 256 * 256 
    + descs[inx + 1] * 256 + descs[inx];
}; 
int desc_getInt2(unsigned char * desc,int inx) {
  return desc[inx] * 256 + desc[inx + 1];
};
int getStringTableIndex(){
  return getInt4(8);
};
int getDesc(int descNo) {
  // returns start address of desctiptor descNo
  int inx = getInt2(8+4+4+(descNo - 1) * 2);
  // printf("descs: %i descNo %i descIndex: %i\n", descs, descNo, inx);
  if (inx > 0) {
    return descs + inx; }
  else 
    return 0;
}

int getByteCode(int desc) {
  return desc + 18;
}


int alloc_main(int descNo) {
  int desc = getDesc(descNo);
  printf("Main desc index: %i\n", desc);
  return desc;
}

char *bc;  
int glsc;
  
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

void dumpStringTable() {
  int inx, StringsSize,  i,j;
  inx = getStringTableIndex();
  StringsSize = getInt4(inx);
  i = 4;  
  while (i < StringsSize) {
    int length = getInt2(inx + i);
    printf(" %i:",length);
    i = i + 2;
    for (j=0; j<length; j++) printf("%c",descs[inx + i + j]);
    i = i + length;
  };
  printf("\n");
};

void dumpDescriptors() {
  int descNo,noOfDescs = getInt4(12);
  printf("Descriptors %i \n",noOfDescs);
  for (descNo=1; descNo < noOfDescs; descNo++) dumpDesc(descNo);
}

void dumpDesc(int descNo) {
  unsigned char * desc;
  int i;
  if ((desc = getDesc(descNo)) > 0 ) {
    printf("\nClass %i ",descNo);
    //for (i=0; i <10; i++) printf("%i ",desc[i]);
    //printf("\n");
    //dumpString(getInt2(desc + 0 ));
    //    dumpString(desc[0] * 256 + desc[1]);
    dumpString(desc_getInt2(desc,0));
    printf(" descInx: %i originOff: %i\n", desc_getInt2(desc,2),desc_getInt2(desc,4));
    dumpCode(desc);
  }
}
void dumpString(int inx) { //printf("dumpString %i\n",inx);
  int i,length = stringTable[4 + inx] + stringTable[4 + inx + 1];
  //printf(" %i:",length);
  for (i=0; i<length; i++) printf("%c",stringTable[4 + inx + 2 + i]);
}
void dumpCode(unsigned char *desc){
  int opCode,arg1,arg2,bcTop;
  bc = getByteCode(desc);
  bcTop = desc_getInt2(desc,16);
  glsc = 0;
  while(glsc < bcTop) {

    printf("%i:\t",glsc);
    opCode = bc[glsc]; glsc = glsc + 1; 
    switch (opCode)
      {
      case pushthis:
	printf("pushthis ");
	break;
      case pushC: 
	arg1 = op1();
	printf("pushC: %i", arg1);
	break;
      case push:
	printf("push %i",op1());
	break;
      case rpush:
	printf("rpush %i",op1());
	break;
      case pushg:
	printf("pushg %i",op1());
	break;
      case rpushg:
	printf("rpushg: %i ", op1());
	break;
      case xpush:
	printf("xpush %i",op1());
	break;
      case xpushg:
	printf("xpushg %i",op1());
	break;
      case store:
	printf("store %i",op1());
     	break;
      case rstore:
	printf("rstore: %i ",op1());
	break;
      case storeg:
	printf("storeg: %i ",op1());
	break;
      case rstoreg:   
	printf("rstoreg: %i ",op1());
	break; 
      case xstore:
	printf("xstore: %i ",op1());
	break;
      case xstoreg:
	printf("xstoreg: %i ",op1());
	break;
      case _double:
	printf("double");
	break;
      case rdouble:
	printf("rdouble");
	break;
      case rtn:
	printf("rtn %c ",op1());
	break;
      case mvStack:
	printf("mvStack");
	break;
      case call:
	arg1 = (char) op1();
	printf("call: %c ",arg1);
	break;
      case alloc:
	arg1 = op2();
	arg2 = op1();
	printf("alloc: %i %i\n",arg1,arg2);
	break;
      case doExit:
	printf("doExit");
	break;
      case rtnExit:
	printf("rtnExit");
	break;
      case prim:
	printf("prim %i",op1());
	break;
      case jmp:
	printf("jmp %i",op2());
	break;
      case jmpFalse:
	printf("jmpFalse %i",op2());
	break;
      case jmpGT:
	printf("jmpGT %i",op2());
	break;
      case pushNone:
	printf("pushNone");
	break;
      case rtnEvent:
	printf("rtnEvent %i ",bc[glsc+1]);
	glsc = glsc + 1;
	break;
      case saveBETAworld:
	printf("saveBETAworld ");
	break;
      case doSuper:
	printf("doSuper %i",op2());
	break;
      case innerx:
	printf("innerx %i",op1());
	break;
      case rtnInner:
	printf("returnInner");
	break;
      case innerExit:
	printf("innerExit %i",op1());
	break;
      case sendv: 
	printf("sendv %i",op1());
	break;
      case send: 
	printf("send %i",op1());
	break;
      case newVrep:
	printf("newVrep");
	break;
      case jmpTrue:
	printf("jmpTrue %i",op2());
	break;
      case pushText:
	printf("pushText %i",op1());
	break;
      case exeAlloc:
	printf("exeAlloc %i",op2());
	break;
      case rtnc:
	printf("rtnC");
	break;
      case rpop:
	printf("rpop");
	break;
      case eq:
	printf("eq");
	break;
      case lt:
	printf("lt");
	break;
      case le:
	printf("le");
	break;
      case gt:
	printf("gt");
	break;
      case ge:
	printf("ge");
	break;
      case ne:
	printf("ne");
	break;
      case req:
	printf("req");
	break;
      case rne:
	printf("rne");
	break;
      case plus: 
	printf("plus");
	break;
      case minus:
	printf("minus");
	break;
      case orr: 
	printf("orr");
	break;
      case xorr:
	printf("xorr");
	break;
      case nott:
	printf("nott");
	break;
      case mult:
	printf("mult");
	break;
      case rdiv:
	printf("rdiv");
	break;
      case idiv:
	printf("idiv");
	break;
      case modd:
	printf("modd");
	break;
      case andd:
	printf("andd");
	break;
      case uminus:
	printf("ne");
	break;
      case pushc2:
	printf("pushc2 %i",op1());
	break;
      case allocIndexed:
	printf("allocIndexed %i",op1());
	break;
      case mkStrucRef: 
	printf("mkStrucRef");
	break;
      case mkVirtualStrucRef:
	printf("mkVirtualStrucRef");
	break;
      case allocFromStrucRefObj:
	printf("allocFromStrucRefObj");
	break;
      case _break:
	printf("OpXX: %i ",bc[glsc]);
	break;
      case stop: 
	printf("stop: ");
	break;
      default:
	printf("Op: %i ",bc[glsc]);
	break;
      }
    printf("\n");
  };
  printf("\n");
}
void dump_image() {
  printf("%c%c%c%c%c%c%c%c\n"
	 ,descs[0],descs[1],descs[2],descs[3],descs[4],descs[5],descs[6],descs[7]);
  printf("StringTableIndex: %i\n",getStringTableIndex());
  dumpStringTable();
  dumpDescriptors();
}

typedef struct{
  int * desc;
  int id;
  bool isObj;
  int vfields[16];
  struct template *rfields[16];
  int vstack[16];
  struct template *rstack[16];
  int vtop; int rtop;
  int lscStack[8];
  int lscTop;
  int lsc;
} template;

template *thisModule,*thisObj,*thisStack, *callee;

int ID = 1000;

int newId() { ID = ID + 1; return ID;}

struct template * allocTemplate(int descNo,bool isObj){

  template * obj = (struct template*)malloc(sizeof(template));
  obj->desc = getDesc(descNo);
  obj->id = newId();
  obj->isObj = isObj;
  obj->vtop = 0;
  obj->rtop = 0;
  obj->lscTop = 0;
  obj->lsc = 0;
  // bc 
  return obj;
}

void dumpObj(template *obj){
  printf("\n*** Object: id:%i\n",obj->id);
}
void allocMain(int descNo){ 
  thisModule = allocTemplate(descNo,true);
  thisObj = thisModule;
  thisStack = thisModule;
}
unsigned char * myCode(template *obj){
  return getByteCode(obj->desc);
}

unsigned char * mySuperCode(template *obj){
  return(myCode(obj));
}

void allocObj(template *origin,int descNo,bool isObj){
  template *Y;
  callee = allocTemplate(descNo,isObj);
  Y = thisObj;
  rPush(callee,thisObj);
  rPush(callee,thisStack);
  rPush(callee,origin);
  saveReturn(thisObj,getDescNo(thisObj),glsc);
  thisStack = callee;
  thisObj = thisStack;

  bc = (unsigned char*)myCode(thisObj);
  glsc = getAllocE(thisObj->desc);
  //dumpObj(thisObj);
}
void vpush(int V){
  if ((thisStack->vtop = thisStack->vtop + 1) > 16 ) printf("vstack overflow\n");
  thisStack->vstack[thisStack->vtop] = V;
}

void rPush(template *stack,template *R){
  //printf("\n*** rPush obj %i at %i \n",R->id,stack->rtop);
  if ((stack->rtop = stack->rtop + 1) > 16 ) printf("stack overflow\n");
  stack->rstack[stack->rtop] = R;
}

template * rPop(template *stack){
  template *R = stack->rstack[stack->rtop];
  // printf("\n*** rPop obj %i from %i \n",R->id,stack->rtop);
  stack->rtop = stack->rtop - 1;
  return stack->rstack[stack->rtop +1 ];
}

int getDescNo(template *obj){
  return desc_getInt2(obj->desc,2);
}
int getAllocE(template *obj){
  //printf("\n*** AllocE %i\n",desc_getInt2(obj,8) -1);
  return desc_getInt2(obj,8) - 1;
}
int getEnterE(template *obj){
  return desc_getInt2(obj,10) - 1;
}
int getdoE(template *obj){
  return desc_getInt2(obj,12) - 1;
}
int getExitE(template *obj){
  return desc_getInt2(obj,16) - 1;
}

void saveReturn(template *obj,int descNo, int lsc){
  if ((obj->lscTop = obj->lscTop + 2) > 16) printf("lsc stack overflow");
  obj->lscStack[obj->lscTop-1] = descNo;
  obj->lscStack[obj->lscTop] = lsc;
}

int restoreReturn(template * obj){
  int V = obj->lscStack[obj->lscTop];
  obj->lscTop = obj->lscTop - 1;
  return V;
}
void interpreter(char descs_a[], int mainDescNo) {
  int opCode,arg1,arg2,descNo;
  template *X, *Y;
  descs = descs_a;
  bc = descs_a;

  printf("\nC interpreter: mainDescNo: %i\n",mainDescNo);
  int i;
  //  for (i=0; i < mainDescNo; i++) printf("%i: %i\n",i,descs[i]);
  printf("Main desc index: %i\n", getDesc(mainDescNo));

  allocMain(mainDescNo);

  bc = getByteCode(getDesc(mainDescNo));

  stringTable = descs + getStringTableIndex();

  dump_image();
  glsc = 0; 

  while ( glsc < 15)
    { opCode = bc[glsc]; glsc = glsc + 1; 
    //printf("Opcode: %i, glsc: %i\n",opCode,glsc);
    switch (opCode)
      {
      case pushthis:
	printf("pushthis\n");
	rPush(thisStack,thisObj);
	break;
      case pushC: 
	arg1 = op1();
	vpush(arg1);
	printf("pushC: %i\n", arg1);
	break;
      case push:
	printf("push %i",op1());
	break;
      case rpush:
	printf("rpush %i\n",op1());
	break;
      case pushg:
	printf("pushg %i",op1());
	break;
      case rpushg:
	arg1 = op1();
	printf("rpushg: %i\n", arg1);
	X = rPop(thisStack);
	rPush(thisStack,X->rfields[arg1]);
	break;
      case xpush:
	printf("xpush %i",op1());
	break;
      case xpushg:
	printf("xpushg %i",op1());
	break;
      case store:
	printf("store %i",op1());
     	break;
      case rstore:
	printf("rstore: %i\n",op1());
	break;
      case storeg:
	printf("storeg: %i ",op1());
	break;
      case rstoreg:   
	printf("rstoreg: %\n",op1());
	break; 
      case xstore:
	printf("xstore: %i ",op1());
	break;
      case xstoreg:
	printf("xstoreg: %i ",op1());
	break;
      case _double:
	printf("double");
	break;
      case rdouble:
	printf("rdouble");
	break;
      case rtn:
	arg1 = op1();
	printf("rtn %c\n",arg1);
	// fix: suspendEnabled ...
	X = thisObj;
	thisStack = rPop(thisObj);
	thisObj = rPop(thisObj);
	glsc = restoreReturn(thisObj);
	descNo = restoreReturn(thisObj);
	bc = myCode(thisObj);
	// return event
	break;
      case mvStack:
	printf("mvStack");
	break;
      case call:
	arg1 = (char) op1();
	printf("call: %c ",arg1);
	callee = rPop(thisStack);
	printf("\n ***call descNo: %i\n",getDescNo(thisObj));
	saveReturn(thisObj,getDescNo(thisObj),glsc);

	// check if resume
	Y = thisObj;
	rPush(callee,thisObj);
	rPush(callee,thisStack);
	bc = myCode(thisObj);
	bc = mySuperCode(thisObj); // must be fixed!
	switch (arg1)
	  {
	  case 'N':
	    // fix
	    break;
	  case 'D':
	    bc = myCode(thisObj);
	    glsc = getEnterE(thisObj->desc);
	    break;
	  case 'X':
	    break;
	  }
	break;
      case alloc:
	arg1 = op2();
	arg2 = op1();
	printf("alloc: %i %i\n",arg1,arg2);
	allocObj(rPop(thisStack),arg1,arg2);
	break;
      case doExit:
	printf("doExit");
	break;
      case rtnExit:
	printf("rtnExit");
	break;
      case prim:
	printf("prim %i",op1());
	break;
      case jmp:
	printf("jmp %i",op2());
	break;
      case jmpFalse:
	printf("jmpFalse %i",op2());
	break;
      case jmpGT:
	printf("jmpGT %i",op2());
	break;
      case pushNone:
	printf("pushNone");
	break;
      case rtnEvent:
	printf("rtnEvent %i ",bc[glsc+1]);
	glsc = glsc + 1;
	break;
      case saveBETAworld:
	printf("saveBETAworld\n");
	break;
      case doSuper:
	printf("doSuper %i",op2());
	break;
      case innerx:
	printf("innerx %i",op1());
	break;
      case rtnInner:
	printf("returnInner");
	break;
      case innerExit:
	printf("innerExit %i",op1());
	break;
      case sendv: 
	printf("sendv %i",op1());
	break;
      case send: 
	printf("send %i",op1());
	break;
      case newVrep:
	printf("newVrep");
	break;
      case jmpTrue:
	printf("jmpTrue %i",op2());
	break;
      case pushText:
	printf("pushText %i",op1());
	break;
      case exeAlloc:
	printf("exeAlloc %i\n",op2());
	break;
      case rtnc:
	printf("rtnC");
	break;
      case rpop:
	printf("rpop");
	break;
      case eq:
	printf("eq");
	break;
      case lt:
	printf("lt");
	break;
      case le:
	printf("le");
	break;
      case gt:
	printf("gt");
	break;
      case ge:
	printf("ge");
	break;
      case ne:
	printf("ne");
	break;
      case req:
	printf("req");
	break;
      case rne:
	printf("rne");
	break;
      case plus: 
	printf("plus");
	break;
      case minus:
	printf("minus");
	break;
      case orr: 
	printf("orr");
	break;
      case xorr:
	printf("xorr");
	break;
      case nott:
	printf("nott");
	break;
      case mult:
	printf("mult");
	break;
      case rdiv:
	printf("rdiv");
	break;
      case idiv:
	printf("idiv");
	break;
      case modd:
	printf("modd");
	break;
      case andd:
	printf("andd");
	break;
      case uminus:
	printf("ne");
	break;
      case pushc2:
	printf("pushc2 %i",op1());
	break;
      case allocIndexed:
	printf("allocIndexed %i",op1());
	break;
      case mkStrucRef: 
	printf("mkStrucRef");
	break;
      case mkVirtualStrucRef:
	printf("mkVirtualStrucRef");
	break;
      case allocFromStrucRefObj:
	printf("allocFromStrucRefObj");
	break;
      case _break:
	printf("OpXX: %i ",bc[glsc]);
	break;
      case stop: 
	printf("stop: ");
	break;
      default:
	printf("Op: %i ",bc[glsc]);
	break;
      }
    }
}

