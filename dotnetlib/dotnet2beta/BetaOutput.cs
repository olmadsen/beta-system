namespace beta.converter
  {
    using System;
	
    public class BetaOutput
      {
	internal int indentlevel = 0;
	internal bool trace = false;
		
	public System.IO.TextWriter output;
		
	internal System.IO.FileInfo entry;
	internal System.IO.FileInfo existing = null;
		
	public BetaOutput(System.String betalib, 
			  System.String resolution, 
			  System.String ns, 
			  System.String cls, 
			  System.String supNs, 
			  System.String sup, 
			  int overwrite, 
			  System.IO.TextWriter outstream)
	  {
			
	    openStream(betalib, ns, "_" + cls, overwrite, outstream);
	    if (output != null)
	      putWrapper(resolution, ns, cls, supNs, sup);
	    openStream(betalib, ns, cls, overwrite, outstream);
	  }
		
	internal virtual void  openStream(System.String betalib, 
					  System.String ns, System.String cls, 
					  int overwrite, 
					  System.IO.TextWriter outstream)
	  {
	    entry = new System.IO.FileInfo(betalib + "/dotnetlib/" + ns + "/" + cls + ".bet");
	    if (System.IO.File.Exists(entry.FullName) || System.IO.Directory.Exists(entry.FullName)) {
	      if (overwrite == - 1) {
		// Ignore if already converted
		output = null;
		return ;
	      }
	      if (overwrite == 0) {
		existing = entry;
		entry = new System.IO.FileInfo(entry.FullName + ".new");
	      }
	    }
	    if (trace){
	      System.Console.Error.Write("Creating directory " + entry.Directory.FullName + "\n");
	    }
	    System.IO.Directory.CreateDirectory(entry.Directory.FullName);
	    if (outstream != null) {
	      output = outstream;
	    }
	    else
	      {
		if (output != null) {
		  output.Close();
		}
		output = new System.IO.StreamWriter(new System.IO.FileStream(entry.FullName, System.IO.FileMode.Create));
	      }
	  }
		
		
	public virtual void  reportFileName()
	  {
	    if (output == null) {
	      // class ignored
	      return ;
	    }
	    if (output == System.Console.Out) {
	      // no file involved
	      return ;
	    }
	    System.Console.Error.Write("Output file:\n\t\"" + entry.FullName + "\"" + "\n");
	    if (existing != null) {
	      System.Console.Error.Write("NOTICE: Not overwriting existing\n\t\"" + existing.FullName + "\"" + "\n");
	      System.Console.Error.Write("\tUse -f or -F option if overwrite desired." + "\n");
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
		
	public virtual System.String comment(System.String cmt)
	  {
	    return "(* " + cmt + " *)";
	  }
		
	public virtual void  commentline(System.String cmt)
	  {
	    putln(comment(cmt));
	  }
		
	public virtual void  fixme(System.String msg)
	  {
	    comment("FIXME: " + msg);
	  }
		
	public virtual void  put(System.String txt)
	  {
	    output.Write(txt);
	  }
		
		
	public virtual void  putln(System.String line)
	  {
	    indent();
	    output.Write(line); 
	    nl();
	  }
		
	public virtual void  nl()
	  {
	    output.Write("\n");
	  }
		
	public virtual System.String mapReserved(System.String word)
	  {
	    // Map declarations and dynamic references
	    System.String prefix = "";
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
	    switch (word.ToLower()){
	    case "File":
	    case "Hashtable":
	    case "Class":
	    case "Process":
	      return prefix + "Dotnet" + word;
	    }
	    // Not reserved
	    return prefix + word;
	  }
		
	public virtual void  putPatternBegin(System.String className, System.String superClass)
	  {
	    if (className.Equals("Object")) {
	      // Special case: Must be *declared* with special name,
	      // but all parameters of type Object should remain Object
	      // (for compatibility with BETA Object)
	      put("DotnetObject: ");
	    }
	    else
	      {
		put(mapReserved(className) + ": ");
	      }
	    if (superClass == null || superClass.Equals("Object")) {
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
		
	public virtual void  putWrapper(System.String resolution, 
					System.String namespaceName, 
					System.String className, 
					System.String superNs, 
					System.String superClass)
	  {
	    putln("ORIGIN '~beta/basiclib/betaenv';");
	    if ((superClass != null) && !superClass.Equals("Object")) {
	      // Include non-wrapper version of superclass
	      putln("INCLUDE '~beta/dotnetlib/" + superNs + "/" + superClass + "';");
	    }
	    ;
	    putln("--LIB: attributes--\n");
	    putln("(* Dotnet " + className + " class declaration.");
	    putln(" * This wrapper is needed to prevent circular fragment INCLUDE.");
	    putln(" * See " + className + ".bet for members.");
	    putln(" *)");
	    putPatternBegin("_" + className, superClass);
	    nl();
	    putTrailer(resolution, namespaceName, className);
	  }
		
	public virtual void  putHeader(System.String namespaceName, System.String className, System.Object[] includes)
	  {
	    putln("ORIGIN '" + "_" + className + "';");
	    if (includes != null) {
	      for (int i = 0; i < includes.Length; i++) {
		putln("INCLUDE '~beta/dotnetlib/" + (System.String) includes[i] + "';");
	      }
	      ;
	    }
	    ;
	    putln("--LIB: attributes--\n");
	    putln("(* .NET " + className + " class. *)");
	    putPatternBegin(className, "_" + className);
	  }
		
	public virtual void  putField(System.String name, System.String type, bool isStatic)
	  {
	    if (isStatic) {
	      commentline("STATIC:");
	    }
	    putln(mapReserved(name) + ": " + mapReserved(type) + ";");
	  }
		
	public virtual void  putConstant(System.String name, System.String value_Renamed)
	  {
	    putln(mapReserved(name) + ": (# exit " + value_Renamed + " #);");
	  }
		
	public virtual void  putMethod(System.String name, 
				       System.String mangledName, 
				       System.String[] parameters, 
				       System.String returnType, 
				       bool isStatic) {
	  bool isConstructor = name.Equals("_init");
	  System.String proctype = (isConstructor)?"cons":((isStatic)?"static_proc":"proc");
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
	    for (int i = 0; i < parameters.Length; i++) {
	      putln("arg" + (++n) + ": " + mapReserved(parameters[i]) + ";");
	    }
	    indent(- 3);
	    indent();
	    put("enter (");
	    bool comma = false;
	    n = 0;
	    for (int i = 0; i < parameters.Length; i++) {
	      if (comma)
		put(", ");
	      else
		comma = true;
	      put("arg" + (++n));
	      if (parameters[i].StartsWith("^"))
		put("[]");
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
		
	public virtual void  putTrailer(System.String resolution, 
					System.String namespaceName, 
					System.String className)
	  {
	    indent(- 3);
	    putln("do '[" + resolution + ']' + namespaceName + '.' + className + "' -> className;");
	    putln("INNER;");
	    putln("#);\n");
	    indent(- 2);
	  }
		
	public virtual void  close()
	  {
	    if (output != System.Console.Out) {
	      output.Close();
	    }
	  }
      }
  }
