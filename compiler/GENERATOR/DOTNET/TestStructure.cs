/* Compilation and run:
   csc /t:library Structure.cs
   csc /t:exe     /r:Structure.dll TestStructure.cs
   TestStructure.exe
*/

public class A : System.Object {
    public System.Object origin;
    public A(){ origin = null; }
    public A(System.Object o){ origin = o; }

    public virtual void id(){
	System.Console.WriteLine("A");
    }
}

public class B : A {
    public B(){ origin = null; }
    public B(System.Object o):base(o){}

    public override void id(){
	System.Console.WriteLine("B");
    }
}

public class TestStructure {
    public static void Main(System.String[] args){
	System.Object o = new System.Object();
	A a = new A(o);
	//B b = new B(o);

	Structure sa = Structure.objS(a); // FIXME: possibly origin as parameter
	sa.iOrigin = a.origin;

	//Structure sb = Structure.AlloS(a.origin, System.Type.GetType("B"));
	Structure sb = Structure.AlloS(a.origin, typeof(B));
	

	System.Console.Write("Id of object created from A##: ");
	A a2 = (A)sa.AlloSI();
	a2.id();

	System.Console.Write("Id of object created from B##: ");
	B b2 = (B)sb.AlloSI();
	b2.id();

	System.Console.Write("Is A## == A##? ");
	System.Console.WriteLine(Structure.eqS(sa, sa));

	System.Console.Write("Is B## == B##? ");
	System.Console.WriteLine(Structure.eqS(sb, sb));

	System.Console.Write("Is A## == B##? ");
	System.Console.WriteLine(Structure.eqS(sa, sb));

	System.Console.Write("Is A## < B##? ");
	System.Console.WriteLine(Structure.ltS(sa, sb));

	System.Console.Write("Is A## > B##? ");
	System.Console.WriteLine(Structure.gtS(sa, sb));

	System.Console.Write("Is A## <= B##? ");
	System.Console.WriteLine(Structure.leS(sa, sb));

	System.Console.Write("Is A## => B##? ");
	System.Console.WriteLine(Structure.geS(sa, sb));
    }
}
