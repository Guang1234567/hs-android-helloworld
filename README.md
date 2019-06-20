# How to run?

I build this project on osx. No experencise in ubuntu or windows.

## download the cross compile and llvm and toolchain-wrapper and ndk 14

more info by http://hackage.mobilehaskell_sdk.org/

[toolchain-wrapper](https://github.com/zw3rk/toolchain-wrapper)

ndk 14

## modify the $PATH

```bash
export LLVM_HOME=$HOME/dev_kit/haskell_sdk/clang+llvm-5.0.0-x86_64-apple-darwin
export PATH=$LLVM_HOME/bin:$HOME/dev_kit/haskell_sdk/ghc-8.6.5-20190531-aarch64-linux-android/bin:$HOME/dev_kit/haskell_sdk/ghc-8.6.5-20190531-armv7-linux-androideabi/bin:$HOME/dev_kit/haskell_sdk/ghc-8.6.5-20190531-x86_64-linux-android/bin:$HOME/dev_kit/haskell_sdk/ghc-8.6.5-20190531-aarch64-apple-ios/bin:$HOME/dev_kit/haskell_sdk/ghc-8.6.5-20190531-x86_64-apple-ios/bin:$HOME/dev_kit/haskell_sdk/toolchain-wrapper:$PATH
```


## build libhs.so

Building `.so` is different from `.a`.  Because you must link the `-lHSrts-1.0 -lHSrts-1.0_thr -lCffi -lCffi_thr`.

They are here: `$HOME/dev_kit/haskell_sdk/ghc-8.6.5-20190531-armv7-linux-androideabi/lib/arm-linux-android-ghc-8.6.5-20190531/rts-1.0`

```bash
  
  # $HOME/dev_kit/haskell_sdk/ghc-8.6.5-20190531-armv7-linux-androideabi/bin/armv7-linux-androideabi-ghc
  
  armv7-linux-androideabi-ghc -fPIC \
      -shared -liconv -lcharset -lffi -lHSrts -lHSrts_thr \
      -I$HOME/dev_kit/haskell_sdk/ghc-build-scripts/dist/libffi-prefix/armv7-linux-androideabi/include \
      -I$HOME/dev_kit/haskell_sdk/ghc-8.6.5-20190531-armv7-linux-androideabi/lib/armv7-linux-androideabi-ghc-8.6.5/include \
      -L./hs-libs/armeabi-v7a \
      -L$HOME/dev_kit/Android/sdk/ndk-bundle/toolchains/arm-linux-androideabi-4.9/prebuilt/darwin-x86_64/lib/gcc/arm-linux-androideabi/4.9.x \
      -o ./hs-libs/armeabi-v7a/libhs.so \
      ./src/main/hs/Lib.hs
  
  
  aarch64-linux-android-ghc -fPIC \
  -I$HOME/dev_kit/haskell_sdk/ghc-build-scripts/dist/libffi-prefix/aarch64-linux-android/include \
    -shared -liconv -lcharset -lffi -lHSrts -lHSrts_thr -lHSdirectory-1.3.3.0 \
    -L./hs-libs/arm64-v8a \
    -L$HOME/dev_kit/Android/sdk/ndk-bundle/toolchains/aarch64-linux-android-4.9/prebuilt/darwin-x86_64/lib/gcc/aarch64-linux-android/4.9.x \
    -L$HOME/dev_kit/haskell_sdk/ghc-8.6.5-20190531-aarch64-linux-android/lib/aarch64-linux-android-ghc-8.6.5/rts \
    -L$HOME/dev_kit/haskell_sdk/ghc-8.6.5-20190531-aarch64-linux-android/lib/aarch64-linux-android-ghc-8.6.5/directory-1.3.3.0 \
    -o ./hs-libs/arm64-v8a/libhs.so \
    ./src/main/hs/Lib.hs
  
  x86_64-linux-android-ghc -fPIC \
    -I$HOME/dev_kit/haskell_sdk/ghc-build-scripts/dist/libffi-prefix/x86_64-linux-android/include \
      -shared -liconv -lcharset -lffi -lHSrts -lHSrts_thr \
      -L./hs-libs/x86_64 \
      -L$HOME/dev_kit/Android/sdk/ndk-bundle/toolchains/x86_64-linux-android-4.9/prebuilt/darwin-x86_64/lib/gcc/x86_64-linux-android/4.9.x \
      -L$HOME/dev_kit/haskell_sdk/ghc-8.6.5-20190531-x86_64-linux-android/lib/x86_64-linux-android-ghc-8.6.5/rts \
      -o ./hs-libs/x86_64/libhs.so \
      ./src/main/hs/Lib.hs
```


## run

import into android studio and run it.