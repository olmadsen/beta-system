
// myClass:
class myClass extends Object {
  Object origin;
  public myClass(Object org){
    origin = org;
    x = 0;
    y = 0;
    z = 0;
  }
  long x;long y;long z;;
  
  // foo:
  class foo extends Object {
    myClass origin;
    public foo(myClass org){
      origin = org;
      a = 0;
      b = 0;
    }
    long a;
    long b;
    
    public void do_0(){
      x = x+a;
      do_1();
      y = y+b;
      a = x*y;
    }
    public void do_1(){}
  }
  public foo new_foo(){ return new foo(this); }
  public void call_foo(long a,long b){
    foo S;
    S = (foo)new_foo();
    S.a = a;
    S.b = b;
    S.do_0();
  };
  
};

// yourClass:
class yourClass extends myClass{
  Object origin;
  public yourClass(Object org){
    super(org);
    origin = org;
    u = 0;
    v = 0;
  }
  long u;long v;;
  
  // foo:
  class foo extends myClass.foo{
    yourClass origin;
    public foo(yourClass org){
      super(org);
      origin = org;
    }
    
    public void do_0(){
      y = x+y;
      System.out.println("yourClass:foo");
    }
    public void do_1(){}
  }
  public myClass.foo new_foo(){ return new foo(this); }
  public void call_foo(){
    foo S;
    S = (foo)new_foo();
    S.do_0();
  };
  
};

class mySubEx extends Object {
  public static void main(String args[]) {
    yourClass S;;
    long V;;
    S = new yourClass(null);
    V = S.call_foo(11,22);
    System.out.print("V = ");
    System.out.println(V);
    System.out.println();
  }
}