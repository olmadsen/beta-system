/*
  javac Calculator.java
  java Calculator
*/

public class Calculator extends java.lang.Object {
  public int R;
  public class add extends java.lang.Object { 
    public int V;
    public void Enter(int a) { V = a; }
    public void Do() { R = R + V; }
    public int Exit() { return R; }
  }
  public void set(int V) { R = V; }
  public int add(int V){ 
    add A = new add();
    A.Enter(V);
    A.Do();
    return A.Exit();
  }
  public static void main(java.lang.String[] args){
      Calculator C = new Calculator();
      int x;

      System.out.println("Using add as a method");
      C.set(12);
      x = C.add(5);
      System.out.println(x);

      System.out.println("Using add as a class");
      Calculator.add A = C.new add();
      C.set(17);
      A.Enter(13); 
      A.Do();
      x = A.Exit();
      System.out.println(x);
      A.V = 10;
      A.Do();
      x = A.Exit();
      System.out.println(x);
    }
}
