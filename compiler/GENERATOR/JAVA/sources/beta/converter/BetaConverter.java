package beta.converter;

import java.lang.*;
import java.io.*;
import java.util.*;

class BetaConverter
{
    static void usage(){
	System.out.println("Usage: BetaConverter <java class-file>\n");
	System.exit(1);
    }

    static boolean isClassFile(String name){
	DataInputStream stream;

	if (!name.endsWith(".class")) return false;
	File file = new File(name);
	try {
	     stream = new DataInputStream(new FileInputStream(file));
	} catch (FileNotFoundException e){
	    return false;
	}
	try {
            if ((stream.readInt() & 0xFFFFFFFFL) != 0xCAFEBABEL) return false;
        } catch (IOException e) {
            return false;
        }

	return true;
    }

    public int convert(String classfilename){
	return 0;
    }

    public static void main(String[] args){
	if (args.length == 1){
	    if (isClassFile(args[0])){
		System.out.println("Converting class file " + args[0] + "\n");
		System.exit(new BetaConverter().convert(args[0]));
	    } else {
		System.out.println("Argument \"" + args[0] + "\" is not a Java class file\n");
		System.exit(1);
	    }
	} else {
	    usage();
	}
    }
}
