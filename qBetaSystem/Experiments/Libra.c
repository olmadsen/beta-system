#include <stdlib.h>
#include <math.h>

#include <stdio.h>
int main(void)
{ double X =  log((40.0 + 10000.0) / 40.0);
  double rocketSpeed = 1000000.0 * log((40.0 + 10000.0) / 40.0);
  printf(" Xlog = %f, rocketSpeed = %f ",X, rocketSpeed);
  
  rocketSpeed = rocketSpeed / 300000000;
  printf("rocketSpeedAdj = %f,time = %f\n",rocketSpeed,70/rocketSpeed);

  printf("%f %f\n",sqrt(560000.0/(1.2 * 4.6)),sqrt(16.0));
  
}


/*
val rocketSpeed = 1000000.0.mps * log(((40.0.kg +10000.0.kg) /40.0.kg).value)
val speedConversion = 300000000.0.mps / 1.c 
val speedInC = rocketSpeed / speedConversion
val time = 77.0.ly / speedInC
//time: Quantity[FieldType[Year, 1] :: HNil] = Quantity(4180.65274634)
*/
