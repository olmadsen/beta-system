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
		  beta.commentline("Public/protected CLS compliant fields");
		  beta.nl();
		}
		first = false;
		if (trace){
		  beta.commentline("Field: " + f.Name + ", type: " + f.FieldType);
		}
		beta.putField(dollarToUnderscore(f.Name), mapType(f.FieldType, false), isStatic);
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
		  beta.commentline("Public/protected CLS compliant constructors");
		  beta.nl();
		}
		first = false;
		System.String name = "_init";
		System.Reflection.ParameterInfo[] parameters = ct.GetParameters();
		bool isStatic = ct.IsStatic;
		System.String[] parameternames = new System.String[parameters.Length];
		for (int j = 0; j < parameters.Length; j++){
		  parameternames[j] = mapType(parameters[j].ParameterType, false);
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
		if (trace){
		  beta.commentline("Constructor: " + name + ", parameters: " + parameternames.ToString());
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
		  beta.commentline("Public/protected CLS compliant methods");
		  beta.nl();
		}
		first = false;
		System.String name = m.Name;
		bool isStatic = m.IsStatic;
		System.String returnType = mapType(m.ReturnType, false);
		System.Reflection.ParameterInfo[] parameters = m.GetParameters();
		System.String[] parameternames = new System.String[parameters.Length];
		for (int j = 0; j < parameters.Length; j++){
		  parameternames[j] = mapType(parameters[j].ParameterType, false);
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
		  beta.commentline("Method: " + name + ", returns: " + returnType + ", parameters: " + parameternames.ToString());
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
	    mapType(cls.BaseType, true);
			
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
		    mapType(f.FieldType, true);
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
			mapType(parameters[j].ParameterType, true);
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
		mapType(m.ReturnType, true);
		System.Reflection.ParameterInfo[] parameters = m.GetParameters();
		for (int j = 0; j < parameters.Length; j++)
		  {
		    mapType(parameters[j].ParameterType, true);
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
		System.Console.Error.Write("prependClassWithUnderscore: class not found: " + name + "\n");
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
	    if (! (m.IsPublic || m.IsFamily)) return false;
	    /* Ignore unsafe methods */
	    System.Object[] attributes = m.GetCustomAttributes(typeof(System.CLSCompliantAttribute),true);
	    for (int i=0; i<attributes.Length; i++){
	      if (! ((System.CLSCompliantAttribute)attributes[i]).IsCompliant){
		if (trace) {
		  System.Console.Error.Write("UNSAFE (ignored): ");
		  print_method(m);
		}
		return false;
	      }
	    }
	    return true;
	  }

	internal virtual void print_method(System.Reflection.MethodBase m)
	  {
	    bool needComma=false;
	    System.Console.Error.Write(m.DeclaringType.Name 
				       + "." 
				       + m.Name 
				       + "(");
	    System.Reflection.ParameterInfo[] parameters = m.GetParameters();
	    for (int j=0; j<parameters.Length; j++){
	      if (needComma) System.Console.Error.Write(", ");
	      needComma=true;
	      System.Console.Error.Write(parameters[j].ParameterType.ToString());
	    }		  
	    System.Console.Error.Write(")\n");
	}
	
	internal virtual System.String mangleType(System.String type)
	  {
	    if (type.StartsWith("[0]")){
	      return "ArrayOf" + CapitalizeFirst(mangleType(type.Substring(3)));
	    }
	    if (type.StartsWith("@")){
	      return type.Substring(1);
	    }
	    if (type.StartsWith("^")){
	      return type.Substring(1);
	    }
	    return type;
	  }
		
	internal virtual System.String mangle(System.String name, System.String[] parameters)
	  {
	    System.String mangled = new System.String(name.ToCharArray());
	    for (int i = 0; i < parameters.Length; i++){
	      System.String mangledType = mangleType(parameters[i]);
	      if (mangledType[0] != '_') mangledType = "_" + mangledType;
	      mangled = mangled + mangledType;
	    }
	    if (trace){
	      System.Console.Error.Write("mangle: " + name + " -> " + mangled + "\n");
	    }
	    return mangled;
	  }

	static System.String CapitalizeFirst(System.String s) 
	  {
	    if (char.IsLower(s[0])){
	      return char.ToUpper(s[0]) + s.Substring(1, s.Length-1);
	      }
	    return s;
	  }

	internal virtual System.String mapPrimitiveType(System.String name)
	  {
	    switch (name){
	    case "bool":
	    case "System.Boolean":
	      return "@boolean";
	    case "sbyte":
	    case "System.SByte":
	      return "@int8";
	    case "short":
	    case "System.Int16":
	      return "@int16";
	    case "int":
	    case "System.Int32":
	      return "@int32";
	    case "long":
	    case "System.Int64":
	      return "@int64";
	    case "byte":
	    case "System.Byte":
	      return "@int8u";
	    case "ushort":
	    case "System.UInt16":
	      return "@int16u";
	    case "uint":
	    case "System.UInt32":
	      return "@int32u";
	    case "ulong":
	    case "System.UInt64":
	      return "@int64u";
	    case "float":
	    case "System.Single":
	      return "@real32";
	    case "double":
	    case "System.Double":
	      return "@real";
	    case "char":
	    case "System.Char":
	      return "@char";
	    default:
	      return null;
	    }
	  }

	internal virtual System.String mapType(System.Type type, bool doIncludes)
	  {
	    System.String result = _mapType(type, doIncludes);
	    if (trace){
	      System.Console.Error.Write("maptype: " + type.FullName + " -> " + result + "\n");
	    }
	    return result;
	  }
		
	internal virtual System.String _mapType(System.Type type, bool doIncludes)
	  {
	    if (type == null){
		return null; // can happen for empty superclass
	    }
	    System.String name = type.FullName;
	    /* Test for array types */
	    if (name.EndsWith("[]")){
	      return "[0]" + mapPrimitiveType(name.Substring(0, name.Length-2));
	    }
	    /* Test for reference types FIXME */
	    if (name.EndsWith("&")){
	      return "^" + mapPrimitiveType(name.Substring(0, name.Length-1));
	    }
	    /* Test for pointer types FIXME */
	    if (name.EndsWith("*")){
	      return "^" + mapPrimitiveType(name.Substring(0, name.Length-1));
	    }
	    if (name.Equals("void")){
		return null;
	    }
	    System.String primitive = mapPrimitiveType(name);
	    if (primitive != null){
		return primitive;
	    } else {
	      // Reference to a class
	      // Find out if that class is an inner class of some outmost class
	      if (doIncludes) {
		include(name);
	      }
	      return makeBetaReference(name);
	    }
	  }
		
	internal virtual System.String makeBetaReference(System.String name)
	  {
	    if (stripNamespace(name).Equals(className)){
	      name = "^" + stripNamespace(dollarToUnderscore(name));
	    } else {
	      switch (name){
	      case "[mscorlib]System.Object":
	      case "System.Object":
	      case "object":
		name = "^" + stripNamespace(dollarToUnderscore(name));
		break;
	      default:
		// Make reference to wrapper class
		name = "^" + "_" + stripNamespace(dollarToUnderscore(name));
		break;
	      }
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
		System.Console.Error.Write("processClass(" + ((outer == null)?"null":outer.FullName) + "," + ((cls == null)?"null":cls.FullName) + ")" + "\n");
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
		System.Console.Error.Write("\nRefered by " + slashToDot(namespaceName + "." + className) + ": " + slashToDot((System.String) inc[i]) + "\n");
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
			System.Console.Error.Write("  --> skipped: already converted by this program execution" + "\n");
		      }
		    else
		      {
			System.Console.Error.Write("  --> ignored: already converted (use -F to force overwrite)" + "\n");
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
		System.Console.Error.Write("Converting class\n\t\"" + thisClass.FullName + "\"" + "\n");
		beta.reportFileName();
		processClass(null, thisClass);
	      }
	    catch (System.Exception e)
	      {
		WriteStackTrace(e, Console.Error);
		return 1;
	      }
	    converted[slashToDot(clsname)] = clsname;
	    System.Console.Error.Write("Done." + "\n");
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
