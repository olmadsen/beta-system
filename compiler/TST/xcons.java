class xcons
{ int q1,q2,q3;

    public xcons(int a, int b)
    { q1 = a; q2 = b;
    }
    public xcons(int a, int b, int c)
    { q1 = a; q2 = b; q3=c;
    }

    public void foo()
    {System.out.println(q1+q2);
    }
    public void bar()
    {System.out.println(q1+q2+q3);
    }
}
