import beta.*;
import org.eclipse.ui.betaeditor.beta.*;
import org.eclipse.jface.text.*;
   
public class Eclipse
{
    public static void main(String args[])
    {
	BetaAutoIndentStrategy bais;
	Screen s = new Screen();
	s.putline("Eclipse Screen.Putline");

	System.out.println("Eclipse: creating BetaAutoIndentStrategy.");
	bais = new BetaAutoIndentStrategy();
	System.out.println("Eclipse: calling customizeDocumentCommand.");
	bais.customizeDocumentCommand(new IDocumentImpl(), new DocumentCommand());
	System.out.println("Eclipse: done.");
    }

}

class IDocumentImpl implements IDocument
{
    public String get() { 
	return "IDocumentImpl";
    }

    public void replace(int x, int y, String s){ 
    }
}
