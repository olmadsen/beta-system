package beta;

public class DateHelper
{
    public static java.util.Date DateFromSeconds(int seconds){
	return new java.util.Date((long)seconds*1000);
    }
    public static java.util.Date DateNow(){
	return new java.util.Date();
    }
}
