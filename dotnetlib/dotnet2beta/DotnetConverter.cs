#define CATCH

using System;
using System.Reflection;
using System.IO;
using System.Runtime.InteropServices;
using System.Collections;
using System.Collections.Specialized;

namespace beta.converter
  {
    class DotnetConverter
      {
	internal static bool verbose = false;
	internal static bool nowarn = false;

	internal enum TraceFlags { Type = 1, File = 2, Runtime = 4 };

	internal static TraceFlags trace = 0;
		
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
	internal bool isValue;
	internal String resolution;
		
	internal static void  usage(String msg)
	  {
	    if (msg != null){
	      Console.Error.WriteLine("\n" + msg + "\n");
	    }
	    Console.Error.WriteLine("Usage:\n");
	    Console.Error.WriteLine("dotnet2beta [-h][-v][-w][-f][-F][-][-tt][-tf][-tr] <dotnet class name>");
	    Console.Error.WriteLine(" e.g.   dotnet2beta System.String\n");
	    Console.Error.WriteLine("Output files will be placed in BETALIB/dotnetlib in a directory");
	    Console.Error.WriteLine("structure corresponding to the namespace of the class.");
	    Console.Error.WriteLine(" e.g.   "
					   + Environment.GetEnvironmentVariable("BETALIB") 
					   + "/dotnetlib/System/String.bet\n");
	    Console.Error.WriteLine("Options:");
	    Console.Error.WriteLine("   -h  Display this help");
	    Console.Error.WriteLine("   -v  Verbose output");
	    Console.Error.WriteLine("   -w  Suppress warnings (ignored if -v)");
	    Console.Error.WriteLine("   -f  Force overwrite of existing output file");
	    Console.Error.WriteLine("   -F  Force overwrite of existing output file AND files for refered classes");
	    Console.Error.WriteLine("   -   Output to terminal instead of file");
	    Console.Error.WriteLine("   -tt Debug: type related verbose output");
	    Console.Error.WriteLine("   -tf Debug: file related verbose output");
	    Console.Error.WriteLine("   -tr Debug: runtime related versbose output");
	    Console.Error.WriteLine("");
	    Environment.Exit((msg == null)?0:1);
	  }
		
	[STAThread]
	  public static void  Main(String[] args)
	  {	    
	    int overwrite = 0;
	    TextWriter output = null;
	    int i = 0;
	    if (args.Length >= 1)
	      {
		foreach (String arg in args){
		  if (arg.StartsWith("-")){
		    switch (arg){
		    case "-h":
		      usage(null);
		      break;
		    case "-v":
		      verbose = true; 
		      nowarn=false;
		      break;
		    case "-w":
		      if (!verbose) nowarn = true;
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
		    case "-tt":
		      trace |= TraceFlags.Type;
		      break;
		    case "-tf":
		      trace |= TraceFlags.File;
		      break;
		    case "-tr":
		      trace |= TraceFlags.Runtime;
		      break;
		    default:
		      usage("Illegal option: " + arg);
		      break;
		    }
		  } else {
		    if (args.Length - i == 1){
		      String betalib = Environment.GetEnvironmentVariable("BETALIB");
		      Environment.Exit(new DotnetConverter().convert(args[args.Length-1], betalib, overwrite, output));
		    } else {
		      usage("Wrong number of arguments after the " + i + " option" + ((i <= 1)?"":"s"));
		    }
		  }
		  i++;
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
	    foreach (FieldInfo f in fieldlist){
	      if (isRelevant(f)){
		bool isStatic = f.IsStatic;
		if (first){
		  beta.nl();
		  beta.commentline("Public/family CLS compliant fields");
		  beta.nl();
		}
		first = false;
		if ((trace&TraceFlags.Type)!=0){
		  beta.commentline("Field: " + f.Name + ", type: " + f.FieldType);
		}
		beta.putField(plusToUnderscore(f.Name), mapType(cls, f.FieldType, false), isStatic);
	      }
	    }
	  }
		
	internal virtual void  doConstructors(Type cls)
	  {
	    String mangledName;
	    String nestedName;
	    bool first = true;
			
	    ConstructorInfo[] ctorlist;
	    ctorlist = cls.GetConstructors(BindingFlags.Instance
					   | BindingFlags.Public 
					   | BindingFlags.DeclaredOnly);
	    foreach (ConstructorInfo ct in ctorlist){
	      if (isRelevant(ct)) {
		if (first){
		  beta.nl();
		  beta.commentline("Public/family CLS compliant constructors");
		  beta.nl();
		}
		first = false;
		String name = "_init";
		ParameterInfo[] parameters = ct.GetParameters();
		bool isStatic = ct.IsStatic;
		String[] parameternames = new String[parameters.Length];
		for (int j = 0; j < parameters.Length; j++){
		  parameternames[j] = mapType(cls, parameters[j].ParameterType, false);
		}
		if (ctorlist.Length > 1){
		  mangledName = plusToUnderscore(mangle(name, parameternames));
		} else {
		  nestedName = plusToUnderscore(name);
		  if (nestedName.Equals(name)){
		    mangledName = null;
		  } else {
		    mangledName = nestedName;
		  }
		}
		if ((trace&TraceFlags.Type)!=0){
		  beta.commentline("Constructor: " + name + ", parameters: " + parameternames.ToString());
		}
		beta.putMethod(name, mangledName, parameternames, mapType(cls, cls, false), isStatic);
	      }
	    }
	  }
		
	internal virtual void  doMethods(Type cls)
	  {
	    IntegerMap methodcount;
	    String mangledName;
	    String nestedName;
	    bool first = true;
			
	    MethodInfo[] methlist;
	    methlist = cls.GetMethods(BindingFlags.Instance 
				      | BindingFlags.Static
				      | BindingFlags.Public 
				      | BindingFlags.DeclaredOnly);
	    if (methlist.Length == 0) return ;
			
	    // Record all methods in order to reveal overloaded methods 
	    methodcount = new IntegerMap();
	    foreach (MethodInfo meth in methlist){
	      if (isRelevant(meth)) methodcount.increment(meth.Name);
	    }
			
	    // Then process each method
	    foreach (MethodInfo m in methlist){
	      if (isRelevant(m)){
		if (first){
		  beta.nl();
		  beta.commentline("Public/family CLS compliant methods");
		  beta.nl();
		}
		first = false;
		String name = m.Name;
		bool isStatic = m.IsStatic;
		if ((trace&TraceFlags.Type)!=0){
		  beta.commentline("Method: " + print_method(m));
		}
		String returnType = mapType(cls, m.ReturnType, false);
		ParameterInfo[] parameters = m.GetParameters();
		String[] parameternames = new String[parameters.Length];
		for (int j = 0; j < parameters.Length; j++){
		  parameternames[j] = mapType(cls, parameters[j].ParameterType, false);
		}
		if (methodcount.val(name) > 1){
		  mangledName = plusToUnderscore(mangle(name, parameternames));
		} else {
		  nestedName = plusToUnderscore(name);
		  if (nestedName.Equals(name)){
		    mangledName = null;
		  } else {
		    mangledName = nestedName;
		  }
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
		
	    foreach (Type nested in classlist){
	      if (isRelevant(nested)) processClass(cls, nested);
	    }
	  }
		
	internal virtual String[] doIncludes(Type cls)
	  {
	    // Scan all parameters of all methods to determine if other types
	    // are used as formal parameters, thus causing a need for a BETA INCLUDE.
			
	    // Super class
	    mapType(cls, cls.BaseType, true);
			
	    // scan fields 
	    FieldInfo[] fieldlist;
	    fieldlist = cls.GetFields(BindingFlags.Instance 
				      | BindingFlags.Public 
				      | BindingFlags.DeclaredOnly);
	    foreach (FieldInfo f in fieldlist) {
	      if (isRelevant(f)) mapType(cls, f.FieldType, true);
	    }
			
	    // scan constructors
	    ConstructorInfo[] ctorlist;
	    ctorlist = cls.GetConstructors(BindingFlags.Instance 
					   | BindingFlags.Public 
					   | BindingFlags.DeclaredOnly);
	    foreach  (ConstructorInfo ct in ctorlist){
	      if (isRelevant(ct)){
		foreach (ParameterInfo param in ct.GetParameters()){
		  mapType(cls, param.ParameterType, true);
		}
	      }
	    }
			
	    // Scan methods
	    MethodInfo[] methlist;
	    methlist = cls.GetMethods(BindingFlags.Instance
				      | BindingFlags.Static 
				      | BindingFlags.Public
				      | BindingFlags.DeclaredOnly);
	    foreach (MethodInfo m in methlist){
	      if (isRelevant(m)){
		mapType(cls, m.ReturnType, true);
		ParameterInfo[] parameters = m.GetParameters();
		foreach (ParameterInfo param in parameters){
		  mapType(cls, param.ParameterType, true);
		}
	      }
	    }
	    
	    // Scan nested classes
	    foreach (Type nested in cls.GetNestedTypes()){
	      if (isRelevant(nested)) doIncludes(nested);
	    }

	    // Collect results
	    if (includes.Values.Count==0) return null;
	    String[] inc = new String[includes.Values.Count];
	    int i=0;
	    foreach (String include in includes.Values){
	      inc[i++] = prependClassWithUnderscore(include);
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
	    case "Object":
	    case "object":
	      // No need to include Object
	      return;
	    default:
	      if ((trace&TraceFlags.File)!=0){
		Console.Error.Write("include(" + dotToSlash(name) + ")\n");
	      }
	      includes[dotToSlash(name)] = dotToSlash(name);
	      return;
	    }
	  }
		
	internal virtual String prependClassWithUnderscore(String name)
	  {
	    if ((trace&TraceFlags.File)!=0){
	      Console.Error.Write("prependClassWithUnderscore(" + name + ")\n");
	    }
	    try
	      {
		Type cls = gettype(slashToDot(name));
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
	    foreach (CLSCompliantAttribute att in attributes){
	      if (!att.IsCompliant) return false;
	    }
	    return true;
	  }
		
	internal virtual bool isRelevant(FieldInfo f)
	  {
	    /* Ignore unsafe fields */
	    if (!isCLScompliant(f)){
	      if ((trace&TraceFlags.Type)!=0) {
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
	      if ((trace&TraceFlags.Type)!=0) {
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
	      if ((trace&TraceFlags.Type)!=0) {
		Console.Error.Write("UNSAFE METHOD/CONSTRUCTOR(ignored): \n   "
				    + print_method(m)
				    + "\n");
	      }
	      return false;
	    }
	    return true;
	  }

	internal virtual String print_method(MethodBase m)
	  {
	    String result = "";
	    bool needComma=false;
	    if (m is MethodInfo){
	      result += ((MethodInfo)m).ReturnType.ToString() + " ";
	    }
	    result += m.DeclaringType.Name + "." + m.Name+ "(";
	    foreach (ParameterInfo param in m.GetParameters()){
	      if (needComma) result += ", ";
	      needComma=true;
	      result += param.ParameterType.ToString();
	    }		  
	    result += ")";
	    return result;
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
	    foreach (String param in parameters){
	      String mangledType = mangleType(param);
	      if (mangledType[0] != '_') mangledType = "_" + mangledType;
	      mangled = mangled + mangledType;
	    }
	    if ((trace&TraceFlags.Type)!=0){
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

	internal virtual String mapType(Type userClass, Type type, bool doIncludes)
	  {
	    if (type == null){
		return null; // can happen for empty superclass
	    }
	    String name = type.FullName;
	    String result = _mapType(userClass, type, doIncludes);
	    if ((trace&TraceFlags.Type)!=0){
	      Console.Error.Write("maptype: " + name + " -> " + result + ((doIncludes)?", include":", no include") + "\n");
	    }
	    return result;
	  }
		
	internal virtual String _mapType(Type userClass, Type type, bool doIncludes)
	  {
	    String name = type.FullName;

	    /* Test for array types */
	    if (type.IsArray){
	      return "[0]" + _mapType(userClass, type.GetElementType(), doIncludes);
	    }
	    /* Test for reference types FIXME */
	    if (type.IsByRef){
	      if (!nowarn) Console.Error.Write("*** Warning: Cannot yet handle REF/OUT parameters in " + name + "\n");
	      return _mapType(userClass, type.GetElementType(), doIncludes);
	    }
	    /* Test for pointer types FIXME */
	    if (type.IsPointer){
	      if (!nowarn) Console.Error.Write("*** Warning: Cannot handle unsafe POINTER parameters in " + name + "\n");
	      return _mapType(userClass, type.GetElementType(), doIncludes);
	    }

	    if (name.Equals("void")){
		return null;
	    }
	    String primitive = mapPrimitiveType(name);
	    if (primitive != null){
		return primitive;
	    } else {
	      // Reference to a class
	      return "^" + checkForNestedName(type, doIncludes);
	    }
	  }

	internal virtual String checkForNestedName(Type type, bool doIncludes)
	  {
	    // Find out if "type" is an inner class of some outmost class
	    String name = type.FullName;
	    Type outmost = null;
	    Type outer = type.DeclaringType;
	    while (outer!=null){ 
	      outmost = outer;
	      outer = outer.DeclaringType; 
	    }
	    if (outmost!=null){
	      if ((trace&TraceFlags.Type)!=0)
		Console.Error.Write(name + " is inner class in " + outmost.FullName + "\n");
	      name = unmangle(outmost, name); // get name relative to outmost
	      if (doIncludes) include(outmost.FullName);
	      return makeBetaReference(name, false);
	    } else {
	      if (doIncludes) include(name);
	      return makeBetaReference(name, true);
	    }
	  }
		
	internal virtual String makeBetaReference(String name, bool use_wrapper)
	  {
	    if (stripNamespace(name).Equals(className)){
	      name = stripNamespace(name);
	    } else {
	      switch (name){
	      case "[mscorlib]System.Object":
	      case "System.Object":
	      case "Object":
	      case "object":
		name = "Object";
		break;
	      default:
		if (use_wrapper){
		  // Make reference to wrapper class
		  name = "_" + stripNamespace(name);
		} else {
		  // Make reference to non-wrapper class
		  name = stripNamespace(name);
		}
		break;
	      }
	    }
	    return name;
	  }
		
	internal virtual String slashToDot(String name)
	  {
	    if (name == null) return null;	    
	    return name.Replace("/", ".");
	  }
		
	internal virtual String dotToSlash(String name)
	  {
	    if (name == null) return null;
	    return name.Replace(".", "/");
	  }
		
	internal virtual String plusToUnderscore(String name)
	  {
	    if (name == null) return null;			
	    return name.Replace("$", "_");
	  }
		
	internal virtual String stripNamespace(String name)
	  {
	    int i;
	    if (name == null) return null;
	    i = slashToDot(name).LastIndexOf((Char) '.');
	    return (i >= 0)?name.Substring(i + 1, (name.Length) - (i + 1)):name;
	  }
		
	internal virtual String stripPath(String name)
	  {
	    int i;
	    if (name == null) return null;
	    i = name.LastIndexOf((Char) '/');
	    return (i >= 0)?name.Substring(i + 1, (name.Length) - (i + 1)):name;
	  }

	internal virtual String stripExtension(String name)
	  {
	    int i;
	    if (name == null) return null;	    
	    i = name.LastIndexOf((Char) '.');
	    return (i >= 0)?name.Substring(1, i-1):name;
	  }
		
	internal virtual String unmangle(Type outer, String innerName)
	  {
	    String unmangled = innerName;
	    if (outer != null)
	      {
		String outerName = outer.FullName + '+';
		if (innerName.StartsWith(outerName))
		  {
		    unmangled = unmangled.Substring(outerName.Length, (unmangled.Length) - (outerName.Length));
		  }
	      }
	    if ((trace&TraceFlags.Type)!=0) 
	      Console.Error.Write("unmangle(" + outer.FullName + ", " + innerName + ") --> " + plusToUnderscore(unmangled) + "\n");
	    return plusToUnderscore(unmangled);
	  }
		
	internal virtual void  processClass(Type outer, Type cls)
	  {
	    if ((trace&TraceFlags.Type)!=0)
	      {
		Console.Error.Write("processClass(" + ((outer == null)?"null":outer.FullName) + "," + ((cls == null)?"null":cls.FullName) + ")" + "\n");
	      }
	    String innerClass = null;
	    String innerName = null;
	    String innerSuper = null;
	    Type sup;
	    sup = cls.BaseType;

	    if (outer == null){
	      beta.putHeader(namespaceName, className, doIncludes(cls));
	    } else {
	      innerClass = stripNamespace(cls.FullName);
	      innerName = stripNamespace(unmangle(outer, cls.FullName));
	      if (sup != null){
		innerSuper = checkForNestedName(sup, false); // stripNamespace(sup.FullName);
	      }
	      beta.indent();
	      beta.putPatternBegin(innerName, innerSuper);
	    }
	    doFields(cls);
	    doConstructors(cls);
	    doMethods(cls);
	    doClasses(cls);
	    
	    if (outer == null){
	      beta.putTrailer(resolution, namespaceName, className, isValue);
	      beta.close();
	    } else {
	      beta.putTrailer(resolution, namespaceName, innerClass, isValue); // Assuming same resolution/namespace!
	    }
	  }
		
	internal virtual int convertIncludes(String betalib, int overwrite, TextWriter output)
	  {
	    Object[] inc = new Object[includes.Values.Count];
	    includes.Values.CopyTo(inc,0);
	    foreach (String i in inc){
	      if (verbose) Console.Error.Write("\nRefered by " 
					       + slashToDot(namespaceName + "." + className) 
					       + ": " 
					       + slashToDot(i) 
					       + "\n");
	      DotnetConverter dotnet2beta = new DotnetConverter();
	      if (dotnet2beta.needsConversion(slashToDot(i), betalib, overwrite, output) != null){
		int status = dotnet2beta.convert(slashToDot(i), betalib, overwrite, output);
		if (status != 0){
		  // error
		  return status;
		}
	      } else {
		if (verbose){
		  if (converted[slashToDot(i)] != null){
		    Console.Error.Write("  --> skipped: already converted by this program execution" + "\n");
		  } else {
		    Console.Error.Write("  --> ignored: already converted (use -F to force overwrite)" + "\n");
		  }
		}
	      }
	    }
	    return 0;
	  }
		
	internal virtual Type needsConversion(String clsname, String betalib, int overwrite, TextWriter output)
	  {
	    className = slashToDot(clsname);
	    if (converted[className] != null){
	      // already converted by this program instance
	      return null;
	    }
	    thisClass = null;
	    try
	      {
		thisClass = gettype(className);
		namespaceName = slashToDot(thisClass.Namespace);
		className = stripNamespace(thisClass.FullName);
		Type sup = thisClass.BaseType;
		resolution = stripPath(stripExtension(codebase(thisClass.FullName)));
		isValue = false;
		// Special case: classes with immediate base type System.ValueType must have keyword valuetype in resolution
		if (sup != null && sup.FullName == "System.ValueType"){
		  isValue = true;
		}
		if (sup != null)
		  {
		    superNs = dotToSlash(sup.Namespace);
		    superClass = stripNamespace(sup.FullName);
		  }
		beta = new BetaOutput(betalib, resolution, dotToSlash(namespaceName), className, dotToSlash(superNs), superClass, overwrite, output, isValue);
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
#if CATCH
	    try
	      {
#endif
		if (thisClass == null)
		  {
		    thisClass = needsConversion(clsname, betalib, overwrite, output);
		  }
		if (thisClass == null)
		  return 0;
		Console.Error.Write("Class:  \"" + thisClass.FullName + "\"" + "\n");
		beta.reportFileName();
		processClass(null, thisClass);
#if CATCH
	      }
	    catch (Exception e)
	      {
	    	WriteStackTrace(e, Console.Error);
		return 1;
	      }
#endif
	    converted[slashToDot(clsname)] = clsname;
	    if (verbose) Console.Error.Write("Done." + "\n");
	    return convertIncludes(betalib, ((overwrite == 2)?2:- 1), ((output == Console.Out)?output:null));
	  }


	internal void WriteStackTrace(Exception throwable, TextWriter stream)
	  {
	    stream.Write("\n\n*** dotnet2beta: Caught exception: \n\n" + throwable.Message + "\n");
	    stream.Write(throwable.StackTrace + "\n\n");
	    stream.Flush();
	  }

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
	      if ((trace&TraceFlags.Runtime)!=0) Console.WriteLine("[  first try: " + firsttry + "]");
	      try {
		asm = Assembly.LoadFile(dir + Path.DirectorySeparatorChar + firsttry + ".dll");
		t = asm.GetType(cls);
		if (t != null){
		  if ((trace&TraceFlags.Runtime)!=0) Console.WriteLine("   FOUND!");
		  return t;
		}
	      } catch (Exception) {
		// Ignore error and go on
	      }
	    }
        
	    // Then search all files in system runtime directory (:-(
	    // Console.Error.WriteLine("Expensive search for type \"" + cls + "\"");
	    foreach (String dll in Directory.GetFiles(dir, "*.dll")){
	      if (dll.EndsWith("mscorlib.dll")) continue; // mscorlib already examined
	      if ((trace&TraceFlags.Runtime)!=0) Console.WriteLine("  [searching " + dll + "]");
	      try {
		asm = Assembly.LoadFile(dll);
		t = asm.GetType(cls);
		if (t != null){
		  if ((trace&TraceFlags.Runtime)!=0) Console.WriteLine("  FOUND!");
		  return t;
		}
	      } catch (Exception) {
		// Ignore error and go on
	      }
	    }
        
	    // Giving up
	    return null;
	  }

	internal static String codebase(String cls)
	  {
	    Type t = gettype(cls);
	    if (t != null){
	      return t.Assembly.CodeBase;
	    } else {
	      return "";
	    } 
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
