
long * loadObject(long *bufAdr, long length)
{ long * start; int i;
  start = (long *)memalign(4,length+4);
  if (start == (long *)0) {printf("Alloc failure in loadObject: memalign\n");};
  if (((int)start % 4) != 0) {printf("Wrong alignment %\n",start); 
     start = (long *) (((int)start / 4) *4);
  }
  if (((int)start % 4) != 0) printf("Wrong alignment again %i\n",start); 
  for (i=0; i < (length / 4); i++) start[i] = bufAdr[i];
  return start;
}

long * MakeStruc(long proto, long origin)
{ long * struc;
  struc =(long *)memalign(4,16);
  if (struc == (long *)0) {printf("Alloc failure in MakeStruc: memalign\n");};
  struc[0] = -3;
  struc[1] = 1;
  struc[2] = origin;
  struc[3] = proto;
  return struc;
}
