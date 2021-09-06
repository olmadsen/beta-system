/* ********************************************************************
 * qBeta interpreter: 
 * files for defining format and accessor functions for bytecode image
 ***********************************************************************/

/* Format of ObjDescs
   0: -xBeta--
   8: image size
   12: mainDescNo
   16: textDescNo
   20: strucRefDescNo
   24: indexOfStringtable 
   28: no of Object descriptors
   32: ObjDesc1
   ...: ...
    
   Format of ObjDesc:
   0: index of name in stringtable
   2: descNo 
   6: topDescNo  
   10: objSize - size of  fields
   14: isIndexed - indexed object
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
bool isXbeta; 
bool newAlloc = false;
int newAllocOff = 0;

//for Arduino, typdef apparently must be in the beginning of the file!?
typedef unsigned char * ObjDesc;

#ifdef __arm__
typedef unsigned char byte;
#endif

typedef struct Btemplate {
  ObjDesc desc;
  int id;
  int valOff;
  bool isObj; 
  int vstack[16];  
  struct Btemplate *rstack[16];
  int vtop; int rtop;
  int lscStack[16];
  int lscTop;
  int lsc;
  volatile int vfields[]; // flexible array
} Btemplate;

typedef struct Block {
  ObjDesc bc;  
  int glsc;
  int currentDescNo;
  Btemplate *thisModule,*thisObj,*thisStack,*callee,*enablee,*top,*world;
  int ID;
  int threadId;
  char *traceFile;
  FILE *trace;
  Btemplate * origin;
} Block;

typedef struct Event {
  int type;
  Btemplate *caller,*thisObj,*org;
  int isObj;
  int descNo;
  int bcPos;
} Event;

enum{
  imageSize_index = 8,
  mainDescInx_index = 12,
  textDescNo_index = 16,
  strucRefDescNo_index = 20,
  stringTable_index = 24,
  noOfObjDesc_index = 28,
};

enum {
  name_index = 0,
  descNo_index = 2,
  topDescNo_index = 6,
  objSize_index = 10,
  isIndexed_index = 14,
  originOff_index = 18,
  procE_index = 20,
  alloE_index = 22,
  enterE_index = 24,
  doE_index = 26,
  exitE_index = 28,
  labIndex = 30,
  literal_index = 34,
  GCinfo_index = 38,
  BC_index = 42,
  vdtTable_index = 46,
};


enum {
  dummy_event = 0,
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
  stop_event = 18,
  scan_event = 19
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
  sendx = 39 ,     
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
  xrpush = 81,
  xrstore = 82,
  xrpushg = 83,
  xrstoreg = 84,
  swap = 85,
  _rswap = 86,
  setThisStack = 87,
  toSuper = 88,
  innera = 89,
  invoke = 90,
  boxedInvokeVal = 91,
  innerP = 92,
  rpopThisObj = 93,
  rtnEventQ = 94,
  doEventQ = 95,
  allocEventQ = 96,
  invokeExternal = 97,
  invokeVal = 98,
  rtnV = 99,
  addOff = 100,
  ovpushg = 101, 
  ovstoreg = 102,
  vassign = 103,
  saveAndSetThis = 104,
  restoreThis = 105,
  pushValue = 106,
  tstOriginNone = 107,
  saveStringOrigin = 108,
  fplus =  109,
  fminus =  110,
  fmult =  112,
  fdiv =  121,   
  feq = 122,
  flt = 123,
  fle = 124,
  fgt = 125,
  fge = 126,
  fne = 127,
  pushFloatConst = 113,
  fstoreg = 114,
  fpushg = 115,
  i2f = 116,
  f2i = 117,
  fovpushg = 118,
  fovstoreg = 119,
  mkVindexed = 128,
  mkRindexed = 129
};


ObjDesc descs;

volatile unsigned char * stringTable;

// NB! The byte order is inconsistent - sometimes big somtimes little endian
unsigned int getInt2(int inx) {
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

int getMainDescInx(){
  return getInt4(mainDescInx_index);
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
  //int ix = noOfObjDesc_index + 4 + (descNo - 1) * 4;
  int inx = getInt4(noOfObjDesc_index + 4 + (descNo - 1) * 4);
  //if (descNo < 10) {
  //  printf("descNo: %i %i %i %i %i %i\n", descNo,inx,descs[ix+3],descs[ix+2],descs[ix+1],descs[ix+0]);

  //}
  //printf("descs: %i descNo %i descIndex: %i\n", descs, descNo, inx);
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

int op1(ObjDesc bc, int *glsc){
  int V = bc[*glsc]; 
  *glsc = *glsc + 1; 
  return V;
};
int op2(ObjDesc bc, int *glsc){ 
  int V = bc[*glsc] * 256 + bc[*glsc + 1];
  *glsc = *glsc + 2;
  return V;
};
int op4 (ObjDesc bc, int*glsc) {
  // used by pushFlotConst to get the two ints (4 bytes) from
  // the 8 bytes in the byte code representing the flot const
  int X; byte *P; int i;
  P = (byte *)&X;
  for (i = 0; i < 4; i++) {
    *P =  bc[*glsc + i];
    P = P + 1;
  }
  *glsc = *glsc + 4;
  return X;  
}
double op8(ObjDesc bc, int*glsc) {
  // gets the double representing the double from the 
  // 8 bytes in the byte code representing the flot const
  // not used!
  double X; byte *P; int i; 
  P = (byte *)&X;
  for (i = 0; i < 8; i++) {
    *P =  bc[*glsc + i];
    P = P + 1;
  }
  *glsc = *glsc + 8;
  return X;
}

int descNo(ObjDesc desc){
  return desc_getInt4(desc,descNo_index);
}

int objSize(ObjDesc desc){
  return desc_getInt4(desc,objSize_index);
}

int isIndexed(ObjDesc desc){
  return desc_getInt4(desc,isIndexed_index);
}


char * nameOf(Btemplate *obj){ 
  if (obj == 0) return "none";
  ObjDesc desc = obj->desc;
  int inx = desc_getInt2(desc,0);
  return getString(inx);
}


int topDescNo(Btemplate *obj){ return desc_getInt4(obj->desc,topDescNo_index); }

Btemplate *myCorigin(Btemplate *obj){ 
  int inx;
  inx = desc_getInt2(obj->desc,originOff_index);
  //printf("myCorigin: %i\n",inx);
  Btemplate * origin = 0;
  if (newAlloc){
    if (inx > 0) origin =(Btemplate *) obj->vfields[inx];
  }else{
    //if (inx > 0) origin = obj->rfields[inx];
  };
  return origin;
}


ObjDesc myCode(Btemplate *obj){
  return getByteCode(obj->desc);
}

ObjDesc mySuperCode(Btemplate *obj){
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

int vdtTable(FILE *trace,Btemplate *obj,int inx){
#ifdef TRACE
  fprintf(trace," vdtTable[%i] = %i "
	  ,inx,desc_getInt4(obj->desc,vdtTable_index + (inx -1 ) * 4));
#endif
  return desc_getInt4(obj->desc,vdtTable_index + (inx -1 ) * 4);
}

int getLiteralStart(Btemplate *obj){
  return desc_getInt4(obj->desc,literal_index);
};

int getLiteral(Btemplate *obj,int inx){
  int lit = desc_getInt2(obj->desc,getLiteralStart(obj) + (inx-1) *2);
  //printf("getLiteral %i %ch %i\n",inx,lit,lit);
  return lit;
}

int getGCinfoStart(Btemplate *obj){
  return desc_getInt4(obj->desc,GCinfo_index);
}

int getGCoff(Btemplate *obj,int inx){
  int off = desc_getInt2(obj->desc,getGCinfoStart(obj) + (inx-1) *2);
  return off;
}

