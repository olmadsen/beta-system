JAVAC = javac -sourcepath src -d classes -classpath classes 

JavaConverter.class: 
	mkdir -p classes/beta/converter
	$(JAVAC) src/beta/converter/JavaConverter.java

clean:
	/bin/rm -f *~ *.class *.ast *.astL *.a2s \#*
	/bin/rm -rf classes


