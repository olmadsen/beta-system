/*
  Compilation statements: 
    (make clean; jbeta -x tstenv; \rm -f javabc/String.class)
    jbeta -x Bclass.bet
    javac -d javabc -classpath javabc BclassUser.java
    java -classpath javabc BclassUser
*/ 

class Jclass extends Bclass
{
  // Java constructor must transfer origin object to BETA constructor
  Jclass(tstenv origin)
    {
	super(origin);
    }

  public void compute(int arg)
    {
      System.out.println("Java: compute(" + arg + ") called. Calling BETA");
      super.compute(arg); 
    }
}


class BclassUser
{
    public static void main(String args[])
    {
	betaenv env = new betaenv(null);
	env.init();
	Bclass b = new Jclass(env);
	b.set(9);
	System.out.println(b.get());
	b.compute(10);
	System.out.println(b.get());
	b.compute(-6);
	System.out.println(b.get());
	b.compute(40);
	System.out.println(b.get());
    } 
    
}
