package betauser;
import beta.*;

class Bclass2User
{
    public static void main(String args[])
    {
	betaenv env = new betaenv(null); 
	env.init();                      
	
	Bclass2 b = new Bclass2(env, 407); 

	System.out.println(b.get());
	b.compute(10);
	System.out.println(b.get());
	b.compute(-6);
	System.out.println(b.get());
	b.compute(40);
	System.out.println(b.get());
    } 
    
}
