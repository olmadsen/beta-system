/* Example of using BETA-like Component.java to
   implement a coroutine package for Java.

   class Coroutine is a superclass for Java coroutines

*/

class Adder extends Coroutine {
    public int res;
    int start, max;
    public Adder(int s, int m) { 
      start = s; max = m; 
    }
    void compute(int V){
	res = V+V;
        A: suspend();
	if (V < max) compute(V+1);
    }
    public void Do() {
	compute(start);
	suspend();
	res = 1000000;
    }
}
class Multiplier extends Coroutine {
    public int res;
    int start, max;
    public Multiplier(int s, int m) { 
      start = s; max = m; 
    }
    void compute(int V){
	res = V*V;
        M: suspend();
	if (V < max) compute(V+1);
    }
    public void Do() {
	compute(start);
	suspend();
	res = 1000000;
    }
}

class Merger extends Coroutine {
    Adder A = new Adder(3,6);
    Multiplier M = new Multiplier(2,5);
    public void Do() {
	int i;
        A.call();
        M.call();
      	for (i=0; i<6; i++){
	    if (A.res < M.res) {
		System.out.println("A: " + A.res);
		A.call();
	    }
	    else {
		System.out.println("M: " + M.res);
		M.call();
	    }
	}
    }      
    public static void main(String args[]) {
	Merger merger = new Merger();
	merger.call();
    }
}

