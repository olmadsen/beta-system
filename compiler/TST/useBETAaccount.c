/**********************************************************
 * 
 *   This is a C program that uese a COM account object
 *   implemented in BETA
 *   The object has operations:
 *   init, deposit and withdraw
 */


/* Interface definition for account COM class */
struct Account; /* forward declaration */
 
/* vtbl is the virtual dispatch table for Account objects 
 * The vtbl has entries in the form of function pointers
 */
struct vtbl
{ long (*init)(struct Account *this, char *name,long initialAmount);
  long (*deposit)(struct Account *this, long amount);
  long (*withdraw)(struct Account *this,long amount);
};

/* Account is the class */
struct Account
{ struct vtbl * proto; /* pointer to virtual dispatch table */
};


/* Called form BETA with COM account object */
void PutAccount(struct Account * R)
{ printf("Enter C PutAccount\n");
  /* not meaningfull printf("Balance%i\n",R->balance); */
  R->proto->deposit(R,111);
  R->proto->withdraw(R,222);
  printf("Leaving C PutAccount\n");
}
