/*******************************************************************
 *   This is a C program that uses a COM object implemented in BETA.
 *   The COM object is called MiniThought and is of type unknown.
 *   It supports two interfaces: calculator and displayer.
 *   calculator supports add and sub;
 *   displayer supports displayEnglish and displayDaish
 */

/************************ MiniThought interface ****************/
struct MiniThought; /* forward */

struct vtbl /* virtual dispatch table for MiniThought */
{ long (*queryIf)(struct MiniThought *this,long IfId);
  long (*addRef)(struct MiniThought *this);
  long (*deleteRef)(struct MiniThought *this);
};

struct MiniThought
{ struct vtbl * proto; /* pointer to virtual dispatch table */
};

/************************ calculator inteface ******************/
struct calculator; /* forward declaration */
 
struct vtbl2 /* virtual dispatch table for calculator */
{ struct calculator *(*queryIf)(struct calculator *this,long IfId);
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
{ struct displayer *(*queryIf)(struct displayer *this,long IfId);
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
  printf("Enter C PutMiniThought\n");
  S = (struct calculator*)R->proto->queryIf(R,1); /* get calculator IF */
  S->proto->add(S,100);
  S->proto->sub(S,31);
  D = (struct displayer*)R->proto->queryIf(R,2);  /* get displayer IF */
  D->proto->displayEnglish(D);
  S->proto->add(S,50);
  D->proto->displayDanish(D);
  printf("Leaving C PutMiniThought\n");
}
