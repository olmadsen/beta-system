#undef TRACE

#include "beta_PcreJvmHelper.h"
#include <stdlib.h>
#include "pcre/pcre.h"

/* Make actual pcre library part of this JNI library */
#include "pcre_beta.c"
#include "pcre/maketables.c"
#include "pcre/get.c"
#include "pcre/study.c"
#include "pcre/pcre.c"

/* JNI wrappers for functions we need to call from BETA via JNI */

static char *errtext=NULL;
static int erroffset=0;


/* Accessor functions for error reporting */
JNIEXPORT jstring JNICALL 
Java_beta_PcreJvmHelpers_last_error (JNIEnv *env, jclass c)
{
}

JNIEXPORT jint JNICALL 
Java_beta_PcreJvmHelpers_last_error_offset (JNIEnv *env, jclass c)
{
}


/* initialize:
 *   arguments: regexp, options
 *   returns:   array: [compiled_regexp, extra, subpatterns]
 */
JNIEXPORT jintArray JNICALL 
Java_beta_PcreJvmHelper_initialize(JNIEnv *env, jclass jobj, jstring jexp, jint options)
{
  const char *regexp=NULL;
  pcre *compiled_regexp;
  pcre_extra *extra;
  int subpatterns;
  int result[3];
  jintArray jresult = (*env)->NewIntArray(env, 3);
  (*env)->SetIntArrayRegion(env, jresult, 0, 3, result);

  if (!jexp) return jresult;
  
  regexp = (*env)->GetStringUTFChars(env, jexp, (jboolean *)NULL);
  
  if (options & PCRE_C_LOCALE){
    result[0] = (int)pcre_compile(regexp, 
				  options & PCRE_NONBETAOPTIONS,
				  (const char **)&errtext,
				  &erroffset, 
				  0);
  } else {
    result[0] = (int)locale_pcre_compile(regexp, 
					 options & PCRE_NONBETAOPTIONS,
					 (const char **)&errtext,
					 &erroffset);
  }
  if (!result[0]){
    return jresult;
  } else {
    if (options & PCRE_DO_STUDY){
      result[1] = (int)pcre_study((pcre*)result[0], 
				  options & PCRE_NONBETAOPTIONS, 
				  (const char **)&errtext);
      if (!errtext){
	return jresult;
      }
    }
    pcre_fullinfo((pcre*)result[0], 
		  (pcre*)result[1], 
		  PCRE_INFO_CAPTURECOUNT, 
		  &result[2]);
    (*env)->SetIntArrayRegion(env, jresult, 0, 3, result);
  }

  (*env)->ReleaseStringUTFChars(env, jexp, regexp);

  return jresult;
}


/* exec:
 */

JNIEXPORT jint JNICALL Java_beta_PcreJvmHelper_exec
  (JNIEnv *env, jclass jobj, jint code, jint extra, jstring jsubject, jint length, jint startoffset, jint options, jintArray jovector, jint ovecsize)
{
  int result;
  int ovector[ovecsize];
  const char *subject = (*env)->GetStringUTFChars(env, jsubject, (jboolean *)NULL);
  (*env)->GetIntArrayRegion(env, jovector, 0, ovecsize, ovector);
#ifdef TRACE
  printf("Java_beta_PcreJvmHelper_exec: subject: \"%s\"\n", subject);
#endif
  result = pcre_exec((const pcre *)code, 
		     (const pcre_extra *)extra,
		     (const char *)subject, 
		     length, 
		     startoffset,
		     options, 
		     ovector, 
		     ovecsize);
  (*env)->SetIntArrayRegion(env, jovector, 0, ovecsize, ovector);
  (*env)->ReleaseStringUTFChars(env, jsubject, subject);

  return result;
}
