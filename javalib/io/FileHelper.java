package beta;

public class FileHelper
{
    public static int lastModifiedAsSeconds(java.io.File F){
	return (int)(F.lastModified()/1000);
    }
}
