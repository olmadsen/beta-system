package betauser;
import beta.*;

class Bclass2User
{
    public static void main(String args[])
    {
	Bclass2 b = new Bclass2(); // brug af __init, OK, men fejler når _init (eller andre cons) tilstede

	System.out.println(b.get());
	b.compute(10);
	System.out.println(b.get());
	b.compute(-6);
	System.out.println(b.get());
	b.compute(40);
	System.out.println(b.get());
    } 
    
}
