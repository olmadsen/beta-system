beta:
	jbeta helloworld.bet
	./helloworld

java: jvm/libhellolib.so jvm/helloworld.class
	LD_LIBRARY_PATH=jvm:$LD_LIBRARY_PATH; export LD_LIBRARY_PATH; java -classpath jvm helloworld

jvm/beta/hellolib.class: hellolib.java
	mkdir -p jvm
	javac -d jvm hellolib.java
jvm/beta_hellolib.h: jvm/beta/hellolib.class
	javah -d jvm -classpath jvm -jni beta.hellolib
jvm/libhellolib.so: hellolib.c realhello.c realhello.h jvm/beta_hellolib.h
	gcc -Wl,-G -I . -I jvm -I /home/java/Solaris/include -I /home/java/Solaris/include/solaris -o jvm/libhellolib.so hellolib.c realhello.c
jvm/helloworld.class: helloworld.java
	javac -d jvm -classpath jvm helloworld.java

clean:
	rm -rf *~ *.ast *.astL *.a2s *.lst *.class *.so beta_hellolib.h beta jvm helloworld helloworld-jdb
