/* C definition of COM tst part for BETA */ 

#ifdef nti
# define STDCALL _stdcall
#else
# define STDCALL
#endif

#define test 1

struct myData{
    long x;
    short s;
    char c;  
};

struct myBigData{
    long x;
    long y;
    short s;
    char c;  
};

struct xCOMclass; /* forward */

/********* definition of class xCOMclass to be impoted by BETA */
/* vtbl is the virtual dispatch table for class xCOMclass
 * The vtbl has entries in the form of function pointers
 */
struct vtbl
{ char (STDCALL *f1)(struct xCOMclass *this, long n);
  char (STDCALL *f2)(struct xCOMclass *this, long a, long b, long c);
  char (STDCALL *f3)(struct xCOMclass *this, char *t, long ix);
  char *(STDCALL *f4)(struct xCOMclass *this, long ix, char *t);
  char (STDCALL *f5)(struct xCOMclass *this, struct myData *S);
  char (STDCALL *f6)(struct xCOMclass *this, struct myData S);
  struct myData (STDCALL *f7)(struct xCOMclass *this, long a, long b, long c);
  struct myBigData (STDCALL *f8)(struct xCOMclass *this, long a, long b, long c);
};

/* xCOMclass is the class */
struct xCOMclass
{ struct vtbl * proto; /* pointer to virtual dispatch table */
  long val; 
  long balance;      
  char * str;
};
 
/* Operations on xCOMclass-objects;
 * the first argument is always the this-pointer 
 * to the xCOMclass object;
 */

char STDCALL f1(struct xCOMclass *this, long n) 
{ char ch;
  if (test) printf("  xCOMclass::f1: %i\n",n);
  this->val = this->val + n;
  ch = '!';           
  if (n == 1013)  ch = 'a';
  return ch;
}

char STDCALL f2(struct xCOMclass *this, long a, long b, long c)
     /* a = 10, b= 20, c = 2 */
{ char ch;
  if (test) printf(" xCOMclass::f2: %i,%i,%i\n",a,b,c);
  this->val = this->val + a + b + c;
  ch = '!';
  if (this->val == 1045) ch = 'b';
  return ch;
}

char STDCALL f3(struct xCOMclass *this, char *t, long ix)
{ char ch;
  if (test) printf(" xCOMclass::F3: %s %i\n",t,ix);
  this->str = t;
  ch = this->str[ix];
  return ch;
}

char *STDCALL f4(struct xCOMclass *this, long ix, char *t)
{ char *s;
  if (test) printf(" xCOMclass::F4: %s %i %c %c\n",t,ix,t[ix],this->str[ix]);
  s = "?!?";
  if (this->str[ix] == t[ix]) s = "def";
  return s;
}

char STDCALL f5(struct xCOMclass *this, struct myData *S)
{ char c;
  if (test) printf(" xCOMclass::F5: %i %i %c \n",S->x,S->s,S->c);
  c = '!';
  if (S->x == 1199) {c = 'q';};
  return c;
}

char STDCALL f6(struct xCOMclass *this, struct myData S)
{ char ch = '!';
  if (test) printf(" xCOMclass::F6: %i %i %c \n",S.x,S.s,S.c);
  if ((S.x == 6060) & (S.s == 7070)) ch = S.c;
  return ch;
}    

struct myData STDCALL f7(struct xCOMclass *this, long a, long b, long c)
{ struct myData mD;
  if (test) printf(" xCOMclass::F7: %d, %d, %d \n",a,b,c);
  mD.x = 1234;
  mD.s = 321;
  mD.c = '=';
  return mD;
}

struct myBigData STDCALL f8(struct xCOMclass *this, long a, long b, long c)
{ struct myBigData mD;
  if (test) printf(" xCOMclass::F8: %d, %d, %d \n",a,b,c);
  mD.x = 1234;
  mD.y = 0x87654321;
  mD.s = 321;
  mD.c = '=';
  return mD;
}


/* This is a virtual dispatch table instance, 
 * that may be shared by all xCOMclass objects 
 */
static struct vtbl theVTBL;

/* GetxCOMclass creates a new xCOMclass and returns a pointer to it */
struct xCOMclass * GetXobj()
{ struct xCOMclass * R;
  /* initialize dispatch table */
  theVTBL.f1 = &f1;
  theVTBL.f2 = &f2;
  theVTBL.f3 = &f3;
  theVTBL.f4 = &f4;
  theVTBL.f5 = &f5;
  theVTBL.f6 = &f6;
  theVTBL.f7 = &f7;
  theVTBL.f8 = &f8;
  /* Allocate xCOMclass object */
  R = (struct xCOMclass *)malloc(sizeof(struct xCOMclass));
  R->proto = &theVTBL;
  R->val = 0;
  R->balance = 0;
  return R; 
}

/*************************************************************
 *   C declarations for using COM object implemented in BETA
 **************************************************************/

/* argument type of g5 below  */
typedef struct tag {
  int x;
  short y;
  short z;
  long v;
  char w;
} foo;

/* Interface definition for bCOMclass COM class */
struct bCOMclass; /* forward declaration */
 
/* vtblX is the virtual dispatch table for bCOMclass objects 
 * The vtblX has entries in the form of function pointers
 */
struct vtblX
{ void (STDCALL *g0)(struct bCOMclass *this);
  void (STDCALL *g1)(struct bCOMclass *this, char ch);
  long (STDCALL *g2)(struct bCOMclass *this, long a, long b, long c);
  long (STDCALL *g3)(struct bCOMclass *this, char * s);
  long (STDCALL *g4)(struct bCOMclass *this, 
		     long a, long b, long c, long d, long e,
		     long f, long g, long h);
  long (STDCALL *g5)(struct bCOMclass *this, foo V);
  long (STDCALL *g6)(struct bCOMclass *this, struct bCOMclass *S, char ch);
  char (STDCALL *ch)(struct bCOMclass *this);
};

/* bCOMclass is the class */
struct bCOMclass
{ struct vtblX * proto; /* pointer to virtual dispatch table */
};



/* Called from BETA with COM bCOMclass object */
void PutBobj(struct bCOMclass * R)
{ char * S;
  foo q = {999,77,-88,1010,'*'}; // if 88 is -88 then it don't work
  if (test) printf("\n   Enter C PutBobj\n");
  R->proto->g0(R);
  R->proto->g1(R,R->proto->ch(R));
  R->proto->g2(R,100,10,1);
  S = (char *) malloc(3);
  S[0] = R->proto->ch(R);
  S[1] = R->proto->ch(R);
  S[2] = 0;
  if (test) printf("\n   s: %s\n",S);
  R->proto->g3(R,S);
  R->proto->g4(R,111,112,113,114,115,116,117,118);
  R->proto->g5(R,q);
  R->proto->g6(R,R,'%');
  if (test) printf("\n   Leaving C PutbCOMclass\n");
}


void olsen(struct xCOMclass * R)
{ struct myData mD;
  struct myBigData mDB;
  mD = f7(R,11,12,'*');
  printf(" xCOMclass::F6: %i %i %i %c \n",mD.x,mD.s,mD.c);
  mDB = f8(R,11,12,'*');
  printf(" xCOMclass::F6: %i %i %i %c \n",mDB.x,mDB.y,mDB.s,mDB.c);
}
