using System;
using System.Reflection;

public class test {
    public static void  Main(System.String[] args)
      {	 
	Console.WriteLine("Hello!");
	Console.WriteLine("Crash: " + asmname());
	return;
      }

    public static String asmname()
      {
	Assembly asm = Assembly.Load("fff");
        return asm.FullName.ToString();
      }
}
