package beta.converter;

import java.lang.*;
import java.io.*;
import java.util.*;
import java.lang.reflect.*;

class JavaConverter
{
    boolean trace = true;

    BetaOutput beta;
    String className;
    String packageName;
    String superClass;
    String superPkg;

    Map includes = new HashMap(10);

    static void usage(String msg){
	if (msg!=null) System.err.println("\n" + msg + "\n");
	System.err.println("Usage:\n");
	System.err.println("Java:   java JavaConverter [-h][-F|-] <java class name> <BETALIB>");
	System.err.println(" e.g.   java JavaConverter java.lang.String /users/beta/r5.3\n");
	System.err.println("Script: java2beta [-F] <java class name>");
	System.err.println(" e.g.   java2beta java.lang.String\n");
	System.err.println("Output files will be placed in $BETALIB/javalib in a directory");
	System.err.println("structure corresponding to the package of the class.");
	System.err.println(" e.g.   $BETALIB/javalib/java/lang/String.bet\n");
	System.err.println("Options:");
	System.err.println("   -h  Display this help");
	System.err.println("   -F  Force overwrite of existing output file");
	System.err.println("   -   Output to terminal instead of file");
	System.err.println("");
	System.err.println("(BETALIB argument is a workaround for the deprecated System.getenv()).");
	System.exit(1);
    }

    public static void main(String[] args){
	boolean overwrite = false;
	PrintStream out = null;
	if (args.length >= 2){
	    for (int i=0; i<args.length; i++){
		if (args[i].startsWith("-")){
		    if (args[i].equals("-h")){
			usage(null);
		    } else if (args[i].equals("-F")){
			overwrite=true;
		    } else if (args[i].equals("-")){
			out=System.out;
		    } else {
			usage("Illegal option: " + args[i]);
		    }
		} else {
		    if (args.length-i == 2){
			System.exit(new JavaConverter().convert(args[i], args[i+1], overwrite, out));
		    } else {
			usage("Wrong number of arguments after the " + i + " option" + ((i<=1)?"":"s"));
		    }
		}
	    }
	} else {
	    usage("Not enough arguments");
	}
    }

    void doFields(Class cls) throws Throwable
    {
	boolean first = true;
	Object o = null;
	
	Field fieldlist[] = cls.getDeclaredFields();
	if (fieldlist.length==0) return;

	for (int i = 0; i < fieldlist.length; i++) {
	    Field f = fieldlist[i];
	    if (!Modifier.isPrivate(f.getModifiers())){
		if (first){
		    beta.nl();
		    beta.commentline("Public/protected fields");
		    beta.nl();
		}
		first = false;
		boolean isStatic = Modifier.isStatic(f.getModifiers());
		String value = null;
		if (isStatic && Modifier.isFinal(f.getModifiers())){
		    String type = f.getType().getName();
		    if (o == null){
			// Create object to look up static final fields from
			// FIXME: Object really needed?
			// o = cls.newInstance() - only possible if default constructor exists
			Constructor ctorlist[] = cls.getDeclaredConstructors();
			for (int j = 0; j < ctorlist.length; j++) {
			    Constructor ct = ctorlist[j];
			    Class params[] = ct.getParameterTypes();
			    if (params.length==0){
				// Found default (parameterless) constructor)
				o = ct.newInstance(null);
				break;
			    }
			}
		    }
		    if (o!=null){
			if (type.equals("byte")){
			    value = new Byte(f.getByte(o)).toString(); 
			} else if (type.equals("short")){
			    value = new Short(f.getShort(o)).toString(); 
			} else if (type.equals("int")){
			    value = new Integer(f.getInt(o)).toString(); 
			} else if (type.equals("long")){
			    value = new Long(f.getLong(o)).toString(); 
			} else if (type.equals("float")){
			    value = new Float(f.getFloat(o)).toString(); 
			} else if (type.equals("double")){
			    value = new Double(f.getDouble(o)).toString(); 
			} else if (type.equals("char")){
			    value = new Character(f.getChar(o)).toString(); 
			} else if (type.equals("boolean")){
			    value = new Boolean(f.getBoolean(o)).toString(); 
			}
		    }
		} 
		if (value!=null){
		    beta.putConstant(f.getName(), value);
		} else {
		    beta.putField(f.getName(), mapType(cls, f.getType(),false), isStatic);
		}
	    }
	}
    }

    void doConstructors(Class cls) throws Throwable
    {
	String mangledName;
	boolean first = true;

	Constructor ctorlist[] = cls.getDeclaredConstructors();
	if (ctorlist.length==0) return;

	for (int i = 0; i < ctorlist.length; i++) {
	    Constructor ct = ctorlist[i];
	    if (!Modifier.isPrivate(ct.getModifiers())){
		if (first){
		    beta.nl();
		    beta.commentline("Public/protected constructors");
		    beta.nl();
		}
		first = false;
		String name = "_init";
		Class params[] = ct.getParameterTypes();
		boolean isStatic = Modifier.isStatic(ct.getModifiers());
		String parameters[] = new String[params.length];
		for (int j=0; j<params.length; j++){
		    parameters[j] = mapType(cls, params[j], false);
		}
		if (ctorlist.length>1) {
		    mangledName = mangle(name, params);
		} else {
		    mangledName = null;
		}
		beta.putMethod(name, mangledName, parameters, null, isStatic);
	    }
	}
    }

    void doMethods(Class cls) throws Throwable
    {
	IntegerMap methodcount;
	String mangledName;
	boolean first = true;

	Method methlist[] = cls.getDeclaredMethods();
	if (methlist.length==0) return;

	// Record all methods in order to reveal overloaded methods 
	methodcount = new IntegerMap(methlist.length);
	for (int i = 0; i < methlist.length; i++) {  
	    if (!Modifier.isPrivate(methlist[i].getModifiers())){
		methodcount.increment(methlist[i].getName());
	    }
	}
	// if (trace) System.err.println("Method counts:\n" + methodcount.toString());
	
	// Then process each method
	for (int i = 0; i < methlist.length; i++) {  
	    Method m = methlist[i];
	    if (!Modifier.isPrivate(m.getModifiers())){
		if (first){
		    beta.nl();
		    beta.commentline("Public/protected methods");
		    beta.nl();	
		}
		first = false;
		String name = m.getName();
		//System.err.println("Method " + name + ": modiciers: " + m.getModifiers());
		boolean isStatic = Modifier.isStatic(m.getModifiers());
		String returnType = mapType(cls, m.getReturnType(), false);
		Class params[] = m.getParameterTypes();
		String parameters[] = new String[params.length];
		for (int j=0; j<params.length; j++){
		    parameters[j] = mapType(cls, params[j], false);
		}
		if (methodcount.value(name)>1) {
		    mangledName = mangle(name, params);
		} else {
		    mangledName = null;
		}
		beta.putMethod(name, mangledName, parameters, returnType, isStatic);
	    }
	}
    }

    void doClasses(Class cls) throws Throwable
    {
	Class classlist[] = cls.getDeclaredClasses();
	if (classlist.length==0) return;

	beta.nl();
	beta.commentline("Inner classes");
	beta.nl();

	for (int i = 0; i < classlist.length; i++) {
	    processClass(cls, classlist[i]);
	}
    }

    Object[] doIncludes(Class cls){
	// Scan all parameters of all methods to determine if other types
	// are used as formal parameters, thus causing a need for a BETA INCLUDE.
	
	// Super class
	mapType(cls, cls.getSuperclass(), true);

	// scan fields 
	Field fieldlist[] = cls.getDeclaredFields();
	for (int i = 0; i < fieldlist.length; i++) {
	    Field f = fieldlist[i];
	    if (!Modifier.isPrivate(f.getModifiers())) {
		mapType(cls, f.getType(), true);
	    }
	}

	// scan constructors
	Constructor ctorlist[] = cls.getDeclaredConstructors();
	for (int i = 0; i < ctorlist.length; i++) {
	    Constructor ct = ctorlist[i];
	    if (!Modifier.isPrivate(ct.getModifiers())) {
		Class params[] = ct.getParameterTypes();
		for (int j=0; j<params.length; j++){
		    mapType(cls, params[j], true);
		}
	    }
	}

	// Scan methods
	Method methlist[] = cls.getDeclaredMethods();
	for (int i = 0; i < methlist.length; i++) {  
	    Method m = methlist[i];
	    if (!Modifier.isPrivate(m.getModifiers())) {
		mapType(cls, m.getReturnType(), true);
		Class params[] = m.getParameterTypes();
		for (int j=0; j<params.length; j++){
		    mapType(cls, params[j], true);
		}
	    }
	}

	if (includes.isEmpty()) return null;
	return includes.keySet().toArray();
    }

    void include(String name){
	//System.err.println("include? " + name + ", self: " + className);
	if (stripPackage(name).equals(className)){
	    // No need to include current class
	} else if (name.equals("java.lang.Object")){
	    // No need to include Object
	} else {
	    includes.put(dotToSlash(name), name);
	}
    }

    String mangleType(String type){
	if (type.startsWith("[")){
	    return "ArrayOf" + mangleType(type.substring(1,type.length()));
	} else if (type.startsWith("L")){
	    return stripPackage(type.substring(1,type.length()-1));
	} else if (type.equals("byte")){
	    return "B";
	} else if (type.equals("void")){
	    return "V";
	} else if (type.equals("short")){
	    return "S";
	} else if (type.equals("int")){
	    return "I";
	} else if (type.equals("long")){
	    return "J";
	} else if (type.equals("float")){
	    return "F";
	} else if (type.equals("double")){
	    return "D";
	} else if (type.equals("char")){
	    return "C";
	} else if (type.equals("boolean")){
	    return "Z";
	} else {
	    //if (trace) System.err.println("mangleType(" + type + ") returns unchanged");
	    return stripPackage(type);
	}
    }

    String mangle(String name, Class[] parameters){
	String mangled = new String(name);
	for (int i=0; i<parameters.length; i++){
	    mangled = mangled.concat("_" + mangleType(parameters[i].getName()));
	}
	//if (trace) System.err.println("mangle: " + name + " -> " + mangled);
	return mangled;
    }

    String mapType(Class user, Class type, boolean doIncludes){
	String name = type.getName();
	if (name.equals("void")){
	    return null;
	} else if (name.equals("byte")){
	    return "@char";
	} else if (name.startsWith("[")){
	    return mapInternalType(name, doIncludes);
	} else if (name.equals("short")){
	    return "@int16";
	} else if (name.equals("int")){
	    return "@int32";
	} else if (name.equals("long")){
	    return "@int64";
	} else if (name.equals("float")){
	    return "@real32";
	} else if (name.equals("double")){
	    return "@real";
	} else if (name.equals("char")){
	    return "@char";
	} else if (name.equals("boolean")){
	    return "@boolean";
	} else {
	    // Reference to a class
	    // Find out if that class is an inner class of some outmost class
	    Class outmost = null;
	    Class outer = type.getDeclaringClass();
	    while (outer!=null){ 
		outmost = outer;
		outer = outer.getDeclaringClass(); 
	    }
	    if (outmost!=null){
		name = unmangle(outmost, name);
		if (doIncludes) include(outmost.getName());
	    } else {
		if (doIncludes) include(name);
	    }
	    return "^" + stripPackage(name);
	}
    }

    String mapInternalType(String name, boolean doIncludes){
	// name == "[..."
	name = name.substring(1, name.length());
	if (name.startsWith("[")){
	    System.err.println("Warning: mapInternalType: [" 
			       + name 
			       + ": Cannot map multidimensional arrays to BETA");
	    beta.fixme("[" + name + ": Cannot map multidimensional arrays to BETA");
	    return "[0]" + mapInternalType(name, doIncludes);
	} else if (name.equals("B")){
	    return "[0]@char";
	} else if (name.equals("C")){
	    return "[0]@char";
	} else if (name.equals("D")){
	    return "[0]@real";
	} else if (name.equals("F")){
	    return "[0]@real32";
	} else if (name.equals("I")){
	    return "[0]@int32";
	} else if (name.equals("J")){
	    return "[0]@int64";
	} else if (name.equals("S")){
	    return "[0]@int16";
	} else if (name.equals("Z")){
	    return "[0]@boolean";
	} else if (name.equals("V")){
	    System.err.println("Warning: mapInternalType: [V: Array of void???"); 
	    beta.fixme("[V: Array of void???");
	    return "[0]@int32";
	} else if (name.startsWith("L")){
	    name = name.substring(1,name.length()-1);
	    if (doIncludes) include(name);
	    return "[0]^" + stripPackage(name);
	} else {
	    System.err.println("Warning: mapInternalType: [" + name + ": unknown type"); 
	    return "[0]@int32";
	}
    }

    String slashToDot(String name){
	return name.replaceAll("/", ".");
    }

    String dotToSlash(String name){
	return name.replaceAll("\\.", "/");
    }

    String stripPackage(String name){
	int i;
	i = slashToDot(name).lastIndexOf('.');
	return (i >= 0) ? name.substring(i+1, name.length()) : name;
    }

    String unmangle(Class outer, String innerName){
	String unmangled = innerName;
	if (outer!=null){
	    String outerName = outer.getName() + '$';
	    if (innerName.startsWith(outerName)){
		unmangled = unmangled.substring(outerName.length(), unmangled.length());
	    }
	}
	return unmangled;
    }

    void processClass(Class outer, Class cls) throws Throwable {
	String innerClass=null;
	String innerName=null;
	String innerSuper=null;
	if (outer==null) {
	    beta.putHeader(packageName, className, superClass, doIncludes(cls));
	} else {
	    innerClass = stripPackage(cls.getName());
	    innerName  = stripPackage(unmangle(outer, cls.getName()));
	    innerSuper = stripPackage(cls.getSuperclass().getName());
	    beta.indent();
	    beta.putPatternBegin(innerName, innerSuper);
	}
	doFields(cls);
	doConstructors(cls);
	doMethods(cls);
	doClasses(cls);
	if (outer==null) {
	    beta.putTrailer(packageName, className);
	    beta.close();
	} else {
	    beta.putTrailer(packageName, innerClass);
	}
    }

    int convert(String clsname, String betalib, boolean overwrite, PrintStream out){
	className = slashToDot(clsname);
	System.err.println("Converting class\n\t\"" + className + "\"");
	try {
	    Class cls   = Class.forName(className);
	    packageName = dotToSlash(cls.getPackage().getName());
	    className   = stripPackage(cls.getName());
	    Class sup   = cls.getSuperclass();
	    if (sup!=null){
		superPkg   = dotToSlash(sup.getPackage().getName());
		superClass = stripPackage(sup.getName());
	    }
	    beta = new BetaOutput(betalib, packageName, className, overwrite, out);
	    processClass(null, cls);
	} catch (Throwable e) {
	    e.printStackTrace();
	    return 1;
	}
	return 0;
    }
}

class IntegerMap extends HashMap
{
    public IntegerMap(int initialCapacity){
	super(initialCapacity);
    }

    public void increment(String key)
    {
	put(key, new Integer(value(key)+1));
    }

    public int value(String key)
    {
	if (containsKey(key)) return ((Integer)get(key)).intValue();
	return 0;
    }
}
