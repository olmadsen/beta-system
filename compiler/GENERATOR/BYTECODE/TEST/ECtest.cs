/*
  Compilation statement 
  csc /t:module /out:ECtest.dll /r:System.dll ECtest.cs
  BETA compile without -s 184 
*/ 

class ECtest: System.Object
{ 
    int N =0;

    public void foo1() 
    { 
       System.Console.WriteLine("foo1");
    }

    public void foo2(int a, int b)
    { 
      System.Console.WriteLine("foo2(" +a + ',' + b + ')');
      N = a+b;
    }

    public int foo3(ECtest S)
    { 
      System.Console.WriteLine("foo3");
      S.foo1();
      return N;
    }
}

