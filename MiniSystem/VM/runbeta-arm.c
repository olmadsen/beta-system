// Interpreter main program for ARm on RaspberryPi
//#include <stdbool.h>
#include "interpreter_c.c"
#include "arm/blink.c"
#include "Hello_bc.c"
//int main(int argc, char *argv[])
void kernel_main( unsigned int r0, unsigned int r1, unsigned int atags )
{ //unsigned char* bc;  //= (unsigned char*)malloc(size * sizeof(char));
  //  int V = fread(bc, 1, size, F);
  //init_interpreter((ObjDesc)BC,0); 

  run_interpreter(1); // isXB = 1 
  bool first = true;
  getEvent(first); 
  while (1) ;
}

void exit(int no){
  while (1) ;
}
