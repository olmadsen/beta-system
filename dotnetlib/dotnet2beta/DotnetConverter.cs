using System;
using System.Reflection;
using System.IO;
using System.Collections;
using System.Collections.Specialized;

namespace beta.converter
  {
    class DotnetConverter
      {
	internal bool trace_type = false;
	internal bool trace_file = false;
		
	internal IDictionary includes;
	internal static IDictionary converted;
		
	public DotnetConverter()
	  {
	    includes = new ListDictionary();
	  }
	static DotnetConverter()
	  {
	    converted = new ListDictionary();
	  }

	internal BetaOutput beta;
	internal Type thisClass;
	internal String className;
	internal String namespaceName;
	internal String superClass;
	internal String superNs;
		
	internal static void  usage(String msg)
	  {
	    if (msg != null){
	      Console.Error.WriteLine("\n" + msg + "\n");
	    }
	    Console.Error.WriteLine("Usage:\n");
	    Console.Error.WriteLine("dotnet2beta [-h][-f][-F][-] <dotnet class name>");
	    Console.Error.WriteLine(" e.g.   dotnet2beta System.String\n");
	    Console.Error.WriteLine("Output files will be placed in BETALIB/dotnetlib in a directory");
	    Console.Error.WriteLine("structure corresponding to the namespace of the class.");
	    Console.Error.WriteLine(" e.g.   "
					   + Environment.GetEnvironmentVariable("BETALIB") 
					   + "/dotnetlib/System/String.bet\n");
	    Console.Error.WriteLine("Options:");
	    Console.Error.WriteLine("   -h  Display this help");
	    Console.Error.WriteLine("   -f  Force overwrite of existing output file");
	    Console.Error.WriteLine("   -F  Force overwrite of existing output file AND files for refered classes");
	    Console.Error.WriteLine("   -   Output to terminal instead of file");
	    Console.Error.WriteLine("");
	    Environment.Exit((msg == null)?0:1);
	  }
		
	[STAThread]
	  public static void  Main(String[] args)
	  {	    
	    int overwrite = 0;
	    TextWriter output = null;
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
		      output = Console.Out;
		      break;
		    default:
		      usage("Illegal option: " + args[i]);
		      break;
		    }
		  } else {
		    if (args.Length - i == 1){
		      String betalib = Environment.GetEnvironmentVariable("BETALIB");
		      Environment.Exit(new DotnetConverter().convert(args[i], betalib, overwrite, output));
		    } else {
		      usage("Wrong number of arguments after the " + i + " option" + ((i <= 1)?"":"s"));
		    }
		  }
		}
	      } else {
		usage("Not enough arguments");
	      }
	  }
		
	internal virtual void  doFields(Type cls)
	  {
	    bool first = true;
			
	    FieldInfo[] fieldlist;
	    fieldlist = cls.GetFields(BindingFlags.Instance 
				      | BindingFlags.Public 
				      | BindingFlags.DeclaredOnly);
	    if (fieldlist.Length == 0) return ;
			
	    for (int i = 0; i < fieldlist.Length; i++){
	      FieldInfo f = fieldlist[i];
	      if (isRelevant(f)){
		bool isStatic = f.IsStatic;
		if (first){
		  beta.nl();
		  beta.commentline("Public/protected CLS compliant fields");
		  beta.nl();
		}
		first = false;
		if (trace_type){
		  beta.commentline("Field: " + f.Name + ", type: " + f.FieldType);
		}
		beta.putField(dollarToUnderscore(f.Name), mapType(f.FieldType, false), isStatic);
	      }
	    }
	  }
		
	internal virtual void  doConstructors(Type cls)
	  {
	    String mangledName;
	    String dollarName;
	    bool first = true;
			
	    ConstructorInfo[] ctorlist;
	    ctorlist = cls.GetConstructors(BindingFlags.Instance
					   | BindingFlags.Public 
					   | BindingFlags.DeclaredOnly);
	    if (ctorlist.Length == 0) return ;
			
	    for (int i = 0; i < ctorlist.Length; i++){
	      ConstructorInfo ct = ctorlist[i];
	      if (isRelevant(ct)) {
		if (first){
		  beta.nl();
		  beta.commentline("Public/protected CLS compliant constructors");
		  beta.nl();
		}
		first = false;
		String name = "_init";
		ParameterInfo[] parameters = ct.GetParameters();
		bool isStatic = ct.IsStatic;
		String[] parameternames = new String[parameters.Length];
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
		if (trace_type){
		  beta.commentline("Constructor: " + name + ", parameters: " + parameternames.ToString());
		}
		beta.putMethod(name, mangledName, parameternames, "^" + stripNamespace(cls.FullName), isStatic);
	      }
	    }
	  }
		
	internal virtual void  doMethods(Type cls)
	  {
	    IntegerMap methodcount;
	    String mangledName;
	    String dollarName;
	    bool first = true;
			
	    MethodInfo[] methlist;
	    methlist = cls.GetMethods(BindingFlags.Instance 
				      | BindingFlags.Public 
				      | BindingFlags.DeclaredOnly);
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
	      MethodInfo m = methlist[i];
	      if (isRelevant(m)){
		if (first){
		  beta.nl();
		  beta.commentline("Public/protected CLS compliant methods");
		  beta.nl();
		}
		first = false;
		String name = m.Name;
		bool isStatic = m.IsStatic;
		String returnType = mapType(m.ReturnType, false);
		ParameterInfo[] parameters = m.GetParameters();
		String[] parameternames = new String[parameters.Length];
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
		if (trace_type){
		  beta.commentline("Method: " + name + ", returns: " + returnType + ", parameters: " + parameternames.ToString());
		}
		beta.putMethod(name, mangledName, parameternames, returnType, isStatic);
	      }
	    }
	  }
		
	internal virtual void  doClasses(Type cls)
	  {
	    Type[] classlist = cls.GetNestedTypes();
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
		
	internal virtual Object[] doIncludes(Type cls)
	  {
	    // Scan all parameters of all methods to determine if other types
	    // are used as formal parameters, thus causing a need for a BETA INCLUDE.
			
	    // Super class
	    mapType(cls.BaseType, true);
			
	    // scan fields 
	    FieldInfo[] fieldlist;
	    fieldlist = cls.GetFields(BindingFlags.Instance 
				      | BindingFlags.Public 
				      | BindingFlags.DeclaredOnly);
	    for (int i = 0; i < fieldlist.Length; i++)
	      {
		FieldInfo f = fieldlist[i];
		if (isRelevant(f))
		  {
		    mapType(f.FieldType, true);
		  }
	      }
			
	    // scan constructors
	    ConstructorInfo[] ctorlist;
	    ctorlist = cls.GetConstructors(BindingFlags.Instance 
					   | BindingFlags.Public 
					   | BindingFlags.DeclaredOnly);
	    for (int i = 0; i < ctorlist.Length; i++)
	      {
		ConstructorInfo ct = ctorlist[i];
		if (isRelevant(ct))
		  {
		    ParameterInfo[] parameters = ct.GetParameters();
		    for (int j = 0; j < parameters.Length; j++)
		      {
			mapType(parameters[j].ParameterType, true);
		      }
		  }
	      }
			
	    // Scan methods
	    MethodInfo[] methlist;
	    methlist = cls.GetMethods(BindingFlags.Instance
				      | BindingFlags.Public
				      | BindingFlags.DeclaredOnly);
	    for (int i = 0; i < methlist.Length; i++){
	      MethodInfo m = methlist[i];
	      if (isRelevant(m)){
		mapType(m.ReturnType, true);
		ParameterInfo[] parameters = m.GetParameters();
		for (int j = 0; j < parameters.Length; j++)
		  {
		    mapType(parameters[j].ParameterType, true);
		  }
	      }
	    }
	    
	    if (includes.Values.Count==0) return null;
	    Object[] inc = new Object[includes.Values.Count];
	    includes.Values.CopyTo(inc,0);
	    for (int i = 0; i < inc.Length; i++){
	      inc[i] = prependClassWithUnderscore((String) inc[i]);
	    };
	    return inc;
	  }
		
	internal virtual void  include(String name)
	  {
	    if (stripNamespace(name).Equals(className)){
	      // No need to include current class
	      return;
	    }
	    switch (slashToDot(name)){
	    case "[mscorlib]System.Object":
	    case "System.Object":
	    case "object":
	      // No need to include Object
	      return;
	    default:
	      if (trace_file){
		Console.Error.Write("include(" + dotToSlash(name) + ")\n");
	      }
	      includes[dotToSlash(name)] = dotToSlash(name);
	      return;
	    }
	  }
		
	internal virtual String prependClassWithUnderscore(String name)
	  {
	    try
	      {
		Type cls = Type.GetType(slashToDot(name));
		return dotToSlash(cls.Namespace) + "/" + "_" + stripNamespace(name);
	      }
	    catch (Exception)
	      {
		Console.Error.Write("prependClassWithUnderscore: class not found: " + name + "\n");
		return null;
	      }
	  }

	internal virtual bool isCLScompliant(MemberInfo m)
	  {
	    Object[] attributes = m.GetCustomAttributes(typeof(CLSCompliantAttribute),true);
	    for (int i=0; i<attributes.Length; i++){
	      if (! ((CLSCompliantAttribute)attributes[i]).IsCompliant){
		return false;
	      }
	    }
	    return true;
	  }
		
	internal virtual bool isRelevant(FieldInfo f)
	  {
	    /* Ignore unsafe fields */
	    if (!isCLScompliant(f)){
	      if (trace_type) {
		Console.Error.Write("UNSAFE FIELD (ignored): " + f.ToString());
	      }
	      return false;
	    }
	    return true;
	  }
		
	internal virtual bool isRelevant(Type t)
	  {
	    /* Ignore unsafe types */
	    if (!isCLScompliant(t)){
	      if (trace_type) {
		Console.Error.Write("UNSAFE FIELD (ignored): " + t.ToString());
	      }
	      return false;
	    }
	    return true;
	  }
		
	internal virtual bool isRelevant(MethodBase m)
	  {
	    if (! (m.IsPublic || m.IsFamily)) return false;
	    /* Ignore unsafe methods */
	    if (!isCLScompliant(m)){
	      if (trace_type) {
		Console.Error.Write("UNSAFE METHOD/CONSTRUCTOR(ignored): \n   ");
		print_method(m);
	      }
	      return false;
	    }
	    return true;
	  }

	internal virtual void print_method(MethodBase m)
	  {
	    bool needComma=false;
	    Console.Error.Write(m.DeclaringType.Name 
				       + "." 
				       + m.Name 
				       + "(");
	    ParameterInfo[] parameters = m.GetParameters();
	    for (int j=0; j<parameters.Length; j++){
	      if (needComma) Console.Error.Write(", ");
	      needComma=true;
	      Console.Error.Write(parameters[j].ParameterType.ToString());
	    }		  
	    Console.Error.Write(")\n");
	}
	
	internal virtual String mangleType(String type)
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
		
	internal virtual String mangle(String name, String[] parameters)
	  {
	    String mangled = new String(name.ToCharArray());
	    for (int i = 0; i < parameters.Length; i++){
	      String mangledType = mangleType(parameters[i]);
	      if (mangledType[0] != '_') mangledType = "_" + mangledType;
	      mangled = mangled + mangledType;
	    }
	    if (trace_type){
	      Console.Error.Write("mangle: " + name + " -> " + mangled + "\n");
	    }
	    return mangled;
	  }

	static String CapitalizeFirst(String s) 
	  {
	    if (s==null) return null;
	    if (s.Length==0) return "";
	    if (char.IsLower(s[0])){
	      return char.ToUpper(s[0]) + s.Substring(1, s.Length-1);
	      }
	    return s;
	  }

	internal virtual String mapPrimitiveType(String name)
	  {
	    switch (name){
	    case "bool": // probably not needed
	    case "System.Boolean":
	      return "@boolean";
	    case "sbyte": // probably not needed
	    case "System.SByte":
	      return "@int8";
	    case "short": // probably not needed
	    case "System.Int16":
	      return "@int16";
	    case "int": // probably not needed
	    case "System.Int32":
	      return "@int32";
	    case "long": // probably not needed
	    case "System.Int64":
	      return "@int64";
	    case "byte": // probably not needed
	    case "System.Byte":
	      return "@int8u";
	    case "ushort": // probably not needed
	    case "System.UInt16":
	      return "@int16u";
	    case "uint": // probably not needed
	    case "System.UInt32":
	      return "@int32u";
	    case "ulong": // probably not needed
	    case "System.UInt64":
	      return "@int64u";
	    case "float": // probably not needed
	    case "System.Single":
	      return "@real32";
	    case "double": // probably not needed
	    case "System.Double":
	      return "@real";
	    case "char": // probably not needed
	    case "System.Char":
	      return "@char";
	    default:
	      return null;
	    }
	  }

	internal virtual String mapType(Type type, bool doIncludes)
	  {
	    if (type == null){
		return null; // can happen for empty superclass
	    }
	    String result = _mapType(type, doIncludes);
	    if (trace_type){
	      Console.Error.Write("maptype: " + type.FullName + " -> " + result + "\n");
	    }
	    return result;
	  }
		
	internal virtual String _mapType(Type type, bool doIncludes)
	  {
	    if (type == null){
		return null; // can happen for empty superclass
	    }
	    String name = type.FullName;
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
	    String primitive = mapPrimitiveType(name);
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
		
	internal virtual String makeBetaReference(String name)
	  {
	    if (stripNamespace(name).Equals(className)){
	      name = "^" + stripNamespace(dollarToUnderscore(name));
	    } else {
	      switch (name){
	      case "[mscorlib]Object":
	      case "Object":
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
		
	internal virtual String slashToDot(String name)
	  {
	    return name.Replace("/", ".");
	  }
		
	internal virtual String dotToSlash(String name)
	  {
	    return name.Replace(".", "/");
	  }
		
	internal virtual String dollarToUnderscore(String name)
	  {
			
	    return name.Replace("$", "_");
	  }
		
	internal virtual String stripNamespace(String name)
	  {
	    int i;
	    i = slashToDot(name).LastIndexOf((Char) '.');
	    return (i >= 0)?name.Substring(i + 1, (name.Length) - (i + 1)):name;
	  }
		
	internal virtual String stripPath(String name)
	  {
	    int i;
	    i = name.LastIndexOf((Char) '/');
	    return (i >= 0)?name.Substring(i + 1, (name.Length) - (i + 1)):name;
	  }

	internal virtual String stripExtension(String name)
	  {
	    int i;
	    i = name.LastIndexOf((Char) '.');
	    return (i >= 0)?name.Substring(1, i-1):name;
	  }
		
	internal virtual String unmangle(Type outer, String innerName)
	  {
	    String unmangled = innerName;
	    if (outer != null)
	      {
		String outerName = outer.FullName + '$';
		if (innerName.StartsWith(outerName))
		  {
		    unmangled = unmangled.Substring(outerName.Length, (unmangled.Length) - (outerName.Length));
		  }
	      }
	    return dollarToUnderscore(unmangled);
	  }
		
	internal virtual void  processClass(Type outer, Type cls)
	  {
	    if (trace_type)
	      {
		Console.Error.Write("processClass(" + ((outer == null)?"null":outer.FullName) + "," + ((cls == null)?"null":cls.FullName) + ")" + "\n");
	      }
	    String innerClass = null;
	    String innerName = null;
	    String innerSuper = null;
	    Type sup;
	    String resolution = stripPath(stripExtension(cls.Assembly.CodeBase.ToString()));
	    String innerRes = null;

	    if (outer == null)
	      {
		beta.putHeader(namespaceName, className, doIncludes(cls));
	      }
	    else
	      {
		innerClass = stripNamespace(cls.FullName);
		innerName = stripNamespace(unmangle(outer, cls.FullName));
		innerRes  = stripPath(stripExtension(Type.GetType(innerClass).Assembly.CodeBase.ToString()));
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
		
	internal virtual int convertIncludes(String betalib, int overwrite, TextWriter output)
	  {
	    Object[] inc = new Object[includes.Values.Count];
	    includes.Values.CopyTo(inc,0);
	    for (int i = 0; i < inc.Length; i++)
	      {
		Console.Error.Write("\nRefered by " + slashToDot(namespaceName + "." + className) + ": " + slashToDot((String) inc[i]) + "\n");
		DotnetConverter dotnet2beta = new DotnetConverter();
		if (dotnet2beta.needsConversion(slashToDot((String) inc[i]), betalib, overwrite, output) != null)
		  {
		    int status = dotnet2beta.convert(slashToDot((String) inc[i]), betalib, overwrite, output);
		    if (status != 0)
		      {
			// error
			return status;
		      }
		  }
		else
		  {
		    if (converted[slashToDot((String) inc[i])] != null)
		      {
			Console.Error.Write("  --> skipped: already converted by this program execution" + "\n");
		      }
		    else
		      {
			Console.Error.Write("  --> ignored: already converted (use -F to force overwrite)" + "\n");
		      }
		  }
	      }
	    return 0;
	  }
		
	internal virtual Type needsConversion(String clsname, String betalib, int overwrite, TextWriter output)
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
		thisClass = Type.GetType(className);
		namespaceName = dotToSlash(thisClass.Namespace);
		className = stripNamespace(thisClass.FullName);
		Type sup = thisClass.BaseType;
	        String resolution = stripPath(stripExtension(thisClass.Assembly.CodeBase.ToString()));
		if (sup != null)
		  {
		    superNs = dotToSlash(sup.Namespace);
		    superClass = stripNamespace(sup.FullName);
		  }
		beta = new BetaOutput(betalib, resolution, namespaceName, className, superNs, superClass, overwrite, output);
		if (beta.output == null)
		  return null;
	      }
	    catch (Exception e)
	      {
		WriteStackTrace(e, Console.Error);
		return null;
	      }
	    return thisClass;
	  }
		
	internal virtual int convert(String clsname, String betalib, int overwrite, TextWriter output)
	  {
	    try
	      {
		if (thisClass == null)
		  {
		    thisClass = needsConversion(clsname, betalib, overwrite, output);
		  }
		if (thisClass == null)
		  return 0;
		Console.Error.Write("Converting class\n\t\"" + thisClass.FullName + "\"" + "\n");
		beta.reportFileName();
		processClass(null, thisClass);
	      }
	    catch (Exception e)
	      {
		WriteStackTrace(e, Console.Error);
		return 1;
	      }
	    converted[slashToDot(clsname)] = clsname;
	    Console.Error.Write("Done." + "\n");
	    return convertIncludes(betalib, ((overwrite == 2)?2:- 1), ((output == Console.Out)?output:null));
	  }


	internal void WriteStackTrace(Exception throwable, TextWriter stream)
	  {
	    stream.Write("\n\n*** dotnet2beta: Caught exception: \n\n" + throwable.Message + "\n");
	    stream.Write(throwable.StackTrace);
	    stream.Flush();
	  }
      }
	
    class IntegerMap: ListDictionary
      {
	public virtual void  increment(String key)
	  {
	    this[key] = val(key) + 1;
	  }
	
	public virtual int val(String key)
	  {
	    if (Contains(key))
	      return ((Int32) this[key]);
	    return 0;
	  }

	public virtual bool isEmpty()
	  {
	    return Keys.Count==0;
	  }
      }

  }
