
class ECtest extends Object
{ int N =0;

    public ECtest() { N = 0; }

    public void foo1() 
    { 
       System.out.println("foo1");
    }

    public void foo2(int a, int b)
    { System.out.println("foo2(" +a + ',' + b + ')');
      N = a+b;
    }

    public int foo3(ECtest S)
    { System.out.println("foo3");
      S.foo1();
      return N;
    }
}

