OBJECTS = PPCMACexbobs.c.o :p2c:p2clib.c.o
LIBS =  "{SharedLibraries}"InterfaceLib ¶
		"{SharedLibraries}"StdCLib ¶
		"{SharedLibraries}"MathLib ¶
		"{PPCLibraries}"PPCToolLibs.o ¶
		"{PPCLibraries}"StdCRuntime.o ¶
		"{PPCLibraries}"PPCCRuntime.o

PPCMACexbobs ÄÄ PPCMACexbobs.make {OBJECTS}
	PPCLink -sym off -mf -c 'MPS ' -t MPST ¶
		{OBJECTS} ¶
		{LIBS} ¶
		-o PPCMACexbobs
		
		
PPCMACexbobs.c.o Ä PPCMACexbobs.make PPCMACexbobs.c
	 MrC -typecheck relaxed  -w off -i : -D MAC PPCMACexbobs.c
	 
:p2c:p2clib.c.o Ä PPCMACexbobs.make :p2c:p2clib.c
	 MrC -typecheck relaxed  -w 2 -i : -D MAC :p2c:p2clib.c

