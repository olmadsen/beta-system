/*
  csc -nologo nested-add.cs
*/

public class Calculator: System.Object {
  int R;
  public class add: System.Object { 
    Calculator origin;
    public int V;
    public add(Calculator outer) { origin = outer; }
    public void Enter(int a) { V = a; }
    public void Do() { origin.R = origin.R + V; }
    public int Exit() { return origin.R; }
  }
  public void set(int V) { R = V; }
  public int call_add(int V){ 
    add A = new add(this);
    A.Enter(V);
    A.Do();
    return A.Exit();
  }
  public static void Main(System.String[] args){
      Calculator C = new Calculator();
      int x;

      System.Console.WriteLine("Using add as a method");
      C.set(12);
      x = C.call_add(5);
      System.Console.WriteLine(x);

      System.Console.WriteLine("Using add as a class");
      Calculator.add A = new Calculator.add(C);
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
