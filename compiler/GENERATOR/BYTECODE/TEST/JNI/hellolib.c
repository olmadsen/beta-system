#include <jni.h>
#include <hellolib.h>
#include <stdio.h>

JNIEXPORT void JNICALL
Java_hellolib_hello(JNIEnv *env, jobject this, jstring who)
{
  jboolean iscopy;
  printf("Hello to %s from C world\n", (*env)->GetStringUTFChars(env, who, &iscopy));
}

