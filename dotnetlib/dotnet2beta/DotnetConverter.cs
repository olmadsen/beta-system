#define CATCH

using System;
using System.Reflection;
using System.IO;
using System.Threading;
using System.Runtime.InteropServices;
using System.Collections;
using System.Collections.Specialized;
using System.Globalization;

namespace beta.converter
  {
    class DotnetConverter
      {
	internal static bool verbose = false;
	internal static bool nowarn = false;

	internal static bool use_nonwrapper_super = false; // enabling creates too many circular dependencies

	internal enum TraceFlags: int16 { Type = 1, File = 2, Runtime = 4 };

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
	    // Set culture to en-us; determines style of formatted output
	    Thread.CurrentThread.CurrentCulture = new CultureInfo("en-us");
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
	    Console.Error.WriteLine("   -tr Debug: runtime related verbose output");
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
		      String cls = args[args.Length-1];
		      if (cls.EndsWith(".bet")) cls = stripExtension(cls);
		      Environment.Exit(new DotnetConverter().convert(cls, betalib, overwrite, output));
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
	    if (cls.IsEnum){
	      // Enums are very restricted, see ECMA 335 section 8.5.2:
	      // - It shall have exactly one instance field, and the type of that 
	      //   field defines the underlying type of the enumeration.
	      // - It shall not have any methods of its own.
	      // - It shall not implement any interfaces of its own.
	      // - It shall not have any properties or events of its own.
	      // - It shall not have any static fields unless they are literal
	      // - The underlying type shall be a built-in integer type. 
	      // - Enums shall derive from System.Enum, hence they are
	      //   value types. Like all value types, they shall be sealed
	      beta.nl();
	      beta.commentline("Enum Literals");
	      beta.nl();
	      Type underlying = Enum.GetUnderlyingType(cls);
	      String[] names  = Enum.GetNames(cls);
	      int i=0;
	      foreach (Object o in Enum.GetValues(cls)){
		if (underlying == typeof(System.Int64)){
		  // Cannot express int64 literal directly in BETA source, so we must use
		  // exponential notation
		  beta.putConstant(plusToDot(names[i]), (long)o);
		} else {
		  // 
		  beta.putConstant(plusToDot(names[i]), (int)o);
		}
		i++;
	      }
	    } else {
	      // cls regular class/valuetype
	      bool first = true;
	      FieldInfo[] fieldlist;
	      fieldlist = cls.GetFields(BindingFlags.Instance 
					| BindingFlags.Public 
					| BindingFlags.Static 
					| BindingFlags.DeclaredOnly);
	      foreach (FieldInfo f in fieldlist){
		if (isRelevant(f)){
		  bool isStatic = f.IsStatic;
		  bool isLiteral = f.IsLiteral;
		  if (first){
		    beta.nl();
		    beta.commentline("Public/family CLS compliant fields");
		    beta.nl();
		  }
		  first = false;
		  if ((trace&TraceFlags.Type)!=0){
		    beta.commentline("Field: " + f.Name + ", type: " + f.FieldType);
		  }
		  beta.putField(plusToDot(f.Name), mapType(cls, f.FieldType, false), isStatic);
		}
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
		String[] mappednames    = new String[parameters.Length];
		for (int j = 0; j < parameters.Length; j++){
		  parameternames[j] = mapParameterType(cls, parameters[j].ParameterType);
		  mappednames[j]    = mapType(cls, parameters[j].ParameterType);
		}
		if (ctorlist.Length > 1){
		  mangledName = plusToDot(mangle(name, mappednames));
		} else {
		  nestedName = plusToDot(name);
		  if (nestedName.Equals(name)){
		    mangledName = null;
		  } else {
		    mangledName = nestedName;
		  }
		}
		if ((trace&TraceFlags.Type)!=0){
		  beta.commentline("Constructor: " + name + ", parameters: " + mappednames.ToString());
		}
		beta.putMethod(name, mangledName, parameternames, mapType(cls, cls), isStatic);
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
		String returnType = mapType(cls, m.ReturnType);
		ParameterInfo[] parameters = m.GetParameters();
		String[] parameternames = new String[parameters.Length];
		String[] mappednames    = new String[parameters.Length];
		for (int j = 0; j < parameters.Length; j++){
		  parameternames[j] = mapParameterType(cls, parameters[j].ParameterType);
		  mappednames[j]    = mapType(cls, parameters[j].ParameterType);
		}
		if (methodcount.val(name) > 1){
		  mangledName = plusToDot(mangle(name, mappednames));
		} else {
		  nestedName = plusToDot(name);
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

	internal virtual String mapParameterType(Type cls, Type param)
	  {
	    if (param.IsEnum){
	      // We currently map Enum literals to simple untypes values
	      return mapType(cls, Enum.GetUnderlyingType(param));
	    }
	    return mapType(cls, param);
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
	    
	    if (cls.DeclaringType != null){
	      // cls is an inner class.
	      // We must include super class declaration
	      // If it's not an inner class, the wrapper will have included the super
	      if ((trace&TraceFlags.File)!=0){
		Console.Error.Write("doIncludes: " 
				    + cls.FullName 
				    + ": is inner class in " 
				    + cls.DeclaringType.FullName
				    + ", so we must include super: "
				    + cls.BaseType.FullName);
	      }
	      mapType(cls, cls.BaseType, true, true);
	    } else {
	      // We must still trigger include of super, since it should be converted too
	      // And needsConversion is based on include list.
	      // In most cases this gives a superflous INCLUDE in the non-wrapper, 
	      // but it's currently the only way to ensure that the super class is also converted.
	      mapType(cls, cls.BaseType, true);
	    }

			
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
	      // include wrapper version
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
	    case "System.Object":
	    case "+System.Object":
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
	    if (name.StartsWith("+")){
	      // See checkForNestedName
	      return dotToSlash(name.Substring(1));
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
	    /* Ignore specialname fields */
	    if (f.IsSpecialName) return false;
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
	    if (m.IsSpecialName) {
	      // In the Common Language Specification
	      //   http://www.ecma-international.org/publications/standards/ECMA-335.HTM
	      // the general rule for overloading is that types must differ in parameter 
	      // number and/or parameter types.
	      // A special exception is defined though (Ecma 335, section 10.3.3), 
	      // which permits two operator-conversion functions
	      // "op_explicit" and "op_Implicit" to be overloaded on return type only.
	      // BETA cannot handle these, since we mangle overloaded names on input-
	      // parameters only, so we disregard these special functions.
	      switch (m.Name){
	      case "op_Implicit":
	      case "op_Explicit":
		return false;
	      }
	    }
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
	      // it is a method, not a constructor
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

	internal virtual String mapType(Type userClass, Type type)
	  {
	    return mapType(userClass, type, false, false);
	  }
	
	internal virtual String mapType(Type userClass, Type type, bool doIncludes)
	  {
	    return mapType(userClass, type, doIncludes, false);
	  }
	

	internal virtual String mapType(Type userClass, Type type, bool doIncludes, bool isSuper)
	  {
	    if (type == null){
		return null; // can happen for empty superclass
	    }
	    String name = type.FullName;
	    String result = _mapType(userClass, type, doIncludes, isSuper);
	    if ((trace&TraceFlags.Type)!=0){
	      Console.Error.Write("maptype: " 
				  + name 
				  + " -> " 
				  + result 
				  + ((doIncludes)?", include":", no include") 
				  + ((isSuper)?", is super":", not super") 
				  + "\n");
	    }
	    return result;
	  }
		
	internal virtual String _mapType(Type userClass, Type type, bool doIncludes, bool isSuper)
	  {
	    String name = type.FullName;

	    /* Test for array types */
	    if (type.IsArray){
	      Type elmType = type.GetElementType();
	      if (elmType.IsArray){
		if (!nowarn) Console.Error.Write("*** Warning: Cannot handle array-of-array parameters in " + name + "\n");
		while (elmType.IsArray) elmType = elmType.GetElementType();
	      }
	      return "[0]" + _mapType(userClass, elmType, doIncludes, isSuper);
	    }
	    /* Test for reference types FIXME */
	    if (type.IsByRef){
	      if (!nowarn) Console.Error.Write("*** Warning: Cannot yet handle REF/OUT parameters in " + name + "\n");
	      return _mapType(userClass, type.GetElementType(), doIncludes, isSuper);
	    }
	    /* Test for pointer types FIXME */
	    if (type.IsPointer){
	      if (!nowarn) Console.Error.Write("*** Warning: Cannot handle unsafe POINTER parameters in " + name + "\n");
	      return _mapType(userClass, type.GetElementType(), doIncludes, isSuper);
	    }

	    switch (name){
	    case "System.Void":
	    case "void":
	      return null;
	    }

	    String primitive = mapPrimitiveType(name);
	    if (primitive != null){
		return primitive;
	    } else {
	      // Reference to a class
	      return "^" + checkForNestedName(type, doIncludes, isSuper);
	    }
	  }

	internal virtual String checkForNestedName(Type type, bool doIncludes, bool isSuper)
	  {
	    // Find out if "type" is an inner class of some outmost class
	    Type outmost = null;
	    Type outer = type.DeclaringType;
	    while (outer!=null){ 
	      outmost = outer;
	      outer = outer.DeclaringType; 
	    }
	    if (outmost!=null){
	      String name = unmangle(outmost, type); // get name relative to outmost
	      if ((trace&TraceFlags.Type)!=0)
		Console.Error.Write(name + " is inner class in " + outmost.FullName + "\n");
	      if (doIncludes) {
		// Indicate to the BETA outputter that the non-wrapper is to be used
		include('+' + outmost.FullName);
	      }
	      return makeBetaReference(name, false);
	    } else {
	      String name = type.FullName;
	      if (doIncludes) {
		if (use_nonwrapper_super && isSuper){
		  // Indicate to the BETA outputter that the non-wrapper is to be used for the super
		  include('+' + name);
		} else {
		  include(name);
		}
	      }
	      return makeBetaReference(name, true);
	    }
	  }
		
	internal virtual String makeBetaReference(String name, bool use_wrapper)
	  {
	    if (stripNamespace(name).Equals(className)){
	      name = stripNamespace(name);
	    } else {
	      switch (name){
	      case "System.Object":
	      case "+System.Object":
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
		
	internal virtual String plusToDot(String name)
	  {
	    if (name == null) return null;			
	    return name.Replace("+", ".");
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

	internal static String stripExtension(String name)
	  {
	    int i;
	    if (name == null) return null;	    
	    i = name.LastIndexOf((Char) '.');
	    return (i >= 0)?name.Substring(0, i):name;
	  }
		
	internal virtual String unmangle(Type outer, Type nested)
	  {
	    String unmangled = nested.FullName;
	    Type declaring = nested.DeclaringType;
	    if (outer != null){
	      while (declaring != null){
		if (declaring == outer){
		  String declaringName = declaring.FullName;
		  if (nested.FullName.StartsWith(declaringName)){
		    unmangled = unmangled.Substring(declaringName.Length, (unmangled.Length) - (declaringName.Length));
		    if (unmangled.StartsWith("+")) unmangled = unmangled.Substring(1);
		  }
		  break;
		}
		declaring = nested.DeclaringType;
	      }
	    }
	    if ((trace&TraceFlags.Type)!=0) 
	      Console.Error.Write("unmangle(" 
				  + outer.FullName 
				  + ", " 
				  + nested.FullName 
				  + ") --> " 
				  + plusToDot(unmangled) 
				  + "\n");
	    return plusToDot(unmangled);
	  }
		
	internal virtual void  processClass(Type outer, Type cls)
	  {
	    if ((trace&TraceFlags.Type)!=0)
	      {
		Console.Error.Write("processClass(" 
				    + ((outer == null)?"null":outer.FullName) 
				    + "," 
				    + ((cls == null)?"null":cls.FullName) 
				    + ")" + "\n");
		beta.commentline("Class: " + cls.FullName + ": " + cls.BaseType);
	      }

	    if (outer == null){
	      beta.putHeader(namespaceName, className, doIncludes(cls));
	    } else {
	      String innerSuper = null;
	      Type sup = cls.BaseType;
	      // Get name of inner class, but leave out prefix of name that is shared with outer class
	      String innerName = stripNamespace(unmangle(outer, cls));
	      if (sup != null){
		// Get name for superclass of inner class.
		innerSuper = stripNamespace(sup.FullName); 
		// Check if the super class is an inner class of some other class
		int plusPos = innerSuper.IndexOf('+');
		if (plusPos>=0){
		  // super is an inner class of some other class.
		  // That other class may be 'outer' but it's OK to use 'outer.inner'
		  // even if we are inside 'outer'.
		  innerSuper = plusToDot(innerSuper);
		} else {
		  // super is not an inner class.
		  // Use wrapper class
		  if (use_nonwrapper_super){
		    innerSuper = makeBetaReference(innerSuper, false);
		  } else {
		    innerSuper = '_' + makeBetaReference(innerSuper, false);
		  }
		}
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
	      beta.close(!cls.IsValueType);
	    } else {
	      // Assuming same resolution/namespace:
	      beta.putTrailer(resolution, namespaceName, stripNamespace(cls.FullName), isValue); 
	    }
	  }
		
	internal virtual int convertIncludes(String betalib, int overwrite, TextWriter output)
	  {
	    Object[] inc = new Object[includes.Values.Count];
	    includes.Values.CopyTo(inc,0);
	    foreach (String _i in inc){
	      String i = _i;
	      if (i.StartsWith("+")){
		// See checkForNestedName
		i = i.Substring(1);
	      }
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
		resolution = getResolution(thisClass);
		// Special case: classes which inherit from System.ValueType
		// must have keyword 'valuetype' in resolution.
		// This includes Enums.
		isValue = thisClass.IsValueType;
		if (sup != null){
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
	    Console.Error.Write("\n*** Cannot open class \"" + cls + "\"\n");
	    return null;
	  }

	internal static String getResolution(Type cls)
	  {
	    if (cls != null){
	      string name = cls.Assembly.FullName;
	      // e.g. System.Windows.Forms, Version=1.0.5000.0, Culture=neutral, PublicKeyToken=b77a5c561934e089
	      int commaPos = name.IndexOf(',');
	      if (commaPos>0) return name.Substring(0, commaPos);
	      return name;
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
