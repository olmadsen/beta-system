/* 
    csc /t:exe /optimize+ primitives.cs
    ildasm /text /out=primitives.il primitives.exe 
*/


class Primitives {
  public bool not (bool b)
    {
      return !b;
    }
  
  public int bitnot (int i){
    return ~i;
  }
  
  public int ror (int i, int r)
    {
      return (i >> r) | ((i & ((1<<r)-1)) << (32-r));
    }
  
  public int rol (int i, int r)
    {
      return (i << r) | ((i & ((1<<r)-1)) >> (32-r));
    }
  
  public ushort byteswapshort (ushort x)
    {
      return (ushort)((x>>8) | ((x<<8) & 0xff00));
    }

  public uint byteswapuint (uint x)
    {
      uint h = (x>>16);
      uint l = (x & 0xffff);
      return ((l>>8) | ((l<<8) & 0xff00)) << 16 | ((h>>8) | ((h<<8) & 0xff00));
    }

  public uint byteswaplong(uint ABCD)
    { 
      // ABCD -> DCBA
      uint AB = (ABCD>>16);
      uint CD = (uint)(ABCD & 0xffff);
      uint BA = (uint)((AB>>8) | ((AB & 0xff)<<8));
      uint DC = (uint)((CD>>8) | ((CD & 0xff)<<8));
      uint DCBA = (DC << 16) | BA;
      return DCBA;
    }
  
  public uint byteswaplonginlined(uint ABCD)
    { 
      return (((uint)((((uint)(ABCD & 0xffff))>>8) | ((((uint)(ABCD & 0xffff)) & 0xff)<<8)) << 16)) | ((uint)(((ABCD>>24)) | (((ABCD>>16) & 0xff)<<8)));
    }

  public static void Main(System.String[] args) {
    Primitives p = new Primitives();
    System.Console.WriteLine("Expected: " + 0x21436587); 
    System.Console.WriteLine("Result:   " + p.byteswaplonginlined(0x87654321)); 
  }

}
