resource 'SIZE' (-1, purgeable) {
	reserved,
	acceptSuspendResumeEvents,
	reserved,
	canBackground,
	multiFinderAware,
	backgroundAndForeground,
	dontGetFrontClicks,
	ignoreChildDiedEvents,
	is32BitCompatible,
	isHighLevelEventAware,
	localAndRemoteHLEvents,
	notStationeryAware,
	dontUseTextEditServices,
	reserved,
	reserved,
	reserved,
	12000000,
	2179072
};

resource 'ALRT' (7129) {
	{49, 60, 306, 452},
	7129,
	{	/* array: 4 elements */
		/* [1] */
		OK, visible, sound1,
		/* [2] */
		OK, visible, sound1,
		/* [3] */
		OK, visible, sound1,
		/* [4] */
		OK, visible, silent
	}
	/****** Extra bytes follow... ******/
	/* $"300A"                                               /* 0. */
};

resource 'ALRT' (7130) {
	{49, 60, 307, 453},
	7130,
	{	/* array: 4 elements */
		/* [1] */
		OK, visible, sound1,
		/* [2] */
		OK, visible, sound1,
		/* [3] */
		OK, visible, sound1,
		/* [4] */
		OK, visible, silent
	}
	/****** Extra bytes follow... ******/
	/* $"300A"                                               /* 0. */
};

resource 'ALRT' (7128, purgeable) {
	{73, 43, 198, 442},
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
	/****** Extra bytes follow... ******/
	/* $"280A"                                               /* (. */
};

resource 'DITL' (7130) {
	{	/* array DITLarray: 3 elements */
		/* [1] */
		{219, 326, 239, 386},
		Button {
			enabled,
			"OK"
		},
		/* [2] */
		{10, 10, 246, 314},
		StaticText {
			disabled,
			"^0^1^2^3"
		},
		/* [3] */
		{10, 322, 74, 386},
		Picture {
			disabled,
			7130
		}
	}
};

resource 'DITL' (7128, purgeable) {
	{	/* array DITLarray: 3 elements */
		/* [1] */
		{94, 302, 114, 382},
		Button {
			enabled,
			"OK"
		},
		/* [2] */
		{14, 92, 84, 376},
		StaticText {
			disabled,
			"Beta Application with Simple Text Consol"
			"e for PowerMac\n\nCopyright © 1995 Mjølner"
			" Informatics"
		},
		/* [3] */
		{14, 15, 78, 79},
		Picture {
			disabled,
			7130
		}
	}
};

resource 'DITL' (7129) {
	{	/* array DITLarray: 3 elements */
		/* [1] */
		{219, 320, 239, 380},
		Button {
			enabled,
			"OK"
		},
		/* [2] */
		{10, 10, 238, 303},
		StaticText {
			disabled,
			"^0^1^2^3"
		},
		/* [3] */
		{10, 316, 74, 380},
		Picture {
			disabled,
			7130
		}
	}
};

resource 'MENU' (7128, preload) {
	7128,
	textMenuProc,
	allEnabled,
	enabled,
	apple,
	{	/* array: 2 elements */
		/* [1] */
		"About Console...", noIcon, noKey, noMark, plain,
		/* [2] */
		"-", noIcon, noKey, noMark, plain
	}
};

resource 'MENU' (7129, preload) {
	7129,
	textMenuProc,
	0x208,
	enabled,
	"File",
	{	/* array: 10 elements */
		/* [1] */
		"New", noIcon, "N", noMark, plain,
		/* [2] */
		"Open...", noIcon, "O", noMark, plain,
		/* [3] */
		"-", noIcon, noKey, noMark, plain,
		/* [4] */
		"Close", noIcon, "W", noMark, plain,
		/* [5] */
		"Save", noIcon, "S", noMark, plain,
		/* [6] */
		"-", noIcon, noKey, noMark, plain,
		/* [7] */
		"Page Setup...", noIcon, noKey, noMark, plain,
		/* [8] */
		"Print...", noIcon, noKey, noMark, plain,
		/* [9] */
		"-", noIcon, noKey, noMark, plain,
		/* [10] */
		"Quit", noIcon, "Q", noMark, plain
	}
};

resource 'MENU' (7130, preload) {
	7130,
	textMenuProc,
	0x1C,
	enabled,
	"Edit",
	{	/* array: 8 elements */
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
		"Clear", noIcon, noKey, noMark, plain,
		/* [7] */
		"-", noIcon, noKey, noMark, plain,
		/* [8] */
		"Select All", noIcon, "A", noMark, plain
	}
};

resource 'MENU' (7131, preload) {
	7131,
	textMenuProc,
	allEnabled,
	enabled,
	"Font",
	{	/* array: 0 elements */
	}
};

resource 'MENU' (7132, preload) {
	7132,
	textMenuProc,
	allEnabled,
	enabled,
	"Size",
	{	/* array: 6 elements */
		/* [1] */
		"9 Point", noIcon, noKey, noMark, plain,
		/* [2] */
		"10 Point", noIcon, noKey, noMark, plain,
		/* [3] */
		"12 Point", noIcon, noKey, noMark, plain,
		/* [4] */
		"14 Point", noIcon, noKey, noMark, plain,
		/* [5] */
		"18 Point", noIcon, noKey, noMark, plain,
		/* [6] */
		"24 Point", noIcon, noKey, noMark, plain
	}
};

resource 'MENU' (7133, preload) {
	7133,
	textMenuProc,
	allEnabled,
	enabled,
	"Style",
	{	/* array: 7 elements */
		/* [1] */
		"Plain", noIcon, "P", noMark, plain,
		/* [2] */
		"-", noIcon, noKey, noMark, plain,
		/* [3] */
		"Bold", noIcon, "B", noMark, 1,
		/* [4] */
		"Italic", noIcon, "I", noMark, 2,
		/* [5] */
		"Underline", noIcon, "U", noMark, 4,
		/* [6] */
		"Outline", noIcon, noKey, noMark, 8,
		/* [7] */
		"Shadow", noIcon, noKey, noMark, 16
	}
};

resource 'WIND' (7128, "BETA Console", purgeable, preload) {
	{64, 60, 314, 460},
	zoomDocProc,
	invisible,
	goAway,
	0x0,
	"BETA Console"
	/****** Extra bytes follow... ******/
	/* $"BA28 0A"                                            /* ∫(. */
};

resource 'ICN#' (-16455) {
	{	/* array: 2 elements */
		/* [1] */
		$"FFFF FFFF 8000 8001 8003 4001 800C 6001"
		$"8030 4001 80C4 4001 83B8 8001 8732 8001"
		$"8956 8001 8174 0001 B505 0001 B475 8001"
		$"B43B C001 B89A 4001 BDBA 2001 BFB8 A001"
		$"BFB6 D001 BFB6 4801 BFA8 0801 BF8C D401"
		$"BFDF 6FC1 BE7F FE21 BC70 7E39 99C0 1C35"
		$"B380 0CA5 9700 0B23 9C00 0FE5 8000 0FF9"
		$"8000 0FC1 8000 0301 8000 0001 FFFF FFFF",
		/* [2] */
		$"FFFF FFFF FFFF FFFF FFFF FFFF FFFF FFFF"
		$"FFFF FFFF FFFF FFFF FFFF FFFF FFFF FFFF"
		$"FFFF FFFF FFFF FFFF FFFF FFFF FFFF FFFF"
		$"FFFF FFFF FFFF FFFF FFFF FFFF FFFF FFFF"
		$"FFFF FFFF FFFF FFFF FFFF FFFF FFFF FFFF"
		$"FFFF FFFF FFFF FFFF FFFF FFFF FFFF FFFF"
		$"FFFF FFFF FFFF FFFF FFFF FFFF FFFF FFFF"
		$"FFFF FFFF FFFF FFFF FFFF FFFF FFFF FFFF"
	}
};

resource 'ICN#' (128, purgeable) {
	{	/* array: 2 elements */
		/* [1] */
		$"0001 0000 0002 8000 0004 4000 0008 2000"
		$"0010 101C 0021 0822 0042 0441 0084 42A1"
		$"0108 8151 0211 12AA 0422 2554 0800 4AA8"
		$"1088 1550 2111 2AA8 4202 5544 8444 AA82"
		$"4088 9501 2110 CA02 1020 E404 0840 F808"
		$"0400 0010 0200 0020 0100 0040 0080 0080"
		$"0040 0100 0020 0200 0010 0400 0008 0800"
		$"0004 1000 0002 2000 0001 4000 0000 80",
		/* [2] */
		$"0001 0000 0003 8000 0007 C000 000F E000"
		$"001F F01C 003F F83E 007F FC7F 00FF FEFF"
		$"01FF FFFF 03FF FFFE 07FF FFFC 0FFF FFF8"
		$"1FFF FFF0 3FFF FFF8 7FFF FFFC FFFF FFFE"
		$"7FFF FFFF 3FFF FFFE 1FFF FFFC 0FFF FFF8"
		$"07FF FFF0 03FF FFE0 01FF FFC0 00FF FF80"
		$"007F FF00 003F FE00 001F FC00 000F F800"
		$"0007 F000 0003 E000 0001 C000 0000 80"
	}
};

resource 'icl8' (-16455) {
	$"FFFF FFFF FFFF FFFF FFFF FFFF FFFF FFFF"
	$"FFFF FFFF FFFF FFFF FFFF FFFF FFFF FFFF"
	$"FF00 0000 0000 0000 0000 0000 0000 00F5"
	$"FDF6 0000 0000 0000 0000 0000 0000 00FF"
	$"FF00 0000 0000 0000 0000 0000 002B FFFF"
	$"2BFE 2B00 0000 0000 0000 0000 0000 00FF"
	$"FF00 0000 0000 0000 0000 002B FFFE 2B00"
	$"00FC F900 0000 0000 0000 0000 0000 00FF"
	$"FF00 0000 0000 0000 0056 FFFD F500 0056"
	$"00FF F500 0000 0000 0000 0000 0000 00FF"
	$"FF00 0000 0000 00F5 FFFF 0000 0056 0000"
	$"00FF 0000 0000 0000 0000 0000 0000 00FF"
	$"FF00 0000 0000 FBFF 8100 ACFF 8100 00F6"
	$"FA56 0000 0000 0000 0000 0000 0000 00FF"
	$"FF00 0000 F9FF FFFF 00F9 81FF ACF6 FE00"
	$"FF00 0000 0000 0000 0000 0000 0000 00FF"
	$"FF00 00F5 FD2B 00FF 0081 00AC 00FC FF00"
	$"FC00 0000 0000 0000 0000 0000 0000 00FF"
	$"FF00 F7F8 00F5 00FF F5AC FFAC 00FF FA56"
	$"5600 0000 0000 0000 0000 0000 0000 00FF"
	$"FF00 81FF 00FF 00FD F7FA 56FC F581 00FF"
	$"F700 0000 0000 0000 0000 0000 0000 00FF"
	$"FF00 FBFF 00FE 0000 0056 81FC F7FF 00FF"
	$"FD00 0000 0000 0000 0000 0000 0000 00FF"
	$"FF00 FCFF 00FB 0000 2B00 FFFF FEF7 F8FF"
	$"FFF7 0000 0000 0000 0000 0000 0000 00FF"
	$"FF00 FEFF FE00 00F7 AC00 F9FC FF00 FFF5"
	$"00FF 0000 0000 0000 0000 0000 0000 00FF"
	$"FF00 FFFF FFFF F656 FF00 FFFF FC00 FD2B"
	$"00F9 FC00 0000 0000 0000 0000 0000 00FF"
	$"FF00 FFFF FFFF FFFF FF00 FBFE FAF9 F52B"
	$"FF00 FFF5 0000 0000 0000 0000 0000 00FF"
	$"FF00 FFFF FFFF FFFF FF00 FFFF 00FF FB00"
	$"FCFC 00FF 0000 0000 0000 0000 0000 00FF"
	$"FF00 FFFF FFFF FFFF FF00 FFFF F6FB FDF6"
	$"00FE 00F9 8100 0000 0000 0000 0000 00FF"
	$"FF00 FFFF FFFF FFFF FF00 FF56 FCAC 00F5"
	$"5600 0000 FEF5 0000 0000 0000 0000 00FF"
	$"FF00 FFFF FFFF FFFF FFF8 2BF6 FFFF 5600"
	$"ACAC 0081 F9FD 0000 0000 0000 0000 00FF"
	$"FF00 FFFF FFFF FFFF FFFE 00FD FFFF FFF9"
	$"00FF FFF5 FFFD FEFF FFFF F800 0000 00FF"
	$"FF00 FFFF FFFF FFF9 00FF 81FF FFFB FBFF"
	$"FFFF FFFF FEFF FFF5 0000 FF00 0000 00FF"
	$"FF00 FDFF FFFF 0000 00FF FFFD 0000 0000"
	$"F6FE FFFF FFFF FF00 0000 81FF FB00 00FF"
	$"FF00 FCFF FF00 00FB FFFF 8100 0000 0000"
	$"0000 F8FF FFFF F900 0000 FBFC FAFF 00FF"
	$"FF00 81FF 0000 FFFF FFF8 0000 0000 0000"
	$"0000 002B FFFE 00F7 FA00 FFF5 00AC F6FF"
	$"FF00 F5FF F9FF FFFF F500 0000 0000 0000"
	$"0000 00F6 FF00 FBFF FAF7 FF00 00F9 F9FF"
	$"FF00 00F9 FFFF 5600 0000 0000 0000 0000"
	$"0000 00F7 FFFF FFFF FFFF FF56 F7FF 00FF"
	$"FF00 0000 0000 0000 0000 0000 0000 0000"
	$"0000 00F6 FFFF FFFF FFFF F9FF FFF7 00FF"
	$"FF00 0000 0000 0000 0000 0000 0000 0000"
	$"0000 0000 FEFF FFFF FFFD 0000 0000 00FF"
	$"FF00 0000 0000 0000 0000 0000 0000 0000"
	$"0000 0000 00F9 ACFD FA00 0000 0000 00FF"
	$"FF00 0000 0000 0000 0000 0000 0000 0000"
	$"0000 0000 0000 0000 0000 0000 0000 00FF"
	$"FFFF FFFF FFFF FFFF FFFF FFFF FFFF FFFF"
	$"FFFF FFFF FFFF FFFF FFFF FFFF FFFF FFFF"
};

data '8BIM' (1001) {
	$"0003 0000 0048 0048 0000 0000 030D 021A"            /* .....H.H.....¬.. */
	$"FFE1 FFE4 032B 0237 0347 057B 03E0 0002"            /* ˇ·ˇ‰.+.7.G.{.‡.. */
	$"0000 0048 0048 0000 0000 030D 021A 0001"            /* ...H.H.....¬.... */
	$"0000 0064 0000 0001 0003 0303 00FF 0001"            /* ...d.........ˇ.. */
	$"270F 0001 0001 0000 0000 0000 0000 0000"            /* '............... */
	$"0000 6808 0019 0190 0000 0000 0000 0000"            /* ..h....ê........ */
	$"0000 0000 0000 0001 0000 0000 0000 0000"            /* ................ */
	$"0000 0000 0000 0000"                                /* ........ */
};

data '8BIM' (1005) {
	$"0048 0000 0001 0000 0048 0000 0001 0000"            /* .H.......H...... */
};

data '8BIM' (1010) {
	$"0000 FFFF FFFF FFFF 0000"                           /* ..ˇˇˇˇˇˇ.. */
};

data '8BIM' (1011) {
	$"0000 0000 0000 00"                                  /* ....... */
};

data '8BIM' (1012) {
	$"0035 0000 0001 002D 0000 0000 0000 0000"            /* .5.....-........ */
	$"0000"                                               /* .. */
};

data '8BIM' (1015) {
	$"0000 FFFF FFFF FFFF FFFF FFFF FFFF FFFF"            /* ..ˇˇˇˇˇˇˇˇˇˇˇˇˇˇ */
	$"FFFF FFFF FFFF FFFF 03E8 0000"                      /* ˇˇˇˇˇˇˇˇ.Ë.. */
};

resource 'PICT' (7130, "MIA logo no shadow") {
	1506,
	{0, 0, 64, 64},
	$"0011 02FF 0C00 FFFE 0000 0048 0000 0048"
	$"0000 0000 0000 0040 0040 0000 0000 0001"
	$"000A 0000 0000 0040 0040 0098 8020 0000"
	$"0000 0040 0040 0000 0000 0000 0000 0048"
	$"0000 0048 0000 0000 0004 0001 0004 0000"
	$"0000 0000 0000 0000 0000 004A 6F30 0000"
	$"000F 0000 FFFF FFFF FFFF 0001 EEEE EEEE"
	$"EEEE 0002 DDDD DDDD DDDD 0003 CCCC CCCC"
	$"CCCC 0004 BBBB BBBB BBBB 0005 AAAA AAAA"
	$"AAAA 0006 9999 9999 9999 0007 8888 8888"
	$"8888 0008 7777 7777 7777 0009 6666 6666"
	$"6666 000A 5555 5555 5555 000B 4444 4444"
	$"4444 000C 3333 3333 3333 000D 2222 2222"
	$"2222 000E 1111 1111 1111 000F 0000 0000"
	$"0000 0000 0000 0040 0040 0000 0000 0040"
	$"0040 0000 06F1 0000 24F2 0008 F200 0229"
	$"FFD3 F300 0AF3 0004 1BFF F8DF 30F4 000B"
	$"F400 052A EFC6 000D F0F4 000C F500 0629"
	$"FFE4 0000 0AF1 F400 0DF6 0002 29FF A4FE"
	$"0001 0FF0 F400 0EF7 0008 3BFF C100 0021"
	$"003F D0F4 000F F800 026D FF92 FE00 0367"
	$"007F 50F4 0010 F900 055F FFD2 0001 10FE"
	$"0001 BF20 F400 10FA 0006 3CFF D300 000B"
	$"90FE 0000 EDF3 0011 FB00 0B07 FFF9 0001"
	$"1000 1006 6003 F6F3 0012 FC00 0C05 DFFF"
	$"4000 BFDD 5000 0360 0CE0 F300 13FD 0008"
	$"03DF FFF6 001E FFFF F6FE 0001 1F80 F300"
	$"13FD 000D BFFF FFF0 008F BFFF E30B C100"
	$"4F10 F300 13FE 000D 4EFF FCEF F000 F205"
	$"FF50 1FFC 00AC F200 1410 0000 03FF FA20"
	$"6FF2 02D0 04F5 006F FD00 F2F2 0013 FE00"
	$"0D11 0000 4FF4 03B0 26F0 00CF F705 E0F2"
	$"0014 0200 0010 FE00 0A1F F606 DD8E C000"
	$"FFF2 0BB0 F200 1410 0008 F400 3700 0FF9"
	$"03FF FFC0 07EF D01E B0F2 0014 1000 0AFE"
	$"008F 000C FA01 FFFF A00B 0450 4FA0 F200"
	$"1410 000D FE10 9F00 03FA 00F3 2EC0 2BC6"
	$"30DF C0F2 0014 1000 0EFF 108F 1000 2300"
	$"C00A C03F FE02 FFE1 F200 1405 001E FF30"
	$"9F20 FE00 07A7 FCF0 BAF7 06FF F7F2 0015"
	$"0500 1FFF 505F 30FE 0008 6FFF F470 C00B"
	$"FFFF 20F3 0015 1100 3FFF B02F 3000 0400"
	$"5FFF FFDE 900F FFDF B0F3 0015 1100 3FFF"
	$"F407 0000 4F00 2F6D FFFF 606F F40F F6F3"
	$"0016 0300 7FFF FDFE 000B 8F20 3813 FBFF"
	$"20CF 8002 FE10 F400 1612 006F FFFF E100"
	$"00DF 501D DEF6 4E01 EC00 008F 70F4 0016"
	$"1200 AFFF FFFE 7000 FF90 1FFF FFC5 05F5"
	$"0200 0DF3 F400 1501 009F FDFF 0C83 EFB0"
	$"0FFF FFE1 0DE0 0F20 02FB F400 1401 00CF"
	$"FBFF 0BD0 0FDD FFC0 2F60 0CE0 006F 50F5"
	$"0014 0100 DFFB FF0B D00F 12EF 607F 2003"
	$"FE00 0AE1 F500 1401 00EF FBFF 0BE0 0FDE"
	$"EF00 DF70 006F B001 F9F5 0014 0000 FAFF"
	$"0CE1 0CFF FB01 FFF5 000B FA00 4F40 F600"
	$"1400 00FA FF0C F10C FFF5 0BF8 FF10 00DF"
	$"400C E0F6 0014 0000 FAFF 0CF2 09FF F11F"
	$"A02D 7000 0C40 00FB F600 1500 00FA FF0D"
	$"F308 FFD0 7FC0 0010 0000 1000 6F40 F700"
	$"1500 00FA FF08 F604 FF40 FFF1 0005 70FE"
	$"0001 0CF1 F700 1500 00FA FF0D FB00 FE17"
	$"FFFD 0002 FE20 0002 00FC F700 1500 00F9"
	$"FF0D 0075 0EFF FF80 002F F900 0DE6 3F80"
	$"F800 1800 00F9 FF10 4000 9FFF FFFA 0001"
	$"FFF1 07FF E4F8 0015 76FB 001A 0100 EFFA"
	$"FF02 A002 EFFE FF0B A101 4FFF 50BF FFAF"
	$"CDFF FFFB FC00 1801 00DF FAFF 01F0 0BFB"
	$"FF03 BFFF FA2F FEFF 03FB CCFF D0FD 0018"
	$"0100 CFFD FF04 FD51 0CFB 4FF8 FF07 DFFF"
	$"FFF5 0000 0AF6 FD00 1A01 00AF FDFF 02A0"
	$"0002 FEFF 03F6 1002 8EFA FF00 F1FE 0000"
	$"FFFD 001E 0100 7FFE FF06 E500 000A FFFF"
	$"F9FD 0001 28EF FCFF 00D0 FE00 04AF 7630"
	$"0000 1D0B 004F FFFF FE10 0001 DFFF FF30"
	$"FC00 000A FCFF 00B0 FE00 04BF FFFC 1000"
	$"1A0A 002F FFFF C100 018F FFFF C2FA 0000"
	$"3DFD FFFD 0004 9FEB DFE1 001B 0A00 2EFF"
	$"FC00 003F FFFF FC10 F900 03CF FFFF F8FD"
	$"0004 DF10 04FA 001B 0900 0EFF A000 08EF"
	$"FFFF 90F8 000C 0AFF FFF0 001C 0001 FF00"
	$"009F 0019 0800 0BFD 0000 AFFF FFF7 F600"
	$"0BCF FF10 00BE 1008 FA00 002F 8019 0400"
	$"07FC 005E FEFF 0030 F600 0BEF F400 5DFF"
	$"100E F400 000F A019 0300 00FF ADFE FF00"
	$"D2F6 000C 01FF 715D FFFF 60CF F000 001F"
	$"A018 0200 007F FEFF 00D5 F500 0203 FFCF"
	$"FEFF 06EC FFC0 0000 9F80 1305 0000 07FF"
	$"FFD5 F400 0002 FAFF 04FC 6438 FF30 0CFE"
	$"0001 1893 F200 F7FF 01F7 000B ED00 FBFF"
	$"05FD 4CFF FE50 000D ED00 00AF FCFF 05F5"
	$"0013 2100 000A ED00 003F FCFF 00E0 FC00"
	$"0AED 0000 04FD FF00 FEFB 000A EC00 0419"
	$"EFFF FFA0 FB00 08EB 0002 0145 21FA 0002"
	$"E100 02E1 0000 00FF"
};

data 'cfrg' (0) {
	$"0000 0000 0000 0000 0000 0001 0000 0000"            /* ................ */
	$"0000 0000 0000 0000 0000 0000 0000 0001"            /* ................ */
	$"7077 7063 0000 0000 0000 0000 0000 0000"            /* pwpc............ */
	$"0000 0000 0000 0101 0000 0000 0000 0000"            /* ................ */
	$"0000 0000 0000 0000 003C 1141 7070 6C65"            /* .........<.Apple */
	$"4576 656E 7473 5361 6D70 6C65"                      /* EventsSample */
};

data 'vers' (1) {
	$"0100 8000 0000 0331 2E30 1FA9 3139 3935"            /* ..Ä....1.0.©1995 */
	$"204D 6ABF 6C6E 6572 2049 6E66 6F72 6D61"            /*  Mjølner Informa */
	$"7469 6373 2C20 496E 632E"                           /* tics, Inc. */
};

data 'clut' (999) {
	$"0000 0204 0000 000F 0000 FFFF FFFF FFFF"            /* ..........ˇˇˇˇˇˇ */
	$"0001 EEEE EEEE EEEE 0002 DDDD DDDD DDDD"            /* ..ÓÓÓÓÓÓ..›››››› */
	$"0003 CCCC CCCC CCCC 0004 BBBB BBBB BBBB"            /* ..ÃÃÃÃÃÃ..ªªªªªª */
	$"0005 AAAA AAAA AAAA 0006 9999 9999 9999"            /* ..™™™™™™..ôôôôôô */
	$"0007 8888 8888 8888 0008 7777 7777 7777"            /* ..àààààà..wwwwww */
	$"0009 6666 6666 6666 000A 5555 5555 5555"            /* .∆ffffff..UUUUUU */
	$"000B 4444 4444 4444 000C 3333 3333 3333"            /* ..DDDDDD..333333 */
	$"000D 2222 2222 2222 000E 1111 1111 1111"            /* .¬""""""........ */
	$"000F 0000 0000 0000"                                /* ........ */
};

resource 'CNTL' (7128, purgeable, preload) {
	{-1, 385, 236, 401},
	0,
	visible,
	0,
	0,
	scrollBarProc,
	0,
	""
};

resource 'CNTL' (7129, purgeable, preload) {
	{235, -1, 251, 386},
	0,
	visible,
	0,
	0,
	scrollBarProc,
	0,
	""
};

resource 'MBAR' (7128, preload) {
	{	/* array MenuArray: 6 elements */
		/* [1] */
		7128,
		/* [2] */
		7129,
		/* [3] */
		7130,
		/* [4] */
		7131,
		/* [5] */
		7132,
		/* [6] */
		7133
	}
};

resource 'STR#' (7128, purgeable) {
	{	/* array StringArray: 12 elements */
		/* [1] */
		"BETA needs at least a Macintosh 512Ke to"
		" run.",
		/* [2] */
		"BETA needs at least system software 6.0 "
		"to run.",
		/* [3] */
		"Application memory size is too small.",
		/* [4] */
		"Not enough memory to run the BETA applic"
		"ation.",
		/* [5] */
		"Not enough memory to do Cut.",
		/* [6] */
		"Cannot do Cut.",
		/* [7] */
		"Cannot do Copy.",
		/* [8] */
		"Cannot exceed 32,000 characters with Pas"
		"te.",
		/* [9] */
		"Not enough memory to do Paste.",
		/* [10] */
		"Cannot create window.",
		/* [11] */
		"Cannot exceed 32,000 characters.",
		/* [12] */
		"Cannot do Paste."
	}
};

