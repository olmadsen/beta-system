/* Example of using BETA's Component.java to
   implement a coroutine package for Java.

   class Coroutine is a superclass for Java coroutines

   Example included

   Use
     javac -classpath "../../jvm;./jvm;jvm;." CoEx.java
     java  -classpath "../../jvm;./jvm;jvm;." CoEx

*/
import beta.*;

class Coroutine extends BetaObject {
    private Component thisC;
 
    public Coroutine(){ thisC = new Component(this); }

    public void call(){	thisC.swap(); }

    public void suspend () { thisC.swap(); }
}

class MyCo1 extends Coroutine {
    public void xdo() { 
       System.out.println("MyCo1:begin"); 
       suspend();
       System.out.println("MyCo1:middle"); 
       suspend();
       System.out.println("MyCo1:end"); 
    }
}

class MyCo2 extends Coroutine {
    public void xdo() { 
       System.out.println("MyCo2:begin"); 
       suspend();
       System.out.println("MyCo2:end"); 
    }
}


class CoEx extends Coroutine {
    MyCo1 C1 = new MyCo1();
    MyCo2 C2 = new MyCo2();

    public void xdo() { 
        System.out.println("CoEx :begin");
        C1.call();
        System.out.println("CoEx :middle:a");
	C2.call();
        System.out.println("CoEx :middle:b");
	C1.call();
        System.out.println("CoEx :middle:c");
	C2.call();
        System.out.println("CoEx :middle:d");
	C1.call();
        System.out.println("CoEx :end");
    }

    public static void main(String args[]) {
	CoEx C = new CoEx();
        C.call();
    }
}
