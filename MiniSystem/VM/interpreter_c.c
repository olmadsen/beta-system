//#define _GNU_SOURCE 
//#define __ARDIUNO__  // just my attempt;-)
//#define usewinsock2
//#define usekbhit
#ifdef linux
//#warning "linux is defined!"
#include <unistd.h> // to get sleep function for linux

#elif defined  __CYGWIN__
   #ifdef usewinsock2
   #include <winsock2.h> // must be included first - for some reason?
   #endif
   #include <windows.h>
   //#include <ws2tcpip.h>

#elif defined __arm__
//#warning "__arm__ is defined!"
   #include "qb-arm/rpi-gpio.h"   
   #include "qb-arm/armc-uart.c"
   #include "qb-arm/led.c"
#endif

#ifdef __arm__
typedef void *FILE; 
#else
#include <stdio.h> 
#endif 
#include <math.h>
#include <stdlib.h>
#include <stdbool.h>

#ifdef linux
#include <string.h> 
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h> 
#include <pthread.h>
#include <sched.h>
#else
#include <string.h>
#endif

#ifdef __ARDIUNO__ 
#include "mraa.h"
#include "mraa/gpio.h"
#define LOW 0
#define HIGH 5
#elif defined __XTENSA__
#include <stdio.h>  
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"
#include "sdkconfig.h"
#include "freertos/semphr.h"

#define BLINK_GPIO 23 // CONFIG_BLINK_GPIO - compiler complains!? 
#endif

#ifdef __arm__
#else
#define DUMP
#endif

//#define TRACE
//#define EVENT
    
#define useBetaHeap true
//#define withGC 

#include "interpreter_image.c"
 
#define MAX_THREADS 10
int threadNo = 0;

/* thisBlock->threadId is the id of a given tread
 * The main program has threadId = 0
 * Threads started using fork has threadId = 1,2, ..., threadNo
 * Status of each thread is stored in threadStatus[threadId]
 * threadNo is number of threads started using fork
 * Note the system id of a forked thread is stored in 
 *     hThreadArray[threadId - 1], pthreadarray[threadId - 1], ...
 * This threadNo and threadId does not correspond: threadId = threadNo + 1
 * may be confusing
 */

#ifdef linux
  pthread_t pthreadArray[MAX_THREADS];
#elif defined  __CYGWIN__
  HANDLE  hThreadArray[MAX_THREADS];
#endif

typedef unsigned char byte;

void runTimeError(char *msg){
#ifdef __arm__
#else
  printf("\n\n*** Run-time error: %s\n\n",msg);
#endif
  exit(-1);
}

void RTE2(char *msg, int errNo){
#ifdef __arm__
#else
  printf("\n\n*** Run-time error: %s %i\n",msg,errNo); 
#endif 
  exit(-1);  
}  

#ifdef withGC
#define heapMax 500000
#else
#define heapMax 30000000
#endif

volatile unsigned char heap[heapMax]; // perhaps initialize to zero?
// perhaps use malloc to initialize heap?

int heapTop;

#ifdef linux
pthread_mutex_t mutex1 = PTHREAD_MUTEX_INITIALIZER; 
#elif defined  __CYGWIN__
HANDLE allocMutex;
#elif __XTENSA__ 
SemaphoreHandle_t mutex1 = NULL;
#endif

Btemplate *mainObj = NULL;
Btemplate *betaWorld = NULL;
Btemplate *stringOrigin = NULL;

void *mkEvent(int type,Btemplate *caller,Btemplate *thisObj,Btemplate *org
	      ,bool isObj,int currentDescNo,int bcPos);

Btemplate *getR(Btemplate *obj,int inx);
void putR(Btemplate *obj,int inx, Btemplate *X);

int getV(Btemplate *obj,int inx){ return obj->vfields[inx];};
void putV(Btemplate *obj,int inx, int V){ obj->vfields[inx] = V;};

// **************** Garbage collector ***********************
//#define traceGC_0
//#define traceGC_1
//#define traceGC_2

Btemplate *lastFreeInHeap;
int noOfFreeBlocks = 0;
int noOfUsedBlocks = 1; // First block in heap is in use
Btemplate * lastFreeStart = NULL;
Btemplate * nextUsed = NULL;

Btemplate *mapStart = NULL; // table for remapping references
Btemplate *mapEnd = NULL;
int mapInx = 0;

Btemplate * newHeapTop = NULL;
int newHT = 0;
int freedInHeap = 0;

int getIheap(Btemplate *R, int inx){
  return *(int*)((int)R + inx);
}
int putIheap(Btemplate *R, int inx, int V){
  *(int*)((int)R + inx) = V;
}
Btemplate *getBTheap(Btemplate *R, int inx){
  return (Btemplate *)*(int*)((int)R + inx);
}

Btemplate *putBTheap(Btemplate *R, int inx, Btemplate *S){
  *(int*)((int)R + inx) = (int)S;
}

void checkInHeap(Btemplate *obj){
  if ((int) obj > (int)&heap[heapTop] | (int)obj < 0) {
#ifdef __arm__
#else
    printf("\n\n*** GC error:\n");
    printf("Object not in heap: %8x %i\n",(int)obj,(int)obj);
    printf("          &heap[0]: %8x\n",(int)&heap[0]);
    printf("    &heap[heapTop]: %8x\n",(int)&heap[heapTop]);
#endif
    exit(-1);
  }
};

#ifdef __CYGWIN__
HANDLE awaitGC[MAX_THREADS];
#endif

int threadStatus[MAX_THREADS];
#define t_running 0
#define t_suspended 1
#define t_stopped 2

bool gcInProgress = false;

Block *contexts[MAX_THREADS];

void dumpObj(FILE *trace,char *name,Btemplate *X);
 
void waitAllThreadsStopped(Block *ctx) {
  //printf("waitAllThreadsStopped threadId: %i\n",ctx->threadId);
  int no;
  for (no = 0; no <= threadNo; no++) {
    if (no == ctx->threadId) {
      //printf("thisThreadId: %i\n",no);
    } else {
    loop:
      if (threadStatus[no] == t_running) {
	//printf("thread running: %i \n", no);
	//Sleep(100);
	goto loop;
      } else {
	//printf("thread not running: %i\n",no);
      }
    }
  }
}

void waitForGC(Block *ctx){
  //printf("waitForGC threadNo: %i\n",ctx->threadId);
  contexts[ctx->threadId] = ctx;
  threadStatus[ctx->threadId] = t_suspended;
 loop:
  //Sleep(100);
  //if (threadStatus[ctx->threadId] == t_suspended) goto loop;
  if (gcInProgress) goto loop;
  //printf("waitForGC resumed threadNo: %i\n",ctx->threadId);
}

int sizeOfDesc(Btemplate * root){
    ObjDesc desc = root->desc;
    int objZ = objSize(desc);
    int size = sizeof(Btemplate) + (objZ + 1 + 0) * sizeof(int);
    if (isIndexed(desc) == 1) {
      //printf("isIndexed ");
	/*int i;
	for (i = 0; i < 15; i++) printf("%i ",getV(root,i));
	printf("\n");*/
	/*for (i = 0; i < 400; i++) {
	  printf(" %i ",(int)*(char *)((int)root + i));
	  if ( i % 15 == 0) printf("\n");
	  }*/
	//printf("range:%i\n",getV(root,2));
	size = size + (getV(root,2) + 2) * sizeof(int);
    }
    return size;
}

void setMap(Btemplate *start, Btemplate *end,int noOfUsedBlocks){
  //if (end == NULL) printf("\n*** end is NULL\n");
  mapStart = (Btemplate *)((int)end - (noOfUsedBlocks * 4 * 2));
  mapStart = (Btemplate *) malloc((noOfUsedBlocks + 2)* 4 * 2);
  //mapEnd = (Btemplate *) ((int)end + 12);  
}

void findAndSetMap(Btemplate * firstFreeStart,int noOfFreeBlocks){
  //printf("\nFindAdSetMap:\n");
  Btemplate * start = firstFreeStart;

  while ((int)start != 0){
    int size = getIheap(start,0) - (int)start;
    //printf("size: %i\n",size);
    if ((size - 8) > (noOfFreeBlocks * 8)) {
      //printf("Bingo! %x %x\n",(int)start,getIheap(start,0));
      setMap(start,getBTheap(start,0),100);
      return;
    }
    /*printf("Free:%x: nextFwdUsed:%x nextFwdFree:%x nextBackFree:%x size: %i\n"
	   ,(int)start,getIheap(start,0),getIheap(start,4),getIheap(start,8)
	   ,getIheap(start,0) - (int)start);*/
    start = getBTheap(start,8);
  }
#ifdef __arm__
#else
  printf("\n\n*** GC error: ");
  printf("not enough space for reference map\n");
#endif
  /*printf("*** noOfFreeBlocks * 8: %i lastFreeSize - 8: %i\n"
    ,noOfFreeBlocks * 8,lastFreeSize - 8);*/
  runTimeError("Garbage collection disrupted\n");
}

void printFreeBlocks(Btemplate * firstFreeStart){
#ifdef __arm__
#else
  printf("\nFree blocks:\n");
#endif  
  Btemplate * start = firstFreeStart;

  while ((int)start != 0){
#ifdef __arm__
#else
    printf("Free:%x: nextFwdUsed:%x nextFwdFree:%x nextBackFree:%x size: %i\n"
	   ,(int)start,getIheap(start,0),getIheap(start,4),getIheap(start,8)
	   ,getIheap(start,0) - (int)start);
#endif
    start = getBTheap(start,8);
  }
}


void addMapRef(Btemplate * oldRef,Btemplate * newRef){
  //printf("addMapRef:%x index:%i old: %x adjust: %i new: %x\n"
  //	 , (int)mapStart,mapInx,oldRef,(int)oldRef - (int)newRef,newRef);
  putBTheap(mapStart,mapInx,oldRef);
  putIheap(mapStart,mapInx + 4,(int)oldRef - (int)newRef);
  mapInx = mapInx + 8;
  //printMapRef();
}

void printMapRef(){
  Btemplate *R;
  int inx;
#ifdef __arm__
#else
  printf("\nprintMap: mapStart: %x mapInx: %i\n",(int)mapStart,mapInx);
#endif
  for (inx = 0; inx < mapInx; inx = inx + 8) {
    R = getBTheap(mapStart,inx);
#ifdef __arm__
#else    
    printf("Ref:%x index:%i stoart: %x adjust: %x %i %s\n"
	   ,(int)mapStart,inx,(int)R, getIheap(mapStart, inx + 4),
    	   getIheap(mapStart, inx + 4),
    	   nameOf((Btemplate *) ((int)R - getIheap(mapStart, inx + 4))));
#endif    
  }
#ifdef __arm__
#else  
  printf("\n");
#endif
}

Btemplate * mapRef(Btemplate * oldRef){
  Btemplate * newRef, *R, *last;
  R = getBTheap(mapStart,0);
  //printf("mapRef: %x tryFirst: %x \n",(int)oldRef,(int)R);
  if ((int) oldRef < (int)R) return oldRef;
  int inx,lastInx;
  last = mapStart;
  lastInx = 0;
  for (inx = 8; inx < mapInx; inx = inx + 8) {
    R = getBTheap(mapStart,inx);
    //printf("  try: %x adjust: %i\n",(int)R, getIheap(mapStart, inx + 4));
    if (oldRef < R)  break;
    last = R;
    lastInx = inx;
  }
  newRef = (Btemplate *)((int) oldRef - getIheap(mapStart, lastInx + 4));
  /*printf("lastInx:%i  mapInx:%i\n",lastInx,mapInx);
    printf("mapRef:old: %x adj: %i \n",
    (int)oldRef,getIheap(mapStart, lastInx + 4));
    printf("new: %x %s\n",(int)newRef,nameOf(newRef)); */

  return newRef;
}

void doGCmark(Block *ctx,Btemplate *root, int level){
  if (root == NULL) return; 
  if (((int)getR(root,0) & 0x1)  == 1 ) {
    //fprintf(ctx->trace,"mark:root:already marked: %s\n",nameOf(root));
    return;
  }
  putV(root,0,1);

#if defined traceGC_1
  /*
  int j;
  for (j = 0; j < sizeof(Btemplate); j = j + 4) {
    fprintf(ctx->trace," %x ",getIheap(root,j - (sizeof(Btemplate) / 4)));
    }
  fprintf(ctx->trace,"\n");
  for (j = 0; j < 64; j = j + 4) {
    fprintf(ctx->trace," %x ",getIheap(root,j));
  }
  fprintf(ctx->trace,"\n");
  if (getIheap(root,0) == 0x61f114) {
    fprintf(ctx->trace,"Got 0x61f114\n");
    //root = (Btemplate *) ((int) root + 8);
    }
  */
#ifdef __arm__
#else  
  fprintf(ctx->trace,"*** mark:root: %x ",(int)root);
  fprintf(ctx->trace," %s\n",nameOf(root));
#endif
  
#endif
  /*printf("*** mark:root: %x ",(int)root);
  printf(" %s\n",nameOf(root));
  printf("desc: %x\n",root->desc);*/
  ObjDesc desc = root->desc;
  if (isIndexed(desc)) {
    Btemplate *RX = getR(root,1);

#if defined traceGC_3
#ifdef __arm__
#else    
    fprintf(ctx->trace,"Mark:GotIndexed: %x\n",RX);
    fprintf(ctx->trace,"Mark:GotIndexed: %x %s %x\n",(int)root,nameOf(root),RX);
#endif
    int j; for (j = 0; j < 40; j= j + 4) printf (" %x",getIheap(RX,j));
#ifdef __arm__
#else    
    fprintf(ctx->trace,"\n");
    fprintf(ctx->trace,"Mark:GotIndexed: %x %s %x %s \n",(int)root,nameOf(root),getR(root,1),nameOf(getR(root,1)));
#endif
#endif
    
    doGCmark(ctx,getR(root,1),level + 1);
  }
  //dumpGCinfo(thisBlock->trace,desc);
  int start = desc_getInt4(desc,GCinfo_index);
  int end = desc_getInt4(desc,BC_index);
  int i; 
  for (i = start; i < end; i = i + 2) {
    int refInx = desc_getInt2(desc,start + (i - start));
    Btemplate *R = (Btemplate *)getR(root,refInx);
    if (R != NULL) {
      //fprintf(ctx->trace,"AAA i:%i %s\n",i,nameOf(root));
      doGCmark(ctx,R,level + 1);
    }
  }
  if (root->rstack[0] != NULL) {
#ifdef __arm__
#else    
    printf("rstack != NULL: %x \n",(int)root->rstack[0]);
#endif
    exit(-1);
  }

  for (i=0; i < root->rtop; i++) {

#if defined traceGC_3
#ifdef __arm__
#else
    fprintf(ctx->trace,"rStack:%s %x\n",nameOf(root->rstack[i + 1]),root->rstack[i + 1]);
#endif
#endif
    doGCmark(ctx,root->rstack[i + 1],level + 1);

#if defined traceGC_3
#ifdef __arm__
#else    
    fprintf(ctx->trace,"\nend doGCmark:inner:2\n");
    ¤endif
#endif
#endif
  }
#if defined traceGC_3
#ifdef __arm__
#else
  fprintf(ctx->trace,"\nend doGCmark\n");
#endif
#endif
}

void doGCmarkContexts(){
  int no;
  Block *ctx;
  for (no = 0; no <= threadNo; no++) {
    ctx = contexts[no];
    if (ctx != NULL) {
#if defined traceGC_1
#ifdef __arm__
#else
      fprintf(ctx->trace,"***  Mark thisObj: %x %s\n",ctx->thisObj,nameOf(ctx->thisObj));
      fprintf(ctx->trace,"***  Mark thisStack: %x %s\n",ctx->thisStack,nameOf(ctx->thisStack));
      fprintf(ctx->trace,"***  Mark world: %x %s\n",ctx->world, nameOf(ctx->world));
#endif
#endif
      doGCmark(ctx,ctx->thisObj,0);
      doGCmark(ctx,ctx->thisStack,0);
      if (ctx->thisModule != NULL) doGCmark(ctx,ctx->thisModule,0);
      if (ctx->enablee != NULL) doGCmark(ctx,ctx->enablee,0);
      if (ctx->top != NULL) doGCmark(ctx,ctx->top,0);
      //printf("f %x\n",(int)ctx->origin);
      if (ctx->origin != NULL) doGCmark(ctx,ctx->origin,0);
      doGCmark(ctx,ctx->world,0);
    }
  }
}

void printBlocks(Btemplate *root){
  int index = 0;
  int noOfUsedBlocks = 1; // First block is in use
  Btemplate *lastBlock = root;
  bool inMarked = true;
  Block *ctx;
  //for (no = 0; no <= threadNo; no++) {
  ctx = contexts[0];
#ifdef __arm__
#else
  fprintf(ctx->trace,"\n***  StartOfBlocks: %x\n",(int)root);
#endif  
  while ((int) root < (int)lastFreeInHeap) {
    /*
      fprintf(ctx->trace,"WWWW root: %x lastFreeInheap: %x\n",(int)root,(int)lastFreeInHeap);
      int i;
      for (i = -4; i < 64; i = i + 1) {
      fprintf(ctx->trace,"i:%3i, %x = %8x, %8i\n"
      ,i
      ,(int)root + i
      ,*((int *)(int)root + i)
	      ,getV(root,i));
	      }
	      fprintf(ctx->trace,"WWWW root: %x %s\n",(int)root,nameOf(root));
	      fprintf(ctx->trace,"size: %i\n",sizeOfDesc(root));
	      fprintf(ctx->trace,"V0: %i\n",getV(root,0));
    */
    int objZ = objSize(root->desc);
    /*fprintf(ctx->trace,"objSize: %i  Btemplate:%i  %i\n"
	    , objZ
	    , sizeof(Btemplate)
	    , sizeof(Btemplate) + (objZ + 1 + 0) * sizeof(int)
	    );
    */
    int size = sizeOfDesc(root);
    if (getV(root,0) == 1) { 
      if (inMarked == false) {
	int i;
	/*
	fprintf(ctx->trace,"\nthis: %x %x %x \n",
		getV(root,0),
		getV(root,1),
		getV(root,2));

	for (i = 0; i < sizeOfDesc(root); i = i + 1) {
	  fprintf(ctx->trace,"%x[i]:%i=%c %x, ",
		  (int)root+sizeof(Btemplate) + i,
		  i,getV(root,i),getV(root,i));
	  if (i % 8 == 0) fprintf(ctx->trace,"\n");
	}
	
	fprintf(ctx->trace,"\n next: %x %x %x %x %x\n",
		getV((Btemplate *)(int)root + size,0),
		getV((Btemplate *)(int)root + size,1),
		getV((Btemplate *)(int)root + size,2),
		getV((Btemplate *)(int)root + size,3),
		getV((Btemplate *)(int)root + size,4)
		);
	fprintf(ctx->trace,"***   NewUsedBlock: %x sizeOfPred: %i\n"
	,(int)root, (int)root - (int)lastBlock);*/
	lastBlock = root;
	noOfUsedBlocks = noOfUsedBlocks + 1;
	inMarked = true;
      }
    }else {
      if (inMarked) {
	/*fprintf(ctx->trace,"***   NewFreeBlock: %x sizeOfPred: %i\n"
	  ,(int)root, (int)root - (int)lastBlock);*/
	lastBlock = root;
	inMarked = false;
      }
    }
#ifdef __arm__
#else    
    fprintf(ctx->trace,"KUK: size: %i\n",size);
#endif    
    root = (Btemplate *)((int)root + size);
#ifdef __arm__
#else
    fprintf(ctx->trace,"KUK:B\n");
#endif
  }
#ifdef __arm__
#else  
  fprintf(ctx->trace,"KIKS:B\n");
  fprintf(ctx->trace,"*** lastFreeInHeap: %x sizeOfPred: %i noOfUsedBlocks: %i\n"
	 ,(int)lastFreeInHeap,(int)lastFreeInHeap - (int)lastBlock
	 ,noOfUsedBlocks);
#endif  
}


Btemplate * doGCsweep(Block *ctx,Btemplate *root){
  int used = 0, free = 0;
  Btemplate *firstFreeStart = NULL, *firstFreeEnd = NULL, *lastUnmarked = NULL;
  Btemplate *unmarkedEnd = NULL;
#ifdef traceGC_1
#ifdef __arm__
#else
  fprintf(ctx->trace,"\n***** doGCsweep *****\n");
#endif
#endif
  while ((int) root < (int)lastFreeInHeap) {
    int size = sizeOfDesc(root);
#if defined traceGC_2
#ifdef __arm__
#else    
    fprintf(ctx->trace,"sweep:root:%x ",root);
    fprintf(ctx->trace,"%s %i ", nameOf(root),size);
#endif
    #endif
    if (getV(root,0) == 1) { 
      //int i;
      //for (i = 0; i < 10; i++) printf("i:%i V:%x\n",i, getV(root,i));
      //printf("root[0]:%x ",getR(root,0));
      putV(root,0,0);
#if defined traceGC_2
#ifdef __arm__
#else      
      fprintf(ctx->trace,"marked\n");
#endif
#endif
      if (lastUnmarked != NULL) {
	if (lastFreeStart != NULL) { // previous free block points to this block
	  *(int*)((int)lastFreeStart + 4) = (int)lastUnmarked;
	}
	noOfUsedBlocks = noOfUsedBlocks + 1;
	unmarkedEnd = root;
	putBTheap(lastUnmarked,8,lastFreeStart);
	lastFreeStart = lastUnmarked;
	nextUsed = unmarkedEnd;

	*(int*)lastFreeStart = (int)nextUsed;  //nextUsedBlock
	*(int*)((int)lastFreeStart + 4) = 0;

	if (firstFreeStart == NULL) {
	  firstFreeStart = lastFreeStart;
	  firstFreeEnd= nextUsed;
	}
	noOfFreeBlocks = noOfFreeBlocks + 1;
#if defined traceGC_2
#ifdef __arm__
#else
	fprintf(ctx->trace,"\n-----Free interval %x %x %5i\n\n"
	       ,(int)lastUnmarked,(int)unmarkedEnd - 4,(int)unmarkedEnd - (int)lastUnmarked);
#endif
#endif
	lastUnmarked = NULL;
      }
      used = used + size;
    }else {
#if defined traceGC_2
#ifdef __arm__
#else      
      fprintf(ctx->trace,"notMarked\n");
#endif
#endif
      free = free + size;
      freedInHeap = freedInHeap + size;
      if (lastUnmarked == NULL) {// met an unMarked obj
	lastUnmarked = root;
      }
    }
    /*printf("sweep:1:\n");
    int i,v; v = (int)root->desc;
    printf("rootA: %x desc: %x\n",(int)root,v);*/

    root = (Btemplate *)(((int) root) + size);
    //printf("sweep:2: %x lastFreeInHeap: %x\n",(int)root,(int)lastFreeInHeap);
    /*for (i = 0; i < 10; i++) printf(" %x ",getV(root,i));
    printf("\n");
    printf("rootB: %x lastFreeInHeap: %x\n",(int)root,(int)lastFreeInHeap);*/
    /*v = (int)root->desc;
    if (v == 0) { printf("v==0\n"); root = (Btemplate *)((int)root + 4); }// ???
    */
    /*printf("rootB: %x lastFreeInHeap: %x desc: %x\n",(int)root,(int)lastFreeInHeap,v);
      for (i = 0; i < 40; i = i + 4) printf(" %x ",*(int *)((int)root + i));
      printf("\n");*/
  }
  if (lastFreeStart == NULL) {
    lastFreeStart = lastUnmarked;
    noOfFreeBlocks = 1;
    nextUsed = lastFreeInHeap; // hack 
  }
  if (free < 500) {
#ifdef __arm__
#else
    printf("\n\nOBS! ****** no free space in heap, free: %i\n",free);
    runTimeError("Garbage collection terminated");
#endif
  }
#if defined traceGC_2
#ifdef __arm__
#else
  fprintf(ctx->trace,"sweep:Z %x %x \n",(int)lastUnmarked,(int)lastFreeStart);
  /* printf("done: lastUnmarked: %x %s lastFreeStart: %x %s\n"
     ,(int)lastUnmarked,nameOf(lastUnmarked),(int)lastFreeStart,nameOf(lastFreeStart));*/
#endif
#endif
  
  *(int*)((int)lastFreeStart + 4) = (int)lastUnmarked;
  if (lastUnmarked != NULL) {
    *(int*)((int)lastUnmarked) = 0;
    *(int*)((int)lastUnmarked + 4) = 0;
  }
  // printf("*** noOfUsedBlocks: %i lastUnMarked: %x\n"
  //	 ,noOfUsedBlocks,(int)lastUnmarked);
  setMap(lastFreeStart,lastUnmarked,noOfUsedBlocks); // what if NULL?
  newHT = used;

#if defined traceGC_1
#ifdef __arm__
#else  
  fprintf(ctx->trace,"\nheapMax:%i used:%i Free:%i free blocks: %i newHeapTop:%i"
	 ,heapMax,heapMax - free,free,noOfFreeBlocks,newHT);
  fprintf(ctx->trace,"\nFirst free: %x %x Last free: %x %x "
	 ,(int)firstFreeStart, (int)firstFreeEnd - 4
	 ,(int)lastFreeStart,(int)nextUsed - 4);
#endif  
#endif

  return firstFreeStart;
}

void doGCcompact(Block *ctx,Btemplate *root, Btemplate *firstFreeStart){
  //int mapStart = (int)firstFreeStart + 4;
  //int mapEnd = (int)firstFreeStart + (noOfFreeBlocks - 1 ) * 8;
  int lastFreeSize = (int)nextUsed - (int)lastFreeStart;

#if defined traceGC_1

#ifdef __arm__
#else  
  fprintf(ctx->trace,"\n**** doGCcompact: root:%x firstFreeStart:%x \n",
	 (int)root,(int)firstFreeStart);
  fprintf(ctx->trace,"**** noOfFreeBlocks: %i lastFreeSize: %i \n", 
	 noOfFreeBlocks,lastFreeSize);
#endif
#endif
  
  Btemplate * nextUsed,* nextFree;
  int nextUsedSize;
  Btemplate *free = firstFreeStart;
  newHeapTop = free;
  while (free != NULL) {
    nextUsed = getBTheap(free,0);
    nextFree = getBTheap(free,4);
    if (nextUsed != 0) {
      if (nextFree != 0) {
	nextUsedSize = (int)nextFree - (int)nextUsed;
      } else 
	nextUsedSize = (int)(int)lastFreeInHeap - (int)nextUsed;
      /*printf("\nFree:%x nextUsed:%x %s, nextUsedSize:%i nextFree:%x newHeapTop: %x\n",
          (int)free,(int)nextUsed,nameOf(nextUsed),nextUsedSize,nextFree,newHeapTop);      
      printf("before:memcpy \n");
      printf("newHeapTop: %x nextUsedSize: %x\n",(int)newHeapTop,nextUsedSize);
      printf("endOfBlock: %x\n", (int)((int)newHeapTop + nextUsedSize));
      printf("nextUsed: %x\n",(int)nextUsed);
      printMapRef();*/
      memcpy((void *)newHeapTop,(void *)nextUsed,nextUsedSize);
      /*printf("after:memcpy\n");
      printMapRef();
      printf("memcpy: from: %x to: %x %s\n",nextUsed,newHeapTop,nameOf(newHeapTop));*/
      addMapRef(nextUsed,newHeapTop);
      newHeapTop = (Btemplate *)((int)newHeapTop + nextUsedSize);      
    }
    free = nextFree;
  }
#if defined traceGC_1
  fprintf(ctx->trace,"\n**** GCcompact done: newHeapTop: %x  heapTop: %x freed:%i\n",
	 newHeapTop,(int)&heap[heapTop], (int)&heap[heapTop] - (int)newHeapTop);
#endif
}

void doGCupdateRefs(Block *ctx,Btemplate *root){
  //printf("\n\n*** UpdateRefs: %x %s\n\n",(int)root,nameOf(root));
  //printMapRef();
  //printf("\n*** sweep of new heap betaWorld: %x\n",betaWorld);

#if defined traceGC_1
#ifdef __arm__
#else
  fprintf(ctx->trace,"newHeapTop: %x \n\nUpdating trefs: \n\n",(int)newHeapTop);
#endif
#endif
  while ((int)root < (int)&heap[heapTop]) {//newHeapTop) {
    ObjDesc desc = root->desc; 

#if defined traceGC_3
#ifdef __arm__
#else
    fprintf(ctx->trace,"Update: %x %s size:%i\n",(int)root,nameOf(root),sizeOfDesc(root));
#endif
#endif    
    Btemplate *R, *Rn;

    if (isIndexed(desc)) {
#if defined traceGC_3
#ifdef __arm__
#else      
      fprintf(ctx->trace,"Update_isIndexed: %x %s",(int)root,nameOf(root));
#endif
#endif      
      // Here we apparantly update origin which is in field: 1
      R = getR(root,1);
      Rn = mapRef(R);
      if (Rn != R) putR(root,1,Rn);

#if defined traceGC_3
      fprintf(ctx->trace," oldOrigin: %x newOrigin:%x %s\n",(int)R,(int)Rn,nameOf(Rn));
#endif

    }
    int start = desc_getInt4(desc,GCinfo_index);
    int end = desc_getInt4(desc,BC_index);
    int i,v;

#if defined traceGC_3
#ifdef __arm__
#else    
    fprintf(ctx->trace,"\n\n** Root:name: %s start:%i end:%i first:%i :: \n"
	    ,nameOf(root),start,end, getR(root,1));
#endif
#endif    
    for (i = start; i < end; i = i + 2) {
      v = desc_getInt2(desc,start + (i - start));
      if (isIndexed(desc) & (v == 1)) {
	// if V == 1, we have a ref in field:1, which is origin and has
	// already been updated above
	//perhaps we should not update origin above?
	//printf("OBS! isIndexed: origin twice!?\n");
	//fprintf(ctx->trace,"OBS! isIndexed: origin twice!?\n");
      }
      
      R = getR(root,v);
      Rn = mapRef(R);
      if (Rn != R) putR(root,v,Rn);

#if defined traceGC_3
#ifdef __arm__
#else      
      fprintf(ctx->trace,"   Map:%i oldOrg: %x ",v,(int)R);
      fprintf(ctx->trace,"newOrg:%x ",(int)Rn);
      fprintf(ctx->trace," name: %s \n",nameOf(Rn));
#endif
#endif
    }
    for (i=0; i < root->rtop; i++) {
      R = root->rstack[i + 1];
      Rn = mapRef(R);
      if (Rn != R) {
	root->rstack[i + 1] = Rn;
	//printf("rStack:oldRef:%x ",(int)R);
	//printf(" new: %x %s\n",(int)Rn,nameOf(Rn));
      }
    }
    root = (Btemplate *)((int) root + sizeOfDesc(root));
  }
  int no;
  for (no = 0; no <= threadNo; no++){
    Block *cty = contexts[no];
    if (cty != NULL) {
#if defined traceGC_1
#ifdef __arm__
#else      
      fprintf(ctx->trace,"mapRef: thisObj: %x  new: %x %s\n"
	     ,cty->thisObj,mapRef(cty->thisObj),nameOf(mapRef(cty->thisObj)));
#endif
#endif
      cty->thisObj = mapRef(cty->thisObj);
      cty->thisStack = mapRef(cty->thisStack);
      cty->callee = mapRef(cty->callee);
      cty->thisModule = mapRef(cty->thisModule);
      cty->enablee = mapRef(cty->enablee);
      cty->top = mapRef(cty->top);
      cty->world = mapRef(cty->world);
      cty->origin = mapRef(cty->origin);
    }
  }
}

void doGCclearHeap() {
  int i;
  for (i = heapTop; i < heapMax; i++) {heap[i] = 0; }
}

#ifdef __CYGWIN__
void suspendThreads(Block *ctx){
#ifdef __arm__
#else  
  printf("\n**** Suspend threads: thisThreadId: %i threadNo: %i\n", 
	 ctx->threadId, threadNo);
#endif  
  int no;
  for (no = 0; no < threadNo; no++) {
#ifdef __arm__
#else    
    printf("\nTry suspend:threadNo: %i threadId: %i",no, no + 1);
#endif    
    // suspend main thread

    if (ctx->threadId > 0)
#ifdef __arm__
#else      
      printf("sysThreadId: %i\n",(int)hThreadArray[no]);
#endif
    else
#ifdef __arm__
#else      
      printf("main thread\n");
#endif    
    if (no != (ctx->threadId - 1)) {
      if (hThreadArray[no] != NULL) {
#ifdef __arm__
#else	
	printf("\n--- Suspend threadNo: %i threadId: %i\n",no, no + 1);
#endif	
	if (SuspendThread(hThreadArray[no]) < 0 )
#ifdef __arm__
#else	  
	  printf("\n**** SuspendThread failed\n");
#endif	
      } else {
#ifdef __arm__
#else	
	printf("\n--- do not suspend threadNo: %i threadId: %i\n",no, no + 1);
#endif
      }
    }
    else
#ifdef __arm__
#else
      printf("\n--- do not suspend main thread\n");
#endif
#ifdef __arm__
#else
    printf("\n....................\n");
#endif
  }
}
#endif

void resumeThreads(Block *ctx){
  /*printf("\n**** Resume threads: thisThreadId: %i subThreadNo: %i noOfSubThreads: %i\n", 
    ctx->threadId, ctx->threadId - 1,threadNo);*/
  int no;
  for (no = 0; no <= threadNo; no++){
    if (threadStatus[no] == t_suspended) {
      threadStatus[no] = t_running;
      //printf("Resumed:threadId: %i\n",no);
    }
  }
  //printf("\nend of resumeThreads\n");
}

void doGCcheckHeap(Btemplate *root){

  while((int)root < (int)&heap[heapTop]) {
#ifdef __arm__
#else    
    printf("Obj: %x %s\n",(int)root,nameOf(root));
#endif
    ObjDesc desc = root->desc;
    if (isIndexed(desc)) {
      checkInHeap(root);
#ifdef __arm__
#else      
      printf("   origin: %x",(int)getR(root,1));
      printf(" %s\n",nameOf(getR(root,1)));
#endif      
    }
    int start = desc_getInt4(desc,GCinfo_index);
    int end = desc_getInt4(desc,BC_index);
    int i; 
    for (i = start; i < end; i = i + 2) {
      int refInx = desc_getInt2(desc,start + (i - start));
      Btemplate *R = (Btemplate *)getR(root,refInx);
      checkInHeap(R);
#ifdef __arm__
#else
      printf(" %2i: %6x",refInx,(int)R);
#endif
#ifdef __arm__
#else
      if (R != NULL) {
	printf(" %s\n",nameOf(R));
      } else printf(" NONE\n");
#endif
    }
    root = (Btemplate *)((int) root + sizeOfDesc(root));
  }
}
void doBGC(Block *ctx,Btemplate *root){
  //fprintf(ctx->trace,"doBGC\n");
#ifdef __arm__
  putstr("**** doBGC:\n");
#endif
  noOfFreeBlocks = 0;
  noOfUsedBlocks = 1; // First block in heap is in use
  lastFreeStart = NULL;
  nextUsed = NULL;
  mapStart = NULL; 
  mapEnd = NULL;
  mapInx = 0;
  newHeapTop = NULL;
  newHT = 0;
  freedInHeap = 0;
  Btemplate *firstFreeStart;

#if defined traceGC_0
#ifdef __arm__
#else  
  fprintf(ctx->trace,"\n<GC threadNo: %i ...",ctx->threadId);
#endif
#endif
  gcInProgress = true;
  contexts[ctx->threadId] = ctx;
  waitAllThreadsStopped(ctx);
  int no; 
  for (no = 0; no <=threadNo; no++) 
    if (no != ctx->threadId) 
      if (threadStatus[no] == t_running) 
#ifdef __arm__
#else
	printf("thread is running: %i threadId: %i\n",no,ctx->threadId);
#endif
#ifdef TRACE
  fprintf(ctx->trace,"\n***** doGC *****\n");
#endif
#if defined traceGC_1
#ifdef __arm__
#else
  fprintf(ctx->trace,"\n*****dogc: lastFreeInHeap: %x \n",lastFreeInHeap);
  fprintf(ctx->trace,"\n**** doGC thisObj: %x %s\n",ctx->thisObj, nameOf(ctx->thisObj));
  fprintf(ctx->trace,"\n**** doGCmark\n");
#endif
#endif
  //doGCcheckHeap(root);
  doGCmark(ctx,root,0); // root  = mainObj
  doGCmarkContexts();

#ifdef traceGC_1
  printBlocks(root);
#ifdef __arm__
#else
  fprintf(ctx->trace,"GC:after:doGCmark\n");
#endif
#endif
  firstFreeStart = doGCsweep(ctx,root);

#ifdef traceGC_1
  printFreeBlocks(lastFreeStart);
#endif
  //findAndSetMap(lastFreeStart,noOfFreeBlocks);
  doGCcompact(ctx,root,firstFreeStart);
  heapTop = heapTop - freedInHeap;
  doGCupdateRefs(ctx,root);
  doGCclearHeap();
#ifdef traceGC_1
  doGCcheckHeap(root);
#endif

#if defined traceGC_0
  #ifdef __arm__
#else
  fprintf(ctx->trace,"\n*** after doGC:\n");
  fprintf(ctx->trace,"thisObj       : %x %s\n",ctx->thisObj,nameOf(ctx->thisObj));
  fprintf(ctx->trace,"thisStack     : %x %s\n",ctx->thisStack,nameOf(ctx->thisStack));
  fprintf(ctx->trace,"mainObj       : %x %s\n",(int)mainObj,nameOf(mainObj));
  fprintf(ctx->trace,"&heap[0]      : %x\n",&heap[0]);
  fprintf(ctx->trace,"heapTop       : %6i\n",heapTop);
  fprintf(ctx->trace,"heapMax       : %6i\n",heapMax);
  fprintf(ctx->trace,"heap[heapTop] : %x\n",&heap[heapTop]);
  fprintf(ctx->trace,"noOfUsedBlocks: %i inUse: %6i bytes: %8i\n"
	 ,noOfUsedBlocks, heapTop,heapTop * 4);
  fprintf(ctx->trace,"noOfFreeBlocks: %i free : %6i bytes: %8i \n"
	 ,noOfFreeBlocks, heapMax- heapTop,(heapMax - heapTop) * 4);
#endif
#endif
  
  resumeThreads(ctx);
#ifdef __arm__
#else
  for (no = 0; no <=threadNo; no++) 
    if (threadStatus[no] == t_suspended) 
	printf("thread is suspended: %i threadId: %i\n",no,ctx->threadId);
#endif  
  gcInProgress = false;
  //printf("end:GC>\n");
}

int ZZ = 0;

#define withTimeOut

void *heapAlloc(Block *ctx,int size) {
  void *obj;
#ifdef linux
  int ret = pthread_mutex_lock( &mutex1 );
  if (ret > 0) RTE2("\n\n*** mutex_lock error: ",ret);
#elif defined  __CYGWIN__
  bool B = true;
  while (B) {
    switch(WaitForSingleObject(allocMutex,2L)) {
    case WAIT_OBJECT_0: 
      B = false;
      break;
    case WAIT_TIMEOUT: 
      //printf("Thread %d: wait timed out\n", GetCurrentThreadId());
      if (gcInProgress) {
	//printf("heapAlloc:allocMutex:busy: %i\n",ctx->threadId);
	waitForGC(ctx);
	//printf("heapAlloc:allocMutex:remuse:after:waitForGC\n");
      }
      break; 
    }
  }

#elif defined __XTENSA__
 L:
  if( xSemaphoreTake( mutex1, ( TickType_t ) 10 ) == pdTRUE ){
    //printf("got mutex1\n");
  }else {
    //printf("waiting for mutex1\n");
    goto L;
  }
#endif
  ZZ = ZZ + 1;
  if (ZZ > 1) runTimeError("Two or more in malloc");
  //#ifdef __arm
  //#else
  if (useBetaHeap) {
    if ((heapTop % 4) != 0) heapTop = ((heapTop + 4) / 4) * 4;
    //printf("heapTop after: %i size: %i",heapTop,size);
    if ((heapTop + size) > (heapMax - 8)) {
	// (heapTop - 8) since we need space for a free block at the end
      lastFreeInHeap =(Btemplate *)&heap[heapTop];
      doBGC(ctx,mainObj);
      //runTimeError("\n\n*** Heap overflow");
      //exit(1);
    }
    obj = (void *)&heap[heapTop];
    /*if (heapTop < 50000) {
      printf("size:%i ",size);
      int i;
      for (i = 0; i< 20; i++) printf(" %x ",getV(obj,i));
      }*/
    //printf(" obj: %i\n", (int)obj);
    heapTop = heapTop + size;
  } else {
    obj = malloc(size);
  }
  //#endif
  if (obj == NULL) {
#ifdef __arm__
#else
    printf("\n\nMalloc failure: %i\n",size);
#endif
    runTimeError("Malloc failure\n");
  }
  ZZ = ZZ - 1;
#ifdef linux 
  ret = pthread_mutex_unlock( &mutex1 );
  if (ret > 0) RTE2("\n\n*** mutex_unlock error: ",ret);
#elif defined  __CYGWIN__
  if (!ReleaseSemaphore(allocMutex,1,NULL))
    runTimeError("ReleaseSemaphoreError: allocMutex");
#elif __XTENSA__
  xSemaphoreGive( mutex1 );
  //printf("realesed mutex1\n");
#endif
       
  if (obj == NULL) {
    RTE2("malloc failed; size: ",size);
  }
  return obj;
}

void releaseHeap(void *S){
#ifdef __arm__
#else
  free(S);
#endif
}

 
#ifdef DUMP
#include "interpreter_dump.c"
#endif

int hSize = 0;



Btemplate *getR(Btemplate *obj,int inx){ 
  checkInHeap(obj);
  if (newAlloc){
    if ((0 <= inx) && (inx <= 64)) {
      return (Btemplate *)obj->vfields[inx];
    } else {
#ifdef __arm__
#else      
      printf("getR: index error %i\n",inx);
#endif
      return (Btemplate *)obj->vfields[inx]; // to fool compilere
    }
  }else{
    return (Btemplate *)obj->vfields[inx]; // to fool compilere
  }
};
void putR(Btemplate *obj,int inx, Btemplate *X){
  checkInHeap(obj);
  if (newAlloc) {
    if ((0 <= inx) && (inx <= 64)) {
      obj->vfields[inx] = (int)X;
    }else{
#ifdef __arm__
#else
      printf("putR: index error %i\n",inx);
#endif
    }
  }
};

Btemplate *allocTemplate(Block *ctx,int ID,int descNo,bool isObj, int vInxSize, int rInxSize){
  int objS = objSize(getDesc(descNo));
  int size = sizeof(Btemplate) + (objS + 1 + vInxSize) * sizeof(int);
 
  //printf("BT:%i objSize:%i vInxSize:%i size:%i xs:%i\n",sizeof(Btemplate),objSz,vInxSize,size,xsize);

  hSize = hSize + size;
  //fprintf(trace,"allocTemplate(%i,%i) ",size, hSize);
  Btemplate *obj = (Btemplate*)heapAlloc(ctx,size);
  //fprintf(ctx->trace,"\ntemplate obj: %x: %i %i %i\n",(int)obj,descNo,vInxSize,size);
  obj->desc = getDesc(descNo);
  obj->id = ID; 
  obj->valOff = 0;
  obj->isObj = isObj;
  obj->vtop = 0; 
  obj->rtop = 0;
  obj->lscTop = -1;
  obj->lsc = 0;
  int i = 0;
  for (i = 0; i < objS + 1 +vInxSize; i++) obj->vfields[i] = 0; 

  return obj;
}

void dumpRstack(FILE *trace,Btemplate *stack);
void dumpVstack(FILE *trace,Btemplate *stack);
void dumpLscStack(FILE *trace,Btemplate * obj);

#ifdef DUMP
void StacksToOut(FILE *trace,Btemplate *thisObj, Btemplate *thisStack)//, Block *ctx)
{ fprintf(trace,"\n\tthisObj = %s ",nameOf(thisObj));
  dumpRstack(trace,thisObj);
  dumpVstack(trace,thisObj); 
  fprintf(trace,"\n\tthisStack = %s ",nameOf(thisStack));
  dumpRstack(trace,thisStack);
  dumpVstack(trace,thisStack);
  fprintf(trace,"\n");
  dumpLscStack(trace,thisObj);
  dumpLscStack(trace,thisStack);
}

void dumpObj(FILE *trace,char *name,Btemplate *X){
  int i;
  fprintf(trace,"Object: %s %s\n",name,nameOf(X));

  fprintf(trace,"Fields: ");
  for (i = 0; i < 20; i++){
    fprintf(trace,"%i:%i,",i,getV(X,i));
  }
  fprintf(trace,"\nVstack: ");
  dumpVstack(trace,X);
  fprintf(trace,"\nRstack: ");
  dumpRstack(trace,X);
  fprintf(trace,"\n");
}

#endif

int threadStubDescNo; // perhaps a hack?
void dumpStackX(Btemplate *obj);

void runTimeErrorX(char *msg, Btemplate *thisObj, int glsc){
#ifdef __arm__
  putstr("\n\n**** Run-time error: ");
  putstr(msg);
  putstr(" obj: ");
  putstr(nameOf(thisObj));
  putint(descNo(thisObj->desc));
  putch(',');
  putint(glsc);
  putstr("\n");
#else
  printf("\n\n**** Run-time error: %s\n\nObject: %s(%i) at: %i\n",msg,nameOf(thisObj),descNo(thisObj->desc),glsc);
#endif
  dumpStackX(thisObj);

  exit(-1);
}

void dumpVstack(FILE *trace,Btemplate *stack){
  int i;
#ifdef __arm__
  putstr("[");
  for (i = 0; i < stack->vtop; i++)
    putint(stack->vstack[i + 1]);
  putstr("]\n");
#else
  //fprintf(trace,"%s:vStack\[",nameOf(stack));
  fprintf(trace,"[");
  for (i=0; i < stack->vtop; i++)
    fprintf(trace,"%i ",stack->vstack[i + 1]);     
  fprintf(trace,"] "); 
#endif
}

void dumpRstack(FILE *trace,Btemplate *stack){
  int i;
#ifdef __arm__
#else
  //fprintf(trace,"%s:rStack\[",nameOf(stack));
  fprintf(trace,"[");
  for (i=0; i < stack->rtop; i++)
    fprintf(trace,"%s ",nameOf(stack->rstack[i + 1]));  
  fprintf(trace,"] ");
#endif
}
int cMyLscTop(Btemplate *obj) { return obj->lscTop; };
  
int topOfLsc(Btemplate *obj,int inx ){ return obj->lscStack[obj->lscTop + inx];};

void dumpStackX(Btemplate *obj){
  Btemplate *X, *Y;
  if (obj != NULL) { 
    X = obj->rstack[1];
    Y = obj->rstack[2];
#ifdef __arm__
#else
    printf("caller: %s(%i) at: %i thisStack: %s\n"
	   ,nameOf(X),topOfLsc(X,-1),topOfLsc(X,0),nameOf(Y));
#endif
    if (((descNo(X->desc) == threadStubDescNo)) ||
	(descNo(X->desc) == (threadStubDescNo - 2 ))) // mainDescNo
	return;
    else
      dumpStackX(X);
  }
}

void vPush(Btemplate *thisStack,int V){
  int i;
  if ((thisStack->vtop = thisStack->vtop + 1) > 16 ) {
#ifdef __arm__
    putstr("vPush: ");
    putstr(nameOf(thisStack));
    dumpVstack(NULL,thisStack);
#else
    printf("\n\nvstack %s [",nameOf(thisStack)); // <<<<<<< OBS FIX
    for (i=0; i < 16; i++) printf(" %i",thisStack->vfields[i]);
    printf("]\n");
#endif 
    runTimeErrorX("vstack overflow(vPush)",thisStack,-1);
  }
  thisStack->vstack[thisStack->vtop] = V;
}

union u_double{
  double V;
  int A[2];
};

void fPush(Btemplate *thisStack, double X){
  int i;
  union u_double V;
  V.V = X;
  //printf("\n**** fPush: %f %f %x %x \n",X,V.V,V.A[0],V.A[1]);
  if ((thisStack->vtop = thisStack->vtop + 2) > 16 ) {
#ifdef __arm__
#else
    printf("\n\nvstack %s [",nameOf(thisStack)); // <<<<<<< OBS FIX
    for (i=0; i < 16; i++) printf(" %i",thisStack->vfields[i]);
    printf("]\n");
#endif 
    runTimeErrorX("vstack overflow",thisStack,-1);
  }

  thisStack->vstack[thisStack->vtop - 1] = V.A[0];
  thisStack->vstack[thisStack->vtop] = V.A[1];
}

bool getIsObj(Btemplate *obj) {return obj->isObj; };

void XdumpRstack(char *S,Btemplate *stack){
#ifdef __arm__
#else
  printf("\n%s: top: %i (",S,stack->rtop);
  int i=0;
  for (i = 0; i <= stack->rtop; i++) printf(" %i",(int)stack->rstack[i]);
  printf(")");
#endif  
}
void rPush(Btemplate *stack,Btemplate *R){
  //fprintf(trace,"\n*** rPush obj %i at %i \n",R->id,stack->rtop);
  checkInHeap(R);
  if ((stack->rtop = stack->rtop + 1) > 16 ) runTimeErrorX("stack overflow",stack,-1);
  stack->rstack[stack->rtop] = R;
  //XdumpRstack("rPush",stack);
  //printf(" push: %i\n",(int)R);
}

// OBS! Whyx do we test -1 for vPop, rPop and rTopElm - and not 0 (zero)?

int vPop(Btemplate *thisStack){
  if ((thisStack->vtop = thisStack->vtop - 1) < -1) 
    runTimeErrorX("vstack underflow",thisStack,-1);
  return thisStack->vstack[thisStack->vtop + 1];
}

double fPop(Btemplate* thisStack){
  union u_double val;
  val.A[1] = vPop(thisStack);
  val.A[0] = vPop(thisStack);
  //printf("\n**** fPop: %f %x %x\n",val.V,val.A[0],val.A[1]);
  return val.V;
}

Btemplate *rPop(Btemplate *stack){
  //Btemplate *R = stack->rstack[stack->rtop];
  // fprintf(trace,"\n*** rPop obj %i from %i \n",R->id,stack->rtop);
  if ((stack->rtop = stack->rtop - 1) < -1) runTimeErrorX("rStack underflow",stack,-1);
  checkInHeap(stack->rstack[stack->rtop + 1]);
  return stack->rstack[stack->rtop + 1];
}

// 2017/01/12: OBS! For some reason, rTopElm was missing and has been added
// but is not necessarily correct
Btemplate *rTopElm(Btemplate*stack,int inx){
  if ((stack->rtop - inx) < -1) runTimeErrorX("rStack underflow:rTopElm",stack,-1);
  checkInHeap(stack->rstack[stack->rtop - inx]);
  return stack->rstack[stack->rtop - inx];
}

void rswapIndexed(Btemplate *stack,int inx){
  Btemplate *obj; int i;
  obj = stack->rstack[stack->rtop - inx];
  for (i = 1; i <= inx; i++)
    stack->rstack[stack->rtop - i] = stack->rstack[stack->rtop - i + 1];
  stack->rstack[stack->rtop] = obj;
}
void lscPush(Btemplate *stack,int V){
  //fprintf(trace,"\n*** rPush obj %i at %i \n",R->id,stack->rtop);
  if ((stack->lscTop = stack->lscTop + 1) > 16 ) runTimeErrorX("lscStack overflow",stack,-1);
  stack->lscStack[stack->lscTop] = V;
}

int lscPop(Btemplate *stack){
  if ((stack->lscTop = stack->lscTop - 1) < -1) runTimeErrorX("lscPop: lscStack underflow",stack,-1);
  return stack->lscStack[stack->lscTop + 1];
}
void cSaveReturn(Btemplate *obj,int descNo, int lsc){
  //fprintf(trace,"\n***cSaveReturn in %s lscTop=%i:",nameOf(obj),obj->lscTop);
  //int i;
  //for (i=0; i < obj->lscTop; i++) fprintf(trace,"%i ",obj->lscStack[i]);
  //fprintf(trace,"\n");
  if ((obj->lscTop = obj->lscTop + 2) > 16) 
    runTimeErrorX("lsc stack overflow",obj,-1);
  obj->lscStack[obj->lscTop-1] = descNo;
  obj->lscStack[obj->lscTop] = lsc;
}

void dumpLscStack(FILE *trace,Btemplate * obj){
  int i;
  fprintf(trace,"\tlscStack:top: %i [", obj->lscTop);
  for (i = 0; i < obj->lscTop; i++){
    fprintf(trace, "%i: %i, ",i, obj->lscStack[i]);
  }
  fprintf(trace,"]\n");
}
int cRestoreReturn(Btemplate * obj){
  //fprintf(trace,"\n***cRestoreReturn: %i %s\n",obj->lscTop,nameOf(obj));
  if (obj->lscTop < 0) runTimeErrorX("cRestoreReturn: lscStack underflow\n",obj,-1);
  int V = obj->lscStack[obj->lscTop];
  obj->lscTop = obj->lscTop - 1;
  return V;
}

#ifdef linux
#elif defined  __CYGWIN__
HANDLE eventReady,eventTaken,eventProcessed;
#endif

Event *theEvent = NULL;

Event XE;

void *mkEvent(int type,Btemplate *caller,Btemplate *thisObj,Btemplate *org
	       ,bool isObj,int currentDescNo,int bcPos){ 
  //printf("\nmkEvent: %i %i %i\n",type,hSize,sizeof(Event));
  hSize = hSize + sizeof(Event);
  //Event *E = (Event *)heapAlloc(sizeof(Event));
  Event *E = &XE;
  E->type = type;
  E->caller = caller;
  E->thisObj = thisObj;
  E->org = org;
  E->isObj = (int) isObj;
  E->descNo = currentDescNo;
  E->bcPos = bcPos; 
  //printf("\nmkEvent: %i",E->type);

#ifdef linux
  int res = 0;
#elif defined  __CYGWIN__
  int res = WaitForSingleObject(eventTaken,INFINITE);
  switch (res) {
  case WAIT_OBJECT_0: 
    theEvent = E; 
    break;      
  default: 
    runTimeError("Wait failiure for eventTaken");
  };
#endif

#ifdef linux
#elif defined  __CYGWIN__
    if (!ReleaseSemaphore(eventReady,1,NULL)) 
        runTimeError("ReleaseSemaphoreError: eventReady");
#endif
#ifdef linux
#elif defined  __CYGWIN__
    switch(WaitForSingleObject(eventProcessed,INFINITE)) {
    case WAIT_OBJECT_0:
      break;
    default:
      runTimeError("Wait failure: eventProcessed");
    }; 
#endif
  return E;  
};

void mkAllocEvent(int type,Btemplate *caller,Btemplate *thisObj,Btemplate *org
		    ,bool isObj,int currentDescNo,int bcPos,bool isIndexed){
  mkEvent(type,caller,thisObj,org,isObj,currentDescNo,bcPos);
};

int descNoOf(Btemplate * obj){
  return desc_getInt4(obj->desc,descNo_index);
}

#ifdef __arm__
#else
void dumpStack(FILE *trace,Btemplate *Z){
  //int i;
  fprintf(trace,"\n\t");
  dumpVstack(trace,Z);
  dumpRstack(trace,Z);
  fprintf(trace,"\n");
}

void dumpSwapped(FILE *trace,Btemplate *X, Btemplate *Y,Btemplate *Z){
  fprintf(trace,"\nswapped: %s R[1]=%s, R[2]=%s  %s %s["
	  ,nameOf(X),nameOf(X->rstack[1]),nameOf(X->rstack[2])
	  ,nameOf(Y),nameOf(Z));
  int i;
  for (i=0; i < Z->rtop; i++)
    fprintf(trace,"%s ",nameOf(Z->rstack[i + 1]));
  fprintf(trace,"]\n");
}
#endif

void rswap(Btemplate *callee, Btemplate **obj1, Btemplate **stack1,bool updateS){
  //fprintf(trace,"***rswap %s %s %i\n",nameOf(*obj1),nameOf(*stack1),obj->rtop);
  Btemplate *obj2 = callee->rstack[1];
  Btemplate *stack2 = callee->rstack[2];
  callee->rstack[1] = *obj1;
  callee->rstack[2] = *stack1;
  *obj1 = obj2;
  //*stack1 = stack2;
  if (updateS) *stack1 = stack2;
  if (callee->rtop == 0) callee->rtop = 2; // first call - we push 2 values
  if (*obj1 == 0) { 
#ifdef __arm__
#else
    printf("*obj1 == 0\n"); 
#endif
    callee->rtop = 0;} // 
}
void rswapX(Btemplate *obj, Btemplate **R, Btemplate **S,bool updateS){
  //fprintf(trace,"***rswap %s %s %i\n",nameOf(*R),nameOf(*S),obj->rtop);
  Btemplate *Rx = obj->rstack[1];
  Btemplate *Sx = obj->rstack[2];
  obj->rstack[1] = *R;
  obj->rstack[2] = *S;
  *R = Rx;
  //*S = Sx;
  if (updateS) *S = Sx;
  if (obj->rtop == 0) obj->rtop = 2; // first call - we push 2 values
  if (*R == 0) { 
#ifdef __arm__
#else
    printf("*R == 0\n"); 
#endif
    obj->rtop = 0;} // 
}

#ifdef   __CYGWIN__
DWORD WINAPI interpreter(LPVOID B);
#else
void *interpreter(void *B);
#endif

void allocMain(Block *thisBlock,int descNo){ 
  mainObj = allocTemplate(thisBlock,1000,descNo,true,0,0);
  thisBlock->thisModule = mainObj;
  thisBlock->thisObj = thisBlock->thisModule;
  thisBlock->thisStack = thisBlock->thisModule;
  thisBlock->callee = NULL;
  thisBlock->enablee = NULL;
  thisBlock->top = NULL;
  thisBlock->world = NULL;
  thisBlock->origin = NULL;  
  //printf("mainObj: %x %s\n",(int)mainObj,nameOf(mainObj));
};

FILE *trace_t;

#ifdef __arm__
#else
// Only called from betaVM and runbeta.c
void init_interpreter(ObjDesc descs_a, int imageS, bool newAlc) {
  FILE *trace;
  trace = fopen("code.s","w");
  setbuf(trace, NULL);
  //setbuf(stdout, NULL);
  //setvbuf(stdout,NULL,_IONBF,0);
  trace_t = trace; // hack
#ifdef linux
#elif defined  __CYGWIN__
  allocMutex = CreateSemaphore(NULL,1,1,NULL);
#endif

  descs = (ObjDesc) malloc(imageS);
  //descs = (ObjDesc) heapAlloc(NULL,imageS);
  memcpy((void *)descs,descs_a,imageS); 

  newAlloc = newAlc;
  if (newAlloc) newAllocOff = 1;
}
#endif

void set_descs(ObjDesc BC){
  descs = BC;
#ifdef linux
#elif defined  __CYGWIN__
  allocMutex = CreateSemaphore(NULL,1,1,NULL);
#endif
}

void run_interpreter(bool isXB){
  int mainDescNo;
  FILE *trace = trace_t;;
  Block *thisBlock;
#ifdef __arm__
  putstr("run_interpreter\n");
#else
  //printf("in run interpreter\n");
#endif
  
#ifdef __XTENSA__
mutex1 = xSemaphoreCreateBinary();
 if (mutex1 == NULL) { printf("Error in allocating semaphore\n");}
 else{
   printf("Semaphore succesfully created\n");
   xSemaphoreGive(mutex1);
}
#endif

  isXbeta = isXB;
  newAlloc = true;
  if (newAlloc) newAllocOff = 1;
  mainDescNo = getMainDescInx();  
  threadStubDescNo = mainDescNo + 2;
  thisBlock = (Block *)malloc(sizeof(Block));
  //thisBlock = (Block *)heapAlloc(NULL,sizeof(Block));
  // OBS trace not defined here!
  thisBlock->trace = trace;
  thisBlock->bc = descs;

#ifdef DUMP
  int imageS = getImageSize();
  fprintf(trace,"C interpreter: mainDescNo: %i imageS: %i mainDesc: %x\n"
	  ,mainDescNo,imageS,(int)getDesc(mainDescNo));
#endif

  thisBlock->bc = getByteCode(getDesc(mainDescNo));
  thisBlock->currentDescNo = mainDescNo;
  stringTable = descs + getStringTableIndex();
#ifdef DUMP
  dump_image(trace);
#endif

  thisBlock->glsc = 0; 
  thisBlock->threadId = 0;
  thisBlock->traceFile = "trace.s";
  allocMain(thisBlock,mainDescNo);
#ifdef DUMP
  fprintf(trace,"**** Execute:\n\n");
#endif
 
#ifdef linux
#elif defined  __CYGWIN__
#ifdef usewinsock2
 int iResult;
 // Initialize Winsock
 WSADATA wsaData;
 iResult = WSAStartup(MAKEWORD(2,2), &wsaData);
 printf("\nInitialize Winsock %i\n",iResult);
 if (iResult != 0) {
   printf("WSAStartup failed: %d\n", iResult);
 }
#endif
#endif


#ifdef linux
  interpreter(thisBlock);
#elif defined  __CYGWIN__
  eventReady = CreateSemaphore(NULL,0,1,NULL);
  eventTaken = CreateSemaphore(NULL,1,1,NULL);
  eventProcessed = CreateSemaphore(NULL,0,1,NULL);
  CreateThread(NULL,0,interpreter,(LPVOID)thisBlock,0,0);
#elif defined __arm__
  putstr("call interpreter\n");
  interpreter(thisBlock);
#else
  printf("Calling interpreter\n");
  interpreter(thisBlock);
#endif

}

Event *getEvent(bool first){
  Event *E;
#ifdef linux
#elif defined  __CYGWIN__
  DWORD dwWaitResult; 
#endif
  //printf("\n***run_interpreter");
  if (!first) {
#ifdef linux
#elif defined  __CYGWIN__
    if (!ReleaseSemaphore(eventProcessed,1,NULL)){ 
      printf("Errorcode: %i",(int)GetLastError());
      runTimeError("ReleaseSemaphoreError: eventProcessed");
    };
#endif
  }

#ifdef linux
  E = (Event *)mkEvent(stop_event,0,0,0,0,0,0); 
#elif defined  __CYGWIN__
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
#else
  E = NULL; // to fool ESP32 compiler
#endif
#ifdef linux
#elif defined  __CYGWIN__
  if (!ReleaseSemaphore(eventTaken,1,NULL))
    runTimeError("ReleaseSemaphoreError: eventTaken");
#endif
  return E;
}

int newId(Block *ctx) { 
  ctx->ID = ctx->ID + 4; 
  // printf("\nID:%i %i",*threadId,*ID + *threadId); 
  return ctx->ID + ctx->threadId;
}

void allocObj(Block *ctx,Btemplate *origin,int descNo,bool isObj,int vInxSize,int rInxSize){
#ifdef TRACE
  fprintf(ctx->trace,"\n\tFROM %s(%i,%i,%i) ",nameOf(ctx->thisObj),ctx->currentDescNo,ctx->glsc,(int)*ctx->bc);
#endif
  ctx->origin = origin;
  ctx->callee = allocTemplate(ctx,newId(ctx),descNo,isObj,vInxSize,rInxSize);
  origin = ctx->origin;
#ifdef TRACE
  fprintf(ctx->trace,"callee: %s %i \n",nameOf(ctx->callee),(int)ctx->callee);
#endif
  rPush(ctx->callee,ctx->thisObj); 
  rPush(ctx->callee,ctx->thisStack);
  rPush(ctx->callee,origin); // OBS - cf invokeObj

  cSaveReturn(ctx->thisObj,ctx->currentDescNo,ctx->glsc);
  
  ctx->currentDescNo = descNo;
  //ctx->thisStack = ctx->callee;
  //ctx->thisObj = ctx->thisStack;
  ctx->thisObj = ctx->callee;
  ctx->thisStack = ctx->thisObj; // OBS - cf invodeObj
  ctx->bc = (ObjDesc) myCode(ctx->thisObj);
  ctx->glsc = getAllocE(ctx->thisObj->desc);
#ifdef TRACE
  fprintf(ctx->trace,"\n\tALLOC %s(%i,%i,%i,%i)\n"
	  ,nameOf(ctx->thisObj),descNo,ctx->glsc,(int)ctx->thisObj,(int)ctx->bc);
#endif
#ifdef EVENT
  // OBS! Y is note declared
  //mkAllocEvent(alloc_event,Y,ctx->thisObj,origin,isObj,ctx->currentDescNo,ctx->glsc,false);
#endif
};

void allocQObj(Block *ctx,Btemplate *origin,int descNo,bool isObj,int vInxSize,int rInxSize){
  // OBS! for isXbeta calls of allocObj may have to be replaced by allocQObj
#ifdef TRACE
  fprintf(ctx->trace,"\n\tFROM %s(%i,%i,%i) ",nameOf(ctx->thisObj),ctx->currentDescNo,ctx->glsc,(int)*ctx->bc);
#endif

  ctx->origin = origin;
  ctx->callee = allocTemplate(ctx,newId(ctx),descNo,isObj,vInxSize,rInxSize);
  origin = ctx->origin;

#ifdef TRACE
  fprintf(ctx->trace,"callee: %s %i \n",nameOf(ctx->callee),(int)ctx->callee);
#endif
  rPush(ctx->callee,ctx->thisObj);
  rPush(ctx->callee,ctx->thisStack);
  if (isXbeta){
    rPush(ctx->thisStack,origin); // OBS - cf invokeObj
  }else{
    rPush(ctx->callee,origin); // OBS - cf invokeObj
  }
  cSaveReturn(ctx->thisObj,ctx->currentDescNo,ctx->glsc);
  
  ctx->currentDescNo = descNo;
  if (isXbeta) {
      ctx->thisObj = ctx->callee;
    }else{
      ctx->thisObj = ctx->callee;
      ctx->thisStack = ctx->thisObj; // OBS - cf invodeObj
    }
  ctx->bc = (ObjDesc) myCode(ctx->thisObj);
  ctx->glsc = getAllocE(ctx->thisObj->desc);
#ifdef TRACE
  fprintf(ctx->trace,"\n\tALLOC %s(%i,%i,%i,%i)\n"
	  ,nameOf(ctx->thisObj),descNo,ctx->glsc,(int)ctx->thisObj,(int)ctx->bc);
#endif
#ifdef EVENT
  // OBS! Y is not declared
  //mkAllocEvent(alloc_event,Y,ctx->thisObj,origin,isObj,ctx->currentDescNo,ctx->glsc,false);
#endif
};

void invokeObj(Block *ctx,int descNo,int staticOff,int vInxSize,int rInxSize){
  // vInxSize and rInxSize = 0 - start using objSize
#ifdef TRACE
  fprintf(ctx->trace,"\n\tFROM %s(%i,%i,%i) ",nameOf(ctx->thisObj),ctx->currentDescNo,ctx->glsc,(int)ctx->bc);
#endif

  ctx->callee = allocTemplate(ctx,newId(ctx),descNo,false,vInxSize,rInxSize);

#ifdef __arm__
#ifdef armtrace
	putstr("invoke: ");
	putstr(nameOf(ctx->callee));
	putstr(" from: ");
	putstr(nameOf(ctx->thisObj));
	putstr("\n");
#endif
#endif
#ifdef TRACE
  fprintf(ctx->trace,"callee: %s %i\n",nameOf(ctx->callee),(int)ctx->callee);
#endif
  if (staticOff > 0) putR(ctx->thisObj,staticOff,ctx->callee);
  
  rPush(ctx->callee,ctx->thisObj);
  rPush(ctx->callee,ctx->thisStack);

  cSaveReturn(ctx->thisObj,ctx->currentDescNo,ctx->glsc);

  ctx->currentDescNo = descNo;
  ctx->thisObj = ctx->callee;
  ctx->bc = (ObjDesc) myCode(ctx->thisObj);
  ctx->glsc = getAllocE(ctx->thisObj->desc);

#ifdef TRACE
  fprintf(ctx->trace,"\n\tALLOC %s(%i,%i,%i,%i) staticOff = %i\n"
	  ,nameOf(ctx->thisObj),descNo,ctx->glsc,(int)ctx->thisObj,(int)ctx->bc
	  ,staticOff);
#endif
#ifdef EVENT
  // OBS! Y is not declared
  // arg 4 : 2 should be origin?
  // we should probably save ctx->thisObj in Y here: caller
  // mkAllocEvent(alloc_event,Y,ctx->thisObj,2,false,ctx->currentDescNo,ctx->glsc,false);
#endif
};

void invokeValObj(Block *ctx,int descNo,int staticOff){
#ifdef TRACE
  fprintf(ctx->trace,"invokeVal %i %i\n",descNo,staticOff);
#endif
  cSaveReturn(ctx->thisObj,ctx->currentDescNo,ctx->glsc);
 
  lscPush(ctx->thisObj,staticOff);

  ctx->currentDescNo = descNo;

  ctx->thisObj->valOff = ctx->thisObj->valOff + staticOff;

  //ctx->currentDescNo = descNo;

  ctx->bc = (ObjDesc) codeFromDescNo(descNo);
  ctx->glsc = getAllocE(getDesc(descNo));
  //ctx->bc = (ObjDesc) myCode(ctx->thisObj);
  //ctx->glsc = getAllocE(ctx->thisObj->desc);
}
void allocIndexedObj(Block *ctx, Btemplate *origin, int descNo,bool isObj, int dinx, int rangee, int isRindexed){ 
#ifdef TRACE
  fprintf(ctx->trace,"allocIndexedObj(%i,%i,%i) ",dinx,rangee,isRindexed);
  printf("OBS! May not work: allocIndexedObj(%i,%i,%i) ",dinx,rangee,isRindexed);
#endif

  if (isRindexed == 0) {
    
    allocObj(ctx,origin,descNo,isObj,rangee,0);
    
  } else {
    if (rangee > 132) {
      RTE2("\n\n**** Ref-rep range: %i\n",rangee);
      runTimeErrorX("Allocating ref-rep larger than 132",origin,-1);
    };
    
    allocObj(ctx,origin,descNo,isObj,0,rangee);
  };
  ctx->thisObj->vfields[dinx] = rangee; 
};

Btemplate *QallocIndexed(Block *ctx, Btemplate *origin, int descNo,bool isObj, int dinx, int rangee, int isRindexed){ 
#ifdef TRACE
  fprintf(ctx->trace,"QallocIndexedObj(%i,%i,%i) \n",dinx,rangee,isRindexed);
#endif    
  //printf("QallocIndexed: %x\n",(int)origin);
  //printf(" %s\n",nameOf(origin));
  ctx->origin = origin;
  // indexed[0] = 0
  // indexed[1] = origin
  // indexed[2] = range
  // indexed[3] = 1st element
  // must add 2 to range below
  if (isRindexed == 0) {
    ctx->callee = allocTemplate(ctx,newId(ctx),descNo,isObj,rangee + 2,0);
  } else {
    if (rangee > 132) {
      runTimeErrorX("Allocating ref-rep larger than 132",origin,-1);
    };
    ctx->callee = allocTemplate(ctx,newId(ctx),descNo,isObj,0,rangee + 2);
  };
  origin = ctx->origin;
  putR(ctx->callee,1,origin); // store origin
  ctx->callee->vfields[dinx + newAllocOff] = rangee; 
  // printf("QallocIndexedB: %x\n",(int)origin);
  // int i=0;
  // for (i = 0; i <= rangee; i++) printf(" %i",callee->vfields[i]);
  // printf(" dinx = %i %i\n", dinx, rangee);
  
  rPush(ctx->thisStack,ctx->callee);
  //printf("QallocIndexedX: %x",(int)origin);
  //printf(" %s\n",nameOf(origin));
  return ctx->callee;
};

void mkIndexed(int descInx,bool isRef,Block *ctx) {
  int length,size,i;
  Btemplate *X;
  length = vPop(ctx->thisStack);
  size = 1;
  X = QallocIndexed(ctx,0,descInx,1,1,length,0);
  for (i = 1; i <= length; i++) {
    X->vfields[1 +  length - i + 1 + newAllocOff] = vPop(ctx->thisStack);
  }
}
void allocStrucRefObj(Block *ctx, Btemplate *origin,int inx, bool isVirtual){
#ifdef TRACE
  fprintf(ctx->trace,"***allocStrucRefObj origin: %s inx:%i \n",nameOf(origin),inx);
#endif
  Btemplate * X = allocTemplate(ctx,newId(ctx),getStrucRefDescNo(),0,0,0);
  if (isVirtual) inx = vdtTable(ctx->trace,origin,inx);
  X->vfields[1] = inx;
  putR(X,2,origin);
  rPush(ctx->thisStack,X);
};

void allocFromStrucRefObj(Block *ctx,Btemplate *obj){
#ifdef TRACE
  fprintf(ctx->trace,"***allocFromStrucRefObj %s : ", nameOf(obj));
#endif
  allocObj(ctx,getR(obj,2),obj->vfields[1],0,0,0);
};
 void allocTextObj(Block *ctx,int litInx){
    // literals[litInx] = length
    Btemplate *origin = 0; // FIX - in beta impl., the text object is used as its own origin
    int dinx,rangee,i;
    dinx = 2; // start of repetition
    rangee = getLiteral(ctx->thisObj,litInx);
    Btemplate *X = ctx->thisObj;
    
    allocIndexedObj(ctx,origin,getTextDescNo(),1,dinx,rangee,0);

    ctx->thisObj->vfields[1] = rangee; // pos = rangee
    for (i = 0; i < rangee; i++) {
      char ch = getLiteral(X, litInx + i + 1);
      ctx->thisObj->vfields[3 + i] = ch;
      // fprintf(trace, "Lit %c",ch);
    }
    // fprintf(trace," %i %i %i %i \n"
    //,thisObj->vfields[0],thisObj->vfields[1],thisObj->vfields[2],thisObj->vfields[3]);
  }
  
void QallocTextObject(Block *ctx,int litInx){
  /* New layout for newAlloc: "abc..."
   * vfields[0] =
   * vfields[1] = origin
   * vfields[2] = rangee
   * vfields[3} = 'a'
   * vfields[4] = ...
   */
  int dinx = 1; // start of repetition: adjust for newAllocOff in QallocIndexed
  int rangee = getLiteral(ctx->thisObj,litInx); // literals[litInx] = rangee
  Btemplate *origin = getR(ctx -> world,3);     // a bloody hack
  
  QallocIndexed(ctx,origin,getTextDescNo(),1,dinx,rangee,0);

  Btemplate *X = ctx->thisObj;
  int i;
  for (i = 0; i < rangee; i++) {
    char ch = getLiteral(X, litInx + i + 1);
    ctx->callee->vfields[dinx + 1 + i + newAllocOff] = ch;
  }
  /* printf("\nQallocTextObject:  range = %i ", rangee);
     for (i = 0; i < 40; i++) printf(" i: %i",getV(ctx->callee,i));
     printf("\n"); */
}

char *mkCstring(Btemplate *T){
  //#ifdef __arm__
  //char *B;
  //#else
  char *B = malloc(T->vfields[1] * sizeof(char));
  //#endif
  int length = T->vfields[1];
  //printf("mkCstring: length: %i ",length);
  //
  int i = 0;
  //for (i = 2; i < T->vtop; i++) {
  for (i = 2; i <= length + 1; i++) {
    //printf("%i %c ",T->vfields[i],(char)T->vfields[i]);
    B[i - 2] = (char)T->vfields[i];
  }
  //printf("\n");
  //B[T->vtop - 2] = 0;
  B[length] = 0;
  return B;
}

void C2QBstring(Block *ctx,char *S){
  int length = -1;
  int i;
  char ch = -1;
  /* printf("C2QBstring: %s ",S); */
  while (ch != 0) {
    length = length + 1;
    ch = S[length];  
    // if (ch != 0) printf(" %c",ch); 
    }
  QallocIndexed(ctx,0,getTextDescNo(),1,1,length,0);
  for (i = 0; i <= length; i++) ctx->callee->vfields[2 + i] = S[i];
  putR(ctx->callee,1,getR(ctx->world,3)); // a bloody hack
#ifdef __arm__
#else
  free(S);
#endif
}

void  ConvertIndexedAsString(Block *ctx) {
  Btemplate *X = rPop(ctx->thisStack);; 
  int i, length  = X->vfields[1 + newAllocOff];
  /*printf("\n*** ConvertIndexedAsString %i:\n", length);
  for (i=0; i <= length + 2; i++) printf("i:%i=%i ",i,X->vfields[i]);
  printf("\n");
  printf("X: %x %s ",(int)X,nameOf(X));
  printf("X.origin: %x ",(int)getR(X,1));
  printf("%s\n",nameOf(getR(X,1)));*/
  
  ctx->origin = X;
  
  //printf("X: %x %s\n",(int)X,nameOf(X));
  //printf("\nlength: %i %i%\n",length,X->vfields[length + 2]);
  while (X->vfields[length + 2] == 0 ) {
    length = length - 1;
    // printf("L:%i ",length);
  }
  QallocIndexed(ctx,X,getTextDescNo(),1,1,length,0);
  
  //printf("\nlength: %i \n",length);
  //printf("aaaD %x %s\n", (int)ctx->world,nameOf(ctx->world));
  //printf("aaaD %x %s\n", (int)getR(ctx->world,3),nameOf(getR(ctx->world,3)));
  putR(ctx->callee,1,getR(ctx->world,3)); // origin - a bloody hack
  ctx->callee->vfields[1 + newAllocOff] = length; // done in QallocIndexed?
  //printf("callee: %x %s\n",(int)ctx->callee,nameOf(ctx->callee));
  //printf("origin: %x %s\n",(int)getR(ctx->callee,1),nameOf(getR(ctx->callee,1)));
  for (i = 2; i <= length + 1; i++) {
    //printf("C: %i\n",X->vfields[i + newAllocOff]);
    ctx->callee->vfields[i + newAllocOff] = X->vfields[i + newAllocOff];
  }
  //printf("origin: %x %s\n",(int)getR(ctx->callee,1),nameOf(getR(ctx->callee,1)));
}

FILE *files[4];
int filesTop = 0;

int fileOpen(Btemplate *FN){
  char *N;
  int L,i;
  N = malloc(30);
  L = getV(FN,2);
  //printf("fileOpen %i",L);
  for (i = 1; i <=L; i++)
    { //printf(" %c ", getV(FN,2 + i));
      N[i - 1] =  getV(FN,2 + i);
    }
  N[L] = 0;
#ifdef __arm__
#else
  files[filesTop] = fopen(N,"r");
#endif
  if (files[filesTop] == NULL)  {
#ifdef __arm__
#else
      printf("fopen failure\n");
#endif      
      stop;
    }
  filesTop = filesTop + 1;
#ifdef TRACE
  printf("fileOpen: filesTop: '%s' %i %x\n",N,filesTop,files[filesTop - 1]);
#endif
  return filesTop - 1;
}

int fileGet(int id){
  char c;
  //printf("fileGet id = %i ",id);
#ifdef __arm__
#else
  c = fgetc(files[id]);
#endif
  //printf(" c = %c  %i\n",c,c);
  return c;
}

int fileEos(int id){
  char c;
#ifdef __arm__
#else
  c = fgetc(files[id]);
  if (c != 0) ungetc(c,files[id]);
#endif
  //printf("fileEos: %c \n",c);
  return c == -1;
}

void fileClose(int id){
#ifdef __arm__
#else
  fclose(files[id]);
#endif
}

void doCall(Block *ctx,bool withEnablingSuspend,bool updateS){
  // coroutines with arguments do not wrok: elim updateS
    int arg1 = (char) op1(ctx->bc,&ctx->glsc);
#ifdef TRACE
    fprintf(ctx->trace,"call %c ",arg1);
#endif
    ctx->callee = rPop(ctx->thisStack);
#ifdef TRACE
    fprintf(ctx->trace,"\n\tFROM %s(%i,%i,%i) ",nameOf(ctx->thisObj),ctx->currentDescNo,ctx->glsc,(int)ctx->bc);
#endif
    if (withEnablingSuspend) ctx->enablee = ctx->callee;
    cSaveReturn(ctx->thisObj,ctx->currentDescNo,ctx->glsc);
    if (ctx->callee->rtop == 0) { 
#ifdef EVENT
      Btemplate *Y = ctx->thisObj;
#endif
      rPush(ctx->callee,ctx->thisObj); 
      rPush(ctx->callee,ctx->thisStack);
      ctx->thisObj = ctx->callee;
#ifdef TRACE
      fprintf(ctx->trace,"TO %s",nameOf(ctx->callee));
#endif
      switch (arg1)
	{
	case 'N':
	  ctx->currentDescNo = descNoOf(ctx->thisObj);
	  ctx->bc = myCode(ctx->thisObj);
	  ctx->glsc = getEnterE(ctx->thisObj->desc);
#ifdef TRACE
	  fprintf(ctx->trace,"(%i,%i,%i) N\n",ctx->currentDescNo,ctx->glsc,(int)ctx->bc);
#endif
	  break;
	case 'D':
	  arg1 = topDescNo(ctx->thisObj);
	  ctx->currentDescNo = arg1;
	  ctx->bc = codeFromDescNo(arg1);
	  ctx->glsc = getDoE(getDesc(arg1));
#ifdef TRACE
	  fprintf(ctx->trace,"D(%i,%i,%s) ",ctx->currentDescNo,ctx->glsc,nameOf(ctx->thisStack));
	  dumpStack(ctx->trace,ctx->thisStack);
#endif
#ifdef EVENT
	  mkEvent(do_event,Y,ctx->thisObj,myCorigin(ctx->thisObj),false,ctx->currentDescNo,ctx->glsc); // withEnablingSuspend
#endif
	  break;
	case 'X':
	  arg1 = topDescNo(ctx->thisObj);
	  ctx->currentDescNo = arg1;
	  //dumpDesc(arg1);
	  ctx->bc = codeFromDescNo(arg1);
	  ctx->glsc = getExitE(getDesc(arg1));
#ifdef TRACE
	  fprintf(ctx->trace,"(%i,%i,%i) X\n",arg1,ctx->glsc,(int)ctx->bc);
#endif
	  break;
	}}
    else {
      switch (arg1)
	{
	case 'N': // same as for callN
	  rPush(ctx->callee,ctx->thisObj);
	  rPush(ctx->callee,ctx->thisStack);
	  ctx->thisObj = ctx->callee;
	  ctx->currentDescNo = descNoOf(ctx->thisObj);
	  ctx->bc = codeFromDescNo(ctx->currentDescNo);
	  ctx->glsc = getEnterE(getDesc(ctx->currentDescNo));
#ifdef TRACE
	  fprintf(ctx->trace, "resumeN %s(%i,%i)\n",nameOf(ctx->callee),ctx->currentDescNo,ctx->glsc);
#endif
	  break;
	case 'D':
#ifdef TRACE
	  fprintf(ctx->trace, "resumeD %s ",nameOf(ctx->callee));
	  dumpSwapped(ctx->trace,ctx->callee,ctx->thisObj,ctx->thisStack);
#endif
	  rswap(ctx->callee,&ctx->thisObj,&ctx->thisStack,updateS);
#ifdef TRACE
	  dumpSwapped(ctx->trace,ctx->callee,ctx->thisObj,ctx->thisStack);
	  if (ctx->thisStack != ctx->thisObj) { // external suspend?
	    fprintf(ctx->trace,"thisObj != thisStack %s %s ",nameOf(ctx->thisObj),nameOf(ctx->thisStack));
	  };
#endif
	  ctx->glsc = cRestoreReturn(ctx->thisObj);
	  ctx->currentDescNo = cRestoreReturn(ctx->thisObj);
	  ctx->bc = codeFromDescNo(ctx->currentDescNo);
#ifdef TRACE
	  fprintf(ctx->trace,"AT %s(%i,%i,%s) \n"
		  ,nameOf(ctx->thisObj),ctx->currentDescNo,ctx->glsc,nameOf(ctx->thisStack));
#endif
	  break;
	case 'X': // same as for callX
	  rPush(ctx->callee,ctx->thisObj);
	  rPush(ctx->callee,ctx->thisStack);
	  ctx->thisObj = ctx->callee;
	  ctx->currentDescNo = topDescNo(ctx->thisObj);
	  ctx->bc = codeFromDescNo(ctx->currentDescNo);
	  ctx->glsc = getExitE(getDesc(ctx->currentDescNo));
#ifdef TRACE
	  fprintf(ctx->trace, "resumeX %s(%i,%i)\n",nameOf(ctx->callee),ctx->currentDescNo,ctx->glsc);
#endif
	  break;
	}
    }
  }
   
void doSuspend(Block *ctx,Btemplate *callee, bool preemptive){
#ifdef TRACE
  fprintf(ctx->trace," AT %s FROM %s(%i,%i,%s) "
	  ,nameOf(callee),nameOf(ctx->thisObj),ctx->currentDescNo,ctx->glsc,nameOf(ctx->thisStack));
  if (preemptive) fprintf(ctx->trace,"preemptive ");
#endif
  
  ctx->thisObj->lsc = ctx->glsc; // is this necessary?
#ifdef TRACE
  if (ctx->thisObj != ctx->thisStack) // external suspend ??
    { fprintf(ctx->trace,"thisObj != thisStack %s %s ",nameOf(ctx->thisObj),nameOf(ctx->thisStack));
    }
#endif
  cSaveReturn(ctx->thisObj,ctx->currentDescNo,ctx->glsc);
#ifdef TRACE
  dumpSwapped(ctx->trace,callee,ctx->thisObj,ctx->thisStack);
#endif
  rswap(callee,&ctx->thisObj,&ctx->thisStack,true); // notice &
#ifdef TRACE
  dumpSwapped(ctx->trace,callee,ctx->thisObj,ctx->thisStack);
#endif
  ctx->glsc = cRestoreReturn(ctx->thisObj);
  ctx->currentDescNo = cRestoreReturn(ctx->thisObj);
#ifdef TRACE
  fprintf(ctx->trace,"TO %s(%i,%i,%s)\n",nameOf(ctx->thisObj),ctx->currentDescNo,ctx->glsc,nameOf(ctx->thisStack));
#endif
  ctx->bc = codeFromDescNo(ctx->currentDescNo);
  rPush(ctx->thisStack,callee);
};

#if defined(linux)
void  *interpreter(void *B){
  
#elif defined  __CYGWIN__
  DWORD WINAPI interpreter(LPVOID B){;

#elif defined __arm__
void  *interpreter(void *B){;
    putstr("interpreter:start\n");
#else
    void  *interpreter(void *B){; // musy be fixed for ESF32
      //printf("In interpreter\n");
#endif

      Block *thisBlock = (Block *)B;
      int threadId;
  threadId = thisBlock->threadId;
  thisBlock->ID = 1000;

  //betaWorld = thisBlock->world;

#ifdef linux
#elif defined  __CYGWIN__
#ifdef usewinsock2
  // declarations related to sockets
  struct hostent *he;
  struct in_addr **addr_list;
  char ip[100];
  struct sockaddr_in server,client;
  char *msg;
#endif
#endif


  bool hasThreads = false;

#ifdef linux
  // The following calls are supposed to associate each interpreter threadh with
  // a specific CPU - have no idea if it works!?
  //cpu_set_t mask;
  //CPU_ZERO(&mask);
  //CPU_SET(threadId,&mask);
#endif

#ifdef withGC
bool traceThreads = true;
#else
 bool traceThreads = false;
#endif

#ifdef __arm__
#else
  if (traceThreads)
    printf("*** C interpreter - threadId: %i\n",threadId);
#endif
  FILE * trace;
  FILE *output;
#ifdef __arm__
  //init_uart();
#elif defined __XTENSA__
  trace = NULL;
#else
  //printf("Before trace = fopen\n");
  trace = fopen(thisBlock->traceFile,"w");
  thisBlock->trace = trace;
  setbuf(trace, NULL);
  if (threadId == 0){
    output = fopen("output","w");
    setbuf(output, NULL);
  }else{
    output = thisBlock->output;
  }
#endif
  //printf("After trace = fopen\n");
  Btemplate *enablee = 0;
  int suspendEnabled = 0;
  int timeToSuspend = 0;
  ObjDesc bc;
  int glsc;
  int currentDescNo;
  Btemplate *thisModule = NULL,*thisObj,*thisStack, *callee; // *eventProcessor;

  bc = thisBlock->bc;
  glsc = thisBlock->glsc;
  currentDescNo = thisBlock->currentDescNo;


  void saveContext(){
    thisBlock->bc = bc;
    thisBlock->glsc = glsc;
    thisBlock->currentDescNo = currentDescNo;
    thisBlock->thisModule = thisModule;
    thisBlock->thisObj = thisObj;
    thisBlock->thisStack = thisStack;
    thisBlock->callee = callee;
    thisBlock->enablee = enablee;
    thisBlock->threadId = threadId;
  }
  void restoreContext(){
    bc = thisBlock->bc;
    glsc = thisBlock->glsc;
    currentDescNo = thisBlock->currentDescNo;
    thisModule = thisBlock->thisModule;
    thisObj = thisBlock->thisObj;
    thisStack = thisBlock->thisStack;
    callee = thisBlock->callee;
    enablee = thisBlock->enablee;
    threadId = thisBlock->threadId;
  }

  int opCode,off,inx,arg1,arg2,arg3,dscNo,V,isValueObj,size,mode;
  int dinx,isRindexed,rangee,i;
  double float1, float2, float3;
  bool running = true, doTrace = false; 
  Btemplate *X, *Y;
  Btemplate *refArgs[10]; int refArgsTop = 0; // see sendv below
  int cnt = 0;
  char ch;

  thisObj = thisBlock->thisObj;
  thisStack = thisObj;
 
#ifdef EVENT
  mkEvent(start_event,0,thisObj,0,true,thisBlock->currentDescNo,thisBlock->glsc);
#endif
  while (running)
    { //printf("Running\n");

      if (suspendEnabled == 1) {
	timeToSuspend = timeToSuspend - 1;
	if (timeToSuspend <= 0) {
	  if (enablee != 0) {
	    suspendEnabled = suspendEnabled - 1;
	    if (suspendEnabled > 0) RTE2("\npSuspend: %i\n",suspendEnabled);

	    saveContext();
	    doSuspend(thisBlock,enablee,true);
	    restoreContext();
	    enablee = 0;
	  }
	}
      }
#ifdef TRACE
      fprintf(trace,"%i:\t",glsc);
#endif
      opCode = bc[glsc]; glsc = glsc + 1;
      /*if (gcInProgress) {
	printf("Interpreter:gcInProgress: threadNo: %i %s\n",threadId,nameOf(thisObj));
	}*/
      
#ifdef __arm__
#ifdef armtrace
      putstr("op: ");
      putint(opCode);
      putstr("\n");
#endif
#else
      if (doTrace)
	printf("*** %i %s: Op: %i, glsc: %i\n",threadId,nameOf(thisObj),opCode,glsc);
#endif
      if (cnt == 0) {
	//blink();
	// pinMode(4,1);
	// digitalWrite(4,0);
      };
      cnt = cnt + 1;
      switch (opCode) {
      case pushthis:
#ifdef TRACE
	fprintf(trace,"pushthis\n");
#endif
#ifdef __arm__
#ifdef armtrace	
	putstr("pushthis: ");
	puthex((int)thisObj);
	putch((int)10);
#endif
#endif
	checkInHeap(thisObj);
	rPush(thisStack,thisObj);
	break;
      case pushC: 
	arg1 = op1(bc,&glsc);
	vPush(thisStack,arg1);
#ifdef TRACE
	fprintf(trace,"pushc %i\n", arg1);
#endif
	break;
      case saveAndSetThis:
	X = rPop(thisStack);
	rPush(thisStack,thisObj);
	thisObj = X;
#ifdef TRACE
	fprintf(trace,"saveAndSetThis %i\n", arg1);
#endif
	break;
      case restoreThis:
	thisObj = rPop(thisStack);
#ifdef TRACE
	fprintf(trace,"restoreThis %i\n", arg1);
#endif
	break;
      case addOff:
	arg1 = op2(bc,&glsc);
	//X = rPop(thisStack);
#ifdef TRACE
	fprintf(trace, "addOff %i\n",arg1);
	//fprintf(trace,"thisObj: %i \n",(int)thisObj);
	//fprintf(trace,"addOff %s (%i) + %i, %i\n",nameOf(thisObj),(int)X,arg1 * 4
	//, (int)X + arg1 *4);
#endif
	// if (X == NULL) runTimeErrorX("Reference is NONE",thisObj,glsc);
	//arg2 = X->vfields[arg1 + X->valOff];
	// rPush(thisStack,(int)X + arg1 * 4 );
	vPush(thisStack,arg1);
	break;
      case push:
	arg1 = op1(bc,&glsc);
#ifdef TRACE
	fprintf(trace,"push ");
#endif
	arg2 = thisObj->vfields[arg1 + thisObj->valOff];
	vPush(thisStack,arg2);
#ifdef TRACE
	fprintf(trace,"%s[%i] = %i\n",nameOf(thisObj),arg1,arg2);
#endif
	break;
      case rpush:
	arg1 = op1(bc,&glsc);
	X = getR(thisObj,arg1);
#ifdef TRACE
	fprintf(trace,"rpush %s[%i] = %s \n",nameOf(thisObj),arg1,nameOf(X));
#endif
	rPush(thisStack,X);
	break;
      case pushg:
	arg1 = op1(bc,&glsc);
	X = rPop(thisStack);
	if (X == NULL) {
#ifdef __arm__
#else	  
	  printf("\n***pushg == NULL %i %i \n",arg1,(int)X);
#endif
	  runTimeErrorX("Reference is NONE",thisObj,glsc);
	}
	arg2 = X->vfields[arg1 + X->valOff];
#ifdef TRACE
	fprintf(trace,"pushg %s[%i + %i] = %i\n",nameOf(X),arg1,X->valOff,arg2);
#endif 
	vPush(thisStack,arg2);
	break;
      case ovpushg:
	arg1 = op1(bc,&glsc);
	arg3 = vPop(thisStack); //descInx of valObj,not used
	arg2 = vPop(thisStack);
	X = rPop(thisStack);
	if (X == NULL) {
	  runTimeErrorX("Reference is NONE",thisObj,glsc);
	}
	arg3 = getV(X,arg1 + arg2 - 1);
        vPush(thisStack,arg3);
#ifdef TRACE
	fprintf(trace,"ovpushg %s[%i] = %s\n",nameOf(X),arg3);
#endif
	break;
      case rpushg:
	arg1 = op1(bc,&glsc);
	X = rPop(thisStack);
	if (X == NULL) {
#ifdef __arm__
#else
	  printf("\n***rpushg == NULL %i %i\n",arg1,(int)X);
#endif
	  runTimeErrorX("Reference is NONE",thisObj,glsc);
	}
	Y = getR(X,arg1);
#ifdef __arm__
#ifdef armtrace
	putstr("rpushg: ");
	puthex((int)Y);
	putch((char)10);
#endif
#endif
	rPush(thisStack,Y);
#ifdef TRACE
	fprintf(trace,"rpushg %s[%i] = %s\n",nameOf(X),arg1,nameOf(Y));
#endif
	break;
      case xpush:
	arg1 = op1(bc,&glsc); // off
	arg2 = vPop(thisStack); // inx
	arg3 = thisObj->vfields[arg1 + arg2 + newAllocOff];
	vPush(thisStack,arg3);
#ifdef TRACE
	fprintf(trace,"xpush %s[%i+%i] = %i\n",nameOf(thisObj),arg1,arg2,arg3);
#endif
	break;
      case xrpush:
	arg1 = op1(bc,&glsc); // off
	arg2 = vPop(thisStack); // inx
	X = getR(thisObj,arg1 + arg2 + newAllocOff);
	rPush(thisStack,X);
#ifdef TRACE
	fprintf(trace,"xrpush %s[%i+%i] = %s\n",nameOf(thisObj),arg1,arg2,nameOf(X));
#endif
	break;
      case xpushg:
	arg1 = op1(bc,&glsc);
	isValueObj = op1(bc,&glsc);
	size = op1(bc,&glsc);
	if (isValueObj == 0 ){
	  // imply size == 1 
	  X = rPop(thisStack);
	  if (X == NULL) runTimeErrorX("Reference is NONE",thisObj,glsc);
	  arg2 = vPop(thisStack);
#ifdef TRACE
	  fprintf(trace,"xpushg %i %i %i %i\n",arg1,isValueObj,size,arg2);
	  dumpObj(trace,"xpushg",X);
#endif
	  for (i=0; i < size; i++){
	    int ix = 0;
	    if (size == 1) ix = arg1 + arg2 + newAllocOff - i;
	    else ix = arg1 + arg2 + newAllocOff + i - 1;
	    arg3 = X->vfields[ix]; // need range check - and do we adjust for range?
	    
#ifdef TRACE
	    fprintf(trace,"xpushg %s[%i] = %i\n",nameOf(X),ix,arg3);
#endif
	    vPush(thisStack,arg3); 
	  }
	}
	else{
	  int inx = vPop(thisStack);
	  vPush(thisStack,arg1 + inx + newAllocOff - 1 );
	} 
	break;
      case xrpushg:
	arg1 = op1(bc,&glsc);
	X = rPop(thisStack); 
	if (X == NULL) runTimeErrorX("Reference is NONE",thisObj,glsc);
	arg2 = vPop(thisStack);
	Y = getR(X,arg1 + arg2 + newAllocOff); // need range check - do we adjust for range?
#ifdef TRACE
	fprintf(trace,"xrpushg %s[%i+%i] = %s/%i)\n",nameOf(X),arg1,arg2,nameOf(Y),(int)Y);
#endif
	rPush(thisStack,Y); 
	break;
      case store:
	arg1 = op1(bc,&glsc);
	arg2 = vPop(thisStack);
#ifdef TRACE
	fprintf(trace,"store %s[%i] = %i\n",nameOf(thisObj),arg1,arg2);
#endif
	thisObj->vfields[arg1 + thisObj->valOff] = arg2; 
     	break;
      case rstore:
	arg1 = op1(bc,&glsc);
#ifdef TRACE
	fprintf(trace,"rstore %i ",arg1);
#endif
	X = rPop(thisStack);
#ifdef __arm__
#ifdef armtrace	
	putstr("rstore: ");
	puthex((int)X);
	putstr(" at:thisObj: ");
	puthex((int)thisObj);
	putch('[');
	putint(arg1);
	putstr("]\n");
#endif	
#endif
	putR(thisObj,arg1,X);
#ifdef __arm__
#ifdef armtrace
	puthex((int)getR(thisObj,arg1));
	putstr("\n");
	#endif
#endif
#ifdef TRACE
	fprintf(trace,"thisObj:%s[%i] = X:%s\n",nameOf(thisObj),arg1,nameOf(X));
#endif
	break;
      case storeg:
	arg1 = op1(bc,&glsc); // off/inx
	X = rPop(thisStack);
	if (X == 0) runTimeErrorX("Reference is none",thisObj,glsc);
	arg2 = vPop(thisStack); // value
#ifdef TRACE
	fprintf(trace,"storeg %s[%i+%i] = %i \n",nameOf(X),arg1,X->valOff,arg2);
#endif
	X->vfields[arg1 + X->valOff] = arg2;
	break;
      case ovstoreg:
	arg1 = op1(bc,&glsc);

	arg2 = vPop(thisStack);
	X = rPop(thisStack);
	if (X == 0) runTimeErrorX("Reference is none",thisObj,glsc);
	arg3 = vPop(thisStack); //descInx of valObj, not used	
	arg3 = vPop(thisStack);
	X->vfields[arg1 + arg3 - 1] = arg2;
#ifdef TRACE
	fprintf(trace,"ovstoreg %i\n",arg1);
#endif
	break;
      case vassign:
	arg1 = op1(bc,&glsc);   // size
	mode = op1(bc,&glsc); 
	arg2 = vPop(thisStack); // destOff
        Y = rPop(thisStack);    // destObj
#ifdef TRACE
	fprintf(trace,"vassign %i\n",arg1);
#endif
	int D[10];
	for (i = 1; i <= arg1; i++){
	  D[i] = vPop(thisStack);
	}
	if (mode == 1) { // originIsValObj
	  arg3 = vPop(thisStack); //descInx of valObj,not used
	  arg2 = arg2 + vPop(thisStack) - 1;
	}
        for (i = 1; i <= arg1; i++) {
	  putV(Y,arg2 + arg1 - i,D[i]);
	}
#ifdef TRACE
	dumpObj(trace,"dest",Y);
#endif
	break;
      case rstoreg:   
	arg1 = op1(bc,&glsc);
	X = rPop(thisStack);
	if (X == 0) {
	  runTimeErrorX("Reference is none",thisObj,glsc);
	};
	Y = rPop(thisStack);
	putR(X,arg1,Y);
#ifdef TRACE
	fprintf(trace,"rstoreg %s[%i] = %s \n",nameOf(X),arg1,nameOf(Y));
#endif
	break; 
      case xstore:
	arg1 = op1(bc,&glsc);
	arg2 = vPop(thisStack); // inx
	arg3 = vPop(thisStack); // value;
#ifdef TRACE
	fprintf(trace,"xstore %s[%i+%i] = %i\n",nameOf(thisObj),arg1,arg2,arg3);
#endif
	thisObj->vfields[arg1 + arg2 + newAllocOff] = arg3;
	break;
      case xrstore:
	arg1 = op1(bc,&glsc);
	arg2 = vPop(thisStack); // inx
	X = rPop(thisStack); // value;
#ifdef TRACE
	fprintf(trace,"xrstore %s[%i+%i] = %s\n",nameOf(thisObj),arg1,arg2,nameOf(X));
#endif
	putR(thisObj,arg1 + arg2 + newAllocOff,X);
	break;
      case xstoreg:
	arg1 = op1(bc,&glsc);       // off
	isValueObj = op1(bc,&glsc);
	size = op1(bc,&glsc);
	X = rPop(thisStack);
	if (X == 0) runTimeErrorX("Reference is none",thisObj,glsc);
	arg2 = vPop(thisStack);  // inx

	if (isValueObj == 1) vPop(thisStack);

	for (i = 0; i < size; i++) {
	  arg3 = vPop(thisStack);
	  int ix = arg1 + arg2 + newAllocOff - i;
#ifdef TRACE
	  fprintf(trace,"xstoreg %i %i %i %s[%i] = %i\n",arg1,isValueObj,size,nameOf(X),ix,arg3);
#endif
	  X->vfields[ix] = arg3;
	}
#ifdef TRACE
	dumpObj(trace,"xstoreg",X);
#endif
	break;
      case xrstoreg:
	arg1 = op1(bc,&glsc);
	X = rPop(thisStack);
	arg2 = vPop(thisStack);
	Y = rPop(thisStack);
	if (X == 0) runTimeErrorX("Reference is none",thisObj,glsc);
#ifdef TRACE
	fprintf(trace,"xrstoreg %s[%i+%i] = %s(%i)\n",nameOf(X),arg1,arg2,nameOf(Y),(int)Y);
#endif
	putR(X,arg1 + arg2 + newAllocOff,Y);
	break;
      case pushValue:
	arg1 = op1(bc,&glsc);   // size
	arg3 = vPop(thisStack); //descInx of valObj, not used	
	arg2 = vPop(thisStack); // srcOff
	X = rPop(thisStack);    // srcObj
#ifdef TRACE
	fprintf(trace,"pushValue %s %i %i ",nameOf(X), arg1,arg2);
#endif
	for (i = 0; i < arg1; i++) {
	  arg3 = getV(X,arg2 + i);
#ifdef TRACE
	  fprintf(trace,"val: %i ",arg3);
	  if (i == (arg1 - 1)) fprintf(trace,"\n");
#endif
          vPush(thisStack,arg3);
	}
#ifdef TRACE
	StacksToOut(trace,thisObj,thisStack);
#endif
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
      case swap:
        arg1 = vPop(thisStack);
	arg2 = vPop(thisStack);
#ifdef TRACE
	fprintf(trace,"swap top-1: %i top: %i\n",arg2,arg1);
#endif
	vPush(thisStack,arg1);
	vPush(thisStack,arg2);
	break;
      case _rswap:
	arg1 = op1(bc,&glsc); // arg1 > 1, not handled
#ifdef TRACE
        fprintf(trace,"rswap %i\n",arg1);
#endif
	if (arg1 > 0) {
#ifdef TRACE	  
	  printf("rswap: %i\n",arg1);
#endif	  
	  rswapIndexed(thisStack,arg1);
	}else {
	  X = rPop(thisStack);
	  Y = rPop(thisStack);
#ifdef TRACE
        fprintf(trace,"\trswap %s %s\n",nameOf(X),nameOf(Y));
#endif
	rPush(thisStack,X);
	rPush(thisStack,Y);
	}
	break;
      case rtn:
	arg1 = op1(bc,&glsc);
#ifdef TRACE
	fprintf(trace,"rtn %c ",arg1);
#endif
	if ((suspendEnabled == 1) && (thisObj == enablee)) 
	  suspendEnabled = suspendEnabled - 1;
#ifdef TRACE
	fprintf(trace,"\n\trtn:FROM thisObj:'%s'(descNo:%i,glsc:%i,thisStack:'%s') \n"
		,nameOf(thisObj),currentDescNo,glsc,nameOf(thisStack));
#endif
	X = thisObj;
#ifdef TRACE
	StacksToOut(trace,thisObj,thisStack);
#endif	
	thisStack = rPop(thisObj);
	thisObj = rPop(thisObj);
	glsc = cRestoreReturn(thisObj);
	currentDescNo = cRestoreReturn(thisObj);
#ifdef TRACE	
	StacksToOut(trace,thisObj,thisStack);
#endif	
	bc = codeFromDescNo(currentDescNo);
        if (! isXbeta)rPush(thisStack,X);
#ifdef TRACE
	fprintf(trace,"\tTO thisObj:'%s'(descNo:%i,glsc:%i,thisStack:'%s')"
		,nameOf(thisObj),currentDescNo,glsc,nameOf(thisStack));
	dumpStack(trace,thisStack);
#endif
#ifdef EVENT
	if (((char)arg1 == 'A') && (thisObj != X)){
	  mkEvent(rtn_event,thisObj,X,myCorigin(X),false,currentDescNo,glsc);
	}
#endif
	break;
      case rtnV:
	arg1 = lscPop(thisObj); // staticOff
#ifdef TRACE
	fprintf(trace,"rtnV: %i\n",arg1);
#endif
	glsc = cRestoreReturn(thisObj);
	currentDescNo = cRestoreReturn(thisObj);        
	bc = codeFromDescNo(currentDescNo);
	thisObj->valOff = thisObj->valOff - arg1;
	//fprintf(trace,"rtnV2: glsc:%i descNo: %i op: %i\n",glsc,currentDescNo,bc[glsc]);
	break;
      case mvStack:
#ifdef TRACE
	//fprintf(trace,"mvStack %s -> %s [",nameOf(thisObj),nameOf(thisStack));
	fprintf(trace,"mvStack");
#endif
	thisStack = thisObj;
#ifdef TRACE
	//for (i = 0; i < thisStack->rtop; i++) fprintf(trace,"%s ",nameOf(thisStack->rstack[i+1]));
	//fprintf(trace,"]\n");
	StacksToOut(trace,thisObj,thisStack);//,thisBlock);
#endif
	break;
      case setThisStack:
#ifdef TRACE
	fprintf(trace,"setThisStack\n");
#endif
	thisStack = thisObj->rstack[thisObj->rtop];
        break;
      case rpopThisObj:
#ifdef TRACE
	fprintf(trace,"rpopThisObj\n");
#endif
	thisObj = rPop(thisObj);
        break;
      case toSuper:
	arg1 = op2(bc,&glsc);
#ifdef TRACE
	fprintf(trace,"toSuper %i thisObj: %s",arg1,nameOf(thisObj));
#endif
	currentDescNo = arg1;
	bc = codeFromDescNo(arg1);
	glsc = getAllocE(getDesc(arg1));
	//bc = (ObjDesc) getByteCode(getDesc(arg1));
	//glsc = getAllocE(getDesc(arg1));             
#ifdef TRACE  
	fprintf(trace," bc: %i glsc: %i\n",(int)bc,glsc);
#endif
	break;
      case call:
	/*return*/

	saveContext();
	doCall(thisBlock,false,true);
	restoreContext();

	break;
      case susp:
#ifdef TRACE
	fprintf(trace,"susp ");
#endif
	callee = rPop(thisStack);
	if ((suspendEnabled == 1) && (callee == enablee)) suspendEnabled = suspendEnabled - 1;

	saveContext();
	doSuspend(thisBlock,callee,false);
	restoreContext();

	break;
      case alloc:
	arg1 = op2(bc,&glsc);
	arg2 = op1(bc,&glsc);
#ifdef TRACE
	fprintf(trace,"alloc %i %i ",arg1,arg2);
#endif
	/*return*/ 

	saveContext();
	allocObj(thisBlock,rPop(thisBlock->thisStack),arg1,arg2,0,0);
	restoreContext();
	break;
      case tstOriginNone:
#ifdef TRACE
	fprintf(trace,"tstOriginNone\n");
#endif
	if (rTopElm(thisStack,0) == NULL)
	  runTimeErrorX("Origin of invoke is NONE",thisObj,glsc); 
	break;
      case invoke:
	arg1 = op2(bc,&glsc);
	arg2 = op2(bc,&glsc);
        arg3 = op1(bc,&glsc);
#ifdef TRACE
	fprintf(trace,"invoke %i %i %i thisObj: %s",arg1,arg2,arg3,nameOf(thisObj));
#endif
#ifdef __arm__
	//dumpVstack(trace,thisStack);
#endif
	saveContext();
        invokeObj(thisBlock,arg1,arg2,0,0);
	restoreContext();
	//fprintf(trace,"thisObj: %s thisStack: %s\n",nameOf(thisObj),nameOf(thisStack));
	break;
      case mkVindexed:
	arg1 = op2(bc,&glsc);
#ifdef TRACE
	fprintf(trace,"mkVindexed %i ", arg1);
#endif
	saveContext();
	mkIndexed(arg1,false,thisBlock);
	restoreContext(true,thisBlock);
	break;
      case mkRindexed:
	arg1 = op2(bc,&glsc);
	saveContext();
	mkIndexed(arg1,true,thisBlock);
	restoreContext();
	break;
      case invokeVal:
	arg1 = op2(bc,&glsc);
	arg2 = op2(bc,&glsc);
	saveContext();
        invokeValObj(thisBlock,arg1,arg2);
	restoreContext();
	break;
      case boxedInvokeVal:
	arg1 = op2(bc,&glsc);
	arg2 = op2(bc,&glsc);
	cSaveReturn(thisObj,currentDescNo,glsc);
	callee = rPop(thisStack);
	rPush(callee,thisObj);
	rPush(callee,thisStack);
	thisObj = callee;
	saveContext();
        invokeValObj(thisBlock,arg1,arg2);
	restoreContext();
	break;
      case invokeExternal:
	arg1 = op1(bc,&glsc);
#ifdef TRACE
        fprintf(trace,"invokeExternal: %i \n",arg1);
#endif
	switch (arg1) {
	case 1: // arm:pinmode
	  arg3 = vPop(thisStack); // mode
	  arg2 = vPop(thisStack); // pinno
	  Y = rPop(thisStack); // origin - not used
#ifdef __arm__
	  pinMode(arg2,arg3);
	  rPush(thisStack,Y); // just a dummy
#endif
#ifdef __ARDIUNO__
	  printf("pinMode(%i,%i)\n",arg2,arg3);
	  mraa_gpio_context pin = mraa_gpio_init(13);
	  if (arg3 == 0) 
	    {printf("OUTPUT\n"); mraa_gpio_dir(pin,MRAA_GPIO_OUT);}
	  else 
	    {mraa_gpio_dir(pin,MRAA_GPIO_IN);};
#elif defined __XTENSA__
          gpio_pad_select_gpio(BLINK_GPIO);
	  gpio_set_direction(BLINK_GPIO, GPIO_MODE_OUTPUT);
#elif defined  __CYGWIN__
	  printf("pinMode(%i,%i) not implemented for this platform\n"
		 ,arg2,arg3);
#endif
	  break;
	case 2: // arm: digitalWrite
	  arg3 = vPop(thisStack);
	  arg2 = vPop(thisStack);
	  Y = rPop(thisStack); // origin - not used
#ifdef __arm__
	  putstr("digitalWrite: ");
	  puthex(arg2);
	  putstr(",");
	  puthex(arg3);
	  putstr("\n");
	  //dumpVstack(trace,thisStack);
	  //arg3 = set_led();
	  arg3 = digitalWrite(arg2,arg3);
	  //rPush(thisStack,Y); // just a dummy - so why did we do it? 2021-09-09
#endif
#ifdef __ARDIUNO__
	  if (arg3 == 0) 
	    {mraa_gpio_write(pin,LOW);}
	  else 
	    {mraa_gpio_write(pin,HIGH);};
#elif defined __XTENSA__
	  gpio_set_level(BLINK_GPIO, arg3);
#elif defined  __CYGWIN__
	  printf("digitalWrite(%i,%i) not implemented for this platform\n",arg2,arg3);
	  //rPush(thisStack,Y); // just a dummy
#endif
	    break;        
	case 3:
	  arg2 = vPop(thisStack);
	  Y = rPop(thisStack); // origin - not used
#ifdef linux
	  sleep(arg2); 
#endif
	  break;
	case 4:
#ifdef usekbhit
#ifdef linux
#elif defined __CYGWIN__
          arg1 = _getch();
#endif
	  Y = rPop(thisStack); // origin - not used
#ifdef TRACE
          fprintf(trace,"_getch: %i\n",arg1);
#endif
	  vPush(thisStack,arg1);
#else
	  runTimeError("_getch not included (Cygwin) or implemented (Linux)");
#endif
	  break;
	case 5:
#ifdef usekbhit
	  Y = rPop(thisStack); // origin - not used
#ifdef linux
#elif defined __CYGWIN__
	  vPush(thisStack,_kbhit());
#endif
#else
	  runTimeError("_kbhit not included (Cygwin) or implemented (Linux)");
#endif
	  break;
	case 6:
#ifdef usewinsock2
	  printf("InvokeExternal: new_socket== socket(AF_INET, SOCK_STREAM, 0)\n");
	  //arg1 = socket(AF_INET, SOCK_STREAM, 0);
	  Y = rPop(thisStack); // origin - not used
#ifdef linux
#elif defined  __CYGWIN__
	  arg1 = socket(AF_INET, SOCK_STREAM,0);
	  if (arg1 == INVALID_SOCKET)
	    printf("Invalid socket: %d\n", WSAGetLastError());
	  vPush(thisStack,arg1);
#endif
#ifdef __arm__
#else
	  printf("No winsock2 library included - check #define usewinsock2\n");
#endif
#endif
	  //vPush(thisStack,100);
	  break;
	case 7:
#ifdef usewinsock2
	  arg3 = vPop(thisStack); // port no
	  Y = rPop(thisStack);    // the name of the server to connect to
	  X = rPop(thisStack);    // origin - not used
	  arg1 = vPop(thisStack); // socket: sockfd
	  //mkCstring(Y);
	  //printf("Host: [%s]\n",mkCstring(Y));
#ifdef linux
#elif defined  __CYGWIN__
          msg = mkCstring(Y);
	  he = gethostbyname(msg);
#endif
	  //Cast the h_addr_list to in_addr ,
	  //since h_addr_list also has the ip address in long format only
#ifdef linux
#elif defined  __CYGWIN__
	  addr_list = (struct in_addr **) he->h_addr_list;
	  
	  for(i = 0; addr_list[i] != NULL; i++) 
	    { //Return the first one;
	      strcpy(ip , inet_ntoa(*addr_list[i]) );
	    }
	  printf("Connect: %i %s %s %i \n",arg1,msg,ip,arg2);
	  server.sin_addr.s_addr = inet_addr(ip);
	  server.sin_family = AF_INET;
	  server.sin_port = htons(arg3);
	  arg3 = connect(arg1 , (struct sockaddr *)&server , sizeof(server));
	  if (arg3 < 0) printf("Connect error\n");
#endif
	  vPush(thisStack,arg3);
#endif
	  break;
	case 8:
#ifdef usewinsock2
	  arg1 = vPop(thisStack);
	  X = rPop(thisStack); // The message to be send
	  Y = rPop(thisStack); // origin - not used
	  
	  //msg = "Hello world\r\n\r\n";
#ifdef linux
#elif defined  __CYGWIN__
	  msg = mkCstring(X);
	  //printf("Send: %i %s\n", arg1, msg);
	  arg3 = send(arg1,msg,strlen(msg),0);
	  if (arg3 < 0) printf("Send error\n");
#endif
	  vPush(thisStack,arg3);
#endif
	  break;
	case 9:
#ifdef useqinsock2
	  arg1 = vPop(thisStack);
	  Y = rPop(thisStack); // origin - not used
	  //printf("Recv: %i\n",arg1);
#ifdef linux
#elif defined  __CYGWIN__
	  msg = malloc(sizeof(char) * 2000);
	  arg2 = recv(arg1,msg,2000,0);
	  if (arg2 == SOCKET_ERROR){ 
	    arg3 = WSAGetLastError();
	    if (arg3 == WSAEWOULDBLOCK) { 
	      //printf("Recv NON-BLOCK\n");
	      rPush(thisStack,NULL);
	    } else {
	      printf("Recv failed with error code : %d\n" ,arg3);
	    }
	  }else {
	    msg[arg2] = 0;
	    //printf("Receive: %i %i %s\n",arg1,arg2,msg);
	    saveContext();
	    C2QBstring(thisBlock,msg);
	    restoreContext();
	  }
#endif
#endif
	  break;
	case 10:
#ifdef usewinsock2
	  arg1 = vPop(thisStack);
	  Y = rPop(thisStack);
#ifdef linux
#elif defined  __CYGWIN__
	  closesocket(arg1);
#endif
#endif
	  break;
	case 11:
#ifdef usewinsock2
	  arg2 = vPop(thisStack);
	  arg1 = vPop(thisStack);
	  Y = rPop(thisStack); // origin
	  printf("Bind: %i %i\n",arg1,arg2);
	  //Prepare the sockaddr_in structure
#ifdef linux
#elif defined  __CYGWIN__
	  server.sin_family = AF_INET;
	  server.sin_addr.s_addr = INADDR_ANY;
	  server.sin_port = htons( arg2 );
	  arg1 = bind(arg1 ,(struct sockaddr *)&server , sizeof(server));
	  if ( arg1 == SOCKET_ERROR)
	    {
	      printf("Bind failed with error code : %d" , WSAGetLastError());
	    }
#endif
	  vPush(thisStack,arg1);
#endif
	  break;
	case 12:
#ifdef usewinsock2
	  arg1 = vPop(thisStack);
	  Y = rPop(thisStack); // origin
#ifdef linux
#elif defined  __CYGWIN__
	  arg2 = listen(arg1,3);
#endif
#ifdef __arm__
#else
	  printf("Listen: %i %i\n",arg1,arg2);
#endif
#endif
	  break;
	case 13:
#ifdef usewinsock2
	  arg1 = vPop(thisStack);
	  Y = rPop(thisStack); // origin
#ifdef linux
#elif defined  __CYGWIN__
	  arg2 = sizeof(struct sockaddr_in);
	  //printf("Accept: %i\n",arg1);
	  arg2 = accept(arg1,(struct sockaddr *)&client, &arg2 );
	  //printf("After accept: %i\n",arg2);
	  if (arg2 ==  INVALID_SOCKET) {
	    arg3 = WSAGetLastError();
	    if (arg3 == WSAEWOULDBLOCK) {
	      //printf("Accept: no request in buffer\n");
	      arg2 = 1;
	    }else
	       printfs("accept failed with error code : %d\n" , arg3);
	  }
#endif
	  vPush(thisStack,arg2);
#endif
	  break;
	case 14:
#ifdef usewinsock2
	  arg2 = vPop(thisStack);
	  arg1 = vPop(thisStack);
          Y = rPop(thisStack); // origin
#ifdef linux
#elif defined  __CYGWIN__
	  u_long iMode = 1;
	  arg3 = ioctlsocket(arg1, FIONBIO,&iMode);
	  if (arg3 != NO_ERROR)
	    printf("ioctlsocket failed with error: %ld\n", arg3);  
#endif
#endif
	  break;
	}
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
	arg1 = op1(bc,&glsc);
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
#ifdef __arm__
	    putch(arg2);
#else
	    printf("%c",(char)arg2);
	    fprintf(output,"%c",(char)arg2);
	    fflush(output);
#ifdef TRACE	    
	    fprintf(trace,"put: %c\n",(char)arg2);
#endif
	    //printf("\n");
	    //fflush(stdout); apparently using stdout gives a linker error!?
	    //fpurge(stdout);
	    // fprintf(stdout,"Hello");
#endif
	    break;
          case 23: // getch from  stdin
#ifdef __arm__
#else
	    arg3 = scanf("%c",&ch);
#endif
#ifdef TRACE
            printf("get: %c\n",ch);
#endif
	    vPush(thisStack,ch);
	    break;
	  case 10: // attach
	    arg2 = vPop(thisStack);
#ifdef TRACE
	    fprintf(trace,"attach %i\n",arg2);
#endif
	    suspendEnabled = suspendEnabled + 1;
	    timeToSuspend = arg2;
	    //glsc = glsc - 1;

	    saveContext();
	    doCall(thisBlock,true,true);
	    restoreContext();

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
	    fprintf(trace,"fork threadNo=%i ",threadNo);
#endif
#ifdef __arm__
	    putstr("forkA\n");
#endif
	    
	    //Y = rPop(thisStack); dont pop to Y if GC
	    Y = Y;
	    
#ifdef TRACE
	    fprintf(trace,"fork A ");
#endif
	    // should we use heapAlloc here? Is not a Beta object
	    //Block *B = (Block *)heapAlloc(thisBlock,sizeof(Block));
	    Block *B = (Block *)malloc(sizeof(Block));
#ifdef TRACE
	    fprintf(trace,"fork B threadStbNo: %i ",threadStubDescNo);	 
#endif   
	    // B is not initialized - see below
	    // a problem if a GC is started by allocTemplate!
	    B->thisModule = NULL;
	    B->thisObj = thisObj;
	    B->thisStack = thisStack;
	    B->bc = NULL;
	    B->currentDescNo = 0;
	    B->top = thisObj;
	    B->world = NULL;
	    B->origin = NULL;
	    X = allocTemplate(B,newId(thisBlock),threadStubDescNo,true,0,0);
	    Y = rPop(thisStack); // ensure Y is ok after GC
#ifdef TRACE
	    fprintf(trace,"fork C");
#endif
	    rPush(X,Y);
#ifdef TRACE
	    fprintf(trace,"fork D");
	    fflush(trace);
#endif
#ifdef TRACE
	    fprintf(trace,"%s top:%s\n",nameOf(X),nameOf(Y));
	    fflush(trace);
#endif
	    B->thisModule = X;
	    B->thisObj = X;
	    B->thisStack = X;
	    B->bc = myCode(X);
	    B->currentDescNo = threadStubDescNo;
	    B->top = Y;
	    B->world = thisBlock->world;
	    B->origin = NULL;
	    B->output = output;
#ifdef TRACE
	    //printf("\ncurrentDescNo: %i %i %i threadNo: %i\n"
	    //,B->currentDescNo,B->glsc,(int)B->bc,threadNo);
#endif
	    B->glsc = 0;
	    // should we use heapAlloc here? Is not a Beta object
	    //char *fileName = heapAlloc(thisBlock,12);
	    char *fileName = (char *)malloc(12);
#ifdef __arm__

#else
	    if (sprintf (fileName,"traceF%i.s",threadNo + 1) < 0) printf("sprintf error\n");
#endif

	    B->traceFile = fileName;
	    //threadNo = threadNo + 1;
	    B->threadId = threadNo + 1;
	    if ((threadNo + 1) > MAX_THREADS) {
#ifdef __arm__
#else	      
	      printf("\nFatal error: too many threads: %i\n",threadNo);
	      fprintf(trace,"\nFatal error: too many threads: %i\n",threadNo);
	      fflush(output);
	      fflush(trace);
#endif	      
	      stop;
	    }
	    threadStatus[B->threadId] = t_running;
#ifdef linux
	    pthread_attr_t attr;      // not used here - NULL may be
	    pthread_attr_init(&attr); // for &attr in pthread_create
	    int iret = 
	      pthread_create(&pthreadArray[threadNo],&attr,interpreter,(void *)B);
#elif defined  __CYGWIN__
	    hThreadArray[threadNo] = CreateThread(NULL,0,interpreter,(LPVOID)B,0,0);
#ifdef withGC
	    printf("CreateThread: threadId: %i, threadNo: %i system_handle: %i system_threadId: %i\n",
		   B->threadId,
		   threadNo,hThreadArray[threadNo],
		   GetThreadId(hThreadArray[threadNo]));
#endif

#elif __arm__
	    extern void Bfork(void *,void *,int);
	    Bfork(interpreter,B,threadNo + 1);
#elif defined __XTENSA__

	    if ((threadNo + 1 > 1)) threadNo = -1;
	    //printf("Fork: %i \n",threadNo + 1);
	    xTaskCreatePinnedToCore(&interpreter, "task0", 2048, B, 5, NULL, threadNo + 1); 
#endif
	    threadNo = threadNo + 1;
	    hasThreads = true;
	    break;
	  case 14: // cmpAndSwap 
	    arg1 = vPop(thisStack); // offset 
	    arg2 = vPop(thisStack); // new value
	    //printf("off: %i new: %i\n",arg1,arg2);
	    X = rPop(thisStack);
	    //printf("Obj: %s\n",nameOf(X));
	    arg3 = X->vfields[arg1];
	    //printf("cmpAndSwap %i %i %x\n",arg1,arg2,(int)X);
	    // V = cmpxchlg(&X->vfields[arg1],arg3,arg2);
	    // V = cmpxchlg(&X->vfields[arg1],0,arg2);
	    //printf("[");
	    // if &X->vfields[arg1] = 0 then 
            //    &X->vfields[arg1] := arg2 
            //    return 1
            // else
            //    return 0
            // for some reason, we have reversed the return value? 
            // we return 1 if failure and 0 if succes?
            // see if below!?
#if defined  __CYGWIN__ || linux
	    /* bool __sync_bool_compare_and_swap 
	     *          (type *ptr, type oldval type newval, ...)
	     * type __sync_val_compare_and_swap 
	     *           (type *ptr, type oldval type newval, ...)
	     * These builtins perform an atomic compare and swap. 
	     * That is, if the current value of *ptr is oldval,
	     * then write newval into *ptr.
	     * The 'bool' version returns true if the comparison is successful 
	     * and newval was written. The 'val' version returns the contents 
	     * of *ptr before the operation. 
	     */
	    V = __sync_bool_compare_and_swap(&X->vfields[arg1],0,arg2);
	    if (V) {V = 0;} else {V = 1;};
#elif __arm__
	    extern int cmpAndSwap(int adr, int old, int new); 
	    V = cmpAndSwap((int)&X->vfields[arg1],0,arg2);
            V = 0x8899;
	    V = __sync_val_compare_and_swap(&X->vfields[arg1],0,arg2);
	    if (V) {V = 0;} else {V = 1;};
#elif __XTENSA__
	    /* From: 
	     * https://github.com/espressif/esp-idf/blob/master/components/freertos/include/freertos/portmacro.h#L273
	     * Wrapper for the Xtensa compare-and-set instruction. 
	     * This subroutine will atomically compare
	     * *addr to 'compare'. If *addr == compare, *addr is set to *set. 
	     * *set is updated with the previous
	     * value of *addr (either 'compare' or some other value.)
	     *
	     * Warning: From the ISA docs: in some (unspecified) cases, 
	     * the s32c1i instruction may return the
	     * *bitwise inverse* of the old mem if the mem wasn't written. 
	     * This doesn't seem to happen on the
	     * ESP32 (portMUX assertions would fail).
	     *
	     * static inline void uxPortCompareSet
	     * (volatile uint32_t *addr, uint32_t compare, uint32_t *set) {
	     *__asm__ __volatile__ (
	     *  		    "WSR 	    %2,SCOMPARE1 \n"
	     *  		    "S32C1I     %0, %1, 0	 \n"
	     *  		    :"=r"(*set)
	     *  		    :"r"(addr), "r"(compare), "0"(*set)
	     *  		    );
	     */
	     uxPortCompareSet((uint32_t *)&X->vfields[arg1],0,(uint32_t *)&arg2);
	     /* if arg2 = 0 then success else failure */
	     V = arg2;
#else
	     V = 0; // not used 
#endif
	    //printf("]");
	    //printf("cmpAndSwap off: %i new: %i old: %i %s adr: %i\n"
	    //	    ,arg1,arg2,arg3,nameOf(X),(int)&X->vfields[arg1,V]);
#ifdef TRACE
	    fprintf(trace,"cmpAndSwap new: %i old: %i %s adr: %i V: %i"
		    ,arg2,arg3,nameOf(X),(int)&X->vfields[arg1],V);
#endif
	    
#ifdef TRACE  
	    fprintf(trace,"%i\n",V);
#endif
	    /*printf("bbb: %x %x %x \n"
		   ,(int)thisStack,(int)&heap[0],(int)&heap[heapTop]);
		   printf(" %s\n",nameOf(thisStack));*/
	    vPush(thisStack,V);
	    break; 
	  case 15: // sleep
	    arg1 = vPop(thisStack);
#ifdef TRACE
	    fprintf(trace,"sleep %i\n",arg1);
#endif
#ifdef linux
	    usleep(arg1); // apparently in micro seconds
#elif defined  __CYGWIN__
	    Sleep(arg1); // apparently in milli seconds - no diff if arg1/1000!?
#elif defined __XTENSA__
	    vTaskDelay(arg1);
#endif
	    break;
	  case 17: 
#ifdef TRACE
	    fprintf(trace,"thisCore %s ",nameOf(thisBlock->thisObj));
	    fprintf(trace," %s \n",nameOf(thisBlock->top));
#endif
	    rPush(thisStack,thisBlock->top);
	    break;
	  case 22: 
#ifdef __XTENSA__
	    arg1 = xPortGetCoreID();
            vPush(thisStack,arg1);
#else
#ifdef __arm__
#else
	    printf("\n***thisCoredId is not implemented for this platform!\n");
#endif
#endif
	    break;
	  case 118: // asString
	    saveContext();
	    ConvertIndexedAsString(thisBlock);
	    restoreContext();
            break;
	  case 130: // file_open
#ifdef TRACE
	    printf("file_open:\n");
#endif
	    vPush(thisStack,fileOpen(rPop(thisStack)));	    
	    break;
	  case 131: // file_get
	    vPush(thisStack,fileGet(vPop(thisStack)));
	    break;
	  case 132: // file_eof
	    vPush(thisStack,fileEos(vPop(thisStack)));
	    break;
	  case 133: // file_close
	    fileClose(vPop(thisStack));
	    break;
          case 140: // dumpObj

	    break;
	  case 141: // log
	    float1 = fPop(thisStack);
#ifdef __arm__
#else
	    float2 = log(float1);
#endif
	    fPush(thisStack,float2);
	    break;
	  case 142: // printf
	    float1 = fPop(thisStack);
#ifdef __arm__
#else
	    printf("%f",float1);
#endif
	    vPush(thisStack,0);
	    break;
	  case 143: // lsqrt
	    float1 = fPop(thisStack);
#ifdef __arm__
#else
	    float2 = sqrt(float1);
#endif
	    fPush(thisStack,float2);
	    break;	    
	  default:
	    RTE2("\n\n*** prim: missing case: ",arg1);
	    runTimeError("prim: missing case");
	  }
	break;
      case jmp:
	glsc = op2(bc,&glsc) - 1;
#ifdef TRACE
	fprintf(trace,"jmp %i\n",glsc);
#endif
	break;
      case jmpFalse:
	arg1 = op2(bc,&glsc);
	arg2 = vPop(thisStack);
#ifdef TRACE
	fprintf(trace,"jmpFalse %i %i \n",arg1, arg2);
#endif
#ifdef __arm__
	//dumpVstack(trace,thisStack);
#endif
	if (arg2 == 0) glsc = arg1 - 1;
	break;
      case jmpGT:
	arg1 = vPop(thisStack);
	arg2 = vPop(thisStack);
	arg3 = op2(bc,&glsc);
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
      case allocEventQ:
	arg1 = op1(bc,&glsc);
#ifdef TRACE
	fprintf(trace,"allocEventQ %i\n",arg1);
#endif
#ifdef EVENT
	mkAllocEvent(alloc_event,rTopElm(thisObj,1),thisObj,myCorigin(thisObj),false,currentDescNo,glsc,false);
#endif
	break;
      case rtnEvent:
	arg1 = op1(bc,&glsc);
	X = rPop(thisObj);
#ifdef TRACE
	fprintf(trace,"rtnEvent %i %s\n",arg1,nameOf(X));
#endif
#ifdef EVENT
	mkEvent(rtn_event,thisObj,X,myCorigin(X),false,currentDescNo,glsc);
#endif
	break; 
      case rtnEventQ:
	//printf("rtnEventQ-A\n");
        arg1 = op1(bc,&glsc);
#ifdef TRACE
	fprintf(trace,"rtnEventQ %i %s\n",arg1,nameOf(thisObj));
#endif
#ifdef EVENT
	mkEvent(rtn_event,rTopElm(thisObj,0),thisObj,myCorigin(thisObj),false,currentDescNo,glsc);
#endif        
	//printf("rtnEventQ-B\n");
        break;
      case doEventQ:
#ifdef TRACE
	fprintf(trace,"doEventQ %s\n",nameOf(thisObj));
#endif
#ifdef EVENT
	mkEvent(do_event,thisObj,X,myCorigin(X),false,currentDescNo,glsc);
#endif        
        break;
      case saveBETAworld:
#ifdef TRACE
	fprintf(trace,"saveBETAworld\n");
#endif
	X = rPop(thisStack); // should be assigned to eventprocessor.fields[1][]
	thisBlock->world = X;
	betaWorld = X;
	break;
      case saveStringOrigin:
#ifdef TRACE
	fprintf(trace,"saveStringOrigin");
#endif
	stringOrigin = thisObj;
	break;
      case doSuper:
	arg1 = op2(bc,&glsc);
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
	arg1 = op1(bc,&glsc);
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
      case innerP:
	arg1 = op1(bc,&glsc);
        X = rPop(thisStack);
        rPush(X,thisObj);
        thisObj = X;
#ifdef TRACE
	fprintf(trace,"innerP %i",arg1);
#endif
	arg2 = vdtTable(trace,X,arg1); // descNo
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


        break;
      case innera:
	arg1 = op1(bc,&glsc);
#ifdef TRACE
	fprintf(trace,"innera %i",arg1);
#endif
	arg2 = vdtTable(trace,thisObj,arg1); // descNo

	if (arg2 > 0) {
	  cSaveReturn(thisObj,currentDescNo,glsc);
	  currentDescNo = arg2;
	  bc = codeFromDescNo(arg2);
	  glsc = getEnterE(getDesc(arg2));
#ifdef TRACE
          fprintf(trace,"innera bc: %i glsc: %i",(int)bc,glsc);
#endif
	}
#ifdef TRACE
	fprintf(trace,"\n");
#endif
	break;
      case rtnInner:
#ifdef TRACE
	fprintf(trace,"returnInner");
#endif
	glsc = cRestoreReturn(thisObj);
	dscNo = cRestoreReturn(thisObj);
	currentDescNo = dscNo;
	bc = codeFromDescNo(dscNo);
#ifdef TRACE
        fprintf(trace," TO descNo: %i bc: %i glsc: %i\n",dscNo,(int)bc,glsc);
#endif
	break;
      case innerExit:
	arg1 = op1(bc,&glsc);
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
	arg1 = op1(bc,&glsc);
	arg2 = op1(bc,&glsc);
#ifdef TRACE
	fprintf(trace,"sendv %i",arg1);
#endif	
	refArgsTop = 0;
	if (arg2 > 0) {
	  for (i = 1; i <= arg2; i++) {   
	    refArgsTop = refArgsTop + 1;
	    refArgs[refArgsTop] = rPop(thisStack);
#ifdef TRACE	    
	    fprintf(trace,"\top ref:A:  %x\n",refArgs[refArgsTop]);
#endif
	  }
	} 
	thisBlock->origin = rPop(thisStack);
	// looks wrong with X below?
	if (X == 0) runTimeErrorX("Reference is none",thisObj,glsc);

	arg3 = vdtTable(trace,thisBlock->origin,arg1); // descNo
#ifdef TRACE
	StacksToOut(trace,thisObj,thisStack);//,thisBlock);
#endif
	saveContext();
	allocQObj(thisBlock,thisBlock->origin,arg3,false,0,0);
	restoreContext();
	if (arg2 > 0) {
	  for (i = 1; i <= arg2; i++) {
	    rPush(thisStack,refArgs[refArgsTop - i  + 1]);
#ifdef TRACE
	    fprintf(trace,"\top ref:B:  %x\n",refArgs[i]);
#endif
	  }
	}
#ifdef TRACE
	StacksToOut(trace,thisObj,thisStack);//,thisBlock);
#endif
	break;
      case sendx: 
#ifdef TRACE
	fprintf(trace,"send %i",op1(bc,&glsc));
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
	arg1 = op2(bc,&glsc);
	arg2 = vPop(thisStack);
#ifdef TRACE
	fprintf(trace,"jmpTrue %i\n",arg1);
#endif
	if (arg2 == 1) glsc = arg1 - 1;
	break;
      case pushText:
	arg1 = op1(bc,&glsc);
#ifdef TRACE
	fprintf(trace,"pushText %i ",arg1);
#endif
        if (isXbeta) {
	  saveContext();
	  QallocTextObject(thisBlock,arg1); 
	  restoreContext();
	}
	else { 
	  saveContext();
	  allocTextObj(thisBlock,arg1);
	  restoreContext();
	};
	break;
      case exeAlloc:
	arg1 = op2(bc,&glsc);
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
	fprintf(trace,"le %i <= %i\n",arg1,arg2);
#endif
	if (arg1 >=  arg2) { vPush(thisStack,1);} else vPush(thisStack,0);
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
	X = getR(X,2);
	Y = getR(Y,2);
#ifdef TRACE
	fprintf(trace,"seq %s %i %s %i\n",nameOf(X),arg1,nameOf(Y),arg2);
#endif
	vPush(thisStack,(arg1 == arg2) && getR(X,2) == getR(Y,2));
	//printf("vTop: %i\n",thisStack->vstack[thisStack->vtop]);
	break;
      case sne:
	X = rPop(thisStack);
	Y = rPop(thisStack);
#ifdef TRACE
	fprintf(trace,"sne %i != %i\n",(int)X,(int)Y);
#endif
	vPush(thisStack,(X->vfields[1] != Y->vfields[1]) || getR(X,2) != getR(Y,2));
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
	if ((arg1 == 1) || (arg2 == 1)) {vPush(thisStack,1);} else vPush(thisStack,0);
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
	arg1 = op2(bc,&glsc);
#ifdef TRACE
	fprintf(trace,"pushc2 %i\n",arg1);
#endif
	vPush(thisStack,arg1);
	break;
      case fplus:
	float2 = fPop(thisStack);
	float1 = fPop(thisStack);
	float3 = float1 + float2;
	//printf("fplus: %f %f %f\n",float1,float2, float3);
	fPush(thisStack,float3);
	break;
      case fminus:
	float2 = fPop(thisStack);
	float1 = fPop(thisStack);
	float3 = float1 - float2;
	//printf("fminus: %f %f %f\n",float1,float2, float3);
	fPush(thisStack,float3);	
	break;
      case fmult:
	float2 = fPop(thisStack);
	float1 = fPop(thisStack);
	float3 = float1 * float2;
	//printf("fmult: %f %f %f\n",float1,float2, float3);
	fPush(thisStack,float3);
	break;
      case fdiv:
	float2 = fPop(thisStack);
	float1 = fPop(thisStack);
	float3 = float1 / float2;
	//printf("fdiv: %f %f %f\n",float1,float2, float3);
	fPush(thisStack,float3);
	break;
      case feq:
	float2 = fPop(thisStack);
	float1 = fPop(thisStack);
	if (float1 == float2) vPush(thisStack,1); else vPush(thisStack,0);
	//printf("feq: %f %f %b\n",float1,float2,float1 == float2);
	break;
      case flt:
	float2 = fPop(thisStack);
	float1 = fPop(thisStack);
	if (float1 < float2) vPush(thisStack,1); else vPush(thisStack,0);
	//printf("flt: %f %f %b\n",float1,float2,float1 < float2);
	break;
      case fle:
	float2 = fPop(thisStack);
	float1 = fPop(thisStack);
	if (float1 <= float2) vPush(thisStack,1); else vPush(thisStack,0);
	//printf("fle: %f %f %b\n",float1,float2,float1 <= float2);
	break;
      case fgt:
	float2 = fPop(thisStack);
	float1 = fPop(thisStack);
	if (float1 > float2) vPush(thisStack,1); else vPush(thisStack,0);
	//printf("fgt: %f %f %b\n",float1,float2,float1 > float2);	
	 break;
      case fge:
	float2 = fPop(thisStack);
	float1 = fPop(thisStack);
	if (float1 >= float2) vPush(thisStack,1); else vPush(thisStack,0);
	//printf("fge: %f %f %b\n",float1,float2,float1 >= float2);	
	break;
      case fne:
	float2 = fPop(thisStack);
	float1 = fPop(thisStack);
	if (float1 != float2) vPush(thisStack,1); else vPush(thisStack,0);
	//printf("fne: %f %f %b\n",float1,float2,float1 != float2);	
	break; 
      case pushFloatConst: 
	arg1 = op4(bc,&glsc);
	arg2 = op4(bc,&glsc);
	//printf("pushFloatConst: %x %x\n",arg1,arg2); 
	vPush(thisStack,arg1);
	vPush(thisStack,arg2);
	break; 
      case fstoreg:
	off = op1(bc,&glsc); 
	X = rPop(thisStack);
	if (X == 0) runTimeErrorX("Reference is none",thisObj,glsc);
	arg2 = vPop(thisStack);
	arg1 = vPop(thisStack);
	//printf("fstoreg: %i %x %x\n",off,arg1,arg2);
	X->vfields[off + X->valOff] = arg1;
	X->vfields[off + 1 + X->valOff] = arg2;
	break;
      case fpushg:
	off = op1(bc,&glsc);
	X = rPop(thisStack);
	if (X == NULL) {
#ifdef __arm__
#else
	  printf("\n***pushg == NULL %i %i \n",off,(int)X);
#endif
	  runTimeErrorX("Reference is NONE",thisObj,glsc);
	}
	arg1 = X->vfields[off + X->valOff];
	arg2 = X->vfields[off + 1 + X->valOff];
	//printf("fpushg %i %x %x\n",off,arg1,arg2);
	vPush(thisStack,arg1);
	vPush(thisStack,arg2);
	break;
      case i2f:
	//printf("i2f\n");
	arg1 = vPop(thisStack);
	float1 = arg1;
	fPush(thisStack,float1);
	break;
      case f2i:
	//printf("f2i\n");
	float1 = fPop(thisStack);
	arg1 = float1;
	vPush(thisStack,arg1);
	break;
      case fovpushg:
	off = op1(bc,&glsc);
	arg3 = vPop(thisStack); //descInx of valObj	
	inx = vPop(thisStack);
	X = rPop(thisStack);
	arg1 = getV(X,off + inx - 1);
	vPush(thisStack,arg1);
	arg2 = getV(X,off + 1 + inx - 1);
	vPush(thisStack,arg2);
	//printf("**** fovpushg\n");
	stop;
	break;
      case fovstoreg:
	off = op1(bc,&glsc);
	arg2 = vPop(thisStack);
	arg1 = vPop(thisStack);
	X = rPop(thisStack);
	arg3 = vPop(thisStack); //descInx of valObj	
	inx = vPop(thisStack);
	//printf("**** fovstoreg %i\n",off);
	X->vfields[off + inx - 1] = arg1;
	X->vfields[off + 1 + inx - 1] = arg2;
	break;
      case allocIndexed:	
	arg1 = op2(bc,&glsc);
	arg2 = op1(bc,&glsc);
	arg3 = op1(bc,&glsc);
#ifdef TRACE
      fprintf(trace,"allocIndexed %i %i %i\n",arg1,arg2,arg3);
#endif
	thisBlock->origin = rPop(thisStack);
	dinx = vPop(thisStack);
	//isRindexed = vPop(thisStack);
	isRindexed = 0; // not used
	rangee = vPop(thisStack);
	if (isXbeta) {
	  saveContext();
	  QallocIndexed(thisBlock,thisBlock->origin,arg1,arg3,dinx,rangee,isRindexed);
	  restoreContext();
	}
	else {
	  saveContext();
	  allocIndexedObj(thisBlock,thisBlock->origin,arg1,arg2,dinx,rangee,isRindexed);
	  restoreContext();
	}
#ifdef TRACE
	dumpObj(trace,"QallocIndexed",thisBlock->callee);
#endif
	break;
      case mkStrucRef: 
	arg1 = vPop(thisStack);
	thisBlock->origin = rPop(thisStack);
#ifdef TRACE
	fprintf(trace,"mkStrucRef %i %s\n",arg1,nameOf(X));
#endif

	saveContext();
	allocStrucRefObj(thisBlock,thisBlock->origin,arg1,false);
	restoreContext();

	//X = thisStack->rstack[thisStack->rtop];
	//printf("mkStrucRef:Result: %s\n",nameOf(X));
	break;
      case mkObjStrucRef: 
	thisBlock->origin = rPop(thisStack);
	//Y = thisStack->rstack[thisStack->rtop];
	//printf("Result-top: %s\n",nameOf(Y));
#ifdef TRACE
	fprintf(trace,"\nmkObjStrucRef X: %s  X.origin: %s X.descNo: %i \n"
	      ,nameOf(X)
	      ,nameOf(myCorigin(X)),descNo(X->desc));
#endif

	saveContext();
	allocStrucRefObj(thisBlock,myCorigin(thisBlock->origin),descNo(thisBlock->origin->desc),false);
	restoreContext();

	//X = thisStack->rstack[thisStack->rtop];
	//printf("Result-top: %s\n",nameOf(X));
	//X = thisStack->rstack[thisStack->rtop - 1];
	//printf("Result-top-1: %s\n",nameOf(X));
	break;
      case mkVirtualStrucRef:
	arg1 = op1(bc,&glsc);
	thisBlock->origin = rPop(thisObj);
#ifdef TRACE
	fprintf(trace,"mkVirtualStrucRef %i %s\n",arg1,nameOf(X));
#endif

	saveContext();
	allocStrucRefObj(thisBlock,thisBlock->origin,arg1,true);
	restoreContext();

	break;
      case _allocFromStrucRefObj:
	thisBlock->origin = rPop(thisStack);
#ifdef TRACE
	fprintf(trace,"allocFromStrucRefObj %s\n",nameOf(X));
#endif
	saveContext();
	allocFromStrucRefObj(thisBlock,thisBlock->origin);
	restoreContext();

	break;
      case _break:
	arg1 = op1(bc,&glsc);
	arg2 = op2(bc,&glsc); 
	arg3 = op2(bc,&glsc); 
#ifdef TRACE
	fprintf(trace,"break %i %i\n",arg1,arg2);
#endif
	if (gcInProgress) {
	  //printf("Break: gcInProgress threadId: %i\n",thisBlock->threadId);
	  saveContext();
	  waitForGC(thisBlock);
	  restoreContext();
	  //printf("Break: gcInProgress:resumed threadId: %i thisObj: %x"
	  //	 ,thisBlock->threadId,thisObj);
	  //printf(" %s \n",nameOf(thisObj));
	  //doTrace = true;
	}
	X = thisObj;
	for (i = 0; i < arg1; i++) { 
#ifdef __arm__
#else
	  if (doTrace) printf("popCallStackA: %s \n",nameOf(X));
#endif
	  X = myCorigin(X);
#ifdef __arm__
#else
	  if (doTrace) printf("popCallStackB: %s \n",nameOf(X));
#endif
	}
	//fprintf(trace,"popCallStackB: %s \n",nameOf(X));
#ifdef __arm__
#else	
	if (doTrace) printf("popCallStackC: %s \n",nameOf(X));
#endif
	/* We need to test for none if the stack does not contain X
	 * Same  for traversing super
	 */
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
      findActualSuper:
	if (currentDescNo != arg3) {
	  glsc = cRestoreReturn(thisObj);
	  currentDescNo = cRestoreReturn(thisObj);
	  thisObj = rPop(thisObj);
	  goto findActualSuper;
	}
	thisStack = thisObj;
	bc = codeFromDescNo(currentDescNo);
	glsc = xlabs(currentDescNo,arg2) - 1; 
	//fprintf(trace,"popCallStackE %i %i\n",currentDescNo,glsc);
	break;
      case stop: 
#ifdef TRACE
	fprintf(trace,"stop - threadId: %i\n",threadId);
#endif
	running = false;
	threadStatus[thisBlock->threadId] = t_stopped;
	break;
      default:
#ifdef TRACE
	fprintf(trace,"Op: %i ",bc[glsc]);
#endif
#ifdef __arm__
#ifdef armtrace	
	putstr("**** Illegal byte code: lsc: ");
	puthex(glsc);
	putstr(" op: ");
	puthex(bc[glsc - 1]);
	putstr("\n");
#endif
#else
	printf("\n\n***Illegal byte code: glsc: %i, op: %i\n",glsc,bc[glsc - 1]);
	printf("thisObj: %x %s \n",(int)thisObj,nameOf(thisObj));
	printf("thisStack: %x %s \n",(int)thisStack,nameOf(thisStack));
#endif
	runTimeError("Illegal byte code");
	break;
      }
    };
#ifdef TRACE
  fclose(trace);
#endif
#ifdef __arm__
#else
  if (traceThreads){
    printf("\nStop: threadId: %i \n",threadId); 
    if (hasThreads) printf("HasThreads threadNo: %i\n",threadNo);
  }
#endif

  //if (threadNo > 0) {
  if (thisBlock->threadId == 0) {
#ifdef linux
    int j;
    for (j = 0; j < threadNo; j++) {
         pthread_join(pthreadArray[j],NULL);
	 printf("Join of: %i\n",j);
      }
#elif defined  __CYGWIN__
    int j;
    WaitForMultipleObjects(threadNo, hThreadArray, TRUE, INFINITE);

    for(j = 0; j < threadNo; j++)
      { if (traceThreads) printf("Close\n");
	CloseHandle(hThreadArray[j]);
      };
#endif
#ifdef __arm__
#else
    if (traceThreads) printf("After Wait\n");
#endif
  };
  if (threadId == 0) mkEvent(stop_event,0,0,0,0,0,0); 
  return 0;
}

void close_interpreter(){ 
}


