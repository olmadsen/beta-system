#ifdef MAC
#include "pcre.h"
#else
#include "pcre/pcre.h"
#endif

#define PCRE_C_LOCALE 65536 /* Keep in sync with definition in perlregexp.bet */
#define PCRE_NONBETAOPTIONS 65535
#define PCRE_DO_STUDY 131072

static const char *precalc_tables = 0;

pcre *
locale_pcre_compile(
    const char *pattern,
    int options,
    const char **errptr,
    int *erroffset)
{
    const char *tables;
    if (!precalc_tables)
        precalc_tables = (char const *) pcre_maketables();
    if (options & PCRE_C_LOCALE) {
        options -= PCRE_C_LOCALE;
	tables = 0;
    }
    else
        tables = precalc_tables;

    return pcre_compile(pattern, options, errptr, erroffset, (unsigned char *) tables);
}
