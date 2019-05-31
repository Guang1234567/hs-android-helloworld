#include <jni.h>
#include <string>
//#include "Lib_stub.h"

extern "C" {

extern void hs_init(int *argc, char **argv[]);
extern char *hello(void);

extern double strtod(const char *nptr, char **endptr);

double atof(const char *nptr)
{
    return (strtod(nptr, NULL));
}

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

/*JNIEXPORT jstring
JNICALL
Java_com_zw3rk_helloworld_MainActivity_stringFromJNI(
        JNIEnv* env,
jobject *//* this *//*) {
std::string hello = "Hello from C++";
return env->NewStringUTF(hello.c_str());
}*/

}