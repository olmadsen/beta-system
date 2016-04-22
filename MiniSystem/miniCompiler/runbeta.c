#include <stdio.h>
#include "interpreter_c.c"
void main(int argc, char *argv[])
{ if (sizeof(argv) < 2) {
    printf("Usage: runbeta file\n");
    return;
  }

  FILE* F = fopen(argv[1], "rb");
  if( fseek(F, 0, SEEK_END) ){
      fclose(F);
      printf("Cannot open file\n");
    }
  int size = ftell(F);
  printf("Runbeta: %i %s %i\n",argc,argv[1],(int)size);
  fseek(F, 0, SEEK_SET);  //same as rewind(f);

  unsigned char* bc = (char*)malloc(size * sizeof(char));
  if (bc == NULL) printf("Malloc error\n");
  int V = fread(bc, 1, size, F);
  if (V != size) printf("File read error: %i %i\n", (int)size,V);
  fclose(F); 
  
  bool isXB = 0;
  init_interpreter((ObjDesc)bc,isXB);
  bool first = true;
  getEvent(first); 
  // for (i=0; i <1000000; i++ ){
  //getEvent(first);
  //   first = false;
  //}
}
