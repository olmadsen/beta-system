beta:
	beta -qw writehello
	./writehello
dump:
	jcf-dump -c HelloWorld
run:
	java HelloWorld
java:
	javac -g:none helloworld.java

beta2:
	beta -qw writehello2
	./writehello2
dump2:
	jcf-dump -c HelloWorld2
run2:
	java HelloWorld2
java2:
	javac -g:none helloworld2.java

danish:
	beta -qw writedanish
	./writedanish
dumpdanish:
	jcf-dump -c Danish
rundanish:
	java Danish
javadanish:
	javac -g:none danish.java

pi:
	beta -qw writepi
	./writepi
dumppi:
	jcf-dump -c Pi
runpi:
	java Pi
javapi:
	javac -g:none pi.java
odpi:
	od -A x -x Pi.class


clean:
	-@rm -f *~ *.dump *.class *.ast *.astL *.a2s *.lst writehello writehello2 writedanish writepi
	-@rm -rf sun4s linux nti_ms nti_gnu

