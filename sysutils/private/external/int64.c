#ifndef INT64
#ifdef __GNUC__
#define INT64 signed long long int
#endif /* __GNUC__ */
#ifdef sgi
#define INT64 signed long long int
#endif
#ifdef nti
#define INT64 signed _int64
#endif /* nti */
#endif /* INT64 */

#ifndef INT64
#error INT64 must be defined
#endif /* INT64 */

INT64 c64(long a, long b){ return ((INT64)a << 32) + b;}
INT64 a64(INT64 a, INT64 b){ return a + b;}
INT64 s64(INT64 a, INT64 b){ return a - b;}

/* The following requires
 *   /usr/local/lib/gcc-lib/sparc-sun-solaris2.5.1/2.8.1/libgcc.a
 * on sparc.
 */
#if 0
INT64 m64(INT64 a, INT64 b){ return a * b;}
INT64 d64(INT64 a, INT64 b){ return a / b;}
INT64 r64(INT64 a, INT64 b){ return a % b;}
#endif

int eq64(INT64 a, INT64 b){return a == b;}
int ne64(INT64 a, INT64 b){return a != b;}
int lt64(INT64 a, INT64 b){return a < b;}
int le64(INT64 a, INT64 b){return a <= b;}
int gt64(INT64 a, INT64 b){return a > b;}
int ge64(INT64 a, INT64 b){return a >= b;}

#define TEST 1
#undef TEST
#ifdef TEST
#include <stdio.h>
int main()
{
  fprintf(stdout, "%d\n", (int)m64(2,3));
  fflush(stdout);
}
#endif
