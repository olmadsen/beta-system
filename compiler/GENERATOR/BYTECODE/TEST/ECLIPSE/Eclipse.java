import org.eclipse.ui.betaeditor.beta.*;
   
public class Eclipse
{
    public static void main(String args[])
    {
	BetaAutoIndentStrategy bais;

	System.out.println("Eclipse: creating BetaAutoIndentStrategy.");
	bais = new BetaAutoIndentStrategy();
	System.out.println("Eclipse: calling customizeDocumentCommand.");
	bais.customizeDocumentCommand(null, null);
	System.out.println("Eclipse: done.");
    }

}
