resource 'STR ' (128, "BETALIB", locked, preload) {
	"<nothing>"
};

resource 'DITL' (-601, purgeable) {
	{	/* array DITLarray: 11 elements */
		/* [1] */
		{157, 253, 177, 333},
		Button {
			enabled,
			"Open"
		},
		/* [2] */
		{126, 253, 146, 333},
		Button {
			enabled,
			"Cancel"
		},
		/* [3] */
		{0, 0, 0, 0},
		HelpItem {
			disabled,
			HMScanhdlg {
				-6043
			}
		},
		/* [4] */
		{30, 236, 46, 338},
		UserItem {
			enabled
		},
		/* [5] */
		{54, 253, 74, 333},
		Button {
			enabled,
			"Eject"
		},
		/* [6] */
		{82, 253, 102, 333},
		Button {
			enabled,
			"Desktop"
		},
		/* [7] */
		{51, 13, 181, 231},
		UserItem {
			enabled
		},
		/* [8] */
		{28, 13, 47, 231},
		UserItem {
			enabled
		},
		/* [9] */
		{113, 252, 114, 334},
		Picture {
			disabled,
			11
		},
		/* [10] */
		{189, 24, 209, 211},
		Button {
			enabled,
			""
		},
		/* [11] */
		{6, 15, 23, 300},
		StaticText {
			disabled,
			"Where is the BETA folder?"
		}
	}
};

resource 'DLOG' (-601, purgeable) {
	{0, 0, 215, 344},
	dBoxProc,
	invisible,
	noGoAway,
	0x0,
	-601,
	""
};

