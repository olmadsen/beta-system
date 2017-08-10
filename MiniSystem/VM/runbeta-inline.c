#include <stdbool.h>
#include "interpreter_c.c"
#include "Hello_bc.c"
//int main(int argc, char *argv[])
int main(int argc, char *argv[])
{ printf("runbeta-X\n");
  set_descs(BC);
  run_interpreter(1); // isXB = 1 
  getEvent(true);  
}
