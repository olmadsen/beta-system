/* C definition of COM tst part for BETA 
*/

#ifdef nti
# define CALL _stdcall
#else
# define CALL
#endif

#define test 0

struct xCOMclass; /* forward */

/********* definition of class xCOMclass to be impoted by BETA */
/* vtbl is the virtual dispatch table for class xCOMclass
 * The vtbl has entries in the form of function pointers
 */
struct vtbl
{ char (CALL *f1)(struct xCOMclass *this, long n);
  char (CALL *f2)(struct xCOMclass *this, long a, long b, long c);
  char (CALL *f3)(struct xCOMclass *this, char *t, long ix);
  char *(CALL *f4)(struct xCOMclass *this, long ix, char *t);
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

char CALL f1(struct xCOMclass *this, long n)
{ char ch;
  if (test) printf("  xCOMclass::f1: %i\n",n);
  this->val = this->val + n;
  ch = '!';
  if (n == 1013)  ch = 'a';
  return ch;
}

char CALL f2(struct xCOMclass *this, long a, long b, long c)
     /* a = 10, b= 20, c = 2 */
{ char ch;
  if (test) printf(" xCOMclass::f2: %i,%i,%i\n",a,b,c);
  this->val = this->val + a + b + c;
  ch = '!';
  if (this->val == 1045) ch = 'b';
  return ch;
}

char CALL f3(struct xCOMclass *this, char *t, long ix)
{ char ch;
  if (test) printf(" xCOMclass::F3: %s %i\n",t,ix);
  this->str = t;
  ch = this->str[ix];
  return ch;
}

char *CALL f4(struct xCOMclass *this, long ix, char *t)
{ char *s;
  if (test) printf(" xCOMclass::F4: %s %i %c %c\n",t,ix,t[ix],this->str[ix]);
  s = "?!?";
  if (this->str[ix] == t[ix]) s = "def";
  return s;
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

/* Interface definition for bCOMclass COM class */
struct bCOMclass; /* forward declaration */
 
/* vtblX is the virtual dispatch table for bCOMclass objects 
 * The vtblX has entries in the form of function pointers
 */
struct vtblX
{ void (*g0)(struct bCOMclass *this);
  void (*g1)(struct bCOMclass *this, char ch);
  long (*g2)(struct bCOMclass *this, long a, long b, long c);
  long (*g3)(struct bCOMclass *this, char * s);
  char(*ch)(struct bCOMclass *this);
};

/* bCOMclass is the class */
struct bCOMclass
{ struct vtblX * proto; /* pointer to virtual dispatch table */
};


/* Called from BETA with COM bCOMclass object */
void PutBobj(struct bCOMclass * R)
{ char * S;
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
  if (test) printf("\n   Leaving C PutbCOMclass\n");
}
