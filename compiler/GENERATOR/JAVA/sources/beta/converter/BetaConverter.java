package beta.converter;

import java.lang.*;
import java.io.*;
import java.util.*;
import java.lang.reflect.*;

class BetaConverter
{
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

    BetaOutput out;

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
	    out.putMethod(m.getName(), m.getParameterTypes(), mapType(m.getReturnType()));
	}
    }

    String mapType(Class type){
	String name = type.getName();
	if (name.equals("void")){
	    return null;
	} else if (name.equals("byte")){
	    return "@char";
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
	    return "^" + stripPackage(name);
	}
    }

    String stripPackage(String name){
	int iDot = name.lastIndexOf('.');
	return (iDot >= 0)? name.substring(iDot+1, name.length()) : name;
    }

    int convert(String classname){
	System.err.println("Converting class \"" + classname + "\".");
	try {
	    Class cls = Class.forName(classname);
	    String name  = cls.getName();
	    String pkg   = cls.getPackage().getName();
	    Class sup = cls.getSuperclass();
	    String superName = null;
	    String superPkg = null;
	    name = stripPackage(name);
	    pkg = pkg.replaceAll("\\.", "/");
	    if (sup!=null){
		superName = sup.getName();
		superPkg  = sup.getPackage().getName();
		superName = stripPackage(superName);
		superPkg = superPkg.replaceAll("\\.", "/");
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
