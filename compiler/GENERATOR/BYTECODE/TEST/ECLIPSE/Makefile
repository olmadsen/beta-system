ECLIPSE_INSTALLDIR=C:/eclipse2/eclipse/workspace/org.eclipse.ui.betaeditor/bin

java: clean java_indenter eclipse
	java -classpath jvm Eclipse

beta: clean beta_indenter eclipse
	java -classpath ../jvm:jvm Eclipse

jvm:
	mkdir jvm

dummies: jvm
	javac -classpath jvm -d jvm IDocument.java
	javac -classpath jvm -d jvm DefaultAutoIndentStrategy.java
	javac -classpath jvm -d jvm DocumentCommand.java

java_indenter: dummies
	javac -classpath jvm -d jvm Screen.java
	javac -classpath jvm -d jvm BetaAutoIndentStrategy.java

beta_indenter: dummies
	jbeta -s 188 BetaAutoIndentStrategy.bet

eclipse:
	javac -classpath jvm -d jvm Eclipse.java

install: clean beta_indenter
	cp ../jvm/*.class $(ECLIPSE_INSTALLDIR)
	cp jvm/org/eclipse/ui/betaeditor/beta/*.class $(ECLIPSE_INSTALLDIR)/org/eclipse/ui/betaeditor/beta

java_install: clean java_indenter
	echo Copying jvm/*.class
	cp jvm/*.class $(ECLIPSE_INSTALLDIR)
	echo Copying jvm/org/eclipse/ui/betaeditor/beta/*.class
	cp jvm/org/eclipse/ui/betaeditor/beta/*.class $(ECLIPSE_INSTALLDIR)/org/eclipse/ui/betaeditor/beta

clean:
	rm -rf jvm *.a2s *.ast *.astL *~ 
