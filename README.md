# dtcodec

av decoder & encoder both for Linux & Android

## Feature

Video Encoder
* H264 - X264 √

## Build

git clone https://github.com/peterfuture/dtcodec<br>
git submodule update --init

###Linux

* cd x264
* ./configure --disable-asm --enable-shared --enable-static
* make & cd ..
* mkdir build & cd build
* cmake.. & make -j8


### Android

* Install [NDK](https://github.com/peterfuture/dttv-android/wiki/1-%E5%AE%89%E8%A3%85android-arm%E4%BA%A4%E5%8F%89%E7%BC%96%E8%AF%91%E9%93%BE)
* cd x264
* ./configure --cross-prefix=arm-linux-androideabi- --sysroot="$ANDROID_SYSROOT" --host=arm-linux --enable-pic --enable-static --disable-cli
* make & cd ..
* mkdir build & cd build
* cmake -DCMAKE_TOOLCHAIN_FILE=../android_toolchain.cmake ..
* make -j8

## Author

peter_future@outlook.com

# Licence

GPL v3.0
