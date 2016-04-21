#include <stdio.h>
#include "interpreter_c.c"
void main(int argc, char *argv[])
{ unsigned char* bc;
  int descInx = 1;
  bool isXB = 0;
  FILE *F;
  long size ;
  char *name = argv[1];
  int mainDescInx ;
  F = fopen(name, "rb");
  if( fseek(F, 0, SEEK_END) ){
      fclose(F);
      printf("Cannot open file\n");
    }
  size =ftell(F);
  printf("Runbeta: %i %s %i\n",argc,argv[1],(int)size);
  fseek(F, 0, SEEK_SET);  //same as rewind(f);
  printf("Rewind\n");
  bc = (char*)malloc(size * sizeof(char));
  if (bc == NULL) printf("Malloc error\n");
  int V;
  V = fread(bc, 1, size, F);
  if (V != size) printf("File read error: %i %i\n", (int)size,V);
  fclose(F); 
  
  int i = 0;
  /*for (i = 0; i < 25; i++){
    printf("%u: %u\n",i,bc[i]);
    }*/
  init_interpreter((ObjDesc)bc,1283,isXB);
  bool first = true;
  getEvent(first); 
  // for (i=0; i <1000000; i++ ){
  //getEvent(first);
  //   first = false;
  //}
}
