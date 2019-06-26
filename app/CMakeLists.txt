# For more information about using CMake with Android Studio, read the
# documentation: https://d.android.com/studio/projects/add-native-code.html

# Sets the minimum version of CMake required to build the native library.

cmake_minimum_required(VERSION 3.4.1)


set(MY_LD_FLAGS "-Wall -v -fPIC -Wl,-Bsymbolic")
set(ALIAS_0_ANDROID_ABI "aarch64-linux-android")
set(ALIAS_1_ANDROID_ABI "aarch64-android")

if (ANDROID_ABI STREQUAL "x86_64")
    set(CMAKE_SHARED_LINKER_FLAGS "${CMAKE_SHARED_LINKER_FLAGS} ${MY_LD_FLAGS} -Wl,--no-warn-shared-textrel")
    set(ALIAS_0_ANDROID_ABI "x86_64-linux-android")
    set(ALIAS_1_ANDROID_ABI "x86_64-android")
elseif (ANDROID_ABI STREQUAL "armeabi-v7a")
    set(CMAKE_SHARED_LINKER_FLAGS "${CMAKE_SHARED_LINKER_FLAGS} ${MY_LD_FLAGS} -Wl,--no-warn-shared-textrel")
    set(ALIAS_0_ANDROID_ABI "armv7-linux-androideabi")
    set(ALIAS_1_ANDROID_ABI "arm-android")
else ()
    set(CMAKE_SHARED_LINKER_FLAGS "${CMAKE_SHARED_LINKER_FLAGS} ${MY_LD_FLAGS} -v")
endif ()

# Creates and names a library, sets it as either STATIC
# or SHARED, and provides the relative paths to its source code.
# You can define multiple libraries, and CMake builds them for you.
# Gradle automatically packages shared libraries with your APK.

add_library( # Sets the name of the library.
        native-lib

        # Sets the library as a shared library.
        SHARED

        # Provides a relative path to your source file(s).
        src/main/cpp/native-lib.cpp)

# Searches for a specified prebuilt library and stores the path as a
# variable. Because CMake includes system libraries in the search path by
# default, you only need to specify the name of the public NDK library
# you want to add. CMake verifies that the library exists before
# completing its build.

find_library( # Sets the name of the path variable.
        log-lib

        # Specifies the name of the NDK library that
        # you want CMake to locate.
        log)

find_library(c-lib
        c)

find_library(z-lib
        z)

#[[find_library(hs-lib
        hs
        PATHS ${PROJECT_SOURCE_DIR}/hs-libs/${ANDROID_ABI}
        NO_CMAKE_FIND_ROOT_PATH)]]

add_library(lib_hs STATIC IMPORTED)
set_target_properties(lib_hs
        PROPERTIES
        IMPORTED_LOCATION $ENV{HOME}/dev_kit/src_code/haskell_code/learn-haskell/dist-newstyle/build/${ALIAS_1_ANDROID_ABI}/ghc-8.6.5/learn-haskell-0.1.0.0/build/libHSlearn-haskell-0.1.0.0-inplace-ghc8.6.5.a)


add_library(lib_hs2 STATIC IMPORTED)
set_target_properties(lib_hs2
        PROPERTIES
        IMPORTED_LOCATION $ENV{HOME}/dev_kit/src_code/haskell_code/android-hs-mobile-common/dist-newstyle/build/${ALIAS_1_ANDROID_ABI}/ghc-8.6.5/android-hs-mobile-common-0.1.0.0/build/libHSandroid-hs-mobile-common-0.1.0.0-inplace-ghc8.6.5.a)


# Specifies libraries CMake should link to your target library. You
# can link multiple libraries, such as libraries you define in this
# build script, prebuilt third-party libraries, or system libraries.

add_library(lib_iconv SHARED IMPORTED)
set_target_properties(lib_iconv
        PROPERTIES
        IMPORTED_LOCATION ${PROJECT_SOURCE_DIR}/hs-libs/${ANDROID_ABI}/libiconv.so)

add_library(lib_charset SHARED IMPORTED)
set_target_properties(lib_charset
        PROPERTIES
        IMPORTED_LOCATION ${PROJECT_SOURCE_DIR}/hs-libs/${ANDROID_ABI}/libcharset.so)

add_library(lib_ffi SHARED IMPORTED)
set_target_properties(lib_ffi
        PROPERTIES
        IMPORTED_LOCATION ${PROJECT_SOURCE_DIR}/hs-libs/${ANDROID_ABI}/libffi.so)

target_include_directories(native-lib PRIVATE
        $ENV{HOME}/dev_kit/haskell_sdk/ghc-8.6.5-20190531-${ALIAS_0_ANDROID_ABI}/lib/${ALIAS_0_ANDROID_ABI}-ghc-8.6.5/include
        $ENV{HOME}/dev_kit/src_code/haskell_code/android-hs-mobile-common/dist-newstyle/build/${ALIAS_1_ANDROID_ABI}/ghc-8.6.5/android-hs-mobile-common-0.1.0.0/build/Android
        ./src/main/hs
        )

target_link_libraries( # Specifies the target library.
        native-lib

        # Links the target library to the log library
        # included in the NDK.
        ${log-lib}
        ${c-lib}
        ${z-lib}
        lib_hs
        lib_hs2
        lib_iconv
        lib_charset
        lib_ffi
        stdc++
        )