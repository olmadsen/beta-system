USETEXTLINKS=1;

foldersTree = gFld("<B>Contents</B>", "");

       aux1 = insDoc(foldersTree, gLnk(0, "Intro", "intro.html"));

       aux1 = insFld(foldersTree, gFld("Statistics", ""));
	      insDoc(aux1, gLnk(2, "Student Statistics", "www.daimi.au.dk/~beta/Statistics/student/"));
	      insDoc(aux1, gLnk(0, "Error Reports Status", "../mjolner/internal/errorReportsStatus.html"));

       aux1 = insFld(foldersTree, gFld("Status", ""));
	      insDoc(aux1, gLnk(2, "MBS Status Matrix", "www.mjolner.dk/Quality/mbs_status.html"));

       aux1 = insFld(foldersTree, gFld("Plan", ""));
	      insDoc(aux1, gLnk(2, "Mj&oslash;lner r4.2 Plan", "www.mjolner.dk/Quality/r4.2-plan.html"));
	      insDoc(aux1, gLnk(2, "Mj&oslash;lner r5.0 Plan", "www.mjolner.dk/Quality/r5.0-plan.html"));

       aux1 = insFld(foldersTree, gFld("Quality", ""));
	      insDoc(aux1, gLnk(2, "Mj&oslash;lner Quality Pages", "www.mjolner.dk/Quality/"));

       aux1 = insFld(foldersTree, gFld("TODO", ""));
              insDoc(aux1, gLnk(0, "Mjolner", "../mjolner/internal/TODO"));
              insDoc(aux1, gLnk(0, "CASE Tool", "../freja/internal/TODO"));
              insDoc(aux1, gLnk(0, "Debugger", "../valhalla/internal/TODO"));
              insDoc(aux1, gLnk(0, "Editor", "../sif/internal/TODO"));
              insDoc(aux1, gLnk(0, "Sourcebrowser", "../ymer/internal/TODO"));
              insDoc(aux1, gLnk(0, "Interfacebuilder", "../frigg/internal/TODO"));
              insDoc(aux1, gLnk(0, "Guienv", "../lidskjalv-ref/internal/TODO"));
              insDoc(aux1, gLnk(0, "Bifrost", "../bifrost-ref/internal/TODO"));
              aux2 = insFld(aux1, gFld("COM", "../comlib/internal/todo.html"));
		   insDoc(aux2, gLnk(0, "Bidl", "../bidl/internal/todo.html"));
              insDoc(aux1, gLnk(0, "MPS", "../yggdrasil/internal/TODO"));
              insDoc(aux1, gLnk(0, "Documentation, general", "../admin/todo.html"));
              aux2 = insFld(aux1, gFld("Manual Errors, reported", "http://www.mjolner.com/ErrorReports/Manuals/"));
		   insDoc(aux2, gLnk(0, "r4.1", "http://www.mjolner.com/ErrorReports/Manuals/r4.1"));
		   insDoc(aux2, gLnk(0, "r5.0", "http://www.mjolner.com/ErrorReports/Manuals/r5.0"));

       aux1 = insFld(foldersTree, gFld("CHANGES", ""));
              insDoc(aux1, gLnk(0, "CASE Tool", "../freja/internal/CHANGES"));
              insDoc(aux1, gLnk(0, "Debugger", "../frigg/internal/CHANGES"));
              insDoc(aux1, gLnk(0, "Editor", "../sif/internal/CHANGES"));
              insDoc(aux1, gLnk(0, "Sourcebrowser", "../ymer/internal/CHANGES"));
              insDoc(aux1, gLnk(0, "Interfacebuilder", "../frigg/internal/CHANGES"));
              insDoc(aux1, gLnk(0, "Guienv", "../lidskjalv-ref/internal/CHANGES"));
              insDoc(aux1, gLnk(0, "Bifrost", "../bifrost-ref/internal/CHANGES"));
              insDoc(aux1, gLnk(0, "MPS", "../yggdrasil/internal/CHANGES"));

       aux1 = insFld(foldersTree, gFld("Internal Documentation", ""));
	      aux2 = insFld(aux1, gFld("Mjolner", "../mjolner/internal/"));
			    insFld(aux2, gLnk(0, "Error Reports Overview", "../mjolner/internal/errorReportsStatus.html"));
			    insFld(aux2, gLnk(0, "Executive summary", "../mjolner/internal/mjolnerbugs.html"));
			    insFld(aux2, gLnk(0, "r5.0 test status", "../mjolner/internal/r5.0-test-status.txt"));

		     aux3 = insFld(aux2, gFld("Eval", "../mjolner/internal/eval"));
			    insFld(aux3, gLnk(0, "Notes", "../mjolner/internal/eval/notes.txt"));
			    insFld(aux3, gLnk(0, "990802", "../mjolner/internal/eval/990802.txt"));
			    insFld(aux3, gLnk(0, "990803", "../mjolner/internal/eval/990803.txt"));
			    insFld(aux3, gLnk(0, "990805", "../mjolner/internal/eval/990805.txt"));
			    insFld(aux3, gLnk(0, "990806", "../mjolner/internal/eval/990806.txt"));
			    insFld(aux3, gLnk(0, "990808", "../mjolner/internal/eval/990808.txt"));

		     aux3 = insFld(aux2, gFld("Architecture", "../mjolner/internal/architecture"));
			    insFld(aux3, gLnk(0, "990319", "../mjolner/internal/architecture/990319/index.html"));

		     aux3 = insFld(aux2, gFld("Plans", "../mjolner/internal/plans"));
			    insFld(aux3, gLnk(0, "uge21-34", "../mjolner/internal/plans/uge21-34.html"));

		     aux3 = insFld(aux2, gFld("Minutes", "../mjolner/internal/minutes"));
			    insFld(aux3, gLnk(0, "990319", "../mjolner/internal/minutes/990319.txt"));
			    insFld(aux3, gLnk(0, "990409", "../mjolner/internal/minutes/990409.txt"));
			    insFld(aux3, gLnk(0, "990416", "../mjolner/internal/minutes/990416.txt"));
			    insFld(aux3, gLnk(0, "990430", "../mjolner/internal/minutes/990430.txt"));
			    insFld(aux3, gLnk(0, "990507", "../mjolner/internal/minutes/990507.txt"));
			    insFld(aux3, gLnk(0, "990521", "../mjolner/internal/minutes/990521.txt"));
	      aux2 = insFld(aux1, gFld("Bifrost", "../bifrost-ref/internal/"));
		     insDoc(aux2, gLnk(0, "README", "../bifrost-ref/internal/README"));
		     insDoc(aux2, gLnk(0, "TODO", "../bifrost-ref/internal/TODO"));
		     insDoc(aux2, gLnk(0, "CHANGES", "../bifrost-ref/internal/CHANGES"));
	      aux2 = insFld(aux1, gFld("Betarun", ""));
		     insDoc(aux2, gLnk(2, "Overview", "www.mjolner.com/Quality/betarun.html"));
		     insDoc(aux2, gLnk(0, "BETART (general)", "../betarun/BETART.html"));
		     insDoc(aux2, gLnk(0, "BETART (debug)", "../betarun/internal/BETART-debug.html"));
		     insDoc(aux2, gLnk(0, "Intel", "../betarun/internal/Rundoc.txt"));
		     insDoc(aux2, gLnk(0, "HPPA", "../betarun/internal/SnakeDoc.txt"));
		     insDoc(aux2, gLnk(0, "SPARC Stack", "../betarun/internal/SparcStack.html"));
		     insDoc(aux2, gLnk(0, "GC Intro", "../betarun/internal/chap5.pdf"));
		     insDoc(aux2, gLnk(0, "Trap Callbacks", "../betarun/internal/trapcallbacks.html"));
		     insDoc(aux2, gLnk(0, "Index of", "../betarun/internal/"));
              insDoc(aux1, gLnk(2, "Compiler", "www.daimi.au.dk/~olm/DOC/"));

       aux1 = insFld(foldersTree, gFld("Testing", "http://www.mjolner.dk/Quality/betatest.html"));
	      aux2 = insFld(aux1, gFld("Tools", ""));
		   insDoc(aux2, gLnk(2, "mjolner", "www.mjolner.dk/Quality/betatest.html#mjolner"));
		   insDoc(aux2, gLnk(2, "compiler", "www.mjolner.dk/Quality/betatest.html#compiler"));
		   insDoc(aux2, gLnk(2, "valhalla", "www.mjolner.dk/Quality/betatest.html#valhalla"));
		   insDoc(aux2, gLnk(2, "freja", "www.mjolner.dk/Quality/betatest.html#freja"));
		   insDoc(aux2, gLnk(2, "frigg", "www.mjolner.dk/Quality/betatest.html#frigg"));
		   insDoc(aux2, gLnk(2, "psbrowser", "www.mjolner.dk/Quality/betatest.html#psbrowser"));
		   insDoc(aux2, gLnk(2, "meta", "www.mjolner.dk/Quality/betatest.html#meta"));
		   insDoc(aux2, gLnk(2, "pp", "www.mjolner.dk/Quality/betatest.html#pp"));
		   insDoc(aux2, gLnk(2, "utils", "www.mjolner.dk/Quality/betatest.html#utils"));
		   insDoc(aux2, gLnk(2, "tool check list", "www.mjolner.dk/Quality/toolchecklist.html"));
	      aux2 = insFld(aux1, gFld("demo", "http://www.mjolner.dk/Quality/betatest.html#demo"));
		   aux3 = insFld(aux2, gFld("demo check list", "http://www.mjolner.dk/Quality/demochecklist.html"));
		   	insDoc(aux3, gLnk(2, "tutorial demos", "www.mjolner.dk/Quality/tutorialdemo.checklist.html"));

initializeDocument();

