/*
   compilation:
     javac -classpath "$BETALIB/basiclib/jvm;$BETALIB/basiclib/private/jvm;." Coroutine.java
 */

import beta.BetaObject;
import beta.Component;

public abstract class Coroutine extends BetaObject {
   
    public Coroutine(){
	comp$ = new Component(this);
    }

    public void call() { comp$.swap(); }

    public void suspend() { comp$.swap(); }
}
