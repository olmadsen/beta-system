package beta.converter;

import java.lang.*;
import java.util.*;

public class BetaOutput
{
    String className;
    String packageName;
    String superClass;
    String superPackage;
    int    indentlevel = 0;

    public BetaOutput(String pkg, String cls, String superPkg, String superCls)
    {
	className    = cls;
	packageName  = pkg;
	superClass   = superCls;
	superPackage = superPkg;
    }

    public void indent(){
	for (int i=0; i<indentlevel; i++) System.out.print(" ");
    }

    public void indent(int delta){
	indentlevel += delta;
    }

    public String comment(String cmt){
	return "(* " + cmt + " *)";
    }

    public void commentline(String cmt){
	putln(comment(cmt));
    }

    public void fixme(String msg){
	comment("FIXME: " + msg);
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

    public void putHeader(Object[] includes)
    {
	putln("ORIGIN '~beta/basiclib/betaenv';");
	if (includes!=null){
	    for (int i = 0; i<includes.length; i++){
		putln("INCLUDE '~beta/javalib/" + (String)includes[i] + "';");
	    };
	};
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

    public void putField(String name, String type, boolean isStatic)
    {
	if (isStatic) {
	    commentline("STATIC:");
	}
	putln(name + ": " + type + ";");
    }

    public void putMethod(String name, String mangledName, String[] parameters, String returnType, boolean isStatic)
    {
	String proctype = (name.equals("_init")) ? "cons" : ((isStatic)? "static_proc" : "proc");
	if (mangledName!=null){
	    putln(mangledName + ": " 
		  + proctype + " " 
		  + comment("Overloaded " + ((name.equals("_init")) ? "constructor" : name)));
	} else {
	    putln(name + ": " + proctype);
	}
	
	indent(+2);
	indent(); put("(# ");
	if (returnType!=null){
	    put("result: " + returnType + ";");
	}
	nl();
	indent(+3);
	if (parameters.length>0){
	    int n = 0;
	    for (int i = 0; i<parameters.length; i++){
		putln("arg" + (++n) + ": " + parameters[i] + ";");
	    }
	    indent(-3);
	    indent();
	    put("enter (");
	    boolean comma = false;
	    n = 0;
	    for (int i = 0; i<parameters.length; i++){
		if (comma) put(", "); else comma=true;
		put("arg" + (++n));
		if (parameters[i].startsWith("^")) put("[]");
	    }
	    put(")");
	    nl();
	    indent(+3);
	}
	indent(-3);
	if (mangledName!=null && !name.equals("_init")) {
	    indent();
	    put("do '" + name + "' -> procname;");
	    nl();
	}
	if (returnType!=null){
	    indent(); put("exit result");
	    if (returnType.startsWith("^")) put("[]");
	    nl();
	}
	putln("#);");
	indent(-2);
    }

    public void putTrailer()
    {
	indent(-3);
	putln("do '" + packageName + '/' + className + "' -> className;");
	putln("#);");
	indent(-2);
    }
}
