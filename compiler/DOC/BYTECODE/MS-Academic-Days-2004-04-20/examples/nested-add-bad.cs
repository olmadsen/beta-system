/*
  csc -nologo nested-add-bad.cs

  => Cannot access a nonstatic member of outer type 
     'Calculator' via nested type 'Calculator.add'
*/

public class Calculator: System.Object {
  int R;
  public class add: System.Object { 
    public int V;
    public void Enter(int a) { V = a; }
    public void Do() { R = R + V; }
    public int Exit() { return R; }
  }
  public void set(int V) { R = V; }
  public int call_add(int V){ 
    add A = new add();
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
      Calculator.add A = new Calculator.add();
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
