#include <jni.h>
#include <jvm_hellolib.h>
#include <stdio.h>

JNIEXPORT void JNICALL
Java_jvm_beta_hellolib_hello(JNIEnv *env, jobject this, jstring who)
{
  printf("Hello to %s from C world\n", who);
}

