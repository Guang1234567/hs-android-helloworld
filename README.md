# How to run?

## download the cross compile and llvm and toolchain-wrapper

more info by http://hackage.mobilehaskell.org/

[toolchain-wrapper](https://github.com/zw3rk/toolchain-wrapper)

ndk 14


## modify the $PATH

```bash
export LLVM_HOME=$HOME/dev_kit/haskell/clang+llvm-5.0.0-x86_64-apple-darwin
export PATH=$LLVM_HOME/bin:$HOME/dev_kit/haskell/ghc-8.4.0.20180109-aarch64-linux-android/bin:$HOME/dev_kit/haskell/ghc-8.4.0.20180109-armv7-linux-androideabi/bin:$HOME/dev_kit/haskell/ghc-8.4.0.20180109-x86_64-linux-android/bin:$HOME/dev_kit/haskell/ghc-8.4.0.20180109-aarch64-apple-ios/bin:$HOME/dev_kit/haskell/ghc-8.4.0.20180109-x86_64-apple-ios/bin:$HOME/dev_kit/haskell/toolchain-wrapper:$PATH
```


## build libhs.a

```bash
armv7-linux-androideabi-ghc -fPIC \
  -L./pre-build-libs/libiconv_prefix/arm-linux-androideabi/lib \
  -staticlib -liconv -lcharset \
  -o /Users/XXXXX/dev_kit/src_code/hs-android-helloworld/app/hs-libs/armeabi-v7a/libhs.a \
  ./src/main/hs/Lib.hs
  
  
  aarch64-linux-android-ghc -fPIC \
  -L./pre-build-libs/libiconv_prefix/aarch64-linux-android/lib \
  -staticlib -liconv -lcharset \
  -o /Users/XXXXX/dev_kit/src_code/hs-android-helloworld/app/hs-libs/arm64-v8a/libhs.a \
  ./src/main/hs/Lib.hs
  
  x86_64-linux-android-ghc -fPIC \
  -L./pre-build-libs/libiconv_prefix/x86_64/lib \
  -staticlib -liconv -lcharset \
  -o /Users/XXXXX/dev_kit/src_code/hs-android-helloworld/app/hs-libs/x86_64/libhs.a \
  ./src/main/hs/Lib.hs
```


## run

import into android studio and run it.