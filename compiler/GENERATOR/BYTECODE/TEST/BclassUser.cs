/*
  Compilation statements: 
    nbeta -x Bclass.bet
    csc /r:System.dll /r:tstenv.dll /r:Bclass.dll BclassUser.cs 
*/ 
using System;

class Cclass: Bclass
{
  // C# constructor must transfer origin object to BETA constructor
 public Cclass(tstenv origin):base(origin)
    {
    }
  public override void fisk(int arg)
    {
      Console.WriteLine("fisk(" + arg + ") called in C# specialization. Calling BETA");
      base.fisk(arg);
    }
}

class BclassUser
{
  public static void Main() 
    {
      Bclass b = new Cclass(null); // Origin should actually be a tstenv instance
      b.set(9);
      Console.WriteLine(b.get());
      b.fisk(10);
      Console.WriteLine(b.get());
      b.fisk(-6);
      Console.WriteLine(b.get());
      b.fisk(40);
      Console.WriteLine(b.get());
    } 
}
