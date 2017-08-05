// One or mor of the following files should not be included 
// before winsock2 is inclued in interpreter_c.c
//#include <stdio.h>
//#include <windows.h>
//#include <stdbool.h>
//#include <stdlib.h>
#include "interpreter_c.c"
char * fixExtension(char* fn) {
  // fn = foo
  // fn = foo.
  // fn = foo..
  // fn = foo..bc
  char* fnx; 
  int len = strlen(fn);
  int pos = 0; 
  int i;
  if (len > 4) {
    if ((fn[len - 4] == '.') 
	&& (fn[len - 3] == '.')
	&& (fn[len - 2] == 'b')
	&& (fn[len - 1] == 'c')) {
      fnx = fn;
      // fn = foo..bc
      return fnx;
    }}
  if (len > 3) {
    if ( (fn[len - 3] == '.')
	 && (fn[len - 2] == 'b')
	 && (fn[len - 1] == 'c')) {
      pos = len - 3;
      // fn = foo.bc
    }}
  if (pos == 0) {
#ifdef __arm__
#else
      printf("FN: %i %s\n",len,fn); 

      // strip possible '.' in 'foo.' or 'foo..'
      pos = len;
      for (i = 1; i <= 2; i++) {
	printf("i : %i ch: %c\n",i,fn[i]);
	if (fn[len - i] == '.') { pos = pos - 1; } else { break;}
      }
      printf("len: %i pos: %i\n",len,pos);
#endif
    }

  // fn[0:pos - 1] = 'foo'
  // add extension '..bc'
#ifdef __arm__
#else
  fnx = malloc(sizeof(char) * (pos + 4));
#endif
  for (i = 0; i < pos; i++) fnx[i] = fn[i];
  fnx[pos + 0] = '.';
  fnx[pos + 1] = '.';
  fnx[pos + 2] = 'b';
  fnx[pos + 3] = 'c';
  // fnx = foo..bc
#ifdef __arm__
#else
  printf("fnx: %s\n",fnx);
#endif
  return fnx;
}

int main(int argc, char *argv[])
{ 
#ifdef __arm__
#else
printf("argc: %i\n",argc);


  if (argc < 2) {
    printf("Usage: runbeta file\n");
    return -1;
  }
#endif
  char * fn = fixExtension(argv[1]);

#ifdef __arm__
  //FILE* F;
  int size,isXB;
  unsigned char* bc;
#else
  FILE* F = fopen(fn, "rb");
  if (F == NULL) {
    printf("No such file: '%s'\n",fn);
    return -1;
  }
  if (fseek(F, 0, SEEK_END)) {
    fclose(F);
    printf("Cannot open file\n");
  }
  int size = ftell(F);
  bool isXB = 1;
  printf("Runbeta: %i %s %i",argc,fn,(int)size);
  if (isXB ==1) 
    {printf(" executing xbeta/qbeta\n");}
  else 
    {printf(" executing beta\n");};

  fseek(F, 0, SEEK_SET);  //same as rewind(f);

  unsigned char* bc = (unsigned char*)malloc(size * sizeof(char));
  if (bc == NULL) printf("Malloc error\n");
  int V = fread(bc, 1, size, F);
  fclose(F); 
  if (V != size){
    printf("File read error: %i %i\n", (int)size,V);
    return -1;
  }
  
#endif

  init_interpreter((ObjDesc)bc,isXB);
  bool first = true;
  getEvent(first); 
  // for (i=0; i <1000000; i++ ){
  //getEvent(first);
  //   first = false;
  //}
  return 0;
}
