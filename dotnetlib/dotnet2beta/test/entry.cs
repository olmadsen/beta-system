using System;
using System.IO;

public class test {
    public static void  Main(System.String[] args)
      {	 
	Console.WriteLine("Testing fisk timestamp!");
	FileInfo f = new FileInfo("fisk");
	Console.WriteLine(f.LastWriteTime.ToFileTime().ToString());
	return;
      }

}
