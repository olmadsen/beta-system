/*
  Compilation statements: 
    $BETALIB/compiler/nti_ms/sbeta -t dotnet Bclass.bet
    csc /r:System.dll /addmodule:Bclass.dll BclassUser.cs 
*/ 
using System;

class Cclass: Bclass
{
  // C# constructor must transfer origin object to BETA constructor
 public Cclass(object origin):base(origin)
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
      Bclass b = new Cclass(null);
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
