/*
   Usage:
    1. cd googleapi; jar xf googleapi.jar; cd ..  // Why!?
    2. javac -classpath googleapi google.java
    3. java -classpath .:googleapi google
       or
       java -classpath .:googleapi google beta.net
*/ 

// import com.google.soap.search; // fails???
import java.io.*;

public class google
{
    
  public static void main(String[] arguments) 
    { 
      String licence = "hweCKhQvbXY6kvKmOpDS2P3lTqQ5ggBu";
      String query = "";
      int i;
      for (i=0; i<arguments.length; i++) query += arguments[i] + " ";
      if (query == "") {
	System.out.print("Search Google for: ");
	query = readLn();
      }
      if (query == "") {
	query = "Ole Lehrmann Madsen BETA.NET";
      }
      System.out.println("\nSearching Google for: " + query);
      com.google.soap.search.GoogleSearch s = new com.google.soap.search.GoogleSearch();
      s.setKey(licence);
      s.setQueryString(query);
      try {
	  com.google.soap.search.GoogleSearchResult r = s.doSearch();
	  System.out.println("Results:" + "\n" + r.toString() + "\n");
      } catch (com.google.soap.search.GoogleSearchFault ne) { 
      }
    }

    public static String readLn() {
        //set aside memory for the keyboard input
        byte [] byteArray = new byte[300];
        
        //things which could fail should be enclosed
        // in a try/catch statement
        try {
            // read stdin into the byte array.
            System.in.read(byteArray);
        } catch (Exception e) {
            // if there is a failure, print an error
            e.printStackTrace();
        }
        
        //make a String from the array of bytes
        String result = new String(byteArray);
	
        //check for a return character, and only
        //keep the characters up to the return
        int newLineIndex = result.indexOf("\n");
        result = result.substring(0,newLineIndex);
        
        return result;
    }

}






