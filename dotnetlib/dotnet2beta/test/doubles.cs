// csc -t:exe doubles.cs

class Class1
{
  static void Main()
    {
      System.Double d = 3.14;
      System.Console.WriteLine(System.String.Format("Pi: {0,1:f6}.", d));
    }
}
