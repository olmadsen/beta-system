#include "ranlib.h"
#include <stdio.h>
#include <math.h>
#include <string.h>
#define min(a,b) ((a) <= (b) ? (a) : (b))

extern void pr_ln_ar(long *array, long larray);

void main(int argc,char* argv[])
/*
     Interactive test for PHRTSD
*/
{
static long K1 = 1;
static long i,itmp,mxint,ntot,nrep,larray,is1,is2;
static char phrase[100];
static long iarray[1000];

    puts(" Tests uniform random integer generator.");
    puts(" Asks for upper bound, number of");
    puts("     replicates per integer in 1..upper bound.");
    puts("     Prints table of num times each integer generated.");

    puts(" Enter phrase to initialize rn generator");
    scanf("%s",phrase);
    phrtsd(phrase,&is1,&is2);
    setall(is1,is2);
/*
     Uniform integer
*/
    puts(" Enter maximum uniform integer - upper limit 1000");
    scanf("%d",&mxint);
    if (mxint < 1 || mxint > 1000){
        puts(" Maximum integer must be between 1 and 1000");
        return;
      }
    puts(" Enter number of replications per integer");
    scanf("%d",&nrep);
    for(i=1; i<=1000; i++) *(iarray+i-1) = 0;
    ntot = mxint*nrep;
    for(i=1; i<=ntot; i++) {
        itmp = ignuin(K1,mxint);
	printf(" %7i",itmp); if (i%10==0) printf("\n");
        *(iarray+itmp-1) += 1;
    };
    printf("\n");
    puts("         Counts of Integers Generated");
    pr_ln_ar(iarray,mxint);
}

void pr_ln_ar(long *array, long larray)
/*
  Print array of longs; length of array is larray.  Print 10 to a
  line using 7 characters for each field.
*/
{
    int lo, hi, i, up;
    up = larray-1;
    for (lo=0; lo <=up; lo +=10) {
        hi = min(lo+9,up);
    	for (i=lo; i<=hi; i++)
            printf(" %7ld",*(array+i));
    puts("");    
    }
}    
