#include <stdbool.h>
#include "interpreter_c.c"
//#include "arm/led.c"
#include "qbeta_image.c"
//int main(int argc, char *argv[])
int main(int argc, char *argv[])
{
  set_descs(BC);
  run_interpreter(1); // isXB = 1 
  getEvent(true);  
}
 
