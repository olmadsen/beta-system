#include <stdio.h>

#define test 1
long long c64(long a, long b){ return ((long long)a << 32) + b;}
long long a64(long long a, long long b){ return a + b;}
long long s64(long long a, long long b){ return a - b;}

/* cannot link on sun4s
long long m64(long long a, long long b){ return a * b;}
long long d64(long long a, long long b){ return a / b;}
*/

/* this one should be reminder, but I dont remember syntax of operator
long long r64(long long a, long long b){ return a // b;}
*/ 
int eq64(long long a, long long b){return a == b;}
int ne64(long long a, long long b){return a != b;}
int lt64(long long a, long long b){return a < b;}
int le64(long long a, long long b){return a <= b;}
int gt64(long long a, long long b){return a > b;}
int ge64(long long a, long long b){return a >= b;}

