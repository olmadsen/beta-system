	import java.io.*;
	import java.net.*;
public class SocketEx {

	    public static void main(String[] args) throws IOException {

	        Socket echoSocket = null;
	        PrintWriter out = null;
	        BufferedReader in = null;

	        try {
	            echoSocket = new Socket("localhost", 5123);
	            out = new PrintWriter(echoSocket.getOutputStream(), true);
	            in = new BufferedReader(new InputStreamReader(
	                                        echoSocket.getInputStream()));
	        } catch (UnknownHostException e) {
	            System.err.println("Don't know about host: taranis.");
	            System.exit(1);
	        } catch (IOException e) {
	            System.err.println("Couldn't get I/O for "
	                               + "the connection to: taranis.");
	            System.exit(1);
	        }

		BufferedReader stdIn = new BufferedReader(
	                                   new InputStreamReader(System.in));
		String userInput;

		//userInput = in.readLine();
		//System.out.println("echo: " + in.readLine());
		
		while ((userInput = in.readLine()) != null) {
		    System.out.println(userInput);
		    //System.out.println("echo: " + in.readLine());
		}
		System.out.println("Done");	
		out.close();
		in.close();
		stdIn.close();
		echoSocket.close();
	    }
	}