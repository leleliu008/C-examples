//http://blog.fpliu.com/it/software/development/language/C/library/mbedTLS/include/md5.h

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stdbool.h>
#include"mbedtls/md5.h"

void showHelp() {
    printf("usage: md5 [option] <str>\n");
    printf("option: -x lower case, default true\n");
    printf("        -X upper case\n");
    printf("example:md5 -X sssssss\n");
    exit(1);
}

void base16(unsigned char input[16], char* output, bool isToUpper) {
    const char *format = isToUpper ? "%02X" : "%02x";
    char tmp[3] = {0};
    for(int i = 0; i < 16; i++) {
        sprintf(tmp, format, input[i]);
        strcat(output, tmp);
    }
}

void performMD5(char* input, bool isToUpper) {
    //MD5算法能够根据任意长度的数据计算出一个固定长度（128bit=16byte）的唯一数据
    unsigned char output[16] = {0};
    mbedtls_md5((unsigned char *)input, strlen(input), output);
    //为了便于比较，通常会把MD5运算后得到的128bit数据再用base16编码。因为每4bit可以表示一个十六进制字符，用十六进制表示就是32个字符。
    char hex[33] = {0};
    base16(output, hex, isToUpper);
    printf("md5(%s)=%s\n", input, hex);
}

int main(int argc, char* argv[]) {
    if (argc == 1) {
        showHelp();
    } else if (argc == 2) {
        if (strcmp("-h", argv[1]) == 0 
        || strcmp("--help", argv[1]) == 0
        || strcmp("-x", argv[1]) == 0
        || strcmp("-X", argv[1]) == 0) {
            showHelp();
        } else {
            performMD5(argv[1], 0);
        }
    } else {
        if (strcmp("-x", argv[1]) == 0) {
            performMD5(argv[2], 0);
        } else if (strcmp("-X", argv[1]) == 0) {
            performMD5(argv[2], 1);
        } else {
            showHelp();
        }
    }

    return 0;
}
