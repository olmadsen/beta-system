/*
 * BETA RUNTIME SYSTEM, Copyright (C) 1992 Mjolner Informatics Aps.
 * Mod: wordsort.c
 * by Tommy Thorn
 */

/* This file implements QuickSort for [unsigned] integers
 * with a few standard improvements:
 *  Simulate recursion with a stack
 *  Push largest block to stack, ensures O(ln n) stack height
 *  Compare median with hi and lo, to improve choise
 *  Use insertion sort for small sections [no done yet]
 *  
 */

typedef unsigned int elem;	/* for easy change of types */

#define SWAP(a,b) do { elem t = *a; *a = *b; *b = t; } while(0)
#define maxt 0

void WordSort(v, size)
elem *v;
int size;
{
  register elem p;
  elem *l, *r;
  int stacktop = 0;
  elem *lstack[32], *rstack[32];	/* 32 = ln(MAX_INT) */
  elem *m, *lo = v, *hi = v+size-1;

  if (size <= 1)
    return;
  
  for (;;)
    {
      m = (hi - lo) / 2 + lo;
      if (*m < *lo)
	SWAP(m, lo);
      if (*hi < *m)
	SWAP(hi, m);
      else
	goto skip;
      if (*m < *lo)
	SWAP(m, lo);
    skip:
      p = *m;
      l = lo + 1;
      r = hi - 1;
      do
	{
	  while (*l < p)
	    l++;
	  while (p < *r)
	    r--;
	  if (l < r)
	    {
	      SWAP(l,r);
	      l++;
	      r--;
	    }
	  else if (l == r)
	    {
	      l++;
	      r--;
	      break;
	    }
	}
      while (l <= r);
      
      if (r - lo <= maxt)
	{
	  if (hi - l <= maxt)
	    {
	      /* both too small, get new target */
	      if (stacktop == 0)
		/* we're though */
		break;
	      --stacktop;
	      lo = lstack[stacktop]; hi = rstack[stacktop];
	    }
	  else
	    /* only left too small */
	    lo = l;
	}
      else if (hi - l <= maxt)
	/* right too small */
	hi = r;
      else if (r - lo > hi - l)	/* push the larger of the two */
	{
	  lstack[stacktop] = lo; rstack[stacktop] = r;
	  ++stacktop;
	  lo = l;
	}
      else
	{
	  lstack[stacktop] = l; rstack[stacktop] = hi;
	  ++stacktop;
	  hi = r;
	}
    }
}

#ifdef TEST_WORDSORT
main(int argc, char *argv[])
{
  int i, n;

  if (argc < 2)
    exit(1);
  n = atoi(argv[1]);
  {
    int v[n];
    srand(i);
    for (i = 0; i < n; i++)
      v[i] = rand() % (10*n);

    /*  
      for (i = 0; i < n; i++)
      printf("%d ", v[i]);
      */
    printf("sorting.."); 
    fflush(stdout);
    intsort(v, n);
    printf("done\n");
    fflush(stdout);

    {
      int i,j,k;
      for (i = 0; i < n; ++i)
	for (j = 0; j < n; ++j)
	  if (v[i] < v[j])
	    {
	      k = v[i];
	      v[i] = v[j];
	      v[j] = k;
	    }

    }
    printf("done bubblesort\n");
    fflush(stdout);
/*  printf("\n"); */
  for (i = 1; i < n; i++)
    if (v[i] < v[i-1])
      printf("bzzzz, wrong guess Hans!\n");
/*  for (i = 0; i < n; i++)
    printf("%d ", v[i]);
*/
  }
}
#endif

