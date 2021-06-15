# C

|一级目录|二级目录|三级目录|说明|
|-|-|-|-|
|standard|iso||`ISO C`的一些测试文件，其中大部分需要通过[GDB](http://blog.fpliu.com/it/software/GNU/GDB)调试进行查看|
|standard|posix||[POSIX](http://blog.fpliu.com/it/organization/IEEE/POSIX)标准的测试文件|
|||||
|library|cJSON||[cJSON](http://blog.fpliu.com/it/software/development/language/C/library/cJSON)的使用案例|
|library|qrencode||[qrencode](http://blog.fpliu.com/it/software/qrencode)的使用案例|
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
|algorithm|base16||[Base16](http://blog.fpliu.com/it/data/text/coding/Base16)算法的实现|
|algorithm|url||[URL](http://blog.fpliu.com/it/data/text/coding/URL)编解码算法的实现|
|algorithm|BCC||[BCC](http://blog.fpliu.com/it/algorithm/check/BCC)校验算法的实现|
|algorithm|LRC||[LRC](http://blog.fpliu.com/it/algorithm/check/LRC)校验算法的实现|
|algorithm|chinese-calendar||中国阳历日期转换为阴历日期、节气、节日算法的实现|

## 编译
每个模块都可以独立编译。也可以整体编译。
```bash
cmake -S . -B build.d -DCMAKE_INSTALL_PREFIX=./output -DENABLE_TESTING=ON
cmake --build build.d --target install
```

## 运行单元测试程序
```bash
cmake --test-dir build.d/algorithm/base16
```
