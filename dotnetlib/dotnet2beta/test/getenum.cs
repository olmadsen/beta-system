using System;
using System.Runtime.InteropServices;
using System.Reflection;
using System.IO;

public class GetType {
  public static void  Main(System.String[] args)
    {  
      if (args.Length>0){
	Console.WriteLine(args[0] + ": ");
	displayEnum(args[0]);
      }
    }
  
  internal static void displayEnum(String cls)
    {
      Type t = Type.GetType(cls);
      if (!t.IsEnum) {
	Console.WriteLine("Not an Enum");
	return;
      }
      FieldInfo[] fieldlist;
      fieldlist = t.GetFields(BindingFlags.Instance 
			      | BindingFlags.Public 
			      | BindingFlags.Static 
			      | BindingFlags.DeclaredOnly);
      foreach (FieldInfo f in fieldlist){
	bool isStatic = f.IsStatic;
	bool isLiteral = f.IsLiteral; 
	if (isStatic && isLiteral){
	  Console.WriteLine(f.Name + ": " + f.GetValue(null));
	}
      }
    }
}
