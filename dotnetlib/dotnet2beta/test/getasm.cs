using System;
using System.Runtime.InteropServices;
using System.Reflection;
using System.IO;

public class getasm {
    public static void  Main(System.String[] args)
      {	 
	Console.WriteLine("Hello!");
	if (args.Length>0){
	  Console.WriteLine(args[0] + " codebase: ");
	  Console.WriteLine(codebase(args[0]));
	}
      }

    static bool trace = false;

    public static String codebase(String cls)
      {
	Type t = Type.GetType(cls);
	if (t != null){
	  return t.Assembly.CodeBase;
	} else {
	  try {
	    String dir = RuntimeEnvironment.GetRuntimeDirectory();
	    Assembly asm;
	    // First try obvious prefix as assembly
	    String firsttry = cls.Substring(0,cls.LastIndexOf('.'));
	    if (trace) Console.WriteLine("[  trying " + firsttry + "]");
	    asm = Assembly.LoadFile(dir + Path.DirectorySeparatorChar + firsttry + ".dll");
	    if (asm != null){
	      if (asm.GetType(cls) != null){
		if (trace) Console.WriteLine("   FOUND!");
		return asm.CodeBase;
	      }
	    }
	    // Then search all files in system runtime directory (:-(
	    String[] dlls = Directory.GetFiles(dir, "*.dll");
	    for (int i=0; i<dlls.Length; i++){
	      if (trace) Console.WriteLine("  [searching " + dlls[i] + "]");
	      try {
		asm = Assembly.LoadFile(dlls[i]);
		if (asm != null){
		  if (asm.GetType(cls) != null){
		    if (trace) Console.WriteLine("  FOUND!");
		    return asm.CodeBase;
		  }
		}
	      } catch (Exception) {
	      }
	    }
	    return "";
	  } catch (Exception e) {
	    Console.WriteLine(e.Message);
	    Console.WriteLine(e.StackTrace);
	    return "";
	  }
	} 
      }
}
