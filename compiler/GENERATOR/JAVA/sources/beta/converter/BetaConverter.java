package beta.converter;

import java.lang.*;
import java.io.*;
import java.util.*;
import java.lang.reflect.*;

class BetaConverter
{
    BetaOutput out;
    Class thisClass;

    static void usage(){
	System.err.println("Usage: BetaConverter <java class name>");
	System.err.println("e.g.:  BetaConverter java.lang.String");
	System.exit(1);
    }

    void doFields(Class cls) throws Throwable
    {
	out.commentline("Fields");
	out.commentline("...");
	out.nl();
	// Currently not supported
    }

    void doConstructors(Class cls) throws Throwable
    {
	out.commentline("Constructors");
	out.commentline("...");
	out.nl();
	Constructor ctorlist[] = cls.getDeclaredConstructors();
	for (int i = 0; i < ctorlist.length; i++) {
	    Constructor ct = ctorlist[i];
	    //System.out.println("name = " + ct.getName());
	    //System.out.println("decl class = " + ct.getDeclaringClass());
	    Class pvec[] = ct.getParameterTypes();
	    for (int j = 0; j < pvec.length; j++)
		//System.out.println("param #" + j + " " + pvec[j])
		;
	    Class evec[] = ct.getExceptionTypes();
	    for (int j = 0; j < evec.length; j++)
		//System.out.println("exc #" + j + " " + evec[j])
		;
	    //System.out.println("-----");
	}
    }

    void doMethods(Class cls) throws Throwable
    {
	out.commentline("Methods");
	out.nl();	
	Method methlist[] = cls.getDeclaredMethods();
	for (int i = 0; i < methlist.length; i++) {  
	    Method m = methlist[i];
	    String returnType = mapType(m.getReturnType());
	    Class params[] = m.getParameterTypes();
	    List parameters = new ArrayList(params.length);
	    for (int j=0; j<params.length; j++){
		parameters.add(mapType(params[j]));
	    }
	    out.putMethod(m.getName(), parameters, returnType);
	}
    }

    void include(String name){
	if (name.equals(thisClass.getName())){
	    // No need to include current class
	} else if (name.equals("java.lang.Object")){
	    // No need to include Object
	} else {
	    System.err.println("INCLUDE of library corresponding to " + name + " NYI");
	}
    }

    String mapType(Class type){
	String name = type.getName();
	if (name.equals("void")){
	    return null;
	} else if (name.equals("byte")){
	    return "@char";
	} else if (name.startsWith("[")){
	    return mapInternalType(name);
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
	    include(name);
	    return "^" + stripPackage(name);
	}
    }

    String mapInternalType(String name){
	// name == "[..."
	name = name.substring(1, name.length());
	if (name.startsWith("[")){
	    System.err.println("Warning: mapInternalType: [" 
			       + name 
			       + ": Cannot map multidimensional arrays to BETA");
	    out.fixme("[" + name + ": Cannot map multidimensional arrays to BETA");
	    return "[0]" + mapInternalType(name);
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
	    include(name);
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
		superPkg = dotToSlash(superPkg);
	    }
	    out = new BetaOutput(pkg, name, superPkg, superName);
	    out.header();
	    doFields(cls);
	    doConstructors(cls);
	    doMethods(cls);
	    out.trailer();
	} catch (Throwable e) {
	    System.err.println(e);
	    return 1;
	}
	return 0;
    }

    public static void main(String[] args){
	if (args.length == 1){
	    System.exit(new BetaConverter().convert(args[0]));
	} else {
	    usage();
	}
    }
}
