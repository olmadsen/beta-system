using System;
using System.Runtime.InteropServices;
using System.Reflection;
using System.IO;

public class GetType {
    public static void  Main(System.String[] args)
      {  
        if (args.Length>0){
          Console.WriteLine(args[0] + ": ");
          Type t = gettype(args[0]);
          if (t != null){
	    Console.WriteLine("Fullname: ");
            Console.WriteLine(t.Assembly.FullName);
	    Console.WriteLine("CodeBase: ");
            Console.WriteLine(t.Assembly.CodeBase);
          } else {
            Console.WriteLine("Type " + args[0] + " not found.");
          }
        }
      }

    static bool trace_runtime = false;
    
    internal static Type gettype(String cls)
      {
        // First try Type.GetType.
        // Searches in the calling object's assembly, then in the mscorlib.dll 
        Type t = Type.GetType(cls);
        if (t != null) return t;
        
        // Then try by loading DLLs
        // Can I search the GAC instead programmatically?
        // Or is it better to exec "gacutil -l" and analyze output?
        String dir = RuntimeEnvironment.GetRuntimeDirectory();
        Assembly asm;
        // First try obvious prefix as assembly
        int dotpos = cls.LastIndexOf('.');
        if (dotpos>0){
          String firsttry = cls.Substring(0,dotpos);
          if (trace_runtime) Console.WriteLine("[  first try: " + firsttry + "]");
          try {
            asm = Assembly.LoadFile(dir + Path.DirectorySeparatorChar + firsttry + ".dll");
            t = asm.GetType(cls);
            if (t != null){
              if (trace_runtime) Console.WriteLine("   FOUND!");
              return t;
            }
          } catch (Exception) {
            // Ignore error and go on
          }
        }
        
        // Then search all files in system runtime directory (:-(
        String[] dlls = Directory.GetFiles(dir, "*.dll");
        for (int i=0; i<dlls.Length; i++){
          if (dlls[i].EndsWith("mscorlib.dll")) continue; // mscorlib already examined
          if (trace_runtime) Console.WriteLine("  [searching " + dlls[i] + "]");
          try {
            asm = Assembly.LoadFile(dlls[i]);
            t = asm.GetType(cls);
            if (t != null){
              if (trace_runtime) Console.WriteLine("  FOUND!");
              return t;
            }
          } catch (Exception) {
            // Ignore error and go on
          }
        }
        
        // Giving up
        return null;
      }
}
