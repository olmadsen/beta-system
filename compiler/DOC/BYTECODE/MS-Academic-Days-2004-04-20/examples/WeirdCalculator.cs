/*
  csc -nologo WeirdCalculator.cs
*/

public class Calculator: System.Object {
  public int R;
  public class add: System.Object { 
    Calculator origin;
    public int V;
    public add(Calculator outer) { origin = outer; }
    public void Enter(int a) { V = a; }
    public void Do() { origin.R = origin.R + V; Inner_1(); }
    public virtual void Inner_1(){}
    public int Exit() { return origin.R; }
  }
  public void set(int V) { R = V; }
  public int call_add(int V){ 
    add A = new add(this);
    A.Enter(V);
    A.Do();
    return A.Exit();
  }
}

public class WeirdCalculator: Calculator {

  public class xadd: Calculator.add
     { 
        WeirdCalculator origin;
        public xadd(WeirdCalculator outer):base(outer) { origin = outer; }
        public override void Inner_1(){
        origin.R = origin.R * V;
      }
    }
  public int call_xadd(int V){ 
    xadd A = new xadd(this);
    A.Enter(V);
    A.Do();
    return A.Exit();
  }


  public static void Main(System.String[] args){
      WeirdCalculator C = new WeirdCalculator();
      int x;

      System.Console.WriteLine("Using xadd as a method");
      C.set(12);
      x = C.call_xadd(5);
      System.Console.WriteLine(x);

      System.Console.WriteLine("Using xadd as a class");
      WeirdCalculator.xadd A = new WeirdCalculator.xadd(C);
      C.set(17);
      A.Enter(13); 
      A.Do();
      x = A.Exit();
      System.Console.WriteLine(x);
      A.V = 10;
      A.Do();
      x = A.Exit();
      System.Console.WriteLine(x);
    }
}
