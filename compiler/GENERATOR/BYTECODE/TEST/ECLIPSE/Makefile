ECLIPSE_INSTALLDIR=C:/eclipse2/eclipse/workspace/org.eclipse.ui.betaeditor

fastbeta: BetaAutoIndentStrategy eclipse
	java -classpath "jvm/BETALIB.jar:jvm" Eclipse

beta: clean beta_indenter eclipse
	java -classpath "jvm/BETALIB.jar:jvm" Eclipse

beta.windows: clean beta_indenter eclipse
	java -classpath "jvm/BETALIB.jar;jvm" Eclipse

jvm:
	mkdir jvm

dummies: jvm 
	javac -classpath jvm -d jvm IDocument.java
	javac -classpath jvm -d jvm DefaultAutoIndentStrategy.java
	javac -classpath jvm -d jvm DocumentCommand.java
	javac -classpath jvm -d jvm Screen.java

betalib: 
	jbeta --mute -qw -s 188 BETALIB
BetaAutoIndentStrategy: 
	jbeta --mute -qw -s 188 BetaAutoIndentStrategy.bet

beta_indenter: dummies betalib BetaAutoIndentStrategy

eclipse: 
	javac -classpath jvm -d jvm Eclipse.java

install: clean beta_indenter
	cp jvm/BETALIB.jar $(ECLIPSE_INSTALLDIR)
	cp jvm/org/eclipse/ui/betaeditor/beta/*.class $(ECLIPSE_INSTALLDIR)/bin/org/eclipse/ui/betaeditor/beta


clean:
	rm -rf jvm *.a2s *.ast *.astL *~ *.out *.run
