//http://blog.fpliu.com/it/software/development/language/C/library/mbedTLS/include/sha256.h

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stdbool.h>
#include"mbedtls/sha256.h"

void showHelp() {
    printf("usage: sha256 [option] <str>\n");
    printf("option: -x lower case, default true\n");
    printf("        -X upper case\n");
    printf("example:sha256 -X sssssss\n");
    exit(1);
}

void base16(unsigned char input[32], char* output, bool isToUpper) {
    const char* format = isToUpper ? "%02X" : "%02x";
    char tmp[3] = {0};
    for(int i = 0; i < 32; i++) {
        sprintf(tmp, format, input[i]);
        strcat(output, tmp);
    }
}

void performSHA256(char* input, bool isToUpper) {
    //SHA-256算法能够根据任意长度的数据计算出一个固定长度（256bit=32byte）的唯一数据
    unsigned char output[32] = {0};
    mbedtls_sha256((unsigned char *)input, strlen(input), output, 0);
    //为了便于比较，通常会把SHA-256运算后得到的256bit数据再用base16编码。因为每4bit可以表示一个十六进制字符，用十六进制表示就是64个字符。
    char hex[65] = {0};
    base16(output, hex, isToUpper);
    printf("sha256(%s)=%s\n", input, hex);
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
            performSHA256(argv[1], 0);
        }
    } else {
        if (strcmp("-x", argv[1]) == 0) {
            performSHA256(argv[2], 0);
        } else if (strcmp("-X", argv[1]) == 0) {
            performSHA256(argv[2], 1);
        } else {
            showHelp();
        }
    }

    return 0;
}
