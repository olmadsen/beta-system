

class cafebabe {
    
    void baadfood(Object r){
	System.arraycopy(r, 0, this /*!!*/, 0, 5); 
    }
    void cheer(){
	System.out.println("Yikes!");
    }

    public static void main(String[] args) {
	int[] r = { 1, 2, 3, 4, 5 };
	cafebabe pamela = new cafebabe();
	pamela.baadfood(r);
	pamela.cheer();
    }
}
