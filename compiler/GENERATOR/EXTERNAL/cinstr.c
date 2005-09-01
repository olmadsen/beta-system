#include <stdio.h>

/* Compile with:
 *   gcc -save-temps -c -O6 cinstr.c
 * and look at cinstr.s
 */

typedef union word
{
  unsigned long raw;
  unsigned char b[4];
} word;

typedef union bitfield
{
  unsigned long raw;
  struct {
    unsigned long bit0_6   :7;
    unsigned long bit7     :1;
    unsigned long bit8_12  :5;
    unsigned long bit13_31 :19;
  } bits;
} bitfield;

unsigned long byteswap(unsigned long x)
{ 
  word w;
  w.raw = x;
  return 
    ((long)w.b[3]<<24) | ((long)w.b[2]<<16) | ((long)w.b[1]<<8) | ((long)w.b[0]);
}

signed long SignExtByte(signed char a)
{
  return (a<<24)>>24;
}

signed long SignExtWord(signed short a)
{
  return (a<<16)>>16;
}

unsigned long GetBits(unsigned long a, int pos, int len)
{
  if (len==0) return 0;
  return (a<<pos) >> (32-len);
}

unsigned long GetBit7(unsigned long a)
{
  bitfield bf;

  bf.raw=a;
  return bf.bits.bit7;
}

unsigned long GetBit8_12(unsigned long a)
{
  bitfield bf;

  bf.raw=a;
  return bf.bits.bit8_12;
}

unsigned long PutBit8_12(unsigned long a, unsigned bits)
{
  bitfield bf;

  bf.raw=a;
  bf.bits.bit8_12 = bits;
  return bf.raw;
}

char GetByteBigEndian(unsigned long a, int byteNo /* 0-3 */)
{ return (a >> (8*(3-byteNo))) & 0xff; /* big endian */ }

char GetByteLittleEndian(unsigned long a, int byteNo /* 0-3 */)
{ return (a >> (8*byteNo)) & 0xff; /* little endian */ }

unsigned long PutByteBigEndian(unsigned long a, unsigned char b, int byteNo /* 0-3 */)
     /* (b, byteno) -> a.%putByte */
{ 
  return ( ( a & ~(0xff << (8*(3-byteNo)))) ) | ( (b & 0xff) << (8*(3-byteNo))  ); 
}

unsigned long PutByteLittleEndian(unsigned long a, unsigned char b, int byteNo /* 0-3 */)
     /* (b, byteno) -> a.%putByte */
{ 
  return ( ( a & ~(0xff << (8*(byteNo)))) ) | ( (b & 0xff) << (8*(byteNo))  ); 
}

signed long GetSignedBits(unsigned long a, int pos, int len)
{
  if (len==0) return 0;
  return ((signed long)(a<<pos)) >> (32-len);
}

int gGetSignedBits(int dr,  int pDr,  int lDr)
{
  return (dr << pDr) >> (32-lDr);
}

void PutBits(unsigned long a, unsigned long *b, int pos, int len)
{
  *b= ((a & ((1<<len)-1)) << (32-len-pos)) 
    | (*b & ~(((1<<len)-1) << (32-len-pos)) );
}

unsigned short GetShortBigEndian(unsigned long a,int shortNo /* 0-1 */)
{ return (a >> (16*(1-shortNo))) & 0xffff; /* big endian */ }

unsigned short GetShortLittleEndian(unsigned long a,int shortNo /* 0-1 */)
{ return (a >> (16*shortNo)) & 0xffff; /* little endian */ }

unsigned int gPutBits(unsigned int dr, unsigned int pDr,
		      unsigned int lDr, unsigned long * ar)
{ unsigned long mask=((unsigned long) ((-1)<<(32-lDr)))>>pDr;
  unsigned long bits=(dr << (32-lDr)) >> pDr;
  *ar= (*ar & ~mask) | bits;
}

signed long ldSignedVl(int size, unsigned long *addr)
{
  switch (size){
  case 1:
    return (signed long) *(signed char *)addr;
  case 2:
    return (signed long) *(signed short *)addr;
  case 4:
    return (signed long) *(signed long *)addr;
  }
}

#if 1
int main()
{ 
  int x,y,z;
  z=0x12345678;
  x=1;
  y=2;
  printf("z=0x%08x, x=%d, y=%d\n", z, x, y);
  printf("(x,y)->z.%%putbyte    big endian => z=0x%x\n", PutByteBigEndian(z, x, y));
  printf("(x,y)->z.%%putbyte little endian => z=0x%x\n", PutByteLittleEndian(z, x, y));
}
#endif

