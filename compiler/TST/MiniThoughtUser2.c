/*******************************************************************
 *   This is a C program that uses a COM object implemented in BETA.
 *   The COM object is called MiniThought and is of type unknown.
 *   It supports two interfaces: calculator and displayer.
 *   calculator supports add and sub;
 *   displayer supports displayEnglish and displayDaish
 */

struct IID 
{ long id1,id2,id3,id4;
};

/************************ MiniThought interface ****************/
struct MiniThought; /* forward */

struct vtbl /* virtual dispatch table for MiniThought */
{ long (*queryIf)(struct MiniThought *this, struct IID *iid, void **ppv);
  long (*addRef)(struct MiniThought *this);
  long (*deleteRef)(struct MiniThought *this);
};

struct MiniThought
{ struct vtbl * proto; /* pointer to virtual dispatch table */
};

/************************ calculator inteface ******************/
struct calculator; /* forward declaration */
 
struct vtbl2 /* virtual dispatch table for calculator */
{ long (*queryIf)(struct calculator *this, struct IID *iid, void **ppv);
  long (*addRef)(struct calculator *this);
  long (*deleteRef)(struct calculator *this);
  long (*add)(struct calculator *this,long n);
  long (*sub)(struct calculator *this,long n);
  long (*display)(struct calculator *this);
};

struct calculator
{ struct vtbl2 * proto; /* pointer to virtual dispatch table */
};

/************************ displayer interface *****************/
struct displayer ;
struct vtbl3
{ struct displayer *(*queryIf)(struct displayer *this, struct IID *iid, void **ppv);
  long (*addRef)(struct displayer *this);
  long (*deleteRef)(struct displayer *this);
  long (*displayEnglish)(struct displayer *this);
  long (*displayDanish)(struct displayer *this);
};
struct displayer
{struct vtbl3 * proto; /* pointer to virtual dispatch table */
};

/* Called from BETA with COM account object */
void PutMiniThought(struct MiniThought * R)
{ struct calculator *S;
  struct displayer *D;
  struct IID *iid;
  long H;
  printf("Enter C PutMiniThought\n");

  iid = (struct IID*)malloc(sizeof(struct IID));
  iid->id1 = 1;
  iid->id2 = 2;
  iid->id3 = 3;
  iid->id4 = 4;
  H = R->proto->queryIf(R,iid,(void**)&S); /* get calculator IF */

  S->proto->add(S,100);
  S->proto->sub(S,31);

  iid->id1 = 2;
  H = R->proto->queryIf(R,iid,(void**)&D);  /* get displayer IF */
  D->proto->displayEnglish(D);
  S->proto->add(S,50);
  D->proto->displayDanish(D);
  printf("Leaving C PutMiniThought\n");
}
