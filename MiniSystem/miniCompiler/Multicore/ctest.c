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
  
//void main() { fool();}
  

