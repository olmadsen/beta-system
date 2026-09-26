#include <stdio.h> 
void showObj(long* obj){
   long *vdt; 
   char *s; 
   int i; 
   //printf("showObj: %lx %lx %lx %lx \n", (long)obj, (long)obj[0], (long)obj[1], (long)obj[2]);

   vdt = (long *)obj[2];

   /* printf("VDT: %lx : ", (long) &vdt[0]);
      for (i =0; i < 4; i++) {
         printf("%lx, ",vdt[i]);
      }
   */
   s = (char *) (vdt + (vdt[0] / 8) );
   //printf("\n>>>Name: %lx , %s\n", (long)s, s);
   printf("\n>>>Name: %s\n", s);
} 
