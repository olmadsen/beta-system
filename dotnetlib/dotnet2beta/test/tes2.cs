using System;
using System.Reflection;

public class test {
    public static void  Main(System.String[] args)
      {	 
	Type t = typeof(System.Byte[][]);
        Console.WriteLine("System.Byte[][] elementtype: " + t.GetElementType().ToString());
        Console.WriteLine("System.Byte[][] elementtype is array?: " + t.GetElementType().IsArray.ToString());
      }

}
