#include <jni.h>
#include <string>
//#include "Lib_stub.h"

extern "C" {

extern void hs_init(int *argc, char **argv[]);
extern char *hello(void);
extern bool isElfFile(const char *path);

JNIEXPORT void
JNICALL
Java_com_zw3rk_helloworld_MainActivityKt_initHS(
        JNIEnv *env,
        jclass /* this */) {
    hs_init(NULL, NULL);
    return;
}

JNIEXPORT jstring
JNICALL
Java_com_zw3rk_helloworld_MainActivity_stringFromJNI(
        JNIEnv *env,
        jobject /* this */) {
    return env->NewStringUTF(hello());
}

JNIEXPORT jboolean
JNICALL
Java_com_zw3rk_helloworld_MainActivity_isElfFileFromJNI(
        JNIEnv *env,
        jobject /* this */,
        jstring path) {
    jboolean isCopy;
    const char *c_value = env->GetStringUTFChars(path, &isCopy);
    printf("%s", c_value);
    jboolean result = isElfFile(c_value) ? JNI_TRUE : JNI_FALSE;
    if (isCopy == JNI_TRUE)
        env->ReleaseStringUTFChars(path, c_value);
    return result;
}

/*JNIEXPORT jstring
JNICALL
Java_com_zw3rk_helloworld_MainActivity_stringFromJNI(
        JNIEnv* env,
jobject *//* this *//*) {
std::string hello = "Hello from C++";
return env->NewStringUTF(hello.c_str());
}*/

}