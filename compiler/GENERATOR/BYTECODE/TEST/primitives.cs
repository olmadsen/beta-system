

// csc /t:library /o primitives.cs


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
 
}
