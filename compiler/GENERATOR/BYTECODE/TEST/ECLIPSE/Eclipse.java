import org.eclipse.ui.betaeditor.beta.*;
   
public class Eclipse
{
    public static void main(String args[])
    {
	BetaAutoIndentStrategy bais = new BetaAutoIndentStrategy();
	bais.customizeDocumentCommand(null, null);
    }

}
