# C

|一级目录|二级目录|三级目录|说明|
|-|-|-|-|
|standard|iso||`ISO C`的一些测试文件，其中大部分需要通过[GDB](http://blog.fpliu.com/it/software/GNU/GDB)调试进行查看|
|standard|posix||[POSIX](http://blog.fpliu.com/it/organization/IEEE/POSIX)标准的测试文件|
|||||
|library|mbedTLS|base64|[mbedTLS](http://blog.fpliu.com/it/software/mbedTLS) / [base64.h](http://blog.fpliu.com/it/software/mbedTLS/include/base64.h)的使用案例|
|library|mbedTLS|AES|[mbedTLS](http://blog.fpliu.com/it/software/mbedTLS) / [aes.h](http://blog.fpliu.com/it/software/mbedTLS/include/aes.h)的使用案例|
|library|mbedTLS|MD5|[mbedTLS](http://blog.fpliu.com/it/software/mbedTLS) / [md5.h](http://blog.fpliu.com/it/software/mbedTLS/include/md5.h)的使用案例|
|library|mbedTLS|RIPEMD-160|[mbedTLS](http://blog.fpliu.com/it/software/mbedTLS) / [ripemd160.h](http://blog.fpliu.com/it/software/mbedTLS/include/ripemd160.h)的使用案例|
|library|mbedTLS|SHA1|[mbedTLS](http://blog.fpliu.com/it/software/mbedTLS) / [sha1.h](http://blog.fpliu.com/it/software/mbedTLS/include/sha1.h)的使用案例|
|library|mbedTLS|SHA256|[mbedTLS](http://blog.fpliu.com/it/software/mbedTLS) / [sha256.h](http://blog.fpliu.com/it/software/mbedTLS/include/sha256.h)的使用案例|
|library|mbedTLS|SHA512|[mbedTLS](http://blog.fpliu.com/it/software/mbedTLS) / [sha512.h](http://blog.fpliu.com/it/software/mbedTLS/include/sha512.h)的使用案例|
|library|mbedTLS|HMAC|[mbedTLS](http://blog.fpliu.com/it/software/mbedTLS) / [md.h](http://blog.fpliu.com/it/software/mbedTLS/include/md.h)的使用案例|
|library|mbedTLS|PBKDF2|[mbedTLS](http://blog.fpliu.com/it/software/mbedTLS) / [pkcs5.h](http://blog.fpliu.com/it/software/mbedTLS/include/pkcs5.h)的使用案例|
|||||
|library|openssl|SHA256|[openssl](http://blog.fpliu.com/it/software/OpenSSL) / [sha.h](http://blog.fpliu.com/it/software/OpenSSL/include/sha.h)的使用案例|
|||||
|library|libcurl||[libcurl](http://blog.fpliu.com/it/software/curl)的使用案例|
|||||
|library|cJSON||[cJSON](http://blog.fpliu.com/it/software/development/language/C/library/cJSON)的使用案例|
|||||
|library|libyaml||[libyaml](http://blog.fpliu.com/it/software/development/language/C/library/libyaml)的使用案例|
|||||
|library|libgit2||[libgit2](http://blog.fpliu.com/it/software/development/language/C/library/libgit2)的使用案例|
|||||
|library|libarchive||[libarchive](http://blog.fpliu.com/it/software/development/language/C/library/libarchive)的使用案例|
|||||
|library|qrencode||[qrencode](http://blog.fpliu.com/it/software/qrencode)的使用案例|
|||||
|algorithm|base16||[Base16](http://blog.fpliu.com/it/data/text/coding/Base16)算法的实现|
|algorithm|url||[URL](http://blog.fpliu.com/it/data/text/coding/URL)编解码算法的实现|
|algorithm|bcc||[BCC](http://blog.fpliu.com/it/algorithm/check/BCC)校验算法的实现|
|algorithm|lrc||[LRC](http://blog.fpliu.com/it/algorithm/check/LRC)校验算法的实现|
|algorithm|chinese-calendar||中国阳历日期转换为阴历日期、节气、节日算法的实现|

## 开发测试过程

**step1. 安装`vcpkg`**
```bash
git clone https://github.com/microsoft/vcpkg.git
cd vcpkg
./bootstrap-vcpkg.sh
export VCPKG_ROOT="$PWD/vcpkg"
export PATH="$VCPKG_ROOT:$PATH"
```

**step2. 通过`vcpkg`安装依赖库**
```bash
vcpkg install curl libyaml libgit2 libarchive libqrencode cunit
```

**step3. 配置**
```bash
cmake \
    -S . \
    -B build.d \
    -DCMAKE_TOOLCHAIN_FILE=$VCPKG_ROOT/scripts/buildsystems/vcpkg.cmake \
    -DCMAKE_VERBOSE_MAKEFILE=ON \
    -DCMAKE_BUILD_TYPE=Debug \
    -DENABLE_TESTING=ON
```

**step4. 编译**
```bash
cmake --build build.d
```

**step5. 运行单元测试**
```bash
ctest --test-dir build.d/algorithm/base16
```

**step6. 运行valgrind测试**
```bash
valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --verbose --error-exitcode=1 build.d/algorithm/base16
```

## release安装过程

**step1. 安装`vcpkg`**
```bash
git clone https://github.com/microsoft/vcpkg.git
cd vcpkg
./bootstrap-vcpkg.sh
export VCPKG_ROOT="$PWD/vcpkg"
export PATH="$VCPKG_ROOT:$PATH"
```

**step2. 通过`vcpkg`安装依赖库**
```bash
vcpkg install curl libyaml libgit2 libarchive libqrencode cunit
```

**step3. 配置**
```bash
cmake \
    -S . \
    -B build.d \
    -DCMAKE_TOOLCHAIN_FILE=$VCPKG_ROOT/scripts/buildsystems/vcpkg.cmake \
    -DCMAKE_INSTALL_PREFIX=./output \
    -DCMAKE_VERBOSE_MAKEFILE=ON \
    -DCMAKE_BUILD_TYPE=Release \
    -DENABLE_TESTING=OFF
```

**step4. 编译**
```bash
cmake --build build.d
```

**step5. 安装**
```bash
cmake --install build.d
```
