
public class EC extends Object
{ int N =0;

    public EC() { N = 0; }

    public void foo1() 
    { 
       System.out.println("foo1");
    }

    public void foo2(int a, int b)
    { System.out.println("foo2(" +a + ',' + b + ')');
      N = a+b;
    }

    public int foo3(EC S)
    { System.out.println("foo3");
      S.foo1();
      return N;
    }
}

