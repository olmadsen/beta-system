// Interpreter main program for ARm on RaspberryPi
//#include <stdbool.h>
#include "interpreter_c.c"
#include "Hello_bc.c"
int main(int argc, char *argv[])
{ 

  //unsigned char* bc;  //= (unsigned char*)malloc(size * sizeof(char));

  //  int V = fread(bc, 1, size, F);

  init_interpreter((ObjDesc)BC,1); // isXB = 1 
  bool first = true;
  getEvent(first); 
  // for (i=0; i <1000000; i++ ){
  //getEvent(first);
  //   first = false;
  //}
  return 0;
}
