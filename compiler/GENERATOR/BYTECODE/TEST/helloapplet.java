// javac helloapplet.java;
// mkdir -p javabc
// mv helloapplet.class javabc/
// Then either
//    1. Open helloapplet.html in browser
// or
//    2. appletviewer [-debug] helloapplet.html

import java.applet.Applet;
import java.awt.Graphics;

public class helloapplet extends Applet {
    public void paint(Graphics g) {
	g.drawString("Hello Applet world from Java!", 50, 24);
    }
}
