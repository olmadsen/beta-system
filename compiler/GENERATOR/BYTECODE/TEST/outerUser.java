package betauser;
=======
/*
  Compilation: 
    jbeta outer.bet
    javac -d jvm -classpath jvm/outer.jar outerUser.java
  Execution UNIX:
    java -classpath "jvm/outer.jar:jvm" outerUser
  Execution Windows:
    java -classpath "jvm/outer.jar;jvm" BclassUser
*/ 

import beta.*;

class outerUser {
    public static void main(String[] args) {
        betaenv B = new betaenv(null);
	B.init();
	outer X = new outer(B);
        outer.inner1 Q = X.new inner1();
	outer.inner1.inner1_2 W = Q.new inner1_2();
	Q.hello();
	W.world();
    }

}
