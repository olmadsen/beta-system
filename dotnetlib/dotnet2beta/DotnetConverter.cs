namespace beta.converter
  {
    using System;
	
    class DotnetConverter
      {
	internal System.Collections.IDictionary includes;
	internal static System.Collections.IDictionary converted;
		
	public DotnetConverter()
	  {
	    includes = new System.Collections.Specialized.ListDictionary();
	  }
	static DotnetConverter()
	  {
	    converted = new System.Collections.Specialized.ListDictionary();
	  }

	internal bool trace = true;
		
	internal BetaOutput beta;
	internal System.Type thisClass;
	internal System.String className;
	internal System.String namespaceName;
	internal System.String superClass;
	internal System.String superNs;
		
	internal static void  usage(System.String msg)
	  {
	    if (msg != null){
	      System.Console.Error.WriteLine("\n" + msg + "\n");
	    }
	    System.Console.Error.WriteLine("Usage:\n");
	    System.Console.Error.WriteLine("dotnet2beta [-h][-f][-F][-] <dotnet class name>");
	    System.Console.Error.WriteLine(" e.g.   dotnet2beta System.String\n");
	    System.Console.Error.WriteLine("Output files will be placed in BETALIB/dotnetlib in a directory");
	    System.Console.Error.WriteLine("structure corresponding to the namespace of the class.");
	    System.Console.Error.WriteLine(" e.g.   "
					   + Environment.GetEnvironmentVariable("BETALIB") 
					   + "/dotnetlib/System/String.bet\n");
	    System.Console.Error.WriteLine("Options:");
	    System.Console.Error.WriteLine("   -h  Display this help");
	    System.Console.Error.WriteLine("   -f  Force overwrite of existing output file");
	    System.Console.Error.WriteLine("   -F  Force overwrite of existing output file AND files for refered classes");
	    System.Console.Error.WriteLine("   -   Output to terminal instead of file");
	    System.Console.Error.WriteLine("");
	    System.Environment.Exit((msg == null)?0:1);
	  }
		
	[STAThread]
	  public static void  Main(System.String[] args)
	  {	    
	    int overwrite = 0;
	    System.IO.TextWriter output = null;
	    if (args.Length >= 1)
	      {
		for (int i = 0; i < args.Length; i++){
		  if (args[i].StartsWith("-")){
		    switch (args[i]){
		    case "-h":
		      usage(null);
		      break;
		    case "-f":
		      overwrite = 1;
		      break;
		    case "-F":
		      overwrite = 2;
		      break;
		    case "-":
		      output = System.Console.Out;
		      break;
		    default:
		      usage("Illegal option: " + args[i]);
		      break;
		    }
		  } else {
		    if (args.Length - i == 1){
		      String betalib = Environment.GetEnvironmentVariable("BETALIB");
		      System.Environment.Exit(new DotnetConverter().convert(args[i], betalib, overwrite, output));
		    } else {
		      usage("Wrong number of arguments after the " + i + " option" + ((i <= 1)?"":"s"));
		    }
		  }
		}
	      } else {
		usage("Not enough arguments");
	      }
	  }
		
	internal virtual void  doFields(System.Type cls)
	  {
	    bool first = true;
			
	    System.Reflection.FieldInfo[] fieldlist;
	    fieldlist = cls.GetFields(System.Reflection.BindingFlags.Instance 
				      | System.Reflection.BindingFlags.Public 
				      | System.Reflection.BindingFlags.DeclaredOnly);
	    if (fieldlist.Length == 0) return ;
			
	    for (int i = 0; i < fieldlist.Length; i++){
	      System.Reflection.FieldInfo f = fieldlist[i];
	      if (isRelevant(f)){
		bool isStatic = f.IsStatic;
		if (first){
		  beta.nl();
		  beta.commentline("Public/protected fields");
		  beta.nl();
		}
		first = false;
		if (trace){
		  beta.commentline("Field: " + f.Name + ", type: " + f.FieldType);
		}
		beta.putField(dollarToUnderscore(f.Name), mapType(cls, f.FieldType, false), isStatic);
	      }
	    }
	  }
		
	internal virtual void  doConstructors(System.Type cls)
	  {
	    System.String mangledName;
	    System.String dollarName;
	    bool first = true;
			
	    System.Reflection.ConstructorInfo[] ctorlist;
	    ctorlist = cls.GetConstructors(System.Reflection.BindingFlags.Instance
					   | System.Reflection.BindingFlags.Public 
					   | System.Reflection.BindingFlags.DeclaredOnly);
	    if (ctorlist.Length == 0) return ;
			
	    for (int i = 0; i < ctorlist.Length; i++){
	      System.Reflection.ConstructorInfo ct = ctorlist[i];
	      if (isRelevant(ct)) {
		if (first){
		  beta.nl();
		  beta.commentline("Public/protected constructors");
		  beta.nl();
		}
		first = false;
		System.String name = "_init";
		System.Reflection.ParameterInfo[] parameters = ct.GetParameters();
		bool isStatic = ct.IsStatic;
		System.String[] parameternames = new System.String[parameters.Length];
		for (int j = 0; j < parameters.Length; j++){
		  parameternames[j] = mapType(cls, parameters[j].ParameterType, false);
		}
		if (ctorlist.Length > 1){
		  mangledName = dollarToUnderscore(mangle(name, parameternames));
		} else {
		  dollarName = dollarToUnderscore(name);
		  if (dollarName.Equals(name)){
		    mangledName = null;
		  } else {
		    mangledName = dollarName;
		  }
		}
		beta.putMethod(name, mangledName, parameternames, "^" + stripNamespace(cls.FullName), isStatic);
	      }
	    }
	  }
		
	internal virtual void  doMethods(System.Type cls)
	  {
	    IntegerMap methodcount;
	    System.String mangledName;
	    System.String dollarName;
	    bool first = true;
			
	    System.Reflection.MethodInfo[] methlist;
	    methlist = cls.GetMethods(System.Reflection.BindingFlags.Instance 
				      | System.Reflection.BindingFlags.Public 
				      | System.Reflection.BindingFlags.DeclaredOnly);
	    if (methlist.Length == 0) return ;
			
	    // Record all methods in order to reveal overloaded methods 
	    methodcount = new IntegerMap();
	    for (int i = 0; i < methlist.Length; i++){
	      if (isRelevant(methlist[i])){
		methodcount.increment(methlist[i].Name);
	      }
	    }
			
	    // Then process each method
	    for (int i = 0; i < methlist.Length; i++){
	      System.Reflection.MethodInfo m = methlist[i];
	      if (isRelevant(m)){
		if (first){
		  beta.nl();
		  beta.commentline("Public/protected methods");
		  beta.nl();
		}
		first = false;
		System.String name = m.Name;
		bool isStatic = m.IsStatic;
		System.String returnType = mapType(cls, m.ReturnType, false);
		System.Reflection.ParameterInfo[] parameters = m.GetParameters();
		System.String[] parameternames = new System.String[parameters.Length];
		for (int j = 0; j < parameters.Length; j++){
		  parameternames[j] = mapType(cls, parameters[j].ParameterType, false);
		}
		if (methodcount.val(name) > 1){
		  mangledName = dollarToUnderscore(mangle(name, parameternames));
		} else {
		  dollarName = dollarToUnderscore(name);
		  if (dollarName.Equals(name)){
		    mangledName = null;
		  } else {
		    mangledName = dollarName;
		  }
		}
		if (trace){
		  beta.commentline("Method: " + name + ", returns: " + returnType + " , parameters: " + parameternames.ToString());
		}
		beta.putMethod(name, mangledName, parameternames, returnType, isStatic);
	      }
	    }
	  }
		
	internal virtual void  doClasses(System.Type cls)
	  {
	    System.Type[] classlist = cls.GetNestedTypes();
	    if (classlist.Length == 0)
	      return ;
			
	    beta.nl();
	    beta.commentline("Inner classes");
	    beta.nl();
			
	    for (int i = 0; i < classlist.Length; i++)
	      {
		if (isRelevant(classlist[i]))
		  processClass(cls, classlist[i]);
	      }
	  }
		
	internal virtual System.Object[] doIncludes(System.Type cls)
	  {
	    // Scan all parameters of all methods to determine if other types
	    // are used as formal parameters, thus causing a need for a BETA INCLUDE.
			
	    // Super class
	    mapType(cls, cls.BaseType, true);
			
	    // scan fields 
	    System.Reflection.FieldInfo[] fieldlist;
	    fieldlist = cls.GetFields(System.Reflection.BindingFlags.Instance 
				      | System.Reflection.BindingFlags.Public 
				      | System.Reflection.BindingFlags.DeclaredOnly);
	    for (int i = 0; i < fieldlist.Length; i++)
	      {
		System.Reflection.FieldInfo f = fieldlist[i];
		if (isRelevant(f))
		  {
		    mapType(cls, f.FieldType, true);
		  }
	      }
			
	    // scan constructors
	    System.Reflection.ConstructorInfo[] ctorlist;
	    ctorlist = cls.GetConstructors(System.Reflection.BindingFlags.Instance 
					   | System.Reflection.BindingFlags.Public 
					   | System.Reflection.BindingFlags.DeclaredOnly);
	    for (int i = 0; i < ctorlist.Length; i++)
	      {
		System.Reflection.ConstructorInfo ct = ctorlist[i];
		if (isRelevant(ct))
		  {
		    System.Reflection.ParameterInfo[] parameters = ct.GetParameters();
		    for (int j = 0; j < parameters.Length; j++)
		      {
			mapType(cls, parameters[j].ParameterType, true);
		      }
		  }
	      }
			
	    // Scan methods
	    System.Reflection.MethodInfo[] methlist;
	    methlist = cls.GetMethods(System.Reflection.BindingFlags.Instance
				      | System.Reflection.BindingFlags.Public
				      | System.Reflection.BindingFlags.DeclaredOnly);
	    for (int i = 0; i < methlist.Length; i++){
	      System.Reflection.MethodInfo m = methlist[i];
	      if (isRelevant(m)){
		mapType(cls, m.ReturnType, true);
		System.Reflection.ParameterInfo[] parameters = m.GetParameters();
		for (int j = 0; j < parameters.Length; j++)
		  {
		    mapType(cls, parameters[j].ParameterType, true);
		  }
	      }
	    }
	    
	    if (includes.Values.Count==0) return null;
	    System.Object[] inc = new System.Object[includes.Values.Count];
	    includes.Values.CopyTo(inc,0);
	    for (int i = 0; i < inc.Length; i++){
	      inc[i] = prependClassWithUnderscore((System.String) inc[i]);
	    };
	    return inc;
	  }
		
	internal virtual void  include(System.String name)
	  {
	    if (stripNamespace(name).Equals(className)){
	      // No need to include current class
	    } else if (slashToDot(name).Equals("java.lang.Object")){
	      // No need to include Object
	    } else {
	      includes[dotToSlash(name)] = name;
	    }
	  }
		
	internal virtual System.String prependClassWithUnderscore(System.String name)
	  {
	    try
	      {
		System.Type cls = System.Type.GetType(slashToDot(name));
		return dotToSlash(cls.Namespace) + "/" + "_" + stripNamespace(name);
	      }
	    catch (System.Exception)
	      {
		System.Console.Error.WriteLine("prependClassWithUnderscore: class not found: " + name + "\n");
		return null;
	      }
	  }
		
	internal virtual bool isRelevant(System.Reflection.FieldInfo f)
	  {
	    return true;
	  }
		
	internal virtual bool isRelevant(System.Type t)
	  {
	    return true;
	  }
		
	internal virtual bool isRelevant(System.Reflection.MethodBase m)
	  {
	    return m.IsPublic || m.IsFamily;
	  }
	
	internal virtual System.String mangleType(System.String type)
	  {
	    if (type.StartsWith("["))
	      {
		return "ArrayOf" + mangleType(type.Substring(1, (type.Length) - (1)));
	      }
	    else if (type.StartsWith("L"))
	      {
		return stripNamespace(type.Substring(1, (type.Length - 1) - (1)));
	      }
	    else if (type.Equals("byte"))
	      {
		return "B";
	      }
	    else if (type.Equals("void"))
	      {
		return "V";
	      }
	    else if (type.Equals("short"))
	      {
		return "S";
	      }
	    else if (type.Equals("int"))
	      {
		return "I";
	      }
	    else if (type.Equals("long"))
	      {
		return "J";
	      }
	    else if (type.Equals("float"))
	      {
		return "F";
	      }
	    else if (type.Equals("double"))
	      {
		return "D";
	      }
	    else if (type.Equals("char"))
	      {
		return "C";
	      }
	    else if (type.Equals("boolean"))
	      {
		return "Z";
	      }
	    else
	      {
		if (trace)
		  System.Console.Error.WriteLine("mangleType(" + type + ") returns unchanged");
		return stripNamespace(type);
	      }
	  }
		
	internal virtual System.String mangle(System.String name, System.String[] parameters)
	  {
	    System.String mangled = new System.String(name.ToCharArray());
	    for (int i = 0; i < parameters.Length; i++){
	      mangled = System.String.Concat(mangled, "_" + mangleType(parameters[i]));
	    }
	    if (trace){
	      System.Console.Error.WriteLine("mangle: " + name + " -> " + mangled);
	    }
	    return mangled;
	  }
		
	internal virtual System.String mapType(System.Type user, System.Type type, bool doIncludes)
	  {
	    if (type == null)
	      {
		return null; // can happen for empty superclass
	      }
	    System.String name = type.FullName;
	    if (name.Equals("void"))
	      {
		return null;
	      }
	    else if (name.Equals("byte"))
	      {
		return "@int8";
	      }
	    else if (name.StartsWith("["))
	      {
		return mapInternalType(name, doIncludes);
	      }
	    else if (name.Equals("short"))
	      {
		return "@int16";
	      }
	    else if (name.Equals("int"))
	      {
		return "@int32";
	      }
	    else if (name.Equals("long"))
	      {
		return "@int64";
	      }
	    else if (name.Equals("float"))
	      {
		return "@real32";
	      }
	    else if (name.Equals("double"))
	      {
		return "@real";
	      }
	    else if (name.Equals("char"))
	      {
		return "@char";
	      }
	    else if (name.Equals("boolean"))
	      {
		return "@boolean";
	      }
	    else
	      {
				// Reference to a class
				// Find out if that class is an inner class of some outmost class
		System.Type outmost = null;
		System.Type outer = type.DeclaringType;
		while (outer != null)
		  {
		    outmost = outer;
		    outer = outer.DeclaringType;
		  }
		if (outmost != null)
		  {
		    name = unmangle(outmost, name);
		    if (doIncludes)
		      include(outmost.FullName);
		  }
		else
		  {
		    if (doIncludes)
		      include(name);
		  }
		return makeBetaReference(name);
	      }
	  }
		
	internal virtual System.String mapInternalType(System.String name, bool doIncludes)
	  {
	    // name == "[..."
	    name = name.Substring(1, (name.Length) - (1));
	    if (name.StartsWith("["))
	      {
		System.Console.Error.WriteLine("Warning: mapInternalType: [" + name + ": Cannot map multidimensional arrays to BETA");
		beta.fixme("[" + name + ": Cannot map multidimensional arrays to BETA");
		return "[0]" + mapInternalType(name, doIncludes);
	      }
	    else if (name.Equals("B"))
	      {
		return "[0]@int8";
	      }
	    else if (name.Equals("C"))
	      {
		return "[0]@char";
	      }
	    else if (name.Equals("D"))
	      {
		return "[0]@real";
	      }
	    else if (name.Equals("F"))
	      {
		return "[0]@real32";
	      }
	    else if (name.Equals("I"))
	      {
		return "[0]@int32";
	      }
	    else if (name.Equals("J"))
	      {
		return "[0]@int64";
	      }
	    else if (name.Equals("S"))
	      {
		return "[0]@int16";
	      }
	    else if (name.Equals("Z"))
	      {
		return "[0]@boolean";
	      }
	    else if (name.Equals("V"))
	      {
		System.Console.Error.WriteLine("Warning: mapInternalType: [V: Array of void???");
		beta.fixme("[V: Array of void???");
		return "[0]@int32";
	      }
	    else if (name.StartsWith("L"))
	      {
		name = name.Substring(1, (name.Length - 1) - (1));
		if (doIncludes)
		  include(name);
		return "[0]" + makeBetaReference(name);
	      }
	    else
	      {
		System.Console.Error.WriteLine("Warning: mapInternalType: [" + name + ": unknown type");
		return "[0]@int32";
	      }
	  }
		
	internal virtual System.String makeBetaReference(System.String name)
	  {
	    if (stripNamespace(name).Equals(className))
	      {
		name = "^" + stripNamespace(dollarToUnderscore(name));
	      }
	    else if (name.Equals("java.lang.Object"))
	      {
		name = "^" + stripNamespace(dollarToUnderscore(name));
	      }
	    else
	      {
				// Make reference to wrapper class
		name = "^" + "_" + stripNamespace(dollarToUnderscore(name));
	      }
	    return name;
	  }
		
	internal virtual System.String slashToDot(System.String name)
	  {
	    return name.Replace("/", ".");
	  }
		
	internal virtual System.String dotToSlash(System.String name)
	  {
	    return name.Replace("\\.", "/");
	  }
		
	internal virtual System.String dollarToUnderscore(System.String name)
	  {
			
	    return name.Replace("\\$", "_");
	  }
		
	internal virtual System.String stripNamespace(System.String name)
	  {
	    int i;
	    i = slashToDot(name).LastIndexOf((System.Char) '.');
	    return (i >= 0)?name.Substring(i + 1, (name.Length) - (i + 1)):name;
	  }
		
	internal virtual System.String stripPath(System.String name)
	  {
	    int i;
	    i = name.LastIndexOf((System.Char) '/');
	    return (i >= 0)?name.Substring(i + 1, (name.Length) - (i + 1)):name;
	  }

	internal virtual System.String stripExtension(System.String name)
	  {
	    int i;
	    i = name.LastIndexOf((System.Char) '.');
	    return (i >= 0)?name.Substring(1, i-1):name;
	  }
		
	internal virtual System.String unmangle(System.Type outer, System.String innerName)
	  {
	    System.String unmangled = innerName;
	    if (outer != null)
	      {
		System.String outerName = outer.FullName + '$';
		if (innerName.StartsWith(outerName))
		  {
		    unmangled = unmangled.Substring(outerName.Length, (unmangled.Length) - (outerName.Length));
		  }
	      }
	    return dollarToUnderscore(unmangled);
	  }
		
	internal virtual void  processClass(System.Type outer, System.Type cls)
	  {
	    if (trace)
	      {
		System.Console.Error.WriteLine("processClass(" + ((outer == null)?"null":outer.FullName) + "," + ((cls == null)?"null":cls.FullName) + ")");
	      }
	    System.String innerClass = null;
	    System.String innerName = null;
	    System.String innerSuper = null;
	    System.Type sup;
	    System.String resolution = stripPath(stripExtension(cls.Assembly.CodeBase.ToString()));
	    System.String innerRes = null;

	    if (outer == null)
	      {
		beta.putHeader(namespaceName, className, doIncludes(cls));
	      }
	    else
	      {
		innerClass = stripNamespace(cls.FullName);
		innerName = stripNamespace(unmangle(outer, cls.FullName));
		innerRes  = stripPath(stripExtension(System.Type.GetType(innerClass).Assembly.CodeBase.ToString()));
		sup = cls.BaseType;
		if (sup != null)
		  {
		    innerSuper = stripNamespace(sup.FullName);
		  }
		beta.indent();
		beta.putPatternBegin(innerName, innerSuper);
	      }
	    doFields(cls);
	    doConstructors(cls);
	    doMethods(cls);
	    doClasses(cls);
	    if (outer == null)
	      {
		beta.putTrailer(resolution, namespaceName, className);
		beta.close();
	      }
	    else
	      {
		  beta.putTrailer(innerRes, namespaceName, innerClass); // Assuming same namespace!
	      }
	  }
		
	internal virtual int convertIncludes(System.String betalib, int overwrite, System.IO.TextWriter output)
	  {
	    System.Object[] inc = new System.Object[includes.Values.Count];
	    includes.Values.CopyTo(inc,0);
	    for (int i = 0; i < inc.Length; i++)
	      {
		System.Console.Error.WriteLine("\nRefered by " + slashToDot(namespaceName + "." + className) + ": " + slashToDot((System.String) inc[i]));
		DotnetConverter dotnet2beta = new DotnetConverter();
		if (dotnet2beta.needsConversion(slashToDot((System.String) inc[i]), betalib, overwrite, output) != null)
		  {
		    int status = dotnet2beta.convert(slashToDot((System.String) inc[i]), betalib, overwrite, output);
		    if (status != 0)
		      {
			// error
			return status;
		      }
		  }
		else
		  {
		    if (converted[slashToDot((System.String) inc[i])] != null)
		      {
			System.Console.Error.WriteLine("  --> skipped: already converted by this program execution");
		      }
		    else
		      {
			System.Console.Error.WriteLine("  --> ignored: already converted (use -F to force overwrite)");
		      }
		  }
	      }
	    return 0;
	  }
		
	internal virtual System.Type needsConversion(System.String clsname, System.String betalib, int overwrite, System.IO.TextWriter output)
	  {
	    className = slashToDot(clsname);
	    if (converted[className] != null)
	      {
		// already converted by this program instance
		return null;
	      }
	    thisClass = null;
	    try
	      {
		thisClass = System.Type.GetType(className);
		namespaceName = dotToSlash(thisClass.Namespace);
		className = stripNamespace(thisClass.FullName);
		System.Type sup = thisClass.BaseType;
	        System.String resolution = stripPath(stripExtension(thisClass.Assembly.CodeBase.ToString()));
		if (sup != null)
		  {
		    superNs = dotToSlash(sup.Namespace);
		    superClass = stripNamespace(sup.FullName);
		  }
		beta = new BetaOutput(betalib, resolution, namespaceName, className, superNs, superClass, overwrite, output);
		if (beta.output == null)
		  return null;
	      }
	    catch (System.Exception e)
	      {
		WriteStackTrace(e, Console.Error);
		return null;
	      }
	    return thisClass;
	  }
		
	internal virtual int convert(System.String clsname, System.String betalib, int overwrite, System.IO.TextWriter output)
	  {
	    try
	      {
		if (thisClass == null)
		  {
		    thisClass = needsConversion(clsname, betalib, overwrite, output);
		  }
		if (thisClass == null)
		  return 0;
		System.Console.Error.WriteLine("Converting class\n\t\"" + thisClass.FullName + "\"");
		beta.reportFileName();
		processClass(null, thisClass);
	      }
	    catch (System.Exception e)
	      {
		WriteStackTrace(e, Console.Error);
		return 1;
	      }
	    converted[slashToDot(clsname)] = clsname;
	    System.Console.Error.WriteLine("Done.");
	    return convertIncludes(betalib, ((overwrite == 2)?2:- 1), ((output == System.Console.Out)?output:null));
	  }


	internal void WriteStackTrace(System.Exception throwable, System.IO.TextWriter stream)
	  {
	    stream.Write(throwable.StackTrace);
	    stream.Flush();
	  }
      }
	
    class IntegerMap:System.Collections.Specialized.ListDictionary
      {
	public virtual void  increment(System.String key)
	  {
	    this[key] = val(key) + 1;
	  }
	
	public virtual int val(System.String key)
	  {
	    if (Contains(key))
	      return ((System.Int32) this[key]);
	    return 0;
	  }

	public virtual bool isEmpty()
	  {
	    return Keys.Count==0;
	  }
      }

  }
