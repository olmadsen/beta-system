#include <stdio.h>
#include <stdarg.h>

#define test 0

struct arg { long argType, a;} arg;

struct T
{ long rgvarg;
  struct arg *b;
  long c,d; 
} T;

struct T*  InitDispatch(long rgvarg) 
{ struct T *S;
  if (test) printf("InitDispatch:%i\n",rgvarg);
  S = (struct T*)malloc(sizeof(T));
  S->rgvarg = 0;
  S->b = (struct arg*)malloc(rgvarg*2*4);
  return S;
}
char *MkNameList(char *name) 
{ if (test) printf("MkNameList: %s\n",name);
  return name;
}
long textLen(char *name)
{ long i,len=0;
  for (i=0; name[i]>0; i++) len= len +1;
  if (test) printf("textLen %s %i\n", name,len);
  return len;
}

void copyText(char *name, char *dest, long len)
{ int i;
  if (test) printf("copytext %s\n",name);  
  for (i=0; i<len; i++) dest[i] = name[i];
}

int  CallInvoke() {}
int  AddDispatchInt8() {}
int  AddDispatchInt16() {}

struct T * AddDispatchInt32(struct T *S,long N) 
{ long next;
  next = S->rgvarg;
  if (test) printf("AddDispatchInt32, next=%i, arg=%i\n",next,N);

  S->b[next].argType   = 1; /* integer*/
  S->b[next].a = N;
  next = next +1;
  S->rgvarg = next;

  return S;
}
int  AddDispatchTxtCst() {}
int  AddDispatchRef() {}

int getType(struct arg *S,long N) 
{ if (test) 
     printf("getType: N=%i type=%i arg=%i\n",N,S[N-1].argType,S[N-1].a);
  return S[N-1].argType;
}
int getArg(struct arg *S,long N) 
{ if (test)  
     printf("getArg: N=%i type=%i arg=%i\n",N,S[N-1].argType,S[N-1].a);
  return S[N-1].a;
}
long MkResList()
{ if (test) printf("MkResList\n");
  return malloc(8);
}

long GetDispId(long *dispList)
{ if (test) printf("GetDispId: %i\n",dispList[0]);
  return dispList[0];
}
void PutDispId(long dispId, long *dispList)
{ if (test) printf("PutDispId: %i\n",dispId);
  dispList[0] = dispId;
}

struct T *MkArgList(long noOfArgs,...)
{ struct T *S;
  long i;
  va_list ap;
  
  if (test) printf("MkArgList: %i\n",noOfArgs);
  S = InitDispatch(noOfArgs);

  va_start(ap,noOfArgs);


  for (i=0; i<noOfArgs; i++)
    { long arg = va_arg(ap,long);
      long type = va_arg(ap,long);
      if (test) printf("Arg: %i, %i\n",arg,type);
      S= AddDispatchInt32(S,arg);
    };
  va_end(ap);
  return S;
}
