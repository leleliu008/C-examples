#include<stdio.h>
#include<sys/syscall.h>

int main() {
    printf("use syscall,pid is:%d\n",syscall("__NR_getpid"));
    return 0;
} 
