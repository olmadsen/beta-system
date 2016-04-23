#include <stdio.h>
#include "interpreter_c.c"
char * fixExtension(char* fn) {
  // fn = foo
  // fn = foo.
  // fn = foo..
  // fn = foo..bc
  int len = strlen(fn);
  printf("FN: %i %s\n",len,fn); 

  return fn;
}
void main(int argc, char *argv[])
{ printf("argc: %i\n",argc);
  if (argc < 2) {
    printf("Usage: runbeta file\n");
    return;
  }
  char * fileName = fixExtension(argv[1]);

  FILE* F = fopen(argv[1], "rb");
  if (F == NULL) {
    printf("No such file: '%s'\n",argv[1]);
    return;
  }
  if (fseek(F, 0, SEEK_END)) {
    fclose(F);
    printf("Cannot open file\n");
  }
  int size = ftell(F);
  printf("Runbeta: %i %s %i\n",argc,argv[1],(int)size);
  fseek(F, 0, SEEK_SET);  //same as rewind(f);

  unsigned char* bc = (char*)malloc(size * sizeof(char));
  if (bc == NULL) printf("Malloc error\n");
  int V = fread(bc, 1, size, F);
  fclose(F); 
  if (V != size){
    printf("File read error: %i %i\n", (int)size,V);
    return;
  }
  
  bool isXB = 0;
  init_interpreter((ObjDesc)bc,isXB);
  bool first = true;
  getEvent(first); 
  // for (i=0; i <1000000; i++ ){
  //getEvent(first);
  //   first = false;
  //}
}
