java: clean
	mkdir jvm
	javac -classpath jvm -d jvm IDocument.java
	javac -classpath jvm -d jvm DefaultAutoIndentStrategy.java
	javac -classpath jvm -d jvm DocumentCommand.java
	javac -classpath jvm -d jvm BetaAutoIndentStrategy.java
	javac -classpath jvm -d jvm Eclipse.java
	java -classpath jvm Eclipse

beta: clean
	mkdir jvm
	javac -d jvm IDocument.java
	javac -d jvm DefaultAutoIndentStrategy.java
	javac -d jvm DocumentCommand.java
	jbeta -s 188 BetaAutoIndentStrategy.bet
	javac -classpath jvm -d jvm Eclipse.java
	java -classpath jvm Eclipse

clean:
	/bin/rm -rf jvm *.a2s *.ast *.astL *~ 
