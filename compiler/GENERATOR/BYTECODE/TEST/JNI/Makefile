clean:
	-rm -rf jvm *.ast *.a2s *.astL *.h helloworld *.so *~ 

compile_beta:
	jbeta helloworld.bet

beta: compile_beta
	./helloworld

java: compile_beta
	javac -d jvm -classpath jvm helloworld.java
	LD_LIBRARY_PATH=jvm; export LD_LIBRARY_PATH; java -cp jvm helloworld
