#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

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

int getStringTableIndex(){
  return getInt4(8);
};

ObjDesc getDesc(int descNo) {
  // returns start address of desctiptor descNo
  int inx = getInt2(8+4+4+(descNo - 1) * 2);
  // fprintf(trace,"descs: %i descNo %i descIndex: %i\n", descs, descNo, inx);
  if (inx > 0) {
    return descs + inx; }
  else 
    return 0;
}

ObjDesc getByteCode(ObjDesc desc) {
  return (ObjDesc) ((int) desc + 18);
}

ObjDesc alloc_main(int descNo) {
  ObjDesc desc = getDesc(descNo);
  fprintf(trace,"Main desc index: %i\n", desc);
  return desc;
}

ObjDesc bc;  
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
    fprintf(trace," %i:",length);
    i = i + 2;
    for (j=0; j<length; j++) fprintf(trace,"%c",descs[inx + i + j]);
    i = i + length;
  };
  fprintf(trace,"\n");
};

void dumpString(int inx) { //fprintf(trace,"dumpString %i\n",inx);
  int i,length = stringTable[4 + inx] + stringTable[4 + inx + 1];
  //fprintf(trace," %i:",length);
  for (i=0; i<length; i++) fprintf(trace,"%c",stringTable[4 + inx + 2 + i]);
}



void dumpCode(ObjDesc desc){
  int opCode,arg1,arg2,bcTop;
  bc = getByteCode(desc);
  bcTop = desc_getInt2(desc,16);
  glsc = 0;
  while(glsc < bcTop) {

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
	fprintf(trace,"rpushg: %i ", op1());
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
	fprintf(trace,"prim %i",op1());
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
	fprintf(trace,"rtnEvent %i ",bc[glsc+1]);
	glsc = glsc + 1;
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
	fprintf(trace,"pushc2 %i",op1());
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
      case allocFromStrucRefObj:
	fprintf(trace,"allocFromStrucRefObj");
	break;
      case _break:
	fprintf(trace,"OpXX: %i ",bc[glsc]);
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

void dumpDesc(int descNo) {
  ObjDesc desc;
  int i;
  if ((desc = getDesc(descNo)) > 0 ) {
    fprintf(trace,"\nClass %i ",descNo);
    //for (i=0; i <10; i++) fprintf(trace,"%i ",desc[i]);
    //fprintf(trace,"\n");
    //dumpString(getInt2(desc + 0 ));
    //    dumpString(desc[0] * 256 + desc[1]);
    dumpString(desc_getInt2(desc,0));
    fprintf(trace," descInx: %i originOff: %i\n", desc_getInt2(desc,2),desc_getInt2(desc,4));
    dumpCode(desc);
  }
}

void dumpDescriptors() {
  int descNo,noOfDescs = getInt4(12);
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

template * allocTemplate(int descNo,bool isObj){
  int i;
  template * obj = (template*)malloc(sizeof(template));
  obj->desc = getDesc(descNo);
  obj->id = newId();
  obj->isObj = isObj;
  obj->vtop = 0;
  obj->rtop = 0;
  obj->lscTop = 0;
  obj->lsc = 0;
  for (i = 0; i < 16; i++) {obj->vfields[i] = 0; obj->rfields[i] = 0;};
  // bc 
  return obj;
}

char * nameOf(template *obj){
  ObjDesc desc = obj->desc;
  int i,inx = desc_getInt2(desc,0);
  int length = stringTable[4 + inx] + stringTable[4 + inx + 1];
  char *name;
  name = malloc(length + 1);;
  for (i=0; i<length; i++) name[i] = stringTable[4 + inx + 2 + i];
  name[length] = 0;
  //fprintf(trace,"\nnameOf %i %s # %c %c %c %c #\n",length,name,name[0],name[1],name[2],name[3]);
  //for (i=0; i<length; i++) fprintf(trace,"%c",name[i]);
  return name;
}

void dumpObj(template *obj){
  fprintf(trace,"\n*** Object: id:%i\n",obj->id);
}

dumpName(ObjDesc desc) {
  dumpString(desc_getInt2(desc,0));
}

void allocMain(int descNo){ 
  thisModule = allocTemplate(descNo,true);
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
  ObjDesc D = getByteCode(getDesc(descNo));///!!!
}

void vpush(int V){
  if ((thisStack->vtop = thisStack->vtop + 1) > 16 ) fprintf(trace,"\n*** vstack overflow\n");
  thisStack->vstack[thisStack->vtop] = V;
}

void rPush(template *stack,template *R){
  //fprintf(trace,"\n*** rPush obj %i at %i \n",R->id,stack->rtop);
  if ((stack->rtop = stack->rtop + 1) > 16 ) fprintf(trace,"\n*** stack overflow\n");
  stack->rstack[stack->rtop] = R;
}

int vpop(){
  thisStack->vtop = thisStack->vtop - 1;
  return thisStack->vstack[thisStack->vtop + 1];
}

template * rPop(template *stack){
  template *R = stack->rstack[stack->rtop];
  // fprintf(trace,"\n*** rPop obj %i from %i \n",R->id,stack->rtop);
  stack->rtop = stack->rtop - 1;
  return stack->rstack[stack->rtop + 1];
}

void saveReturn(template *obj,int descNo, int lsc){
  if ((obj->lscTop = obj->lscTop + 2) > 16) fprintf(trace,"\n*** lsc stack overflow");
  obj->lscStack[obj->lscTop-1] = descNo;
  obj->lscStack[obj->lscTop] = lsc;
}

int restoreReturn(template * obj){
  // fprintf(trace,"\n***restoreReturn: %i\n",obj->lscTop);
  if (obj->lscTop <= 0) fprintf(trace,"\n**** ERROR:  lscStack underflow\n");
  int V = obj->lscStack[obj->lscTop];
  obj->lscTop = obj->lscTop - 1;
  return V;
}
void allocObj(template *origin,int descNo,bool isObj){
  template *Y;
  callee = allocTemplate(descNo,isObj);
  Y = thisObj;
  rPush(callee,thisObj);
  rPush(callee,thisStack);
  rPush(callee,origin);
  fprintf(trace,"\n***allocObj from %i %i %i %s ",thisObj,thisStack,glsc,nameOf(thisObj));
  saveReturn(thisObj,descNo,glsc);
  thisStack = callee;
  thisObj = thisStack;

  bc = (ObjDesc) myCode(thisObj);
  glsc = getAllocE(thisObj->desc);
  fprintf(trace," alloc: %i %s\n",descNo,nameOf(thisObj));
  //dumpObj(thisObj);
}

void allocIndexedObj(template * origin, int descNo,bool isObj, int dinx, int rangee){ fprintf(trace,"\n*** allocIndexedObj");
  allocObj(origin,descNo,isObj);
}

int getDescNo(template * obj){
  return desc_getInt2(obj->desc,2);
}
int getAllocE(ObjDesc obj){
  //fprintf(trace,"\n*** AllocE %i\n",desc_getInt2(obj,8) -1);
  return desc_getInt2(obj,8) - 1;
}
int getEnterE(ObjDesc obj){
  return desc_getInt2(obj,10) - 1;
}
int getDoE(ObjDesc obj){
  //fprintf(trace,"\n***getDoE %i %i\n", obj, desc_getInt2(obj,12));
  return desc_getInt2(obj,12) - 1;
}
int getExitE(ObjDesc obj){
  return desc_getInt2(obj,16) - 1;
}

void interpreter(char descs_a[], int mainDescNo) {
  int opCode,arg1,arg2,arg3,descNo;
  int dinx,rangee;
  bool running = true;
  template *X, *Y;

  trace = fopen("trace.s","w");

  descs = descs_a;
  bc = descs_a;

  fprintf(trace,"\nC interpreter: mainDescNo: %i\n",mainDescNo);
  int i;
  //  for (i=0; i < mainDescNo; i++) fprintf(trace,"%i: %i\n",i,descs[i]);
  fprintf(trace,"Main desc index: %i\n", getDesc(mainDescNo));

  allocMain(mainDescNo);

  bc = getByteCode(getDesc(mainDescNo));

  stringTable = descs + getStringTableIndex();

  dump_image();
  glsc = 0; 

  fprintf(trace,"**** Execute:\n\n");

  while (running)
    { opCode = bc[glsc]; glsc = glsc + 1; 
    //fprintf(trace,"\n*** Opcode: %i, glsc: %i\n",opCode,glsc);
    fprintf(trace,"%i:\t",glsc);
    switch (opCode)
      {
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
	fprintf(trace,"push %i ",arg1);
	vpush(thisObj->vfields[arg1]);
	fprintf(trace," V: %i\n",thisObj->vfields[arg1]);
	break;
      case rpush:
	arg1 = op1();
	X = rPop(thisStack);
	Y = thisObj->rfields[arg1];
	fprintf(trace,"rpush %s at %i : %s\n",nameOf(X),arg1,nameOf(Y));
	rPush(thisStack,Y);
	break;
      case pushg:
	arg1 = op1();
	X = rPop(thisStack);
	fprintf(trace,"pushg %i %i\n",arg1,X);
	vpush(X->vfields[arg1]);
	break;
      case rpushg:
	arg1 = op1();
	fprintf(trace,"rpushg %i ", arg1);
	X = rPop(thisStack);
	rPush(thisStack,X->rfields[arg1]);
	fprintf(trace," %i\n",X->rfields[arg1]);
	break;
      case xpush:
	arg1 = op1(); // off
	arg2 = vpop(); // inx
	vpush(thisObj->vfields[arg1 + arg2]);
	fprintf(trace,"xpush %i %i\n",arg1,arg2);
	break;
      case xpushg:
	fprintf(trace,"xpushg %i",op1());
	break;
      case store:
	arg1 = op1();
	fprintf(trace,"store %i\n",arg1);
	thisObj->vfields[arg1] = vpop(thisStack);
     	break;
      case rstore:
	arg1 = op1();
	fprintf(trace,"rstore: %i ",arg1);
	X = rPop(thisStack);
	thisObj->rfields[arg1] = X;
	fprintf(trace,"%i %s\n",X,nameOf(X));
	break;
      case storeg:
	arg1 = op1(); // off/inx
	X = rPop(thisStack);
	arg2 = vpop(); // value
	fprintf(trace,"storeg: %i %i %i \n",arg1,X,arg2);
	X->vfields[arg1] = arg2;
	break;
      case rstoreg:   
	fprintf(trace,"rstoreg: %\n",op1());
	break; 
      case xstore:
	arg1 = op1();
	arg2 = vpop(); // inx
	arg3 = vpop(); // value;
	fprintf(trace,"xstore: %i %i %i\n",arg1,arg2,arg3);
	thisObj->vfields[arg1 + arg2] = arg3;
	break;
      case xstoreg:
	fprintf(trace,"xstoreg: %i ",op1());
	break;
      case _double:
	arg1 = vpop();
	fprintf(trace,"double\n");
	vpush(arg1);
	vpush(arg1);
	break;
      case rdouble:
	fprintf(trace,"rdouble");
	break;
      case rtn:
	arg1 = op1();
	fprintf(trace,"rtn %c\n",arg1);
	// fix: suspendEnabled ...
	fprintf(trace,"***Rtn: from: %i %i %s ", (int)thisObj,(int)thisStack,nameOf(thisObj));
	X = thisObj;
	thisStack = rPop(thisObj);
	thisObj = rPop(thisObj);
	fprintf(trace,"to: %i %i %s ",(int)thisObj,(int)thisStack,nameOf(thisObj)); 
	glsc = restoreReturn(thisObj);
	descNo = restoreReturn(thisObj);
	bc = myCode(thisObj);
	fprintf(trace," %i %i\n",descNo,glsc);
	rPush(thisStack,X);
	// return event
	break;
      case mvStack:
	fprintf(trace,"mvStack\n");
	thisStack = thisObj;
	break;
      case call:
	arg1 = (char) op1();
	fprintf(trace,"call: %c ",arg1);
	callee = rPop(thisStack);
	fprintf(trace,"\n***call from %s %i ",nameOf(thisObj),getDescNo(thisObj));
	saveReturn(thisObj,getDescNo(thisObj),glsc);

	// check if resume
	Y = thisObj;
	rPush(callee,thisObj);
	rPush(callee,thisStack);
	thisObj = callee;
	bc = myCode(thisObj);
	bc = mySuperCode(thisObj); // must be fixed!
	fprintf(trace,"to %s %i ",nameOf(callee),getDescNo(callee));
	switch (arg1)
	  {
	  case 'N':
	    bc = myCode(thisObj);
	    glsc = getEnterE(thisObj->desc);
	    fprintf(trace," enter at %i'\n",glsc);
	    break;
	  case 'D':
	    bc = myCode(thisObj);
	    glsc = getDoE(thisObj->desc);
	    fprintf(trace,"do at %i'\n",glsc);
	    break;
	  case 'X':
	    bc = myCode(thisObj);
	    glsc = getExitE(thisObj->desc);
	    fprintf(trace,"exit at %i\n",glsc);
	    break;
	  }
	break;
      case alloc:
	arg1 = op2();
	arg2 = op1();
	fprintf(trace,"alloc: %i %i\n",arg1,arg2);
	allocObj(rPop(thisStack),arg1,arg2);
	break;
      case doExit:
	fprintf(trace,"doExit");
	break;
      case rtnExit:
	fprintf(trace,"rtnExit");
	break;
      case prim:
	arg1 = op1();
	fprintf(trace,"prim %i",arg1);
	switch (arg1)
	  {
	  case 2: // put
	    arg2 = vpop();
	    fprintf(trace," %c\n",(char)arg2);
	    printf("%c",(char)arg2);
	    break;
	  default:
	    fprintf(trace,"\n*** prim: missing case\n");
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
	fprintf(trace,"jmpGT %i\n",arg1,arg2);
	if (arg2 > arg1) glsc = arg3 - 1;
	break;
      case pushNone:
	fprintf(trace,"pushNone\n");
	rPush(thisStack,0);
	break;
      case rtnEvent:
	arg1 = op1();
	X = rPop(thisObj);
	fprintf(trace,"rtnEvent %i %i\n",arg1,X);
	break;
      case saveBETAworld:
	fprintf(trace,"saveBETAworld\n");
	X = rPop(thisStack); // should be assigned to eventprocessor.rfields[1][]
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
	arg1 = op2();
	fprintf(trace,"exeAlloc %i\n",arg1);
	fprintf(trace,"\n***exeAlloc %i %i %i %i\n",thisObj,thisObj,getDescNo(thisObj),glsc);
	X = rPop(thisStack);
	saveReturn(thisObj,getDescNo(thisObj),glsc);
	rPush(thisObj,thisObj);
	thisStack = thisObj;
	rPush(thisObj,thisStack);
	rPush(thisObj,X);
	bc = codeFromDescNo(arg1);
	glsc = getAllocE(getDesc(arg1));
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
	fprintf(trace,"lt %i %i\n",arg1,arg2);
	if (arg1 > arg2) { vpush(1);} else vpush(0);
	break;
      case le:
	arg1 = vpop();
	arg2 = vpop();
	fprintf(trace,"le %i %i\n",arg1,arg2);
	if (arg1 >= arg2) { vpush(1);} else vpush(0);
	break;
      case gt:
	arg1 = vpop();
	arg2 = vpop();
	fprintf(trace,"gt %i %i\n",arg1,arg2);
	if (arg1 < arg2) { vpush(1);} else vpush(0);
	break;
      case ge:
	arg1 = vpop();
	arg2 = vpop();
	fprintf(trace,"ge %i %i\n",arg1,arg2);
	if (arg1 <= arg2) { vpush(1);} else vpush(0);
	break;
      case ne:
	arg1 = vpop();
	arg2 = vpop();
	fprintf(trace,"ne %i %i\n",arg1,arg2);
	if (arg1 <= arg2) { vpush(1);} else vpush(0);
	break;
      case req:
	fprintf(trace,"req");
	break;
      case rne:
	fprintf(trace,"rne");
	break;
      case plus:
	arg1 = vpop();
	arg2 = vpop();
	fprintf(trace,"plus %i %i\n",arg1,arg2);
	vpush(arg1 + arg2);
	break;
      case minus:
	arg1 = vpop();
	arg2 = vpop();
	fprintf(trace,"minus %i %i\n",arg1,arg2);
	vpush(arg2 - arg1);
	break;
      case orr: 
	arg1 = vpop();
	arg2 = vpop();
	fprintf(trace,"orr %i %i\n",arg1,arg2);
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
	fprintf(trace,"mult %i %i\n",arg1,arg2);
	vpush(arg1 * arg2);
	break;
      case rdiv:
	arg1 = vpop();
	arg2 = vpop();
	fprintf(trace,"\n**** rdiv is not implemented!\n\n");
	break;
      case idiv:
	arg1 = vpop();
	arg2 = vpop();
	fprintf(trace,"idiv %i %i\n",arg2,arg1);
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
	fprintf(trace,"pushc2 %i\n",op2());
	break;
      case allocIndexed:	
	arg1 = op2();
	arg2 = op1();
	fprintf(trace,"allocIndexed %i %i\n",arg1,arg2);
	X = rPop(thisStack);
	dinx = vpop();
	rangee = vpop();
	allocIndexedObj(X,arg1,arg2,dinx,rangee);
	//...

	break;
      case mkStrucRef: 
	fprintf(trace,"mkStrucRef");
	break;
      case mkVirtualStrucRef:
	fprintf(trace,"mkVirtualStrucRef");
	break;
      case allocFromStrucRefObj:
	fprintf(trace,"allocFromStrucRefObj");
	break;
      case _break:
	fprintf(trace,"OpXX: %i ",bc[glsc]);
	break;
      case stop: 
	fprintf(trace,"stop: \n");
	running = false;
	break;
      default:
	fprintf(trace,"Op: %i ",bc[glsc]);
	break;
      }
    };
  fclose(trace);
}

