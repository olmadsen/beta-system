

// csc /t:library /optimize+ primitives.cs
// ildasm /text /out=primitives.il primitives.dll 


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
    
}
