/*
  csc -nologo naive.cs
*/

public class Calculator: System.Object
  { 
    int R;
    void set(int V) { R = V; }
    int add(int V) { R = R + V; return R; }

    public static void Main(System.String[] args){
      Calculator C = new Calculator();
      int x;
      C.set(12);
      x = C.add(5);
      System.Console.WriteLine(x);
    }
  }
