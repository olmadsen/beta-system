# Using SUN compilers
# CC             = cc
# LD             = cc -G

# Using GNU compilers
CC               = gcc -static
LD               = gcc -Wl,-G

JNI_CHECK        = -Xcheck:jni
JNI_INCLUDE      = -I /users/datpete/src/j2sdk1.4.0_01/include -I /users/datpete/src/j2sdk1.4.0_01/include/solaris
JNI_LIBRARY_PATH = .

clean:
	-rm -rf jvm *.class *.ast *.a2s *.astL *.h helloworld *.so *.o *~ 

## BETA build


beta:
	jbeta helloworld.bet
	./helloworld

## JAVA only build

hellolib.class: hellolib.java
	@echo Compiling native JAVA wrapper:
	javac hellolib.java
hellolib.h: hellolib.class
	@echo Generating C/C++ header:
	javah -jni hellolib
hellolib.o: hellolib.h
	@echo Compiling native library:
	$(CC) -c -I . $(JNI_INCLUDE) -o hellolib.o hellolib.c
libhellolib.so: hellolib.o
	@echo Creating shared library:
	$(LD) -o libhellolib.so hellolib.o
helloworld.class: helloworld.java
	@echo Compiling JAVA example program:
	javac helloworld.java

java: 
	@echo ""
	@echo Generating JNI example:
	@echo ""
	@$(MAKE) libhellolib.so
	@$(MAKE) helloworld.class
	@echo ""
	@echo Running JAVA JNI example:
	@echo ""
	sh -c 'LD_LIBRARY_PATH=$(JNI_LIBRARY_PATH); export LD_LIBRARY_PATH; java $(JNI_CHECK) helloworld'

