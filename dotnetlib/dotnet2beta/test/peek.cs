using System;
using System.IO;
using System.Threading;

public class test {
    public static void  Main(System.String[] args)
      {	 
	Console.Write("Enter some text: ");
	// first peek will block!!
	while (Console.In.Peek() == -1){ 
	  // we never get here
	  Console.Write('.'); Thread.Sleep(500);
	}
	Console.WriteLine("Input 1 available: " + Console.ReadLine());

	Console.Write("Enter some more text: ");
	// second peek is non-blocking, but never detects input!!
	while (Console.In.Peek() == -1){ 
	  // we never get out of here
	  Console.Write('.'); Thread.Sleep(500);
	}
	Console.WriteLine("Input 2 available: " + Console.ReadLine());
      }
}
