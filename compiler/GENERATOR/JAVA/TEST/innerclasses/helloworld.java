import java.lang.*;

class HelloWorld {

    public String print(){
	return "Hello " + new World().print();
    }

    public class World {
	public String print(){
	    return "World "; 
	}
    }

    public static void main(String[] args) {
	System.out.println(new HelloWorld().print());
    }
}
