#define Kb                1024
#define Mb             Kb * Kb

#ifndef DEFAULT_IOASIZE
#define DEFAULT_IOASIZE  512 * Kb
#endif

#ifndef DEFAULT_AOASIZE
#define DEFAULT_AOASIZE  512 * Kb
#endif

#ifndef DEFAULT_LVRASISE
#define DEFAULT_LVRASIZE 512 * Kb
#endif

#ifndef DEFAULT_CBFASIZE
#define DEFAULT_CBFASIZE   1 * Kb
#endif

#ifdef DOT
#ifndef DEFAULT_DOTSIZE
#define DEFAULT_DOTSIZE   0
#endif
#endif

#ifndef DEFAULT_IOAPERCENTAGE
#define DEFAULT_IOAPERCENTAGE  10
#endif


#ifndef DEFAULT_AOAMINFREE
#define DEFAULT_AOAMINFREE     100 * Kb
#endif

#ifndef DEFAULT_AOAPERCENTAGE
#define DEFAULT_AOAPERCENTAGE  0
#endif

#ifndef DEFAULT_LVRAMINFREE
#define DEFAULT_LVRAMINFREE    200 * Kb
#endif

#ifndef DEFAULT_LVRAPERCENTAGE
#define DEFAULT_LVRAPERCENTAGE 0
#endif
