#include "beta_PcreJvmHelper.h"
#include <stdlib.h>

/* Make actual pcre library part of this JNI library */
#include "pcre_beta.c"
#include "pcre/maketables.c"
#include "pcre/get.c"
#include "pcre/study.c"
#include "pcre/pcre.c"

/* JNI wrappers for functions we need to call from java */
/* .. */
