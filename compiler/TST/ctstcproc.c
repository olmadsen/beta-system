
#include <stdio.h>
char *ident( r) char *r; { return r; }
int  giveMe1Argument(a,b,c) int a,b,c; { return a; }
int  giveMe2Argument(a,b,c) int a,b,c; { return b; }
int  giveMe3Argument(a,b,c) int a,b,c; { return c; }
int sumMany(a,b,c,d,e,f,g,h,i,j) int a,b,c,d,e,f,g,h,i,j;
{return a+b+c+d+e+f+g+h+i+j; }

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
void sprint2(a,b,r) char *a; const char * b; double r;{int i; 
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
