#include <jni.h>

#include <unistd.h>
#include <sstream>
#include <string>

#include "ghcversion.h"
#include "HsFFI.h"
#include "Rts.h"

#include "my_log.h"
#include "Lib_stub.h"
#include "FileSystem_stub.h"
#include "ForeignUtils_stub.h"
#include "android_hs_common.h"

/*#ifdef MY_LOG_TAG
#   undef MY_LOG_TAG
#   define MY_LOG_TAG create_log_tag_with_pid()
#endif

const char *create_log_tag_with_pid(void) {
    std::stringstream ss;
    ss << "native-lib.cpp" << "(" << getpid() << ")";
    return ss.str().c_str();
}*/

/*
char *copyCStr(const char *srcCStr) {
    LOG_E("%s", "before1 NewStringUTF");
    size_t jslen = strlen(srcCStr);
    LOG_E("%s", "before2 NewStringUTF");
    char newCStr[jslen];
    LOG_E("%s", "before3 NewStringUTF");
    memset(newCStr, '\0', jslen);
    LOG_E("%s", "before4 NewStringUTF");
    strcpy(newCStr, srcCStr);
    LOG_E("%s", "before5 NewStringUTF");
    return newCStr;
}
 */

extern "C" {

/**
 * Init haskell runtime.
 *
 * https://stackoverflow.com/questions/49554430/how-to-declare-native-cpp-method-for-which-declared-in-kotlin-companion-object?answertab=votes#tab-top
 */
JNIEXPORT void
JNICALL
Java_com_zw3rk_helloworld_HsApp_hsInit(
        JNIEnv *env,
        jclass thisClazz,
        jobjectArray jargv) {

    LOG_ASSERT(NULL != env, "JNIEnv cannot be NULL.");
    LOG_ASSERT(NULL != thisClazz, "jclass cannot be NULL.");
    LOG_ASSERT(NULL != jargv, "jobjectArray cannot be NULL.");
    LOG_D("native-lib", "env=%p thisClazz=%p", env, thisClazz);

    int argc = env->GetArrayLength(jargv);
    typedef char *pchar;
    pchar *argv = new pchar[argc];

    for (int i = 0; i < argc; i++) {
        jobject x = env->GetObjectArrayElement(jargv, i);
        jstring js = static_cast<jstring>(x);
        const char *pjc = env->GetStringUTFChars(js, NULL);
        size_t jslen = strlen(pjc);
        argv[i] = new char[jslen];
        strcpy(argv[i], pjc);
        env->ReleaseStringUTFChars(js, pjc);

        LOG_D("native-lib", "%s", argv[i]);
    }

#if __GLASGOW_HASKELL__ >= 703
    {
        RtsConfig conf = defaultRtsConfig;
        conf.rts_opts_enabled = RtsOptsAll;
        hs_init_ghc(&argc, &argv, conf);
    }
#else
    hs_init(&argc, &argv);
#endif

    //free the argv
    for (int i = 0; i < argc; i++)
        delete[] argv[i];
    delete[] argv;

    return;
}

/**
 * Exit haskell runtime.
 *
 * https://stackoverflow.com/questions/49554430/how-to-declare-native-cpp-method-for-which-declared-in-kotlin-companion-object?answertab=votes#tab-top
 */
JNIEXPORT void
JNICALL
Java_com_zw3rk_helloworld_HsApp_hsExit(
        JNIEnv *env,
        jclass thisClazz) {

    LOG_ASSERT(NULL != env, "JNIEnv cannot be NULL.");
    LOG_ASSERT(NULL != thisClazz, "jclass cannot be NULL.");
    LOG_D("native-lib", "env=%p thisClazz=%p", env, thisClazz);

    hs_exit();
    return;
}

JNIEXPORT jstring
JNICALL
Java_com_zw3rk_helloworld_MainActivity_stringFromJNI(
        JNIEnv *env,
        jobject thiz) {

    LOG_ASSERT(NULL != env, "JNIEnv cannot be NULL.");
    LOG_ASSERT(NULL != thiz, "jobject cannot be NULL.");

    return env->NewStringUTF(static_cast<const char *>(hello()));
}

JNIEXPORT jboolean
JNICALL
Java_com_zw3rk_helloworld_MainActivity_isElfFileFromJNI(
        JNIEnv *env,
        jobject thiz,
        jstring path) {

    LOG_ASSERT(NULL != env, "JNIEnv cannot be NULL.");
    LOG_ASSERT(NULL != thiz, "jobject cannot be NULL.");
    LOG_ASSERT(NULL != path, "jstring cannot be NULL.");

    const char *c_value = env->GetStringUTFChars(path, NULL);
    jboolean result = isElfFile(const_cast<char *>(c_value)) ? JNI_TRUE : JNI_FALSE;
    env->ReleaseStringUTFChars(path, c_value);
    return result;
}

JNIEXPORT jboolean
JNICALL
Java_com_zw3rk_helloworld_MainActivity_matchesGlobFromJNI(
        JNIEnv *env,
        jobject thiz,
        jstring name,
        jstring glob) {

    LOG_ASSERT(NULL != env, "JNIEnv cannot be NULL.");
    LOG_ASSERT(NULL != thiz, "jobject cannot be NULL.");
    LOG_ASSERT(NULL != name, "jstring cannot be NULL.");
    LOG_ASSERT(NULL != glob, "jstring cannot be NULL.");

    const char *c_name = env->GetStringUTFChars(name, NULL);
    const char *c_glob = env->GetStringUTFChars(glob, NULL);

    jboolean result = matchesGlob(const_cast<char *>(c_name), const_cast<char *>(c_glob))
                      ? JNI_TRUE : JNI_FALSE;

    env->ReleaseStringUTFChars(name, c_name);
    env->ReleaseStringUTFChars(glob, c_glob);
    return result;
}


/*
JNIEXPORT jobjectArray
JNICALL
Java_com_zw3rk_helloworld_MainActivity_namesMatchingJNI(
        JNIEnv *env,
        jobject thiz,
        jstring path) {

    LOG_ASSERT(NULL != env, "JNIEnv cannot be NULL.");
    LOG_ASSERT(NULL != thiz, "jobject cannot be NULL.");
    LOG_ASSERT(NULL != path, "jstring cannot be NULL.");

    const char *c_value = env->GetStringUTFChars(path, NULL);
    const char **result = static_cast<const char **>(namesMatching(
            const_cast<char *>(c_value)));
    jsize len = 0;
    for (; result[len] != NULL; len++);
    //jsize len = sizeof(result) / sizeof(result[0]);

    env->ReleaseStringUTFChars(path, c_value);
    jobjectArray strs = env->NewObjectArray(len, env->FindClass("java/lang/String"), env->NewStringUTF(""));
    for (int i = 0; i < len; i++) {
        jstring str = env->NewStringUTF(result[i]);
        env->SetObjectArrayElement(strs, i, str);
    }
    // freeCStringArray frees the newArray pointer created in haskell module
    freeNamesMatching(result);
    return strs;
}
*/

JNIEXPORT jobjectArray
JNICALL
Java_com_zw3rk_helloworld_MainActivity_namesMatchingJNI(
        JNIEnv *env,
        jobject thiz,
        jstring path) {

    LOG_ASSERT(NULL != env, "JNIEnv cannot be NULL.");
    LOG_ASSERT(NULL != thiz, "jobject cannot be NULL.");
    LOG_ASSERT(NULL != path, "jstring cannot be NULL.");

    const char *c_value = env->GetStringUTFChars(path, NULL);
    CStringArrayLen *cstrArrLen = static_cast<CStringArrayLen *>(namesMatching(
            const_cast<char *>(c_value)));

    char **result = cstrArrLen->cstringArray;
    jsize len = cstrArrLen->length;

    env->ReleaseStringUTFChars(path, c_value);
    jobjectArray strs = env->NewObjectArray(len, env->FindClass("java/lang/String"),
                                            env->NewStringUTF(""));
    for (int i = 0; i < len; i++) {
        jstring str = env->NewStringUTF(result[i]);
        env->SetObjectArrayElement(strs, i, str);
    }
    // freeCStringArray frees the newArray pointer created in haskell module
    freeNamesMatching(cstrArrLen);
    return strs;
}

}