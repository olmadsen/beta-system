namespace beta.converter
  {
    using System;
	
    class DotnetConverter
      {
	internal Map includes;
	internal static Map converted;
		
	public DotnetConverter()
	  {
	    includes = new HashMap(10);
	  }
	static DotnetConverter()
	  {
	    converted = new HashMap(10);
	  }
	internal bool trace = false;
		
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
	    System.Console.Error.WriteLine("dotnet2beta [-F] <dotnet class name>");
	    System.Console.Error.WriteLine(" e.g.   dotnet2beta System.String\n");
	    System.Console.Error.WriteLine("Output files will be placed in %BETALIB%/dotnetlib in a directory");
	    System.Console.Error.WriteLine("structure corresponding to the namespace of the class.");
	    System.Console.Error.WriteLine(" e.g.   $BETALIB/dotnetlib/System/String.bet\n");
	    System.Console.Error.WriteLine("Options:");
	    System.Console.Error.WriteLine("   -h  Display this help");
	    System.Console.Error.WriteLine("   -f  Force overwrite of existing output file");
	    System.Console.Error.WriteLine("   -F  Force overwrite of existing output file AND files for refered classes");
	    System.Console.Error.WriteLine("   -   Output to terminal instead of file");
	    System.Console.Error.WriteLine("");
	    System.Environment.Exit(1);
	  }
		
	[STAThread]
	  public static void  Main(System.String[] args)
	  {	    
	    int overwrite = 0;
	    /*System.IO.StreamWriter*/ SYstem.IO.TextWriter output = null;
	    if (args.Length >= 1)
	      {
		for (int i = 0; i < args.Length; i++)
		  {
		    if (args[i].StartsWith("-"))
		      {
			if (args[i].Equals("-h"))
			  {
			    usage(null);
			  }
			else if (args[i].Equals("-f"))
			  {
			    overwrite = 1;
			  }
			else if (args[i].Equals("-F"))
			  {
			    overwrite = 2;
			  }
			else if (args[i].Equals("-"))
			  {
			    //UPGRADE_ISSUE: 'java.lang.System.out' was converted to 'System.Console.Out' which is not valid in this expression. 
			    output = System.Console.Out;
			  }
			else
			  {
			    usage("Illegal option: " + args[i]);
			  }
		      }
		    else
		      {
			if (args.Length - i == 1)
			  {
			    String betalib = Environment.GetEnvironmentVariable("BETALIB");
			    System.Environment.Exit(new DotnetConverter().convert(args[i], betalib, overwrite, output));
			  }
			else
			  {
			    usage("Wrong number of arguments after the " + i + " option" + ((i <= 1)?"":"s"));
			  }
		      }
		  }
	      }
	    else
	      {
		usage("Not enough arguments");
	      }
	  }
		
	internal virtual void  doFields(System.Type cls)
	  {
	    bool first = true;
	    System.Object o = null;
			
	    System.Reflection.FieldInfo[] fieldlist = cls.GetFields(System.Reflection.BindingFlags.Instance | System.Reflection.BindingFlags.NonPublic | System.Reflection.BindingFlags.Public | System.Reflection.BindingFlags.DeclaredOnly);
	    if (fieldlist.Length == 0)
	      return ;
			
	    for (int i = 0; i < fieldlist.Length; i++)
	      {
		System.Reflection.FieldInfo f = fieldlist[i];
		//UPGRADE_TODO: Method java.lang.reflect.Field.getModifiers was not converted. 
		if (isRelevant(f.getModifiers()))
		  {
		    if (first)
		      {
			beta.nl();
			beta.commentline("Public/protected fields");
			beta.nl();
		      }
		    first = false;
		    //UPGRADE_TODO: Method java.lang.reflect.Modifier.isStatic was not converted. 
		    //UPGRADE_TODO: Method java.lang.reflect.Field.getModifiers was not converted. 
		    bool isStatic = Modifier.isStatic(f.getModifiers());
		    System.String value_Renamed = null;
		    //UPGRADE_TODO: Method java.lang.reflect.Modifier.isFinal was not converted. 
		    //UPGRADE_TODO: Method java.lang.reflect.Field.getModifiers was not converted. 
		    if (isStatic && Modifier.isFinal(f.getModifiers()))
		      {
			System.String type = f.FieldType.FullName;
			if (o == null)
			  {
			    // Create object to look up static final fields from
			    // FIXME: Object really needed?
			    // o = cls.newInstance() - only possible if default constructor exists
			    System.Reflection.ConstructorInfo[] ctorlist = cls.GetConstructors(System.Reflection.BindingFlags.Instance | System.Reflection.BindingFlags.NonPublic | System.Reflection.BindingFlags.Public | System.Reflection.BindingFlags.DeclaredOnly);
			    for (int j = 0; j < ctorlist.Length; j++)
			      {
				System.Reflection.ConstructorInfo ct = ctorlist[j];
				//UPGRADE_TODO: The equivalent in .NET for method 'java.lang.reflect.Constructor.getParameterTypes' may return a different value. 
				System.Type[] params_Renamed = ct.GetParameters();
				if (params_Renamed.Length == 0)
				  {
				    // Found default (parameterless) constructor)
				    //UPGRADE_ISSUE: Method 'java.lang.reflect.Constructor.newInstance' was not converted. 
				    o = ct.newInstance(null);
				    break;
				  }
			      }
			  }
			if (o != null)
			  {
			    if (type.Equals("byte"))
			      {
				value_Renamed = ((sbyte) f.GetValue(o)).ToString();
			      }
			    else if (type.Equals("short"))
			      {
				value_Renamed = ((short) f.GetValue(o)).ToString();
			      }
			    else if (type.Equals("int"))
			      {
				value_Renamed = ((int) f.GetValue(o)).ToString();
			      }
			    else if (type.Equals("long"))
			      {
				value_Renamed = ((long) f.GetValue(o)).ToString();
			      }
			    else if (type.Equals("float"))
			      {
				//UPGRADE_TODO: The equivalent in .NET for method 'java.lang.Float.toString' may return a different value. 
				value_Renamed = ((float) f.GetValue(o)).ToString();
			      }
			    else if (type.Equals("double"))
			      {
				value_Renamed = ((double) f.GetValue(o)).ToString();
			      }
			    else if (type.Equals("char"))
			      {
				value_Renamed = ((char) f.GetValue(o)).ToString();
			      }
			    else if (type.Equals("boolean"))
			      {
				//UPGRADE_TODO: The equivalent in .NET for method 'java.lang.Boolean.toString' may return a different value. 
				value_Renamed = ((bool) f.GetValue(o)).ToString();
			      }
			  }
		      }
		    if (value_Renamed != null)
		      {
			beta.putConstant(f.Name, value_Renamed);
		      }
		    else
		      {
			beta.putField(dollarToUnderscore(f.Name), mapType(cls, f.FieldType, false), isStatic);
		      }
		  }
	      }
	  }
		
	internal virtual void  doConstructors(System.Type cls)
	  {
	    System.String mangledName;
	    System.String dollarName;
	    bool first = true;
			
	    System.Reflection.ConstructorInfo[] ctorlist = cls.GetConstructors(System.Reflection.BindingFlags.Instance | System.Reflection.BindingFlags.NonPublic | System.Reflection.BindingFlags.Public | System.Reflection.BindingFlags.DeclaredOnly);
	    if (ctorlist.Length == 0)
	      return ;
			
	    for (int i = 0; i < ctorlist.Length; i++)
	      {
		System.Reflection.ConstructorInfo ct = ctorlist[i];
		if (trace)
		  System.Console.Error.WriteLine("Constructor: modifiers: " + SupportClass.GetConstructorModifiers(ct));
		if (isRelevant(SupportClass.GetConstructorModifiers(ct)))
		  {
		    if (first)
		      {
			beta.nl();
			beta.commentline("Public/protected constructors");
			beta.nl();
		      }
		    first = false;
		    System.String name = "_init";
		    //UPGRADE_TODO: The equivalent in .NET for method 'java.lang.reflect.Constructor.getParameterTypes' may return a different value. 
		    System.Type[] params_Renamed = ct.GetParameters();
		    //UPGRADE_TODO: Method java.lang.reflect.Modifier.isStatic was not converted. 
		    bool isStatic = Modifier.isStatic(SupportClass.GetConstructorModifiers(ct));
		    System.String[] parameters = new System.String[params_Renamed.Length];
		    for (int j = 0; j < params_Renamed.Length; j++)
		      {
			parameters[j] = mapType(cls, params_Renamed[j], false);
		      }
		    if (ctorlist.Length > 1)
		      {
			mangledName = dollarToUnderscore(mangle(name, params_Renamed));
		      }
		    else
		      {
			dollarName = dollarToUnderscore(name);
			if (dollarName.Equals(name))
			  {
			    mangledName = null;
			  }
			else
			  {
			    mangledName = dollarName;
			  }
		      }
		    beta.putMethod(name, mangledName, parameters, null, isStatic);
		  }
	      }
	  }
		
	internal virtual void  doMethods(System.Type cls)
	  {
	    IntegerMap methodcount;
	    System.String mangledName;
	    System.String dollarName;
	    bool first = true;
			
	    System.Reflection.MethodInfo[] methlist = cls.GetMethods(System.Reflection.BindingFlags.Instance | System.Reflection.BindingFlags.NonPublic | System.Reflection.BindingFlags.Public | System.Reflection.BindingFlags.DeclaredOnly);
	    if (methlist.Length == 0)
	      return ;
			
	    // Record all methods in order to reveal overloaded methods 
	    methodcount = new IntegerMap(methlist.Length);
	    for (int i = 0; i < methlist.Length; i++)
	      {
		//UPGRADE_ISSUE: Method 'java.lang.reflect.Method.getModifiers' was not converted. 
		if (isRelevant(methlist[i].getModifiers()))
		  {
		    methodcount.increment(methlist[i].Name);
		  }
	      }
	    if (trace)
	      System.Console.Error.WriteLine("Method counts:\n" + methodcount.toString());
			
	    // Then process each method
	    for (int i = 0; i < methlist.Length; i++)
	      {
		System.Reflection.MethodInfo m = methlist[i];
		if (trace)
		  {
		    //UPGRADE_ISSUE: Method 'java.lang.reflect.Method.getModifiers' was not converted. 
		    System.Console.Error.WriteLine("Method " + m.Name + ": modifiers: " + m.getModifiers());
		  }
				//UPGRADE_ISSUE: Method 'java.lang.reflect.Method.getModifiers' was not converted. 
		if (isRelevant(m.getModifiers()))
		  {
		    if (first)
		      {
			beta.nl();
			beta.commentline("Public/protected methods");
			beta.nl();
		      }
		    first = false;
		    System.String name = m.Name;
		    //UPGRADE_TODO: Method java.lang.reflect.Modifier.isStatic was not converted. 
		    //UPGRADE_ISSUE: Method 'java.lang.reflect.Method.getModifiers' was not converted. 
		    bool isStatic = Modifier.isStatic(m.getModifiers());
		    System.String returnType = mapType(cls, m.ReturnType, false);
		    //UPGRADE_TODO: The equivalent in .NET for method 'java.lang.reflect.Method.getParameterTypes' may return a different value. 
		    System.Type[] params_Renamed = m.GetParameters();
		    System.String[] parameters = new System.String[params_Renamed.Length];
		    for (int j = 0; j < params_Renamed.Length; j++)
		      {
			parameters[j] = mapType(cls, params_Renamed[j], false);
		      }
		    if (methodcount.value_Renamed(name) > 1)
		      {
			mangledName = dollarToUnderscore(mangle(name, params_Renamed));
		      }
		    else
		      {
			dollarName = dollarToUnderscore(name);
			if (dollarName.Equals(name))
			  {
			    mangledName = null;
			  }
			else
			  {
			    mangledName = dollarName;
			  }
		      }
		    beta.putMethod(name, mangledName, parameters, returnType, isStatic);
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
				//UPGRADE_ISSUE: Method 'java.lang.Class.getModifiers' was not converted. 
		if (isRelevant(classlist[i].getModifiers()))
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
	    System.Reflection.FieldInfo[] fieldlist = cls.GetFields(System.Reflection.BindingFlags.Instance | System.Reflection.BindingFlags.NonPublic | System.Reflection.BindingFlags.Public | System.Reflection.BindingFlags.DeclaredOnly);
	    for (int i = 0; i < fieldlist.Length; i++)
	      {
		System.Reflection.FieldInfo f = fieldlist[i];
				//UPGRADE_TODO: Method java.lang.reflect.Field.getModifiers was not converted. 
		if (isRelevant(f.getModifiers()))
		  {
		    mapType(cls, f.FieldType, true);
		  }
	      }
			
	    // scan constructors
	    System.Reflection.ConstructorInfo[] ctorlist = cls.GetConstructors(System.Reflection.BindingFlags.Instance | System.Reflection.BindingFlags.NonPublic | System.Reflection.BindingFlags.Public | System.Reflection.BindingFlags.DeclaredOnly);
	    for (int i = 0; i < ctorlist.Length; i++)
	      {
		System.Reflection.ConstructorInfo ct = ctorlist[i];
		if (isRelevant(SupportClass.GetConstructorModifiers(ct)))
		  {
		    //UPGRADE_TODO: The equivalent in .NET for method 'java.lang.reflect.Constructor.getParameterTypes' may return a different value. 
		    System.Type[] params_Renamed = ct.GetParameters();
		    for (int j = 0; j < params_Renamed.Length; j++)
		      {
			mapType(cls, params_Renamed[j], true);
		      }
		  }
	      }
			
	    // Scan methods
	    System.Reflection.MethodInfo[] methlist = cls.GetMethods(System.Reflection.BindingFlags.Instance | System.Reflection.BindingFlags.NonPublic | System.Reflection.BindingFlags.Public | System.Reflection.BindingFlags.DeclaredOnly);
	    for (int i = 0; i < methlist.Length; i++)
	      {
		System.Reflection.MethodInfo m = methlist[i];
				//UPGRADE_ISSUE: Method 'java.lang.reflect.Method.getModifiers' was not converted. 
		if (isRelevant(m.getModifiers()))
		  {
		    mapType(cls, m.ReturnType, true);
		    //UPGRADE_TODO: The equivalent in .NET for method 'java.lang.reflect.Method.getParameterTypes' may return a different value. 
		    System.Type[] params_Renamed = m.GetParameters();
		    for (int j = 0; j < params_Renamed.Length; j++)
		      {
			mapType(cls, params_Renamed[j], true);
		      }
		  }
	      }
			
	    if (includes.isEmpty())
	      return null;
	    return includes.keySet().toArray();
	  }
		
	internal virtual void  include(System.String name)
	  {
	    //System.err.println("include? " + name + ", self: " + className);
	    if (stripNamespace(name).Equals(className))
	      {
				// No need to include current class
	      }
	    else if (name.Equals("java.lang.Object"))
	      {
				// No need to include Object
	      }
	    else
	      {
		includes.put(dotToSlash(name), name);
	      }
	  }
		
	internal virtual bool isRelevant(int m)
	  {
	    //UPGRADE_TODO: Method java.lang.reflect.Modifier.isPublic was not converted. 
	    //UPGRADE_TODO: Method java.lang.reflect.Modifier.isProtected was not converted. 
	    return Modifier.isPublic(m) || Modifier.isProtected(m);
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
		
	internal virtual System.String mangle(System.String name, System.Type[] parameters)
	  {
	    System.String mangled = new System.String(name.ToCharArray());
	    for (int i = 0; i < parameters.Length; i++)
	      {
		mangled = System.String.Concat(mangled, "_" + mangleType(parameters[i].FullName));
	      }
	    if (trace)
	      System.Console.Error.WriteLine("mangle: " + name + " -> " + mangled);
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
		return "@char";
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
		return "^" + stripNamespace(dollarToUnderscore(name));
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
		return "[0]@char";
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
		return "[0]^" + stripNamespace(name);
	      }
	    else
	      {
		System.Console.Error.WriteLine("Warning: mapInternalType: [" + name + ": unknown type");
		return "[0]@int32";
	      }
	  }
		
	internal virtual System.String slashToDot(System.String name)
	  {
	    return name.replaceAll("/", ".");
	  }
		
	internal virtual System.String dotToSlash(System.String name)
	  {
	    return name.replaceAll("\\.", "/");
	  }
		
	internal virtual System.String dollarToUnderscore(System.String name)
	  {
			
	    return name.replaceAll("\\$", "_");
	  }
		
	internal virtual System.String stripNamespace(System.String name)
	  {
	    int i;
	    i = slashToDot(name).LastIndexOf((System.Char) '.');
	    return (i >= 0)?name.Substring(i + 1, (name.Length) - (i + 1)):name;
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
	    if (outer == null)
	      {
		beta.putHeader(namespaceName, className, superClass, doIncludes(cls));
	      }
	    else
	      {
		innerClass = stripNamespace(cls.FullName);
		innerName = stripNamespace(unmangle(outer, cls.FullName));
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
		beta.putTrailer(namespaceName, className);
		beta.close();
	      }
	    else
	      {
		beta.putTrailer(namespaceName, innerClass);
	      }
	  }
		
	internal virtual int convertIncludes(System.String betalib, int overwrite, System.IO.StreamWriter output)
	  {
	    System.Object[] inc = includes.keySet().toArray();
	    for (int i = 0; i < inc.Length; i++)
	      {
		System.Console.Error.WriteLine("\nRefered by " + slashToDot(namespaceName + "." + className) + ": " + slashToDot((System.String) inc[i]));
		DotnetConverter dotnet2beta = new DotnetConverter();
		if (dotnet2beta.needsConversion(slashToDot((System.String) inc[i]), betalib, overwrite, out) != null)
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
		    if (converted.get(slashToDot((System.String) inc[i])) != null)
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
		
	internal virtual System.Type needsConversion(System.String clsname, System.String betalib, int overwrite, System.IO.StreamWriter output)
	  {
	    className = slashToDot(clsname);
	    if (converted.get(className) != null)
	      {
		// already converted by this program instance
		return null;
	      }
	    thisClass = null;
	    //UPGRADE_NOTE: Exception 'java.lang.Throwable' was converted to 'System.Exception' which has different behavior. 
	    try
	      {
		//UPGRADE_TODO: Format of parameters of method 'java.lang.Class.forName' are different in the equivalent in .NET. 
		thisClass = System.Type.GetType(className);
		namespaceName = dotToSlash(thisClass.Namespace.Name);
		className = stripNamespace(thisClass.FullName);
		System.Type sup = thisClass.BaseType;
		if (sup != null)
		  {
		    superNs = dotToSlash(sup.Namespace.Name);
		    superClass = stripNamespace(sup.FullName);
		  }
		beta = new BetaOutput(betalib, namespaceName, className, overwrite, output);
		if (beta.output == null)
		  return null;
	      }
	    catch (System.Exception e)
	      {
		SupportClass.WriteStackTrace(e, Console.Error);
		return null;
	      }
	    return thisClass;
	  }
		
	internal virtual int convert(System.String clsname, System.String betalib, int overwrite, System.IO.StreamWriter output)
	  {
	    //UPGRADE_NOTE: Exception 'java.lang.Throwable' was converted to 'System.Exception' which has different behavior. 
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
		SupportClass.WriteStackTrace(e, Console.Error);
		return 1;
	      }
	    converted.put(slashToDot(clsname), clsname);
	    System.Console.Error.WriteLine("Done.");
	    return convertIncludes(betalib, ((overwrite == 2)?2:- 1), ((output == System.Console.Out)?output:null));
	  }
      }
	
    class IntegerMap:HashMap
      {
	public IntegerMap(int initialCapacity):base(initialCapacity)
	  {
	  }
		
	public virtual void  increment(System.String key)
	  {
	    put(key, value_Renamed(key) + 1);
	  }
		
	public virtual int value_Renamed(System.String key)
	  {
	    if (containsKey(key))
	      return ((System.Int32) get(key));
	    return 0;
	  }
      }
  }
