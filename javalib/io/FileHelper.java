package beta;

public class FileHelper
{
    public static int lastModifiedAsSeconds(java.io.File F){
	return (int)(F.lastModified()/1000);
    }

    public static void setLastModifiedAsSeconds(java.io.File F, int time){
	F.setLastModified((long)time*1000);
    }

    public static int lengthAsInt(java.io.File F){
	return (int)(F.length());
    }
}
