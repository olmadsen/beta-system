#include <stdio.h>
#include "interpreter_c.c"
void main(int argc, char *argv[])
{ ObjDesc bc = 0;
  int descInx = 1;
  bool isXB = 0;
  FILE *F;
  long size ;
  char *name = argv[1];
  F = fopen(name, "rb");
  if( fseek(F, 0, SEEK_END) ){
      fclose(F);
      printf("Cannot open file\n");
    }
  size =ftell(F);
  printf("Runbeta: %i %s %i\n",argc,argv[1],(int)size);
  fseek(F, 0, SEEK_SET);  //same as rewind(f);
  printf("Rewind\n");
  bc = malloc(size);
  fread(bc, size, 1, F);
  fclose(F); 

  init_interpreter(bc,1283,isXB);
  bool first = true;
  getEvent(first); 
  // for (i=0; i <1000000; i++ ){
  //getEvent(first);
  //   first = false;
  //}
}
