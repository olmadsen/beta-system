resource 'STR ' (128, "BETALIB", preload, locked) {
	"tromlen:beta:r4.0.2:"
};

resource 'DITL' (-601, purgeable) {
	{	/* array DITLarray: 13 elements */
		/* [1] */
		{154, 256, 172, 336},
		Button {
			enabled,
			"Open"
		},
		/* [2] */
		{1152, 59, 1232, 77},
		Button {
			enabled,
			"Hidden"
		},
		/* [3] */
		{205, 256, 223, 336},
		Button {
			enabled,
			"Cancel"
		},
		/* [4] */
		{55, 232, 75, 347},
		UserItem {
			disabled
		},
		/* [5] */
		{84, 256, 102, 336},
		Button {
			enabled,
			"Eject"
		},
		/* [6] */
		{109, 256, 127, 336},
		Button {
			enabled,
			"Desktop"
		},
		/* [7] */
		{55, 12, 201, 230},
		UserItem {
			enabled
		},
		/* [8] */
		{55, 229, 201, 246},
		UserItem {
			enabled
		},
		/* [9] */
		{140, 252, 141, 340},
		UserItem {
			disabled
		},
		/* [10] */
		{1044, 20, 1145, 116},
		StaticText {
			disabled,
			""
		},
		/* [11] */
		{179, 256, 197, 336},
		Button {
			enabled,
			"Directory"
		},
		/* [12] */
		{7, 48, 25, 233},
		Button {
			enabled,
			"Select Current Directory:"
		},
		/* [13] */
		{205, 12, 225, 245},
		StaticText {
			disabled,
			"Please Select your BETA Folder"
		}
	}
};

resource 'DLOG' (-601, "Get File", purgeable) {
	{0, 0, 232, 348},
	dBoxProc,
	invisible,
	noGoAway,
	0x0,
	-601,
	""
};

