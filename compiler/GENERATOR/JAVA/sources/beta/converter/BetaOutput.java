package beta.converter;

import java.lang.*;
import java.lang.reflect.*;

public class BetaOutput
{
    String className;
    String packageName;
    String superClass;
    String superPackage;
    int    indentlevel = 0;

    String includes[];

    public BetaOutput(String pkg, String cls, String superPkg, String superCls)
    {
	className    = cls;
	packageName  = pkg;
	superClass   = superCls;
	superPackage = superPkg;

	includes = new String[0];
    }

    public void indent(){
	for (int i=0; i<indentlevel; i++) System.out.print(" ");
    }

    public void indent(int delta){
	indentlevel += delta;
    }

    public void commentline(String cmt){
	indent();
	System.out.println("(* " + cmt + " *)");
    }

    public void put(String txt){
	System.out.print(txt);
    };

    public void putln(String line){
	indent();
	System.out.println(line);
    }

    public void nl(){
	System.out.println("");
    }
    
    public void header()
    {
	putln("ORIGIN '~beta/basiclib/betaenv';");
	for (int i = 0; i < includes.length; i++) {
	    putln("INCLUDE '" + includes[i] + "';");
	}
	putln("--LIB: attributes--\n");
	putln("(* Java " + className + " class.");
	putln(" * See http://java.sun.com/j2se/1.4.1/docs/api/" 
			   + packageName + '/' + className + ".html");
	putln(" *)");
	put(className + ": ");
	if (superClass==null || superClass.equals("Object")){
	    put("ExternalClass");
	} else {
	    put(superClass);
	}
	nl();
	indent(+2);
	putln("(#");
	indent(+3);
    }

    public void putMethod(String name, Class methods[], String returnType)
    {
	putln(name + ": proc");
	indent(+2);
	indent(); put("(# ");
	if (returnType!=null){
	    put("result: " + returnType);
	}
	nl();
	indent(+3);
	indent(-3);
	if (returnType!=null){
	    indent(); put("exit result");
	    if (returnType.startsWith("^")) put("[]");
	    nl();
	}
	putln("#);");
	indent(-2);
    }

    public void trailer()
    {
	indent(-3);
	putln("do '" + packageName + '/' + className + "' -> className;");
	putln("#);");
	indent(-2);
    }
}
