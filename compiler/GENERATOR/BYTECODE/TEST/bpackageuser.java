// see bpackage.bet

import foo.bar.*;
import beta.*;

public class bpackageuser
{
    public static void main(String args[])
    { 
	betaenv env = new betaenv(null);
	env.init();
	bpackage BP = new bpackage(env);
	BP.go();
    }
}
 
