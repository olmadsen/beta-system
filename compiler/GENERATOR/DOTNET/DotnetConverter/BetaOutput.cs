namespace beta.converter
  {
    using System;
    
    public class BetaOutput
      {
	internal int indentlevel = 0;
	
	public System.IO.TextWriter output;
	
	internal System.IO.FileInfo entry;
	internal System.IO.FileInfo existing = null;
	
	public BetaOutput(System.String betalib, System.String ns, System.String cls, int overwrite, System.IO.TextWriter outstream)
	  {
	    entry = new System.IO.FileInfo(betalib + "/dotnetlib/" + ns + "/" + cls + ".bet");
	    if (System.IO.File.Exists(entry.FullName)) {
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
	    System.IO.Directory.CreateDirectory(entry.Directory.Name);
	    if (outstream != null) {
	      output = outstream;
	    } else {
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
	    System.Console.Error.WriteLine("Output file:\n\t\"" + entry.FullName + "\"");
	    if (existing != null) {
	      System.Console.Error.WriteLine("NOTICE: Not overwriting existing\n\t\"" + existing.FullName + "\"");
	      System.Console.Error.WriteLine("\tUse -f or -F option if overwrite desired.");
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
	    output.WriteLine(line);
	  }
		
	public virtual void  nl()
	  {
	    output.WriteLine("");
	  }
		
	public virtual System.String mapReserved(System.String word)
	  {
	    // Map declarations and dynamic references
	    System.String prefix = "";
	    // Extract declarator prefix
	    if (word.StartsWith("^"))
	      {
		prefix = "^";
		word = word.Substring(1, (word.Length) - (1));
	      }
	    else if (word.StartsWith("[0]^"))
	      {
		prefix = word.Substring(0, (4) - (0));
		word = word.Substring(4, (word.Length) - (4));
	      }
	    else if (word.StartsWith("@"))
	      {
		return word;
	      }
	    else if (word.StartsWith("[0]@"))
	      {
		return word;
	      }
			
	    // compare word against grammatically reserved BETA words
	    if (word.ToUpper().Equals("enter".ToUpper()))
	      {
		return prefix + "Dotnet" + word;
	      }
	    else if (word.ToUpper().Equals("exit".ToUpper()))
	      {
		return prefix + "Dotnet" + word;
	      }
	    else if (word.ToUpper().Equals("do".ToUpper()))
	      {
		return prefix + "Dotnet" + word;
	      }
	    else if (word.ToUpper().Equals("for".ToUpper()))
	      {
		return prefix + "Dotnet" + word;
	      }
	    else if (word.ToUpper().Equals("repeat".ToUpper()))
	      {
		return prefix + "Dotnet" + word;
	      }
	    else if (word.ToUpper().Equals("if".ToUpper()))
	      {
		return prefix + "Dotnet" + word;
	      }
	    else if (word.ToUpper().Equals("restart".ToUpper()))
	      {
		return prefix + "Dotnet" + word;
	      }
	    else if (word.ToUpper().Equals("inner".ToUpper()))
	      {
		return prefix + "Dotnet" + word;
	      }
	    else if (word.ToUpper().Equals("suspend".ToUpper()))
	      {
		return prefix + "Dotnet" + word;
	      }
	    else if (word.ToUpper().Equals("code".ToUpper()))
	      {
		return prefix + "Dotnet" + word;
	      }
	    else if (word.ToUpper().Equals("then".ToUpper()))
	      {
		return prefix + "Dotnet" + word;
	      }
	    else if (word.ToUpper().Equals("else".ToUpper()))
	      {
		return prefix + "Dotnet" + word;
	      }
	    else if (word.ToUpper().Equals("tos".ToUpper()))
	      {
		return prefix + "Dotnet" + word;
	      }
	    else if (word.ToUpper().Equals("this".ToUpper()))
	      {
		return prefix + "Dotnet" + word;
	      }
	    else if (word.ToUpper().Equals("or".ToUpper()))
	      {
		return prefix + "Dotnet" + word;
	      }
	    else if (word.ToUpper().Equals("xor".ToUpper()))
	      {
		return prefix + "Dotnet" + word;
	      }
	    else if (word.ToUpper().Equals("div".ToUpper()))
	      {
		return prefix + "Dotnet" + word;
	      }
	    else if (word.ToUpper().Equals("mod".ToUpper()))
	      {
		return prefix + "Dotnet" + word;
	      }
	    else if (word.ToUpper().Equals("and".ToUpper()))
	      {
		return prefix + "Dotnet" + word;
	      }
	    else if (word.ToUpper().Equals("not".ToUpper()))
	      {
		return prefix + "Dotnet" + word;
	      }
	    else if (word.ToUpper().Equals("none".ToUpper()))
	      {
		return prefix + "Dotnet" + word;
	      }
			
	    // Compare word against basic patterns
	    if (word.ToUpper().Equals("integer".ToUpper()))
	      {
		return prefix + "Dotnet" + word;
	      }
	    else if (word.ToUpper().Equals("shortInt".ToUpper()))
	      {
		return prefix + "Dotnet" + word;
	      }
	    else if (word.ToUpper().Equals("char".ToUpper()))
	      {
		return prefix + "Dotnet" + word;
	      }
	    else if (word.ToUpper().Equals("boolean".ToUpper()))
	      {
		return prefix + "Dotnet" + word;
	      }
	    else if (word.ToUpper().Equals("false".ToUpper()))
	      {
		return prefix + "Dotnet" + word;
	      }
	    else if (word.ToUpper().Equals("true".ToUpper()))
	      {
		return prefix + "Dotnet" + word;
	      }
	    else if (word.ToUpper().Equals("real".ToUpper()))
	      {
		return prefix + "Dotnet" + word;
	      }
	    else if (word.ToUpper().Equals("int8".ToUpper()))
	      {
		return prefix + "Dotnet" + word;
	      }
	    else if (word.ToUpper().Equals("int8u".ToUpper()))
	      {
		return prefix + "Dotnet" + word;
	      }
	    else if (word.ToUpper().Equals("int16".ToUpper()))
	      {
		return prefix + "Dotnet" + word;
	      }
	    else if (word.ToUpper().Equals("int16u".ToUpper()))
	      {
		return prefix + "Dotnet" + word;
	      }
	    else if (word.ToUpper().Equals("int32".ToUpper()))
	      {
		return prefix + "Dotnet" + word;
	      }
	    else if (word.ToUpper().Equals("int32u".ToUpper()))
	      {
		return prefix + "Dotnet" + word;
	      }
	    else if (word.ToUpper().Equals("int64".ToUpper()))
	      {
		return prefix + "Dotnet" + word;
	      }
	    else if (word.ToUpper().Equals("int64u".ToUpper()))
	      {
		return prefix + "Dotnet" + word;
	      }
			
	    // Compare against other patterns that may confuse 
	    if (word.Equals("File"))
	      {
		return prefix + "Dotnet" + word;
	      }
			
	    // Not reserved
	    return prefix + word;
	  }
		
	public virtual void  putPatternBegin(System.String className, System.String superClass)
	  {
	    put(mapReserved(className) + ": ");
	    if (superClass == null || superClass.Equals("Object"))
	      {
		put("ExternalClass");
	      }
	    else
	      {
		put(superClass);
	      }
	    nl();
	    indent(+ 2);
	    indent();
	    put("(#");
	    indent(+ 3);
	  }
		
	public virtual void  putHeader(System.String namespaceName, System.String className, System.String superClass, System.Object[] includes)
	  {
	    putln("ORIGIN '~beta/basiclib/betaenv';");
	    if (includes != null)
	      {
		for (int i = 0; i < includes.Length; i++)
		  {
		    putln("INCLUDE '~beta/dotnetlib/" + (System.String) includes[i] + "';");
		  }
		;
	      }
	    ;
	    putln("--LIB: attributes--\n");
	    putln("(* .NET " + className + " class.");
	    putln(" *)");
	    putPatternBegin(className, superClass);
	  }
		
	public virtual void  putField(System.String name, System.String type, bool isStatic)
	  {
	    if (isStatic)
	      {
		commentline("STATIC:");
	      }
	    putln(mapReserved(name) + ": " + mapReserved(type) + ";");
	  }
		
	public virtual void  putConstant(System.String name, System.String value_Renamed)
	  {
	    putln(mapReserved(name) + ": (# exit " + value_Renamed + " #);");
	  }
		
	public virtual void  putMethod(System.String name, System.String mangledName, System.String[] parameters, System.String returnType, bool isStatic)
	  {
	    System.String proctype = (name.Equals("_init"))?"cons":((isStatic)?"static_proc":"proc");
	    if (mangledName != null)
	      {
		putln(mangledName + ": " + proctype + " " + comment(((name.Equals("_init"))?"constructor":name)));
	      }
	    else
	      {
		putln(mapReserved(name) + ": " + proctype);
	      }
			
	    indent(+ 2);
	    indent(); put("(# ");
	    if (returnType != null)
	      {
		put("result: " + mapReserved(returnType) + ";");
	      }
	    nl();
	    indent(+ 3);
	    if (parameters.Length > 0)
	      {
		int n = 0;
		for (int i = 0; i < parameters.Length; i++)
		  {
		    putln("arg" + (++n) + ": " + mapReserved(parameters[i]) + ";");
		  }
		indent(- 3);
		indent();
		put("enter (");
		bool comma = false;
		n = 0;
		for (int i = 0; i < parameters.Length; i++)
		  {
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
	    if (mangledName != null && !name.Equals("_init"))
	      {
		indent();
		put("do '" + name + "' -> procname;");
		nl();
	      }
	    if (returnType != null)
	      {
		indent(); put("exit result");
		if (returnType.StartsWith("^"))
		  put("[]");
		nl();
	      }
	    putln("#);");
	    indent(- 2);
	  }
		
	public virtual void  putTrailer(System.String resolution, System.String namespaceName, System.String className)
	  {
	    indent(- 3);
	    putln("do '[" + resolution + ']' + namespaceName + '/' + className + "' -> className;");
	    putln("INNER;");
	    putln("#);\n");
	    indent(- 2);
	  }
		
	public virtual void  close()
	  {
	    if (output != System.Console.Out)
	      output.Close();
	  }
      }
  }
