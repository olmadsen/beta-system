// javac helloapplet.java
// jar cf helloapplet.jar helloapplet.class
// Open helloapplet.html in browser

import java.applet.Applet;
import java.awt.Graphics;

public class helloapplet extends Applet {
    public void paint(Graphics g) {
	g.drawString("Hello world!", 50, 25);
    }
}
