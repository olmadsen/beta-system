/* Compile with
     javac -O primitives.java
   the inpect generated code by
     jcf-dump -c Primitives
*/

class Primitives {
  public boolean lognot (boolean b)
  {
    return !b;
  }

  public int not (int i){
    return ~i;
  }

  public int lsr8 (int i){
    return i >>> 8;
  }

  public int ror (int i, int r)
  {
    int mask = (1 << r) - 1;
    return (i >> r) | ((i & mask) << (32-r));
  }
  
  public int rol8 (int i, int r)
  {
    int mask = (1 << r) - 1;
    return (i << r) | ((i & mask) >> (32-r));
  }
  
  int byteswap(int x)
  { 
    return 0 /* FIXME */;
  }

  int SignExtByte(byte a)
  {
    return (a<<24)>>24;
  }

  int SignExtWord(short a)
  {
    return (a<<16)>>16;
  }

  int GetBits(int a, int pos, int len)
  {
    if (len==0) return 0;
    return (a<<pos) >> (32-len);
  }

  int GetBit7(int a)
  {
    return 0 /* FIXME */;
  }

  int GetBit8_12(int a)
  {
    return 0 /* FIXME */;
  }

  int PutBit8_12(int a, int bits)
  {
    return 0 /* FIXME */;
  }

  byte GetByte(int a, int byteNo /* 0-3 */)
  { 
    return (byte)((a >> (8*(3-byteNo))) & 0xff); /* big endian */
  }

  int GetSignedBits(int a, int pos, int len)
  {
    if (len==0) return 0;
    return ((a<<pos)) >> (32-len);
  }

  int gGetSignedBits(int dr,  int pDr,  int lDr)
  {
    return (dr << pDr) >> (32-lDr);
  }

  int PutBits(int a, int b, int pos, int len)
  {
    b= ((a & ((1<<len)-1)) << (32-len-pos)) 
      | (b & ~(((1<<len)-1) << (32-len-pos)) );
    return b;
  }

  short GetShort(int a,int shortNo /* 0-1 */)
  { 
    return (short)((a >> (16*(1-shortNo))) & 0xffff); /* big endian */
  }

  int gPutBits(int dr, int pDr, int lDr, int ar)
  { 
    int mask=((int) ((-1)<<(32-lDr)))>>>pDr;
    int bits=(dr << (32-lDr)) >>> pDr;
    ar= (ar & ~mask) | bits;
    return ar;
  }

}




