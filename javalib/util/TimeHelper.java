package beta;

public class TimeHelper
{
    public static java.util.Date DateFromSeconds(int seconds){
	return new java.util.Date((long)seconds*1000);
    }
}
