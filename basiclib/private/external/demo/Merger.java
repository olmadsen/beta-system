/* Example of using BETA-like Component.java to
   implement a coroutine package for Java.

   class Coroutine is a superclass for Java coroutines

*/

class Producer1 extends Coroutine {
    public int res;
    int start, max;
    public Producer1(int s, int m) { 
      start = s; max = m; 
    }
    void compute(int V){
	res = V+V;
        suspend();
	if (V < max) compute(V+1);
    }
    public void Do() {
	compute(start);
	suspend();
	res = 1000000;
    }
}
class Producer2 extends Coroutine {
    public int res;
    int start, max;
    public Producer2(int s, int m) { 
      start = s; max = m; 
    }
    void compute(int V){
	res = V*V;
        suspend();
	if (V < max) compute(V+1);
    }
    public void Do() {
	compute(start);
	suspend();
	res = 1000000;
    }
}

class Merger {
    Producer1 P1 = new Producer1(3,6);
    Producer2 P2 = new Producer2(2,5);
    void merge() {
	int i;
        P1.call();
        P2.call();
      	for (i=0; i<6; i++){
	    if (P1.res < P2.res) {
		System.out.println("P1: " + P1.res);
		P1.call();
	    }
	    else {
		System.out.println("P2: " + P2.res);
		P2.call();
	    }
	}
    }      
    public static void main(String args[]) {
	Merger merger = new Merger();
	merger.merge();
    }
}

