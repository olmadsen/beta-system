/* Compile with
     javac -O primitives.java
   the inpect generated code by
     jcf-dump -c Primitives
*/

class Primitives {
    public static boolean lognot (boolean b)
    {
	return !b;
    }

    public static int not (int i){
	return ~i;
    }

    public static int lsr8 (int i){
	return i >>> 8;
    }

    public static int ror (int i, int r)
    {
	int mask = (1 << r) - 1;
	return (i >> r) | ((i & mask) << (32-r));
    }
  
    public static int rol (int i, int r)
    {
	int mask = (1 << r) - 1;
	return (i << r) | ((i & mask) >> (32-r));
    }
  
    static short byteswapshort(short x)
    { 
	return (short)((x>>8) | ((x<<8) & 0xff00));
    }

    static int byteswaplong(int x)
    { 
	short h = (short)(x>>16);
	short l = (short)(x & 0xffff);
	short nl = (short)((h>>8) | ((h<<8) & 0xff00));
	short nh = (short)((l>>8) | ((l<<8) & 0xff00));
	int nhl = (nh << 16) | nl;
	return nhl;
    }

    static int byteswaplonginlined(int x)
    { 
	return (((short)((((short)(x & 0xffff))>>8) | ((((short)(x & 0xffff))<<8) & 0xff00))) << 16) | ((short)((((short)(x>>16))>>8) | ((((short)(x>>16))<<8) & 0xff00)));
    }

    static int SignExtByte(byte a)
    {
	return (a<<24)>>24;
    }

    static int SignExtWord(short a)
    {
	return (a<<16)>>16;
    }

    static int GetBits(int a, int pos, int len)
    {
	if (len==0) return 0;
	return (a<<pos) >> (32-len);
    }

    static int GetBit7(int a)
    {
	return 0 /* FIXME */;
    }

    static int GetBit8_12(int a)
    {
	return 0 /* FIXME */;
    }

    static int PutBit8_12(int a, int bits)
    {
	return 0 /* FIXME */;
    }

    static byte GetByte(int a, int byteNo /* 0-3 */)
    { 
	return (byte)((a >> (8*(3-byteNo))) & 0xff); /* big endian */
    }

    static int GetSignedBits(int a, int pos, int len)
    {
	if (len==0) return 0;
	return ((a<<pos)) >> (32-len);
    }

    static int gGetSignedBits(int dr,  int pDr,  int lDr)
    {
	return (dr << pDr) >> (32-lDr);
    }

    static int PutBits(int a, int b, int pos, int len)
    {
	b= ((a & ((1<<len)-1)) << (32-len-pos)) 
	    | (b & ~(((1<<len)-1) << (32-len-pos)) );
	return b;
    }

    static short GetShort(int a,int shortNo /* 0-1 */)
    { 
	return (short)((a >> (16*(1-shortNo))) & 0xffff); /* big endian */
    }

    static int gPutBits(int dr, int pDr, int lDr, int ar)
    { 
	int mask=((int) ((-1)<<(32-lDr)))>>>pDr;
	int bits=(dr << (32-lDr)) >>> pDr;
	ar= (ar & ~mask) | bits;
	return ar;
    }
    
    public static void main(String[] args) {
	System.out.println(byteswaplong(0x12345678)); 
    }

}




