package beta.converter;

import java.lang.*;
import java.util.*;
import java.io.*;

public class BetaOutput
{
    int    indentlevel = 0;

    public PrintStream out;
    
    File entry;
    File existing = null;

    public BetaOutput(String betalib, 
		      String pkg, 
		      String cls, 
		      String supPkg, 
		      String sup, 
		      int overwrite,
		      PrintStream outstream)
	throws Throwable
    {
        
	openStream(betalib, pkg, "_" + cls, overwrite, outstream);
	if (out!=null) putWrapper(pkg, cls, supPkg, sup);
	openStream(betalib, pkg, cls, overwrite, outstream);
    }

    void openStream(String betalib, 
		    String pkg, 
		    String cls, 
		    int overwrite,
		    PrintStream outstream)
	throws Throwable
    {
	entry   = new File(betalib + "/javalib/" + pkg + "/" + cls + ".bet");
	if (entry.exists()){
	    if (overwrite==-1){
		// Ignore if already converted
		// System.err.println("BetaOutput: ignore: " + entry.getAbsolutePath() + "\"");
		out = null;
		return;
	    }
	    if (overwrite==0){
		existing = entry;
		// System.err.println("BetaOutput: .new: " + entry.getAbsolutePath() + "\"");
		entry = new File(entry.getAbsolutePath() + ".new");
	    }
	}
	entry.getParentFile().mkdirs();
	if (outstream != null){
	    // System.err.println("BetaOutput: existing outstream");
	    out = outstream;
	} else {
	    // System.err.println("BetaOutput: new outstream");
	    if (out != null) { out.close(); }
	    out = new PrintStream(new FileOutputStream(entry));
	}
    }


    public void reportFileName()
    {
	if (out == null){
	    // class ignored
	    return;
	}
	if (out == System.out){
	    // no file involved
	    return;
	}
	System.err.println("Output file:\n\t\"" + entry.getAbsolutePath() + "\"");
	if (existing!=null){
	    System.err.println("NOTICE: Not overwriting existing\n\t\"" 
			       + existing.getAbsolutePath()
			       + "\"");
	    System.err.println("\tUse -f or -F option if overwrite desired.");
	}
    }

    public void indent(){
	for (int i=0; i<indentlevel; i++) put(" ");
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
	out.print(txt);
    };

    public void putln(String line){
	indent();
	out.println(line);
    }

    public void nl(){
	out.println("");
    }

    public String mapReserved(String word){
	// Map declarations and dynamic references
	String prefix = "";
	// Extract declarator prefix
	if (word.startsWith("^")){
	    prefix = "^";
	    word = word.substring(1,word.length());
	} else if (word.startsWith("[0]^")){
	    prefix = word.substring(0,4);
	    word = word.substring(4,word.length());
	} else if (word.startsWith("@")){
	    return word;
	} else if (word.startsWith("[0]@")){
	    return word;
	} 

	// compare word against grammatically reserved BETA words
	if (word.equalsIgnoreCase("enter")){
	    return prefix + "Java" + word;
	} else if (word.equalsIgnoreCase("exit")){
	    return prefix + "Java" + word;
	} else if (word.equalsIgnoreCase("do")){
	    return prefix + "Java" + word;
	} else if (word.equalsIgnoreCase("for")){
	    return prefix + "Java" + word;
	} else if (word.equalsIgnoreCase("repeat")){
	    return prefix + "Java" + word;
	} else if (word.equalsIgnoreCase("if")){
	    return prefix + "Java" + word;
	} else if (word.equalsIgnoreCase("restart")){
	    return prefix + "Java" + word;
	} else if (word.equalsIgnoreCase("inner")){
	    return prefix + "Java" + word;
	} else if (word.equalsIgnoreCase("suspend")){
	    return prefix + "Java" + word;
	} else if (word.equalsIgnoreCase("code")){
	    return prefix + "Java" + word;
	} else if (word.equalsIgnoreCase("then")){
	    return prefix + "Java" + word;
	} else if (word.equalsIgnoreCase("else")){
	    return prefix + "Java" + word;
	} else if (word.equalsIgnoreCase("tos")){
	    return prefix + "Java" + word;
	} else if (word.equalsIgnoreCase("this")){
	    return prefix + "Java" + word;
	} else if (word.equalsIgnoreCase("or")){
	    return prefix + "Java" + word;
	} else if (word.equalsIgnoreCase("xor")){
	    return prefix + "Java" + word;
	} else if (word.equalsIgnoreCase("div")){
	    return prefix + "Java" + word;
	} else if (word.equalsIgnoreCase("mod")){
	    return prefix + "Java" + word;
	} else if (word.equalsIgnoreCase("and")){
	    return prefix + "Java" + word;
	} else if (word.equalsIgnoreCase("not")){
	    return prefix + "Java" + word;
	} else if (word.equalsIgnoreCase("none")){
	    return prefix + "Java" + word;
	}
		   
	// Compare word against basic patterns
	if (word.equalsIgnoreCase("integer")){
	    return prefix + "Java" + word;
	} else if (word.equalsIgnoreCase("shortInt")){
	    return prefix + "Java" + word;
	} else if (word.equalsIgnoreCase("char")){
	    return prefix + "Java" + word;
	} else if (word.equalsIgnoreCase("boolean")){
	    return prefix + "Java" + word;
	} else if (word.equalsIgnoreCase("false")){
	    return prefix + "Java" + word;
	} else if (word.equalsIgnoreCase("true")){
	    return prefix + "Java" + word;
	} else if (word.equalsIgnoreCase("real")){
	    return prefix + "Java" + word;
	} else if (word.equalsIgnoreCase("int8")){
	    return prefix + "Java" + word;
	} else if (word.equalsIgnoreCase("int8u")){
	    return prefix + "Java" + word;
	} else if (word.equalsIgnoreCase("int16")){
	    return prefix + "Java" + word;
	} else if (word.equalsIgnoreCase("int16u")){
	    return prefix + "Java" + word;
	} else if (word.equalsIgnoreCase("int32")){
	    return prefix + "Java" + word;
	} else if (word.equalsIgnoreCase("int32u")){
	    return prefix + "Java" + word;
	} else if (word.equalsIgnoreCase("int64")){
	    return prefix + "Java" + word;
	} else if (word.equalsIgnoreCase("int64u")){
	    return prefix + "Java" + word;
	}
	    
	// Compare against other patterns that may confuse 
	if (word.equals("File")){
	    return prefix + "Java" + word;
	} 

	// Not reserved
	return prefix + word;
	
    }

    public void putPatternBegin(String className, String superClass){
	put(mapReserved(className) + ": ");
	if (superClass==null || superClass.equals("Object")){
	    put("ExternalClass");
	} else {
	    put(superClass);
	}
	nl();
	indent(+2);
	indent();
	put("(#");
	indent(+3);
    }

    public void putWrapper(String packageName, String className, String superPkg, String superClass)
    {
	putln("ORIGIN '~beta/basiclib/betaenv';");
	if ((superClass!=null) && !superClass.equals("Object")){
	    // Include non-wrapper version of superclass
	    putln("INCLUDE '~beta/javalib/" + superPkg + "/" + superClass + "';");
	};
	putln("--LIB: attributes--\n");
	putln("(* Java " + className + " class declaration.");
	putln(" * This wrapper is needed to prevent circular fragment INCLUDE.");
	putln(" * See " + className + ".bet for members.");
	putln(" *)");
	putPatternBegin("_" + className, superClass);
	nl();
	putTrailer(packageName, className);
    }

    public void putHeader(String packageName, String className, Object[] includes)
    {
	putln("ORIGIN '" + "_" + className + "';");
	if (includes!=null){
	    for (int i = 0; i<includes.length; i++){
		putln("INCLUDE '~beta/javalib/" + (String)includes[i] + "';");
	    };
	};
	putln("--LIB: attributes--\n");
	putln("(* Java " + className + " class members.");
	putln(" * See " + "_" + className + " for class declaration.");
	putln(" * See http://java.sun.com/j2se/1.4.1/docs/api/" 
	      + packageName + '/' + className + ".html");
	putln(" *)");
	putPatternBegin(className, "_" + className);
    }

    public void putField(String name, String type, boolean isStatic)
    {
	if (isStatic) {
	    commentline("STATIC:");
	}
	putln(mapReserved(name) + ": " + mapReserved(type) + ";");
    }

    public void putConstant(String name, String value)
    {
	putln(mapReserved(name) + ": (# exit " + value + " #);");
    }

    public void putMethod(String name, String mangledName, String[] parameters, String returnType, boolean isStatic)
    {
	boolean isConstructor = name.equals("_init");
	String proctype = (isConstructor) ? "cons" : ((isStatic)? "static_proc" : "proc");
	if (mangledName!=null){
	    putln(mangledName + ": " 
		  + proctype + " " 
		  + comment(((isConstructor) ? "constructor" : name)));
	} else {
	    putln(mapReserved(name) + ": " + proctype);
	}
	
	indent(+2);
	indent(); put("(# ");
	if (returnType!=null){
	    put("result: " + mapReserved(returnType) + ";");
	}
	nl();
	indent(+3);
	if (parameters.length>0){
	    int n = 0;
	    for (int i = 0; i<parameters.length; i++){
		putln("arg" + (++n) + ": " + mapReserved(parameters[i]) + ";");
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
	if (mangledName!=null && !isConstructor) {
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

    public void putTrailer(String packageName, String className)
    {
	indent(-3);
	putln("do '" + packageName + '/' + className + "' -> className;");
	indent(+3);
	putln("INNER;");
	indent(-3);
	putln("#);\n");
	indent(-2);
    }

    public void close(){
	if (out != System.out) out.close();
    }
}
