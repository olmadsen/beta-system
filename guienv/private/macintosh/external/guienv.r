resource 'MENU' (128) {
	128,
	textMenuProc,
	0x7FFFFFFD,
	enabled,
	apple,
	{	/* array: 2 elements */
		/* [1] */
		"About", noIcon, noKey, noMark, plain,
		/* [2] */
		"-", noIcon, noKey, noMark, plain
	}
};

data 'ppat' (128) {
	$"0001 0000 001C 0000 004E 0000 0000 FFFF"            /* .........N....яя */
	$"0000 0000 0000 0000 0000 0000 0000 0000"            /* ................ */
	$"8001 0000 0000 0008 0008 0000 0000 0000"            /* Ђ............... */
	$"0000 0048 0000 0048 0000 0000 0001 0001"            /* ...H...H........ */
	$"0001 0000 0000 0000 0056 0000 0000 0000"            /* .........V...... */
	$"0000 0000 0000 0000 0000 0000 0000 0000"            /* ................ */
	$"DDDD DDDD DDDD"                                     /* ЭЭЭЭЭЭ */
};

resource 'MENU' (129) {
	129,
	textMenuProc,
	allEnabled,
	enabled,
	"nothing",
	{	/* array: 1 elements */
		/* [1] */
		"nothing", noIcon, noKey, noMark, plain
	}
};


