data 'WIND' (7128, "BETA Console") {
	$"002E 0008 0062 008C 0008 0000 0100 0000"            /* .....b.å........ */
	$"0000 0C42 4554 4120 436F 6E73 6F6C 65"              /* ...BETA Console */
};

resource 'MENU' (7128, "Apple", preload) {
	7128,
	textMenuProc,
	0x7FFFFFFD,
	enabled,
	apple,
	{	/* array: 2 elements */
		/* [1] */
		"About ...", noIcon, noKey, noMark, plain,
		/* [2] */
		"-", noIcon, noKey, noMark, plain
	}
};

resource 'MENU' (7129, "File", preload) {
	7129, textMenuProc,
	0b0000000000000000000100000000000,	/* enable Quit only, program enables others */
	enabled, "File",
	{
		"New",
			noicon, "N", nomark, plain;
		"Open",
			noicon, "O", nomark, plain;
		"-",
			noicon, nokey, nomark, plain;
		"Close",
			noicon, "W", nomark, plain;
		"Save",
			noicon, "S", nomark, plain;
		"Save As\311",
			noicon, nokey, nomark, plain;
		"Revert",
			noicon, nokey, nomark, plain;
		"-",
			noicon, nokey, nomark, plain;
		"Page Setup\311",
			noicon, nokey, nomark, plain;
		"Print\311",
			noicon, nokey, nomark, plain;
		"-",
			noicon, nokey, nomark, plain;
		"Quit",
			noicon, "Q", nomark, plain
	}
};

resource 'MENU' (7130, "Edit", preload) {
	7130,
	textMenuProc,
	0x1C,
	enabled,
	"Edit",
	{	/* array: 6 elements */
		/* [1] */
		"Undo", noIcon, "Z", noMark, plain,
		/* [2] */
		"-", noIcon, noKey, noMark, plain,
		/* [3] */
		"Cut", noIcon, "X", noMark, plain,
		/* [4] */
		"Copy", noIcon, "C", noMark, plain,
		/* [5] */
		"Paste", noIcon, "V", noMark, plain,
		/* [6] */
		"Clear", noIcon, noKey, noMark, plain
	}
};

resource 'ALRT' (7128, purgeable) {
	{82, 90, 201, 410},
	7128,
	{	/* array: 4 elements */
		/* [1] */
		OK, visible, silent,
		/* [2] */
		OK, visible, silent,
		/* [3] */
		OK, visible, silent,
		/* [4] */
		OK, visible, silent
	}
};

resource 'DITL' (7128, purgeable) {
	{	/* array DITLarray: 3 elements */
		/* [1] */
		{87, 222, 107, 302},
		Button {
			enabled,
			"OK"
		},
		/* [2] */
		{21, 19, 40, 302},
		StaticText {
			disabled,
			"Beta Application with Simple Text Console"
			"e"
		},
		/* [3] */
		{56, 21, 74, 299},
		StaticText {
			disabled,
			"Copyright © 1991-97 Mjølner Informatics"
		}
	}
};


