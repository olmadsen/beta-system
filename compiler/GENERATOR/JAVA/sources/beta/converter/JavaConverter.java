package beta.converter;

import java.lang.*;
import java.io.*;
import java.util.*;
import java.lang.reflect.*;

class JavaConverter
{
    boolean trace = true;

    BetaOutput out;
    Class thisClass;

    Map includes = new HashMap(10);

    static void usage(){
	System.err.println("Usage: java JavaConverter <java class name>");
	System.err.println("e.g.:  java JavaConverter java.lang.String");
	System.exit(1);
    }

    void doFields(Class cls) throws Throwable
    {
	Field fieldlist[] = cls.getDeclaredFields();
	if (fieldlist.length==0) return;

	out.nl();
	out.commentline("Public/protected fields");
	out.nl();

	for (int i = 0; i < fieldlist.length; i++) {
	    Field f = fieldlist[i];
	    if ((f.getModifiers() & Modifier.PRIVATE)==0){
		boolean isStatic = (f.getModifiers() & Modifier.STATIC)!=0;
		out.putField(f.getName(), mapType(f.getType(),false), isStatic);
	    }
	}
	out.nl();
    }

    void doConstructors(Class cls) throws Throwable
    {
	String mangledName;

	Constructor ctorlist[] = cls.getDeclaredConstructors();
	if (ctorlist.length==0) return;

	out.nl();
	out.commentline("Public/protected constructors");
	out.nl();

	for (int i = 0; i < ctorlist.length; i++) {
	    Constructor ct = ctorlist[i];
	    if ((ct.getModifiers() & Modifier.PRIVATE)==0){
		String name = "_init";
		Class params[] = ct.getParameterTypes();
		boolean isStatic = (ct.getModifiers() & Modifier.STATIC)!=0;
		String parameters[] = new String[params.length];
		for (int j=0; j<params.length; j++){
		    parameters[j] = mapType(params[j], false);
		}
		if (ctorlist.length>1) {
		    mangledName = mangle(name, params);
		} else {
		    mangledName = null;
		}
		out.putMethod(name, mangledName, parameters, null, isStatic);
	    }
	}
	out.nl();
    }

    void doMethods(Class cls) throws Throwable
    {
	IntegerMap methodcount;
	String mangledName;

	Method methlist[] = cls.getDeclaredMethods();
	if (methlist.length==0) return;

	out.nl();
	out.commentline("Public/protected methods");
	out.nl();	
	
	// Record all methods in order to reveal overloaded methods 
	methodcount = new IntegerMap(methlist.length);
	for (int i = 0; i < methlist.length; i++) {  
	    if ((methlist[i].getModifiers() & Modifier.PRIVATE)==0){
		methodcount.increment(methlist[i].getName());
	    }
	}
	// if (trace) System.err.println("Method counts:\n" + methodcount.toString());
	
	// Then process each method
	for (int i = 0; i < methlist.length; i++) {  
	    Method m = methlist[i];
	    if ((m.getModifiers() & Modifier.PRIVATE)==0){
		String name = m.getName();
		boolean isStatic = (m.getModifiers() & Modifier.STATIC)!=0;
		String returnType = mapType(m.getReturnType(), false);
		Class params[] = m.getParameterTypes();
		String parameters[] = new String[params.length];
		for (int j=0; j<params.length; j++){
		    parameters[j] = mapType(params[j], false);
		}
		if (methodcount.value(name)>1) {
		    mangledName = mangle(name, params);
		} else {
		    mangledName = null;
		}
		out.putMethod(name, mangledName, parameters, returnType, isStatic);
	    }
	}
	out.nl();
    }

    Object[] doIncludes(Class cls){
	// Scan all parameters of all methods to determine if other types
	// are used as formal parameters, thus causing a need for a BETA INCLUDE.
	
	// scan fields 
	Field fieldlist[] = cls.getDeclaredFields();
	for (int i = 0; i < fieldlist.length; i++) {
	    Field f = fieldlist[i];
	    if ((f.getModifiers() & Modifier.PRIVATE)==0) {
		mapType(f.getType(), true);
	    }
	}

	// scan constructors
	Constructor ctorlist[] = cls.getDeclaredConstructors();
	for (int i = 0; i < ctorlist.length; i++) {
	    Constructor ct = ctorlist[i];
	    if ((ct.getModifiers() & Modifier.PRIVATE)==0) {
		Class params[] = ct.getParameterTypes();
		for (int j=0; j<params.length; j++){
		    mapType(params[j], true);
		}
	    }
	}

	// Scan methods
	Method methlist[] = cls.getDeclaredMethods();
	for (int i = 0; i < methlist.length; i++) {  
	    Method m = methlist[i];
	    if ((m.getModifiers() & Modifier.PRIVATE)==0) {
		mapType(m.getReturnType(), true);
		Class params[] = m.getParameterTypes();
		for (int j=0; j<params.length; j++){
		    mapType(params[j], true);
		}
	    }
	}

	if (includes.isEmpty()) return null;
	return includes.keySet().toArray();
    }

    void include(String name){
	if (name.equals(thisClass.getName())){
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

    String mapType(Class type, boolean doIncludes){
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
	    if (doIncludes) include(name);
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
	    out.fixme("[" + name + ": Cannot map multidimensional arrays to BETA");
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
	    out.fixme("[V: Array of void???");
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

    int convert(String classname){
	System.err.println("Converting class \"" + classname + "\".");
	try {
	    Class cls = Class.forName(classname);
	    thisClass = cls;
	    String name  = cls.getName();
	    String pkg   = cls.getPackage().getName();
	    Class sup = cls.getSuperclass();
	    String superName = null;
	    String superPkg = null;
	    name = stripPackage(name);
	    pkg = dotToSlash(pkg);
	    if (sup!=null){
		superName = sup.getName();
		superPkg  = sup.getPackage().getName();
		superName = stripPackage(superName);
		superPkg  = dotToSlash(superPkg);
	    }
	    out = new BetaOutput(pkg, name, superPkg, superName);
	    out.putHeader(doIncludes(cls));
	    doFields(cls);
	    doConstructors(cls);
	    doMethods(cls);
	    out.putTrailer();
	} catch (Throwable e) {
	    e.printStackTrace();
	    return 1;
	}
	return 0;
    }

    public static void main(String[] args){
	if (args.length == 1){
	    System.exit(new JavaConverter().convert(args[0]));
	} else {
	    usage();
	}
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
