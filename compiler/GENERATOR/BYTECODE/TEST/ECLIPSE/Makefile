#ECLIPSE_INSTALLDIR=/tmp
#COPY=cp

ECLIPSE_INSTALLDIR=C:\eclipse2\...
COPY=copy

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
	javac -classpath jvm -d jvm BetaAutoIndentStrategy.java

beta_indenter: dummies
	jbeta -s 188 BetaAutoIndentStrategy.bet

eclipse:
	javac -classpath jvm -d jvm Eclipse.java

install: clean beta_indenter
	$(COPY) ../jvm/*.class $(ECLIPSE_INSTALLDIR)
	$(COPY) jvm/org/eclipse/ui/betaeditor/*.class $(ECLIPSE_INSTALLDIR)

clean:
	/bin/rm -rf jvm *.a2s *.ast *.astL *~ 
