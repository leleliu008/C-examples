//http://blog.fpliu.com/it/software/development/language/C/library/mbedTLS/include/md.h

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stdbool.h>
#include"mbedtls/md.h"

void showHelp() {
    printf("usage: hmac <option> <KEY> <CONTENT>\n");
    printf("option: -x lower case, default true\n");
    printf("        -X upper case\n");
    printf("example:hmac -X 123456 abcdefg\n");
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

void performHMAC_SHA256(char* key, char* input, bool isToUpper) {
    //SHA-256算法能够根据任意长度的数据计算出一个固定长度（256bit=32byte）的唯一数据
    unsigned char output[32] = {0};
    extern const mbedtls_md_info_t mbedtls_sha256_info;
    int resultCode = mbedtls_md_hmac(&mbedtls_sha256_info, (unsigned char*)key, strlen(key), (unsigned char*)input, strlen(input), output);
    if (0 == resultCode) {
        //为了便于比较，通常会把SHA-256运算后得到的256bit数据再用base16编码。因为每4bit可以表示一个十六进制字符，用十六进制表示就是64个字符。
        char hex[65] = {0};
        base16(output, hex, isToUpper);
        printf("hmac_sha256(content=%s,key=%s)=%s\n", input, key, hex);
    } else {
        printf("occrued error, code is %d\n", resultCode);
    }
}

int main(int argc, char* argv[]) {
    if (4 == argc) {
        if (strcmp("-x", argv[1]) == 0) {
            performHMAC_SHA256(argv[2], argv[3], false);
        } else if (strcmp("-X", argv[1]) == 0) {
            performHMAC_SHA256(argv[2], argv[3], true);
        } else {
            showHelp();
        }
    }

    return 0;
}
