/**********************************************************
 * 
 *   This is a C program that builds a simplified
 *   Microsoft COM-like class as described in "Inside OLE"
 *
 *   The class is an account with operations 
 *   init, deposit and withdraw
 */
#ifdef nti
# define CALL _stdcall
#else
# define CALL
#endif
/* FIXME: The functions below does not actually return
 * HRESULTs, but e.g balance/amount.
 */
#define HRESULT unsigned long

struct Account; /* forward declaration */
 
/* vtbl is the virtual dispatch table for Account objects 
 * The vtbl has entries in the form of function pointers
 */
struct vtbl
{ HRESULT (CALL *init)(struct Account *this, char *name,long initialAmount); 
  HRESULT (CALL *deposit)(struct Account *this, long amount);
  HRESULT (CALL *withdraw)(struct Account *this,long amount);
};

/* Account is the class */
struct Account
{ struct vtbl * proto; /* pointer to virtual dispatch table */
  long balance;       
  char * name;
};

/* Operations on Account-objects;
 * the first argument is always the this-pointer 
 * to the Account object;
 */

HRESULT CALL init(struct Account *this, char* name, long initialAmount)
{ printf("Initializing account for %s\n",name);
  this->name = name;
  this->balance = initialAmount;
  return this->balance;
}

HRESULT CALL deposit(struct Account *this, long amount)
{ printf("Deposit %i\n",amount);
  this->balance = this->balance + amount;
  return this->balance;
}

HRESULT CALL withdraw(struct Account *this, long amount)
{ printf("Withdraw %i\n",amount);
  this->balance = this->balance - amount;
  return this->balance;
}

/* This is a virtual dispatch table instance, 
 * that may be shared by all Account objects 
 */
static struct vtbl theVTBL;

/* GetAccount creates a new Account and returns a pointer to it */
struct Account * GetAccount()
{ struct Account * R;
  /* initialize dispatch table */
  theVTBL.init = &init;
  theVTBL.deposit = &deposit;
  theVTBL.withdraw = &withdraw;
  /* Allocate Account object */
  R = (struct Account *)malloc(sizeof(struct Account));
  R->proto = &theVTBL;
  R->balance = 0;
  return R; 
}
