resource 'SIZE' (-1, purgeable) {
	saveScreen,
	acceptSuspendResumeEvents,
	disableOptionSwitch,
	canBackground,
	multiFinderAware,
	backgroundAndForeground,
	dontGetFrontClicks,
	ignoreChildDiedEvents,
	is32BitCompatible,
	reserved,
	reserved,
	reserved,
	reserved,
	reserved,
	reserved,
	reserved,
	1400000,
	1400000
};

resource 'STR ' (129, "BETART", preload, locked) { "IOA#100:AOA#200:LVRA#200:CBFA#10" };


data 'ALRT' (7129) {
	$"0031 003C 0132 01C4 1BD9 5554 300A"                 /* .1.<.2.Ÿ..UT0. */
};

data 'DITL' (7129) {
	$"0001 0000 0000 00E1 0140 00F5 017A 0402"            /* .........@...z.. */
	$"4F4B 0000 0000 0011 000D 00D5 017A 8808"            /* OK.......¬.¹.zà. */
	$"5E30 5E31 5E32 5E33"                                /* ^0^1^2^3 */
};


