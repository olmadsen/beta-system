#include <stdio.h>
#include <stdarg.h>

#ifdef nti
# define STDCALL _stdcall
#else
# define STDCALL
#endif


#define test 0

typedef struct tagVARIANT { 
  short vt;
  short wr1,wr2,wr3;
  long  lVal;
  long  lVal2;
} VARIANT;

struct struct_tagDISPPARAMS
{ VARIANT *rgvarg;
  struct VARIANT *rgdispidNamedArgs;
  long cArgs, cNamedArgs;
} struct_tagDISPPARAMS;

struct struct_tagDISPPARAMS *InitDispatch(long cArgs) 
{ struct struct_tagDISPPARAMS *S;
  if (test) printf("InitDispatch:%i\n",cArgs);
  S = (struct struct_tagDISPPARAMS*)malloc(sizeof(struct_tagDISPPARAMS));
  S->cArgs = 0;
  S->rgvarg = (VARIANT*)malloc(cArgs*sizeof(VARIANT));
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

struct struct_tagDISPPARAMS *AddDispatchInt32(struct struct_tagDISPPARAMS *S,long arg, long argType) 
{ long next; 
  next = S->cArgs;
  if (test) 
     printf("AddDispatchInt32, next=%i, arg=%i, type=%i\n",next,arg,argType);

  S->rgvarg[next].vt = argType;
  S->rgvarg[next].lVal = arg;
  next = next + 1;
  S->cArgs = next;
  return S;
}


typedef struct COM { long dummy; }COM ;

int getType(VARIANT *S,long N) 
{ if (test) 
     printf("getType: N=%i type=%i arg=%i\n",N,S[N-1].vt,S[N-1].lVal);
  return S[N-1].vt;
}

int getArg(VARIANT *S,long N) 
{ if (test)  
     printf("getArg: N=%i type=%i arg=%i\n",N,S[N-1].vt,S[N-1].lVal);
  return S[N-1].lVal;
}

long * getRefArg(VARIANT *S, long N)
{ if (test)  
     printf("getArg: N=%i type=%i arg=%i\n",N,S[N-1].vt,S[N-1].lVal);
  return (long *)S[N-1].lVal;
}

char *getTextArg(VARIANT *S,long N) 
{ if (test)  
     printf("getArg: N=%i type=%i arg=%S\n",N,S[N-1].vt,(char *)S[N-1].lVal);
  return (char* )S[N-1].lVal;
}

struct COM *getCOMrefArg(VARIANT *S,long N) 
{ if (test)  
     printf("geCOMreftArg: N=%i type=%i arg=%i\n",N,S[N-1].vt,S[N-1].lVal);
  return (COM* )S[N-1].lVal;
}
long *MkResList()
{ if (test) printf("MkResList\n");
  return (long *)malloc(8);
}

long GetDispId(long *dispList)
{ if (test) printf("GetDispId: %i\n",dispList[0]);
  return dispList[0];
}
void PutDispId(long dispId, long *dispList)
{ if (test) printf("PutDispId: %i\n",dispId);
  dispList[0] = dispId;
}

struct struct_tagDISPPARAMS *MkArgList(long noOfArgs,...)
{ struct struct_tagDISPPARAMS *S;

  long *types = (long *)malloc(noOfArgs*4);

  long i;
  va_list ap;
  
  if (test) printf("MkArgList: %i\n",noOfArgs);
  S = InitDispatch(noOfArgs);

  
  va_start(ap,noOfArgs);

  for (i=0; i<noOfArgs; i++) types[i] = (long) va_arg(ap,long);

  for (i=0; i<noOfArgs; i++)
    { long arg = va_arg(ap,long);
      long type =types[i];
      if (test) printf("type= %i arg=",type);
      switch (types[i]) {
      case 3: // long
         if (test) printf("%i\n",arg);    
         S= AddDispatchInt32(S,arg,type);
	 break;
      case 4: // text
         if (test) printf("%s\n",arg);    
         S= AddDispatchInt32(S,arg,type);
	 break;
      default:
	printf("MkArgList: unknown argument type: %i\n",types[i]);
      };
    };
  va_end(ap);
  return S;
}

struct idispatch; // forward
struct vtbl
{ long (STDCALL *QI)(struct idispatch *this);
  long (STDCALL *AddRef)(struct idispatch *this);
  long (STDCALL *DeleteRef)(struct idispatch *this);
  long (STDCALL *GetIdsOfNames)(struct idispatch *this
				, char *names
				, long *resList);
  long (STDCALL *Invoke)(struct idispatch *this
			 ,long dispIdMember
			 ,struct struct_tagDISPPARAMS *pDispParams );
};

struct idispatch
{ struct vtbl * proto; /* pointer to virtual dispatch table */
};

long BETA_Invoke(struct idispatch *pdisp
		 ,char *pszName
		 ,long noOfArgs
		 ,...)
{ char * nameList;
  long * resList;
  long HR,dispid;
  struct struct_tagDISPPARAMS *argList;
  long *types = (long *)malloc(noOfArgs*4);
  va_list ap;
  long i;

  if (test) printf("BETA_Invoke: %s noOfArgs=%i\n",pszName,noOfArgs);

  argList = InitDispatch(noOfArgs);
  va_start(ap,noOfArgs);

  for (i=0; i<noOfArgs; i++) types[i] = (long) va_arg(ap,long);

  for (i=0; i<noOfArgs; i++)
    { long arg=0;
      long type =types[i];
      if (test) printf("type= %i arg=",type);
      switch (types[i]) {
      case 3: // long
	arg = va_arg(ap,long);
	if (test) printf("%i\n",arg);    
	argList = AddDispatchInt32(argList,arg,type);
	break;
      case 4: // text
	arg = (long) va_arg(ap,char *);
	if (test) printf("%s\n",arg);    
	argList = AddDispatchInt32(argList,arg,type);
	break;
      case 12: // COM ref
        arg = (long) va_arg(ap,long *);
	if (test) printf("%i\n",arg);    
        argList = AddDispatchInt32(argList,arg,type);
        break;
      case 14: // holder
        arg = (long) va_arg(ap,long *);
	if (test) printf("%i\n",arg);    
        argList = AddDispatchInt32(argList,arg,type);
        break;
      default:
	printf("MkArgList: unknown argument type: %i\n",types[i]);
      };
    };
  va_end(ap);
  nameList = MkNameList(pszName);

  resList = MkResList();


  HR = pdisp->proto->GetIdsOfNames(pdisp,nameList,resList);
  dispid = resList[0];

  pdisp->proto->Invoke(pdisp,dispid,argList);

  return 1;
}

