using System;
using System.Reflection;
 
class GetVersion
{
    public static void  Main(System.String[] args)
      {  
        if (args.Length>0){
	  Assembly ass = Assembly.LoadWithPartialName(args[0]);
	  try {
	    System.Console.WriteLine("Version of {0} is {1}", args[0], ass.GetName().Version);
	  } catch{
	    Console.WriteLine("Illegal assembly name: {0}", args[0]);
	  }
	} else {
	  Console.WriteLine("usage: getversion assembly");
        }
      }
}
