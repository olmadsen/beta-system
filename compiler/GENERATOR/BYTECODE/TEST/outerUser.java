import beta.*;

class outerUser {
    public static void main(String[] args) {
        betaenv B = new betaenv(null);
	beta.outer X = new outer(B);
        outer.inner1 Q = X.new inner1();

    }

}
