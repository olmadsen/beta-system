#include <jni.h>
#include <beta_hellolib.h>
#include <realhello.h>

/* Function to handle non-ascci strings (e.g. latin1)
 * GetStringUTFChars will not work.
 * Taken from http://java.sun.com/docs/books/jni/html/other.html 
*/

#if USE_UTF8
/* Use GetStringUTFChars */
#else
static jmethodID MID_String_getBytes = 0;

void
JNU_ThrowByName(JNIEnv *env, const char *name, const char *msg)
{
  jclass cls = (*env)->FindClass(env, name);
  /* if cls is NULL, an exception has already been thrown */
  if (cls != NULL) {
    (*env)->ThrowNew(env, cls, msg);
  }
  /* free the local ref */
  (*env)->DeleteLocalRef(env, cls);
}

char *JNU_GetStringNativeChars(JNIEnv *env, jstring jstr)
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
#endif

JNIEXPORT void JNICALL Java_beta_hellolib_hello
  (JNIEnv *env, jobject obj, jstring who)
{
  const char *str;
#if USE_UTF8
  str = (*env)->GetStringUTFChars(env, who, 0);
#else
  str = JNU_GetStringNativeChars(env, who);
#endif
  hello(str);
#if USE_UTF8
  (*env)->ReleaseStringUTFChars(env, who, str);
#endif

}

