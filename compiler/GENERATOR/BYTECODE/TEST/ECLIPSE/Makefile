ECLIPSE_INSTALLDIR=C:/eclipse2/eclipse/workspace/org.eclipse.ui.betaeditor
JBETA=jbeta --mute -qw -s 188
JAVAC=javac -classpath jvm -d jvm

fastbeta: BetaAutoIndentStrategy eclipse
	java -classpath "jvm/BETALIB.jar:jvm" Eclipse

beta: clean beta_indenter eclipse
	java -classpath "jvm/BETALIB.jar:jvm" Eclipse

beta.windows: clean beta_indenter eclipse
	java -classpath "jvm/BETALIB.jar;jvm" Eclipse

jvm:
	mkdir jvm

dummies: jvm 
	$(JAVAC) IDocument.java
	$(JAVAC) DefaultAutoIndentStrategy.java
	$(JAVAC) DocumentCommand.java
	$(JAVAC) Screen.java

betalib: 
	$(JBETA) BETALIB
BetaAutoIndentStrategy: 
	$(JBETA) BetaAutoIndentStrategy.bet

beta_indenter: dummies betalib BetaAutoIndentStrategy

eclipse: 
	$(JAVAC) Eclipse.java

install: clean beta_indenter
	cp jvm/BETALIB.jar $(ECLIPSE_INSTALLDIR)
	cp jvm/org/eclipse/ui/betaeditor/beta/*.class $(ECLIPSE_INSTALLDIR)/bin/org/eclipse/ui/betaeditor/beta


clean:
	rm -rf jvm *.a2s *.ast *.astL *~ *.out *.run
