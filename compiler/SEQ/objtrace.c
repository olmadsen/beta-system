#include <stdio.h>

void (*cCall)(long objAdr);
void (*cReturn)(long objAdr);

void inittrace(f,g)
     void (*f)(long objAdr);
     void (*g)(long objAdr);
{ printf("InitTrace\n"); 
  cCall = f;
  cReturn = g;
}

char doTrace = 0;

void trace(char on)
{ doTrace = on;
}

void traceCall(long objAdr)
{ 
   if (doTrace==1)
     { /* printf("Cadr: %i\n",objAdr); */
        doTrace = 0;   
        cCall(objAdr);
        doTrace = 1;
      }
}
void traceReturn(long objAdr)
{ if (doTrace==1)
  { /* printf("Creturn: %i\n",objAdr);  */
       doTrace = 0;   
       cReturn(objAdr);
       doTrace = 1;
     }
}
