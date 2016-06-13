# dtcodec

av decoder & encoder both for Linux & Android

## Installation

### Linux
* Install [x264](https://github.com/peterfuture/dtcodec/wiki/%E7%BC%96%E8%AF%91x264) Linux Version
* mkdir build & cd build
* cmake..
* make -j8

### Android
* Install [NDK](https://github.com/peterfuture/dttv-android/wiki/1-%E5%AE%89%E8%A3%85android-arm%E4%BA%A4%E5%8F%89%E7%BC%96%E8%AF%91%E9%93%BE)
* Install [x264](https://github.com/peterfuture/dtcodec/wiki/%E7%BC%96%E8%AF%91x264) Android Version
* mkdir build & cd build
* cmake -DCMAKE_TOOLCHAIN_FILE=../android_toolchain.cmake ..
* make -j8

## Author

peter_future@outlook.com

# Licence

GPL v3.0
