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
	// Currently not supported
    }

    BetaOutput out;

    void doConstructors(Class cls) throws Throwable
    {
	Constructor ctorlist[] = cls.getDeclaredConstructors();
	for (int i = 0; i < ctorlist.length; i++) {
	    Constructor ct = ctorlist[i];
	    System.out.println("name = " + ct.getName());
	    System.out.println("decl class = " + ct.getDeclaringClass());
	    Class pvec[] = ct.getParameterTypes();
	    for (int j = 0; j < pvec.length; j++)
		System.out.println("param #" + j + " " + pvec[j]);
	    Class evec[] = ct.getExceptionTypes();
	    for (int j = 0; j < evec.length; j++)
		System.out.println("exc #" + j + " " + evec[j]);
	    System.out.println("-----");
	}
    }

    void doMethods(Class cls) throws Throwable
    {
	Method methlist[] = cls.getDeclaredMethods();
	for (int i = 0; i < methlist.length; i++) {  
	    Method m = methlist[i];
	    System.out.println("name = " + m.getName());
	    System.out.println("decl class = " + m.getDeclaringClass());
	    Class pvec[] = m.getParameterTypes();
	    for (int j = 0; j < pvec.length; j++)
		System.out.println("param #" + j + " " + pvec[j]);
	    Class evec[] = m.getExceptionTypes();
	    for (int j = 0; j < evec.length; j++)
		System.out.println("exc #" + j + " " + evec[j]);
	    System.out.println("return type = " + m.getReturnType());
	    System.out.println("-----");
	}
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
	    int iDot;
	    iDot = name.lastIndexOf('.');
            name = (iDot >= 0)? name.substring(iDot+1, name.length()) : name;
	    pkg = pkg.replaceAll("\\.", "/");
	    if (sup!=null){
		superName = sup.getName();
		superPkg  = sup.getPackage().getName();
		iDot = superName.lastIndexOf('.');
		superName = (iDot >= 0)? superName.substring(iDot+1, superName.length()) : superName;
		superPkg = superPkg.replaceAll("\\.", "/");
	    }
	    out = new BetaOutput(pkg, name, superPkg, superName);
	    doFields(cls);
	    doConstructors(cls);
	    doMethods(cls);
	    out.print();
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
