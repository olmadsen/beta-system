using System;
using System.IO;
using System.Collections;
using System.Collections.Specialized;

namespace beta.converter
  {
    public class BetaOutput
      {
	internal bool trace = false;
	internal bool do_flush = false;
		
	internal int indentlevel = 0;

	internal String thisClass;

	public TextWriter output;
		
	internal FileInfo entry;
	internal FileInfo existing = null;

	internal static IDictionary needs_prefix;
	internal static IDictionary use_wrapper_super;

	static BetaOutput(){
	  // Read %BETALIB%/dotnetlib/conversion-rules.txt
	  // and collect information into the two static
	  // dictionaries needs_prefix and use_wrapper_super.
	  needs_prefix      = new ListDictionary();
	  use_wrapper_super = new ListDictionary();
	  String fname = Environment.GetEnvironmentVariable("BETALIB") 
	    + "/dotnetlib/conversion-rules.txt";
	  try 
	    {
	      // Create an instance of StreamReader to read from a file.
	      // The using statement also closes the StreamReader.
	      using (StreamReader sr = new StreamReader(fname)){
		String line;
		while ((line = sr.ReadLine()) != null){
		  // Using .NET Regex seems an overkill...
		  String match;
		  String value;
		  match = "needs-prefix: ";
		  if (line.StartsWith(match)){
		    value = line.Substring(match.Length);
		    needs_prefix[value] = value;
		    // Console.Error.Write("needs-prefix --> " + value + "\n");
		    continue;
		  }
		  match = "use-wrapper-super: ";
		  if (line.StartsWith(match)){
		    value = line.Substring(match.Length);
		    use_wrapper_super[value] = value;
		    // Console.Error.Write("use_wrapper_super --> " + value + "\n");
		    continue;
		  }
		}
	      }
	    }
	  catch (Exception) 
	    {
	      // Ignore configuration file reading.
	      // Console.Error.Write("Configuration file " + fname + " could not be read:\n");
	      // Console.Write(e.Message + "\n");
	    }
	  
	}
		
	public BetaOutput(String betalib, 
			  String resolution, 
			  String ns, 
			  String cls, 
			  String supNs, 
			  String sup, 
			  int overwrite, 
			  TextWriter outstream,
			  bool isValue)
	  {
	    // Open wrapper
	    openStream(betalib, ns, "_" + cls, overwrite, outstream);
	    if (output != null) putWrapper(resolution, ns, cls, supNs, sup, isValue);
	    // Open non-wrapper
	    openStream(betalib, ns, cls, overwrite, outstream);
	  }

	internal virtual void  openStream(String betalib, 
					  String ns, String cls, 
					  int overwrite, 
					  TextWriter outstream)
	  {
	    entry = new FileInfo(betalib + "/dotnetlib/" + ns + "/" + cls + ".bet");
	    if (File.Exists(entry.FullName) || Directory.Exists(entry.FullName)) {
	      if (overwrite == - 1) {
		// Ignore if already converted
		output = null;
		return;
	      }
	      if (overwrite == 0) {
		existing = entry;
		entry = new FileInfo(entry.FullName + ".new");
	      }
	    }
	    if (trace){
	      Console.Error.Write("Creating directory " + entry.Directory.FullName + "\n");
	    }
	    Directory.CreateDirectory(entry.Directory.FullName);
	    if (outstream != null) {
	      output = outstream;
	    } else {
	      if (output != null) {
		output.Close();
	      }
	      if (trace){
		Console.Error.Write("Creating file " + entry.FullName + "\n");
	      }
	      output = new StreamWriter(new FileStream(entry.FullName, FileMode.Create));
	    }
	  }
		
		
	public virtual void  reportFileName()
	  {
	    if (output == null) {
	      // class ignored
	      return ;
	    }
	    if (output == Console.Out) {
	      // no file involved
	      return ;
	    }
	    Console.Error.Write("    --> \"" + entry.FullName + "\"" + "\n");
	    if (existing != null) {
	      Console.Error.Write("NOTICE:\n\tNot overwriting existing\n\t\"" + existing.FullName + "\"" + "\n");
	      Console.Error.Write("\tUse -f or -F option if overwrite desired." + "\n");
	    }
	  }
		
	public virtual void  indent()
	  {
	    for (int i = 0; i < indentlevel; i++)
	      put(" ");
	  }
		
	public virtual void  indent(int delta)
	  {
	    indentlevel += delta;
	  }
		
	public virtual String comment(String cmt)
	  {
	    return "(* " + cmt + " *)";
	  }
		
	public virtual void  commentline(String cmt)
	  {
	    putln(comment(cmt));
	  }
		
	public virtual void  fixme(String msg)
	  {
	    comment("FIXME: " + msg);
	  }
		
	public virtual void  put(String txt)
	  {
	    output.Write(txt);
	    if (do_flush) output.Flush();
	  }
		
		
	public virtual void  putln(String line)
	  {
	    indent();
	    output.Write(line); 
	    nl();
	  }
		
	public virtual void  nl()
	  {
	    output.Write("\n");
	  }
		
	public virtual String mapReserved(String word)
	  {
	    // Map declarations and dynamic references
	    String prefix = "";
	    // Extract declarator prefix
	    if (word.StartsWith("^")) {
	      prefix = "^";
	      word = word.Substring(1, (word.Length) - (1));
	    } else if (word.StartsWith("[0]^")) {
	      prefix = word.Substring(0, (4) - (0));
	      word = word.Substring(4, (word.Length) - (4));
	    } else if (word.StartsWith("@")) {
	      return word;
	    } else if (word.StartsWith("[0]@")) {
	      return word;
	    }
			
	    // compare word against grammatically reserved BETA words
	    switch (word.ToLower()){
	    case "enter":
	    case "exit":
	    case "do":
	    case "for":
	    case "repeat":
	    case "if":
	    case "restart":
	    case "inner":
	    case "suspend":
	    case "code":
	    case "then":
	    case "else":
	    case "tos":
	    case "this":
	    case "or":
	    case "xor":
	    case "div":
	    case "mod":
	    case "and":
	    case "not":
	    case "none":
	      return prefix + "Dotnet" + word;
	    }
			
	    // Compare word against basic patterns
	    switch(word.ToLower()){
	    case "integer":
	    case "shortInt":
	    case "char":
	    case "boolean":
	    case "false":
	    case "true":
	    case "real":
	    case "int8":
	    case "int8u":
	    case "int16":
	    case "int16u":
	    case "int32":
	    case "int32u":
	    case "int64":
	    case "int64u":
	      return prefix + "Dotnet" + word;
	    }
			
	    // Compare against other patterns that may confuse 
	    if (needs_prefix[word] != null){
	      return prefix + "Dotnet" + word;
	    }
	    // Not reserved
	    return prefix + word;
	  }

	public virtual String mapDeclaration(String className)
	  {
	    if (className.Equals("Object")) {
	      // Special case: Must be *declared* with special name,
	      // but all parameters of type Object should remain Object
	      // (for compatibility with BETA Object)
	      return "DotnetObject";
	    } else {
	      return mapReserved(className);
	    }
	  }
		
	public virtual void  putPatternBegin(String className, String superClass)
	  {
	    put(mapDeclaration(className) + ": ");
	    if (superClass == null || superClass.Equals("Object") || superClass.Equals("_Object")) {
	      put("ExternalClass");
	    }
	    else
	      {
		put(mapReserved(superClass));
	      }
	    nl();
	    indent(+ 2);
	    indent();
	    put("(#");

	    indent(+ 3);
	  }
		
	public virtual void  putWrapper(String resolution, 
					String namespaceName, 
					String className, 
					String superNs, 
					String superClass,
					bool isValue)
	  {
	    String dotNs = namespaceName.Replace('/', '.');
	    bool use_wrapper = (use_wrapper_super[dotNs + "." + className] != null);
	    putln("ORIGIN '~beta/basiclib/betaenv';");
	    if ((superClass != null) && !superClass.Equals("Object")) {
	      if (use_wrapper){
		// Include wrapper version of superclass
		putln("INCLUDE '~beta/dotnetlib/" + superNs + "/" + "_" + superClass + "' (* Cannot use non-wrapper *);");
	      } else {
		// Include non-wrapper version of superclass
		putln("INCLUDE '~beta/dotnetlib/" + superNs + "/" + superClass + "';");
	      }
	    }
	    ;
	    putln("--LIB: attributes--\n");
	    putln("(* Dotnet " + className + " class declaration.");
	    putln(" * This wrapper is needed to prevent circular fragment INCLUDE.");
	    putln(" * See " + className + ".bet for members.");
	    putln(" *)");
	    if (use_wrapper){
	      putPatternBegin("_" + className, "_" + superClass);
	    } else {
	      putPatternBegin("_" + className, superClass);
	    }
	    nl();
	    putTrailer(resolution, dotNs, className, isValue);
	  }
		
	public virtual void  putHeader(String namespaceName, String className, String[] includes)
	  {
	    thisClass = className;
	    putln("ORIGIN '" + "_" + className + "';");
	    putln("ON 19 (* Disable warnings about runtime qualification tests *);");
	    if (includes != null) {
	      foreach (String include in includes) {
		putln("INCLUDE '~beta/dotnetlib/" + include + "';");
	      }
	      ;
	    }
	    ;
	    putln("--LIB: attributes--\n");
	    putln("(* .NET " + className + " class. *)");
	    putPatternBegin(className, "_" + className);
	  }
		
	public virtual void  putField(String name, String type, bool isStatic)
	  {
	    if (isStatic) {
	      commentline("STATIC:");
	    }
	    putln(mapReserved(name) + ": " + mapReserved(type) + ";");
	  }
		
	public virtual void  putConstant(String name, int val)
	  {
	    putln(mapReserved(name) + ":");
	    indent(+2);
	    putln("(# exit " + val + " #);");
	    indent(-2);
	  }
		
	public virtual void  putConstant(String name, long val)
	  {
	    // Cannot express int64 literal directly in BETA source, so we must use
	    // exponential notation
	    putln(mapReserved(name) + ":");
	    indent(+2);
	    putln("(# exit " + val.ToString("E") + " #);");
	    indent(-2);
	  }
		
	public virtual void  putMethod(String name, 
				       String mangledName, 
				       String[] parameters, 
				       String returnType, 
				       bool isStatic) {
	  bool isConstructor = name.Equals("_init");
	  String proctype = (isConstructor)?"cons":((isStatic)?"static_proc":"proc");
	  if (mangledName != null) {
	    putln(mangledName + ": " + proctype + " " + comment(((isConstructor)?"constructor":name)));
	  } else {
	    putln(mapReserved(name) + ": " + proctype);
	  }
			
	  indent(+ 2);
	  indent(); put("(# ");
	  if (returnType != null) {
	    put("result: " + mapReserved(returnType) + ";");
	  }
	  nl();
	  indent(+ 3);
	  if (parameters.Length > 0) {
	    int n = 0;
	    foreach (String param in parameters) {
	      putln("arg" + (++n) + ": " + param + ";");
	    }
	    indent(- 3);
	    indent();
	    put("enter (");
	    bool comma = false;
	    n = 0;
	    foreach (String param in parameters) {
	      if (comma)
		put(", ");
	      else
		comma = true;
	      put("arg" + (++n));
	      if (param.StartsWith("^") || param.StartsWith("[0]") /* using Ref2Rep */){
		put("[]");
	      }
	    }
	    put(")");
	    nl();
	    indent(+ 3);
	  }
	  indent(- 3);
	  if ((mangledName != null && !isConstructor) || !name.Equals(mapReserved(name))) {
	    indent();
	    put("do '" + name + "' -> procname;");
	    nl();
	  }
	  if (returnType != null) {
	    indent(); put("exit result");
	    if (returnType.StartsWith("^"))
	      put("[]");
	    nl();
	  }
	  putln("#);");
	  indent(- 2);
	}
		
	public virtual void  putTrailer(String resolution, 
					String namespaceName, 
					String className, 
					bool isValue)
	  {
	    indent(- 3);
	    indent();
	    put("do '");
	    if (isValue) put("@valuetype ");
	    put("[" + resolution + ']' + namespaceName + '.' + className.Replace('+', '/') + "' -> className;");
	    // Nested classes are indicated by '/' in IL, but by '+' in the type system!
	    nl();
	    putln("INNER;");
	    putln("#);\n");
	    indent(- 2);
	  }

	public virtual void putCaster()
	  { 
	    putln("(* Utility function to ease casting to fully specified class. *)");
	    putln("as" + thisClass + ":");
	    indent(+ 2);
	    putln("(# _" + thisClass[0] + ": ^_" + thisClass + ";");
	    indent(+ 3);
	    putln(thisClass[0] + ": ^" + mapDeclaration(thisClass) + ";");
	    indent(- 3);
	    putln("enter _" + thisClass[0] + "[]");
	    putln("do _" + thisClass[0] + "[]->" + thisClass[0] + "[]" + ";");
	    putln("exit " + thisClass[0] + "[]");
	    putln("#);");
	    indent(- 2);
	  }
		
	public virtual void  close(bool doCaster)
	  {
	    if (doCaster) putCaster();
	    if (output != Console.Out) {
	      output.Close();
	    }
	  }
      }
  }
