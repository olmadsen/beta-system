/*
  Compilation: 
    nbeta Bclass.bet
    csc /nologo /r:clr/Bclass/Bclass.dll,clr/Bclass/betaenv.dll BclassUser.cs
  Execution:
    BclassUser.exe
*/ 
using System;

class Cclass: Bclass
{
  // C# constructor must transfer origin object to BETA constructor
  public Cclass(betaenv origin):base(origin)
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
      betaenv env = new betaenv(null);
      env.init();
      Bclass b = new Cclass(env);
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
