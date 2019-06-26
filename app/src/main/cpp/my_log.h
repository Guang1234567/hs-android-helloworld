#pragma once

#include <jni.h>
#include <android/log.h>


#define __FILENAME__ (strrchr(__FILE__, '/') ? strrchr(__FILE__, '/') + 1 : __FILE__)


#ifndef MY_LOG_TAG
#   define MY_LOG_TAG __FILENAME__
#endif


#ifndef MY_LOG_LEVEL
#   define MY_LOG_LEVEL ANDROID_LOG_VERBOSE
#endif


#define LOG_NOOP (void) NULL


#define LOG_PRINT_TAG(level, tag, fmt, ...)    \
    if(tag == NULL || tag[0] == '\0') {     \
        __android_log_print(level, MY_LOG_TAG, "(%s:%u) %s: " fmt,  \
            __FILE__, __LINE__, __PRETTY_FUNCTION__, ##__VA_ARGS__); \
    } else {                                \
        __android_log_print(level, tag, "(%s:%u) %s: " fmt,         \
            __FILE__, __LINE__, __PRETTY_FUNCTION__, ##__VA_ARGS__); \
    }


#define LOG_PRINT(level, fmt, ...) \
    LOG_PRINT_TAG(level, MY_LOG_TAG, fmt, ##__VA_ARGS__)


#if ANDROID_LOG_VERBOSE >= MY_LOG_LEVEL
#   define LOG_V(tag, fmt, ...) \
        LOG_PRINT_TAG(ANDROID_LOG_VERBOSE, tag, fmt, ##__VA_ARGS__)
#else
#   define LOG_V(...) LOG_NOOP
#endif


#if ANDROID_LOG_DEBUG >= MY_LOG_LEVEL
#   define LOG_D(tag, fmt, ...) \
        LOG_PRINT_TAG(ANDROID_LOG_DEBUG, tag, fmt, ##__VA_ARGS__)
#else
#   define LOG_D(...) LOG_NOOP
#endif


#if ANDROID_LOG_INFO >= MY_LOG_LEVEL
#   define LOG_I(tag, fmt, ...) \
        LOG_PRINT_TAG(ANDROID_LOG_INFO, tag, fmt, ##__VA_ARGS__)
#else
#   define LOG_I(...) LOG_NOOP
#endif


#if ANDROID_LOG_WARN >= MY_LOG_LEVEL
#   define LOG_W(tag, fmt, ...) \
        LOG_PRINT_TAG(ANDROID_LOG_WARN, tag, fmt, ##__VA_ARGS__)
#else
#   define LOG_W(...) LOG_NOOP
#endif


#if ANDROID_LOG_ERROR >= MY_LOG_LEVEL
#   define LOG_E(tag, fmt, ...) \
        LOG_PRINT_TAG(ANDROID_LOG_ERROR, tag, fmt, ##__VA_ARGS__)
#else
#   define LOG_E(...) LOG_NOOP
#endif


#if ANDROID_LOG_FATAL >= MY_LOG_LEVEL
#   define LOG_FATAL(tag, fmt, ...) \
        LOG_PRINT_TAG(ANDROID_LOG_FATAL, tag, fmt, ##__VA_ARGS__)
#else
#   define LOG_FATAL(...) LOG_NOOP
#endif


#if ANDROID_LOG_FATAL >= MY_LOG_LEVEL
#   define LOG_ASSERT(expression, fmt, ...) \
        if (!(expression)) { \
            __android_log_assert(#expression, MY_LOG_TAG, "(%s:%u) %s: " fmt, \
        __FILE__, __LINE__, __PRETTY_FUNCTION__, ##__VA_ARGS__); \
    }
#else
#   define LOG_ASSERT(...) LOG_NOOP
#endif