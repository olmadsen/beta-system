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

    boolean local;

    public BetaOutput(String betalib, 
		      String pkg, 
		      String cls, 
		      String supPkg, 
		      String sup, 
		      int overwrite,
		      boolean local,
		      PrintStream outstream)
	throws Throwable
    {
        this.local = local;
	openStream(betalib, pkg, "_" + cls, overwrite, local, outstream);
	if (out!=null) putWrapper(pkg, cls, supPkg, sup);
	openStream(betalib, pkg, cls, overwrite, local, outstream);
    }

    File getParent(File entry)
    {
	File parent = entry.getParentFile();
	if (parent==null){
	    /* File.getParentFile can return null when the file is specified without
	     * a directory.
	     */
	    if (entry.isAbsolute()){
		parent = new File(File.separator);
	    } else {
		parent = new File(System.getProperty("user.dir"));
	    }
	}
	return parent;
    }

    String getUpPath(String packageName){
	String path = "";
	int lastCh = 0;
	while ( (lastCh=packageName.indexOf("/", lastCh+1)) != -1 ){
	    path += "../";
	}
	return path;
    }

    String fixPackagePath(String pkg)
    {
	String result;
	if (pkg==null){
	    result = "";
	} else {
	    result = pkg;
	    if (!pkg.endsWith("/")) result += "/";
	};
	return result;
    }

    void openStream(String betalib, 
		    String pkg, 
		    String cls, 
		    int overwrite,
		    boolean local,
		    PrintStream outstream)
	throws Throwable
    {
	pkg = fixPackagePath(pkg);
	if (local && !pkg.startsWith("java/")){
	    entry = new File(pkg + cls + ".bet");
	} else {
	    entry = new File(betalib + "/javalib/" + pkg + cls + ".bet");
	}
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
		// entry = new File(entry.getAbsolutePath() + ".new");
		out = null;
		return;
	    }
	}
	getParent(entry).mkdirs();
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
	if (out == System.out){
	    // no file involved
	    return;
	}
	if (existing!=null){
	    System.err.println("Existing \"" 
			       + existing.getAbsolutePath()
			       + "\"\n"
			       + "\t is up-to-date.");
	    System.err.println("\t Use -f or -F option if overwrite desired.");
	} else {
	    if (local){
		System.err.println("     --> \"" + entry.getPath() + "\"");
	    } else {
		System.err.println("     --> \"" + entry.getAbsolutePath() + "\"");
	    }
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
	} else if (word.equals("Hashtable")){
	    return prefix + "Java" + word;
	} else if (word.equals("Class")){
	    return prefix + "Java" + word;
	} else if (word.equals("Process")){
	    return prefix + "Java" + word;
	} 

	// Not reserved
	return prefix + word;
	
    }

    public void putPatternBegin(String className, String superClass){
        if (className.equals("Object")){
	    // Special case: Must be *declared* with special name,
	    // but all parameters of type Object should remain Object
	    // (for compatibility with BETA Object)
	    put("JavaObject: ");
	} else {
	    put(mapReserved(className) + ": ");
	 }
	if (superClass==null || superClass.equals("Object")){
	    put("ExternalClass");
	} else {
	    put(mapReserved(superClass));
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
	    String path;
	    superPkg    = fixPackagePath(superPkg);
	    packageName = fixPackagePath(packageName);
	    if (local && !superPkg.startsWith("java/")){
		path = getUpPath(packageName);
	    } else {
		path = "~beta/javalib/";
	    }
	    putln("INCLUDE '" + path + superPkg + superClass + "';");
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
	packageName = fixPackagePath(packageName);
	putln("ORIGIN '" + "_" + className + "';");
	if (includes!=null){
	    for (int i = 0; i<includes.length; i++){
		String path;
		String include = (String)includes[i];
		if (local && !include.startsWith("java/")){
		    path = getUpPath(packageName);
		} else {
		    path = "~beta/javalib/";
		}
		putln("INCLUDE '" + path + include + "';");
	    };
	};
	putln("--LIB: attributes--\n");
	putln("(* Java " + className + " class members.");
	putln(" * See " + "_" + className + ".bet for class declaration.");
	if (packageName.startsWith("java/")){
	    putln(" * See http://java.sun.com/j2se/" 
		  + System.getProperty("java.version") 
		  + "/docs/api/" 
		  + packageName + className + ".html");
	}
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
		if (parameters[i].startsWith("^") 
		    || parameters[i].startsWith("[0]") /* using Ref2Rep */) {
		    put("[]");
		}
	    }
	    put(")");
	    nl();
	    indent(+3);
	}
	indent(-3);
	if ((mangledName!=null && !isConstructor) || !name.equals(mapReserved(name)) ) {
	    indent();
	    put("do '" + name + "' -> procname;");
	    nl();
	}
	if (returnType!=null){
	    indent(); put("exit result");
	    if (returnType.startsWith("^") 
		|| returnType.startsWith("[0]") /* using Ref2Rep */) {
		put("[]");
	    }
	    nl();
	}
	putln("#);");
	indent(-2);
    }

    public void putTrailer(String packageName, String className)
    {
	indent(-3);
	packageName = fixPackagePath(packageName);
	putln("do '" + packageName + className + "' -> className;");
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
