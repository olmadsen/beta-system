#include <stdio.h>
#include <stdlib.h>
int putCh(int ch){
  printf("%c",ch);
  return 0;
}
int* allocIndexed(int size, int range){
  int * A = (int *)malloc(8 + range * size * 4);
  A[0] = 0; // should be ref to en obj templete
  A[1] = range;
  return A;
}
int arrayLength(int * A){
  return A[1];
}
int* allocString(char *T, int range){
  int * stringObj;
  int i;
  printf("\nallocString: %s = ",T);
  stringObj = allocIndexed(1,range);
  for (i = 0; i < range; i++) {
    stringObj[i + 2] = T[i];
  }
  return stringObj;
}
int putHex(int V){
  printf("%x %i\n",V,V);
  return 0;
}
int dumpHex(int V, int n){
  int * A = (int *) V;
  int i;
  printf("obj %x:\n",V);
  for (i = 0; i < 5; i++)
    {printf("%i:%x, ",i,A[i]);}
  printf("\n");
  if ((n > 0) && (A[1] > 0)) dumpHex(A[1],n-1);
  return 0;
}
void notImpl(int op){
  printf("\n!!!! objCode: %i not implemented in LLVM!\n",op);
}
void arrayStuff(int I){
  struct{int range;int AAA[11];} R;
  int V;
  R.AAA[I] = 117;
  V = R.AAA[I];  
}
/*
; Function Attrs: noinline nounwind optnone
define dso_local void @arrayStuff(i32) #0 {
  %2 = alloca i32, align 4
  %3 = alloca %struct.anon, align 4
  %4 = alloca i32, align 4
  store i32 %0, i32* %2, align 4

  %5 = getelementptr inbounds %struct.anon, %struct.anon* %3, i32 0, i32 1
  %6 = load i32, i32* %2, align 4
  %7 = getelementptr inbounds [11 x i32], [11 x i32]* %5, i32 0, i32 %6
  store i32 117, i32* %7, align 4

  %8 = getelementptr inbounds %struct.anon, %struct.anon* %3, i32 0, i32 1
  %9 = load i32, i32* %2, align 4
  %10 = getelementptr inbounds [11 x i32], [11 x i32]* %8, i32 0, i32 %9
  %11 = load i32, i32* %10, align 4

  store i32 %11, i32* %4, align 4

  ret void
}

*/
