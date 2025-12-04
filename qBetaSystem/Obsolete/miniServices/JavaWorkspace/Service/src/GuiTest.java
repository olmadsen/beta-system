import java.awt.Color;
import java.awt.Component;
import java.awt.Container;
import java.awt.Dimension;
import java.awt.event.MouseEvent;
import java.awt.event.MouseListener;

import javax.swing.JButton;
import javax.swing.JFrame;
import javax.swing.JLabel;
import javax.swing.JPanel;
import javax.swing.JTextField;

public class GuiTest {

	public class MyMouseListener implements MouseListener {
		public void mousePressed(MouseEvent e) {
			//System.out.println("Mouse pressed (# of clicks: " + e.getClickCount() + " button:" + e.getButton() +")");
			if (e.getButton() == MouseEvent.BUTTON3) { // On Windows Shift&click gives 3 
				// On Mac shift&click always gives 1? A real mouse works
				//createPopupMenu(e.getComponent(),e.getX(),e.getY());
			}
		}
		public void mouseReleased(MouseEvent e) {
			// System.out.println("Mouse released (# of clicks: " + e.getClickCount() + ")");
		}

		public void mouseEntered(MouseEvent e) {
			System.out.println("Mouse entered");
		}

		public void mouseExited(MouseEvent e) {
			//System.out.println("Mouse exited");
		}

		public void mouseClicked(MouseEvent e) {
			System.out.println("Mouse clicked (# of clicks: " + e.getClickCount() + ")");
		}
	}
	JFrame newJframe(String title) {
		JFrame F = null;
		F = new JFrame(title);
		F.setSize(500,600);
		F.setVisible(true);
		return F;
	}

	void run() {
		JFrame C = null;
		C = newJframe("Hello"); 
		C.setPreferredSize(new Dimension(300,300)); // setSize does not work?
		//************** 
		JPanel JF = new JPanel();
		//JF.setVisible(true);
		JF.setPreferredSize(new Dimension(80,50));
		JF.setBackground(Color.red);
		MouseListener MS = new MyMouseListener();
		JF.addMouseListener(MS);
		C.add(JF);
		//**********************
		JPanel J = new JPanel();
		JF.add(J);
		//J.setVisible(true);
		J.setPreferredSize(new Dimension(80,50));
		J.setBackground(Color.red);
		MouseListener M2 = new MyMouseListener();
		JF.addMouseListener(M2);
		C.add(JF);
		J.setLocation(40,40);
		J.setBackground(Color.cyan);
		//******************
		JLabel L = new JLabel("hello");
		JF.add(L);
		//********************
		JTextField T = new JTextField(10);
		JF.add(T);
		T.setText("Burger");
		//******************
		JButton B = new JButton("Push");
		JF.add(B);

	}
	public static void main(String[] args) {
		// TODO Auto-generated method stub
		new GuiTest().run();

	}

}
