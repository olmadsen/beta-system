/*
  Compilation statements: 
    csc /t:library /r:System.dll nstringuser.cs 
    nbeta nstring.bet
*/ 
using System;

public class nstringuser
{  
  public void display(string S)
    { 
      Console.WriteLine(S);
    }
  public string get()
    { 
      return "Greetings from C#";
    }
}
