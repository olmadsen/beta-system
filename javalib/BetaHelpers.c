#include "beta_BetaHelpers.h"
#include <stdlib.h>
#ifdef unix /* Set by e.g. gcc; verify this by: gcc -E -dM foo.h */
#include <sys/types.h>
#include <sys/stat.h>
#endif /* unix */

JNIEXPORT jstring JNICALL Java_beta_BetaHelpers_getenv 
  (JNIEnv *env, jclass c, jstring jname)
{
  const char *name, *value;

  if (!jname) return NULL;

  name = (*env)->GetStringUTFChars(env, jname, (jboolean *)NULL);

  value = getenv(name);

  (*env)->ReleaseStringUTFChars(env, jname, name);

  return value ? (*env)->NewStringUTF(env, value) : NULL;
}

JNIEXPORT void JNICALL Java_beta_BetaHelpers_setFileExePermission
  (JNIEnv *env, jclass c, jstring jpath)
{

#ifdef unix
  const char *path;
  struct stat statBuffer;

  if (!jpath) return;

  path = (*env)->GetStringUTFChars(env, jpath, (jboolean *)NULL);

  
  if (stat(path,&statBuffer)==0){
    chmod(path, statBuffer.st_mode | S_IXUSR | S_IXGRP | S_IXOTH);
  }

  (*env)->ReleaseStringUTFChars(env, jpath, path);

#endif /* unix */
}

