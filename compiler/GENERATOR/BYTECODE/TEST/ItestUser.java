/*
  javac ItestUser.java
  java ItestUser
*/

class ItestUser
{
    public static void main(String args[])
    {
	Itest myItest = new ItestImpl();
	System.out.println("Itest implemented by " + myItest.describe());
    } 
}
