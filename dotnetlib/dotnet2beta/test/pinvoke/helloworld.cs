using System;
using System.Text;

public class helloworld
  {
    public static void Main(String[] args)
      {  
        String msg = null;
	hellowrapper.hello("C#");
	hellowrapper.gethello(ref msg);
	Console.WriteLine(msg);
      }
  }
