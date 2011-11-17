import java.io.*;
import java.net.*;

public class Service {
	Socket echoSocket = null;
	PrintWriter out = null;
	BufferedReader in = null;
	boolean trace = false;

	Service(int port) { 
		if (trace) System.out.println("New service");
		try {
			echoSocket = new Socket("localhost", port);
			out = new PrintWriter(echoSocket.getOutputStream(), true);
			in = new BufferedReader(new InputStreamReader(echoSocket.getInputStream()));
		} catch (UnknownHostException e) {
			System.err.println("Don't know about host: localhost.");
			System.exit(1);
		} catch (IOException e) {
			System.err.println("Couldn't get I/O for "
					+ "the connection to: localhost.");
			System.exit(1);
		}
		if (trace) System.out.println("New Java service started");
	}

	String getNextCmd() throws IOException { 
		String cmd = null;
		cmd = in.readLine();
		return cmd;
	}

	String handle(Object S) {
		String h = new String("");
		top = top + 1; // check overflow
		handles[top] = S;
		h = new Integer(top).toString();
		return h;
	}

	void returnAnswer(String ans) {
		if (trace) System.out.println("Java:returnAnswer:"+ans);
		out.println(ans);
	}

	Object getObj(String handle) {
		//System.out.println("Handle: " + getComp(handle).getClass().toString());
		return handles[Integer.parseInt(handle)];
	}
    Object getComp(String handle) {return handles[Integer.parseInt(handle)];}
	Object[] handles = new Object[100];
	int top;
	
	int getHandle(Object C) {
		int h=0;
		for (int i = 0; i < handles.length; i++) {
			if (handles[i] == C) {
				h = i;
				break;
			}
		}
		return h;
	}

	void close() throws IOException {
		if (trace) System.out.println("Done");
		echoSocket.close();
	}
}
