#include <jni.h>
#include <beta_hellolib.h>
#include <realhello.h>

JNIEXPORT void JNICALL Java_beta_hellolib_hello
  (JNIEnv *env, jobject obj, jstring who)
{
  const char *str = (*env)->GetStringUTFChars(env, who, 0);
  hello(str);
  (*env)->ReleaseStringUTFChars(env, who, str);
}

