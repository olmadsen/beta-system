/*
   compilation:
     csc -nologo -t:exe -r:"$BETALIB/basiclib/clr/betaenv.dll,$BETALIB/basiclib/private/clr/Component.dll" Coroutine.cs
 */

public abstract class Coroutine: BetaObject {
   
    public Coroutine(){
	_comp = new Component(this);
    }

    public void call() { _comp.swap(); }

    protected void suspend() { _comp.swap(); }
}
