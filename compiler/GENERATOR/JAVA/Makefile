JAVAC = javac -sourcepath sources -d classes -classpath classes 

BetaConverter.class: 
	mkdir -p classes/beta/converter
	$(JAVAC) sources/beta/converter/BetaConverter.java

clean:
	/bin/rm -f *~ *.class *.ast *.astL *.a2s \#*
	/bin/rm -rf classes


