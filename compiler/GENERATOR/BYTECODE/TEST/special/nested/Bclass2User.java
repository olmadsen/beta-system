package betauser;
import beta.*;

class Bclass2User
{
    public static void main(String args[])
    {
	Bclass2 b = new Bclass2(); // OK, brug af __init

	Bclass2.nested n = b.new nested(); // OK

	System.out.println(b.get());
	b.compute(10);
	System.out.println(b.get());
	b.compute(-6);
	System.out.println(b.get());
	b.compute(40);
	System.out.println(b.get());
    } 
    
}
