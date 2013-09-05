#include <windows.h>
#include <stdio.h>


static HANDLE CS() { HANDLE H; H = CreateSemaphore(NULL,1,1,NULL); return H;}

void fool() {
  printf("Hello from fool");
   
  __asm__( "movl $10, %eax;"
	   "movl $20, %ebx;"
	   "addl %ebx, %eax;"
	    ); 
}
  
int V = 0;
void callC(int X) {
  V = V + X;
  printf("C is here: %i\n",V);
}

;
//void main() { fool();}
  

