/*
  Compilation: 
    jbeta Bclass.bet
    javac -d jvm -classpath jvm/Bclass.jar BclassUser.java
  Execution UNIX:
    java -classpath "jvm/Bclass.jar:jvm" betauser.BclassUser
  Execution Windows:
    java -classpath "jvm/Bclass.jar;jvm" betauser.BclassUser
*/ 

package betauser;
import beta.*;

class Jclass extends Bclass
{
  // Java constructor must transfer origin object to BETA constructor
  Jclass(betaenv origin)
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
