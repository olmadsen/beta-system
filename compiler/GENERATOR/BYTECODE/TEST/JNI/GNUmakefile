# Using SUN compilers
# CC             = cc
# LD             = cc -G

# Using GNU compilers
CC               = gcc -Wall -static
LD               = gcc -Wl,-G

JAVAHOME	 = /users/datpete/bin/sun4/j2sdk1.4.1_02
JAVA_CLASSPATH   = jvm

JNI_CHECK        = -Xcheck:jni
JNI_INCLUDE      = -I $(JAVAHOME)/include -I $(JAVAHOME)/include/solaris
JNI_LIBRARY_PATH = jvm

VPATH            = jvm:jvm/beta
MAKEFLAGS	 = --no-print-directory

####################### Clean directory #################################

clean:
	-rm -rf helloworld *.bat *.exe jvm *.class *.ast *.a2s *.astL helloworld *.so *.o *~ 

####################### BETA build ######################################

beta: clean
	@echo ""
	@echo Compiling BETA program and JNI wrappers:
	jbeta -s 23 helloworld.bet
	@echo ""
	@echo Running BETA program:
	./helloworld
	@echo ""

####################### JAVA only build #################################

## Directory to place temporaries into
jvm:
	mkdir -p jvm

## Actual library being interfaces
realhello.o: jvm realhello.c realhello.h
	@echo Compiling native library:
	$(CC) -c -I . -I jvm -o jvm/realhello.o realhello.c

## JNI glue steps
hellolib.class: jvm hellolib.java
	@echo Compiling native JAVA wrapper:
	javac -d jvm hellolib.java
beta_hellolib.h: hellolib.class
	@echo Generating C/C++ header:
	javah -jni -d jvm -classpath jvm beta.hellolib
hellolib.o: jvm_beta_hellolib.h
	@echo Compiling native C wrapper:
	$(CC) -c -I . -I jvm $(JNI_INCLUDE) -o jvm/hellolib.o hellolib.c
libhellolib.so: hellolib.o realhello.o
	@echo Creating shared library:
	$(LD) -o jvm/libhellolib.so jvm/hellolib.o jvm/realhello.o
helloworld.class: helloworld.java
	@echo Compiling JAVA example program:
	javac -classpath jvm -d jvm helloworld.java

java: 
	@echo ""
	@echo Generating JNI example:
	@echo ""
	@$(MAKE) libhellolib.so
	@$(MAKE) helloworld.class
	@echo ""
	@echo Running JAVA JNI example:
	@echo ""
	@sh -c 'LD_LIBRARY_PATH=$(JNI_LIBRARY_PATH); export LD_LIBRARY_PATH; java -classpath jvm $(JNI_CHECK) helloworld'

