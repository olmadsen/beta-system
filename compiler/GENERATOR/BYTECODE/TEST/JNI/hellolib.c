#include <jni.h>
#include <beta_hellolib.h>
#include <realhello.h>

JNIEXPORT void JNICALL Java_beta_hellolib_hello
  (JNIEnv *env, jobject obj, jstring who)
{
  jboolean iscopy;
  hello((*env)->GetStringUTFChars(env, who, &iscopy));
}

