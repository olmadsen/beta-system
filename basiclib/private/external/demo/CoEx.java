/* Example of using BETA-like Component.java to
   implement a coroutine package for Java.

   class Coroutine is a superclass for Java coroutines

*/

class MyCo1 extends Coroutine {
    public void foo() {
       System.out.println("MyCo1:middle"); 
       suspend();
    }
    public void Do() { 
       System.out.println("MyCo1:begin"); 
       suspend();
       foo();
       System.out.println("MyCo1:end"); 
    }
}

class MyCo2 extends Coroutine {
    public void Do() { 
       System.out.println("MyCo2:begin"); 
       suspend();
       System.out.println("MyCo2:end"); 
    }
}


class CoEx extends Coroutine {
    MyCo1 C1 = new MyCo1();
    MyCo2 C2 = new MyCo2();

    public void Do() { 
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
