#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

typedef unsigned long DWORD;
typedef void *LPVOID;
typedef void *PVOID;
typedef PVOID HANDLE;
#define TRUE 1
#define INFINITE 0xFFFFFFFF // not the correct value 
// and in any case the threading routines must be changed to Posix?
#define WAIT_OBJECT_0 0x00000000L

typedef struct ObjDesc { } ObjDesc;
typedef struct template { } template;

typedef struct Event {
  int type;
  template *caller,*thisObj,*org;
  int isObj;
  int descNo;
  int bcPos;
} Event;

bool getIsObj(template *obj) {}

int getV(template *obj,int inx){ }

template *getR(template *obj,int inx){ };

void vPush(template *thisStack,int V){ }

void rPush(template *stack,template *R){ }

int vPop(template *thisStack){ }

template *rPop(template *stack){ }

void cSaveReturn(template *obj,int descNo, int lsc){ }

int cMyLscTop(template *obj) { }

int topOfLsc(template *obj,int inx ){ }

int cRestoreReturn(template * obj){ }

char * nameOf(template *obj){ }

template *myCorigin(template *obj){ }

int descNoOf(template * obj){ }

Event *init_interpreter(ObjDesc descs_a, int mainDescNo) { }
void close_interpreter(){ }

Event *getEvent(bool first){ }

DWORD WaitForSingleObject(HANDLE hHandle,  DWORD dwMilliseconds);
