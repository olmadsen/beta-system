/* Example of using BETA-like Component.cs to
   implement a coroutine package for C#.

   class Coroutine is a superclass for C# coroutines
 */

using System;

class Adder: Coroutine {
    public int res;
    int start;
    public Adder(int s) { 
      start = s; 
    }
    void compute(int V){
	res = V+V;
        A: suspend();
	compute(V+1);
    }
    public override void Do() {
	compute(start);
    }
}
class Multiplier: Coroutine {
    public int res;
    int start;
    public Multiplier(int s) { 
      start = s;
    }
    void compute(int V){
	res = V*V;
        M: suspend();
	compute(V+1);
    }
    public override void Do() {
	compute(start);
	suspend();
    }
}

class Merger: Coroutine {
    Adder A = new Adder(3);
    Multiplier M = new Multiplier(2);
    public override void Do() {
        A.call();
        M.call();
      	for (int i=0; i<6; i++){
	    if (A.res < M.res) {
		System.Console.WriteLine("A: " + A.res);
		A.call();
	    } else {
		System.Console.WriteLine("M: " + M.res);
		M.call();
	    }
	}
    }      
    public static void Main(String[] args) {
	Merger merger = new Merger();
	merger.call();
    }
}

