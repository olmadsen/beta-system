public abstract class array {
    Object Q[];
    String S[] = new String[3];
    public void go(){
	Q = S;
	S = (String[])Q;
	    }
}
