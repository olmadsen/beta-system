import java.io.IOException;
import java.io.*;
import java.util.*;
import javax.swing.JFrame;
import java.awt.*;
import java.awt.event.*;
import javax.swing.*;
import java.awt.event.MouseListener;
import java.awt.event.MouseEvent;
import java.beans.*;
public class GUIservice {
	Service S = new Service(5124);
	Service mouseResponse = new Service(5125); 
	boolean trace = false;
	String[] tokens = null;
	
	String newJframe(String title) {
		JFrame F = null;
		F = new JFrame(title);
		F.setSize(500,600);
		F.setVisible(true);
		return S.handle(F);
	}
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
			//System.out.println("Mouse entered");
			//Component C = e.getComponent();
			//mouseResponse.returnAnswer(S.getHandle(C) + " 2 Mouse entered");
		}

		public void mouseExited(MouseEvent e) {
			//System.out.println("Mouse exited");
		}

		public void mouseClicked(MouseEvent e) {
			//System.out.println("Mouse clicked (# of clicks: " + e.getClickCount() + ")");
			Component C = e.getComponent();
			mouseResponse.returnAnswer( S.getHandle(C) + " 1 " + e.getClickCount() + " Mouse clicked " + C.getClass().toString());
		}
	}

	void run() throws IOException {
		String cmd = null;
		String delims = "[ ]+";
		String h;
		listen:
		while ((cmd = S.getNextCmd()) != null) {
			if	(trace) System.out.println("Java:GUIService: " + '"' + cmd + '"');
			tokens = cmd.split(delims);

			int cmdNo = Integer.parseInt(tokens[0]);
			// System.out.println("cmd: " + cmdNo);
			if (trace) {
				for (int i = 0; i < tokens.length; i++)
				System.out.println("arg:" + i + ':' + '"' + tokens[i] + '"');
			}

			switch (cmdNo) {
			case 0:
				S.close();
				mouseResponse.close();
				break listen;
			case 1:
				h = newJframe(tokens[1]); 
				S.returnAnswer(h); 
				if (trace) System.out.println("Java:Guiservice:answer returned: " + h);
				break;
			case 2:
				JPanel JF = new JPanel();
				JF.setVisible(true);
				JF.setBackground(Color.red);
				MouseListener MS = new MyMouseListener();
				JF.addMouseListener(MS);
				((Container)S.getObj(tokens[1])).add(JF);
				S.returnAnswer(S.handle(JF));
				break;
			case 3:
				((JComponent)S.getObj(tokens[1])).setBackground(Color.cyan);
				S.returnAnswer(tokens[1]);
				break;
			case 4:
				//System.out.println(tokens[1] + "setLocation(" + tokens[2] + ',' + tokens[3] + ')' );
				((JComponent)S.getObj(tokens[1])).setLocation(Integer.parseInt(tokens[2]),Integer.parseInt(tokens[3]));
				S.returnAnswer(tokens[1]);
				break;
			case 5:
				//System.out.println("Add label: " + tokens[2]);
				JLabel L = new JLabel(tokens[2]);
				((Container)S.getObj(tokens[1])).add(L);
				S.returnAnswer(S.handle(L));
				break;
			case 6:
				//System.out.println("Add TextField: " + tokens[2]);
				JTextField T = new JTextField(10);
				// T.setSize(10,100);
				((Container)S.getObj(tokens[1])).add(T);
				S.returnAnswer(S.handle(T));
				break;
			case 7:
				//System.out.println("SetSize: " + tokens[2] + ',' + tokens[3]);
				((JComponent)S.getObj(tokens[1])).setPreferredSize(new Dimension(Integer.parseInt(tokens[2]),Integer.parseInt(tokens[3])));
				S.returnAnswer(tokens[1]);
				break;	
			case 8:
				//System.out.println("SetText: " + tokens[2]);
				((JTextField)S.getObj(tokens[1])).setText(tokens[2]);
				S.returnAnswer(tokens[1]);
				break;
			case 9:
				//System.out.println("GetText:");
				S.returnAnswer(((JTextField) S.getObj(tokens[1])).getText());
				break;
			case 10:
				//System.out.println("Open button:");
				JButton B = new JButton(tokens[2]);
				B.addMouseListener(new MyMouseListener());
				((Container)S.getObj(tokens[1])).add(B);
				S.returnAnswer(S.handle(B));
				break;
			case 999: 
				trace = true;
				break;
			}
		}
	}

	public static void main(String[] args) {
		GUIservice GS = new GUIservice();
		if (GS.trace) System.out.println("Java GUIservice started");
		try {
			GS.run();
		} catch (IOException e) {
			System.err.println("Java GUIservice couldn't get I/O for "
					+ "the connection to: BETA localhost.");
			System.exit(1);
		}
	}

}
