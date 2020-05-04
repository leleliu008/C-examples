//http://blog.fpliu.com/it/software/development/language/C/library/mbedTLS/include/sha1.h

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stdbool.h>
#include"mbedtls/sha1.h"

void showHelp() {
    printf("usage: sha1 [option] <str>\n");
    printf("option: -x lower case, default true\n");
    printf("        -X upper case\n");
    printf("example:sha1 -X sssssss\n");
    exit(1);
}

void base16(unsigned char input[20], char* output, bool isToUpper) {
    const char* format = isToUpper ? "%02X" : "%02x";
    char tmp[3] = {0};
    for(int i = 0; i < 20; i++) {
        sprintf(tmp, format, input[i]);
        strcat(output, tmp);
    }
}

void performSHA1(char* input, bool isToUpper) {
    //SHA-1算法能够根据任意长度的数据计算出一个固定长度（160bit=20byte）的唯一数据
    unsigned char output[20] = {0};
    mbedtls_sha1((unsigned char*)input, strlen(input), output);
    //为了便于比较，通常会把SHA-1运算后得到的160bit数据再用base16编码。因为每4bit可以表示一个十六进制字符，用十六进制表示就是40个字符。
    char hex[41] = {0};
    base16(output, hex, isToUpper);
    printf("sha1(%s)=%s\n", input, hex);
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
            performSHA1(argv[1], 0);
        }
    } else {
        if (strcmp("-x", argv[1]) == 0) {
            performSHA1(argv[2], 0);
        } else if (strcmp("-X", argv[1]) == 0) {
            performSHA1(argv[2], 1);
        } else {
            showHelp();
        }
    }

    return 0;
}
