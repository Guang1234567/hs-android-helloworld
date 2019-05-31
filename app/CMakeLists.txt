# For more information about using CMake with Android Studio, read the
# documentation: https://d.android.com/studio/projects/add-native-code.html

# Sets the minimum version of CMake required to build the native library.

cmake_minimum_required(VERSION 3.4.1)


set(MY_LD_FLAGS "-Wall -v -fPIC -Wl,-Bsymbolic")

if (ANDROID_ABI STREQUAL "x86_64")
    set(CMAKE_SHARED_LINKER_FLAGS "${CMAKE_SHARED_LINKER_FLAGS} ${MY_LD_FLAGS} -Wl,--no-warn-shared-textrel")
elseif (ANDROID_ABI STREQUAL "x86")
    set(CMAKE_SHARED_LINKER_FLAGS "${CMAKE_SHARED_LINKER_FLAGS} ${MY_LD_FLAGS} -Wl,--no-warn-shared-textrel")
elseif (ANDROID_ABI STREQUAL "armeabi-v7a")
    set(CMAKE_SHARED_LINKER_FLAGS "${CMAKE_SHARED_LINKER_FLAGS} ${MY_LD_FLAGS} -Wl,--no-warn-shared-textrel")
else ()
    set(CMAKE_SHARED_LINKER_FLAGS "${CMAKE_SHARED_LINKER_FLAGS} ${MY_LD_FLAGS}")
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

find_library(hs-lib
        hs
        PATHS ${PROJECT_SOURCE_DIR}/hs-libs/${ANDROID_ABI}
        NO_CMAKE_FIND_ROOT_PATH)

# Specifies libraries CMake should link to your target library. You
# can link multiple libraries, such as libraries you define in this
# build script, prebuilt third-party libraries, or system libraries.

add_library(lib_iconv STATIC IMPORTED)
set_target_properties(lib_iconv
        PROPERTIES
        IMPORTED_LOCATION /Users/lihanguang/dev_kit/haskell/ghc-build-scripts/dist/libiconv_prefix/${ANDROID_ABI}/lib/libiconv.a)

add_library(lib_charset STATIC IMPORTED)
set_target_properties(lib_charset
        PROPERTIES
        IMPORTED_LOCATION /Users/lihanguang/dev_kit/haskell/ghc-build-scripts/dist/libiconv_prefix/${ANDROID_ABI}/lib/libcharset.a)


target_include_directories(native-lib PRIVATE
        ./src/main/hs
        /Users/lihanguang/dev_kit/haskell/ghc-8.6.5-20190531-armv7-linux-androideabi/lib/armv7-linux-androideabi-ghc-8.6.5/include
        /Users/lihanguang/dev_kit/haskell/ghc-build-scripts/dist/libiconv_prefix/${ANDROID_ABI}/include)

target_link_libraries( # Specifies the target library.
        native-lib

        # Links the target library to the log library
        # included in the NDK.
        ${log-lib}
        ${c-lib}
        ${hs-lib}
        lib_iconv
        lib_charset
        stdc++
        )