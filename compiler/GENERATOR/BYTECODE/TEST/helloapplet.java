// javac -d jvm helloapplet.java;
// jar cf jvm/helloapplet.jar -C jvm beta/helloapplet.class
// 
// Then either
//    1. Open helloapplet.html in browser
// or
//    2. appletviewer [-debug] helloapplet.html

package beta;

import java.applet.Applet;
import java.awt.Graphics;

public class helloapplet extends Applet {
    public void paint(Graphics g) {
	g.drawString("Hello Applet world from Java!", 50, 24);
    }
}
