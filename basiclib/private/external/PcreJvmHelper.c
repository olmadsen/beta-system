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

static char *errtext=NULL;
static int erroffset=0;

/* Function to handle non-ascii strings (e.g. latin1)
 * GetStringUTFChars will not work.
 * Taken from http://java.sun.com/docs/books/jni/html/other.html 
*/

static jmethodID MID_String_getBytes = 0;

static void JNU_ThrowByName(JNIEnv *env, const char *name, const char *msg)
{
  jclass cls = (*env)->FindClass(env, name);
  /* if cls is NULL, an exception has already been thrown */
  if (cls != NULL) {
    (*env)->ThrowNew(env, cls, msg);
  }
  /* free the local ref */
  (*env)->DeleteLocalRef(env, cls);
}

static char *JNU_GetStringNativeChars(JNIEnv *env, jstring jstr)
 {
   jbyteArray bytes = 0;
   jthrowable exc;
   char *result = 0;
   if ((*env)->EnsureLocalCapacity(env, 2) < 0) {
     return 0; /* out of memory error */
   }
   if (!MID_String_getBytes){
     jclass cls = (*env)->FindClass(env, "java/lang/String");
     MID_String_getBytes = (*env)->GetMethodID(env, cls, "getBytes", "()[B");
   }
   bytes = (*env)->CallObjectMethod(env, jstr, MID_String_getBytes);
   exc = (*env)->ExceptionOccurred(env);
   if (!exc) {
     jint len = (*env)->GetArrayLength(env, bytes);
     result = (char *)malloc(len + 1);
     if (result == 0) {
       JNU_ThrowByName(env, "java/lang/OutOfMemoryError", 0);
       (*env)->DeleteLocalRef(env, bytes);
       return 0;
     }
     (*env)->GetByteArrayRegion(env, bytes, 0, len,
				(jbyte *)result);
     result[len] = 0; /* NULL-terminate */
   } else {
     (*env)->DeleteLocalRef(env, exc);
   }
   (*env)->DeleteLocalRef(env, bytes);
   return result;
 }

/* JNI wrappers for functions we need to call from BETA via JNI */

/*
 * Class:     beta_PcreJvmHelper
 * Method:    compile
 * Signature: (Ljava/lang/String;II)I
 */
JNIEXPORT jint JNICALL Java_beta_PcreJvmHelper_compile
(JNIEnv *env, jclass jobj, jstring jexp, jint options, jint tableptr)
{
  const char *regexp=NULL;
  pcre *compiled_regexp;
  
  if (!jexp) return 0;
  errtext=NULL;
  regexp = JNU_GetStringNativeChars(env, jexp);
#ifdef TRACE 
  printf("PcreJvmHelper_compile: regexp=\"%s\"\n", regexp);
#endif
  compiled_regexp = pcre_compile(regexp, 
				 options,
				 (const char **)&errtext,
				 &erroffset, 
				 (const unsigned char *)0);
  return (jint)compiled_regexp;
}



/*
 * Class:     beta_PcreJvmHelper
 * Method:    locale_compile
 * Signature: (Ljava/lang/String;I)I
 */
JNIEXPORT jint JNICALL Java_beta_PcreJvmHelper_locale_1compile
(JNIEnv *env, jclass jobj, jstring jexp, jint options)
{
  const char *regexp=NULL;
  pcre *compiled_regexp;

  if (!jexp) return 0;
  errtext=NULL;
  regexp = JNU_GetStringNativeChars(env, jexp);
#ifdef TRACE 
  printf("PcreJvmHelper_locale_compile: regexp=\"%s\"\n", regexp);
#endif
  compiled_regexp = locale_pcre_compile(regexp, 
					options,
					(const char **)&errtext,
					&erroffset);
  return (jint)compiled_regexp;
}



/*
 * Class:     beta_PcreJvmHelper
 * Method:    exec
 * Signature: (IILjava/lang/String;III[II)I
 */
JNIEXPORT jint JNICALL Java_beta_PcreJvmHelper_exec
(JNIEnv *env, jclass jobj, jint code, jint extra, jstring jsubject, jint length, jint startoffset, jint options, jintArray jovector, jint ovecsize)
{
  int result;
#ifdef WIN32
  int *ovector = malloc(sizeof(int)*ovecsize);
#else
  int ovector[ovecsize];
#endif
  const char *subject = JNU_GetStringNativeChars(env, jsubject);
  (*env)->GetIntArrayRegion(env, jovector, 0, ovecsize, (jint *)ovector);
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
  (*env)->SetIntArrayRegion(env, jovector, 0, ovecsize, (jint*)ovector);
#ifdef WIN32
  free(ovector);
#endif

  return result;
}



/*
 * Class:     beta_PcreJvmHelper
 * Method:    study
 * Signature: (II)I
 */
JNIEXPORT jint JNICALL Java_beta_PcreJvmHelper_study
(JNIEnv *env, jclass jobj, jint code, jint options)
{
  pcre_extra *extra;
  errtext=NULL;
  extra = pcre_study((pcre*)code, 
		     options, 
		     (const char **)&errtext);
  return (jint)extra;
}



/*
 * Class:     beta_PcreJvmHelper
 * Method:    full_info
 * Signature: (III)[I
 */
JNIEXPORT jintArray JNICALL Java_beta_PcreJvmHelper_full_1info
(JNIEnv *env, jclass jobj, jint code, jint extra, jint what)
{
  int results[2]; /* Multiple return: (where, status) */
  jintArray jresults;
  results[1]=pcre_fullinfo((pcre*)code, 
			   (pcre_extra*)extra, 
			   what, 
			   (void*)&results[0]);
  jresults = (*env)->NewIntArray(env, 2);
  (*env)->SetIntArrayRegion(env, jresults, 0, 2, (jint*)results);
  return jresults;
}



/*
 * Class:     beta_PcreJvmHelper
 * Method:    last_error
 * Signature: ()Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_beta_PcreJvmHelper_last_1error
(JNIEnv *env, jclass jobj)
{
  if (errtext){
    return (*env)->NewStringUTF(env, errtext);
  } else {
    return NULL;
  }
}



/*
 * Class:     beta_PcreJvmHelper
 * Method:    last_error_offset
 * Signature: ()I
 */
JNIEXPORT jint JNICALL Java_beta_PcreJvmHelper_last_1error_1offset
(JNIEnv *env, jclass jobj)
{
  return erroffset;
}

