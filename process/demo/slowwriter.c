#include <stdio.h>

#ifdef __WIN32
#define SLEEPFACTOR *10
#else
#define SLEEPFACTOR /100
#endif

static void
usage()
{
	fprintf(stderr, "Usage: slowwriter [-s]\n");
	exit(1);
}

main(int argc, char **argv)
{
	int i;
        int sleepatend = 0;
        if (argc > 1)
		if (argv[1][0] != '-')
			usage();
	if (strchr(argv[1], 's'))
		sleepatend = 1;
	for (i = 0; i < 5; i++) {
		printf("%d\n", i);
		fprintf(stderr, "%d\n", i);
		sleep(i SLEEPFACTOR);
	}
	if (sleepatend)
		sleep(10 SLEEPFACTOR);
}
