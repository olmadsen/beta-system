package betauser;
import beta.*;

class Bclass2User
{
    public static void main(String args[])
    {
	Bclass2 b = Bclass2.create(); // static constructor; bliver ikke static i jbeta

	System.out.println(b.get());
	b.compute(10);
	System.out.println(b.get());
	b.compute(-6);
	System.out.println(b.get());
	b.compute(40);
	System.out.println(b.get());
    } 
    
}
