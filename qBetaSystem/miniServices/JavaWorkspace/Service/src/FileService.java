import java.io.*;

public class FileService {
	Service S = new Service(5123);
	File F = null;
	BufferedWriter writer = null;
	boolean trace = false;

	String newFile(String name) throws IOException {
		F = new File(name);
		writer = new BufferedWriter(new FileWriter(F));
		return S.handle(writer);
	}

	void put(String ch) throws IOException {
		BufferedWriter BW = (BufferedWriter) S.getObj(tokens[1]);
		BW.write(ch);
	}

	String[] tokens = null;

	void close() throws IOException {
		BufferedWriter BW = (BufferedWriter) S.getObj(tokens[1]);
		BW.close();
	}

	void run() throws IOException {
		String cmd = null;
		String delims = "[ ]+";
		listen:
		while ((cmd = S.getNextCmd()) != null) {
			String h;
			if (trace) System.out.println("\nFileService: " + cmd);
			tokens = cmd.split(delims);

			int cmdNo = Integer.parseInt(tokens[0]);
			// System.out.println("cmd: " + cmdNo);
			if (trace) {
				for (int i = 0; i < tokens.length; i++)
					System.out.println("arg:" + i + ':' + tokens[i]);
			}
				

			switch (cmdNo) {
			case 0:
				S.close();
				S.returnAnswer("0");
				break listen;
			case 1:
				h = newFile(tokens[1]);
				S.returnAnswer(h); // System.out.println("answer returned");
				break;
			case 2:
				put(tokens[2]);
				S.returnAnswer("0");
				break;
			case 3:
				close();
				S.returnAnswer("0");
				break;
			}
		}
	}

	public static void main(String[] args) {
		FileService FS = new FileService();
		if (FS.trace) System.out.println("Java FileService started");
		try {
			FS.run();
		} catch (IOException e) {
			System.err.println("Java FileService couldn't get I/O for "
					+ "the connection to: BETA localhost.");
			System.exit(1);
		}
	}

}
