/** 
 * The HelloWorldApp class implements an application that
 * simply displays "Hello World!" to the standard output.
 * 
 * compile with (Sun)
 *   javac -g:none helloworld.java
 * or (GNU gcc3.1)
 *   gcj helloworld.java

 * run with
 *   java HelloWorld 

 * examine with (Sun)
 *   javap -c  -private -s -verbose HelloWorld
 * or (GNU gcc3.1)
 *   jcf-dump -c HelloWorld
 * 
 */
class HelloWorld {
    public static void main(String[] args) {
	System.out.println("Hello World!"); //Display the string.
    }
}
