int extsearch (int val, int* startAdr)
{ int *p1 = startAdr;

 label1:
  if ((*p1) == val)
    return (p1 - startAdr) + 1;

  p1++;
  goto label1;
}
