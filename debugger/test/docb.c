typedef void (*cbtype) (int,int,int);
void docb (cbtype thecb)
{ int i;
  for (i=0;i<10;i++) thecb(i*3,i*3+1,i*3+2);
}
