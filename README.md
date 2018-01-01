# C
<a href="http://blog.fpliu.com/it/language/C" target="_blank">参考</a>

## 该项目目录结构
standard目录下是ANSI C标准的一些测试文件，其中大部分需要通过<a href="http://blog.fpliu.com/it/software/GNU/GDB" target="_blank">gdb</a>调试进行查看。<br><br>
posix目录下是<a href="http://blog.fpliu.com/it/organization/IEEE#POSIX" target="_blank">IEEE POSIX</a>标准的测试文件。<br><br>
library目录下是常用的第三方运行时库的一些使用测试。这些源文件都放在jni目录下，原因是为了兼容<a href="http://blog.fpliu.com/it/os/Android/ndk" target="_blank">Google NDK</a>中的ndk-build命令的构建。如果您想在PC上构建您当前系统的可执行文件，通过<a href="http://blog.fpliu.com/it/software/GNU/GCC" target="_blank">gcc</a>命令直接构建即可。<br><br>
algorithm目录下是一些常见算法实现。<br>
