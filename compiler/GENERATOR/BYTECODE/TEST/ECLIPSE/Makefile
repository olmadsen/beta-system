ECLIPSE_INSTALLDIR=C:/eclipse2/eclipse/workspace/org.eclipse.ui.betaeditor
JBETA=BETART=simpledump; export BETART; jbeta -qw -s 188 # --mute 
JAVAC=javac -classpath jvm -d jvm

fastbeta: BetaAutoIndentStrategy eclipse
	java -classpath "jvm/BetaAutoIndentStrategy.jar:jvm" Eclipse

beta: clean beta_indenter eclipse
	java -classpath "jvm/BetaAutoIndentStrategy.jar:jvm" Eclipse

beta.windows: clean beta_indenter eclipse
	java -classpath "jvm/BetaAutoIndentStrategy.jar;jvm" Eclipse

java: clean java_indenter eclipse
	java -classpath "jvm" Eclipse

jvm:
	mkdir jvm

dummies: jvm 
	$(JAVAC) IDocument.java
	$(JAVAC) DefaultAutoIndentStrategy.java
	$(JAVAC) DocumentCommand.java
	$(JAVAC) Screen.java

BetaAutoIndentStrategy: 
	$(JBETA) BetaAutoIndentStrategy.bet

beta_indenter: dummies BetaAutoIndentStrategy

java_indenter: dummies
	$(JAVAC) BetaAutoIndentStrategy.java

eclipse: 
	$(JAVAC) Eclipse.java

clean:
	rm -rf jvm *.a2s *.ast *.astL *~ *.out *.run
