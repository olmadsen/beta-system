#include <stdio.h>
#include <string.h>
#include <errno.h>

#ifdef __WIN32
#include <windows.h>
#define SLEEPFACTOR *10
#else
#define SLEEPFACTOR /1000
#endif

static void
usage()
{
	fprintf(stderr, "Usage: reader [-w]\n"
		" -w Use Windows handles (not stdio)\n");
	exit(1);
}

main(int argc, char **argv)
{
	int i;
	int result;
	int c;
	char ch;
        if (argc > 1)
		if (argv[1][0] != '-')
			usage();
#ifdef __WIN32
	if (argc > 1 && strchr(argv[1], 'w')) {
		HANDLE in = GetStdHandle(STD_INPUT_HANDLE);
		HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);
		DWORD bytesread, byteswritten;
		DWORD lasterror;
		while(ReadFile(in, &ch, 1, &bytesread, 0)) {
			if (ch >= 'A' && ch <= 'Z')
				ch -= 'A' - 'a';
			else if (ch >= 'a' && ch <= 'z')
				ch -= 'a' - 'A';
			WriteFile(out, &ch, 1, &byteswritten, 0);
		}
		lasterror = GetLastError();
		if (lasterror != ERROR_SUCCESS &&
                    lasterror != ERROR_BROKEN_PIPE) {
			fprintf(stderr, "Reader got error %d!\n", lasterror);
		} else {
			sleep(100 SLEEPFACTOR);
			WriteFile(out, "Reader normal exit\n",
				strlen("Reader normal exit\n"), &byteswritten,
				0);
		}
	} else {
#endif /* def __WIN32 */
		while ((c = getchar()) != EOF) {
			if (c >= 'A' && c <= 'Z')
				c -= 'A' - 'a';
			else if (c >= 'a' && c <= 'z')
				c -= 'a' - 'A';
			putchar(c);
		}
		if (errno) {
			perror("reading from pipe");
		} else {
			sleep(100 SLEEPFACTOR);
			printf("READER NORMAL EXIT\n");
		}
#ifdef __WIN32
	}
#endif __WIN32
	exit(0);
}
