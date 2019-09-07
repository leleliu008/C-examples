# C
工作中用到的一些有关[C](http://blog.fpliu.com/it/software/development/language/C)语言相关的东西。


|一级目录|二级目录|说明
|-|-|-|
|standard|iso|[ISO C](http://blog.fpliu.com/it/software/development/language/C/standard#iso)的一些测试文件，其中大部分需要通过[GDB](http://blog.fpliu.com/it/software/GNU/GDB)调试进行查看|
|standard|posix|[POSIX](http://blog.fpliu.com/it/organization/IEEE#POSIX)标准的测试文件|
|library|cJSON|[cJSON](http://blog.fpliu.com/it/software/development/language/C/third-part-library/cJSON)的使用案例|
|library|mbedTLS|[mbedTLS](http://blog.fpliu.com/it/software/development/language/C/third-part-library/mbedTLS)的使用案例|
|algorithm|base16|[Base16](http://blog.fpliu.com/it/data/text/encoding/Base16)算法的实现
|algorithm|url|[URL](http://blog.fpliu.com/it/data/text/encoding/URL)编解码算法的实现


大多数源文件放在`jni`目录下，原因是为了兼容[Android NDK](http://blog.fpliu.com/it/software/GoogleAndroidNDK)中的[ndk-build](http://blog.fpliu.com/it/software/GoogleAndroidNDK/bin/ndk-build)命令的构建。如果您想构建您当前系统的可执行文件，通过[gcc](http://blog.fpliu.com/it/software/GNU/GCC/bin/gcc)或者[clang](http://blog.fpliu.com/it/software/clang)直接构建即可。
