
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
      y = y+b;
      a = x*y;
      System.out.println(a);
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
  
  // elem:
  class elem extends Object {
    myClass origin;
    public elem(myClass org){
      origin = org;
      q = 0;
      w = 0;
    }
    long q;;
    long w;;
    
  }
  public elem new_elem(){ return new elem(this); };
  
};

class myEx extends Object {
  public static void main(String args[]) {
    myClass S;;
    long V;;
    S = new myClass(null);
    V = S.call_foo(11,22);
    System.out.print("V = ");
    System.out.println(V);
    System.out.println();
  }
}