/*
  Compilation statements: 
    nbeta -x Bclass.bet
    csc /nologo /r:System.dll /r:dotnet/tstenv.dll /r:dotnet/Bclass.dll BclassUser.cs 
*/ 
using System;

class Cclass: Bclass
{
  // C# constructor must transfer origin object to BETA constructor
  public Cclass(tstenv origin):base(origin)
    {
    }

  public override void compute(int arg)
    {
      Console.WriteLine("C#:   compute(" + arg + ") called. Calling BETA");
      base.compute(arg); // super
    }
}

class BclassUser
{
  public static void Main() 
    {
      Bclass b = new Cclass(new tstenv(null));
      b.set(9);
      Console.WriteLine(b.get());
      b.compute(10);
      Console.WriteLine(b.get());
      b.compute(-6);
      Console.WriteLine(b.get());
      b.compute(40);
      Console.WriteLine(b.get());
    } 
}
