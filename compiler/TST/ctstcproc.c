
#include <stdio.h>
char *ident( r) char *r; { return r; }
int  giveMe1Argument(a,b,c) int a,b,c; { return a; }
int  giveMe2Argument(a,b,c) int a,b,c; { return b; }
int  giveMe3Argument(a,b,c) int a,b,c; { return c; }
int sumMany(a,b,c,d,e,f,g,h,i,j) int a,b,c,d,e,f,g,h,i,j;
{
  /*printf("\n%i %i %i %i %i %i %i %i %i %i\n",a,b,c,d,e,f,g,h,i,j);*/
  return a+b+c+d+e+f+g+h+i+j; 
}

void doCallBar(f)
     void (*f)();
{
  f();
}

int doCallBack(f)  
int (*f)();
{int x;
   x=f('l',"mn",'!','!','!','!','!','o');
   return x;  
}

int doCallBack2(f)
int (*f)();
{ int x;
   x=f('6',"78",'!','!','!','!','!','9');
   return x;  
}

typedef double real;        /* The C representation of a Beta real.  */

real radd(x1,x2)
  /* Calculate x1+x2. */
  real x1,x2;
  {
   return(x1+x2);
  }
real rcopy(x1)
  double x1;
  {
   return(x1);
  }
real tau(){double x; x=3.0; return (x); }

void outr(a,b,r) int a,b; double r;{printf("int=%d,%d,real:%lf\n",a,b,r);}
void sprint2(a,b,r) char *a; const char * b; double r;{ 
  printf("buffer=%s,control=%s,real=%lf\n",a,b,r);

  sprintf(a,b,r);
  printf("sprintf: %s\n",a);
}

int copystring( r) char *r; { printf(r); return 111; }

void PP(ch) char ch;{printf("%c",ch);}

struct Xdata{int w; char ch,q; long y;};
struct Ydata{int w; char ch,q; long y; char a,b; int d;};

struct Ydata *XdataToYdata(r) struct Xdata *r;
{ struct Ydata *s;
  /*printf ("\nFrom C: \tw:%d, ch:%c, q:%c, y:%d\n",r->w,r->ch,r->q,r->y);
  fflush(stdout);*/

  s=(struct Ydata*)malloc(sizeof(struct Ydata));
  if (r->w==99) {s->w=r->w-1;};
  if (r->ch=='a') {s->ch='#';} else {s->ch='?';}
  s->q='$';
  s->y=r->y-1;
  s->a='+';
  s->b='*';
  s->d=444;
  /*printf ("\nFrom C: \tw:%d, ch:%c, q:%c, y:%d, a:%c, b:%c, d:%d\n",s->w,s->ch,s->q,s->y,s->a,s->b,s->d);
  fflush(stdout);*/
  return s;
}
char *XdataToText(r) struct Xdata *r;
{ struct Ydata *s;
  /*printf ("\nFrom C: \tw:%d, ch:%c, q:%c, y:%d\n",r->w,r->ch,r->q,r->y);
  fflush(stdout);*/

  if (r->w==99) 
    { if (r->ch=='a') 
	{return "012";} else {return "!!!";};
    }
  else {return "???";}
}

void printSub(s) char *s; {
   printf("%s",s);
   fflush(stdout);
 }

int fdd(i,s) long i; char *s; {
   if(( i==111) && (s="qwerty")) {return 'g';}
   else return '!';
 }
  
long id(long x) { return x; }

long intFloat(int n, real x) {return (long)(n+x);}
long floatInt(real x, int n) {return (long)(n+x);}

void bar(f) long (*f)();
{ long b;
  b = f('a',1);
  printf("%c\n",b);
}


long tst3reals(double d1, double d2, double d3)
{ 
  if (d1 != 1.0){
    fprintf(stdout, "[%.1f<>%.1f]", d1, 1.0);
    fflush(stdout);
    return 0;
  }
  if (d2 != 2.0){
    fprintf(stdout, "[%.1f<>%.1f]", d2, 2.0);
    fflush(stdout);
    return 0;
  }
  if (d3 != 3.0){
    fprintf(stdout, "[%.1f<>%.1f]", d3, 3.0);
    fflush(stdout);
    return 0;
  }
  return 1; /* all matched */
}

/* tstvarargs test that it is called with a consecutive 
 * list of reals, i.e. 1.0, 2.0, 3.0...
 */
#include <stdarg.h>
long tstvarargs(long numreals, ...)
{ 
  double d,v;
  va_list ap;
  if (numreals) {
    /* At least 1 real */
    va_start(ap, numreals);
    d = 1.0;
    while (numreals--){
      v = (double)(va_arg(ap, double));
      if (v != d){
	fprintf(stdout, "[%.1f<>%.1f]", v, d);
	fflush(stdout);
	return 0;
      }
      d+=1.0;
    }
    va_end(ap);
  }
  return 1; /* all matched */
}

long tstreal1(long n1, double d1)
{ return n1+d1;
}

long tstreal2(long n1, double d1, double d2)
{ return n1+d1+d2;
}

long tstreal3(long n1, double d1, double d2, double d3)
{ return n1+d1+d2+d3;
}

long tstreal4(long n1, long n2 , double d1, double d2)
{ return n1+n2+d1+d2;
}

long tstreal5(long n1, long n2 , long n3, double d1)
{ return n1+n2+n3+d1;
}

long tstreal6(double d1, long n1)
{ return d1 + n1;
}

long tstreal7(double d1, double d2, long n1)
{ return d1 + d2 + n1;
}

long tstreal8(double d1, long n1, long n2)
{ return d1 + n1 + n2;
}

long tstreal9(double d1, long n1, long n2, long n3)
{ return d1 + n1 + n2 + n3;
}

long tstreal10(double d1, long n1, double d2)
{ return d1 + n1 + d2;
}

long tstreal11(long n1, double d1, double d2, double d3, double d4)
{ return n1+d1+d2+d3+d4;
}

long tstrealX()
{ long x,y,z,w,v;
 x = tstreal1(11,11.1);
 y = tstreal2(22,12.2,13.3);
 z = tstreal3(33,14.4,15.5,16.6);
 v = tstreal4(44,55,17.7,18.8);
 w = tstreal5(66,77,88,20.2);
}
