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
     printf("getTextArg: N=%i type=%i arg=%s\n",N,S[N-1].vt,(char *)S[N-1].lVal);
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

struct idispatch; // forward

struct vtbl
{ long (STDCALL *QI)(struct idispatch *this);
  long (STDCALL *AddRef)(struct idispatch *this);
  long (STDCALL *DeleteRef)(struct idispatch *this);
  long (STDCALL *GTIC)();
  long (STDCALL *GTI)();
  /* GetIdsOfNames does NOT have the correct parameters
   * corresponding to the official IDISPATCH interface */
  long (STDCALL *GetIdsOfNames)(struct idispatch *this
				, long *riid
				, char *rgzNames
				, char *cNames
				, long lcid
				, long *rgDispId);
  long (STDCALL *Invoke)(struct idispatch *this
			 ,long dispIdMember
			 , long riid
			 , long _lcid
			 , long wFlags
			 , struct struct_tagDISPPARAMS *pDispParams 
			 , VARIANT *pVarResult
			 , VARIANT *pExcepInfo
			 , long *puArgErr);
};

struct idispatch
{ struct vtbl * proto; /* pointer to virtual dispatch table */
};

long BETA_Invoke(struct idispatch *pdisp
		 ,char *pszName
		 ,char *pszFmt
		 ,...)
{ char * nameList;
  long * resList; 
  long HR,dispid;
  struct struct_tagDISPPARAMS *argList;
  va_list ap;
  long noOfArgs=0,i,j=0;

  if (test) 
     printf("BETA_Invoke: %s noOfArgs=%i types=%s\n",pszName,noOfArgs,pszFmt);

  for (j=0 ;pszFmt[j] != 0;) {
    if (pszFmt[j] == '&') j = j + 1;
    j= j + 1;
    noOfArgs=noOfArgs + 1;
  };
  j = 0;
  if (test) 
    printf("BETA_Invoke: %s noOfArgs=%i types=%s\n",pszName,noOfArgs,pszFmt);

  argList = InitDispatch(noOfArgs);
  va_start(ap,noOfArgs);

  //for (i=0; i<noOfArgs; i++) types[i] = (long) va_arg(ap,long);

  for (i=0; i<noOfArgs; i++)  
    { long arg=0;
      if (test) printf("type=%c arg=",pszFmt[j]);
      switch (pszFmt[j]) {
      case 'I': // long
	arg = va_arg(ap,long);
	if (test) printf("%i\n",arg);    
	argList = AddDispatchInt32(argList,arg,3);
	break;
      case 'x': // text
	arg = (long) va_arg(ap,char *);
	if (test) printf("%s\n",arg);    
	argList = AddDispatchInt32(argList,arg,4);
	break;
      case 'U': // COM ref
        arg = (long) va_arg(ap,long *);
	if (test) printf("%i\n",arg);    
        argList = AddDispatchInt32(argList,arg,12);
        break;
      case '&': // holder
        { j = j+1;
          switch (pszFmt[j]) {   
	  case 'I':
	    arg = (long) va_arg(ap,long *);
	    if (test) printf("%i\n",arg);    
	    argList = AddDispatchInt32(argList,arg,14);
	    break;
	  default:
	  };
	  break;
	}
      default:
	printf("MkArgList: unknown argument type: %c\n",pszFmt[j]);
        goto L;
      };
      j = j + 1;      
    };
 L:
  va_end(ap);
  nameList = MkNameList(pszName);

  resList = MkResList();


  HR = pdisp->proto->GetIdsOfNames(pdisp,0,nameList,0,0,resList);
  dispid = resList[0];

  pdisp->proto->Invoke(pdisp,dispid,0,0,0,argList,NULL,NULL,NULL);

  return 1;
}

