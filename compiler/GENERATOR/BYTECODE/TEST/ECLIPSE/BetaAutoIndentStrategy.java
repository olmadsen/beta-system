package org.eclipse.ui.betaeditor.beta;

import org.eclipse.jface.text.DefaultAutoIndentStrategy;
import org.eclipse.jface.text.DocumentCommand;
import org.eclipse.jface.text.IDocument;


/**
 * Auto indent strategy
 */
public class BetaAutoIndentStrategy extends DefaultAutoIndentStrategy {
    
    public BetaAutoIndentStrategy() {
    }
    
    /* Method declared on IAutoIndentStrategy */
    public void customizeDocumentCommand(IDocument d, DocumentCommand c) {
	//if ("\t".equals(c.text)) {
	//    // Tab
	//    c.text = "";
	//    c.length = 0;
	//    System.out.println("Indent...");
	//}
	//else if ("\r\n".equals(c.text)) {
	//    // Enter
	//    System.out.println("Indent...");
	//}
	Screen s = new Screen();
	s.putline("customizeDocumentCommand JAVA");
    }
    
}
