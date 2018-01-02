#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"sha256.h"

void showHelp() {
    printf("usage: sha256 [option] <str>\n");
    printf("option: -x lower case, default true\n");
    printf("        -X upper case\n");
    printf("example:sha256 -X sssssss\n");
    exit(1);
}

void performSHA256(char *input, int flag) {
    unsigned char output[32] = {0};
    mbedtls_sha256((unsigned char *)input, strlen(input), output, 0);
    
    char format[5] = {0};
    format[0] = '%';
    format[1] = '0';
    format[2] = '2';
    if(flag) {
        format[3] = 'X';    
    } else {
        format[3] = 'x';
    }
    //转换为十六进制字符串
    char hex[65] = {0};
    char tmp[3] = {0};
    for(int i = 0; i < 32; i++) {
        sprintf(tmp, format, output[i]);
        strcat(hex, tmp);
    }
    
    printf("sha256(%s)=%s\n", input, hex);
}

int main(int argc, char *argv[]) {
    if(argc == 1) {
        showHelp();
    } else if(argc == 2) {
        if(strcmp("-h", argv[1]) == 0 
        || strcmp("--help", argv[1]) == 0
        || strcmp("-x", argv[1]) == 0
        || strcmp("-X", argv[1]) == 0) {
            showHelp();
        } else {
            performSHA256(argv[1], 0);
        }
    } else {
        if(strcmp("-x", argv[1]) == 0) {
            performSHA256(argv[2], 0);
        } else if(strcmp("-X", argv[1]) == 0) {
            performSHA256(argv[2], 1);
        } else {
            showHelp();
        }
    }

    return 0;
}
