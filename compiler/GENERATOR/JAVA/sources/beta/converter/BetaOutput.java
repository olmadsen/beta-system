package beta.converter;

import java.lang.*;

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

    void indent(){
	for (int i=0; i<indentlevel; i++) System.out.print(" ");
    }

    void indent(int delta){
	indentlevel += delta;
    }

    void commentline(String cmt){
	indent();
	System.out.println("(* " + cmt + " *)");
    }

    void put(String txt){
	System.out.print(txt);
    };

    void putln(String line){
	indent();
	System.out.println(line);
    }

    void nl(){
	System.out.println("");
    }
    
    public void print()
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
	commentline("Fields");
	commentline("...");
	nl();
	commentline("Constructors");
	commentline("...");
	nl();
	commentline("Methods");
	commentline("...");
	nl();
	
	indent(-3);
	putln("do '" + packageName + '/' + className + "' -> className;");
	putln("#);");
	indent(-2);
    }
}
