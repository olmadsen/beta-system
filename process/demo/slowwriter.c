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
	fprintf(stderr, "Usage: slowwriter [-sn]\n");
	exit(1);
}

main(int argc, char **argv)
{
	int i;
        int sleepatend = 0;
        int newlineatend = 1;
        if (argc > 2 || argc < 1)
		usage();
	if (argc == 2) {
		if (argv[1][0] != '-')
			usage();
		if (strchr(argv[1], 's'))
			sleepatend = 1;
		if (strchr(argv[1], 'n'))
			newlineatend = 0;
	}
	for (i = 0; i < 5; i++) {
		printf("%c", 'A' + i);
		if (i < 4 || newlineatend)
			printf("\n");
		sleep(i SLEEPFACTOR);
	}
	if (sleepatend)
		sleep(1000 SLEEPFACTOR);
}
