public class hellolib
{
    public native void hello(String who);

    static {
	System.loadLibrary("hellolib");
    }
}
