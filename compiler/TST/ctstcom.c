/* C definition of COM tst part for BETA */ 

#ifdef nti
# define STDCALL _stdcall
#else
# define STDCALL
#endif

#define test 0
struct xCOMclass; /* forward */

#include <stdio.h>
#include <stdlib.h>

struct data4a { long x; };
struct data4b { short x; short y; };
struct data8a { long x; long y; };
struct data8b { long x;  short y; short z; };
struct data12a { long x; long y; long z; };
struct data12b { long x; long y;  short z; short z2; };

struct data4a STDCALL f_data4a(struct xCOMclass *this)
{
  struct data4a d = { 7 };
  return d;
}
struct data4b STDCALL f_data4b(struct xCOMclass *this)
{
  struct data4b d = { 7, 9 };
  return d;
}
struct data8a STDCALL f_data8a(struct xCOMclass *this)
{
  struct data8a d = { 11, 13 };
  return d;
}
struct data8b STDCALL f_data8b(struct xCOMclass *this)
{
  struct data8b d = { 14, 15, 16 };
  return d;
}
struct data12a STDCALL f_data12a(struct xCOMclass *this)
{
  struct data12a d = { 11, 13, 14 };
  return d;
}
struct data12b STDCALL f_data12b(struct xCOMclass *this)
{
  struct data12b d = { 14, 15, 16, 17 };
  return d;
}

void teststructreturn(struct xCOMclass *this)
{
  struct data4a d4a;
  struct data4b d4b;
  struct data8a d8a;
  struct data8b d8b;
  struct data12a d12a;
  struct data12b d12b;

  d4a = f_data4a(this);
  d4b = f_data4b(this);
  d8a = f_data8a(this);
  d8b = f_data8b(this);
  d12a = f_data12a(this);
  d12b = f_data12b(this);
}

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
  char (STDCALL *f9)(struct xCOMclass *this, long a, struct myData S, long b);

  char (STDCALL *f10)(struct xCOMclass *this, long a, struct myData *S);
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
  if (test) printf("  xCOMclass::f1: %i\n",(int)n);
  this->val = this->val + n;
  ch = '!';           
  if (n == 1013)  ch = 'a';
  return ch;
}

char STDCALL f2(struct xCOMclass *this, long a, long b, long c)
     /* a = 10, b= 20, c = 2 */
{ char ch;
  if (test) printf(" xCOMclass::f2: %i,%i,%i\n",(int)a,(int)b,(int)c);
  this->val = this->val + a + b + c;
  ch = '!';
  if (this->val == 1045) ch = 'b';
  return ch;
}

char STDCALL f3(struct xCOMclass *this, char *t, long ix)
{ char ch;
  if (test) printf(" xCOMclass::F3: %s %i\n",t,(int)ix);
  this->str = t;
  ch = this->str[ix];
  return ch;
}

char *STDCALL f4(struct xCOMclass *this, long ix, char *t)
{ char *s;
  if (test) printf(" xCOMclass::F4: %s %i %c %c\n",t,(int)ix,(int)t[ix],(int)this->str[ix]);
  s = "?!?";
  if (this->str[ix] == t[ix]) s = "def";
  return s;
}

char STDCALL f5(struct xCOMclass *this, struct myData *S)
{ char c;
  if (test) printf(" xCOMclass::F5: %i %i %c \n",(int)S->x,(int)S->s,(int)S->c);
  c = '!';
  if (S->x == 1199) {c = 'q';};
  return c;
}

char STDCALL f6(struct xCOMclass *this, struct myData S)
{ char ch = '!';
  if (test) printf(" xCOMclass::F6: %i %i %c \n",(int)S.x,(int)S.s,(int)S.c);
  if ((S.x == 6060) & (S.s == 7070)) ch = S.c;
  return ch;
}    

struct myData STDCALL f7(struct xCOMclass *this, long a, long b, long c)
{ struct myData mD;
  if (test) printf(" xCOMclass::F7: %d, %d, %d \n",(int)a,(int)b,(int)c);
  mD.x = a+1234;
  mD.s = 321;
  mD.c = 'u';
  return mD;
}

struct myBigData STDCALL f8(struct xCOMclass *this, long a, long b, long c)
{ struct myBigData mD;
  if (test) printf(" xCOMclass::F8: %d, %d, %d \n",(int)a,(int)b,(int)c);
  mD.x = a+1234;
  mD.y = 0x87654321;
  mD.s = 321;
  mD.c = 't';
  return mD;
}

char STDCALL f9(struct xCOMclass *this, long a, struct myData S, long b)
{
 if (test) printf(" xCOMclass::F9: %d, %d, %d \n",(int)a,(int)S.x,(int)b);
 if ((a == S.x) & (b == S.s)) {return S.c;}
 else {return '?';};
}

char STDCALL f10(struct xCOMclass *this, long a, struct myData *S)
{
 if (test) printf(" xCOMclass::F10: %d, %d\n",(int)a,(int)S->x);
 if (a == S->x) {return S->c;}
 else {return '?';};
}

/* This is a virtual dispatch table instance, 
 * that may be shared by all xCOMclass objects 
 */
static struct vtbl theVTBL;

/* GetxCOMclass creates a new xCOMclass and returns a pointer to it */
struct xCOMclass * GetXobj()
{ struct xCOMclass * R;
  /* initialize dispatch table */  
  if (test) printf(" GetxCOMclass: &f1 = %x,f1=%x\n",(int)&f1,(int)f1);
  theVTBL.f1 = &f1;
  theVTBL.f2 = &f2;
  theVTBL.f3 = &f3;
  theVTBL.f4 = &f4;
  theVTBL.f5 = &f5;
  theVTBL.f6 = &f6;
  theVTBL.f7 = &f7;
  theVTBL.f8 = &f8;
  theVTBL.f9 = &f9;
  theVTBL.f10 = &f10;
  /* Allocate xCOMclass object */
  R = (struct xCOMclass *)malloc(sizeof(struct xCOMclass));
  R->proto = &theVTBL;
  R->val = 0;
  R->balance = 0;
  if (test) printf(" GetxCOMclass: &f1 = %x,f1=%x\n",(int)&f1,(int)f1);
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
  long (STDCALL *g7)(struct bCOMclass *this);
  char (STDCALL *ch)(struct bCOMclass *this);
};

/* bCOMclass is the class */
struct bCOMclass
{ struct vtblX * proto; /* pointer to virtual dispatch table */
};



/* Called from BETA with COM bCOMclass object */
void PutBobj(struct bCOMclass * R)
{ char * S;
  foo q = {999,77,-88,1010,'*'}; /* if 88 is -88 then it dont work*/
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
  /* the following call overwrites q.w on sun4s */
  R->proto->g4(R,111,112,113,114,115,116,117,118);

  if (test) printf("\nPrint af q.w = %c,%i\n",(int)q.w,(int)q.w);
  q.w ='*'; /* on sun4s foo q = {...,'*'} don't work! */
  if (test) printf("\nPrint af q.w = %c,%i\n",(int)q.w,(int)q.w);
  R->proto->g5(R,q);
  R->proto->g6(R,R,'%');
  R->proto->g7(R);
  if (test) printf("\n   Leaving C PutbCOMclass\n");
}


void olsen(struct xCOMclass * R)
{ struct myData mD;
  struct myBigData mDB;
  mD = f7(R,11,12,'*');
  printf(" xCOMclass::F6: %i %i %i %c \n",(int)mD.x,(int)mD.s,(int)mD.c,(int)mDB.c);
  mDB = f8(R,11,12,'*');
  printf(" xCOMclass::F6: %i %i %i %c \n",(int)mDB.x,(int)mDB.y,(int)mDB.s,(int)mDB.c);
}

struct data1 { long x; };
struct data2 { long x; long y; };
struct data3 { long x; long y; long z; };

static void setData1(struct data1 *d1)
{ d1->x = 101;
}
static void setData2(struct data2 *d2)
{ d2->x = 201;
  d2->y = 202;
}
static void setData3(struct data3 *d3)
{ d3->x = 301;
  d3->y = 302;
  d3->z = 303;
}

void hansen()
{ struct data1 d1;
  struct data2 d2;
  struct data3 d3;
 
  setData1(&d1);
  printf("d1:%i\n",(int)d1.x);
  setData2(&d2);
  printf("d2:%i,%i\n",(int)d2.x,(int)d2.y);
  setData3(&d3);
  printf("d3:%i,%i,%i\n",(int)d3.x,(int)d3.y,(int)d3.z);
}

/*
void main()
{struct xCOMclass * R;
 char (STDCALL *f)(struct xCOMclass *this, long n);
 f = &f1;
 f(R,7);
 f1(R,8);
}
*/
