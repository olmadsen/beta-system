#include <stdio.h>
#include <string.h>

#ifdef __WIN32
#define SLEEPFACTOR *10
#else
#define SLEEPFACTOR /1000
#endif

static void
usage()
{
	fprintf(stderr, "Usage: slowwriter [-sne]\n");
	exit(1);
}

main(int argc, char **argv)
{
	int i;
        int sleepatend = 0;
        int newlineatend = 1;
        int usestderr = 0;
	int useboth = 0;
        if (argc > 2 || argc < 1)
		usage();
	if (argc == 2) {
		if (argv[1][0] != '-')
			usage();
		if (strchr(argv[1], 's'))
			sleepatend = 1;
		if (strchr(argv[1], 'n'))
			newlineatend = 0;
		if (strchr(argv[1], 'e'))
			usestderr = 1;
		if (strchr(argv[1], 'b'))
			useboth = 1;
	}
	for (i = 0; i < 5; i++) {
		fprintf(usestderr ? stderr : stdout, "%c", 'A' + i);
		if (i < 4 || newlineatend)
			fprintf(usestderr ? stderr : stdout, "\n");
		if (useboth)
		    usestderr = !(i & 1);
		fflush(stdout);
		sleep(i SLEEPFACTOR);
	}
	if (sleepatend)
		sleep(1000 SLEEPFACTOR);
}
