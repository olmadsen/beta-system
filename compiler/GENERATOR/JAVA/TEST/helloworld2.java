/** 
 * The HelloWorldApp class implements an application that
 * simply displays "Hello World!" to the standard output.
 * 
 * compile with (Sun)
 *   javac -g:none helloworld2.java
 * or (GNU gcc3.1)
 *   gcj helloworld2.java

 * run with
 *   java HelloWorld 

 * examine with (Sun)
 *   javap -c  -private -s -verbose HelloWorld2
 * or (GNU gcc3.1)
 *   jcf-dump -c HelloWorld2
 * 
 */
class HelloWorld2 {
    public String hello;
    public String world;

    public void print(int mode){
	if (mode==0){
	    System.out.print(hello);
	} else {
	    System.out.println(world);
	}	
    }

    public static void main(String[] args) {
	HelloWorld2 hw2  = new HelloWorld2();
	hw2.hello = "Hello, ";
	hw2.world = "World!";
	hw2.print(0);
	hw2.print(1);
    }
}
