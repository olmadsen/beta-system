ECLIPSE_INSTALLDIR=C:/eclipse2/eclipse/workspace/org.eclipse.ui.betaeditor
BETALIB=C:/beta/r5.3

java: clean java_indenter eclipse
	java -classpath jvm Eclipse

beta: clean beta_indenter eclipse
	java -classpath "$(BETALIB)/basiclib/jvm/betaenv.jar:jvm:" Eclipse

beta.windows: clean beta_indenter eclipse
	java -classpath "$(BETALIB)/basiclib/jvm/betaenv.jar;jvm" Eclipse

jvm:
	mkdir jvm

dummies: jvm 
	javac -classpath jvm -d jvm IDocument.java
	javac -classpath jvm -d jvm DefaultAutoIndentStrategy.java
	javac -classpath jvm -d jvm DocumentCommand.java
	javac -classpath jvm -d jvm Screen.java

beta_indenter: dummies
	cd $(BETALIB)/basiclib ; jbeta --mute -qw -s 188 betaenv
	jbeta --mute -qw -s 188 BetaAutoIndentStrategy.bet

eclipse:
	javac -classpath jvm -d jvm Eclipse.java

install: clean beta_indenter
	cp $(BETALIB)/basiclib/jvm/betaenv.jar $(ECLIPSE_INSTALLDIR)
	cp jvm/org/eclipse/ui/betaeditor/beta/*.class $(ECLIPSE_INSTALLDIR)/bin/org/eclipse/ui/betaeditor/beta


clean:
	rm -rf jvm *.a2s *.ast *.astL *~ *.out *.run
